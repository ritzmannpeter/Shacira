/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [sink.c]                       Type: Sink                                */
/*                                                                          */
/* Copyright (c) 1993 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "otab.h"

/*!!
  This module [sink] implements a dynamic sink i.e. string stream. 
  It uses the printf-konform formatting facility.

  Note: Float and double values aren't supported yet.
*/

/*I---------------------------- The Type ---------------------------------- */

AbstractType( Sink ); /* Abstract sink / string stream type */

/*I---------------------------- Basics ------------------------------------ */

Sink Sink_open(void)
/* creates a new sink */
{
  return (Sink) OT_CREATE_ADT(char);
}

void Sink_putc(Sink s, char c)
/* adds character 'c' to sink 's' */
{
  OT_T_INS((OT_Tab)s,(long)c);
}

void Sink_puts(Sink s, string str)
/* adds string 'str' to sink 's' */
{ string aux = str;
  for(; *aux != '\0'; aux++ ) OT_T_INS((OT_Tab)s,(long)(*aux));
}

void Sink_puts_raw(Sink s, string str)
/* adds string 'str' in a printable format to sink 's' */
{ string aux = str;
  for(; *aux != '\0'; aux++ ) 
  { 
    if( !iscntrl(*aux) || isspace(*aux) )
      OT_T_INS((OT_Tab)s,(long)(*aux));
    else
    { char h[2+1];
      sprintf(h,"%02x",*aux);
      OT_T_INS((OT_Tab)s,(long)(h[0]));
      OT_T_INS((OT_Tab)s,(long)(h[1]));
    }
  }
}

string Sink_close(Sink s)
/* closes and converts sink 's' into a string;
   allocs memory
*/
{ OT_Tab tab = (OT_Tab) s;
  long   siz = OT_CNT(tab);
  string res = (string)NewMem(siz+1);
  long   i;
  for (i = 0; i < siz; i++)
    res[i] = OT_GET_small(char,tab,i);
  res[siz] = 0;
  OT_DEL_T(tab);
  return res;
}

bool Sink_empty(Sink s)
/* whether sink 's' is empty */
{
  return OT_CNT((OT_Tab)s) == 0;
}

/*I---------------------------- Printing ---------------------------------- */

ConcreteType(SinkEnv_T)
{
  Sink csink;    /* current sink      */
  bool FlagAlt;  /* alternative form  */
  bool FlagLeft; /* adjust left       */
  bool FlagZero; /* leading zeros     */
  int  FlagSign; /* sign for numerics */
  int  FlagLeng; /* length flag       */
  bool FlagPrec; /* 'Prec' seen       */
  bool FlagWide; /* 'Wide' seen       */
  int  Wide;
  int  Prec;
};

static void reset_sinkenv(SinkEnv_T sinkenv)
{
  sinkenv->FlagAlt  = False;
  sinkenv->FlagLeft = False;
  sinkenv->FlagZero = False;
  sinkenv->FlagSign = 0;
  sinkenv->FlagLeng = 0;
  sinkenv->FlagPrec = False;
  sinkenv->FlagWide = False;
  sinkenv->Wide     = 0;
  sinkenv->Prec     = 0;
}

static void init_sinkenv(SinkEnv_T sinkenv, Sink csink)
{
  sinkenv->csink = csink;
  reset_sinkenv(sinkenv);
}

static void t_putc(SinkEnv_T sinkenv, char cc)
{
  Sink_putc(sinkenv->csink,cc);
};

static void t_putstr(SinkEnv_T sinkenv, string s, int prec)
/* auxiluary */
{ int i;
  if (prec > strlen(s))
    prec = strlen(s);
  for (i = 0; i < prec; i++)
    t_putc(sinkenv,s[i]);
}

static void t_putspaces(SinkEnv_T sinkenv, int n)
/* auxiluary */
{ int i;
  for (i = 0; i < n; i++)
    t_putc(sinkenv,' ');
}

static void tp_c(SinkEnv_T sinkenv, char x)
{
  if (sinkenv->FlagLeft)
  {
    t_putc(sinkenv,x); t_putspaces(sinkenv,sinkenv->Wide-1);
  }
  else
  {
    t_putspaces(sinkenv,sinkenv->Wide-1); t_putc(sinkenv,x);
  }
}

static void tp_s(SinkEnv_T sinkenv, string x)
/* formats strings */
{
  if (!sinkenv->FlagPrec)
    sinkenv->Prec = strlen(x);
  if (sinkenv->FlagLeft)
  {
    t_putstr(sinkenv,x,sinkenv->Prec); 
    t_putspaces(sinkenv,sinkenv->Wide-sinkenv->Prec);
  }
  else
  {
    t_putspaces(sinkenv,sinkenv->Wide-sinkenv->Prec); 
    t_putstr(sinkenv,x,sinkenv->Prec);
  }
}

/* integer conversion */

void xultoa_aux(Sink dst, unsigned long value, int radix)
/* converts and adds long 'value' to sink 'dst' */
{ int           digit = value % radix;
  unsigned long rest  = value / radix;
  if (rest != 0) xultoa_aux(dst,rest,radix);
  Sink_putc(dst,"0123456789abcdefghijklmnopqrstuvwxyz"[digit]);
}

string xultoa(unsigned long value, int radix)
/* converts long 'value' into a string; allocs memory */
{ Sink res = Sink_open();
  xultoa_aux(res,value,radix);
  return Sink_close(res);
}

static void tp_d(SinkEnv_T sinkenv, long x, char form)
/* formats integers */
{ string xs; string sgn_str = ""; string alt_str = "";
  if (form == 'u' || form == 'x' || form == 'X' || form == 'o')
    xs = xultoa(x, form == 'o' ? 8 : form == 'u' ? 10 : 16 );
  else
  {
    if (x < 0)
    {
      sgn_str = "-";
      if (x != (1L << (8*sizeof(long)-1))) /* asymmetric of number range! */
        x = -x;
    }
    else
    {
      sgn_str = (sinkenv->FlagSign == '+') ? "+" : (sinkenv->FlagSign == ' ') ? " " : "";
    }
    xs =  xultoa(x,10);
  }
  /* alternativ Format */
  if (sinkenv->FlagAlt)
  {
    alt_str = (form == 'o' && x != 0) ? "0"
            : (form == 'X'          ) ? "0X"
            : (form == 'x'          ) ? "0x"
            : "";
  }
  /* effective PREC */
  { int actprec = strlen(xs) + strlen(sgn_str) + strlen(alt_str);
    int zeroes = sinkenv->Prec - actprec;
    if (!sinkenv->FlagPrec && sinkenv->FlagZero) zeroes = sinkenv->Wide - actprec;
    /* add zeroes */
    if (zeroes > 0 || strlen(sgn_str) != 0 || strlen(alt_str) != 0)
    { int i,n; Sink tmp = Sink_open();
      if (sgn_str[0] != 0) Sink_putc(tmp,sgn_str[0]);
      n = strlen(alt_str); for (i = 0; i < n; i++) Sink_putc(tmp,alt_str[i]);
      for (i = 0; i < zeroes; i++) Sink_putc(tmp,'0');
      n = strlen(xs); for (i = 0; i < n; i++) Sink_putc(tmp,xs[i]);
      FreeMem(xs);
      xs = Sink_close(tmp);
    }
    sinkenv->Prec = strlen(xs);
  }
  /* convert to uppercase if nessesary */
  if (form == 'X')
  { int i,n = strlen(xs);
    for (i = 0; i < n; i++) xs[i] = toupper(xs[i]);
  }
  if (sinkenv->FlagLeft)
  {
    t_putstr(sinkenv,xs,sinkenv->Prec); 
    t_putspaces(sinkenv,sinkenv->Wide-sinkenv->Prec);
  }
  else
  {
    t_putspaces(sinkenv,sinkenv->Wide-sinkenv->Prec); 
    t_putstr(sinkenv,xs,sinkenv->Prec);
  }
  FreeMem(xs);
}

void Sink_vprintf(Sink sink, string format, va_list args)
/* like 'vfprintf'
   The text resulting from 'format' and arguments 'args'
   will be added to 'sink'. 
*/
{ string s;
  ConcreteImp(SinkEnv_T) sinkenv;
  init_sinkenv(&sinkenv,sink);
  for (s = format; *s != 0; s+=1)
  {
    if (s[0] != '%')
      t_putc(&sinkenv,*s);
    else
    if (s[1] == '%')
    { t_putc(&sinkenv,'%'); s+=1; }
    else
    /* process formater: '%'{Flag}[width]['.'precision]['hl']Type */
    { string f = s+1;
      reset_sinkenv(&sinkenv);
    Flags:
      switch(f[0])
      {
        case '#' :                       sinkenv.FlagAlt  = True; f += 1; goto Flags;
        case '-' :                       sinkenv.FlagLeft = True; f += 1; goto Flags;
        case ' ' : if(!sinkenv.FlagSign) sinkenv.FlagSign = f[0]; f += 1; goto Flags;
        case '+' :                       sinkenv.FlagSign = f[0]; f += 1; goto Flags;
        default  : break;
      }
      switch(f[0]) /* Breite */
      {
        case '*' : sinkenv.Wide = va_arg(args,int); f += 1; sinkenv.FlagWide = True;
                   break;
        case '0' : sinkenv.FlagZero = True; goto Digit;
        case '1' : case '2' : case '3' : case '4' :
        case '5' : case '6' : case '7' : case '8' : case '9' :
      Digit:
          for (; isdigit(f[0]); f += 1)
            sinkenv.Wide = 10 * sinkenv.Wide + (f[0]-'0');
          break;
        default  : break;
      }
      if (f[0] == '.') /* Praezision */
      {
        f += 1; sinkenv.FlagPrec = True;
        if (f[0] == '*')
        {
          sinkenv.Prec = va_arg(args,int); f += 1;
        }
        else
        {
          for (; isdigit(f[0]); f += 1)
            sinkenv.Prec = 10 * sinkenv.Prec + (f[0]-'0');
        }
      }
      switch (f[0]) /* length: 'hl' */
      {
        case 'l' : case 'h' :
          sinkenv.FlagLeng = f[0]; f += 1;
      }
      switch (f[0])
      {
        /* Character */
        case 'c' : tp_c(&sinkenv,va_arg(args,char  )); s = f; break;
        case 's' : tp_s(&sinkenv,va_arg(args,string)); s = f; break;
        /* Integer   */
        case 'd' : case 'x' : case 'X' : case 'o' : case 'u' : case 'i' :
                   tp_d(&sinkenv,  
                          sinkenv.FlagLeng == 'l' ? va_arg(args,long)
                        : sinkenv.FlagLeng == 'h' ? va_arg(args,short)
                        : va_arg(args,int),
                        f[0]);
                   s = f; break;
        /* float NOT IMPLEMENTED (hint: use 'ecvt' from <stdlib.h> */
        default  : /* forgives all */ t_putc(&sinkenv,*s);
      }
    }
  }
}

void Sink_printf(Sink sink, string format, ...)
/* like 'fprintf'
   The text resulting from 'format' and arguments '...'
   will be added to 'sink'. 
*/
{ va_list args; 
  va_start(args,format);
  Sink_vprintf(sink, format,args);
  va_end(args);
}

string Str_printf(string format, ...)
/* like 'sprintf' 
   with resulting string from 'format' and arguments '...';
   allocs memory
*/
{ Sink sink;
  va_list args; va_start(args,format); 
  sink = Sink_open();
  Sink_vprintf(sink, format,args);
  va_end(args);
  return Sink_close(sink);
}

