/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [xml_test.c]                 XML Parser Test                             */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "pathes.h"
#include "sink.h"
#include "hmap.h"
#include "ptm.h"
#include "xml_base.h"
#include "xml_test_cim.h"


#define file CTX_EVAL(c_string,"file")
#define cset CTX_EVAL(c_string,"cset")
#define all  CTX_EVAL(c_bool,"all")  
#define dtd  CTX_EVAL(c_bool,"dtd")  


int main(int argc, string argv[])
{ XmlApp_T xmlapp; XmlCtx_T xmlctx; 
  MAP(symbol,PT_Term) trees; 
  MAPIT itr; PT_Term rng; symbol dom;
  int errcnt = -1;
  CTX_init_xml_test(argc,argv);
  assert0
  (
    xmlapp = XML_app_init(NULL,NULL,NULL,NULL,NULL),
    "creation of application context failed"
  );
  assert0
  (
    xmlctx = XML_init(xmlapp,NULL,C_True,C_True),
    "creation of parsing context failed"
  );
  errcnt = XML_load_file(xmlctx,file,cset,dtd,all);
  XML_get_trees(xmlctx,_,&trees);
HERE;
  MAP_forItrAsg(dom,rng,itr,trees)
  {
    printf("\nParsing results for '%s':\n",symbolToString(dom));
    PT_print_rawutf8(rng);
  }
  XML_quit(xmlctx);
  XML_app_quit(xmlapp);
  CTX_quit();
  BUG_CORE;
  return 0;
}

