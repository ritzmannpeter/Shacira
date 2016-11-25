/* [xml_test_cim.c] Context table for 'xml_test'  */

#include "ctx.h"

void CTX_init_xml_test(int argc, c_string argv[])
{ CTX_T ctx;
  ctx = CTX_new(4,"xml_test");
  CTX_set(ctx, 0,"file",CTX_OPT,CTX_STRING,StrCopy(""));
  CTX_set(ctx, 1,"cset",CTX_OPT,CTX_STRING,StrCopy("ISO-8859-1"));
  CTX_set(ctx, 2,"all", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_set(ctx, 3,"dtd", CTX_OPT,CTX_FLAG,  StrCopy("false"));
  CTX_ctx_set(ctx);
  CTX_interprete(argc, argv);
}
