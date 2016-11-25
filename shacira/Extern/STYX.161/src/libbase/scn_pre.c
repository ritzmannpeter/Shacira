/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_pre.c]           STYX-konform preprocessing                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/* export prefix "SPP_" */

#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "scn_base.h"

#include "otab.h"
#include "pathes.h"
#include "sink.h"
#include "gstream.h"

/*!
  <p>The STYX system comes up with a macro preprocessing facility - 
  <br>based on the following macro definition syntax and evaluation process 
  during the lexical analysis:
  <p><table cellspacing=10 noborder>
  <tr>
  <td><b>#include</b> Path</td>
  <td>supports modular grammar design
  <br>The macro will be replaced by the content of source file 'Path' and
      then rescanned.
  </td>
  </tr>
  <tr>
  <td><b>#macro</b> Name ( FormalParameter , ... ) = Text <b>#end</b></td>
  <td>supports text replacement
  <br>Parameter and replacement text are optional.
  <br>The macro will be collected by the preprocessing module and 
      skipped by the scanner.
  <br>A macro expression ( Name ActualParameter Delimiter ... ) will be 
      replaced by the previous definition and then rescanned.
  </td>
  </tr>
  <tr>
  <td>' Delimiter</td>
  <td>introduces another - the second - character as delimiter for the 
      actual macro parameter.
  <br>Spaces will be used as default delimiter. 
      To reactive the default behaviour specify ' -.
  <br>The scanner skips these token.
  </td>
  </tr>
  <tr>
  <td><b>#undefine</b> Name</td>
  <td>revokes a previous definition
  </td>
  </tr>
  <tr>
  <td><b>#if[n]def</b> Name IfPart <b>#else</b> ElsePart <b>#end</b></td>
  <td>supports conditional parsing
  <br>Dependant on the existence of macro 'Name' the scanner skips the
      'ElsePart' or 'IfPart'. 
  <br>Its possible to introduce environment variables as macros.
  </td>
  </tr>
  </table>
  <br>
  <p>You can use this preprocessing facility if your regular grammar defines
  the above kind of macros in the same way - 
  <br>apart from token names and keywords. 
  ( see below and <a href="styx_cfg.htm"><b>styx</b> reference</a> )
  <br>
  <p>Note: 
  <p>The reentrant version of the preprocessing module expects that the
     preprocessor ( constructed by the function 'SPP_init_reentrant' )
     will be added to the scan stream as value of the context variable 'SPP_premac'.
  <br>
*/

/*I-------------------- Types & Macros ------------------------------------ */


ExternalType( SPP_T )  /* Abstract preprocessing type */
{
  /* Preprocessing parameter */
  MAP(long,symbol) pCurPreParMap; 

  /* macro definition:
     macro name |--> { formal parameter name } macro text
  */ 
  MAP(symbol,ROW(symbol)) pMacDfnMap;

  /* evaluate the current token sequence as macro apply:
     ( actual parameter[], macro name )[]
  */
  ROW(_) pCurMacRow;

  /* macro condition:
     empty row --> scan all
     top = 1   --> scan til #else/#end
     top = 0   --> skip til #else/#end
     top = -1  --> skip all
  */
  ROW(long) pCondRow;

  /* current macro parameter separator */
  char szCurMacSep[3];

  /* current parameter */
  Sink pCurMacPar;
};


/*!
  <p><b>Identifier for the ( macro ) token names</b>
*/

/*DOC_INTERFACE*/
#define SPP_TOK_IDE         0 // Identifier
#define SPP_TOK_MACDFN      1 // Macro 
#define SPP_TOK_MACSEP      2 // Delimiter
#define SPP_TOK_MACINC      3 // Include
#define SPP_TOK_MACCOND     4 // Condition
#define SPP_TOK_MACDEL      5 // Undefine

/*!
  <p><b>Identifier for macro token keywords</b>
*/

/*DOC_INTERFACE*/
#define SPP_PAT_START       6  // #macro
#define SPP_PAT_END         7  // #end
#define SPP_PAT_IFDEF       8  // #ifdef
#define SPP_PAT_IFNDEF      9  // #ifndef
#define SPP_PAT_ELSE        10 // #else
#define SPP_PAT_INC         11 // #include
#define SPP_PAT_UNDEFINE    12 // #undefine
#define SPP_PAT_ENDIF       13 // #endif

/*!
  <p><b>Identifier for include path and character set</b>
*/

/*DOC_INTERFACE*/
#define SPP_INC_PATH        14
#define SPP_INC_CHARSET     15

#define SPP_COND_SCAN       1
#define SPP_COND_SKIP       0
#define SPP_COND_ERROR      -1

#define SPP_ISSPACE(c)      ( (c) == ' '  || (c) == '\t' || \
                              (c) == '\n' || (c) == '\r' )

#define SPP_PREPAR(pp,p) ( ( (pp)->pCurPreParMap == (MAP(_,_))NULL ||              \
                         ! MAP_defined(pp->pCurPreParMap,p) ) ? (szPreParIds[p])   \
                         : symbolToString(MAP_apply(symbol,(pp)->pCurPreParMap,p)) )


// Preprocessing Parameter
static c_string szPreParIds[] =
{
  "Ide",        // us-ascii or ignore case !!!
  "MacDfn",
  "MacSep",
  "MacInc",
  "MacCond",
  "MacDel",

  "#macro",
  "#end",
  "#ifdef",
  "#ifndef",
  "#else",
  "#include",
  "#undefine",
  "#endif",

  "PATH",
  ""
};

// static preprocessing context ( non-reentrant )
static SPP_T pCurPP = (SPP_T)NULL;

static c_string szINIT_ERROR = "preprocessing not initialized";


/*I-------------------- Macro Expansion ----------------------------------- */

static SPP_T SPP_init_aux(MAP(long,symbol) pPreParMap)
/* reentrant version of SPP_init */
{ MAPTY pMapTyp = MAP_newTyp
                  (
                    primCopy,primFree,primEqual,primHash,primCopy,OT_delT
                  );
  SPP_T pPP     = New(SPP_T);
  pPP->pMacDfnMap    = MAP_newMap(pMapTyp);
  pPP->pCondRow      = OT_CREATE_ADT(long);
  pPP->pCurMacPar    = Sink_open();  
  pPP->pCurMacRow    = (ROW(_))NULL;
  *pPP->szCurMacSep  = '\0';
  pPP->pCurPreParMap = pPreParMap;
  return pPP;
}

void SPP_init(MAP(long,symbol) pPreParMap)
/* initializes STYX-konform macro preprocessing 
   'pPreParMap': re-definitions for macro token names,
                 initial macro token keywords, 
                 include path and characterset
*/
{ 
  pCurPP = SPP_init_aux(pPreParMap);
}

SPP_T SPP_init_reentrant(MAP(long,symbol) pPreParMap)
/* reentrant version of SPP_init */
{ 
  return SPP_init_aux(pPreParMap);
}

void SPP_addCtxMacro(symbol pMacNam)
/* adds ( lower case symbol ) 'pMacNam' as pre-defined macro */
{ ROW(symbol) pMacDfn = OT_CREATE_ADT(symbol);
  assert0(pCurPP != (SPP_T)NULL, szINIT_ERROR);
  MAP_ovrdom(pCurPP->pMacDfnMap,pMacNam,pMacDfn);
  OT_PUSH(stringToSymbol(""),pMacDfn);
}

void SPP_addCtxMacro_reentrant(SPP_T pPP, symbol pMacNam)
/* reentrant version of SPP_addCtxMacro */
{ ROW(symbol) pMacDfn = OT_CREATE_ADT(symbol);
  assert0(pPP != (SPP_T)NULL, szINIT_ERROR);
  MAP_ovrdom(pPP->pMacDfnMap,pMacNam,pMacDfn);
  OT_PUSH(stringToSymbol(""),pMacDfn);
}

static void SPP_quit_aux(SPP_T pPP)
{ 
  assert0(pPP != (SPP_T)NULL, szINIT_ERROR);
  { MAPTY  pMapTyp = MAP_MapTyp(pPP->pMacDfnMap);
    string szTmp   = Sink_close(pPP->pCurMacPar);
    pPP->pCurMacPar = (Sink)NULL; FreeMem(szTmp);
    if( pPP->pCurMacRow != (ROW(_))NULL )
    { long lCnt = OT_CNT(pPP->pCurMacRow), lI;
      for( lI=0; lI < lCnt; lI += 2 )
        OT_DEL_T(OT_GET(ROW(symbol),pPP->pCurMacRow,lI));
      OT_DEL_T(pPP->pCurMacRow);  
      pPP->pCurMacRow = (ROW(symbol))NULL;
    }
    MAP_freeMap(pPP->pMacDfnMap); 
    pPP->pMacDfnMap = (MAP(symbol,symbol))NULL;
    OT_DEL_T(pPP->pCondRow);      
    pPP->pCondRow   = (ROW(long))NULL;
    MAP_freeTyp(pMapTyp);
    FreeMem(pPP);
  }
}

void SPP_quit(void)
/* terminates STYX-konform macro preprocessing */
{ 
  SPP_quit_aux(pCurPP); pCurPP = (SPP_T)NULL;
}

void SPP_quit_reentrant(SPP_T pPP)
/* reentrant version of SPP_quit */
{ 
  SPP_quit_aux(pPP);
}

static symbol SPP_getInclude(SPP_T pPP, string cTokVal)
/* extract include file */
{ string szS, szT, szDir, szPath;
  symbol pPath = (symbol)NULL;
  szS = cTokVal + strlen(SPP_PREPAR(pPP,SPP_PAT_INC));
  while( SPP_ISSPACE(*szS) ) szS++;
  szDir  = SPP_PREPAR(pPP,SPP_INC_PATH);
  szT    = GetEnvCtx(szDir);
  if( szT == NULL )
  { PIT pItr = PIT_make(szDir); 
    while( ( szT = PIT_read(pItr) ) != NULL )
    {
      szPath = MkPath(szT,szS,"",'d');
      pPath = stringToSymbol(szPath);
      FreeMem(szPath);
      if( IsPath(symbolToString(pPath)) ) break;
    }
    PIT_drop(pItr);
  }
  else
  {
    szPath = MkPath(szDir,szS,"",'p');
    pPath  = stringToSymbol(szPath);
    FreeMem(szPath);
  }
  return pPath;
}

static void SPP_setCurMacSep(SPP_T pPP, string cTokVal)
{
  if( strlen(cTokVal) >= 2 )
  { char cSep = cTokVal[1];
    if( SPP_ISSPACE(cSep) ) *pPP->szCurMacSep = '\0';
    else *pPP->szCurMacSep = cSep;
  }
  else 
    *pPP->szCurMacSep = '\0';
}

static bool SPP_evalCond(SPP_T pPP, string cTokVal)
/* eval macro condition */
{ string szS = cTokVal, szT, szID;
  symbol pID;
  while( !SPP_ISSPACE(*szS) ) szS++;
  while(  SPP_ISSPACE(*szS) ) szS++;
  szID = StrCopy(szS); StrToLower(szID);
  pID  = stringToSymbol(szID);
  FreeMem(szID);
  szT = SPP_PREPAR(pPP,SPP_PAT_IFDEF);
  if( !strncmp(cTokVal,szT,strlen(szT)) )
  {
    return MAP_defined(pPP->pMacDfnMap,pID);
  }
  else
  {
    return ! MAP_defined(pPP->pMacDfnMap,pID);
  }
}

static void SPP_delMacro(SPP_T pPP, string cTokVal)
/* delete macro definition */
{ Sink        pSnk    = Sink_open();
  string      szS     = cTokVal + strlen(SPP_PREPAR(pPP,SPP_PAT_UNDEFINE)), szVal;
  symbol      pSym;
  // extract name
  while( SPP_ISSPACE(*szS) ) szS++;
  while( !SPP_ISSPACE(*szS) && 
         *szS != '(' && *szS != '='  && *szS != '\0' ) 
  {
    Sink_printf(pSnk,"%c",*szS); szS++;
  }
  szVal = Sink_close(pSnk); StrToLower(szVal);
  pSym  = stringToSymbol(szVal);
  // remove definition
  if( MAP_defined(pPP->pMacDfnMap,pSym) )
    MAP_rmvdom(pPP->pMacDfnMap,pSym);
  FreeMem(szVal); 
}

static void SPP_addMacro(SPP_T pPP, string cTokVal)
/* add macro definition */
{ Sink        pSnk    = Sink_open();
  ROW(symbol) pMacDfn = OT_CREATE_ADT(symbol);
  string      szS     = cTokVal + strlen(SPP_PREPAR(pPP,SPP_PAT_START)), szT, szVal;
  // extract name
  while( SPP_ISSPACE(*szS) ) szS++;
  while( !SPP_ISSPACE(*szS) && 
         *szS != '(' && *szS != '='  && *szS != '\0' ) 
  {
    Sink_printf(pSnk,"%c",*szS); szS++;
  }
  szVal = Sink_close(pSnk); StrToLower(szVal);
  MAP_ovrdom(pPP->pMacDfnMap,stringToSymbol(szVal),pMacDfn);
  FreeMem(szVal); 
  while( SPP_ISSPACE(*szS) ) szS++;
  // extract parameter
  if( *szS == '(' )
  {
    szS++; szT = strstr(szS,")");
    pSnk = Sink_open();
    while( szS != szT )
    {
      if( SPP_ISSPACE(*szS) )
        ;
      else
      if( *szS == ',' )
      {
        szVal = Sink_close(pSnk);
        OT_PUSH(stringToSymbol(szVal),pMacDfn);
        FreeMem(szVal);
        pSnk  = Sink_open(); 
      }
      else Sink_printf(pSnk,"%c",*szS);
      szS++;
    }
    szVal = Sink_close(pSnk);
    OT_PUSH(stringToSymbol(szVal),pMacDfn);
    FreeMem(szVal);
    szS++;
  }
  // extract value
  szT = strstr(szS,"=");
  if( szT != (string)NULL )
  {
    szS   = szT+1;
    szVal = SubStrCopy(szS,strlen(szS)-strlen(SPP_PREPAR(pPP,SPP_PAT_END)));
    OT_PUSH(stringToSymbol(szVal),pMacDfn);
    FreeMem(szVal);
  }
  else OT_PUSH(stringToSymbol(""),pMacDfn);
}

static long SPP_nextParameter
            (
              string szMacText, MAP(symbol,long) pParMap
            )
{ MAPIT pItr; symbol pParNam; long lParIdx;
  MAP_forItrAsg(pParNam,lParIdx,pItr,pParMap)
  {
    if( strstr(szMacText,symbolToString(pParNam)) == szMacText )
    {
      MAP_freeItr(pItr); return lParIdx;
    }
  }
  return -1;
}

static symbol SPP_evalMacro(ROW(symbol) pMacDfnRow, ROW(symbol) pMacParRow)
{ MAP(symbol,long) pParMap   = MAP_newPrimMap();
  long             lCnt      = OT_CNT(pMacDfnRow), lIdx, lI;
  symbol           pMacText  = OT_GET(symbol,pMacDfnRow,lCnt-1), pParNam;
  string           szMacText = symbolToString(pMacText), 
                   szS       = szMacText, szT;
  Sink             pSnk      = Sink_open();
  for( lI=0; lI < lCnt-1; ++lI )
  {
    pParNam = OT_GET(symbol,pMacDfnRow,lI);
    if( ! MAP_defined(pParMap,pParNam) ) MAP_dfndom(pParMap,pParNam,lI);
  }
  while( *szS != '\0' )
  {
    lIdx = SPP_nextParameter(szS,pParMap);
    if( lIdx < 0 ) 
    {
      Sink_printf(pSnk,"%c",*szS); ++szS;
    }
    else 
    {
      Sink_printf(pSnk,"%s",symbolToString(OT_GET(symbol,pMacParRow,lIdx))); 
      szS += strlen(symbolToString(OT_GET(symbol,pMacDfnRow,lIdx)));
    }
  }
  szT      = Sink_close(pSnk);
  pMacText = stringToSymbol(szT);
  MAP_freeMap(pParMap); FreeMem(szT);
  return pMacText;
}

static symbol SPP_applyParameter(SPP_T pPP, symbol pTokVal, symbol* pMacNam)
{ symbol      pTopMac    = OT_TOP(symbol,pPP->pCurMacRow), pMacVal;
  long        lCnt       = OT_CNT(pPP->pCurMacRow);
  ROW(symbol) pMacDfnRow = MAP_apply(ROW(symbol),pPP->pMacDfnMap,pTopMac),
              pMacParRow = OT_GET(ROW(symbol),pPP->pCurMacRow,lCnt-2);
  OT_PUSH(pTokVal,pMacParRow);
  *pMacNam = pTopMac;
  if( OT_CNT(pMacParRow) == OT_CNT(pMacDfnRow) - 1 )
  {
    pMacVal = SPP_evalMacro(pMacDfnRow, pMacParRow);
    OT_POP(pPP->pCurMacRow); OT_POP(pPP->pCurMacRow); OT_DEL_T(pMacParRow);
    if( OT_CNT(pPP->pCurMacRow) == 0 )
    {
      OT_DEL_T(pPP->pCurMacRow); pPP->pCurMacRow = (ROW(symbol))NULL;
      return pMacVal;
    }
    else return SPP_applyParameter(pPP,pMacVal,pMacNam);
  }
  else return (symbol)NULL;
}

static symbol SPP_applyMacro(SPP_T pPP, symbol pTokVal)
{ ROW(symbol) pMacDfnRow = MAP_apply(ROW(symbol),pPP->pMacDfnMap,pTokVal), pTmpRow;
  if( pPP->pCurMacRow == (ROW(symbol))NULL )
  {
    if( OT_CNT(pMacDfnRow) == 1 ) return OT_GET(symbol,pMacDfnRow,0);
    else
    {
      pPP->pCurMacRow = OT_CREATE_ADT(symbol);
      pTmpRow    = OT_CREATE_ADT(symbol);
      OT_PUSH(pTmpRow,pPP->pCurMacRow);
      OT_PUSH(pTokVal,pPP->pCurMacRow);
      return (symbol)NULL;
    }
  }
  else
  { symbol pMacNam;
    if( OT_CNT(pMacDfnRow) == 1 ) 
      return SPP_applyParameter(pPP,OT_GET(symbol,pMacDfnRow,0),&pMacNam);
    else
    {
      pTmpRow = OT_CREATE_ADT(symbol);
      OT_PUSH(pTmpRow,pPP->pCurMacRow);
      OT_PUSH(pTokVal,pPP->pCurMacRow);
      return (symbol)NULL;
    }
  }
}

static int SPP_prepare_rescan
           (
             SPP_T pPP, Scn_Stream pStream, 
             int nScnAction, symbol pMacNam, symbol* cMacVal
           )
/* prepare rescan action */
{ string szCharSet = (string)NULL;
  if( ( nScnAction == SCN_FLG_RescanString  && 
        ! Stream_unicode(pStream) )         ||
      ( nScnAction == SCN_FLG_RescanExtFile &&   
        strlen(szCharSet = SPP_PREPAR(pPP,SPP_INC_CHARSET)) == 0 ) )
  { 
    return nScnAction;
  }
  else
  { Scn_Stream_Itr pItr     = (Scn_Stream_Itr)NULL;
    GStream_T      pGS      = (GStream_T)NULL;
    c_string       szMacVal = symbolToString(*cMacVal),
                   szGSName = szMacVal;
    if( nScnAction == SCN_FLG_RescanExtFile )
    { FILE* pFP = OpnFile(szMacVal,"rb");
      pGS = GS_stream_file_new(pFP, szCharSet, C_True);
    } 
    else
    if( nScnAction == SCN_FLG_RescanString )
    {
      pGS = GS_stream_string_new(szMacVal,strlen(szMacVal)+1,CS_ID_MBYTE);
      if( pMacNam != (symbol)NULL )
        szGSName = symbolToString(pMacNam);
    } 
    assert1
    (
      pGS != (GStream_T)NULL, "creation of stream '%s' failed",szMacVal
    );
    pItr = Stream_Itr_new
           (
             GS_stream_get_wcrc, GS_fun_destruct(pGS), GS_ucs4_to_utf8, 
             GS_fun_seek(pGS), pGS, szGSName
           );
    *cMacVal = (symbol)pItr;
    return SCN_FLG_RescanChrItr;
  }
}

int SPP_premac
    (
      Scn_Stream pStream, string cTokNam, string cTokVal, symbol* cMacVal
    )
/* preprocesses current token of non-binary scan stream 'pStream'
   'cTokNam': name of separated token
   'cTokVal': value of separated token
   'cMacVal': preprocessing result ( see [scn_base] )
   ( cTokNam, cTokVal: single byte or utf-8 characterset ) 
*/
{ SPP_T pPP  = (SPP_T)Stream_get_ctxval(pStream,SPP_premac);
  long  lCnt;
  if( pPP == (SPP_T)NULL )
  {
    pPP = (SPP_T)Stream_get_ctxval(pStream,stringToSymbol("SPP_premac"));
    if( pPP == (SPP_T)NULL )
    {
      assert0(pCurPP != (SPP_T)NULL, szINIT_ERROR);
      pPP = pCurPP;
    }
    Stream_add_ctxval(pStream,SPP_premac,pPP);
  }
  lCnt = OT_CNT(pPP->pCondRow);
  if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACCOND)) )
  { 
    if( !strcmp(cTokVal,SPP_PREPAR(pPP,SPP_PAT_END)) ||
        !strcmp(cTokVal,SPP_PREPAR(pPP,SPP_PAT_ENDIF)) )
    {
      if( lCnt == 0 ) OT_PUSH(SPP_COND_ERROR,pPP->pCondRow);
      else            OT_POP(pPP->pCondRow);
    }
    else
    if( !strcmp(cTokVal,SPP_PREPAR(pPP,SPP_PAT_ELSE)) )
    {
      if( lCnt == 0 ) OT_PUSH(SPP_COND_ERROR,pPP->pCondRow);
      else
      {
        if( OT_TOP(long,pPP->pCondRow) == SPP_COND_SKIP )
          OT_UPD(long,pPP->pCondRow,lCnt-1,SPP_COND_SCAN);
        else 
        if( OT_TOP(long,pPP->pCondRow) == SPP_COND_SCAN )
          OT_UPD(long,pPP->pCondRow,lCnt-1,SPP_COND_SKIP);
      }
    }
    else
    if( lCnt == 0 || OT_TOP(long,pPP->pCondRow) == SPP_COND_SCAN )
    {
      if( SPP_evalCond(pPP,cTokVal) ) 
        OT_PUSH(SPP_COND_SCAN,pPP->pCondRow);
      else OT_PUSH(SPP_COND_SKIP,pPP->pCondRow);
    }
    else OT_PUSH(SPP_COND_ERROR,pPP->pCondRow);
    *cMacVal = (symbol)NULL;
    return SCN_FLG_RescanNone;
  }
  else
  {
    if( lCnt > 0 &&
        ( OT_TOP(long,pPP->pCondRow) == SPP_COND_ERROR ||
          OT_TOP(long,pPP->pCondRow) == SPP_COND_SKIP   ) )
    {
      *cMacVal = (symbol)NULL;
      return SCN_FLG_RescanNone;
    }
    else
    if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACINC)) )
    { 
      *cMacVal = SPP_getInclude(pPP,cTokVal);
      return SPP_prepare_rescan(pPP,pStream,SCN_FLG_RescanExtFile,(symbol)NULL,cMacVal);
    }
    else
    if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACDFN)) )
    { 
      SPP_addMacro(pPP,cTokVal);
      *cMacVal = (symbol)NULL;
      return SCN_FLG_RescanNone;
    }
    else
    if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACDEL)) )
    { 
      SPP_delMacro(pPP,cTokVal);
      *cMacVal = (symbol)NULL;
      return SCN_FLG_RescanNone;
    }
    else
    { symbol pValSym    = stringToSymbol(cTokVal), 
             pLowValSym = pValSym, 
             pMacNam    = (symbol)NULL;
      if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_IDE)) && !Stream_cica(pStream) )
      { c_string szLowTokVal = StrCopy(cTokVal);
        StrToLower(szLowTokVal);
        pLowValSym = stringToSymbol(szLowTokVal);
        FreeMem(szLowTokVal);
      } 
      if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_IDE)) && 
          MAP_defined(pPP->pMacDfnMap,pLowValSym)       )
      { 
        *cMacVal = SPP_applyMacro(pPP,pLowValSym);
        return ( *cMacVal != (symbol)NULL )
               ? SPP_prepare_rescan(pPP,pStream,SCN_FLG_RescanString,pLowValSym,cMacVal) 
               : SCN_FLG_RescanNone;
      }
      else
      if( !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACSEP)) && 
          ( pPP->pCurMacRow == (ROW(symbol))NULL || strcmp(cTokVal,pPP->szCurMacSep) ) )
      {
        SPP_setCurMacSep(pPP,cTokVal);
        *cMacVal = (symbol)NULL;
        return SCN_FLG_RescanNone;
      }
      else
      if( pPP->pCurMacRow != (ROW(symbol))NULL )
      {
        if( strlen(pPP->szCurMacSep) == 0 && Sink_empty(pPP->pCurMacPar) ) 
        {
          *cMacVal = SPP_applyParameter(pPP,pValSym,&pMacNam);
          return ( *cMacVal != (symbol)NULL )
                 ? SPP_prepare_rescan(pPP,pStream,SCN_FLG_RescanString,pMacNam,cMacVal) 
                 : SCN_FLG_RescanNone;
        }
        else
        {
          if( strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACSEP)) && 
              strcmp(cTokVal,pPP->szCurMacSep)                )
            Sink_printf(pPP->pCurMacPar,"%s",cTokVal);
          if( strlen(pPP->szCurMacSep) == 0                   ||
              !strcmp(cTokNam,SPP_PREPAR(pPP,SPP_TOK_MACSEP)) || 
              !strcmp(cTokVal,pPP->szCurMacSep)                )
          { string szPar = Sink_close(pPP->pCurMacPar);
            *cMacVal = SPP_applyParameter(pPP,stringToSymbol(szPar),&pMacNam);
            FreeMem(szPar); pPP->pCurMacPar = Sink_open();
            return ( *cMacVal != (symbol)NULL )
                   ? SPP_prepare_rescan(pPP,pStream,SCN_FLG_RescanString,pMacNam,cMacVal) 
                   : SCN_FLG_RescanNone;
          } 
          else
          {
            *cMacVal = (symbol)NULL;
            return SCN_FLG_RescanNone;
          }
        }
      }
      *cMacVal = pValSym;
      return SCN_FLG_RescanNone;
    }
  }
}

