/* [cmd__cim.c] Context table for 'cmd_test'  */

#include "ctx.h"

void CTX_init_cmd_test(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(5,"cmd_test");
  CTX_set(ctx, 0,"SomePath",CTX_ARG,CTX_PATH,  "");
  CTX_set(ctx, 1,"OptPath", CTX_OPT,CTX_PATH,  StrCopy("C:/:D:/msvc:/dev/rtc0:$BINSTYX/cmd.cim"));
  CTX_set(ctx, 2,"OptPath2",CTX_OPT,CTX_PATH,  StrCopy("/dev/rtc0"));
  CTX_set(ctx, 3,"CMDENV",  CTX_ENV,CTX_PATH,  StrCopy(""));
  CTX_set(ctx, 4,"vargs",   CTX_ARG,CTX_STRING,"");
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
