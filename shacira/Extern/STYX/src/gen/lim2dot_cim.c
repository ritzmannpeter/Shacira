/* [lim2dot_cim.c] Context table for 'lim2dot'  */

#include "ctx.h"

void CTX_init_lim2dot(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(3,"lim2dot");
  CTX_set(ctx, 0,"Img",     CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"OutFile", CTX_OPT,CTX_PATH,  StrCopy(""));
  CTX_set(ctx, 2,"Template",CTX_OPT,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
