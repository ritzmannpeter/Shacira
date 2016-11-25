/* [com_cim.c] Context table for 'com'  */

#include "ctx.h"

void CTX_init_com(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(2,"com");
  CTX_set(ctx, 0,"r",    CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 1,"vargs",CTX_ARG,CTX_STRING,"");
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
