/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cmdarg.c]                   CMD Compiler                                */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "ptm.h"
#include "gls.h"
#include "cmdlib.h"
#include "cmda_cim.h"
#include "cmd_int.h"

#define command   CTX_EVAL(string,"Command")
#define version   CTX_EVAL(bool,"version")
#define shortform CTX_EVAL(bool,"shortform")
#define cmdenv    "CMDENV"
#define cimenv    "CIMENV"

static void addCtxEntry(CTX_T ctx, short idx, byte cat, cmdDfn d)
/* define ctx[idx] */
{ GLS_Tok id; cmdTyp typ; cmdOptVal ov; cmdVal v;
  cmdDfn_defn(d,&id,&typ,&ov,_);
  CTX_set(ctx,idx,
          GLS_Tok_string(id),
          cat,
          (byte)( cmdTyp_flag(typ) ? CTX_FLAG
                : cmdTyp_path(typ) ? CTX_PATH
                : cmdTyp_int (typ) ? CTX_INT
                : cmdTyp_str (typ) ? CTX_STRING
                : cmdTyp_name(typ) ? CTX_NAME
                : (C_BUG, 0)
                ),
          ( cat == CTX_ENV && cmdOptVal_non(ov) ?
            StrCopy("") : cmdOptVal_non(ov) ? 
            "" : cmdOptVal_val(ov,&v) ? CMD_Val_to_String(v) : (C_BUG, "")
          )
         );
}

static void CMD_to_CIM(cmdSource src, string fid)
/* Uebersetzung CMD --> CIM */
{ cmdDfn vargs = (cmdDfn)NULL; cmdDfn d; GLS_Tok id;
  CTX_T ctx = CTX_new((short)CMD_NumberOfValues(),fid);
  byte cat = CTX_ARG; short idx = 0; PT_Itr it;
  PT_FORALL(it,src)
  { PT_Term t = PT_termIT(it);
    if (PT_stateIT(it) == PT_POST && cmd_OptDoc(t,_)) /* TRICKY! */
      cat += 1;
    if (PT_stateIT(it) == PT_POST && cmd_Dfn(t,&d) )
    { 
      if ( cmdDfn_defn(d,&id,_,_,_) )
      {
        if( ! strcmp(GLS_Tok_string(id),CTX_VARG) ) vargs = d;
        else 
        {
          addCtxEntry(ctx,idx,cat,d); ++idx;
        }
      }
    }
  }
  if( vargs != (cmdDfn)NULL ) 
  {
    addCtxEntry(ctx,idx,CTX_ARG,vargs); ++idx;
  }
  bug0(idx == CMD_NumberOfValues(),"idx out of sync");
  if (CTX_EVAL(bool,"makeC")) 
  {
    CTX_C_Modul("CMDGEN",ctx,shortform);
#if !defined(_MSDOS) && !defined(MSDOS) 
    if( shortform ) CTX_C_Modul("CMDGEN",ctx,C_False);
#endif
  }
  else CTX_put(cimenv,ctx);
  CTX_free(ctx);
}

int main(int argc, string argv[])
{ cmdSource src;
  CTX_init_cmdarg(argc, argv);
  initSymbols();
  if (version) fprintf(stderr,"Welcome to 'cmd' Version '%s'\n",__DATE__);
  src = CMD_init(cmdenv,command,True);
  CMD_to_CIM(src,command); /* CMD -> CIM - Uebersetzer */
  CMD_done();
  freeSymbols();
  CTX_quit();
  BUG_CORE;
  return(0);
}
