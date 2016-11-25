/* [cmdd_cim.c] Context table for 'cmddoc'  */

#include "ctx.h"

void CTX_init_cmddoc(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(6,"cmddoc");
  CTX_set(ctx, 0,"InFile",  CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"OutFile", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"Template",CTX_OPT,CTX_PATH,  StrCopy("/p/styx/pat/pcmddoc_us.htm"));
  CTX_set(ctx, 3,"RefAlias",CTX_OPT,CTX_STRING,StrCopy("&amp;"));
  CTX_set(ctx, 4,"recursiv",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"PATH",    CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
