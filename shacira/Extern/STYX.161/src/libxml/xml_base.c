/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [xml_base.c]             XML Base Library                                 */
/*                  - parsing, interpretation and transformation -           */
/*                                                                           */
/* Copyright (c) 2003 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "hset.h"
#include "ptm.h"
#include "xml_dfn.h"

#include "ptm_gen.h"
#include "scn_base.h"
#include "scn_pre.h"
#include "gls.h"
#include "gstream.h"
#include "charlib.h"
#include "literal.h"
#include "pathes.h"
#include "sink.h"
#include "line_scn.h"

#include "xml_int.h"
#include "xml_lim.h"
#include "xml_pim.h"
#include "xmllit_lim.h"
#include "dtd_int.h"
#include "dtd_lim.h"
#include "dtd_pim.h"


/*!!
   The module [xml_base] provides an reentrant interface for the parsing, 
   interpretation and transformation of XML documents. 
*/

/*TODO: character set recognition
  - gstream.c:  add update_cset function
  - xml_base.c: add functions void XML_update_string/file_cset
                and calls in XML_load_extfile/url
*/


/*I-------------------------- Types and macros ------------------------------ */


ExternalType( XmlApp_T ) /* Abstract XML application type */
{
  PLR_Tab                  xmlptab;        /* XML Parse table            */
  PLR_Tab                  dtdptab;        /* DTD Parse table            */
  Scn_T                    xmlscn;         /* XML Scan table             */
  Scn_T                    dtdscn;         /* DTD Scan table             */
  Scn_T                    litscn;         /* XML literal Scan table     */
  XMLHDL_io_init           io_init;        /* XML I/O init function      */ 
  XMLHDL_io_cleanup        io_quit;        /* XML I/O quit function      */
  XMLHDL_io_create_handle  io_create;      /* XML I/O create function    */
  XMLHDL_io_drop_handle    io_drop;        /* XML I/O drop function      */
  XMLHDL_io_download       io_download;    /* XML I/O download function  */
};


ExternalType( XmlCtx_T ) /* Abstract XML parser type */
{
  XmlApp_T                xmlapp;    /* XML application configuration  */
  /* XML compilation configuration                                     */
  c_bool                  verbose;   /* print progress information     */
  c_bool                  diagnose;  /* print diagnose information     */
  Any_T                   extctx;    /* external context               */
  /* Parsing & semantic check of XML definition                        */
  symbol                  cset;      /* XML character set              */
  symbol                  auth;      /* user authentification          */
  symbol                  rootfile;  /* XML root document              */
  c_bool                  resolv;    /* load external entities         */
  MAP(symbol,symbol)      documents; /* document |--> character set    */
  MAP(symbol,PT_Term)     trees;     /* Source derivation trees        */
  MAP(symbol,symbol)      macros;    /* macro |--> replacement         */
  MAP(symbol,PT_Term)     entities;  /* macro |--> entity definition   */
  PT_Diag                 diag;      /* Diagnose context               */
  int                     errorCnt;  /* number of errors               */
  Scn_Stream              stream;    /* current XML stream             */
  Scn_Stream              litstream; /* XML literal stream             */
  UrlHdl_T                io_hdl;    /* XML I/O handle                 */
  c_bool                  dtdblock;  /* DTD parser activated ?         */
  c_bool                  extid;     /* first ExternalID ?             */
};


/* Token IDs */
typedef enum _XmlTokID
{
  XML_TOK_ENTITY  = 1,
  XML_TOK_PENTITY = 2,
  XML_TOK_HEXCHAR = 3,
  XML_TOK_DECCHAR = 4
} XmlTokID;

/* Macro Type */
typedef enum _XmlMacTyp
{
  XML_MAC_NONE = 0,
  XML_MAC_CHAR = 1,
  XML_MAC_PMAC = 2,
  XML_MAC_IMAC = 3,
  XML_MAC_EMAC = 4
} XmlMacTyp;

/* Literal/Token Context */
typedef enum _XmlLitCtx
{
  XML_LITCTX_ENTITY    = 0,
  XML_LITCTX_ATTRIBUTE = 1
} XmlLitCtx;


/* ----------------------------- Auxiliary functions ------------------------ */


static Scn_Stream XML_create_stream
                  (
                    c_string file, GStream_T gstream, Scn_T scn
                  )
{ Scn_Stream_Itr itr = Stream_Itr_new
                       (
                         GS_stream_get_wcrc, GS_fun_destruct(gstream), 
                         GS_ucs4_to_utf8, GS_fun_seek(gstream), 
                         gstream, file
                       );
  Scn_Stream res = Stream_bgn(scn,itr);
  Stream_Itr_free(itr);
  return res;
}

static void XML_create_litstream(XmlCtx_T xmlctx)
{ GStream_T gstream = GS_stream_string_new("",1,CS_ID_MBYTE);
  xmlctx->litstream = 
    XML_create_stream("<literal>",gstream,xmlctx->xmlapp->litscn);
  Stream_defEofId(xmlctx->litstream,-1);
  Stream_defErrId(xmlctx->litstream, 0);
  Stream_defTokId(xmlctx->litstream, "ERef",     XML_TOK_ENTITY);
  Stream_defTokId(xmlctx->litstream, "PERef",    XML_TOK_PENTITY);
  Stream_defTokId(xmlctx->litstream, "HCharRef", XML_TOK_HEXCHAR);
  Stream_defTokId(xmlctx->litstream, "DCharRef", XML_TOK_DECCHAR);
}

static void XML_drop_litstream(XmlCtx_T xmlctx)
{
  Stream_close(xmlctx->litstream);
  Stream_free(xmlctx->litstream);
  xmlctx->litstream = (Scn_Stream)NULL;
}

static c_bool XML_reset_litstream(XmlCtx_T xmlctx, c_string s, unsigned int len)
{ GStream_T gstream = (GStream_T)Stream_cstream(xmlctx->litstream);
  c_bool  res       = GS_stream_string_set(gstream,s,len+1);
  Stream_reset(xmlctx->litstream);
  return res;
}

static int XML_insert_litstream(XmlCtx_T xmlctx, c_string s, unsigned int len)
{ GStream_T gstream = (GStream_T)Stream_cstream(xmlctx->litstream);
  return GS_stream_string_set(gstream,s,len+1);
}


/*I----------------------------- Init & Quit -------------------------------- */


static void XML_init_macros(XmlCtx_T xmlctx)
/* set default macros */
{ symbol pLtKey   = stringToSymbol("&lt;"),
         pGtKey   = stringToSymbol("&gt;"),
         pAmpKey  = stringToSymbol("&amp;"),
         pAposKey = stringToSymbol("&apos;"),
         pQuotKey = stringToSymbol("&quot;");
  MAP_dfndom(xmlctx->entities,pLtKey,(dtdEntity)NULL);
  MAP_dfndom(xmlctx->macros,pLtKey,stringToSymbol("<"));
  MAP_dfndom(xmlctx->entities,pGtKey,(dtdEntity)NULL);
  MAP_dfndom(xmlctx->macros,pGtKey,stringToSymbol(">"));
  MAP_dfndom(xmlctx->entities,pAmpKey,(dtdEntity)NULL);
  MAP_dfndom(xmlctx->macros,pAmpKey,stringToSymbol("&"));
  MAP_dfndom(xmlctx->entities,pAposKey,(dtdEntity)NULL);
  MAP_dfndom(xmlctx->macros,pAposKey,stringToSymbol("'"));
  MAP_dfndom(xmlctx->entities,pQuotKey,(dtdEntity)NULL);
  MAP_dfndom(xmlctx->macros,pQuotKey,stringToSymbol("\""));
}


XmlApp_T XML_app_init
         (
           XMLHDL_io_init           io_init, 
           XMLHDL_io_cleanup        io_quit, 
           XMLHDL_io_create_handle  io_create, 
           XMLHDL_io_drop_handle    io_drop,
           XMLHDL_io_download       io_download
         )
/* init XML application;
   optional I/O handler:
   'io_init'     = init download module 
   'io_quit'     = cleanup download module 
   'io_create'   = create download handle 
   'io_drop'     = drop download handle 
   'io_download' = download URL to (string) stream 
*/
{ XmlApp_T xmlapp;
  initSymbols();
  MAP_init();
  xml_initSymbols();
  dtd_initSymbols();
  xmlapp = New(XmlApp_T);
  Scn_get_xml(&xmlapp->xmlscn);
  Scn_get_dtd(&xmlapp->dtdscn);
  Scn_get_xmllit(&xmlapp->litscn);
  xmlapp->xmlptab     = PLR_get_xml();
  xmlapp->dtdptab     = PLR_get_dtd();
  xmlapp->io_init     = io_init;
  xmlapp->io_quit     = io_quit;
  xmlapp->io_create   = io_create;
  xmlapp->io_drop     = io_drop;
  xmlapp->io_download = io_download;
  if( io_init != NULL ) 
  {
    (*io_init)();
  }
  return xmlapp;
}

void XML_app_quit(XmlApp_T xmlapp)
/* quit XML application; release resources */
{
  if( xmlapp != (XmlApp_T)NULL )
  {
    if( xmlapp->io_quit != NULL )
    {
      (*xmlapp->io_quit)();
    }
    if( xmlapp->xmlptab != (PLR_Tab)NULL ) 
    {
      PLR_delTab(xmlapp->xmlptab); 
      xmlapp->xmlptab = (PLR_Tab)NULL;
    }
    if( xmlapp->dtdptab != (PLR_Tab)NULL ) 
    {
      PLR_delTab(xmlapp->dtdptab); 
      xmlapp->dtdptab = (PLR_Tab)NULL;
    }
    if( xmlapp->litscn != (Scn_T)NULL ) 
    {
      Scn_free(xmlapp->litscn); 
      xmlapp->litscn = (Scn_T)NULL;
    }
    if( xmlapp->xmlscn != (Scn_T)NULL ) 
    {
      Scn_free(xmlapp->xmlscn); 
      xmlapp->xmlscn = (Scn_T)NULL;
    }
    if( xmlapp->dtdscn != (Scn_T)NULL ) 
    {
      Scn_free(xmlapp->dtdscn); 
      xmlapp->dtdscn = (Scn_T)NULL;
    }
    FreeMem(xmlapp);
  }
  xml_quitSymbols();
  dtd_quitSymbols();
  MAP_quit();
  freeSymbols();
}

static void XML_reset(XmlCtx_T xmlctx)
{ MAPIT itr; symbol dom; PT_Term rng;
  xmlctx->rootfile = (symbol)NULL;
  xmlctx->cset     = (symbol)NULL;
  xmlctx->auth     = (symbol)NULL;
  xmlctx->resolv   = C_False;
  xmlctx->errorCnt = 0;
  xmlctx->dtdblock = C_False;
  xmlctx->extid    = C_True;
  MAP_forItrAsg(dom,rng,itr,xmlctx->trees)
  {
    PT_delT(rng);
  }
  MAP_rmvall(xmlctx->trees);
  MAP_rmvall(xmlctx->documents);
  MAP_rmvall(xmlctx->entities);
  MAP_rmvall(xmlctx->macros);
  XML_init_macros(xmlctx);
}

XmlCtx_T XML_init
      (
        XmlApp_T xmlapp, 
        void (*prMsg)(c_string msg), c_bool verbose, c_bool diagnose
      )
/* init XML parsing;
   'prMsg'    --> print function or NULL
   'verbose'  --> (de)activate progress information
   'diagnose' --> (de)activate diagnose information 
*/
{ XmlCtx_T xmlctx;
  BUG_NULL(xmlapp);
  xmlctx              = New(XmlCtx_T);
  xmlctx->xmlapp      = xmlapp;
  xmlctx->verbose     = verbose;
  xmlctx->diagnose    = diagnose;
  xmlctx->rootfile    = (symbol)NULL;
  xmlctx->cset        = (symbol)NULL;
  xmlctx->auth        = (symbol)NULL;
  xmlctx->resolv      = C_False;
  xmlctx->diag        = PT_diag_init(prMsg!=NULL?prMsg:prMsg_stderr);
  xmlctx->trees       = MAP_newPrimMap();
  xmlctx->documents   = MAP_newPrimMap();
  xmlctx->macros      = MAP_newPrimMap();
  xmlctx->entities    = MAP_newPrimMap();
  xmlctx->errorCnt    = 0;
  xmlctx->stream      = (Scn_Stream)NULL;
  xmlctx->io_hdl      = (UrlHdl_T)NULL;
  xmlctx->dtdblock    = C_False;
  xmlctx->extid       = C_True;
  if( xmlapp->io_create != NULL )
  {
    xmlctx->io_hdl = (*xmlapp->io_create)();
  }
  XML_create_litstream(xmlctx);
  return xmlctx;
}

void XML_quit(XmlCtx_T xmlctx)
/* quit XML compilation; release resources */
{
  if(xmlctx != (XmlCtx_T)NULL )
  {
    XML_reset(xmlctx);
    MAP_freeMap(xmlctx->macros);
    MAP_freeMap(xmlctx->entities);
    MAP_freeMap(xmlctx->documents);
    MAP_freeMap(xmlctx->trees);
    xmlctx->trees = (PT_Term)NULL;
    if( xmlctx->diag != (PT_Diag)NULL ) 
    {
      PT_diag_quit(xmlctx->diag);
      xmlctx->diag = (PT_Diag)NULL;
    }
    if( xmlctx->xmlapp->io_drop != NULL && 
        xmlctx->io_hdl != (UrlHdl_T)NULL )
    {
      (*xmlctx->xmlapp->io_drop)(xmlctx->io_hdl);
      xmlctx->io_hdl = (UrlHdl_T)NULL;
    }
    XML_drop_litstream(xmlctx);
    FreeMem(xmlctx);
  }
}


/*I---------------------------- Set & Get ----------------------------------- */


void XML_set_verbose(XmlCtx_T xmlctx, c_bool verbose)
/* (de)activate progress information */
{
  BUG_NULL(xmlctx);
  xmlctx->verbose = verbose;
}

void XML_set_diagnose(XmlCtx_T xmlctx, c_bool diagnose)
/* (de)activate diagnose information */
{
  BUG_NULL(xmlctx);
  xmlctx->diagnose = diagnose;
}

void XML_set_context(XmlCtx_T xmlctx, Any_T extctx)
/* set external context information */
{
  BUG_NULL(xmlctx);
  xmlctx->extctx = extctx;
}

Any_T XML_get_context(XmlCtx_T xmlctx)
/* get external context information */
{
  BUG_NULL(xmlctx);
  return xmlctx->extctx;
}

void XML_get_trees(XmlCtx_T xmlctx, symbol* root, MAP(symbol,PT_Term)* trees)
/* get document trees */
{
  BUG_NULL(xmlctx);
  if( root != (symbol*)NULL ) 
    *root  = xmlctx->rootfile;
  if( trees != (MAP(symbol,PT_Term)*)NULL ) 
    *trees = xmlctx->trees;
}


/*I---------------------------- Parsing & Tree construction ----------------- */


static XmlMacTyp XML_replace_macro
                 (
                   XmlCtx_T xmlctx, string macro, symbol* value
                 )
/* replace reference macro with its value */
/* RC = macro type                        */
{ 
  if( macro[1] == '#' ) /* Character Reference */
  { int c; char cref[2]; 
    if( isdigit(macro[2]) ) /* decimal value */
    {
      c = atoi(&macro[2]);
    }
    else /* hex value */
    {
      macro[1] = '0';
      sscanf(&macro[1],"%x",&c);
      macro[1] = '#';
    }
    sprintf(cref,"%c",(char)c);
    *value = stringToSymbol(cref);
    return XML_MAC_CHAR;
  }
  else /* (P)Entity Reference or no Macro */
  { symbol macsym = stringToSymbol(macro);
    if( MAP_defined(xmlctx->macros,macsym) )
    { dtdEntity entity;
      entity = MAP_apply(dtdEntity,xmlctx->entities,macsym);
      *value = MAP_apply(symbol,xmlctx->macros,macsym);
      if( entity == (dtdEntity)NULL )
        return XML_MAC_CHAR;
      else
      { dtdEntityVal entityval;
        if( dtdEntity_pent(entity,_,&entityval) ||
            dtdEntity_gent(entity,_,&entityval)  )
        {
          if( dtdEntityVal_ient(entityval,_) )
            return macro[0]=='&'?XML_MAC_IMAC:XML_MAC_PMAC;
          else return XML_MAC_EMAC;
        }
        else C_BUG;
      }
    }
  }
  return XML_MAC_NONE; /* no Macro */
}

static int XML_premac
           (
             Scn_Stream stream, string cTokNam, string cTokVal, symbol* cMacVal
           )
/* pre-process token */
{ XmlCtx_T xmlctx = (XmlCtx_T)Stream_get_ctxval(stream,stream);
  if( ( cTokVal[0] == '%' && xmlctx->dtdblock ) || cTokVal[0] == '&' ) 
  { 
    if( cTokVal[strlen(cTokVal)-1] == ';' )
    { XmlMacTyp mactyp = XML_replace_macro(xmlctx, cTokVal, cMacVal);
      switch( mactyp )
      { 
        case XML_MAC_CHAR:
        case XML_MAC_EMAC:
          return SCN_FLG_RescanNone;
        case XML_MAC_IMAC:
        case XML_MAC_PMAC:
          return SCN_FLG_RescanString;
        case XML_MAC_NONE:
          break;
      }
    }
  }
  if( !strcmp(cTokNam,"DTDStart") )
    xmlctx->dtdblock = C_True;
  *cMacVal = stringToSymbol(cTokVal);
  return SCN_FLG_RescanNone;
}

static void XML_parse_lit
            (
              XmlCtx_T xmlctx, GLS_Tok littok, c_string lit, 
              XmlLitCtx litctx, Sink snk
            )
/* parse XML Literal */
{ 
  bug0
  (
    XML_reset_litstream(xmlctx,lit,strlen(lit)),
    "memory allocation failed"
  );
  for( Stream_next(xmlctx->litstream); 
       Stream_ctid(xmlctx->litstream) >= 0; Stream_next(xmlctx->litstream) )
  { symbol cursym = Stream_csym(xmlctx->litstream), 
           newsym = (symbol)NULL;
    switch( Stream_ctid(xmlctx->litstream) )
    { XmlMacTyp mactyp;
      case XML_TOK_HEXCHAR:
      case XML_TOK_DECCHAR:
        mactyp = XML_replace_macro(xmlctx,symbolToString(cursym),&newsym);
        break;
      case XML_TOK_PENTITY:
        if( xmlctx->dtdblock )
        {
          mactyp = XML_replace_macro(xmlctx,symbolToString(cursym),&newsym);
          if( mactyp == XML_MAC_PMAC )
          { unsigned int len = strlen(symbolToString(newsym));
            bug0
            (
              XML_insert_litstream(xmlctx,symbolToString(newsym),len) >= len,
              "memory allocation failed"
            );
            newsym = (symbol)NULL;
          }
        }
        break;
      case XML_TOK_ENTITY:
        if( litctx == XML_LITCTX_ATTRIBUTE )
        {
          mactyp = XML_replace_macro(xmlctx,symbolToString(cursym),&newsym);
          if( mactyp == XML_MAC_IMAC )
          { unsigned int len = strlen(symbolToString(newsym));
            bug0
            (
              XML_insert_litstream(xmlctx,symbolToString(newsym),len) >= len,
              "memory allocation failed"
            );
            newsym = (symbol)NULL;
          }
          else
          if( mactyp == XML_MAC_EMAC )
          { 
            PT_diag_err
            (
              littok, xmlctx->diag, 
              "illegal reference '%s'", symbolToString(cursym)
            ); 
            newsym = cursym;
          }
        }
        break;
      default:
        newsym = cursym;
        break;
    }
    if( newsym != (symbol)NULL )
      Sink_printf(snk,"%s",symbolToString(newsym));
  }
}

static symbol XML_getEntityName(XmlCtx_T xmlctx, dtdXName xname)
{ PT_Itr itr; symbol res = (symbol)NULL;
  PT_FORALL(itr,xname)
  { PT_Term t = PT_termIT(itr);
    if( PT_stateIT(itr) == PT_PRAE && (PT_isKey(t) || PT_isToken(t)) )
    {
      res = PT_value(t);
      PT_BREAK(itr);
    }
  }
  return res;
}

static symbol XML_saveEntityTerm
              (
                XmlCtx_T xmlctx, dtdEntity entity, dtdEntityVal* entityval
              )
{ dtdXName xname; symbol name;
  string   keystr = (string)NULL; 
  symbol   keysym = (symbol)NULL;
  if( dtdEntity_gent(entity,&xname,entityval) )
  {
    assert0((name = XML_getEntityName(xmlctx,xname)),"");
    keystr = Str_printf("&%s;",symbolToString(name));
  }
  else
  if( dtdEntity_pent(entity,&xname,entityval) )
  {
    assert0((name = XML_getEntityName(xmlctx,xname)),"");
    keystr = Str_printf("%c%s;",'%',symbolToString(name));
  }
  else C_BUG;
  if( keystr != (string)NULL )
  {
    keysym  = stringToSymbol(keystr);
    if( ! MAP_defined(xmlctx->entities,keysym) )
      MAP_dfndom(xmlctx->entities,keysym,entity);
    FreeMem(keystr);
  }
  return keysym;
}

static void XML_saveEntityValue
            (
              XmlCtx_T xmlctx, symbol key, dtdXLiteral xlit, XmlLitCtx litctx
            )
{ Sink snk; GLS_Tok scntok;
  string newtok, curtok = (string)NULL;
  if( dtdXLiteral_lit(xlit,&scntok) )
  { symbol scnval = GLS_Tok_symbol(scntok);
    curtok = StrCopy(symbolToString(scnval)+1);
    curtok[strlen(curtok)-1] = '\0';
  }
  else
  if( dtdXLiteral_pref(xlit,&scntok) )
  {
    curtok = StrCopy(GLS_Tok_string(scntok));
  }
  else C_BUG;
  snk = Sink_open();
  XML_parse_lit(xmlctx,scntok,curtok,XML_LITCTX_ENTITY,snk);
  newtok = Sink_close(snk);
  MAP_dfndom(xmlctx->macros,key,stringToSymbol(newtok));
  FreeMem(newtok);
  FreeMem(curtok);
}

static void XML_saveAttrValue
            (
              XmlCtx_T xmlctx, GLS_Tok scntok, XmlLitCtx litctx
            )
{ Sink   snk;
  symbol scnval = GLS_Tok_symbol(scntok);
  string newtok, curtok;
  curtok = StrCopy(symbolToString(scnval));
  snk = Sink_open();
  XML_parse_lit(xmlctx,scntok,curtok,XML_LITCTX_ATTRIBUTE,snk);
  newtok = Sink_close(snk);
  PT_updVal(scntok,stringToSymbol(newtok));
  FreeMem(newtok);
  FreeMem(curtok);
}

/*forwards*/
static int XML_load_extfile
           (
             XmlCtx_T xmlctx, c_string xmldoc, c_string cset, c_bool dtd
           );
static int XML_load_exturl
           (
             XmlCtx_T xmlctx, c_string xmldoc, 
             c_string cset, c_string auth, c_bool dtd
           );

static int XML_load_reference(XmlCtx_T xmlctx, dtdExtID extid)
{ dtdXLiteral xlit; GLS_Tok lit;
  if( ( dtdExtID_sys(extid,&xlit) || dtdExtID_pub(extid,_,&xlit) ) &&
      dtdXLiteral_lit(xlit,&lit) )
  { 
    string url  = StrCopy(GLS_Tok_string(lit)+1),
           base = FilePrefix(symbolToString(PT_file(extid)));
    int    len  = strlen(url), i;
    url[len-1]  = '\0';
    if( xmlctx->xmlapp->io_download == NULL )
    {
      if( !AbsolutPath(url) && *base != '<' )
      { Sink snk = Sink_open();
        Sink_printf(snk,"%s/%s",base,url);
        FreeMem(url);
        url = Sink_close(snk);
      }
      XML_load_extfile(xmlctx,url,symbolToString(xmlctx->cset),C_True);
    }
    else
    { MAP(long,symbol) urlparts = MAP_newPrimMap();
      Sink snk = Sink_open();
      for( i=0; i < len; ++i )
      {
        if( isspace(url[i]) )
        {
          if( i < len - 1 && !isspace(url[i+1]) )
          {
            Sink_printf(snk,"%20");
          }
        }
        else
        {
          if( isascii(url[i]) )
            Sink_printf(snk,"%c",url[i]);
          else
            Sink_printf(snk,"%c%02x",'%',(int)url[i]);
        }
      }
      FreeMem(url);
      url = Sink_close(snk);
      URI_RelToAbs(url,base,"",urlparts);
      FreeMem(url);
      url = URI_consParts(urlparts,C_False);
      MAP_freeMap(urlparts);
      XML_load_exturl
      (
        xmlctx,url,symbolToString(xmlctx->cset),
        symbolToString(xmlctx->auth),C_True
      );
    }
    FreeMem(url); FreeMem(base);
  }
  return xmlctx->errorCnt;
}

static PT_Term XML_convNtm(PT_Term tree, Any_T ctx)
{ XmlCtx_T     xmlctx = (XmlCtx_T)ctx;
  dtdEntity    entity;
  dtdEntityVal entityval;
  dtdExtID     extid;
  dtdNData     ndata;
  xmlAttr      attribute;
  GLS_Tok      lit;
  symbol       key;
  if( dtd_Embed(tree,_) ) xmlctx->dtdblock = C_False;
  else
  if( dtd_Entity(tree,&entity) &&
      (key = XML_saveEntityTerm(xmlctx,entity,&entityval)) != (symbol)NULL )
  { 
    if( ! MAP_defined(xmlctx->macros,key) )
    { dtdXLiteral xlit;
      if( dtdEntityVal_ient(entityval,&xlit) )
      {
        XML_saveEntityValue(xmlctx,key,xlit,XML_LITCTX_ENTITY);
      }
      else 
      if( dtdEntityVal_eent(entityval,&extid,&ndata) )
      {
        if( xmlctx->resolv && dtdNData_nul(ndata) )
          XML_load_reference(xmlctx,extid);
        if( !MAP_defined(xmlctx->macros,key) )
          MAP_dfndom(xmlctx->macros,key,key); 
        xmlctx->dtdblock = C_True;
      }
    }
  }
  else
  if( xml_Attr(tree,&attribute) && xmlAttr_dfn(attribute,_,_,_,_,&lit) )
  {
    XML_saveAttrValue(xmlctx,lit,XML_LITCTX_ATTRIBUTE);
  }
  else
  if( xmlctx->extid && dtd_ExtID(tree,&extid) )
  {
    if( xmlctx->resolv ) 
      XML_load_reference(xmlctx,extid);
    xmlctx->extid    = C_False;
    xmlctx->dtdblock = C_True;
  }
  return tree;
}


static int XML_load_document
           (
             XmlCtx_T xmlctx, GStream_T gstream, symbol file, c_bool dtd
           )
{ void (*prMsg)(c_string msg) = PT_diag_msgFun(xmlctx->diag);
  if (xmlctx->verbose) 
  {
    (*prMsg)("parsing document '");
    (*prMsg)(symbolToString(file));
    (*prMsg)("' ...\n");
  }
  if( !MAP_defined(xmlctx->documents,file) )
  { Scn_Stream_Itr itr = Stream_Itr_new
                         (
                           GS_stream_get_wcrc, GS_fun_destruct(gstream), 
                           GS_ucs4_to_utf8, GS_fun_seek(gstream), 
                           gstream, symbolToString(file)
                         );
    PT_Cfg pcfg; PT_Term tree;
    c_bool extid = xmlctx->extid;
    xmlctx->extid = C_True;
    MAP_dfndom(xmlctx->documents,file,xmlctx->cset);
    if( !dtd )
      xmlctx->stream = Stream_bgn(xmlctx->xmlapp->xmlscn,itr);
    else
      xmlctx->stream = Stream_bgn(xmlctx->xmlapp->dtdscn,itr);
    Stream_Itr_free(itr);
    Stream_premac_set(xmlctx->stream, XML_premac);
    Stream_add_ctxval(xmlctx->stream, xmlctx->stream, xmlctx);
    if( !dtd )
    {
      pcfg = PT_init(xmlctx->xmlapp->xmlptab,xmlctx->stream);
      PT_setEParser(pcfg,PLR_getETab,PLR_delTab,NULL);
    }
    else
    {
      pcfg = PT_init(xmlctx->xmlapp->dtdptab,xmlctx->stream);
    }
    PT_setNtmConvFunEx(pcfg,XML_convNtm, xmlctx);
    tree = PT_PARSE(pcfg,"");
    MAP_dfndom(xmlctx->trees,file,tree);
    PT_diag_setErrorCnt
    (
      xmlctx->diag,PT_diag_errorCnt(xmlctx->diag)+PT_synErrorCnt(pcfg)
    );
    xmlctx->errorCnt += PT_diag_errorCnt(xmlctx->diag);
    PT_quit(pcfg);
    Stream_close(xmlctx->stream);
    Stream_free(xmlctx->stream);
    xmlctx->stream = (Scn_Stream)NULL;
    xmlctx->extid = extid;
  }
  else
  {
    (*GS_fun_destruct(gstream))(gstream);
  }
  if (xmlctx->diagnose || xmlctx->verbose) 
  { c_string msg = Str_printf("Totally %d errors.\n",xmlctx->errorCnt);
    (*prMsg)(msg);
    FreeMem(msg);
  }
  return xmlctx->errorCnt;
}

static int XML_load_extfile
           (
             XmlCtx_T xmlctx, c_string xmldoc, c_string cset, c_bool dtd
           )
{ 
  xmlctx->cset = stringToSymbol(STR_EMPTY(cset)?CS_ID_MBYTE:cset);
  if( STR_EMPTY(xmldoc) || IsPath(xmldoc) )
  { FILE* fp = STR_EMPTY(xmldoc) ? stdin : TryOpnFile(xmldoc,"rb");
    if( fp != (FILE*)NULL )
    { GStream_T gstream = GS_stream_file_new(fp,cset,!STR_EMPTY(xmldoc));
      if( gstream != (GStream_T)NULL )
      {
        return XML_load_document
               (
                 xmlctx,gstream,
                 stringToSymbol(STR_EMPTY(xmldoc)?"<stdin>":xmldoc),dtd
               );
      }
      else 
      {
        fclose(fp);
        PT_diag_err((PT_Term)NULL,xmlctx->diag,"Stream creation failed"); 
      }
    }
    else
    { 
      PT_diag_err
      (
        (PT_Term)NULL,xmlctx->diag,"Document %s couldn't be opened",xmldoc
      ); 
    }
  }
  else
  { 
    PT_diag_err
    (
      (PT_Term)NULL,xmlctx->diag,"Document %s not found",xmldoc
    ); 
  }
  return xmlctx->errorCnt += PT_diag_errorCnt(xmlctx->diag);
}

static int XML_load_exturl
           (
             XmlCtx_T xmlctx, c_string xmldoc, 
             c_string cset, c_string auth, c_bool dtd
           )
{ 
  xmlctx->cset = stringToSymbol(STR_EMPTY(cset)?CS_ID_MBYTE:cset);
  xmlctx->auth = stringToSymbol(STR_EMPTY(auth)?"":auth);
  if( xmlctx->xmlapp->io_download == NULL )
  {
    PT_diag_err((PT_Term)NULL,xmlctx->diag,"missing download handler"); 
  }
  else
  { GStream_T gstream = GS_stream_string_new("",1,cset);
    if( gstream != (GStream_T)NULL )
    {
      if( (*xmlctx->xmlapp->io_download)
          (xmlctx->io_hdl,xmldoc,auth,gstream,PT_diag_msgFun(xmlctx->diag)) )
      {
        return XML_load_document(xmlctx,gstream,stringToSymbol(xmldoc),dtd);
      }
      else
      {
        PT_diag_err((PT_Term)NULL,xmlctx->diag,"download failed"); 
        (*GS_fun_destruct(gstream))(gstream);
      }
    }
    else 
    {
      PT_diag_err((PT_Term)NULL,xmlctx->diag,"Stream creation failed"); 
    }
  }
  return xmlctx->errorCnt += PT_diag_errorCnt(xmlctx->diag);
}


/* ---------------------------- Interface functions ------------------------- */


int XML_load_file
    (
      XmlCtx_T xmlctx, c_string xmldoc, c_string cset, c_bool dtd, c_bool all
    )
/* parses XML/DTD definition in file 'xmldoc' and
   constructs the corresponding tree;
   'cset' = character set name ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   'dtd'  = True --> 'xmldoc' contains DTD definitions
   'all'  = True --> loads all referenced documents
   RC >  0: number of (syntax and semantic) errors
   RC = -1: tree construction failed
   RC =  0: successful load
*/
{ 
  BUG_NULL(xmlctx); BUG_NULL(xmldoc);
  XML_reset(xmlctx);
  xmlctx->rootfile = stringToSymbol(xmldoc);
  xmlctx->resolv   = all;
  return XML_load_extfile(xmlctx,xmldoc,cset,dtd);
}

int XML_load_string
    (
      XmlCtx_T xmlctx, c_string xmldoc, unsigned int len, 
      c_string cset, c_bool dtd, c_bool all
    )
/* parses XML definition in string 'xmldoc' and
   constructs the corresponding tree;
   'len'  = string size in bytes, inclusive terminating bytes
   'cset' = character set name ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   'dtd'  = True --> 'xmldoc' contains DTD definitions
   'all'  = True --> loads all referenced documents
   RC >  0: number of syntax and semantic errors
   RC = -1: tree construction failed
   RC =  0: successful load
*/
{ GStream_T gstream;
  BUG_NULL(xmlctx); BUG_NULL(xmldoc);
  XML_reset(xmlctx);
  xmlctx->rootfile = stringToSymbol("<rootstring>");
  xmlctx->cset     = stringToSymbol(STR_EMPTY(cset)?CS_ID_MBYTE:cset);
  xmlctx->resolv   = all;
  gstream          = GS_stream_string_new(xmldoc,len,cset);
  if( gstream != (GStream_T)NULL )
  {
    return XML_load_document(xmlctx,gstream,xmlctx->rootfile,dtd);
  }
  else 
  {
    PT_diag_err((PT_Term)NULL,xmlctx->diag,"Stream creation failed"); 
  }
  return xmlctx->errorCnt = PT_diag_errorCnt(xmlctx->diag);
}

int XML_load_url
    (
      XmlCtx_T xmlctx, c_string xmldoc, 
      c_string cset, c_string auth, c_bool dtd, c_bool all
    )
/* parses XML definition identified by URL 'xmldoc' and
   constructs the corresponding tree;
   'cset' = character set name ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   'auth' = optional user authentification ( format: user:passwd )
   'dtd'  = True --> 'xmldoc' contains DTD definitions
   'all'  = True --> loads all referenced documents
   RC >  0: number of syntax and semantic errors
   RC = -1: tree construction failed
   RC =  0: successful load
   assertion: valid I/O handler
*/
{ 
  BUG_NULL(xmlctx); BUG_NULL(xmldoc);
  XML_reset(xmlctx);
  xmlctx->rootfile = stringToSymbol(xmldoc);
  xmlctx->resolv   = all;
  return XML_load_exturl(xmlctx,xmldoc,cset,xmlctx->auth,dtd);
}

