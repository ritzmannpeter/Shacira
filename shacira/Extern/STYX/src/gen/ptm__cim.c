/* [ptm__cim.c] Context table for 'ptm_img'  */

#include "ctx.h"

void CTX_init_ptm_img(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(17,"ptm_img");
  CTX_set(ctx, 0,"Language", CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"Img",      CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"FileName", CTX_OPT,CTX_PATH,  StrCopy(""));
  CTX_set(ctx, 3,"charset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 4,"skipset",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 5,"lookahead",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"binmode",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 7,"wprint",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 8,"prepar",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"premac",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"prefun",   CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,11,"Start",    CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,12,"xaron",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,13,"early",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx,14,"shiftfun", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,15,"reducefun",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,16,"BINSTYX",  CTX_ENV,CTX_PATH,  StrCopy("PATH"));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
