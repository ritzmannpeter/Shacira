/* [genm_cim.c] Context table for 'genmak'  */

#include "ctx.h"

void CTX_init_genmak(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(8,"genmak");
  CTX_set(ctx, 0,"project", CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"rootpath",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 2,"xoutput", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 3,"woutput", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 4,"targets", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 5,"exclude", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 6,"dynamic", CTX_OPT,CTX_FLAG,  StrCopy("true"));
  CTX_set(ctx, 7,"version", CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
