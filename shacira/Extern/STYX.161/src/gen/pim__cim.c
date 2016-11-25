/* [pim__cim.c] Context table for 'pim_test'  */

#include "ctx.h"

void CTX_init_pim_test(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(16,"pim_test");
  CTX_set(ctx, 0,"Language", CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"FileName", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"charset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 3,"skipset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 4,"binmode",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"wprint",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"prepar",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 7,"premac",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 8,"prefun",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"Start",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"xaron",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,11,"early",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,12,"shiftfun", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,13,"reducefun",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,14,"tree",     CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx,15,"BINSTYX",  CTX_ENV,CTX_PATH,  StrCopy("PATH"));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
