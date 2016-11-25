/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctx_imp.h]        Program Context Implementation Types                  */
/*                                                                          */
/* Copyright (c) 1993 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef CTX_IMP_INCL
#define CTX_IMP_INCL

#include "standard.h"

ConcreteType( CTX_L_Imp )
{
  /* static  */
  c_string  ide; /* Identifier */
  c_byte    cat; /* Category   */
  c_byte    typ; /* Type       */
  c_string  dft; /* Default    */
  /* dynamic */
  c_bool    asg; /* ?assigned  */
  StdCPtr   val; /* Value      */
};

ConcreteType( CTX_T_Imp )
{
  short     cnt;
  c_string  prg;
  CTX_L_Imp tbl; /* [cnt] */
};

#define CTX_T_IMP(tbl) ((CTX_T_Imp)(tbl))

#endif //_INCL
