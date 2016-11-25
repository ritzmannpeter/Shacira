/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prdps.c]                 Dependence Analysis                            */
/*                                                                          */
/* Copyright (c) 1996 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "list.h"
#include "otab.h"
#include "hmap.h"
#include "hset.h"
#include "symbols.h"
#include "glo_tab.h"
#include "pathes.h"
#include "dicts.h"
#include "sink.h"
#include "binimg.h"
#include "com_get.h"
#include "scn_base.h"
#include "scn_pre.h"
#include "ptm_gen.h"
#include "ptm.h"
#include "prjfun.h"

#include "cdps_lim.h"
#include "prdp_cim.h"
#include "cprj_int.h"
#include "cprj_lim.h"
#include "cprj_pim.h"
#include "reg_exp.h"

/* -------------------- Types, Constants & Globals ----------------------- */

#define CTX_PROJECT  CTX_EVAL(string,"project") 
#define CTX_DIAGNOSE CTX_EVAL(string,"diagnose") 
#define CTX_LEXSORT  CTX_EVAL(bool,"lexsort") 
#define CTX_STRICT   CTX_EVAL(bool,"strict") 
#define CTX_MULTISRC CTX_EVAL(bool,"multisrc") 
#define CTX_WARNINGS CTX_EVAL(bool,"warnings") 
#define CTX_CHANGES  CTX_EVAL(bool,"changes") 
#define CTX_MKNANO   CTX_EVAL(bool,"makeNANO") 
#define CTX_MKLIST   CTX_EVAL(bool,"makeLIST") 
#define CTX_REPLACE  CTX_EVAL(string,"replace") 
#define CTX_PATHSEP  CTX_EVAL(string,"pathsep") 
#define CTX_PREMAC   CTX_EVAL(string,"premac") 

#define lex(a,b) ((a) ? (a) : (b))

/* Assumption:

   The Macro and Source File Names are unique within the current 
   project definitions. 
   That means: Basename + Suffix can be treated as a Key.

   Root Source Files can't be in Object Files.

   GenerierungsabhÑngigkeiten zwischen Regeln mÅssen explizit durch eine
   entsprechende lexikalische Ordnung der Regelnamen sichergestellt sein.
*/

/* Function Type: DpsLib Init & Quit */
/*
   init: RC=0 <==> OK
   quit: RC=Memory Counter
*/
typedef long (*PFN_DpsLib)(void);

/* Function Type: Direct Dependency Evaluation */
/*
   Elements of pDepFiles must be released
*/
typedef void (*PFN_Dps)
             (
               string     szSrcPath,
               StdCPtr    pDepFiles,
               PFN_AddDep pAddDepFun, 
               bool*      pbRoot
             );

/* Function Type: External Rule Evaluation */
typedef void (*PFN_Ext)
             (
               ROW(string) pDstPathes, 
               SET(string) pSrcPathes,
               StdCPtr     pDstSrcGroups, 
               PFN_AddGrp  pAddGrpFun,
               PFN_AddDst  pAddDstFun,
               PFN_AddSrc  pAddSrcFun
             );
/* Function Type: External File Comparison */
typedef int (*PFN_Cmp)(string szLftPath, string szRgtPath);

ConcreteType(PRJ_Type)
{
  SET(symbol) pTypSfx; /* Suffixes of Source / Target Type                  */
  SET(symbol) pIncSfx; /* Source Dependant Suffixes of Source Type          */
  symbol      pObjSfx; /* Intermediate Target Suffix of Source Type or NULL */
  symbol      pFstSfx; /* First Source / Target Suffix                      */
};

ConcreteType(PRJ_Environ)
{
  symbol              pPrjDir;  /* Project Directory ( NMK )                  */
  symbol              pDstDir;  /* Target Directory ( EXE/RES/LIB/DLL )       */
  symbol              pObjDir;  /* Intermediate Directory ( OBJ )             */
  symbol              pDpsLib;  /* Typ Repository / DPS Library               */
  MAP(symbol,PT_Term) pOExtDir; /* Opt. External Include/Library Directories  */
  SET(symbol)         pExtDir;  /* External Include/Library Directories       */
  MAP(symbol,symbol)  pOExtLib; /* Opt. Ext. Libraries: File Name |--> Path   */
  MAP(symbol,symbol)  pExtLib;  /* (External) Libraries: File Name |--> Path  */
  MAP(symbol,ROW(symbol))        pTypCmd; 
                                /* Source/Target Type |--> Command            */
  MAP(symbol,MAP(symbol,symbol)) pCmdPar; 
                                /* Source/Target Type |--> Command Parameter  */
};

/*
   Optional external Libraries and Directories 
   belonging to the same Group have the same Path Term.
*/

ConcreteType(PRJ_Project)
{
  MAP(symbol,PRJ_Type) pTypDfn; /* Source/Target Types          */
  PRJ_Environ          pStdEnv; /* Standard Project Environment */
};

ConcreteType(PRJ_Rule)
{
  symbol                  pName;    /* Rule Name                           */
  cprjRuleAttr            pAttr;    /* Rule Attribute                      */
  symbol                  pSrcTyp;  /* Source Type                         */
  cprjSrcDfn              pSrcDfn;  /* Source Definition                   */
  cprjDstDfn              pDstDfn;  /* Target Definition                   */
  SET(symbol)             pSrcDir;  /* Source Directories                  */
  MAP(symbol,symbol)      pSrcPat;  /* Source Directory Pattern            */
  MAP(symbol,SET(symbol)) pDepDfn;  /* Rule Dependant |--> Target Suffixes */
  ROW(symbol)             pDepRow;  /* ordered Rule Dependants             */
  SET(symbol)             pNeeds;   /* Rule-Closure                        */
  SET(symbol)             pTargets; /* Targets                             */
  ROW(symbol)             pDstRow;  /* sorted Targets                      */
  PRJ_Environ             pRuleEnv; /* Rule Environment                    */
};

ConcreteType(PRJ_Source)
{
  symbol      pPath;   /* Path                                    */
  symbol      pFile;   /* Filename                                */
  symbol      pType;   /* Type                                    */
  long        lTime;   /* Last-modified time                      */
  SET(symbol) pDepDfn; /* direct Source Dependants of this Type,  */
                       /* Target Dependants (res,lib,...)         */
  SET(symbol) pNeeds;  /* Source-Dependant-Closure                */
  bool        bRoot;   /* Root Source or Modul Source             */
  symbol      pPrefix; /* Modul-Prefix or NULL ( -> Dep.Analyse ) */
};

ConcreteType(PRJ_Target)
{
  symbol             pPath;    /* Path                                    */
  symbol             pFile;    /* Filename                                */
  symbol             pType;    /* Type                                    */
  SET(symbol)        pSources; /* Sources / Source-Closure                */
  SET(symbol)        pNeeds;   /* direct dependant Targets                */
  MAP(symbol,symbol) pExtLib;  /* External Libraries: File Name |--> Path */
  PRJ_Rule           pRule;    /* Target Rule ( --> Environment )         */
  symbol             pNext;    /* Filename of next Target or NULL         */
                               /* Translation Unit: Target List           */
  symbol             pRoot;    /* Filename of Master Target or NULL       */ 
                               /* pSources,pNeeds only defined in         */
                               /* Single/Master Targets                   */
  ROW(symbol)        pSrcRow;  /* sorted Sources                          */
};

/* Preprocessing */
static SPP_T pPP = (SPP_T)NULL;
static MAP(long,symbol) pPreParMap = (MAP(_,_))NULL;

/* Diagnose */
static FILE* pFP_Diag = (FILE*)NULL;

/* Source Type |--> Dependency Evaluation Function */
static MAP(symbol,PFN_Dps) pDpsLib;

/* Sum of DPS Repository Memory Count */
static long lDpsLibMemCnt = 0;

/* Last Project File Modification Time */
static long lMaxPrjModTime = 0;

/* project definition file |--> project definition term */
static MAP(symbol,PT_Term) pPrjMap;

/* project definition */
static PRJ_Project pProject;

/* replace map */
static MAP(symbol,symbol) pReplaceMap;

/* macro name |--> expanded value */
static MAP(symbol,symbol) pMacMap;

/* source name |--> source definition (c|o h,rc,...) */
static MAP(symbol,PRJ_Source) pSrcMap, pPrevSrcMap;

/* target name |--> target definition (lib,res,dll,...) */
static MAP(symbol,PRJ_Target) pDstMap;

/* rule name |--> rule definition */
static MAP(symbol,PRJ_Rule) pRuleMap;
static MAP(symbol,long)     pRuleIdxMap;

static ROW(symbol) pRuleRow; // Rules, sortiert

static void (*pfnDepError)(PT_Term t, string f, ...);

/* -------------------------- Auxiliary ----------------------------------- */

static void PRJ_dummyDepError(PT_Term t, string f, ...)
{
}

static bool PRJ_IsMetaChar(char cC)
{
  return cC == '%' || cC == '$' || cC == '(' || cC == ')';
}

static bool PRJ_IsPatternChar(char cC)
{
  return cC == '?' || cC == '*' || cC == '&';
}

static string PRJ_convPathPattern(string szPattern)
{ long   lLen     = strlen(szPattern), lI;
  string szResult = (string)NULL;
  for( lI=0; lI < lLen; ++lI )
  {
    if( szResult == (string)NULL )
    {
      if( szPattern[lI] == '&' )
      {
        szResult = StrCopy(szPattern); szResult[lI] = '?';
      }
    }
    else
    if( szResult[lI] == '&' ) szResult[lI] = '?';
  }
  return szResult;
}

static bool PRJ_getPathPattern
            (
              string szPath, string* pszPath, string* pszPattern
            )
{ long lLen = strlen(szPath), lI;
  for( lI=lLen-1; lI >= 0; --lI )
  {
    if( PRJ_IsPatternChar(szPath[lI]) )
    { string szTmp;
      *pszPath    = FilePrefix(szPath);
      szTmp       = szPath+strlen(*pszPath);
      *pszPattern = StrCopy(szTmp+AbsolutePathSep(szTmp));
      return True;
    }
  }
  return False;
}

static string PRJ_getDstBaseByMask(string szSource, string szPattern)
/* target basename by source and directory pattern */
{ string szBase = BaseFile(szSource), szDstBase = (string)NULL;
  long   lLen   = strlen(szPattern), lI;
  if( strlen(szBase) == lLen )
  {
    szDstBase = StrCopy(szPattern);
    for( lI=0; lI < lLen; ++lI )
      if( szPattern[lI] == '&' ) szDstBase[lI] = szBase[lI];
  }
  FreeMem(szBase);
  return szDstBase;
}

static bool PRJ_IsNumber(string s)
{ long lLen = strlen(s), lI;
  for( lI=0; lI < lLen; ++lI )
    if( ! isdigit(s[lI]) ) return False;
  return True;
}

static void PRJ_getMacro(string szNam, string* pszMac)
{ symbol pNam  = stringToSymbol(szNam), pVal;
  *pszMac = (string)NULL;
  if( MAP_defined(pMacMap,pNam) )
  { 
    pVal = MAP_apply(symbol,pMacMap,pNam);
    if( pVal != (symbol)NULL ) 
      *pszMac = symbolToString(pVal);
  } 
}

static int PRJ_expandMacro(string szS, string* pszMac, bool bEnv)
{ string szTmp, szDft; int nI = 0, nP;
  *pszMac = (string)NULL;
  szTmp   = StrCopy(szS);
  if( szTmp != (string)NULL )
  {
    while( szS[nI] != '\0' && ! PRJ_IsMetaChar(szS[nI]) ) ++nI;
    szTmp[nI] = '\0';
    if( bEnv ) 
    {
      szDft = strstr(szTmp,":");
      if( szDft != (string)NULL )
      {
        *szDft   = '\0';
        szDft   += 1;
        *pszMac  = getenv(szTmp);
        if( *pszMac == (string)NULL )
        {
          if( *szDft == '&' )
          {
            PRJ_getMacro(szDft+1,pszMac);
          }
          else
          {
            *pszMac = symbolToString(stringToSymbol(szDft));
          }
        }
      }
      else 
      {
        *pszMac = getenv(szTmp);
      }
    }
    else       
    if( PRJ_IsNumber(szTmp) && ( nP = atoi(szTmp) ) < CTX_argcnt() )
    {
      *pszMac = CTX_ARGVAL(string,nP);
    }
    else
    {
      PRJ_getMacro(szTmp,pszMac);
    }
    FreeMem(szTmp);
  }
  return nI;
}

static string PRJ_expandName(string szNam)
{ string szRes = (string)NULL, szS, szMac, szTmp;
  if( szNam != (string)NULL )
  { Sink pSnk = Sink_open();
    bool bOK  = True;
    szS = szNam;
    while( *szS != '\0' )
    { char cC = *szS;
      if( ! PRJ_IsMetaChar(cC) ) 
      {
        Sink_putc(pSnk,cC); szS += 1;
      }
      else
      {
        szS += 1;
        if( cC == '%' )
        { 
          szS += PRJ_expandMacro(szS,&szMac,True);
          assert0((*szS=='%'),"");
          szS += 1;
          if( szMac != (string)NULL ) 
          {
            Sink_puts(pSnk,szMac);
          }
          else { bOK = False; break; }
        }
        else
        if( cC == '$' )
        {
          if( *szS != '(' )
          {
            szS += PRJ_expandMacro(szS,&szMac,True);
            if( szMac != (string)NULL ) 
            {
              Sink_puts(pSnk,szMac);
            }
            else { bOK = False; break; }
          } 
          else
          {
            szS += 1;
            szS += PRJ_expandMacro(szS,&szMac,False);
            if( szMac != (string)NULL ) 
            {
              Sink_puts(pSnk,szMac);
            }
            else { bOK = False; break; }
            assert2((*szS==')'),"end of macro %s, %s",szMac,szS);
            szS += 1;
          }
        }
        else //C_BUG;
        {
          Sink_putc(pSnk,cC); 
        }
      }
    }
    szTmp = Sink_close(pSnk);
    if( bOK && szTmp != (string)NULL ) 
    {
      szRes = szTmp;
    }
    else      
    if( szTmp != (string)NULL ) FreeMem(szTmp);
  }
  return szRes;
}

static symbol PRJ_ValueToSymbol(GLS_Tok pVal)
{ symbol pRes  = (symbol)NULL;
  string szTmp = GLS_Tok_string(pVal), szTmp2, szVal, szMac;
  szVal  = StrCopy(szTmp+1); 
  szTmp2 = szVal+strlen(szVal)-1;
  while( *szTmp2 == '\r' || *szTmp2 == '\n' )
  {
    *szTmp2 = '\0'; --szTmp2;
  }
  //szVal[strlen(szVal)-2] = '\0';
  szMac = ( *szTmp == '~' ) ? PRJ_expandName(szVal) : StrCopy(szVal);
  if( szMac != (string)NULL )
  {
    pRes = stringToSymbol(szMac);
    FreeMem(szMac);
  }
  else PT_error(pVal,"value specification: %s",szTmp);
  FreeMem(szVal);
  return pRes;
}

static symbol PRJ_NameToSymbol(GLS_Tok pVal)
{ symbol pRes  = (symbol)NULL;
  string szTmp = symbolToString(GLS_Tok_symbol(pVal)),
         szMac = PRJ_expandName(szTmp);
  if( szMac != (string)NULL )
  {
    pRes = stringToSymbol(szMac);
    FreeMem(szMac);
  }
  else PT_error(pVal,"path specification: %s",szTmp);
  return pRes;
}

static bool PRJ_IsRecursive(cprjSrcDfn pSrcDfn)
{ cprjSrcAttr pSrcAttr;
  assert0(cprjSrcDfn_dfn(pSrcDfn,_,&pSrcAttr),"");
  return cprjSrcAttr_rexp(pSrcAttr,_);
}

static GLS_Tok PRJ_getSrcPathes(cprjSrcDfn pSrcDfn)
{ GLS_Tok pSrcPathes;
  assert0(cprjSrcDfn_dfn(pSrcDfn,&pSrcPathes,_),"");
  return pSrcPathes;
}

static Reg_T PRJ_getRegExp(cprjSrcDfn pSrcDfn)
{ cprjSrcAttr pSrcAttr;
  cprjRegExp  pRegExp;
  Reg_T       pRScn = (Reg_T)NULL;
  assert0(cprjSrcDfn_dfn(pSrcDfn,_,&pSrcAttr),"");
  if( ! cprjSrcAttr_exp(pSrcAttr,&pRegExp) )
    assert0( cprjSrcAttr_rexp(pSrcAttr,&pRegExp), "");
  if( !cprjRegExp_nul(pRegExp) )
  { GLS_Tok pRTok;
    assert0( cprjRegExp_exp(pRegExp,&pRTok), "");
    assert0(pRScn = REG_CREATE(symbolToString(PRJ_ValueToSymbol(pRTok))),"");
  }
  return pRScn;
}

static bool PRJ_IsExecutable(cprjRuleAttr pRuleAttr)
{ 
  return( cprjRuleAttr_exe(pRuleAttr) || cprjRuleAttr_ex2(pRuleAttr) );
}

static bool PRJ_NoSourceDerivedTargets(cprjRuleAttr pRuleAttr)
{ 
  return( cprjRuleAttr_ex2(pRuleAttr) );
}

static bool PRJ_IsExternalTarget(cprjDstDfn pDstDfn)
{ 
  return( cprjDstDfn_ext(pDstDfn) );
}

static bool PRJ_IsInternalTarget(cprjDstDfn pDstDfn, GLS_Tok* pType)
{ 
  return( cprjDstDfn_int(pDstDfn,pType,_,_,_) );
}

static PRJ_Type PRJ_getTargetType(cprjDstDfn pDstDfn)
{ PRJ_Type pResult = (PRJ_Type)NULL;
  GLS_Tok  pDstTyp;
  if( PRJ_IsInternalTarget(pDstDfn,&pDstTyp)                 &&
      MAP_defined(pProject->pTypDfn,GLS_Tok_symbol(pDstTyp))  )
    pResult = MAP_apply(PRJ_Type,pProject->pTypDfn,GLS_Tok_symbol(pDstTyp));
  return pResult;
}

static PRJ_Type PRJ_getTargetTypeSym(cprjDstDfn pDstDfn)
{ symbol  pResult = (symbol)NULL;
  GLS_Tok pDstTyp;
  if( PRJ_IsInternalTarget(pDstDfn,&pDstTyp) )
    pResult = GLS_Tok_symbol(pDstTyp);
  return pResult;
}

static symbol PRJ_getTargetPrefix(cprjDstDfn pDstDfn)
{ symbol         pResult = (symbol)NULL;
  cprjOptTPrefix pOptPrefix;
  GLS_Tok        pPrefix;
  if( cprjDstDfn_int(pDstDfn,_,_,&pOptPrefix,_) &&
      cprjOptTPrefix_pre(pOptPrefix,&pPrefix)    )
    pResult = GLS_Tok_symbol(pPrefix);
  return pResult;
}

static symbol PRJ_getSourcePrefix(cprjDstDfn pDstDfn)
{ symbol         pResult = (symbol)NULL;
  cprjOptSPrefix pOptPrefix;
  GLS_Tok        pPrefix;
  if( cprjDstDfn_int(pDstDfn,_,_,_,&pOptPrefix) &&
      cprjOptSPrefix_pre(pOptPrefix,&pPrefix)    )
    pResult = GLS_Tok_symbol(pPrefix);
  return pResult;
}

static bool PRJ_IsTargetByRoot(cprjDstDfn pDstDfn)
{ cprjDstName pDstName;
  return( cprjDstDfn_int(pDstDfn,_,&pDstName,_,_) && cprjDstName_root(pDstName) );
}

static bool PRJ_IsTargetByDirectory(cprjDstDfn pDstDfn)
{ cprjDstName pDstName;
  return( cprjDstDfn_int(pDstDfn,_,&pDstName,_,_) && cprjDstName_dir(pDstName) );
}

static bool PRJ_IsTargetBySource(cprjDstDfn pDstDfn)
{ cprjDstName pDstName;
  return( cprjDstDfn_int(pDstDfn,_,&pDstName,_,_) && cprjDstName_src(pDstName) );
}

static bool PRJ_IsTargetByName(cprjDstDfn pDstDfn, GLS_Tok* pName)
{ cprjDstName pDstName;
  return
  ( 
    cprjDstDfn_int(pDstDfn,_,&pDstName,_,_) && cprjDstName_nam(pDstName,pName) 
  );
}

static bool PRJ_IsInclude
            (
              symbol pIncSfx, symbol pSrcTyp,
              SET(symbol) pIncSfxSet, symbol* pRefSrcTyp
            )
/*
   Evaluation Rule:
   1) Member
   2) Refernce
   3) Dynamic (*)
   else) False
*/
{
  if( HS_MBR_ELM(pIncSfx,pIncSfxSet) )
  {
    if( pRefSrcTyp != (symbol*)NULL ) *pRefSrcTyp = pSrcTyp; 
    return True;
  }
  else
  { HS_Itr   pItr;
    symbol   pSfx, pTyp;
    string   szSfx;
    PRJ_Type pTypDfn; 
    HS_FORALL(pSfx,pItr,pIncSfxSet)
    {
      szSfx   = symbolToString(pSfx);
      if( *szSfx == '&' )
      {
        pTyp    = stringToSymbol(szSfx+1);
        pTypDfn = MAP_apply(PRJ_Type,pProject->pTypDfn,pTyp);
        if( PRJ_IsInclude(pIncSfx,pTyp,pTypDfn->pIncSfx,pRefSrcTyp) )
        {
          HS_DROP_ITR(pItr); return True;
        }
      }
    }
    if( HS_MBR_ELM(stringToSymbol("*"),pIncSfxSet) )
    {
      if( pRefSrcTyp != (symbol*)NULL ) *pRefSrcTyp = pSrcTyp; 
      return True;
    }
  }
  if( pRefSrcTyp != (symbol*)NULL ) *pRefSrcTyp = (symbol*)NULL;
  return False;
}

static SET(string) PRJ_SymbolToStringSet
                   (
                     SET(string) pDstSet, SET(symbol) pSrcSet
                   )
{ SET(string) pResSet = ( pDstSet == (SET(string))NULL ) 
                        ? HS_CREATE_ADTSET(string) : pDstSet;
  HS_Itr      pItr;
  symbol      pElm;
  HS_FORALL(pElm,pItr,pSrcSet)
  {
    HS_SET_ELM(symbolToString(pElm),pResSet);
  }
  return pResSet;
}

static void PRJ_setPathSep(string szPathes, PIT pItr)
{ int  nLen = strlen(CTX_PATHSEP), nI;
  char szSep[2];
  szSep[1] = '\0';
  for( nI=0; nI < nLen; ++nI )
  { 
    szSep[0] = CTX_PATHSEP[nI];
    if( strstr(szPathes,szSep) != (string)NULL )
    {
      PIT_sep(pItr,szSep); return;
    }
  }
  PIT_sep(pItr,";");
}

/* --------------------- DpsLib CallBack Functions ------------------------ */

static void PRJ_addGrp(StdCPtr pGBag, StdCPtr* ppTBag, StdCPtr* ppSBag)
{ MAP(ROW(symbol),SET(symbol)) pDstSrcGroups = (MAP(_,_))pGBag;
  ROW(symbol) pTargets = OT_CREATE_ADT(symbol);
  SET(symbol) pSources = HS_CREATE_ADTSET(symbol);
  MAP_dfndom(pDstSrcGroups,pTargets,pSources);
  *ppTBag = pTargets;
  *ppSBag = pSources;
}

static void PRJ_addDst(StdCPtr pBag, string szDstFile, string szDstPath)
{ ROW(symbol) pTargets = (ROW(symbol))pBag;
  OT_PUSH(stringToSymbol(szDstFile),pTargets);
  OT_PUSH(stringToSymbol(szDstPath),pTargets);
}

static void PRJ_addSrc(StdCPtr pBag, string szSrcFile)
{ SET(symbol) pSources = (SET(symbol))pBag;
  HS_SET_ELM(stringToSymbol(szSrcFile),pSources);
}

/* --------------------- Create & Release Ressources ---------------------- */

static PRJ_Type PRJ_newType(void)
{ PRJ_Type pType = (PRJ_Type)NewMem(SizeOf(PRJ_Type));
  pType->pFstSfx = (symbol)NULL;
  pType->pObjSfx = (symbol)NULL;
  pType->pTypSfx = HS_CREATE_ADTSET(symbol);
  pType->pIncSfx = HS_CREATE_ADTSET(symbol);
  return pType;
}

static PRJ_Environ PRJ_newEnviron(void)
{ PRJ_Environ pEnviron = (PRJ_Environ)NewMem(SizeOf(PRJ_Environ));
  pEnviron->pPrjDir    = (symbol)NULL;
  pEnviron->pDstDir    = (symbol)NULL;
  pEnviron->pObjDir    = (symbol)NULL;
  pEnviron->pDpsLib    = (symbol)NULL;
  pEnviron->pOExtDir   = MAP_newPrimMap();
  pEnviron->pExtDir    = HS_CREATE_ADTSET(symbol);
  pEnviron->pOExtLib   = MAP_newPrimMap();
  pEnviron->pExtLib    = MAP_newPrimMap();
  pEnviron->pTypCmd    = MAP_newPrimMap();
  pEnviron->pCmdPar    = MAP_newPrimMap();
  return pEnviron;
}

static void PRJ_unionEnviron(PRJ_Environ pTarget, PRJ_Environ pSource)
{ HS_Itr             pSItr; 
  MAPIT              pMItr;
  symbol             pFile, pDir, pType;
  GLS_Tok            pPathes;
  ROW(symbol)        pCmds;
  MAP(symbol,symbol) pPars;
  if( pTarget->pPrjDir == (symbol)NULL ) pTarget->pPrjDir = pSource->pPrjDir;
  if( pTarget->pDstDir == (symbol)NULL ) pTarget->pDstDir = pSource->pDstDir;
  if( pTarget->pObjDir == (symbol)NULL ) pTarget->pObjDir = pSource->pObjDir;
  if( pTarget->pDpsLib == (symbol)NULL ) pTarget->pDpsLib = pSource->pDpsLib;
  MAP_forItrAsg(pDir,pPathes,pMItr,pSource->pOExtDir) 
    if( ! MAP_defined(pTarget->pOExtDir,pDir) )
      MAP_dfndom(pTarget->pOExtDir,pDir,pPathes);
  HS_FORALL(pDir,pSItr,pSource->pExtDir) HS_SET_ELM(pDir,pTarget->pExtDir);
  if( MAP_count(pTarget->pOExtLib) == 0 )
    MAP_forItrAsg(pFile,pDir,pMItr,pSource->pOExtLib)
      MAP_dfndom(pTarget->pOExtLib,pFile,pDir);
  if( MAP_count(pTarget->pExtLib) == 0 )
    MAP_forItrAsg(pFile,pDir,pMItr,pSource->pExtLib)
      MAP_dfndom(pTarget->pExtLib,pFile,pDir);
  MAP_forItrAsg(pType,pCmds,pMItr,pSource->pTypCmd)
  {
    if( ! MAP_defined(pTarget->pTypCmd,pType) )
    {
      MAP_dfndom(pTarget->pTypCmd,pType,OT_COPY(pCmds));
    }
  }
  MAP_forItrAsg(pType,pPars,pMItr,pSource->pCmdPar)
  {
    if( ! MAP_defined(pTarget->pCmdPar,pType) )
    {
      MAP_dfndom(pTarget->pCmdPar,pType,MAP_prim_copy(pPars));
    }
  }
}

static PRJ_Project PRJ_newProject(void)
{ PRJ_Project pProject = (PRJ_Project)NewMem(SizeOf(PRJ_Project));
  pProject->pTypDfn    = MAP_newPrimMap();
  pProject->pStdEnv    = PRJ_newEnviron();
  return pProject;
}

static PRJ_Rule PRJ_newRule(void)
{ PRJ_Rule pRule  = (PRJ_Rule)NewMem(SizeOf(PRJ_Rule));
  pRule->pName    = (symbol)NULL;
  pRule->pAttr    = (cprjRuleAttr)NULL;
  pRule->pSrcTyp  = (symbol)NULL;
  pRule->pSrcDfn  = (cprjSrcDfn)NULL;
  pRule->pDstDfn  = (cprjDstDfn)NULL;
  pRule->pSrcDir  = HS_CREATE_ADTSET(symbol);
  pRule->pSrcPat  = MAP_newPrimMap();
  pRule->pDepDfn  = MAP_newPrimMap();
  pRule->pDepRow  = OT_CREATE_ADT(symbol);
  pRule->pTargets = HS_CREATE_ADTSET(symbol);
  pRule->pNeeds   = HS_CREATE_ADTSET(symbol);
  pRule->pRuleEnv = PRJ_newEnviron();
  pRule->pDstRow  = OT_CREATE_ADT(symbol);
  return pRule;
}

static PRJ_Source PRJ_newSource(void)
{ PRJ_Source pSource = (PRJ_Source)NewMem(SizeOf(PRJ_Source));
  pSource->pDepDfn   = HS_CREATE_ADTSET(symbol);
  pSource->pNeeds    = HS_CREATE_ADTSET(symbol);
  pSource->pPath     = (symbol)NULL;
  pSource->pFile     = (symbol)NULL;
  pSource->pType     = (symbol)NULL;
  pSource->lTime     = 0;
  pSource->bRoot     = False;
  pSource->pPrefix   = (symbol)NULL;
  return pSource;
}

static PRJ_Target PRJ_newTarget(PRJ_Rule pRule, SET(symbol) pSources)
{ PRJ_Target pTarget = (PRJ_Target)NewMem(SizeOf(PRJ_Target));
  pTarget->pSources  = pSources;
  pTarget->pRule     = pRule;
  pTarget->pNeeds    = pSources!=(SET(symbol))NULL
                       ?HS_CREATE_ADTSET(symbol):(SET(symbol))NULL;
  pTarget->pExtLib   = pSources!=(SET(symbol))NULL
                       ?MAP_newPrimMap():(MAP(symbol,symbol))NULL;
  pTarget->pSrcRow   = pSources!=(SET(symbol))NULL
                       ?OT_CREATE_ADT(symbol):(ROW(symbol))NULL;
  pTarget->pPath     = (symbol)NULL;
  pTarget->pFile     = (symbol)NULL;
  pTarget->pType     = (symbol)NULL;
  pTarget->pNext     = (symbol)NULL;
  pTarget->pRoot     = (symbol)NULL;
  return pTarget;
}

static void PRJ_freeType(PRJ_Type pType)
{ 
  HS_DROP_SET(pType->pIncSfx);
  HS_DROP_SET(pType->pTypSfx);
  FreeMem(pType);
}

static void PRJ_freeEnviron(PRJ_Environ pEnviron)
{ MAPIT pItr; HMP_Dom pDom; HMP_Rng pRng;
  MAP_freeMap(pEnviron->pOExtDir);
  HS_DROP_SET(pEnviron->pExtDir);
  MAP_freeMap(pEnviron->pOExtLib);
  MAP_freeMap(pEnviron->pExtLib);
  MAP_forItrAsg(pDom,pRng,pItr,pEnviron->pTypCmd) OT_DEL_T(pRng);
  MAP_freeMap(pEnviron->pTypCmd);
  MAP_forItrAsg(pDom,pRng,pItr,pEnviron->pCmdPar) MAP_freeMap(pRng);
  MAP_freeMap(pEnviron->pCmdPar);
  FreeMem(pEnviron);
}

static void PRJ_freeProject(PRJ_Project pProject)
{ MAPIT pItr; HMP_Dom pDom; HMP_Rng pRng;
  MAP_forItrAsg(pDom,pRng,pItr,pProject->pTypDfn) PRJ_freeType(pRng);
  MAP_freeMap(pProject->pTypDfn);
  PRJ_freeEnviron(pProject->pStdEnv);
  FreeMem(pProject);
}

static void PRJ_freeRule(PRJ_Rule pRule)
{ MAPIT pItr; HMP_Dom pDom; HMP_Rng pRng;
  MAP_forItrAsg(pDom,pRng,pItr,pRule->pDepDfn) HS_DROP_SET(pRng);
  MAP_freeMap(pRule->pDepDfn);
  OT_DEL_T(pRule->pDepRow);
  HS_DROP_SET(pRule->pSrcDir);
  MAP_freeMap(pRule->pSrcPat);
  HS_DROP_SET(pRule->pTargets);
  HS_DROP_SET(pRule->pNeeds);
  PRJ_freeEnviron(pRule->pRuleEnv);
  OT_DEL_T(pRule->pDstRow);
  FreeMem(pRule);
}

static void PRJ_freeSource(PRJ_Source pSource)
{ 
  HS_DROP_SET(pSource->pDepDfn);
  HS_DROP_SET(pSource->pNeeds);
  FreeMem(pSource);
}

static void PRJ_freeTarget(PRJ_Target pTarget)
{ 
  if( pTarget->pSources != (SET(symbol))NULL ) HS_DROP_SET(pTarget->pSources);
  if( pTarget->pNeeds != (SET(symbol))NULL )   HS_DROP_SET(pTarget->pNeeds);
  if( pTarget->pExtLib != (MAP(symbol,symbol))NULL )
    MAP_freeMap(pTarget->pExtLib);
  if( pTarget->pSrcRow != (ROW(symbol))NULL )  OT_DEL_T(pTarget->pSrcRow);
  FreeMem(pTarget);
}

static void PRJ_newRessources(void)
{
  pProject    = PRJ_newProject();
  pDpsLib     = MAP_newPrimMap();
  pPrjMap     = MAP_newPrimMap();
  pMacMap     = MAP_newPrimMap();
  pSrcMap     = MAP_newPrimMap();
  pPrevSrcMap = MAP_newPrimMap();
  pDstMap     = MAP_newPrimMap();
  pRuleMap    = MAP_newPrimMap();
  pReplaceMap = MAP_newPrimMap();
  pRuleIdxMap = MAP_newPrimMap();
  pRuleRow    = OT_CREATE_ADT(symbol);
}

static void PRJ_freeRessources(void)
{ MAPIT pItr; HMP_Dom pDom; HMP_Rng pRng;
  OT_DEL_T(pRuleRow);
  MAP_forItrAsg(pDom,pRng,pItr,pSrcMap)     
  {
    if( ! MAP_defined(pPrevSrcMap,pDom) ||
        ((PRJ_Source)pRng) != MAP_apply(PRJ_Source,pPrevSrcMap,pDom) )
      PRJ_freeSource(pRng);
  }
  MAP_freeMap(pSrcMap);
  MAP_forItrAsg(pDom,pRng,pItr,pPrevSrcMap) PRJ_freeSource(pRng);
  MAP_freeMap(pPrevSrcMap);
  MAP_forItrAsg(pDom,pRng,pItr,pDstMap)     PRJ_freeTarget(pRng);
  MAP_freeMap(pDstMap);
  MAP_freeMap(pMacMap);
  MAP_forItrAsg(pDom,pRng,pItr,pRuleMap)    PRJ_freeRule(pRng);
  MAP_freeMap(pRuleMap);
  MAP_freeMap(pRuleIdxMap);
  MAP_forItrAsg(pDom,pRng,pItr,pPrjMap)     PT_delT(pRng);
  MAP_freeMap(pPrjMap);
  MAP_freeMap(pDpsLib);
  MAP_freeMap(pReplaceMap);
  PRJ_freeProject(pProject);
}

/*forward*/
/**/ static void C_parse
                 (
                   string szSrcPath, StdCPtr pDepFiles,
                   PFN_AddDep pAddDepFun, bool* pbRoot
                 );

static void PRJ_initDpsLib(void)
{
  MAP_dfndom(pDpsLib,stringToSymbol("C"),C_parse);
  MAP_dfndom(pDpsLib,stringToSymbol("SRC"),C_parse);
  MAP_dfndom(pDpsLib,stringToSymbol("MOC_S"),C_parse);
}

static void PRJ_init(int argc, string argv[])
{ PIT pItr; string s, r, t1, t2;
  CTX_init_prdps(argc,argv);
  initSymbols();
  MAP_init();
  Glo_init();
  cprj_initSymbols();
  PRJ_newRessources();
  PRJ_initDpsLib();
  if( CTX_STRICT )   pfnDepError = PT_error;
  else
  if( CTX_WARNINGS ) pfnDepError = PT_warn;
  else               pfnDepError = PRJ_dummyDepError;
  s = CTX_REPLACE;
  if( s != (string)NULL && strlen(s) > 0 )
  { 
    pItr = PIT_make(s); PIT_sep(pItr,";");
    while( ( t1 = PIT_read(pItr) ) != NULL )
    { 
      r  = StrCopy(t1);
      t2 = strstr(r,"=");
      if( t2 != (string)NULL )
      {
        *t2 = '\0';
        if( *r == '^' ) // start sequence condition
        {
          MAP_ovrdom(pReplaceMap,stringToSymbol(""),stringToSymbol(t2+1));
          MAP_ovrdom(pReplaceMap,(symbol)NULL,stringToSymbol(r+1));
        }
        else
          MAP_ovrdom(pReplaceMap,stringToSymbol(r),stringToSymbol(t2+1));
      }
      FreeMem(r);
    }
    PIT_drop(pItr);
  }
  /* init preprocessing */
  pPreParMap = MAP_newPrimMap();
  MAP_dfndom(pPreParMap,SPP_TOK_IDE,stringToSymbol("Name"));
  MAP_dfndom(pPreParMap,SPP_TOK_MACDFN,stringToSymbol("MMacDfn"));
  pPP = SPP_init_reentrant(pPreParMap);
  /* add pre-defined macros */
  if( strlen(CTX_PREMAC) > 0 )
  { 
    pItr = PIT_make(CTX_PREMAC); PIT_sep(pItr,",");
    while( ( s = PIT_read(pItr) ) != NULL )
    {
      SPP_addCtxMacro_reentrant(pPP,lstringToSymbol(s));
    }
    PIT_drop(pItr);
  }
}

static void PRJ_quit(void)
{
  if( pPreParMap != (MAP(_,_))NULL ) MAP_freeMap(pPreParMap);
  if( pPP != (SPP_T)NULL )           SPP_quit_reentrant(pPP);
  PRJ_freeRessources();
  cprj_quitSymbols();
  Glo_quit();
  MAP_quit();
  freeSymbols();
  CTX_quit();
}

/* ---------------------------- get & put --------------------------------- */

static void PRJ_get(void)
/* read source file image */
{ string szMstPrj = BaseFile(CTX_PROJECT),
         szFile   = MkPath
                    (
                      symbolToString(pProject->pStdEnv->pPrjDir),
                      szMstPrj,".dps",'d'
                    ),
         szPath;
  if( IsPath(szFile) && lMaxPrjModTime < PathMTime(szFile) )
  { long lCnt, lCnt2, lI, lJ, lTime;
    bool bRoot;
    getBgn("",szFile,"");
    getHeader("prdps",1,0);
    getLong(&lCnt);
    for( lI=0; lI < lCnt; ++lI )
    { PRJ_Source pSource = PRJ_newSource();
      symbol     pSymbol;
      getSymbol(&pSymbol);
      pSource->pPath   = pSymbol;
      getSymbol(&pSymbol);
      pSource->pFile   = pSymbol;
      getSymbol(&pSymbol);
      pSource->pType   = pSymbol;
      getLong(&lTime);
      pSource->lTime   = lTime;
      getInt(&bRoot);
      pSource->bRoot   = bRoot;
      getLong(&lCnt2);
      if( lCnt2 > 0 )
      {
        getSymbol(&pSymbol);
        pSource->pPrefix = pSymbol;
      }
      getLong(&lCnt2);
      for( lJ=0; lJ < lCnt2; ++lJ )
      {
        getSymbol(&pSymbol);
        HS_SET_ELM(pSymbol,pSource->pDepDfn);       
      }
      szPath = MkPath
               (
                 symbolToString(pSource->pPath),
                 symbolToString(pSource->pFile),"",'d'
               );
      if( IsPath(szPath) )
        MAP_dfndom(pPrevSrcMap,pSource->pFile,pSource);
      else
        PRJ_freeSource(pSource);
      FreeMem(szPath);
    }
    getEnd();
  }
  FreeMem(szMstPrj); FreeMem(szFile);
}

static void PRJ_put(void)
/* write source file image */
{ string     szMstPrj = BaseFile(CTX_PROJECT),
             szFile   = MkPath
                        (
                          symbolToString(pProject->pStdEnv->pPrjDir),
                          szMstPrj,".dps",'d'
                        ),
             szHdr    = Str_printf
                        (
                          "[%s.dps] binary file for 'prdps'\n",szMstPrj
                        );
  MAPIT      pMItr;
  HS_Itr     pSItr;
  PRJ_Source pSource;
  symbol     pFile, pDepSym;
  long       lCnt = 0;
  putBgn("",szFile,"");
  putHeader(szHdr,"prdps",1,0);
  putLong(MAP_count(pSrcMap));
  MAP_forItrAsg(pFile,pSource,pMItr,pSrcMap)
  {
    putSymbol(pSource->pPath);
    putSymbol(pSource->pFile);
    putSymbol(pSource->pType);
    putLong(pSource->lTime);
    putInt(pSource->bRoot);
    lCnt = pSource->pPrefix != (symbol)NULL;
    putLong(lCnt);
    if( lCnt > 0 ) putSymbol(pSource->pPrefix);
    putLong(HS_CARD(pSource->pDepDfn));
    HS_FORALL(pDepSym,pSItr,pSource->pDepDfn)
      putSymbol(pDepSym);
  }
  putEnd();
  FreeMem(szMstPrj); FreeMem(szFile); FreeMem(szHdr);
}

/* -------------------------- Analysis ------------------------------------ */

/* -------------------------- Dependencies -------------------------------- */

//TODO: report same error only once !!!
static void PRJ_printDepError(symbol pLft, symbol pRgt, PT_Term t)
{
  if( t != (PT_Term)NULL )
  {
    if( pLft != pRgt )
      (*pfnDepError)
      (
        t, "reflexive dependance between %s and %s",
        symbolToString(pLft), symbolToString(pRgt)
      );
  }
  else
  {
    if( pLft != pRgt && ( CTX_STRICT || CTX_WARNINGS ) )
      fprintf
      (
        STDERR, "reflexive dependance between %s and %s\n",
        symbolToString(pLft), symbolToString(pRgt)
      );
    if( CTX_STRICT )
      PT_setErrorCnt(PT_errorCnt() + 1);
  }
}

static int PRJ_cmpRules(OT_Obj pLft, OT_Obj pRgt)
{ PRJ_Rule pLftRule = MAP_apply(PRJ_Rule,pRuleMap,(symbol)pLft),
           pRgtRule = MAP_apply(PRJ_Rule,pRuleMap,(symbol)pRgt);
  if( CTX_LEXSORT                    || 
      ! PT_hasPos(pLftRule->pDstDfn) ||
      ! PT_hasPos(pRgtRule->pDstDfn)  )
    return 
      strcmp(symbolToString(pLftRule->pName),symbolToString(pRgtRule->pName));
  else
    return (int)(PT_row(pLftRule->pDstDfn) - PT_row(pRgtRule->pDstDfn));
}

static void PRJ_sortRules_aux(symbol pRuleSym, SET(symbol) pVisitSet)
{ PRJ_Rule    pRule = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym);
  ROW(symbol) pTmp  = OT_CREATE_ADT(symbol);
  long        lCnt, lI;
  symbol      pDepSym;
  HS_Itr      pItr;
  HS_SET_ELM(pRuleSym,pVisitSet);
  HS_FORALL(pDepSym,pItr,pRule->pNeeds)
  { 
    if( MAP_defined(pRuleMap,pDepSym) )
    { PRJ_Rule pDepRule = MAP_apply(PRJ_Rule,pRuleMap,pDepSym);
      if( pRule->pName != pDepRule->pName           &&
          HS_MBR_ELM(pRule->pName,pDepRule->pNeeds) &&
          HS_MBR_ELM(pDepRule->pName,pRule->pNeeds)  )
        PRJ_printDepError(pRule->pName,pDepRule->pName,(PT_Term)NULL);
      OT_S_INS(pTmp,pDepSym,PRJ_cmpRules);
    }
  }
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pDepSym = OT_GET(symbol,pTmp,lI);
    if( ! HS_MBR_ELM(pDepSym,pVisitSet) )
      PRJ_sortRules_aux(pDepSym,pVisitSet); 
  }
  OT_PUSH(pRuleSym,pRuleRow);
  OT_DEL_T(pTmp);
}

static void PRJ_sortRules(void)
/* sort build rules */
{ symbol      pRuleSym;
  SET(symbol) pVisitSet = HS_CREATE_ADTSET(symbol);
  ROW(symbol) pTmp      = OT_CREATE_ADT(symbol);
  long        lCnt, lI;
  MAPIT       pItr;
  MAP_forItr(pRuleSym,pItr,pRuleMap)
    OT_S_INS(pTmp,pRuleSym,PRJ_cmpRules);
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pRuleSym = OT_GET(symbol,pTmp,lI);
    if( ! HS_MBR_ELM(pRuleSym,pVisitSet) )
      PRJ_sortRules_aux(pRuleSym,pVisitSet); 
  }
  lCnt = OT_CNT(pRuleRow);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pRuleSym = OT_GET(symbol,pRuleRow,lI);
    MAP_dfndom(pRuleIdxMap,pRuleSym,lI);
  }
  OT_DEL_T(pTmp);
  HS_DROP_SET(pVisitSet);
}

static void PRJ_addRuleNeedsClosure(void)
/* build rule closure */
{ symbol   pRuleSym, pRuleSym2;
  PRJ_Rule pRule,    pRule2;
  MAPIT    pItr;
  HS_Itr   pItr2;
  long     lCard;
  bool     bChanges = True;
  while( bChanges == True )
  {
    bChanges = False;
    MAP_forItrAsg(pRuleSym,pRule,pItr,pRuleMap)
    { 
      lCard = HS_CARD(pRule->pNeeds);
      if( lCard > 0 )
      { SET(symbol) pTmp = HS_COPY(pRule->pNeeds);
        HS_FORALL(pRuleSym2,pItr2,pTmp)
        {
          if( pRuleSym != pRuleSym2 )
          {
            pRule2 = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym2);
            HS_UNION(pRule->pNeeds,pRule->pNeeds,pRule2->pNeeds);
            if( HS_CARD(pRule->pNeeds) != lCard ) bChanges = True;
          }
        }
        HS_DROP_SET(pTmp);
      }
    }
  }
}

static int PRJ_cmpSources(OT_Obj pLft, OT_Obj pRgt)
{
  return 
    strcmp(symbolToString((symbol)pLft),symbolToString((symbol)pRgt));
}

static void PRJ_sortTargetSources_aux
            (
              ROW(symbol) pSrcRow, symbol pSrcSym,
              SET(symbol) pSrcSet, SET(symbol) pVisitSet
            )
{ PRJ_Source  pSource = MAP_apply(PRJ_Source,pSrcMap,pSrcSym);
  ROW(symbol) pTmp    = OT_CREATE_ADT(symbol);
  long        lCnt, lI;
  symbol      pDepSym;
  HS_Itr      pItr;
  HS_SET_ELM(pSrcSym,pVisitSet);
  HS_FORALL(pDepSym,pItr,pSource->pNeeds)
  { 
    if( MAP_defined(pSrcMap,pDepSym) )
    { PRJ_Source pDepSource = MAP_apply(PRJ_Source,pSrcMap,pDepSym);
      if( HS_MBR_ELM(pSource->pFile,pDepSource->pNeeds) &&
          HS_MBR_ELM(pDepSource->pFile,pSource->pNeeds)  )
      { bool bError = True;
	if( pSource->pPrefix == pDepSource->pPrefix && 
	    pSource->pPrefix != (symbol)NULL         )
        { string szPrefix = symbolToString(pSource->pPrefix);
          if( strstr(symbolToString(pSource->pFile),szPrefix) &&
	      !strcmp(symbolToString(pSource->pFile)+strlen(szPrefix),
		      symbolToString(pDepSource->pFile)) )
	    bError = False;
	  else 
          if( strstr(symbolToString(pDepSource->pFile),szPrefix) &&
	      !strcmp(symbolToString(pDepSource->pFile)+strlen(szPrefix),
		      symbolToString(pSource->pFile)) )
	    bError = False;
	}
	if( bError )
          PRJ_printDepError(pSource->pFile,pDepSource->pFile,(PT_Term)NULL);
      }
      OT_S_INS(pTmp,pDepSym,PRJ_cmpSources);
    }
  }
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pDepSym = OT_GET(symbol,pTmp,lI);
    if( HS_MBR_ELM(pDepSym,pSrcSet) && ! HS_MBR_ELM(pDepSym,pVisitSet) )
      PRJ_sortTargetSources_aux(pSrcRow,pDepSym,pSrcSet,pVisitSet); 
  }
  OT_PUSH(pSrcSym,pSrcRow);
  OT_DEL_T(pTmp);
}

static void PRJ_sortTargetSources(PRJ_Target pTarget, SET(symbol) pSorted)
/* sort not sorted target sources */
{ SET(symbol)      pSrcSet   = HS_CREATE_ADTSET(symbol),
                   pVisitSet = HS_CREATE_ADTSET(symbol);
  ROW(symbol)      pTmp      = OT_CREATE_ADT(symbol);
  long             lCnt, lI;
  symbol           pSrcSym;
  HS_Itr           pItr;
  HS_FORALL(pSrcSym,pItr,pTarget->pSources)
  { 
    if( CTX_MULTISRC || ! HS_MBR_ELM(pSrcSym,pSorted) )
    {
      OT_S_INS(pTmp,pSrcSym,PRJ_cmpSources);
      HS_SET_ELM(pSrcSym,pSrcSet);
      HS_SET_ELM(pSrcSym,pSorted);
    }
  }
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pSrcSym = OT_GET(symbol,pTmp,lI);
    if( ! HS_MBR_ELM(pSrcSym,pVisitSet) )
      PRJ_sortTargetSources_aux(pTarget->pSrcRow,pSrcSym,pSrcSet,pVisitSet); 
  }
  OT_DEL_T(pTmp);
  HS_DROP_SET(pSrcSet);
  HS_DROP_SET(pVisitSet);
}

static symbol PRJ_getSrcMod(PRJ_Source pSource, symbol pSrcModTyp, symbol pSrcModPrefix)
/* get source modul for include 'pSource' or null */
{ PRJ_Type pType    = MAP_apply(PRJ_Type,pProject->pTypDfn,pSrcModTyp);
  string   szSuffix = FileSuffix(symbolToString(pSource->pFile)), 
           szExt    = szSuffix + (*szSuffix=='.'),
           szBase, szFile;
  symbol   pSrcMod  = (symbol)NULL, pModSfx;
  if( PRJ_IsInclude(
        stringToSymbol(szExt),pSrcModTyp,pType->pIncSfx,(symbol*)NULL) )
  { HS_Itr pItr;
    szBase  = BaseFile(symbolToString(pSource->pFile));
    HS_FORALL(pModSfx,pItr,pType->pTypSfx)
    {
      if( pSrcModPrefix != (symbol)NULL )
        szFile  = Str_printf("%s%s.%s",symbolToString(pSrcModPrefix),
			szBase,symbolToString(pModSfx));
      else
        szFile  = Str_printf("%s.%s",szBase,symbolToString(pModSfx));
      pSrcMod = stringToSymbol(szFile);
      if( MAP_defined(pSrcMap,pSrcMod) )
      {
        FreeMem(szFile);
        HS_DROP_ITR(pItr); break;
      }
      else pSrcMod = (symbol)NULL;
      FreeMem(szFile);
    }
    if( pSrcMod == (symbol)NULL && pType->pObjSfx != (symbol)NULL )
    {
      if( pSrcModPrefix != (symbol)NULL )
        szFile  = Str_printf("%s%s.%s",symbolToString(pSrcModPrefix),
			szBase,symbolToString(pType->pObjSfx));
      else
        szFile  = Str_printf("%s.%s",szBase,symbolToString(pType->pObjSfx));
      pSrcMod = stringToSymbol(szFile);
      if( ! MAP_defined(pSrcMap,pSrcMod) )
        pSrcMod = (symbol)NULL;
      FreeMem(szFile);
    }
    FreeMem(szBase);
  }
  FreeMem(szSuffix);
  return pSrcMod;
}

static void PRJ_addSourceNeedsClosure(void)
/* build source closure */
{ symbol     pSrcSym, pSrcSym2, pSrcSym3, pSuffix;
  PRJ_Source pSource, pSource2, pSource3;
  PRJ_Type   pSrcTyp;
  MAPIT      pItr;
  HS_Itr     pItr2;
  string     szSuffix, szExt;
  long       lCard;
  bool       bChanges = True;
  while( bChanges == True )
  {
    bChanges = False;
    MAP_forItrAsg(pSrcSym,pSource,pItr,pSrcMap)
    { 
      lCard = HS_CARD(pSource->pNeeds);
      if( lCard > 0 )
      { SET(symbol) pTmp = HS_COPY(pSource->pNeeds);
        pSrcTyp  = MAP_apply(PRJ_Type,pProject->pTypDfn,pSource->pType);
        szSuffix = FileSuffix(symbolToString(pSource->pFile)); 
        szExt    = szSuffix + (*szSuffix=='.');
        pSuffix  = stringToSymbol(szExt);
        HS_FORALL(pSrcSym2,pItr2,pTmp)
        {
          if( MAP_defined(pSrcMap,pSrcSym2) )
          {
            pSource2 = MAP_apply(PRJ_Source,pSrcMap,pSrcSym2);
            HS_UNION(pSource->pNeeds,pSource->pNeeds,pSource2->pNeeds);
            if( pSource->pType == pSource2->pType         &&
                ( HS_MBR_ELM(pSuffix,pSrcTyp->pTypSfx) ||
                  pSrcTyp->pObjSfx == pSuffix           )  )
            {
              pSrcSym3 = PRJ_getSrcMod(pSource2,pSource->pType,(symbol)NULL);
              if( pSrcSym3 != (symbol)NULL && pSrcSym2 != pSrcSym3 )
              {
                pSource3 = MAP_apply(PRJ_Source,pSrcMap,pSrcSym3);
                HS_SET_ELM(pSrcSym3,pSource->pNeeds);
                HS_UNION(pSource->pNeeds,pSource->pNeeds,pSource3->pNeeds);
              }
	      if( pSource2->pPrefix != (symbol)NULL )
	      {
                pSrcSym3 = PRJ_getSrcMod(pSource2,pSource->pType,pSource2->pPrefix);
                if( pSrcSym3 != (symbol)NULL && pSrcSym2 != pSrcSym3 )
                {
                  pSource3 = MAP_apply(PRJ_Source,pSrcMap,pSrcSym3);
                  HS_SET_ELM(pSrcSym3,pSource->pNeeds);
                  HS_UNION(pSource->pNeeds,pSource->pNeeds,pSource3->pNeeds);
                }
	      }
            }
            if( HS_CARD(pSource->pNeeds) != lCard ) bChanges = True;
          }
        }
        FreeMem(szSuffix);
        HS_DROP_SET(pTmp);
      }
    }
  }
  if( pFP_Diag != (FILE*)NULL )
  {
    fprintf(pFP_Diag,"\n\n\n>>> Source-Closure:");
    MAP_forItrAsg(pSrcSym,pSource,pItr,pSrcMap)
    {
      fprintf(pFP_Diag,"\n\n\t%s:",symbolToString(pSrcSym));
      HS_FORALL(pSrcSym2,pItr2,pSource->pNeeds)
        fprintf(pFP_Diag,"\n\t\t%s",symbolToString(pSrcSym2));
    }
  }
}

static SET(symbol) PRJ_collectIncludes(PRJ_Source pSource)
/* collect dependant include sources */
{ SET(symbol) pIncSet = HS_CREATE_ADTSET(symbol);
  PRJ_Type    pSrcTyp = MAP_apply(PRJ_Type,pProject->pTypDfn,pSource->pType);
  PRJ_Source  pDepSrc1, pDepSrc2;
  HS_Itr      pItr1, pItr2;
  symbol      pNeed1, pNeed2;
  string      szDepSfx1, szDepSfx2, szExt;
  HS_FORALL(pNeed1,pItr1,pSource->pDepDfn)
  { 
    if( MAP_defined(pSrcMap,pNeed1) && pSource->pFile != pNeed1 )
    {
      pDepSrc1  = MAP_apply(PRJ_Source,pSrcMap,pNeed1);
      szDepSfx1 = FileSuffix(symbolToString(pNeed1));
      szExt     = szDepSfx1 + (*szDepSfx1=='.');
      if( PRJ_IsInclude(
            stringToSymbol(szExt),pSource->pType,
            pSrcTyp->pIncSfx,(symbol*)NULL) )
      {
        HS_SET_ELM(pNeed1,pIncSet);
        HS_FORALL(pNeed2,pItr2,pDepSrc1->pNeeds)
        {
          if( MAP_defined(pSrcMap,pNeed2) && pNeed1 != pNeed2 )
          {
            pDepSrc2  = MAP_apply(PRJ_Source,pSrcMap,pNeed2);
            szDepSfx2 = FileSuffix(symbolToString(pNeed2));
            szExt     = szDepSfx2 + (*szDepSfx2=='.');
            if( PRJ_IsInclude(
                  stringToSymbol(szExt),pSource->pType,
                  pSrcTyp->pIncSfx,(symbol*)NULL) )
              HS_SET_ELM(pNeed2,pIncSet);
            FreeMem(szDepSfx2);
          }
        }
      }
      FreeMem(szDepSfx1); 
    }
  }
  return pIncSet;
}

static bool PRJ_IsNeededTarget(symbol pTarget, SET(symbol) pNeeds)
{ HS_Itr pItr;
  symbol pElm;
  HS_FORALL(pElm,pItr,pNeeds)
  { PRJ_Target pDepTarget = MAP_apply(PRJ_Target,pDstMap,pElm);
    if( pDepTarget->pRoot == pTarget )
    {
      HS_DROP_ITR(pItr); return True;
    }
  }
  return False;
}

static PFN_Cmp pCurExtCmp = (PFN_Cmp)NULL;

static int PRJ_cmpTargets(OT_Obj pLft, OT_Obj pRgt)
{
  return 
    strcmp(symbolToString((symbol)pLft),symbolToString((symbol)pRgt));
}

static int PRJ_cmpTargets_ext(OT_Obj pLft, OT_Obj pRgt)
{
  return 
    ( pCurExtCmp != (PFN_Cmp)NULL )
    ? (*pCurExtCmp)(symbolToString((symbol)pLft),symbolToString((symbol)pRgt))
    : strcmp(symbolToString((symbol)pLft),symbolToString((symbol)pRgt));
}

static void PRJ_sortRuleTargets_aux
            (
              ROW(symbol) pDstRow, symbol pDstSym,
              SET(symbol) pDstSet, SET(symbol) pVisitSet
            )
{ PRJ_Target  pTarget = MAP_apply(PRJ_Target,pDstMap,pDstSym),
              pDepTarget, pRootTarget;
  ROW(symbol) pTmp    = OT_CREATE_ADT(symbol);
  long        lCnt, lI;
  symbol      pDepSym, pRoot;
  HS_Itr      pItr;
  HS_SET_ELM(pDstSym,pVisitSet);
  HS_FORALL(pDepSym,pItr,pTarget->pNeeds)
  { 
    if( MAP_defined(pDstMap,pDepSym) )
    { 
      pDepTarget  = MAP_apply(PRJ_Target,pDstMap,pDepSym);
      pRoot       = ( pDepTarget->pRoot == (symbol)NULL ) 
                    ? pDepSym : pDepTarget->pRoot;
      pRootTarget = MAP_apply(PRJ_Target,pDstMap,pRoot);
      if( PRJ_IsNeededTarget(pTarget->pFile,pRootTarget->pNeeds) &&
          PRJ_IsNeededTarget(pDepTarget->pFile,pTarget->pNeeds)   )
        PRJ_printDepError(pTarget->pFile,pDepTarget->pFile,(PT_Term)NULL);
      OT_S_INS(pTmp,pRoot,PRJ_cmpTargets);
    }
  }
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pDepSym = OT_GET(symbol,pTmp,lI);
    if( HS_MBR_ELM(pDepSym,pDstSet) && ! HS_MBR_ELM(pDepSym,pVisitSet) )
      PRJ_sortRuleTargets_aux(pDstRow,pDepSym,pDstSet,pVisitSet); 
  }
  OT_PUSH(pDstSym,pDstRow);
  OT_DEL_T(pTmp);
}

static void PRJ_sortRuleTargets(PRJ_Rule pRule)
/* sort rule root targets */
{ SET(symbol)      pDstSet   = HS_CREATE_ADTSET(symbol),
                   pVisitSet = HS_CREATE_ADTSET(symbol);
  ROW(symbol)      pTmp      = OT_CREATE_ADT(symbol);
  long             lCnt, lI;
  symbol           pDstSym;
  HS_Itr           pItr;
  int (*pCmpFun)(OT_Tab pLft, OT_Tab pRgt) = PRJ_cmpTargets;
  if( PRJ_IsExternalTarget(pRule->pDstDfn) ) // externe Sortierung
  { string szExtFun = Str_printf
                      (
                        "%s_cmpTargets",symbolToString(pRule->pSrcTyp)
                      ); 
    if( pRule->pRuleEnv->pDpsLib != (symbol)NULL )
      pCurExtCmp = (PFN_Cmp)Glo_load
                   (
                     pRule->pRuleEnv->pDpsLib,stringToSymbol(szExtFun),True
                   );
    pCmpFun = PRJ_cmpTargets_ext;
    FreeMem(szExtFun);
  }
  HS_FORALL(pDstSym,pItr,pRule->pTargets)
  { 
    if( MAP_apply(PRJ_Target,pDstMap,pDstSym)->pRoot == (symbol)NULL )
    {
      OT_S_INS(pTmp,pDstSym,pCmpFun);
      HS_SET_ELM(pDstSym,pDstSet);
    }
  }
  lCnt = OT_CNT(pTmp);
  for( lI=0; lI < lCnt; ++lI )
  { 
    pDstSym = OT_GET(symbol,pTmp,lI);
    if( ! HS_MBR_ELM(pDstSym,pVisitSet) )
      PRJ_sortRuleTargets_aux(pRule->pDstRow,pDstSym,pDstSet,pVisitSet); 
  }
  OT_DEL_T(pTmp);
  HS_DROP_SET(pDstSet);
  HS_DROP_SET(pVisitSet);
  pCurExtCmp = (PFN_Cmp)NULL;
}

static void PRJ_addTargetRootSourceClosure(void)
/* build root source closure for all targets with build rule 'byRoot' */
{ MAPIT    pItr1;
  symbol   pRuleSym, pDstSym, pSrcSym, pDepSym, pSuffix, pPath, pFile;
  PRJ_Rule pRule;
  MAP_forItrAsg(pRuleSym,pRule,pItr1,pRuleMap)
  {
    if( PRJ_IsTargetByRoot(pRule->pDstDfn) )
    { HS_Itr   pItr2, pItr3, pItr4;
      PRJ_Type pSrcTyp = MAP_apply(PRJ_Type,pProject->pTypDfn,pRule->pSrcTyp);
      HS_FORALL(pDstSym,pItr2,pRule->pTargets)
      { PRJ_Target pTarget = MAP_apply(PRJ_Target,pDstMap,pDstSym);
        if( pTarget->pRoot == (symbol)NULL && HS_CARD(pTarget->pSources) > 0 )
        { SET(symbol) pTmp = HS_COPY(pTarget->pSources);
          HS_FORALL(pSrcSym,pItr3,pTmp)
          { PRJ_Source pSource = MAP_apply(PRJ_Source,pSrcMap,pSrcSym);
            HS_FORALL(pDepSym,pItr4,pSource->pNeeds)
            { string szDepSym = symbolToString(pDepSym),
                     szSuffix = FileSuffix(szDepSym),
                     szExt    = szSuffix + (*szSuffix=='.'),
                     szPath   = FilePrefix(szDepSym),
                     szTmp    = szDepSym+strlen(szPath),
                     szFile   = szTmp+AbsolutePathSep(szTmp);
              pSuffix = stringToSymbol(szExt);
              pFile   = stringToSymbol(szFile);
              if( MAP_defined(pSrcMap,pFile) )
              {
                pPath = MAP_apply(PRJ_Source,pSrcMap,pFile)->pPath;
                if( ( HS_MBR_ELM(pSuffix,pSrcTyp->pTypSfx) || 
                      pSuffix == pSrcTyp->pObjSfx           ) &&
                    HS_MBR_ELM(pPath,pRule->pSrcDir)           )
                  HS_SET_ELM(pFile,pTarget->pSources);
              }
              FreeMem(szSuffix); FreeMem(szPath);
            }
          }
          HS_DROP_SET(pTmp);
        }
      }
    }
  }
}

static void PRJ_addInternalTargetNeed
            (
              symbol pDepSrcFile, PRJ_Target pTarget, bool bInclude
            )
/* add internal target need */
{ MAPIT       pMItr;
  HS_Itr      pSItr;
  symbol      pRuleSym, pDstSym;
  string      szDepBase, szDstBase, szDstSfx, szExt;
  SET(symbol) pSuffixes;
  PRJ_Source  pDepSource = MAP_apply(PRJ_Source,pSrcMap,pDepSrcFile);
  bool        bFound     = False;
  MAP_forItrAsg(pRuleSym,pSuffixes,pMItr,pTarget->pRule->pDepDfn)
  { PRJ_Rule pRule = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym);
    if( pRule->pSrcTyp == pDepSource->pType          &&
        HS_MBR_ELM(pDepSource->pPath,pRule->pSrcDir)  )
    {
      if( PRJ_IsTargetByDirectory(pRule->pDstDfn) ||
          PRJ_IsTargetBySource(pRule->pDstDfn)     )
      { 
        if( PRJ_IsTargetByDirectory(pRule->pDstDfn) )
        {
          if( MAP_defined(pRule->pSrcPat,pDepSource->pPath) )
          {
            szDepBase = PRJ_getDstBaseByMask
                        (
                          symbolToString(pDepSrcFile), 
                          symbolToString
                          (
                            MAP_apply(symbol,pRule->pSrcPat,pDepSource->pPath)
                          )
                        );
          }
          else szDepBase = BaseFile(symbolToString(pDepSource->pPath));
        }
        else
        {
          szDepBase = BaseFile(symbolToString(pDepSrcFile));
        }
        if( szDepBase != (string)NULL )
        {
          HS_FORALL(pDstSym,pSItr,pRule->pTargets)
          { PRJ_Target pRuleTarget = MAP_apply(PRJ_Target,pDstMap,pDstSym);
            if( pRuleTarget->pRoot != pTarget->pRoot || 
                ( pTarget->pRoot == (symbol)NULL && pDstSym != pTarget->pFile ) )
            {
              szDstBase = BaseFile(symbolToString(pDstSym));
              szDstSfx  = FileSuffix(symbolToString(pDstSym));
              szExt     = szDstSfx + (*szDstSfx=='.');
              if( ! strcmp(szDepBase,szDstBase) && 
                  ( HS_CARD(pSuffixes) == 0 || 
                    HS_MBR_ELM(stringToSymbol(szExt),pSuffixes) ) )
              {
                HS_SET_ELM(pDstSym,pTarget->pNeeds);
                bFound = True;
              }
              FreeMem(szDstBase); FreeMem(szDstSfx);
            }
          }
          FreeMem(szDepBase);
        }
      }
      else
      if( PRJ_IsTargetByName(pRule->pDstDfn, _) )
      {
        HS_FORALL(pDstSym,pSItr,pRule->pTargets)
        { PRJ_Target pRuleTarget = MAP_apply(PRJ_Target,pDstMap,pDstSym);
          if( pRuleTarget->pRoot != pTarget->pRoot || 
              ( pTarget->pRoot == (symbol)NULL && pDstSym != pTarget->pFile ) )
          {
            szDstSfx = FileSuffix(symbolToString(pDstSym));
            szExt    = szDstSfx + (*szDstSfx=='.');
            if( HS_CARD(pSuffixes) == 0 || 
                HS_MBR_ELM(stringToSymbol(szExt),pSuffixes) )
            {
              HS_SET_ELM(pDstSym,pTarget->pNeeds);
              bFound = True;
            }
            FreeMem(szDstSfx);
          }
        }
      }
/* Baustelle
      else
      if( PRJ_IsTargetByRoot(pRule->pDstDfn) )
      {
      }
*/
      if( bInclude ) bFound = True;
    }
  }
  if( ! bFound )
  {
    (*pfnDepError)
    (
      pTarget->pRule->pDstDfn,"target for %s not found",
      symbolToString(pDepSrcFile)
    );
  }
}

static symbol PRJ_getExtDir(symbol pPath, symbol pFile, PRJ_Rule pRule)
/* external directory symbol of 'pFile' or NULL */ 
{ symbol pResult = (symbol)NULL, pExtDir;
  if( HS_MBR_ELM(pPath,pRule->pRuleEnv->pExtDir) ) pResult = pPath;
  else
  { HS_Itr pItr;
    HS_FORALL(pExtDir,pItr,pRule->pRuleEnv->pExtDir)
    { string szPath = MkPath
                      (
                        symbolToString(pExtDir),symbolToString(pFile),"",'d'
                      );
      if( IsPath(szPath) )
      {
        pResult = pExtDir; 
        FreeMem(szPath);
        HS_DROP_ITR(pItr); break;
      }
      FreeMem(szPath);
    }
  }
  return pResult;
}

static void PRJ_addTargetNeed
            (
              PRJ_Source pSource, symbol pDepSym, PRJ_Target pTarget
            )
/* add target need */
{ string   szDepSym = symbolToString(pDepSym),
           szSuffix = FileSuffix(szDepSym),
           szExt    = szSuffix + (*szSuffix=='.'),
           szPath   = FilePrefix(szDepSym),
           szTmp    = szDepSym+strlen(szPath),
           szFile   = szTmp+AbsolutePathSep(szTmp),
                      szDepBase, szDstBase;
  symbol   pSuffix  = stringToSymbol(szExt),
           pPath    = stringToSymbol(szPath),
           pFile    = stringToSymbol(szFile), 
                      pExtDir, pExtLib, pExtLibDir;
  PRJ_Type pSrcTyp  = MAP_apply
                      (
                        PRJ_Type,pProject->pTypDfn,pTarget->pRule->pSrcTyp
                      );
  bool     bInclude = PRJ_IsInclude
                      (
                        pSuffix,pTarget->pRule->pSrcTyp,
                        pSrcTyp->pIncSfx,(symbol*)NULL
                      );
  if( MAP_defined(pSrcMap,pFile) )
  { PRJ_Source pDepSource = MAP_apply(PRJ_Source,pSrcMap,pFile);
    if( PRJ_NoSourceDerivedTargets(pTarget->pRule->pAttr) )
      /*do nothing*/;
    else
    if( pDepSource->pType != pTarget->pRule->pSrcTyp            ||
        ! HS_MBR_ELM(pDepSource->pPath,pTarget->pRule->pSrcDir)  )
    {
      PRJ_addInternalTargetNeed(pFile,pTarget,bInclude);
    }
    else
    {
      if( PRJ_IsTargetByDirectory(pTarget->pRule->pDstDfn) )
      {
        if( pSource->pPath != pDepSource->pPath )
          PRJ_addInternalTargetNeed(pFile,pTarget,bInclude);
        else
        if( MAP_defined(pTarget->pRule->pSrcPat,pDepSource->pPath) )
        {
          szDepBase = PRJ_getDstBaseByMask
                      (
                        symbolToString(pFile), 
                        symbolToString
                        (
                          MAP_apply
                          (
                            symbol,pTarget->pRule->pSrcPat,pDepSource->pPath
                          )
                        )
                      );
          szDstBase = BaseFile(symbolToString(pTarget->pFile));
          if( szDepBase == (string)NULL || strcmp(szDepBase,szDstBase) )
            PRJ_addInternalTargetNeed(pFile,pTarget,bInclude);
          if( szDepBase != (string)NULL ) FreeMem(szDepBase); 
          FreeMem(szDstBase);
        }
      }
      else
      if( PRJ_IsTargetBySource(pTarget->pRule->pDstDfn) )
      {
        szDepBase = BaseFile(szFile);
        szDstBase = BaseFile(symbolToString(pTarget->pFile));
        if( strcmp(szDepBase,szDstBase) )
          PRJ_addInternalTargetNeed(pFile,pTarget,bInclude);
        FreeMem(szDepBase); FreeMem(szDstBase);
      }
      /* equal source types and source path membership and 
         rule by name, by root, external 
         --> no dependant source-derivated target
      */
    }
  }
  else
  if( MAP_defined(pDstMap,pFile) ) // zusaetzliche Pfadpruefung ?!
  { PRJ_Target pDepTarget = MAP_apply(PRJ_Target,pDstMap,pFile);
    if( pDepTarget->pType != pTarget->pRule->pSrcTyp )
      HS_SET_ELM(pFile,pTarget->pNeeds);
    else
      (*pfnDepError)
      (
        pTarget->pRule->pDstDfn,"target dependant %s has source type",
        symbolToString(pFile)
      );
  }
  else
  { 
    if( HS_MBR_ELM(pSuffix,pSrcTyp->pTypSfx) )
      (*pfnDepError)
      (
        pTarget->pRule->pDstDfn,"external source %s not allowed",
        symbolToString(pFile)
      );
    else
    { 
      if( ! MAP_defined(pTarget->pRule->pRuleEnv->pExtLib,pFile) )
      {
        pExtDir = PRJ_getExtDir(pPath, pFile, pTarget->pRule);
        if( pExtDir == (symbol)NULL && strlen(szPath) == 0 )
          (*pfnDepError)
          (
            pTarget->pRule->pDstDfn, "path for %s not found", 
            symbolToString(pFile)
          );
        else
        if( ! bInclude )
        {
          if( strlen(szPath) > 0 ) pExtDir = pPath;
          if( ! MAP_defined(pTarget->pExtLib,pFile) )
            MAP_dfndom(pTarget->pExtLib,pFile,pExtDir);
        }
        else // Inference of optional external Libraries
        if( MAP_defined(pTarget->pRule->pRuleEnv->pOExtDir,pExtDir) )
        { MAPIT pItr;
          MAP_forItrAsg
          (
            pExtLib,pExtLibDir,pItr,pTarget->pRule->pRuleEnv->pOExtLib
          )
          {
            if(   MAP_apply
                  (
                    PT_Term,pTarget->pRule->pRuleEnv->pOExtDir,pExtLibDir
                  ) 
               == MAP_apply
                  (
                    PT_Term,pTarget->pRule->pRuleEnv->pOExtDir,pExtDir
                  ) 
               && ! MAP_defined(pTarget->pExtLib,pExtLib) )
              MAP_dfndom(pTarget->pExtLib,pExtLib,pExtLibDir);
          }
        }
      }
    }
  }
  FreeMem(szSuffix); FreeMem(szPath);
}

static void PRJ_addTargetNeeds(void)
/* add target needs */
{ symbol       pDstSym, pSrcSym, pDepSym, pLibFile;
  PRJ_Target   pTarget;
  MAPIT        pItr1, pItr2;
  MAP_forItrAsg(pDstSym,pTarget,pItr1,pDstMap)
  {
    if( pTarget->pRoot == (symbol)NULL          &&
        PRJ_IsExecutable(pTarget->pRule->pAttr)  )
    { HS_Itr pItr3, pItr4;
      MAP_forItr(pLibFile,pItr2,pTarget->pRule->pRuleEnv->pExtLib)
      {
        if( MAP_defined(pDstMap,pLibFile) )
          HS_SET_ELM(pLibFile,pTarget->pNeeds);
      }
      HS_FORALL(pSrcSym,pItr3,pTarget->pSources)
      { PRJ_Source pSource = MAP_apply(PRJ_Source,pSrcMap,pSrcSym);
        HS_FORALL(pDepSym,pItr4,pSource->pNeeds)
        {
          if( ! HS_MBR_ELM(pDepSym,pTarget->pSources) )
          {
            PRJ_addTargetNeed(pSource, pDepSym, pTarget);
          }
        }
      }
    }
  }
}

/* -------------------------- Standard Scanner ---------------------------- */

static void C_parse
            (
              string szSrcPath, StdCPtr pDepFiles,
              PFN_AddDep pAddDepFun, bool* pbRoot
            )
/* Dependency Scanner for Standard Source Type C */
{ string     szTxt, szTmp, szFile;
  int        nLen, nI;
  Scn_T      pScn;
  Scn_Stream pStream;

  Scn_get_cdps(&pScn);
  pStream = Stream_file(pScn, "", szSrcPath, "");
  Stream_defEofId(pStream, -1);
  Stream_defErrId(pStream,  0);
  Stream_defTokId(pStream, "Include",  1);
  Stream_defTokId(pStream, "Library",  2);
  Stream_defTokId(pStream, "Resource", 3);
  Stream_defTokId(pStream, "Program",  4);

  *pbRoot = False;
  for(Stream_next(pStream); Stream_ctid(pStream) >= 0; Stream_next(pStream))
  {
    szTxt = symbolToString(Stream_csym(pStream));
    if (Stream_ctid(pStream) == 1 && Stream_ccol(pStream) == 1)
    { 
      szTmp = strstr(szTxt,"\"");
      if( szTmp != (string)NULL )
      {
        szTmp += 1;
        nLen = strlen(szTmp);
        for( nI=nLen-1; nI >=0; --nI ) if( szTmp[nI] == '"' ) break;
      }
      else
      {
        szTmp = strstr(szTxt,"<");
        if( szTmp != (string)NULL )
        {
          szTmp += 1;
          nLen = strlen(szTmp);
          for( nI=nLen-1; nI >=0; --nI ) if( szTmp[nI] == '>' ) break;
        }
      }
      if( szTmp != (string)NULL )
      {
        szFile = SubStrCopy(szTmp,nI);
        (*pAddDepFun)(pDepFiles,szFile);
        FreeMem(szFile);
      }
    }
    else
    if (Stream_ctid(pStream) == 2)
    { 
      nLen   = strlen(szTxt);
      szFile = SubStrCopy(szTxt+7,nLen-9);
      (*pAddDepFun)(pDepFiles,szFile);
      FreeMem(szFile);
    }
    else
    if (Stream_ctid(pStream) == 3)
    { 
      nLen   = strlen(szTxt);
      szFile = SubStrCopy(szTxt+7,nLen-9);
      (*pAddDepFun)(pDepFiles,szFile);
      FreeMem(szFile);
    }
    else
    if (Stream_ctid(pStream) == 4) *pbRoot = True;
  }

  Stream_close(pStream);
  Stream_free(pStream);
  Scn_free(pScn);
}

/* -------------------------- Pass 1 -------------------------------------- */

static void PRJ_addMacro(GLS_Tok pMacNam, cprjMacDfn pMacDfn)
/* add macro definition ( override previous definition ) */
{ cprjRelOp pRelOp;
  GLS_Tok  pMacVal1, pMacVal2, pName1, pName2;
  string   szName1, szName2;
  symbol   pVal = (symbol)NULL;
  if( cprjMacDfn_val(pMacDfn,&pMacVal1) )
  {
    pVal = PRJ_ValueToSymbol(pMacVal1);
  }
  else
  {
    assert0
    (
      cprjMacDfn_cond(pMacDfn,&pName1,&pRelOp,&pName2,&pMacVal1,&pMacVal2),""
    );
    szName1 = PRJ_expandName(symbolToString(GLS_Tok_symbol(pName1)));
    szName2 = PRJ_expandName(symbolToString(GLS_Tok_symbol(pName2)));
    if( szName1 != (string)NULL && szName2 != (string)NULL )
    { bool bCond = False;
      if( cprjRelOp_eq(pRelOp) )
        bCond = ( ! strcmp(szName1,szName2) );
      else
      if( cprjRelOp_ne(pRelOp) )
        bCond = strcmp(szName1,szName2);
      else
      if( cprjRelOp_le(pRelOp) )
        bCond = ( strcmp(szName1,szName2) < 0 );
      else
      if( cprjRelOp_lt(pRelOp) )
        bCond = ( strcmp(szName1,szName2) <= 0 );
      else
      if( cprjRelOp_ge(pRelOp) )
        bCond = ( strcmp(szName1,szName2) > 0 );
      else
      if( cprjRelOp_gt(pRelOp) )
        bCond = ( strcmp(szName1,szName2) >= 0 );
      else C_BUG;
      pVal = PRJ_ValueToSymbol(bCond?pMacVal1:pMacVal2);
    }
    else
      PT_error
      (
        pMacDfn,"condition specification:\n   %s\n   %s",
        symbolToString(GLS_Tok_symbol(pName1)),
        symbolToString(GLS_Tok_symbol(pName2))
      );
    if( szName1 != (string)NULL ) FreeMem(szName1);
    if( szName2 != (string)NULL ) FreeMem(szName2);
  }
  MAP_ovrdom(pMacMap,GLS_Tok_symbol(pMacNam),pVal);
}

static void PRJ_execCommand(GLS_Tok pCmdVal)
/* exec command ( prepocessing, e.g. ctoh ) */
{ symbol pVal = PRJ_ValueToSymbol(pCmdVal);
  if( pVal != (symbol)NULL && strlen(symbolToString(pVal)) > 0 )
  //{ int res = runprg(symbolToString(pVal),STD_CMD_WAIT);
  { int res = system(symbolToString(pVal));
    if( res != 0 )
    {
      fprintf
      (
        STDERR,"'prdps' aborted due to error code (%s:%d).\n",
        symbolToString(pVal), res
      );
      exit(1);
    }
  }
}

static void PRJ_addCommand
            (
              PRJ_Environ pEnviron, GLS_Tok pTypNam, GLS_Tok pCmdVal
            )
/* add command definition */
{ ROW(symbol) pCmds;
  symbol      pVal;
  if( ! MAP_defined(pEnviron->pTypCmd,GLS_Tok_symbol(pTypNam)) )
  { 
    pCmds = OT_CREATE_ADT(symbol);
    MAP_dfndom(pEnviron->pTypCmd,GLS_Tok_symbol(pTypNam),pCmds);
  }
  else
    pCmds = MAP_apply(ROW(symbol),pEnviron->pTypCmd,GLS_Tok_symbol(pTypNam));
  pVal = PRJ_ValueToSymbol(pCmdVal);
  OT_PUSH(pVal,pCmds);
}

static void PRJ_addParameter
            (
              PRJ_Environ pEnviron, GLS_Tok pTypNam, 
              GLS_Tok pParNam, GLS_Tok pParVal
            )
/* add command parameter definition */
{ MAP(symbol,symbol) pPars;
  if( ! MAP_defined(pEnviron->pCmdPar,GLS_Tok_symbol(pTypNam)) )
  { 
    pPars = MAP_newPrimMap();
    MAP_dfndom(pEnviron->pCmdPar,GLS_Tok_symbol(pTypNam),pPars);
  }
  else
    pPars = MAP_apply
            (
              MAP(symbol,symbol),pEnviron->pCmdPar,GLS_Tok_symbol(pTypNam)
            );
  MAP_ovrdom(pPars,GLS_Tok_symbol(pParNam),PRJ_ValueToSymbol(pParVal));
}

static void PRJ_addPrjDirectories(PRJ_Environ pEnviron, GLS_Tok pPrjDir)
/* add project directories */
{ 
  if( pEnviron->pPrjDir == (symbol)NULL )
  {
    pEnviron->pPrjDir = PRJ_NameToSymbol(pPrjDir);
  }
  else PT_error(pPrjDir,"project directory already defined");
}

static void PRJ_addDstDirectories(PRJ_Environ pEnviron, GLS_Tok pDstDir)
/* add target directories */
{ 
  if( pEnviron->pDstDir == (symbol)NULL )
  {
    pEnviron->pDstDir = PRJ_NameToSymbol(pDstDir);
  }
  else PT_error(pDstDir,"target directory/ies already defined");
}

static void PRJ_addObjDirectories(PRJ_Environ pEnviron, GLS_Tok pObjDir)
/* add object directories */
{ 
  if( pEnviron->pObjDir == (symbol)NULL )
  {
    pEnviron->pObjDir = PRJ_NameToSymbol(pObjDir);
  }
  else PT_error(pObjDir,"object directory already defined");
}

static void PRJ_addRepository
            (
              PRJ_Environ pEnviron, GLS_Tok pDpsLib
            )
/* add type repository */
{ 
  if( pEnviron->pDpsLib == (symbol)NULL )
  {
    pEnviron->pDpsLib = PRJ_NameToSymbol(pDpsLib);
  }
  else PT_error(pDpsLib,"type repository already defined");
}

static void PRJ_addExtDirectories
            (
              PRJ_Environ pEnviron, GLS_Tok pPathes, bool bOptional
            )
/* add external include and library directories */
{ PIT pItr; string szPath, szPathes; symbol pPath;
  szPathes = PRJ_expandName(symbolToString(GLS_Tok_symbol(pPathes)));
  if( szPathes != (string)NULL )
  {
    pItr = PIT_make(szPathes); 
    PRJ_setPathSep(szPathes,pItr);
    while( ( szPath = PIT_read(pItr) ) != NULL )
    { 
      pPath = stringToSymbol(szPath);
      HS_SET_ELM(pPath,pEnviron->pExtDir); 
      if( bOptional )
        if( ! MAP_defined(pEnviron->pOExtDir,pPath) )
          MAP_dfndom(pEnviron->pOExtDir,pPath,pPathes); 
    }
    PIT_drop(pItr); FreeMem(szPathes);
  }
  else
    PT_error
    (
      pPathes,"path specification: %s",symbolToString(GLS_Tok_symbol(pPathes))
    );
}

static void PRJ_addLibraries(PRJ_Environ pEnviron, GLS_Tok pPathes)
/* add ( external ) libraries */
{ PIT pItr; string szPath, szPathes;
  szPathes = PRJ_expandName(symbolToString(GLS_Tok_symbol(pPathes)));
  if( szPathes != (string)NULL )
  {
    pItr = PIT_make(szPathes);
    PRJ_setPathSep(szPathes,pItr);
    while( ( szPath = PIT_read(pItr) ) != NULL )
    { symbol pLib = stringToSymbol(szPath), 
             pDir = (symbol)NULL, pElm;
      HS_Itr pItr; 
      HS_FORALL(pElm,pItr,pEnviron->pExtDir)
      {
        if( IsDirEntry(szPath,symbolToString(pElm)) )
        {
          pDir = pElm; HS_DROP_ITR(pItr); break;
        }
      }
      if( pDir == (symbol)NULL && pEnviron != pProject->pStdEnv )
      {
        HS_FORALL(pElm,pItr,pProject->pStdEnv->pExtDir)
        {
          if( IsDirEntry(szPath,symbolToString(pElm)) )
          {
            pDir = pElm; HS_DROP_ITR(pItr); break;
          }
        }
      }
      // pDir = NULL --> internal Library
      if( pDir == (symbol)NULL || ! MAP_defined(pEnviron->pOExtDir,pDir) )
        MAP_dfndom(pEnviron->pExtLib,pLib,pDir);
      else
        MAP_dfndom(pEnviron->pOExtLib,pLib,pDir);
    }
    PIT_drop(pItr); FreeMem(szPathes);
  }
  else
    PT_error
    (
      pPathes,"path specification: %s",symbolToString(GLS_Tok_symbol(pPathes))
    );
}

static void PRJ_addType(cprjTypDfn pTypDfn)
/* add source / target type */
{ GLS_Tok pName, pSuffixes = (symbol)NULL, pSuffix;
  assert0
  ( 
    cprjTypDfn_one(pTypDfn,&pName) || 
    cprjTypDfn_two(pTypDfn,&pName,&pSuffixes),""
  );
  if( ! MAP_defined(pProject->pTypDfn,GLS_Tok_symbol(pName)) )
  { PRJ_Type pType = PRJ_newType();
    MAP_dfndom(pProject->pTypDfn,GLS_Tok_symbol(pName),pType);
    if( pSuffixes != (symbol)NULL )
    { PIT pItr1, pItr2; int nGroup = 0;
      string szSuffix, szSuffixes, szSfxGroups;
      szSfxGroups = PRJ_expandName(symbolToString(GLS_Tok_symbol(pSuffixes)));
      if( szSfxGroups != (string)NULL )
      {
        pItr1 = PIT_make(szSfxGroups); PIT_sep(pItr1,";");
        while( ( szSuffixes = PIT_read(pItr1) ) != NULL )
        {
          ++nGroup;
          if( strlen(szSuffixes) > 0 )
          {
            if( nGroup < 3 )
            { SET(symbol) pSet = ( nGroup == 1 ) 
                                 ? pType->pTypSfx : pType->pIncSfx;
              pItr2 = PIT_make(szSuffixes); PIT_sep(pItr2,".");
              while( ( szSuffix = PIT_read(pItr2) ) != NULL )
              {
                pSuffix = stringToSymbol(szSuffix);
                if( pType->pFstSfx == (symbol)NULL )
                  pType->pFstSfx = pSuffix;
                HS_SET_ELM(pSuffix,pSet);
                if( *szSuffix == '&' )
                {
                  if( pSet != pType->pIncSfx )
                    PT_error
                    (
                      pSuffixes,
                      " type references only in include section: %s",szSuffix
                    );
                  else
                  if( ! MAP_defined(
                          pProject->pTypDfn,stringToSymbol(szSuffix+1)) )
                    PT_error(pSuffixes, "type '%s' not found",szSuffix+1);
                }
              }
              PIT_drop(pItr2);
            }
            else
            if( nGroup == 3 )
              pType->pObjSfx = stringToSymbol(szSuffixes);
          }
        }
        if( nGroup > 3 )
          PT_error
          (
            pSuffixes,"too many groups in suffix specification: %s",szSfxGroups
          );
        PIT_drop(pItr1); FreeMem(szSfxGroups);
      }
      else 
        PT_error
        (
          pSuffixes,"suffix specification: %s",
          symbolToString(GLS_Tok_symbol(pSuffixes))
        );
    }
  }
  else
    PT_error
    (
      pName,"type %s already defined", symbolToString(GLS_Tok_symbol(pName))
    );
}

static bool PRJ_addRuleDepRule(PRJ_Rule pRule, string szDepExp)
/* add dependant rule */
{ bool        bResult   = False;
  string      szDepExpPart;
  symbol      pDepRuleSym;
  SET(symbol) pSuffixes = (SET(symbol))NULL;
  PIT         pItr; 
  pItr = PIT_make(szDepExp); PIT_sep(pItr,".");
  while( ( szDepExpPart = PIT_read(pItr) ) != NULL )
  { 
    if( bResult == False )
    { 
      pDepRuleSym = stringToSymbol(szDepExpPart);
      if( MAP_defined(pRuleMap,pDepRuleSym) ) 
      { PRJ_Rule pDepRule = MAP_apply(PRJ_Rule,pRuleMap,pDepRuleSym);
        bResult = True;
        if( ! PRJ_IsTargetByRoot(pDepRule->pDstDfn)   &&
            ! PRJ_IsExternalTarget(pDepRule->pDstDfn)  ) 
        {
          if( ! MAP_defined(pRule->pDepDfn,pDepRuleSym) ) 
          {
            pSuffixes = HS_CREATE_ADTSET(symbol);
            MAP_dfndom(pRule->pDepDfn,pDepRuleSym,pSuffixes);
            HS_SET_ELM(pDepRuleSym,pRule->pNeeds);
            OT_PUSH(pDepRuleSym,pRule->pDepRow);
          }
          else pSuffixes = MAP_apply(SET(symbol),pRule->pDepDfn,pDepRuleSym);
        }
        else
        {
          PT_error
          (
            pRule->pDstDfn,"rule %s not allowed as dependant",
            symbolToString(pDepRule->pName)
          );
          break;
        }
      }
      else break;
    }
    else HS_SET_ELM(stringToSymbol(szDepExpPart),pSuffixes);
  }
  PIT_drop(pItr);
  return bResult;
}

static void PRJ_addRuleDepDfn(PRJ_Rule pRule, GLS_Tok pDepPathes)
/* add rule dependants */
{ PIT    pItr; 
  string szPath, szPathes, szPathDir, szPat1, szPat2, szPat, szDir, szTmp;
  szPathes = PRJ_expandName(symbolToString(GLS_Tok_symbol(pDepPathes)));
  if( szPathes != (string)NULL )
  {
    pItr = PIT_make(szPathes); 
    PRJ_setPathSep(szPathes,pItr);
    while( ( szPath = PIT_read(pItr) ) != NULL )
    {
      if( ! PRJ_addRuleDepRule(pRule,szPath) )
      { 
        if( PRJ_getPathPattern(szPath,&szPathDir,&szPat1) )
        /*
           Beispiel:
           e:\sp_entw\lvdb&&&& |-->
           Verzeichnisse e:\sp_entw\lvdb???? und
           Quelldateien  ????&&&&.<Suffix>
           Im Pattern fÅr Quell-Verzeichnisse und -dateien ist nur '&' erlaubt.
           Im Pattern fÅr Quell-Verzeichnisse sind '*' und '?' erlaubt.
           Im Pfad der Quell-Verzeichnisse sind keine Pattern-Zeichen erlaubt.
        */
        { DII pDItr; 
          szPat2 = PRJ_convPathPattern(szPat1);
          szPat  = ( szPat2 == (string)NULL ) ? szPat1 : szPat2;
          if( PRJ_IsTargetByDirectory(pRule->pDstDfn) || 
              szPat2 == (string)NULL                   )
          {
            DII_FORALL(pDItr,szPathDir,szPat)
            {
              if( DII_isDir(pDItr) )
              { symbol pPath;
                szDir = DII_get_file(pDItr);
                szTmp = MkPath(szPathDir,szDir,"",'d');
                pPath = stringToSymbol(szTmp);
                HS_SET_ELM(pPath,pRule->pSrcDir);
                if( szPat2 != (string)NULL )
                  MAP_dfndom(pRule->pSrcPat,pPath,stringToSymbol(szPat1));
                FreeMem(szDir); FreeMem(szTmp);
              }
            }
          }
          else 
            PT_error(pRule->pDstDfn,"source mask implies rule by directory");
          FreeMem(szPathDir); FreeMem(szPat1);
          if( szPat2 != (string)NULL ) FreeMem(szPat2);
        }
        else HS_SET_ELM(stringToSymbol(szPath),pRule->pSrcDir);
      }
    }
    PIT_drop(pItr); FreeMem(szPathes);
  }
  else
    PT_error
    (
      pDepPathes,"path specification: %s",
      symbolToString(GLS_Tok_symbol(pDepPathes))
    );
}

/*forward*/ static void PRJ_eval
                        (
                          PLR_Tab pPlr, Scn_T pScn, 
                          cprjProject pPrjDfn, PRJ_Environ pEnviron
                        );

static void PRJ_addRule(cprjProject pRuleDfn)
/* add build rule */
{ GLS_Tok      pRuleID, pSrcTyp, pDstTyp, pDepPathes;
  cprjProject  pEnvDfn;
  cprjRuleAttr pRuleAttr;
  cprjDstDfn   pDstDfn;
  cprjSrcDfn   pSrcDfn;
  symbol       pRuleSym;
  assert0
  (
    cprjProject_rule
    (
      pRuleDfn,&pRuleID,&pRuleAttr,&pDstDfn,&pEnvDfn,&pSrcTyp,&pSrcDfn,_
    ), ""
  );
  pDepPathes = PRJ_getSrcPathes(pSrcDfn);
  pRuleSym   = GLS_Tok_symbol(pRuleID);
  if( ! MAP_defined(pRuleMap,pRuleSym) )
  { PRJ_Rule pRule = PRJ_newRule();
    PRJ_eval((PLR_Tab)NULL,(Scn_T)NULL,pEnvDfn,pRule->pRuleEnv);
    PRJ_unionEnviron(pRule->pRuleEnv,pProject->pStdEnv);
    pRule->pName   = pRuleSym;
    pRule->pAttr   = pRuleAttr;
    pRule->pSrcTyp = GLS_Tok_symbol(pSrcTyp);
    if( ! MAP_defined(pProject->pTypDfn,pRule->pSrcTyp) )
      PT_error(pSrcTyp,"unknown type %s",symbolToString(pRule->pSrcTyp));
    pRule->pDstDfn = pDstDfn;
    pRule->pSrcDfn = pSrcDfn;
    if( PRJ_IsInternalTarget(pRule->pDstDfn,&pDstTyp)            &&
        ! MAP_defined(pProject->pTypDfn,GLS_Tok_symbol(pDstTyp))  )
      PT_error
      (
        pDstDfn,"unknown type %s",symbolToString(GLS_Tok_symbol(pDstTyp))
      );
    MAP_dfndom(pRuleMap,pRuleSym,pRule);
    PRJ_addRuleDepDfn(pRule,pDepPathes);
  }
  else
    PT_error(pRuleID,"rule %s already defined",symbolToString(pRuleSym));
}

/*forward*/ static void PRJ_parse
                        (
                          PLR_Tab pPlr, Scn_T pScn, string szFile,
                          PRJ_Environ pEnviron
                        );

static void PRJ_addProjects
            (
              PLR_Tab pPlr, Scn_T pScn, GLS_Tok pPathes,
              PRJ_Environ pEnviron
            )
/* parse dependant project defintions */
{ PIT pItr; string szPath, szPathes;
  szPathes = PRJ_expandName(GLS_Tok_string(pPathes));
  if( szPathes != (string)NULL )
  { 
    pItr = PIT_make(szPathes);
    PRJ_setPathSep(szPathes,pItr);
    while( ( szPath = PIT_read(pItr) ) != NULL )
    {
      PRJ_parse(pPlr,pScn,szPath,pEnviron);
    }
    PIT_drop(pItr); FreeMem(szPathes);
  }
  else 
    PT_error
    (
      pPathes,"path specification: %s",GLS_Tok_string(pPathes)
    );
}

static void PRJ_eval
            (
              PLR_Tab pPlr, Scn_T pScn, cprjProject pPrjDfn, 
              PRJ_Environ pEnviron
            )
/* eval project definition */
{ 
  while( True )
  { cprjProject pPrjDfn_aux;
    GLS_Tok     pNam, pNam2, pVal, pPath1;
    cprjTypDfn  pTypDfn;
    cprjMacDfn  pMacDfn;
    if( cprjProject_inc(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addProjects(pPlr,pScn,pPath1,pEnviron);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_mac(pPrjDfn,&pNam,&pMacDfn,&pPrjDfn_aux) )
    {
      PRJ_addMacro(pNam,pMacDfn);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_typ(pPrjDfn,&pTypDfn,&pPrjDfn_aux) )
    {
      PRJ_addType(pTypDfn);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_res(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addRepository(pEnviron,pPath1);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_dprj(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addPrjDirectories(pEnviron,pPath1);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_ddst(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addDstDirectories(pEnviron,pPath1);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_dobj(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addObjDirectories(pEnviron,pPath1);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_lib(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addLibraries(pEnviron,pPath1);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_ext(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addExtDirectories(pEnviron,pPath1,False);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_oext(pPrjDfn,&pPath1,&pPrjDfn_aux) )
    {
      PRJ_addExtDirectories(pEnviron,pPath1,True);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_cmd(pPrjDfn,&pNam,&pVal,&pPrjDfn_aux) )
    {
      PRJ_addCommand(pEnviron,pNam,pVal);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_par(pPrjDfn,&pNam,&pNam2,&pVal,&pPrjDfn_aux) )
    {
      PRJ_addParameter(pEnviron,pNam,pNam2,pVal);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_exec(pPrjDfn,&pVal,&pPrjDfn_aux) )
    {
      PRJ_execCommand(pVal);
      pPrjDfn = pPrjDfn_aux;
    }
    else
    if( cprjProject_rule(pPrjDfn,_,_,_,_,_,_,&pPrjDfn_aux) )
    {
      PRJ_addRule(pPrjDfn);
      pPrjDfn = pPrjDfn_aux;
    }
    else 
    {
      assert0(cprjProject_nul(pPrjDfn),"");
      break;
    }
  }
}

static void PRJ_parse
            (
              PLR_Tab pPlr, Scn_T pScn, string szFile, PRJ_Environ pEnviron
            )
/* parse project definition */
{ Scn_Stream pCStream; 
  PT_Cfg     pPCfg; 
  PT_Term    pRes   = (PT_Term)NULL; 
  string     szPath = MkPath("PRDPS",szFile,"",'p');
  symbol     pFile  = stringToSymbol(szFile);
  if( IsPath(szPath) && ! MAP_defined(pPrjMap,pFile) )
  {
    pCStream = Stream_file(pScn,"",szPath,"");
    Stream_premac_set(pCStream, SPP_premac);
    Stream_add_ctxval(pCStream,SPP_premac,pPP);
    pPCfg    = PT_init(pPlr,pCStream);
    pRes     = PT_PARSE(pPCfg,"ProjectDfn");
    PT_setErrorCnt(PT_errorCnt() + PT_synErrorCnt(pPCfg));
    if( pRes != (PT_Term)NULL )
      MAP_dfndom(pPrjMap,pFile,pRes);
    if( PT_synErrorCnt(pPCfg) == 0 )
    { cprjProjectDfn pPrjDfn;
      cprjProject    pPrj;
      assert0
      (
        cprj_Start_ProjectDfn(pRes,&pPrjDfn) &&
        cprjProjectDfn_root(pPrjDfn,&pPrj),""
      );
      PRJ_eval(pPlr,pScn,pPrj,pEnviron);
      lMaxPrjModTime = MAX(lMaxPrjModTime,PathMTime(szPath));
    }
    PT_quit(pPCfg);
    Stream_close(pCStream);
    Stream_free(pCStream);
  }
  else
  if( ! MAP_defined(pPrjMap,pFile) )
  {
    fprintf(STDERR,"project file %s not found\n",szFile);
    PT_setErrorCnt(PT_errorCnt() + 1);
  }
  FreeMem(szPath);
}

static void PRJ_checkStdEnv(void)
/* check existence of standard environment directories */
{
  if( pProject->pStdEnv->pPrjDir == (symbol)NULL ||
      pProject->pStdEnv->pDstDir == (symbol)NULL ||
      pProject->pStdEnv->pObjDir == (symbol)NULL  )
  {
    fprintf(STDERR,"missing standard environment directories\n");
    PT_setErrorCnt(PT_errorCnt() + 1);
  }
}

/* -------------------------- Pass 2 -------------------------------------- */

static void PRJ_printSourceChanges
            (
              string szSrcFile, SET(symbol) pDepDfn, SET(symbol) pPrevDepDfn
            )
/* print source changes - according environment setting */
{ HS_Itr pItr;
  symbol pDepSym;
  fprintf(STDOUT,": %s\n",szSrcFile);
  HS_FORALL(pDepSym,pItr,pDepDfn)
  {
    if( pPrevDepDfn == (SET(symbol))NULL || 
        ! HS_MBR_ELM(pDepSym,pPrevDepDfn) )
      fprintf(STDOUT,"  > %s\n",symbolToString(pDepSym));
  }
  if( pPrevDepDfn != (SET(symbol))NULL )
  {
    HS_FORALL(pDepSym,pItr,pPrevDepDfn)
    {
      if( ! HS_MBR_ELM(pDepSym,pDepDfn) )
        fprintf(STDOUT,"  - %s\n",symbolToString(pDepSym));
    }
  } 
}

static void PRJ_addSourceNeeds(PRJ_Rule pRule, PRJ_Source pSource)
/* add and synchronize direct dependencies as source needs */
{ HS_Itr pItr;
  symbol pDep, pDepFile;
  string szDep, szDepFile, szDepBase, szDepPath, szDepSfx;
  HS_FORALL(pDep,pItr,pSource->pDepDfn) 
  {
    if( MAP_defined(pSrcMap,pDep) || MAP_defined(pDstMap,pDep) )
    {
      HS_SET_ELM(pDep,pSource->pNeeds);
    }
    else
    {
      szDep     = symbolToString(pDep);
      szDepBase = BaseFile(szDep);
      szDepSfx  = FileSuffix(szDep); 
      szDepPath = FilePrefix(szDep);
      szDepFile = Str_printf("%s%s",szDepBase,szDepSfx);
      pDepFile  = stringToSymbol(szDepFile);
      if( MAP_defined(pSrcMap,pDepFile) )
      { PRJ_Source pSrc = MAP_apply(PRJ_Source,pSrcMap,pDepFile);
        if( strlen(szDepPath) == 0 || 
            stringToSymbol(szDepPath) == pSrc->pPath )
        {
          HS_SET_ELM(pDepFile,pSource->pNeeds);
        }
      }
      if( ! HS_MBR_ELM(pDepFile,pSource->pNeeds) && 
          MAP_defined(pDstMap,pDepFile) )
      { PRJ_Target pDst = MAP_apply(PRJ_Target,pDstMap,pDepFile);
        if( strlen(szDepPath) == 0 || 
            stringToSymbol(szDepPath) == pDst->pPath )
        {
          HS_SET_ELM(pDepFile,pSource->pNeeds);
        }
      }
      if( ! HS_MBR_ELM(pDepFile,pSource->pNeeds) ) 
      {
        HS_SET_ELM(pDep,pSource->pNeeds);
      }
      FreeMem(szDepBase);
      FreeMem(szDepFile);
      FreeMem(szDepPath);
      FreeMem(szDepSfx);
    }
  }
  HS_DROP_SET(pSource->pDepDfn);
  pSource->pDepDfn = HS_COPY(pSource->pNeeds);
}

static void PRJ_addSource
            (
              PRJ_Rule pRule, symbol pRefTyp, 
              string szSrcPath, string szSrcFile
            )
/* add source */
{ string szFile   = MkPath(szSrcPath, szSrcFile, "", 'd'), 
         szSuffix = FileSuffix(szFile), 
         szExt    = szSuffix + (*szSuffix=='.'),
         szParseFun;
  symbol pSrcFile = stringToSymbol(szSrcFile), pParseFun;
  if( ! MAP_defined(pSrcMap,pSrcFile) )
  { long       lTime       = PathMTime(szFile);
    PRJ_Source pPrevSource = (PRJ_Source)NULL, pSource;
    PRJ_Type   pSrcTyp     = MAP_apply(PRJ_Type,pProject->pTypDfn,pRefTyp);
    if( ! MAP_defined(pPrevSrcMap,pSrcFile) || 
        ( pSource = pPrevSource = 
          MAP_apply(PRJ_Source,pPrevSrcMap,pSrcFile) )->lTime < lTime )
    { PFN_Dps pFun = (StdCPtr)NULL;
      pSource          = PRJ_newSource();
      pSource->pPath   = stringToSymbol(szSrcPath);
      pSource->pFile   = pSrcFile;
      pSource->pType   = pRefTyp;
      pSource->lTime   = lTime;
      pSource->bRoot   = False;
      pSource->pPrefix = PRJ_getSourcePrefix(pRule->pDstDfn);
      if( pSrcTyp->pObjSfx != stringToSymbol(szExt) )
      {
        szParseFun = Str_printf("%s_parse",symbolToString(pRefTyp));
        pParseFun  = stringToSymbol(szParseFun);
        if( pRule->pRuleEnv->pDpsLib != (symbol)NULL )
          pFun = (PFN_Dps)Glo_load(pRule->pRuleEnv->pDpsLib,pParseFun,True);
        if( pFun == (PFN_Dps)NULL && MAP_defined(pDpsLib,pRefTyp) )
          pFun = MAP_apply(PFN_Dps,pDpsLib,pRefTyp);
        if( pFun != (PFN_Dps)NULL )
        { 
          (*pFun)(szFile,pSource->pDepDfn,PRJ_addSrc,&pSource->bRoot);
          if( CTX_CHANGES )
            PRJ_printSourceChanges
            (
              szSrcFile,pSource->pDepDfn,
              ( pPrevSource != (PRJ_Source)NULL ) 
              ? pPrevSource->pDepDfn : (SET(symbol))NULL
            );
        }
        FreeMem(szParseFun);
      }
    } 
    MAP_dfndom(pSrcMap,pSrcFile,pSource);
    PRJ_addSourceNeeds(pRule,pSource);
  }
  else
  {
    if( stringToSymbol(szSrcPath) != 
        MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pPath )
      PT_error
      (
        pRule->pDstDfn,
        "source %s exists in more than one directory ( %s, %s )",
        szSrcFile,
        symbolToString(MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pPath),
        szSrcPath
      );
    if( pRefTyp != MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pType )
      PT_error
      (
        pRule->pDstDfn,
        "source %s: type re-definition ( %s, %s )",
        szSrcFile,
        symbolToString(MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pType),
        symbolToString(pRefTyp)
      );
    if( PRJ_getSourcePrefix(pRule->pDstDfn) != 
	MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pPrefix )
      PT_error
      (
        pRule->pDstDfn,
        "source %s: prefix re-definition ( %s, %s )",
        szSrcFile,
        symbolToString(MAP_apply(PRJ_Source,pSrcMap,pSrcFile)->pPrefix),
        symbolToString(PRJ_getSourcePrefix(pRule->pDstDfn))
      );
  }
  FreeMem(szFile); FreeMem(szSuffix);
}

static bool PRJ_equalTargets
            (
              PRJ_Target pTarget, symbol pDstTyp, symbol pFile, symbol pPath,
              symbol pPrevFile, SET(symbol) pSources
            )
/* compare new target with defined target */
{
  if( pTarget->pPath != pPath   ) return False;
  if( pTarget->pType != pDstTyp ) return False;
  if( ( pSources == (SET(symbol))NULL            && 
        pTarget->pSources != (SET(symbol))NULL ) ||
      ( pSources != (SET(symbol))NULL            && 
        pTarget->pSources == (SET(symbol))NULL ) ||
      ( pSources != (SET(symbol))NULL            && 
        pTarget->pSources != (SET(symbol))NULL   &&
        ! HS_EQUAL(pTarget->pSources,pSources) )  ) return False;
  if( pPrevFile == (symbol)NULL      && 
      pTarget->pRoot != (symbol)NULL  ) return False;
  if( pPrevFile != (symbol)NULL )
  {
    if( ! MAP_defined(pDstMap,pPrevFile) ) return False;
    if( MAP_apply(PRJ_Target,pDstMap,pPrevFile)->pNext != pFile ) 
      return False;
  }
  return True;
}

static void PRJ_addTarget
            (
              PRJ_Rule pRule, symbol pDstTyp, symbol pFile, symbol pPath,
              symbol pPrevFile, SET(symbol) pSources
            )
/* add target */
{ 
  if( ! MAP_defined(pDstMap,pFile) )
  { PRJ_Target pTarget = ( pPrevFile == (symbol)NULL )
                         ? PRJ_newTarget(pRule,pSources)
                         : PRJ_newTarget(pRule,(SET(symbol))NULL);
    pTarget->pPath = pPath;
    pTarget->pFile = pFile;
    pTarget->pType = pDstTyp;
    if( pPrevFile != (symbol)NULL )
    { PRJ_Target pPrevTarget = MAP_apply(PRJ_Target,pDstMap,pPrevFile);
      pTarget->pRoot = ( pPrevTarget->pRoot == (symbol)NULL )
                       ? pPrevFile : pPrevTarget->pRoot;
      MAP_apply(PRJ_Target,pDstMap,pPrevFile)->pNext = pFile;
    }
    MAP_dfndom(pDstMap,pFile,pTarget);
    HS_SET_ELM(pFile,pRule->pTargets);
  }
  else
  {
    if( ! PRJ_equalTargets(
            MAP_apply(PRJ_Target,pDstMap,pFile),
            pDstTyp,pFile,pPath,pPrevFile,pSources) )
      PT_error
      (
        pRule->pDstDfn, "target %s differently defined", symbolToString(pFile)
      );
    if( pSources != (SET(symbol))NULL ) HS_DROP_SET(pSources);
  }
}

static void PRJ_setRuleSource(symbol pFile, symbol pPath, SET(symbol) pSources)
{
  if( pPath == (symbol)NULL ) HS_SET_ELM(pFile,pSources);
  else
  { string szPath = MkPath(symbolToString(pPath),symbolToString(pFile),"",'d');
    HS_SET_ELM(stringToSymbol(szPath),pSources);
    FreeMem(szPath);
  }
}

static void PRJ_delRuleSource(symbol pFile, symbol pPath, SET(symbol) pSources)
{
  if( pPath == (symbol)NULL ) HS_DEL_ELM(pFile,pSources);
  else
  { string szPath = MkPath(symbolToString(pPath),symbolToString(pFile),"",'d');
    HS_DEL_ELM(stringToSymbol(szPath),pSources);
    FreeMem(szPath);
  }
}

static bool PRJ_mbrRuleSource(symbol pFile, symbol pPath, SET(symbol) pSources)
{
  if( pPath == (symbol)NULL ) return HS_MBR_ELM(pFile,pSources);
  else
  { string szPath  = MkPath(symbolToString(pPath),symbolToString(pFile),"",'d');
    bool   bResult = HS_MBR_ELM(stringToSymbol(szPath),pSources);
    FreeMem(szPath);
    return bResult;
  }
}

static void PRJ_addRuleSources
            (
              PRJ_Rule pRule, string szPath, 
              SET(symbol) pSources, SET(symbol) pSrcDirs, bool bFull
            )
/* add rule sources */
{ DII        pItr; 
  PRJ_Type   pSrcTyp    = MAP_apply(PRJ_Type,pProject->pTypDfn,pRule->pSrcTyp);
  bool       bRecursive = PRJ_IsRecursive(pRule->pSrcDfn), 
             bDirPath   = IsDirPath(szPath);
  Reg_T      pRScn      = PRJ_getRegExp(pRule->pSrcDfn);
  for( pItr = bDirPath?DII_make(szPath,"*",bRecursive,False):(DII)NULL;
       !bDirPath || (DII_empty(pItr)?DII_drop(pItr),False:True); )
  { string szFile  = bDirPath?DII_get_file(pItr):StrCopy(szPath),
           szBase  = bDirPath?DII_get_base(pItr):BaseFile(szFile),
           szDir   = bDirPath?DII_get_path(pItr):FilePrefix(szPath),
           szExt   = bDirPath?DII_get_ext(pItr):FileSuffix(szFile), 
           szAPath = MkPath(szDir,szFile,"",'d'), szTmp;
    symbol pSuffix = stringToSymbol(szExt+(*szExt=='.')), 
           pPath   = bFull?stringToSymbol(szDir):(symbol)NULL, 
           pRefTyp = pRule->pSrcTyp, pTmp;
    if( ( HS_MBR_ELM(pSuffix,pSrcTyp->pTypSfx) ||
          PRJ_IsInclude(pSuffix,pRule->pSrcTyp,pSrcTyp->pIncSfx,&pRefTyp) ||
          pSuffix == pSrcTyp->pObjSfx ) &&
          ( pRScn == (Reg_T)NULL || REG_MATCH(pRScn,szAPath,(long*)NULL) != (string)NULL ) )
    { PRJ_Source pSource;
      HS_SET_ELM(stringToSymbol(szDir),pSrcDirs);
      PRJ_addSource(pRule,pRefTyp,szDir,szFile);
      pSource = MAP_apply(PRJ_Source,pSrcMap,stringToSymbol(szFile));
      if( ! PRJ_IsTargetByRoot(pRule->pDstDfn) || pSource->bRoot )
      { 
        if( pSrcTyp->pObjSfx != (symbol)NULL &&
            pSuffix == pSrcTyp->pObjSfx && pSource->bRoot )
          PT_error(pRule->pDstDfn,"object %s as main source",szFile);
        else
        if( pSrcTyp->pObjSfx != (symbol)NULL && pSuffix == pSrcTyp->pObjSfx )
        { HS_Itr pSItr;
          bool   bSourceFound = False;
          HS_FORALL(pTmp,pSItr,pSrcTyp->pTypSfx)
          {
            szTmp = Str_printf("%s.%s",szBase,symbolToString(pTmp));
            if( PRJ_mbrRuleSource(stringToSymbol(szTmp),pPath,pSources) )
              bSourceFound = True;
            FreeMem(szTmp);            
          }
          if( ! bSourceFound )
            PRJ_setRuleSource(pSource->pFile,pPath,pSources);
        }
        else
        if( HS_MBR_ELM(pSuffix,pSrcTyp->pTypSfx) )
        {
          if( pSrcTyp->pObjSfx != (symbol)NULL )
          {
            szTmp = Str_printf("%s.%s",szBase,symbolToString(pSrcTyp->pObjSfx));
            pTmp  = stringToSymbol(szTmp);
            if( PRJ_mbrRuleSource(pTmp,pPath,pSources) )
              PRJ_delRuleSource(pTmp,pPath,pSources);
            FreeMem(szTmp);            
          }
          PRJ_setRuleSource(pSource->pFile,pPath,pSources);
        }
      }
    }
    FreeMem(szFile); FreeMem(szBase); FreeMem(szExt); 
    FreeMem(szDir); FreeMem(szAPath); 
    if( bDirPath ) DII_next(pItr);
    else break;
  }
  REG_drop(pRScn);
}

static void PRJ_addExternalTarget
            (
              PRJ_Rule pRule, ROW(symbol) pTargets, SET(symbol) pSources
            )
/* add external target */
{ symbol pPrevFile = (symbol)NULL, pFile, pPath;
  long   lCnt      = OT_CNT(pTargets), lI;
  if( lCnt == 0 ) HS_DROP_SET(pSources);
  else
    for( lI=0; lI < lCnt; lI+=2 )
    { SET(symbol) pTmp = ( pPrevFile == (symbol)NULL )
                         ? pSources : (SET(symbol))NULL;
      pFile = OT_GET(string,pTargets,lI);
      pPath = OT_GET(string,pTargets,lI+1);
      PRJ_addTarget(pRule,(symbol)NULL,pFile,pPath,pPrevFile,pTmp);
      pPrevFile = pFile;
    }
}

static void PRJ_addInternalTarget
            (
              PRJ_Rule pRule, string szBase, GLS_Tok pDstTyp, 
              SET(symbol) pSources
            )
/* add internal target */
{ symbol   pDstTypSym = GLS_Tok_symbol(pDstTyp);
  PRJ_Type pType      = MAP_apply(PRJ_Type,pProject->pTypDfn,pDstTypSym);
  symbol   pDstSfx, pFile, pPrefix, pPrevFile = (symbol)NULL;
  string   szFile;
  HS_Itr   pItr;
  pPrefix = PRJ_getTargetPrefix(pRule->pDstDfn);
  if( pType->pFstSfx != (symbol)NULL )
  {
    if( pPrefix != (symbol)NULL )
      szFile = Str_printf("%s%s.%s",symbolToString(pPrefix),szBase,symbolToString(pType->pFstSfx));
    else
      szFile = Str_printf("%s.%s",szBase,symbolToString(pType->pFstSfx));
    pFile  = stringToSymbol(szFile);
    PRJ_addTarget
    (
      pRule,pDstTypSym,pFile,pRule->pRuleEnv->pDstDir,pPrevFile,pSources
    );
    pPrevFile = pFile;
    FreeMem(szFile);
  }
  else // no target suffix
  {
    if( pPrefix != (symbol)NULL )
    {
      szFile = Str_printf("%s%s",symbolToString(pPrefix),szBase);
      pFile  = stringToSymbol(szFile);
    }
    else pFile = stringToSymbol(szBase);
    PRJ_addTarget
    (
      pRule,pDstTypSym,pFile,pRule->pRuleEnv->pDstDir,pPrevFile,pSources
    );
  }
/*
  if( MAP_defined(pDstMap,pFile) &&
      MAP_apply(PRJ_Target,pDstMap,pFile)->pSources != pSources )
    HS_DROP_SET(pSources);
*/
  HS_FORALL(pDstSfx,pItr,pType->pTypSfx)
  {
    if( pDstSfx != pType->pFstSfx )
    {
      if( pPrefix != (symbol)NULL )
        szFile = Str_printf("%s%s.%s",symbolToString(pPrefix),szBase,symbolToString(pDstSfx));
      else
        szFile = Str_printf("%s.%s",szBase,symbolToString(pDstSfx));
      pFile  = stringToSymbol(szFile);
      PRJ_addTarget
      (
        pRule,pDstTypSym,pFile,pRule->pRuleEnv->pDstDir,
        pPrevFile,(SET(symbol))NULL
      );
      pPrevFile = pFile;
      FreeMem(szFile);
    }
  }      
}

static void PRJ_getFilesByMask
            (
              PRJ_Rule pRule, string szPattern, SET(symbol) pSources, 
              MAP(symbol,SET(symbol)) pDstSrcGroups
            )
/* find target / source groups by directory pattern */
{ HS_Itr pItr;
  symbol pSrcSym, pDstBaseSym;
  HS_FORALL(pSrcSym,pItr,pSources)
  { string szDstBase = PRJ_getDstBaseByMask(symbolToString(pSrcSym),szPattern);
    if( szDstBase != (string)NULL )
    { SET(symbol) pSrcSet = (SET(symbol))NULL;
      pDstBaseSym = stringToSymbol(szDstBase);
      if( ! MAP_defined(pDstSrcGroups,pDstBaseSym) )
      {
        pSrcSet = HS_CREATE_ADTSET(symbol);
        MAP_dfndom(pDstSrcGroups,pDstBaseSym,pSrcSet);
      }
      else MAP_apply(SET(symbol),pDstSrcGroups,pDstBaseSym);
      HS_SET_ELM(pSrcSym,pSrcSet);
      FreeMem(szDstBase);
    }
    else
      PT_error
      (
        pRule->pDstDfn,"no match between mask %s and source %s",
        szPattern, symbolToString(pSrcSym)
      );
  }
}

static void PRJ_addRuleTargets(PRJ_Rule pRule)
/* add rule targets */
{ GLS_Tok     pDstTyp, pDstName;
  SET(symbol) pSources, pSrcDirs, pTmp;
  HS_Itr      pItr;
  MAPIT       pGrpItr; 
  symbol      pPath, pBase;
  pSrcDirs = HS_CREATE_ADTSET(symbol);
  if( PRJ_IsInternalTarget(pRule->pDstDfn,&pDstTyp) ) 
                                // interne Ziel/Quell-Bestimmung
  { string szBase;
    if( PRJ_IsTargetByDirectory(pRule->pDstDfn) )
    { 
      HS_FORALL(pPath,pItr,pRule->pSrcDir)
      { 
        pSources = HS_CREATE_ADTSET(symbol);
        PRJ_addRuleSources(pRule,symbolToString(pPath),pSources,pSrcDirs,False);
        if( HS_CARD(pSources) > 0 )
        {
          if( ! MAP_defined(pRule->pSrcPat,pPath) )
          {
            szBase = BaseFile(symbolToString(pPath));
            PRJ_addInternalTarget(pRule,szBase,pDstTyp,pSources);
            FreeMem(szBase);
          }
          else
          { MAP(symbol,SET(symbol)) pDstSrcGroups = MAP_newPrimMap();
            PRJ_getFilesByMask
            (
              pRule,symbolToString(MAP_apply(symbol,pRule->pSrcPat,pPath)),
              pSources,pDstSrcGroups
            );
            MAP_forItrAsg(pBase,pTmp,pGrpItr,pDstSrcGroups)
              PRJ_addInternalTarget(pRule,symbolToString(pBase),pDstTyp,pTmp);
            MAP_freeMap(pDstSrcGroups);
            HS_DROP_SET(pSources);
          }
        }
        else HS_DROP_SET(pSources);
      }
    }
    else
    { 
      pSources = HS_CREATE_ADTSET(symbol);
      HS_FORALL(pPath,pItr,pRule->pSrcDir)
      {
        PRJ_addRuleSources(pRule,symbolToString(pPath),pSources,pSrcDirs,False);
      }
      if( PRJ_IsTargetByName(pRule->pDstDfn,&pDstName) )
      {
        if( HS_CARD(pSources) > 0 )
        {
          szBase = PRJ_expandName(symbolToString(GLS_Tok_symbol(pDstName)));
          PRJ_addInternalTarget(pRule,szBase,pDstTyp,pSources);
          FreeMem(szBase);
        }
        else HS_DROP_SET(pSources);
      }
      else
      {
        HS_FORALL(pPath,pItr,pSources)
        { 
          pTmp = HS_CREATE_ADTSET(symbol);
          HS_SET_ELM(pPath,pTmp);
          szBase = BaseFile(symbolToString(pPath));
          PRJ_addInternalTarget(pRule,szBase,pDstTyp,pTmp);
          FreeMem(szBase);
        }
        HS_DROP_SET(pSources);
      }
    }
  }
  else
  if( PRJ_IsExternalTarget(pRule->pDstDfn) ) 
                            // externe Ziel/Quell-Bestimmung
  { string  szExtFun    = Str_printf
                          (
                            "%s_getFiles",symbolToString(pRule->pSrcTyp)
                          ), 
            szDstPathes = symbolToString(pRule->pRuleEnv->pDstDir), szDstPath;
    PFN_Ext pFun        = (PFN_Ext)NULL;
    if( pRule->pRuleEnv->pDpsLib != (symbol)NULL )
    { 
      pFun = (PFN_Ext)Glo_load
                      (
                        pRule->pRuleEnv->pDpsLib,stringToSymbol(szExtFun),True
                      );
    }
    if( pFun != (PFN_Ext)NULL )
    { MAPTY pGrpMapTyp = MAP_newTyp
                         (
                           primCopy,OT_delT,primEqual,primHash,
                           primCopy,primFree
                         );
      MAP(ROW(symbol),SET(symbol)) pDstSrcGroups = MAP_newMap(pGrpMapTyp);
      SET(string) pStrSet;
      SET(symbol) pSymSet;
      ROW(string) pStrRow;
      ROW(symbol) pSymRow;
      PIT         pDirItr;
      pSources = HS_CREATE_ADTSET(symbol);
      HS_FORALL(pPath,pItr,pRule->pSrcDir)
      {
        PRJ_addRuleSources(pRule,symbolToString(pPath),pSources,pSrcDirs,True);
      }
      pStrRow = OT_CREATE_ADT(string);
      pDirItr = PIT_make(szDstPathes); 
      PRJ_setPathSep(szDstPathes,pDirItr);
      while( ( szDstPath = PIT_read(pDirItr) ) != NULL )
        OT_PUSH(symbolToString(stringToSymbol(szDstPath)),pStrRow);
      PIT_drop(pDirItr);
      pStrSet = PRJ_SymbolToStringSet((SET(symbol))NULL,pSources);
      (*pFun)(pStrRow,pStrSet,pDstSrcGroups,PRJ_addGrp,PRJ_addDst,PRJ_addSrc);
      HS_DROP_SET(pStrSet);
      OT_DEL_T(pStrRow);
      MAP_forItrAsg(pSymRow,pSymSet,pGrpItr,pDstSrcGroups)
      {
        PRJ_addExternalTarget(pRule,pSymRow,pSymSet);
      }
      MAP_freeMap(pDstSrcGroups);
      MAP_freeTyp(pGrpMapTyp);
      HS_DROP_SET(pSources);
    }
    else PT_error(pRule->pDstDfn,"missing external rule evaluation function");
    FreeMem(szExtFun);
  }
  else C_BUG;
  HS_UNION(pRule->pSrcDir,pRule->pSrcDir,pSrcDirs);
  HS_DROP_SET(pSrcDirs);
}

static long PRJ_DpsLibMain(symbol pFunNam)
/* init/quit necessary dps libraries */
{ long        lRuleCnt = OT_CNT(pRuleRow), 
              lResult  = 0, lI;
  symbol      pRuleSym;
  PRJ_Rule    pRule;
  PFN_DpsLib  pFun;
  SET(symbol) pTmp = HS_CREATE_ADTSET(symbol);
  for( lI=0; lI < lRuleCnt; ++lI )
  { 
    pRuleSym = OT_GET(symbol,pRuleRow,lI);
    pRule    = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym);
    if( pRule->pRuleEnv->pDpsLib != (symbol)NULL    &&
        ! HS_MBR_ELM(pRule->pRuleEnv->pDpsLib,pTmp)  )
    {
      pFun = (PFN_DpsLib)Glo_load(pRule->pRuleEnv->pDpsLib,pFunNam,True);
      if( pFun != (PFN_DpsLib)NULL ) lResult += (*pFun)();
      HS_SET_ELM(pRule->pRuleEnv->pDpsLib,pTmp);
    }
  }
  HS_DROP_SET(pTmp);
  return lResult;
}

static void MinimizeTargetNeeds(void)
{ long lRCnt = 0, lTCnt = 0, lI, lJ;
  lRCnt = OT_CNT(pRuleRow);
  for( lI=0; lI < lRCnt; ++lI )
  { PRJ_Rule pRule;
    PRJ_Type pSrcTyp;
    symbol   pRuleSym, pNeedSym, pObjectSym;
    pRuleSym = OT_GET(symbol,pRuleRow,lI);
    pRule    = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym);
    lTCnt    = OT_CNT(pRule->pDstRow);
    for( lJ=0; lJ < lTCnt; ++lJ )
    { PRJ_Target pTarget, pSubTarget, pObjTarget;
      pTarget = MAP_apply
                (
                  PRJ_Target,pDstMap,OT_GET(symbol,pRule->pDstRow,lJ)
                );
      if( PRJ_IsExecutable(pTarget->pRule->pAttr) )
      { SET(symbol) pNotNeeded = HS_CREATE_ADTSET(symbol);
        HS_Itr      pItr, pItr2;
        HS_FORALL(pNeedSym,pItr,pTarget->pNeeds)
        { 
          if( MAP_defined(pDstMap,pNeedSym) )
          {
            pSubTarget = MAP_apply(PRJ_Target,pDstMap,pNeedSym);
            if( PRJ_IsExecutable(pSubTarget->pRule->pAttr) )
            { 
              HS_FORALL(pObjectSym,pItr2,pSubTarget->pNeeds)
              { 
                if( MAP_defined(pDstMap,pObjectSym) )
                { string szSuffix, szExt;
                  pObjTarget = MAP_apply(PRJ_Target,pDstMap,pObjectSym);
                  pSrcTyp = MAP_apply
                            (
                              PRJ_Type,pProject->pTypDfn,
                              pObjTarget->pRule->pSrcTyp
                            );
                  szSuffix = FileSuffix(symbolToString(pObjTarget->pFile));
                  szExt    = szSuffix + (*szSuffix=='.');
                  if( pSrcTyp->pObjSfx != (symbol)NULL &&
                      stringToSymbol(szExt) == pSrcTyp->pObjSfx )
                  {
                    HS_SET_ELM(pObjectSym,pNotNeeded);
                  }
                  FreeMem(szSuffix);
                }
              }
            }
          }
        }
        pTarget->pNeeds = HS_MINUS(pTarget->pNeeds,pTarget->pNeeds,pNotNeeded);
        HS_DROP_SET(pNotNeeded);
      }
    }
  }
}

static void PRJ_evalRules(void)
/* eval build rules */
{ long     lRuleCnt = 0, lDstCnt, lSrcCnt, lI, lJ, lK;
  symbol   pRuleSym, pDstSym;
  PRJ_Rule pRule;
  PRJ_addRuleNeedsClosure();
  PRJ_sortRules();
  if( PT_errorCnt() == 0 )
  {
    if( PRJ_DpsLibMain(stringToSymbol("DpsLib_init")) != 0 )
    {
      fprintf(STDERR, "Initialisation of Project Libraries failed\n");
      PT_setErrorCnt(PT_errorCnt() + 1);
    }
    if( PT_errorCnt() == 0 )
    {
      lRuleCnt = OT_CNT(pRuleRow);
      for( lI=0; lI < lRuleCnt; ++lI )
      { 
        pRuleSym = OT_GET(symbol,pRuleRow,lI);
        PRJ_addRuleTargets(MAP_apply(PRJ_Rule,pRuleMap,pRuleSym));
      }
    }
    if( PT_errorCnt() == 0 )
    { SET(symbol) pSorted = HS_CREATE_ADTSET(symbol);
      PRJ_addSourceNeedsClosure();
      PRJ_addTargetRootSourceClosure();
      PRJ_addTargetNeeds();
      if( pFP_Diag != (FILE*)NULL )
      {
        fprintf(pFP_Diag,"\n\n\n>>> Sorted Rules:");
      }
      for( lI=0; lI < lRuleCnt; ++lI )
      { 
        pRuleSym = OT_GET(symbol,pRuleRow,lI);
        pRule    = MAP_apply(PRJ_Rule,pRuleMap,pRuleSym);
        if( pFP_Diag != (FILE*)NULL )
        {
          fprintf(pFP_Diag,"\n\n\t%s:",symbolToString(pRuleSym));
        }
        PRJ_sortRuleTargets(pRule);
        lDstCnt = OT_CNT(pRule->pDstRow);
        for( lJ=0; lJ < lDstCnt; ++lJ )
        { PRJ_Target pTarget;  
          pDstSym = OT_GET(PRJ_Target,pRule->pDstRow,lJ);
          pTarget = MAP_apply(PRJ_Target,pDstMap,pDstSym);
          if( pFP_Diag != (FILE*)NULL )
          {
            fprintf(pFP_Diag,"\n\n\t\t%s:",symbolToString(pDstSym));
          }
          PRJ_sortTargetSources(pTarget,pSorted);
          if( pFP_Diag != (FILE*)NULL )
          {
            lSrcCnt = OT_CNT(pTarget->pSrcRow);
            for( lK=0; lK < lSrcCnt; ++lK )
            {
              fprintf
              (
                pFP_Diag,"\n\t\t\t%s",
                symbolToString(OT_GET(symbol,pTarget->pSrcRow,lK))
              );
            }
          }
        }
      }
      HS_DROP_SET(pSorted);
      MinimizeTargetNeeds();
    }
    lDpsLibMemCnt = PRJ_DpsLibMain(stringToSymbol("DpsLib_quit"));
  }
}

/* ----------------------- Generating & Printing -------------------------- */

static bool PRJ_IsReplacePat(string szS, symbol* ppPat, symbol* ppVal)
/* whether 'szS' matches a replace pattern at the beginning */
{ MAPIT  pItr;
  string szP, szT;
  MAP_forItrAsg(*ppPat,*ppVal,pItr,pReplaceMap)
  {
    if( *ppPat != (symbol)NULL )
    {
      szP = symbolToString(*ppPat);
      if( *szP != '\0' )
      {
        szT = strstr(szS,szP);
        if( szT == szS )
        {
          MAP_freeItr(pItr); return True;
        }
      }
    }
  }
  return False;
}

static void PRJ_genPath(FILE* pSysOut, string szTag, string szPath)
/* generate tagged path */
{ symbol pPat = stringToSymbol(""), pVal;
  string szS = szPath;
  fprintf(pSysOut,"%s ",szTag);
  /* external path prefix */
  if( MAP_defined(pReplaceMap,pPat) )
  {
    // treat special start sequence condition
    if( MAP_defined(pReplaceMap,(symbol)NULL) )
    {
      pVal = MAP_apply(symbol,pReplaceMap,(symbol)NULL);
      if( strstr(szS,symbolToString(pVal)) == szS )
      {
        pVal = MAP_apply(symbol,pReplaceMap,pPat);
        fprintf(pSysOut,"%s",symbolToString(pVal));
      }
    }
    else // unconditional
    {
      pVal = MAP_apply(symbol,pReplaceMap,pPat);
      fprintf(pSysOut,"%s",symbolToString(pVal));
    }
  }
  /* path pattern replacement */
  while( *szS != '\0' )
  {
    if( PRJ_IsReplacePat(szS,&pPat,&pVal) )
    {
      fprintf(pSysOut,"%s",symbolToString(pVal));
      szS+=strlen(symbolToString(pPat));
    }
    else
    {
      fprintf(pSysOut,"%c",*szS); ++szS;
    }
  }
  fprintf(pSysOut,"\n");
}

static void PRJ_genNmkCmdPat(FILE* pSysOut, PRJ_Rule pRule, symbol pType)
/* generate command pattern */
{ ROW(symbol) pCmds;
  long        lCnt, lI;
  if( MAP_defined(pRule->pRuleEnv->pTypCmd,pType) )
  {
    pCmds = MAP_apply(ROW(symbol),pRule->pRuleEnv->pTypCmd,pType);
    lCnt = OT_CNT(pCmds);
    if( lCnt > 0 )
    {
      fprintf(pSysOut,"[%s]\n",symbolToString(pType));
      for( lI=0; lI < lCnt; ++lI )
        fprintf(pSysOut,"%s\n",symbolToString(OT_GET(symbol,pCmds,lI)));
      fprintf(pSysOut,"\n");
    }
  }
}

static void PRJ_genNmkCmdEnv(FILE* pSysOut, PRJ_Rule pRule, symbol pType)
/* generate command environment */
{ HS_Itr             pItr;
  MAP(symbol,symbol) pPars;
  symbol             pExtDir, pNam, pVal;
  HS_FORALL(pExtDir,pItr,pRule->pRuleEnv->pExtDir)
    PRJ_genPath(pSysOut,"D", symbolToString(pExtDir));
  if( MAP_defined(pRule->pRuleEnv->pCmdPar,pType) )
  {
    pPars = MAP_apply(MAP(symbol,symbol),pRule->pRuleEnv->pCmdPar,pType);
    MAP_forItrAsg(pNam,pVal,pItr,pPars)
      fprintf(pSysOut,"P %s=%s\n",symbolToString(pNam),symbolToString(pVal));
  }
  fprintf(pSysOut,";%s\n",symbolToString(pType));
}

static void PRJ_genNmkSrcCmd
            (
              FILE* pSysOut, PRJ_Rule pRule, 
              PRJ_Source pSource, PRJ_Type pSrcTyp
            )
/* genearte source command */
{ string szSuffix = FileSuffix(symbolToString(pSource->pFile)),
         szExt    = szSuffix + (*szSuffix=='.'),
         szBase, szPath;
  if( stringToSymbol(szExt) != pSrcTyp->pObjSfx )
  { SET(symbol) pIncSet = PRJ_collectIncludes(pSource);
    symbol      pNeed;
    HS_Itr      pItr;
    szExt  = Str_printf(".%s",symbolToString(pSrcTyp->pObjSfx));
    szBase = BaseFile(symbolToString(pSource->pFile));
    szPath = MkPath
             (
               symbolToString(pRule->pRuleEnv->pObjDir),szBase, szExt,'d'
             );
    fprintf(pSysOut,"\n\n");
    PRJ_genPath(pSysOut,"T", szPath);
    FreeMem(szPath);
    FreeMem(szBase);
    FreeMem(szExt);
    szPath = MkPath
             (
               symbolToString(pSource->pPath),
               symbolToString(pSource->pFile),"",'d'
             );
    PRJ_genPath(pSysOut,"S", szPath);
    FreeMem(szPath);
    HS_FORALL(pNeed,pItr,pIncSet)
    { PRJ_Source pDepSource = MAP_apply(PRJ_Source,pSrcMap,pNeed);
      szPath = MkPath
               (
                 symbolToString(pDepSource->pPath),
                 symbolToString(pDepSource->pFile),"",'d'
               );
      PRJ_genPath(pSysOut,"I", szPath);
      FreeMem(szPath);
    }
    PRJ_genNmkCmdEnv(pSysOut,pRule,pSource->pType);
    HS_DROP_SET(pIncSet);
  }
  FreeMem(szSuffix);
}

static void PRJ_genNmkDstCmd
            (
              FILE* pSysOut, PRJ_Target pTarget, 
              PRJ_Type pDstTyp, PRJ_Type pSrcTyp
            )
/* genearte target command */
{ PRJ_Target pNxtTarget = pTarget, pSubTarget;
  string     szSuffix, szBase, szPath, szExt;
  symbol     pSrcSym, pNeed, pDir;
  HS_Itr     pItr1, pItr2, pItr3;
  MAPIT      pItr4;
  while( pNxtTarget != (PRJ_Target)NULL )
  {
    szPath = MkPath
             (
               symbolToString(pNxtTarget->pPath),
               symbolToString(pNxtTarget->pFile),"",'d'
             );
    fprintf(pSysOut,"%s",pNxtTarget==pTarget?"\n\n":"");
    PRJ_genPath(pSysOut,"T", szPath);
    FreeMem(szPath);
    if( pNxtTarget->pNext != (symbol)NULL )
      pNxtTarget = MAP_apply(PRJ_Target,pDstMap,pNxtTarget->pNext);
    else pNxtTarget = (PRJ_Target)NULL;
  }
  HS_FORALL(pSrcSym,pItr1,pTarget->pSources)
  { PRJ_Source pSource = MAP_apply(PRJ_Source,pSrcMap,pSrcSym), 
               pDepSource;
    if( pSrcTyp->pObjSfx != (symbol)NULL )
    { 
      szExt  = Str_printf(".%s",symbolToString(pSrcTyp->pObjSfx));
      szBase = BaseFile(symbolToString(pSource->pFile));
      szPath = MkPath
               (
                 symbolToString(pTarget->pRule->pRuleEnv->pObjDir),
                 szBase,szExt,'d'
               );
      PRJ_genPath(pSysOut,"S", szPath);
      FreeMem(szBase);
      FreeMem(szPath);
      FreeMem(szExt);
    }
    else
    { SET(symbol) pIncSet = PRJ_collectIncludes(pSource);
      szPath = MkPath
               (
                 symbolToString(pSource->pPath),
                 symbolToString(pSource->pFile),"",'d'
               );
      PRJ_genPath(pSysOut,"S", szPath);
      FreeMem(szPath);
      HS_FORALL(pNeed,pItr2,pIncSet)
      {
        if( ! HS_MBR_ELM(pNeed,pTarget->pSources) )
        {
          pDepSource = MAP_apply(PRJ_Source,pSrcMap,pNeed);
          szPath     = MkPath
                       (
                         symbolToString(pDepSource->pPath),
                         symbolToString(pDepSource->pFile),"",'d'
                       );
          PRJ_genPath(pSysOut,"I", szPath);
          FreeMem(szPath);
        }
      }
      HS_DROP_SET(pIncSet);
    }
  }
  if( PRJ_IsExecutable(pTarget->pRule->pAttr) )
  { SET(symbol) pTmp = HS_CREATE_ADTSET(symbol);
    long        lCnt = OT_CNT(pTarget->pRule->pDepRow), lI;
    PRJ_Type    pSubSrcTyp;
    for( lI=0; lI < lCnt; ++lI ) // ordered rule dependants
    {
      HS_FORALL(pNeed,pItr3,pTarget->pNeeds)
      { 
        pSubTarget = MAP_apply(PRJ_Target,pDstMap,pNeed);
        pSubSrcTyp = MAP_apply(PRJ_Type,pProject->pTypDfn,pSubTarget->pRule->pSrcTyp);
        if( pSubTarget->pRule->pName == 
            OT_GET(symbol,pTarget->pRule->pDepRow,lI) )
        { 
          szSuffix = FileSuffix(symbolToString(pSubTarget->pFile)),
          szExt    = szSuffix + (*szSuffix=='.');
          if( pSubSrcTyp->pObjSfx == (symbol)NULL ||
              stringToSymbol(szExt) != pSubSrcTyp->pObjSfx )
            szPath = MkPath
                     (
                       symbolToString(pSubTarget->pPath),
                       symbolToString(pSubTarget->pFile),"",'d'
                     );
          else
            szPath = MkPath
                     (
                       symbolToString(pSubTarget->pRule->pRuleEnv->pObjDir),
                       symbolToString(pSubTarget->pFile),"",'d'
                     );
          PRJ_genPath(pSysOut,"L", szPath);
          HS_SET_ELM(pSubTarget->pFile,pTmp);
          FreeMem(szSuffix);
          FreeMem(szPath);
        }
      }
    }
    HS_FORALL(pNeed,pItr3,pTarget->pNeeds) // remaining (internal) dependants
    { 
      pSubTarget = MAP_apply(PRJ_Target,pDstMap,pNeed);
      pSubSrcTyp = MAP_apply(PRJ_Type,pProject->pTypDfn,pSubTarget->pRule->pSrcTyp);
      if( ! HS_MBR_ELM(pSubTarget->pFile,pTmp) )
      {
        szSuffix = FileSuffix(symbolToString(pSubTarget->pFile)),
        szExt    = szSuffix + (*szSuffix=='.');
        if( pSubSrcTyp->pObjSfx == (symbol)NULL ||
            stringToSymbol(szExt) != pSubSrcTyp->pObjSfx )
          szPath = MkPath
                   (
                     symbolToString(pSubTarget->pPath),
                     symbolToString(pSubTarget->pFile),"",'d'
                   );
        else
          szPath = MkPath
                   (
                     symbolToString(pSubTarget->pRule->pRuleEnv->pObjDir),
                     symbolToString(pSubTarget->pFile),"",'d'
                   );
        PRJ_genPath(pSysOut,"L", szPath);
        HS_SET_ELM(pSubTarget->pFile,pTmp);
        FreeMem(szSuffix);
        FreeMem(szPath);
      }
    }
    HS_DROP_SET(pTmp);
    // external target and rule dependants
    MAP_forItrAsg(pNeed,pDir,pItr4,pTarget->pExtLib)
    {
      szPath = MkPath(symbolToString(pDir),symbolToString(pNeed),"",'d');
      PRJ_genPath(pSysOut,"L", szPath);
      FreeMem(szPath);
    }
    MAP_forItrAsg(pNeed,pDir,pItr4,pTarget->pRule->pRuleEnv->pExtLib)
    {
      if( pDir != (symbol)NULL )
      {
        szPath = MkPath(symbolToString(pDir),symbolToString(pNeed),"",'d');
        PRJ_genPath(pSysOut,"L", szPath);
        FreeMem(szPath);
      }
    }
  }
  if( pDstTyp != (PRJ_Type)NULL )
    PRJ_genNmkCmdEnv(pSysOut,pTarget->pRule,pTarget->pType);
  else
    PRJ_genNmkCmdEnv(pSysOut,pTarget->pRule,pTarget->pRule->pSrcTyp);
}

static void PRJ_genNmk(void)
/* generate project file for 'nmk' */
{ string szMstPrj = BaseFile(CTX_PROJECT),
         szFile   = MkPath
                    (
                      symbolToString(pProject->pStdEnv->pPrjDir),
                      szMstPrj,".nmk",'d'
                    );
  FILE*       pSysOut = OpnFile(szFile,"wt");
  long        lRCnt   = OT_CNT(pRuleRow), lTCnt, lSCnt, lI, lJ, lK;
  SET(symbol) pTmp    = HS_CREATE_ADTSET(symbol);
  fprintf(pSysOut,"# [%s.nmk] generated by 'prdps' for 'prnmk'\n",szMstPrj);
  for( lI=0; lI < lRCnt; ++lI )
  { PRJ_Rule pRule   = MAP_apply(PRJ_Rule,pRuleMap,OT_GET(symbol,pRuleRow,lI));
    PRJ_Type pSrcTyp = MAP_apply(PRJ_Type,pProject->pTypDfn,pRule->pSrcTyp),
             pDstTyp = PRJ_getTargetType(pRule->pDstDfn);
    symbol   pType;
    fprintf(pSysOut,"\n# Rule %s\n\n",symbolToString(pRule->pName));
    pType = PRJ_getTargetTypeSym(pRule->pDstDfn);
    if( ! HS_MBR_ELM(pRule->pSrcTyp,pTmp) )
    {
      PRJ_genNmkCmdPat(pSysOut, pRule, pRule->pSrcTyp);
      HS_SET_ELM(pRule->pSrcTyp,pTmp);
    }
    if( ! HS_MBR_ELM(pType,pTmp) )
    {
      PRJ_genNmkCmdPat(pSysOut, pRule, pType);
      HS_SET_ELM(pType,pTmp);
    }
    lTCnt = OT_CNT(pRule->pDstRow);
    for( lJ=0; lJ < lTCnt; ++lJ )
    { PRJ_Target pTarget = MAP_apply
                           (
                             PRJ_Target,pDstMap,OT_GET(symbol,pRule->pDstRow,lJ)
                           );
      if( pSrcTyp->pObjSfx != (symbol)NULL ) 
      {
        lSCnt = OT_CNT(pTarget->pSrcRow);
        for( lK=0; lK < lSCnt; ++lK )
        { PRJ_Source pSource = MAP_apply
                               (
                                 PRJ_Source,pSrcMap,
                                 OT_GET(symbol,pTarget->pSrcRow,lK)
                               );
          PRJ_genNmkSrcCmd(pSysOut, pRule, pSource, pSrcTyp);
        }
      }
      if( PRJ_IsExternalTarget(pRule->pDstDfn) ||
          HS_CARD(pDstTyp->pTypSfx) != 1       || 
          pSrcTyp->pObjSfx != pDstTyp->pFstSfx  )
      {
        PRJ_genNmkDstCmd(pSysOut, pTarget, pDstTyp, pSrcTyp);
      }
    }
  }
  fclose(pSysOut);
  HS_DROP_SET(pTmp);
  FreeMem(szMstPrj); FreeMem(szFile);
}

static void PRJ_genList(void)
{
}

/* --------------------------- Program ------------------------------------ */

static bool PRJ_load(void)
/* load and eval project definitions */
{ Scn_T   pScn;
  PLR_Tab pPlr;
  pPlr = PLR_get_cprj();
  Scn_get_cprj(&pScn);
  PRJ_parse(pPlr,pScn,CTX_PROJECT,pProject->pStdEnv);
  if( PT_errorCnt() == 0 )
  {
    PRJ_checkStdEnv();
    if( PT_errorCnt() == 0 )
    {
      PRJ_get();
      PRJ_evalRules();
    }
  }
  Scn_free(pScn);
  PLR_delTab(pPlr);
  return ( PT_errorCnt() == 0 );
}

int main(int argc, string argv[])
{ string szDiag;
  PRJ_init(argc,argv);
  szDiag = CTX_DIAGNOSE;
  if( strlen(szDiag) > 0 ) pFP_Diag = fopen(szDiag,"wt");
  if( PRJ_load() )
  {
    // generate project files ( NMK, ... )
    if( CTX_MKNANO ) PRJ_genNmk();
    if( CTX_MKLIST ) PRJ_genList();
    PRJ_put();
  }
  if( pFP_Diag != (FILE*)NULL )
  {
    fclose(pFP_Diag); pFP_Diag = (FILE*)NULL;
  }
  PRJ_quit();
  BUG_CORE_EX(lDpsLibMemCnt);
  return(0);
}
