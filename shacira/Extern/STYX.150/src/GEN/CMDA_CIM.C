/* [cmda_cim.c] Context table for 'cmdarg'  */

#include "ctx.h"

void CTX_init_cmdarg(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(6,"cmdarg");
  CTX_set(ctx, 0,"Command",CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"version",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 2,"makeC",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 3,"CMDENV", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 4,"CIMENV", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 5,"CMDGEN", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
