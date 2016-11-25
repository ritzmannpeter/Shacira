/* [styx_cim.c] Context table for 'styx'  */

#include "ctx.h"

void CTX_init_styx(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(9,"styx");
  CTX_set(ctx, 0,"Language",CTX_ARG,CTX_STRING,"");
  CTX_set(ctx, 1,"diagnose",CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 2,"verbose", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 3,"makeIMG", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 4,"makeINT", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 5,"makeC",   CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 6,"BINSTYX", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 7,"GENSTYX", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_set(ctx, 8,"SPESTYX", CTX_ENV,CTX_PATH,  StrCopy("."));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
