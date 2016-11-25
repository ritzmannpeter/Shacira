/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [integer.c]                   Type: Integer                              */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

/*D
  Hinweis

  Die Performanz dieses Moduls ist einigermassen schwach.

  Ca. 400 Operation/sec netto fuer Zahlen maessiger Groesse auf 286/16MHz.
  Die Zeit wird dabei Ueberwiegend von den Speicherverwaltungsoperationen
  'Int_copy', 'Int_free' konsumiert. Gegenueber diesem Overhead sind die
  eigentlichen Rechenoperationen etwa so effizient wie die C-Arithmetik.

  Daher war ein Optimierungsversuch innerhalb dieser Speicherverwaltung
  mit einer Sonderbehandlung fuer kleine Zahlen nahezu wirkungslos (6%).

  Ein ziemliches Problem stellt die Division dar. Dass die ineffizenteste
  Operation ausgerechnet die in [rational] am haeufigsten angewendete ist,
  ist ein sehr unglueckliches Zusammentreffen. Die Performanz kann durch
  einen geschickteren Algorithmus sicher deutlich gesteigert werden.
*/

/*D
  Interessante Erweiterungen
  - min, max, gcd, ... ?
  - logische Operationen : '<<','>>','&','|','~', ...
*/

#include "standard.h"


/*I---------------------------- The Type --------------------------------- */

/*!!
   [integer] implements the algebraic operations for long integers with a
   maximum number of MAX_LONG digits. 
   An integer number is represented by its sign, length and digits: 
   N.value = N.Sgn * Sum { N.Dig[i] * (IntBase^i) | i in [0 .. N.Len - 1] }
*/

#define MIN_LONG ((long)(((long)1)<<(8*sizeof(long)-1)))
#define MAX_LONG (-((MIN_LONG)+1))

#define IntBase 256

ExternalType(Integer) // Abstract integer type
{
  int  Sgn;    /* -1; 0; +1  */
  int  Len;    /* >= 0       */
  byte Dig[1]; /* the digits */
};

/*I---------------------------- Basics ----------------------------------- */

/*!!
   In the following functions the integer operands won't be consumed and
   the resulting integers have to be released.
*/

Integer Int_cons(int Sgn, int Len, byte Dig[])
/* constructs an integer from sign 'Sgn', length 'Len' and digits 'Dig' */
{ Integer res; int i;
  assert0( Len >= 0, "invalid number length");
  res = (Integer) NewMem(SizeOf(Integer)+Len-1);
  res->Sgn = Sgn;
  res->Len = Len;
  for (i = 0; i < Len; i++)
    res->Dig[i] = Dig[i];
  return res;
}

void Int_des(Integer x, int *Sgn, int *Len, byte **Dig)
/* destructs an integer into sign 'Sgn', length 'Len' and digits 'Dig' */
{ Integer res = x;
  *Sgn = res->Sgn;
  *Len = res->Len;
  *Dig = res->Dig;
}

Integer Int_copy(Integer a)
/* copies integer 'a' */
{ Integer xa = a;
  return Int_cons(xa->Sgn,xa->Len,xa->Dig);
}

void Int_free(Integer a)
/* frees integer 'a' */
{ Integer xa = a;
  FreeMem(xa);
}

void Int_show(Integer a)
/* prints integer 'a' to stdout; for debugging */
{ Integer xa = a; int i;
  fprintf(STDOUT,"(Sgn = %d, Len = %d, Dig = [",xa->Sgn,xa->Len);
  for (i = 0; i < xa->Len; i++)
    fprintf(STDOUT,"%s%02x",i>0?", ":"",xa->Dig[i]);
  fprintf(STDOUT,"])\n");
}

/*I--------------------------- Conversion --------------------------------- */

ConcreteType(IntCnvEnv_T)
{
  byte *Temp;
  int  Tlen;
  int  Ttop;
};

static void Temp_init(IntCnvEnv_T cnvenv)
{
  cnvenv->Temp = (byte*)NewMem(1);
  cnvenv->Ttop = 1;
  cnvenv->Tlen = 0;
}

static void Temp_addc(IntCnvEnv_T cnvenv, byte c)
{
  if (cnvenv->Tlen == cnvenv->Ttop)
  { long i; byte* x;
    x = (byte*)NewMem(2*cnvenv->Ttop);
    for (i = 0; i < cnvenv->Ttop; i++)
      x[i] = cnvenv->Temp[i];
    FreeMem(cnvenv->Temp);
    cnvenv->Temp = x;
    cnvenv->Ttop *= 2;
  }
  cnvenv->Temp[cnvenv->Tlen++] = c;
}

static string Temp_done(IntCnvEnv_T cnvenv, string prefix)
/* result: prefix+reverse(Temp) */
{ int prelen = strlen(prefix);
  string res = (string)NewMem(prelen+cnvenv->Tlen+1);
  long i;
  for(i = 0; i < prelen; i++)
    res[i] = prefix[i];
  for (i = 0; i < cnvenv->Tlen; i++)
    res[i+prelen] = cnvenv->Temp[cnvenv->Tlen-1-i];
  res[cnvenv->Tlen+prelen] = 0;
  FreeMem(cnvenv->Temp);
  return res;
}

string Int_itoa(Integer a, int Base)
/* converts integer 'a' into a string; allocs memory */
{ Integer b = Int_copy(a); Integer xb = b; int Len; byte* Dig; string res;
  ConcreteImp(IntCnvEnv_T) cnvenv;
  assert0( 2 <= Base && Base <= 36, "Bad conversion base" );
  Temp_init(&cnvenv);
  if (xb->Sgn == 0)
  { res = Temp_done(&cnvenv,"0"); Int_free(b); return res; }
  Len = xb->Len;
  Dig = xb->Dig;
  while(Len > 0)
  { int rem, i;
    rem = 0;
    for (i = Len; i > 0; i--)
    { int tmp, quo;
      tmp = (int) IntBase * rem + Dig[i-1];
      quo = tmp / Base;
      rem = tmp % Base;
      Dig[i-1] = quo;
    }
    if (Dig[Len-1] == 0)
      Len -= 1;
    Temp_addc(&cnvenv,"0123456789abcdefghijklmnopqrstuvwxyz"[rem]);
  }
  res = Temp_done(&cnvenv,(xb->Sgn < 0) ? "-" : "");
  Int_free(b);
  return res;
}

static int digval(char d)
/* get value of digit 'd' */
{
  return INRANGE('0',d,'9') ? d - '0'
       : INRANGE('A',d,'Z') ? d - 'A' + 10
       : INRANGE('a',d,'z') ? d - 'a' + 10
       : -1;
}

bool Int_s_ok(string s, int Base)
/* whether string 's' represents an integer; not consuming 's' */
{
  assert0( INRANGE(2,Base,36), "Bad conversion base" );
  if (*s == '-') s += 1;     /* skip optional '-' */
  if (*s == 0) return False; /* no digits         */
  for (; *s; s++)
    if (!INRANGE(0,digval(*s),Base))
      return False;
  return True;
}

Integer Int_atoi(string sn, int Base)
/* converts string 'sn' into a number; not consuming 'sn' */
{ int Sgn = 1; Integer res;
  ConcreteImp(IntCnvEnv_T) cnvenv;
  assert1( Int_s_ok(sn,Base), "invalid number '%s'", sn );
  if (*sn == '-') { Sgn = -1; sn += 1; }
  for (Temp_init(&cnvenv); *sn; sn++)
  { int i, carry = digval(*sn);
    for (i = 0; i < cnvenv.Tlen; i++)
    { int temp;
      temp = Base * cnvenv.Temp[i] + carry;
      cnvenv.Temp[i] = temp % IntBase;
      carry   = temp / IntBase;
    }
    if (carry > 0) /* we must add a new digit */
      Temp_addc(&cnvenv,(byte)carry);
  }
  if (cnvenv.Tlen == 0) Sgn = 0;
  res = Int_cons(Sgn,cnvenv.Tlen,cnvenv.Temp);
  FreeMem(cnvenv.Temp);
  return res;
}

Integer Int_Cto(long a)
/* converts long 'a' into an integer */
{ unsigned long b; int len = 0; int sign; byte Dig[sizeof(long)];
  if (a == 0)
    return Int_cons(0,0,Dig);
  if (a == MIN_LONG)
  { sign = -1; b = a; }
  else
  if (a < 0)
  { sign = -1; b = -a; }
  else
  { sign = +1; b =  a; }
  while (b > 0)
  { Dig[len++] = (byte)(b % IntBase); b /= IntBase; }
  return Int_cons(sign,len,Dig);
}

bool Int_okC(Integer n)
/* whether integer 'n' can be converted into a long */
{ Integer xn = n; int i, sgn = xn->Sgn; unsigned long tmp = 0;
  if (sgn == 0) return True;
  if(xn->Len > sizeof(long)) return False;
  for (i = 0; i < xn->Len; i++)
    tmp = IntBase*tmp + xn->Dig[xn->Len-i-1];
  if (sgn < 0 && tmp == MIN_LONG) return True;
  return tmp <= MAX_LONG;
}

long Int_toC(Integer n)
/* converts integer 'n' into a long */
{ Integer xn = n; int i, sgn = xn->Sgn; unsigned long tmp = 0;
  if (sgn == 0) return 0;
  assert0(xn->Len <= sizeof(long),"Number too large");
  for (i = 0; i < xn->Len; i++)
    tmp = IntBase*tmp + xn->Dig[xn->Len-i-1];
  if (sgn < 0 && tmp == MIN_LONG)
    return (long)tmp;
  assert0(tmp <= MAX_LONG,"Number too large");
  return (sgn > 0) ? (long)tmp : -((long)tmp);
}

/*I--------------------------- Comparison --------------------------------- */

bool Int_is0(Integer x)
/* x == 0 ? */
{
  return x->Sgn == 0;
}

static int cmpAbsNums(Integer xa, Integer xb)
/* compares absolute values of numbers; sign cmpPosNums(a,b) == sign a-b */
{ int i;
  if (xa->Len != xb->Len)
    return xa->Len < xb->Len ? -1 : 1;
  /* fact: xa->Len == xb->Len */
  for (i = xa->Len-1; i >= 0; i--)
    if (xa->Dig[i] != xb->Dig[i])
      return xa->Dig[i] < xb->Dig[i] ? -1 : 1;
  return 0;
}

int Int_cmp(Integer a, Integer b)
/* a < b ? -1 : a == b ? 0 : +1 */
{ Integer xa = a, xb = b; int res;
  if (a == b) return 0;
  res = ( xa->Sgn == 0 )                ? -xb->Sgn
      : ( xb->Sgn == 0 )                ?  xa->Sgn
      : ( xa->Sgn > 0 && xb->Sgn > 0 )  ? cmpAbsNums(a,b)
      : ( xa->Sgn > 0 && xb->Sgn < 0 )  ?  1
      : ( xa->Sgn < 0 && xb->Sgn > 0 )  ? -1
      :/* xa->Sgn < 0 && xb->Sgn < 0 */   cmpAbsNums(b,a);
  return res;
}

bool Int_eq(Integer a, Integer b)
/* a == b ? */
{
  return Int_cmp(a,b) == 0;
}

bool Int_ne(Integer a, Integer b)
/* a != b ? */
{
  return Int_cmp(a,b) != 0;
}

bool Int_lt(Integer a, Integer b)
/* a < b ? */
{
  return Int_cmp(a,b) < 0;
}

bool Int_le(Integer a, Integer b)
/* a <= b ? */
{
  return Int_cmp(a,b) <= 0;
}

bool Int_gt(Integer a, Integer b)
/* a > b ? */
{
  return Int_cmp(a,b) > 0;
}

bool Int_ge(Integer a, Integer b)
/* a >= b ? */
{
  return Int_cmp(a,b) >= 0;
}

/*I---------------------------- Arithmetic -------------------------------- */

static Integer rplNumSgn(int Sgn, Integer a)
/* replaces the sign of integer 'a' */
{ Integer xa = a; xa->Sgn = Sgn; return a; }

static Integer addAbsNums(Integer a, Integer b)
/* adds the absolute values of two numbers */
{ Integer xa = a, xb = b;
  byte*   Dig = (byte*)NewMem(MAX(xa->Len,xb->Len)+1);
  int     i,carry = 0;
  Integer res;
  if (xa->Len < xb->Len)
  { Integer t = xa; xa = xb; xb = t; }
  /* xa->Len now >= xb->Len */
  for (i = 0; i < xb->Len; i++)
  {
    int t = (int) xa->Dig[i] + xb->Dig[i] + carry;
    carry = (t >= IntBase);
    Dig[i] = t - (carry ? IntBase : 0);
  }
  for (; i < xa->Len; i++)
  {
    int t = (int) xa->Dig[i] + carry;
    carry = (t >= IntBase);
    Dig[i] = t - (carry ? IntBase : 0);
  }
  if (carry != 0)
  {
    Dig[i] = carry;
    i += 1;
  }
  res = Int_cons((i>0),i,Dig);
  FreeMem(Dig);
  return res;
}

static Integer subPosAbsNums(Integer a, Integer b)
/* subtracts the absolute values two Numbers, where a >= b (positive result) */
{ Integer xa = a, xb = b; Integer res;
  byte *Dig = (byte*)NewMem(xa->Len); int i,carry = 0;
  for (i = 0; i < xb->Len; i++)
  {
    int t = (int) xa->Dig[i] - xb->Dig[i] - carry;
    carry = (t < 0);
    Dig[i] = t + (carry ? IntBase : 0);
  }
  for (; i < xa->Len; i++)
  {
    int t = (int) xa->Dig[i] - carry;
    carry = (t < 0);
    Dig[i] = t + (carry ? IntBase : 0);
  }
  while (i > 0 && Dig[i-1] == 0)
    i -= 1;
  res = Int_cons((i>0),i,Dig);
  FreeMem(Dig);
  return res;
}

static Integer subAbsNums(Integer a, Integer b)
/* subtracts the absolute values of Numbers */
{ int sig = cmpAbsNums(a,b);
  if ( sig == 0 ) return Int_Cto(0);
  if ( sig > 0 )  return               subPosAbsNums(a,b)  ;
    /* sig < 0 */ return rplNumSgn(-1, subPosAbsNums(b,a) );
}

int Int_sgn(Integer a)
/* signum of integer 'a' */
{
  return a->Sgn;
}

Integer Int_abs(Integer a)
/* absolute value |a| */
{ Integer xa = a;
  return Int_cons(xa->Sgn == 0 ? 0 : 1, xa->Len, xa->Dig);
}

Integer Int_neg(Integer a)
/* negation -a */
{ Integer xa = a;
  return Int_cons(-(xa->Sgn), xa->Len, xa->Dig);
}

Integer Int_add(Integer a, Integer b)
/* addition a + b */
{ Integer xa = a, xb = b; Integer res;
  if ( xa->Sgn == 0 ) return Int_copy(b);
  if ( xb->Sgn == 0 ) return Int_copy(a);
  res = ( xa->Sgn > 0 && xb->Sgn > 0 )  ?              addAbsNums(a,b)
      : ( xa->Sgn > 0 && xb->Sgn < 0 )  ?              subAbsNums(a,b)
      : ( xa->Sgn < 0 && xb->Sgn > 0 )  ?              subAbsNums(b,a)
      :/* xa->Sgn < 0 && xb->Sgn < 0 */   rplNumSgn(-1,addAbsNums(a,b));
  return res;
}

Integer Int_sub(Integer a, Integer b)
/* substraction a - b */
{ Integer xa = a, xb = b; Integer res;
  if ( a == b ) return Int_Cto(0);
  if ( xa->Sgn == 0 ) return Int_neg(b);
  if ( xb->Sgn == 0 ) return Int_copy(a);
  res = ( xa->Sgn > 0 && xb->Sgn > 0 )  ?              subAbsNums(a,b)
      : ( xa->Sgn > 0 && xb->Sgn < 0 )  ?              addAbsNums(a,b)
      : ( xa->Sgn < 0 && xb->Sgn > 0 )  ? rplNumSgn(-1,addAbsNums(a,b))
      :/* xa->Sgn < 0 && xb->Sgn < 0 */                subAbsNums(b,a);
  return res;
}

/* ------------------------- Multiplication ------------------------------- */

Integer Int_mlt(Integer a, Integer b)
/* multiplication a * b */
{ Integer xa = a, xb = b;
  int Len; byte* Dig;
  int i,j,carry;
  Integer res;
  if ( xa->Sgn == 0 ) return Int_copy(a);
  if ( xb->Sgn == 0 ) return Int_copy(b);
  Len = xa->Len + xb->Len;
  Dig = (byte*)NewMem(Len);
  for (i = 0; i < Len; i++)
    Dig[i] = 0;
  for (i = 0; i < xa->Len; i++)
  {
    carry = 0;
    for (j = 0; j < xb->Len; j++)
    { long temp;
      temp = (long) xa->Dig[i] * xb->Dig[j] + Dig[i+j] + carry;
      Dig[i+j] = temp % IntBase;
      carry    = temp / IntBase;
    }
    for (; carry > 0; j++)
    { int temp;
      temp = Dig[i+j] + carry;
      Dig[i+j] = temp % IntBase;
      carry    = temp / IntBase;
    }
  }
  while (Len > 0 && Dig[Len-1] == 0)
    Len -= 1;
  res = Int_cons(xa->Sgn == xb->Sgn ? 1 : -1, Len, Dig);
  FreeMem(Dig);
  return res;
}

/* ---------------------------- Division ---------------------------------- */

/*D
  Zur Division von ganzen Zahlen mit Rest

  Waehrend die Regelung fuer die Division von natuerlichen Zahlen feststeht,
  existiert eine solche fuer ganze Zahlen nicht. Vielmehr laesst sich die
  natuerlichzahlige Division in mehr als einer plausiblen Weise in die
  Arithmetik der ganzen Zahlen einbetten. Auch Regelungen, die auf den
  ersten Blick recht haarstreubend erscheinen moegen, koennen durchaus
  gewichtige Argumente fuer sich geltend machen. In "C" werden die
  folgenden Varianten verwendet ((-1)/2==0, (-1)>>1==(-1)).

           a    b  |  quo     rem |  div     mod
          ---------+--------------+-------------
           7 /  3  =   2 rest  1  =   2 rest  1
           7 / -3  =  -2 rest  1  =  -2 rest  1
          -7 /  3  =  -2 rest -1  =  -3 rest  2
          -7 / -3  =   2 rest -1  =   3 rest  2

  Fuer die erste Variante gilt: ("quo" ist der Quotient, "rem" der Rest)

    (Elimination)  ( a quo b ) * b + ( a rem b ) = a
                   0 <= | a rem b | < | b |

                   | a quo b |     = | a | quo | b |
                   | a rem b |     = | a | rem | b |
                   sign( a quo b ) = sign(a) * sign(b)
                   sign( a rem b ) = sign(a)

  Beim Uebergang zu rationalen Zahlen muss mit normalisierten Bruechen
  gearbeitet werden ( a/b mit a in Integer, b in Natural, gcd(a,b) = 1).

  Ferner ist zu beachten, dass die Folge a(i) = [ i rem k | i in Integer ]
  an der Stelle 0 einen Symmetriebruch erfaehrt. Der folgende Funktions-
  graph (k = 5) visualisiert das Problem:

                                   |
                                   |   x    x    x    x    x
            (y = x rem 5)          |  x    x    x    x    x
                                   | x    x    x    x    x    ...
                                   |x    x    x    x    x    x
    -----------x----x----x----x----x----x----x----x----x----x-------->
              x    x    x    x    x|
           ...    x    x    x    x |
                 x    x    x    x  |
                x    x    x    x   |
                                   |

  Ist man hingegen an einer glatten Restfunktion interessiert,
  kann man definieren:

                          |         a rem b    für a >= 0
               a mod b = -|         a rem b    für a <  0 /\ a rem b == 0
                          | |b| + ( a rem b )  für a <  0 /\ a rem b != 0

                                   |
     (y = x mod 5) x    x    x    x|   x    x    x    x    x
                  x    x    x    x |  x    x    x    x    x
        ...      x    x    x    x  | x    x    x    x    x    ...
           x    x    x    x    x   |x    x    x    x    x    x
    ------x----x----x----x----x----x----x----x----x----x----x-------->
                                   |

  Der zugehoerige Quotient ist

                    |            a quo b    fuer a >= 0
         a div b = -|            a quo b    fuer a <  0 /\ a rem b == 0
                    | sgn(a) + ( a quo b )  fuer a <  0 /\ a rem b != 0

  Um die Verwirrung komplett zu machen, sei darauf hingewiesen, dass noch
  weitere Definitionen der Division und des Rest exstieren. Man denke etwa
  daran, bei der Division zur kleineren Zahl hin zu runden, und nicht zur
  0 hin, wie in den obigen Faellen.
*/

static bool aux_cmpVals(byte a[], int ByteOff, int blen, byte b[], int BitOff)
/* a cmpabs (b * (2 ** (8*ByteOff+BitOff) */
{ int i;
  for (i = blen; i >= 0; i--)
  { byte temp; int res;
    temp = (((i<blen) ? b[i]:0) << BitOff) | ((i ? b[i-1]:0) >> (8-BitOff));
    res  = (int) a[i+ByteOff] - temp;
    if (res != 0)
      return res < 0 ? -1 : 1;
  }
  return 0;
}

static void aux_subVals(byte a[], int ByteOff, int blen, byte b[], int BitOff)
/* a -= (b * (2 ** (8*ByteOff+BitOff) */
{ int i, carry = 0;
  for (i = 0; i <= blen; i++)
  { byte temp; int t;
    temp = (((i<blen) ? b[i]:0) << BitOff) | ((i ? b[i-1]:0) >> (8-BitOff));
    t = (int) a[i+ByteOff] - temp - carry;
    carry = (t < 0);
    a[i+ByteOff] = t + (carry ? IntBase : 0);
  }
  assert0( carry == 0, "internal error");
}

/*forward*/void Int_quo_rem(Integer a, Integer b, Integer *quo, Integer *rem);

Integer Int_quo(Integer a, Integer b)
/* division a / b */
{ Integer res;
  Int_quo_rem(a,b,&res,_);
  return res;
}

Integer Int_rem(Integer a, Integer b)
/* remainder a % b */
{ Integer res;
  Int_quo_rem(a,b,_,&res);
  return res;
}

/*D
  Technische Hinweise

  Fuer die Division teilen wir die Variable Dig[] in zwei Komponenten:

  * die Ziffern des Divident/Rest   Dig[0..pos-1]
  * 0 in                            Dig[pos]
  * die Ziffern des Quotienten      Dig[pos+1..xa->Len+1]

  Ferner ist von Bedeutung, dass der Divident um eine Ziffer (0) verlaengert
  wird. Wir tragen damit dem Umstand normalisierend Rechnung, dass der
  Divisor durch die Binaerverschiebung mit Hilfe des BitOff in den voran
  stehenden Hilfsroutinen um je ein Byte verlaengert erscheint.
*/

void Int_quo_rem(Integer a, Integer b, Integer *quo, Integer *rem)
/* *quo = a/b; *rem = a%b */
{ Integer xa = a, xb = b; byte* Dig; int i,j,pos;
  assert0(xb->Sgn != 0, "zero division");
  /* The following shortcuts assert that |a| > |b|. */
  if ( xa->Sgn == 0 )
  {
    if (quo != NULL) *quo = Int_copy(a);
    if (rem != NULL) *rem = Int_copy(a);
    return;
  }
  { int tmp = cmpAbsNums(a,b);
    if (tmp <  0)
    {
      if (quo != NULL) *quo = Int_Cto(0);
      if (rem != NULL) *rem = ( xa->Sgn > 0
                                ? xb->Sgn > 0
                                  ? Int_copy(a)
                                  : Int_neg(a)
                                : xb->Sgn > 0
                                  ? Int_copy(a)
                                  : Int_neg(a) );
      return;
    }
    if (tmp == 0)
    {
      if (quo != NULL) *quo = Int_Cto(xa->Sgn == xb->Sgn ? 1 : -1);
      if (rem != NULL) *rem = Int_Cto(0);
      return;
    }
  }
  /* We start to divide here */
  Dig = (byte*)NewMem(xa->Len+2);
  for (i = 0; i < xa->Len; i++)
    Dig[i] = xa->Dig[i];
  Dig[xa->Len] = 0;   /* extra most significant zero */
  pos = xa->Len+1;    /* position of quotient in Dig */
  for (i = xa->Len - xb->Len; i >= 0; i--)
  { int res = 0;
    for (j = 7; j >= 0; j--)
    {
      res *= 2;
      if (aux_cmpVals(Dig,i,xb->Len,xb->Dig,j) >= 0)
      { res += 1; aux_subVals(Dig,i,xb->Len,xb->Dig,j); }
    }
    Dig[pos] = res; pos -= 1; bug0(Dig[pos] == 0, "Dig[pos] != 0");
  }
  /* the remainder in Dig[0..pos-1], the quotient in Dig[pos+1..xa->Len+1] */
  for (i = pos-1; i >= 0; i--) if (Dig[i] != 0) break;
  if (rem!=NULL) *rem=Int_cons(i < 0 ? 0 : xa->Sgn,i+1,Dig);
  if (quo!=NULL)
  { int al;
    for(al = xa->Len; al >= pos && Dig[al+1] == 0; al -= 1);
    *quo = Int_cons(al+1-pos==0?0:(xa->Sgn==xb->Sgn?1:-1),al+1-pos,Dig+pos+1);
  }
  FreeMem(Dig);
}

Integer Int_gcd(Integer a, Integer b)
/* greatest common divisor of integer 'a' and 'b' */
{
  if (Int_sgn(a) < 0)
  { Integer tmp = Int_neg(a);
    Integer res = Int_gcd(tmp,b);
    Int_free(tmp);
    return res;
  }
  if (Int_sgn(b) < 0)
  { Integer tmp = Int_neg(b);
    Integer res = Int_gcd(a,tmp);
    Int_free(tmp);
    return res;
  }
  if (Int_sgn(b) == 0)
  {
    return (Int_sgn(a) == 0) ? Int_Cto(1) : Int_copy(a);
  }
  { Integer tmp = Int_rem(a,b);
    Integer res = Int_gcd(b,tmp);
    Int_free(tmp);
    return res;
  }
}

Integer Int_exp(Integer b, long n)
/* exponent b ^ n */
{ long p; Integer exp, sqr, res;
  assert0( n >= 0, "negative exponent" );
  if( n == 0 ) return Int_Cto(1);
  if( ( n & 1 ) == 0 ) 
  {
    p = n >> 1;
    exp = Int_exp(b,p);
    sqr = Int_mlt(exp,exp);
    Int_free(exp);
    return sqr;
  }
  else                           
  {
    p = ( n - 1 ) >> 1;
    exp = Int_exp(b,p);
    sqr = Int_mlt(exp,exp);
    res = Int_mlt(sqr,b);
    Int_free(exp); Int_free(sqr);
    return res;
  }
}

