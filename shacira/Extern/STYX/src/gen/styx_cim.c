/* [styx_cim.c] Context table for 'styx'  */

#include "ctx.h"

void CTX_init_styx(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(14,"styx");
  CTX_set(ctx, 0,"Language",  CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"diagnose",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 2,"verbose",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 3,"conflicts", CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 4,"makeIMG",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"makeINT",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"makeANT",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 7,"makeC",     CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 8,"export",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 9,"exportTMPL",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"shortform", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,11,"BINSTYX",   CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx,12,"GENSTYX",   CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx,13,"SPESTYX",   CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
