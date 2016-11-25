/* [styp_cim.c] Context table for 'stypp'  */

#include "ctx.h"

void CTX_init_stypp(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(15,"stypp");
  CTX_set(ctx, 0,"srclang",  CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"dstlang",  CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 2,"filename", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 3,"charset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 4,"wprint",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"prepar",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 6,"premac",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 7,"prefun",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 8,"Start",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"xaron",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,10,"early",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,11,"shiftfun", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,12,"reducefun",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,13,"ppfun",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,14,"PATH",     CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
