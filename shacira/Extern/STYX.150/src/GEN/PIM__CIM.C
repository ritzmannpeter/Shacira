/* [pim__cim.c] Context table for 'pim_test'  */

#include "ctx.h"

void CTX_init_pim_test(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(15,"pim_test");
  CTX_set(ctx, 0,"Language", CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"FileName", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"charset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 3,"binmode",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 4,"wprint",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"prepar",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 6,"premac",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 7,"prefun",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 8,"Start",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"xaron",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,10,"early",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,11,"shiftfun", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,12,"reducefun",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,13,"tree",     CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx,14,"PATH",     CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
