/* [bin__cim.c] Context table for 'bin_dump'  */

#include "ctx.h"

void CTX_init_bin_dump(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(1,"bin_dump");
  CTX_set(ctx, 0,"Filename",CTX_ARG,CTX_PATH,  "");
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
