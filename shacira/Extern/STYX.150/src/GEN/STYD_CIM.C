/* [styd_cim.c] Context table for 'stydoc'  */

#include "ctx.h"

void CTX_init_stydoc(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(12,"stydoc");
  CTX_set(ctx, 0,"InFile",  CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"OutFile", CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 2,"StyxPath",CTX_OPT,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 3,"Template",CTX_OPT,CTX_PATH,  StrCopy("/p/styx/pat/tstydoc_us.htm"));
  CTX_set(ctx, 4,"RefAlias",CTX_OPT,CTX_STRING,StrCopy("&amp;"));
  CTX_set(ctx, 5,"recursiv",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"prodcom", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 7,"keepNTs", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 8,"noClass", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 9,"exProds", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,10,"ignRRef", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx,11,"PATH",    CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
