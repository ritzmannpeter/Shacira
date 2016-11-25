/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [rational.c]                  Type: Rational                             */
/*                                                                          */
/* Copyright (c) 1995 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "integer.h"

#include "sink.h"

/*I---------------------------- The Type --------------------------------- */

/*!!
   [rational] implements the algebraic operations for rationals.
   A rational number is represented by its numerator and denominator.  
   NF: gcd(Z,N)=1 /\ N>0 
*/

ExternalType(Rational) /* Abstract rational type */
{
  Integer Z;
  Integer N;
};

/*I--------------------------- Basics ------------------------------------- */

/*!!
   In the following functions the integer and rational operands won't be 
   consumed and the resulting integer or rational have to be released.
*/

Rational Rat_cons(Integer Z, Integer N)
/* constructs a rational 
   from numerator 'Z' and denominator 'N' 
*/
{ Rational res = New(Rational);
  res->Z = Z;
  res->N = N;
  return res;
}

Rational Rat_copy(Rational a)
/* copies rational 'a' */
{ Rational xa = a;
  return Rat_cons(xa->Z,xa->N);
}

void Rat_free(Rational a)
/* frees rational 'a' */
{ Rational xa = a;
  Int_free(xa->Z);
  Int_free(xa->N);
  FreeMem(xa);
}

Rational Rat_Int_to(Integer a)
/* constructs a rational from numerator 'a' ( a/1 ) */
{
  return Rat_cons(Int_copy(a),Int_Cto(1));
}

Rational Rat_Int_div(Integer a, Integer b)
/* divides integer 'a' thru integer 'b' 
   giving a rational 
*/
{
  assert0(Int_sgn(b) != 0,"division by zero");
  if (Int_sgn(b) < 0)
  { Integer xa = Int_neg(a);
    Integer xb = Int_neg(b);
    Rational res = Rat_Int_div(xa,xb);
    Int_free(xa); Int_free(xb);
    return res;
  }
  { Integer q = Int_gcd(a,b);
    Integer z = Int_quo(a,q);
    Integer n = Int_quo(b,q);
    Rational res = Rat_cons(z,n);
    Int_free(q);
    return res;
  }
}

void Rat_des(Rational r, Integer* z, Integer* n)
/* destructs rational 'r' 
   to numerator 'z' and denominator 'n'
*/
{
  *z = r->Z;
  *n = r->N;
}

Integer Rat_nom(Rational r)
/* copies numerator of rational 'r' */
{
  return Int_copy(r->Z);
}

Integer Rat_den(Rational r)
/* copies denominator of rational 'r' */
{
  return Int_copy(r->N);
}

void showRat(Rational r)
/* prints rational 'r' to stdout; for debugging */
{ string z = Int_itoa(r->Z,10);
  string n = Int_itoa(r->N,10);
  fprintf(STDOUT,"%s / %s",z,n);
  FreeMem(z); FreeMem(n); 
}

/*I--------------------------- Comparison --------------------------------- */

bool Rat_is0(Rational r)
/* r == 0 ? */
{
  return Int_is0(r->Z);
}

int Rat_cmp(Rational a, Rational b)
/* a < b ? -1 : a == b ? 0 : 1 */
{ Integer ia  = Int_mlt(a->Z,b->N),
          ib  = Int_mlt(a->N,b->Z),
          id  = Int_sub(ia,ib);
  int     res = Int_sgn(id);
  Int_free(ia); Int_free(ib); Int_free(id);
  return res;
}

bool Rat_eq(Rational a, Rational b)
/* a == b ? */
{
  return Rat_cmp(a,b) == 0;
}

bool Rat_ne(Rational a, Rational b)
/* a != b ? */
{
  return Rat_cmp(a,b) != 0;
}

bool Rat_lt(Rational a, Rational b)
/* a < b ? */
{
  return Rat_cmp(a,b) == -1;
}

bool Rat_le(Rational a, Rational b)
/* a <= b ? */
{
  return Rat_cmp(a,b) <= 0;
}

bool Rat_gt(Rational a, Rational b)
/* a > b ? */
{
  return Rat_cmp(a,b) == 1;
}

bool Rat_ge(Rational a, Rational b)
/* a >= b ? */
{
  return Rat_cmp(a,b) >= 0;
}

/*I---------------------------- Arithmetic -------------------------------- */

int Rat_sgn(Rational r)
/* signum of rational 'r' (0,-1,1) */
{
  return Int_sgn(r->Z);
}

Rational Rat_abs(Rational r)
/* absolute value |r| */
{
  return (Rational)Rat_cons(Int_abs(r->Z),Int_copy(r->N));
}

Rational Rat_neg(Rational r)
/* negation -r */
{
  return (Rational)Rat_cons(Int_neg(r->Z),Int_copy(r->N));
}

Rational Rat_inv(Rational r)
/* inverse 1 / r ( r != 0 ) */
{ int Zsgn = Int_sgn(r->Z), Nsgn = Int_sgn(r->N);
  assert0( Nsgn != 0, "division by zero" );
  return ( Zsgn == -1 )
         ? (Rational)Rat_cons(Int_neg(r->N),Int_copy(r->Z))
         : (Rational)Rat_cons(Int_copy(r->N),Int_copy(r->Z));
}

static Rational Rat_lineOp(Rational a, Rational b, bool subtract)
{ Integer  ia  = Int_mlt(a->Z,b->N);
  Integer  ib  = Int_mlt(a->N,b->Z);
  Integer  iz  = subtract?Int_sub(ia,ib):Int_add(ia,ib);
  Integer  in  = Int_mlt(a->N,b->N);
  Rational res = Rat_Int_div(iz,in); 
  Int_free(iz); Int_free(in);
  Int_free(ia); Int_free(ib);
  return res;
}

Rational Rat_add(Rational a, Rational b)
/* addition a + b */
{
  return Rat_lineOp(a,b,False);
}

Rational Rat_sub(Rational a, Rational b)
/* substraction a - b */
{
  return Rat_lineOp(a,b,True);
}

Rational Rat_mlt(Rational a, Rational b)
/* multiplication a * b */
{ Integer  iz  = Int_mlt(a->Z,b->Z),
           in  = Int_mlt(a->N,b->N);
  Rational res = Rat_Int_div(iz,in); 
  Int_free(iz); Int_free(in);
  return res;
}

Rational Rat_quo(Rational a, Rational b)
/* division a / b */
{ Integer  iz, in; int Nsgn = Int_sgn(b->Z);
  Rational res;
  assert0( Nsgn != 0, "division by zero" );
  iz  = Int_mlt(a->Z,b->N),
  in  = Int_mlt(a->N,b->Z);
  res = Rat_Int_div(iz,in); 
  Int_free(iz); Int_free(in);
  return res;
}

/*I--------------------------- Conversion --------------------------------- */

/*!
  <p><b>Q --> Z</b>
*/

Integer Rat_floor(Rational r)
/* greatest Integer z with z <= r */
{ 
  return Int_quo(r->Z,r->N);
}

Integer Rat_ceiling(Rational r)
/* smallest Integer z with z >= r */
{ Integer  i   = Int_add(r->Z,r->N),
           iz  = Int_sub(i,Int_Cto(1)),
           res = Int_quo(iz,r->N);
  Int_free(i); Int_free(iz);
  return res;
}

Integer Rat_round(Rational r)
/* rounding */
{ Rational q   = Rat_cons(Int_Cto(1),Int_Cto(2)),
           p   = Rat_add(r,q);
  Integer  res = Rat_floor(p);
  Rat_free(q); Rat_free(p);
  return res;
}

/*!
  <p><b>Q --> Q</b>
*/

static Rational Rat_fix
                (
                  Rational r, int b, long n, Integer (*toInt)(Rational q)
                )
{ Integer  ba = Int_Cto(b),
           in = Int_exp(ba,n), iz;
  Rational rn = Rat_Int_to(in),
           rz = Rat_mlt(r,rn), res;
  iz  = (*toInt)(rz);
  res = Rat_Int_div(iz,in);
  Int_free(ba); Int_free(in); Int_free(iz);
  Rat_free(rz); Rat_free(rn);
  return res;
}

Rational Rat_fix_floor(Rational r, int b, long n)
/* Rational(floor(r * b ^ n), b ^n) */
{
  return Rat_fix(r,b,n,Rat_floor);
}

Rational Rat_fix_ceiling(Rational r, int b, long n)
/* Rational(ceiling(r * b ^ n), b ^n) */
{
  return Rat_fix(r,b,n,Rat_ceiling);
}

Rational Rat_fix_round(Rational r, int b, long n)
/* Rational(round(r * b ^ n), b ^n) */
{
  return Rat_fix(r,b,n,Rat_round);
}

/*!
  <p><b>Q <--> String</b>
*/

string Rat_to_Str(Rational r, int Base, int Digits)
/* converts rational 'r' into a string; allocs memory */
{ Integer quo, rem; string res;
  assert0( 2 <= Base && Base <= 36, "Bad conversion base" );
  assert0( Digits >= 0, "negative number of digits" );
  Int_quo_rem(r->Z,r->N,&quo,&rem);
  res = Int_itoa(quo,Base);
  if (Digits > 0)
  {
    Integer i1 = Int_Cto(Base);
    Integer i2 = Int_exp(i1,Digits);
    Integer i9 = Int_abs(rem);
    Integer i3 = Int_mlt(i9,i2);
    Integer i4 = Int_quo(i3,r->N);
    string  s1 = Int_itoa(i4,Base);
    Sink    si = Sink_open();
    int i, len = strlen(s1);
    if (Int_sgn(r->Z)<0 && Int_sgn(quo)==0)
      Sink_putc(si,'-');
    Sink_printf(si,"%s.",res);
    for (i = 0; i < Digits-len; i++)
      Sink_putc(si,'0');
    Sink_printf(si,"%s",s1);
    Int_free(i1); Int_free(i2); Int_free(i3); Int_free(i4); Int_free(i9);
    FreeMem(res); FreeMem(s1); res = Sink_close(si);
  }
  Int_free(quo); Int_free(rem);
  return res;
}

Rational Rat_Str_to(string s, int Base)
/* converts string 's' into a rational; not consuming 's' */
/* assuming 'Rat_Str_ok(s,Base)' */
{ int len = strlen(s), i;
  assert0( 2 <= Base && Base <= 36, "Bad conversion base" );
  for (i = 0; i < len; i++) if ( s[i] == '.' ) break;
  if (s[i] != '.')
  { Integer  tmp = Int_atoi(s,Base);
    Rational res = Rat_Int_to(tmp);
    Int_free(tmp);
    return res;
  }
  else
  { Integer  b   = Int_Cto(Base);
    Integer  den = Int_exp(b,(long)(len-i-1));
    string   s1  = SubStrCopy(s,i);
    string   s2  = StrCopy(s+i+1);
    string   s3  = Str_printf("%s%s",s1,s2);
    Integer  num = Int_atoi(s3,Base);
    Rational res = Rat_Int_div(num,den);
    Int_free(b); Int_free(den); Int_free(num);
    FreeMem(s1); FreeMem(s2); FreeMem(s3);
    return res;
  }
}

static int digval(char d)
/* return value of digit d */
{
  return INRANGE('0',d,'9') ? d - '0'
       : INRANGE('A',d,'Z') ? d - 'A' + 10
       : INRANGE('a',d,'z') ? d - 'a' + 10
       : -1;
}

bool Rat_s_ok(string s, int Base)
/* whether string 's' represents a fix point numeral */
{
  assert0( INRANGE(2,Base,36), "Bad conversion base" );
  if (*s == '-') s += 1;     /* skip optional '-' */
  if (*s == 0) return False; /* no digits */
  for (; *s; s++) if (!INRANGE(0,digval(*s),Base)) return False;
  if (*s == 0) return True;
  if (*s != '.') return False; s++;
  if (*s == 0) return False; /* no digits */
  for (; *s; s++) if (!INRANGE(0,digval(*s),Base)) return False;
  return (*s == 0);
}

/*I--------------------------- Xaron Support -------------------------------- */

void Rat_references(Rational x, StdCPtr (*act)(StdCPtr r))
/* performs 'act' on all pointer references in rational 'x'
   ( garbage collection service for xaron )
*/
{
/*
  x->Z = (Integer)((*act)(x->Z));
  x->N = (Integer)((*act)(x->N));
*/
}
