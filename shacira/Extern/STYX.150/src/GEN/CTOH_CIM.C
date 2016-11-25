/* [ctoh_cim.c] Context table for 'ctoh'  */

#include "ctx.h"

void CTX_init_ctoh(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(9,"ctoh");
  CTX_set(ctx, 0,"CPATH",CTX_OPT,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 1,"HPATH",CTX_OPT,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 2,"PRJ",  CTX_OPT,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 3,"force",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 4,"ct",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"exp",  CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"DPATH",CTX_OPT,CTX_PATH,  StrCopy(""));
  CTX_set(ctx, 7,"DROOT",CTX_OPT,CTX_PATH,  StrCopy("index.html"));
  CTX_set(ctx, 8,"api",  CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
