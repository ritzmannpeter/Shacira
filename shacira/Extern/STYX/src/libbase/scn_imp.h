/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_imp.h]               Scanner Implementation                         */
/*                                                                          */
/* To be used only in [scn_io.c] and [regset.c]                             */
/*                                                                          */
/* Copyright (c) 1993 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef SCN_IMP_INCL
#define SCN_IMP_INCL

#include "standard.h"

/* all extended ascii */
//#define SCN_CHAR_SET_SIZE (256) 
/* all UCS4 character */
#define SCN_CHAR_SET_SIZE   (0xFFFFFFFFu) 
//#define SCN_CHAR_SET_SIZE   (~((wc_char)0)) 

/* token IDs within a dyck scanner */
#define SCN_DYCKTOKEN_PREFIX  1
#define SCN_DYCKTOKEN_SUFFIX  2
#define SCN_DYCKTOKEN_PATTERN 3

#define Scn_IMP(X) ((scn_t)(X))
#define Scn_ADT(X) ((Scn_T)(X))

#define SCN_Edges(X) (Scn_IMP(X)->StaEdg[Scn_IMP(X)->States])

ConcreteType(scn_t)
{
  c_string   Name;     /* lexical language ( or group ) name  */
  /* single scanner */
  short      States;   /* number of states or 0               */
  short      Tokens;   /* number of tokens or 0               */
  long      *StaEdg;   /* [States] -> first edge              */
  short     *StaFin;   /* [States] -> (-1 or token)           */
  wc_char   *EdgeC ;   /* [Edges]  -> lower character         */
  long      *EdgeS ;   /* [Edges]  -> State                   */
  c_string  *TokId ;   /* [Tokens] -> string                  */
  c_byte    *Flags ;   /* [Tokens] -> properties, e.g. ignore */
  /* group scanner  */
  short      Groups;   /* number of groups or 0               */
  scn_t     *GrpScn;   /* group scanners                      */
  short     *Switch;   /* [Tokens] -> Group                   */
  /* dyck token specification */
  short      dyckcnt;  /* number of dyck tokens               */
  short     *dyckidx;  /* [dyckcnt] -> token index            */
  scn_t     *dyckpat;  /* [dyckcnt] -> dyck scanner           */
};

#endif
