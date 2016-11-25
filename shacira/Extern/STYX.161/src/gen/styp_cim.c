/* [styp_cim.c] Context table for 'stypp'  */

#include "ctx.h"

void CTX_init_stypp(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(16,"stypp");
  CTX_set(ctx, 0,"srclang",  CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"dstlang",  CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 2,"filename", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 3,"charset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 4,"skipset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 5,"wprint",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"prepar",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 7,"premac",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 8,"prefun",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"Start",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"xaron",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,11,"early",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,12,"shiftfun", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,13,"reducefun",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,14,"ppfun",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,15,"BINSTYX",  CTX_ENV,CTX_PATH,  StrCopy("PATH"));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
