/* [refo_cim.c] Context table for 'reformat'  */

#include "ctx.h"

void CTX_init_reformat(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(2,"reformat");
  CTX_set(ctx, 0,"FileName",  CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"PageLength",CTX_OPT,CTX_INT,   StrCopy("65"));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
