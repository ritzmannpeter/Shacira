/* [prdp_cim.c] Context table for 'prdps'  */

#include "ctx.h"

void CTX_init_prdps(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(14,"prdps");
  CTX_set(ctx, 0,"project", CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"diagnose",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 2,"changes", CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 3,"lexsort", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 4,"strict",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"multisrc",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"warnings",CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 7,"makeNANO",CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 8,"makeLIST",CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 9,"replace", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"pathsep", CTX_OPT,CTX_STRING,StrCopy(";"));
  CTX_set(ctx,11,"premac",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,12,"PRDPS",   CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_set(ctx,13,"vargs",   CTX_ARG,CTX_STRING,"");
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
