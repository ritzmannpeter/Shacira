/* [meta_cim.c] Context table for 'metastyx'  */

#include "ctx.h"

void CTX_init_metastyx(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(4,"metastyx");
  CTX_set(ctx, 0,"MetaFile",CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"InFile",  CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"OutFile", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 3,"PATH",    CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
