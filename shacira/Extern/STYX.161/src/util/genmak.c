/* [genmak.c]  generates automake input <project>.am from <project>.nmk  */

#include "stdosx.h"
#include "pathes.h"
#include "line_scn.h"
#include "symbols.h"
#include "hmap.h"
#include "hset.h"
#include "otab.h"
#include "charlib.h"
#include "sink.h"

#include "genm_cim.h"


#define CTX_ROOTPATH  CTX_EVAL(string,"rootpath") 
#define CTX_PROJECT   CTX_EVAL(string,"project") 
#define CTX_XOUTPUT   CTX_EVAL(string,"xoutput") 
#define CTX_WOUTPUT   CTX_EVAL(string,"woutput") 
#define CTX_TARGETS   CTX_EVAL(string,"targets") 
#define CTX_EXCLUDE   CTX_EVAL(string,"exclude") 
#define CTX_DYNAMIC   CTX_EVAL(bool,"dynamic") 
#define CTX_VERSION   CTX_EVAL(string,"version") 

#define PRJ_TYP_C    "C"
#define PRJ_TYP_EXE  "EXE"
#define PRJ_TYP_LIB  "LIB"
#define PRJ_TYP_DLL  "DLL"

#define RELATED_SOURCE_FILE 0
#define RELATED_SOURCE_DIR  1
#define RELATED_SOURCE_PATH 2

ConcreteType(MakTarget)
{
  symbol      pFile;
  symbol      pType;
  ROW(symbol) pSrcRow;
  ROW(symbol) pDepRow;
  SET(symbol) pIncSet;
};

static MAP(symbol,MakTarget) pDstMap;
static SET(symbol)           pDepLibSet;
static SET(symbol)           pIncDirSet;
static SET(symbol)           pSrcDirSet;
static SET(symbol)           pInstallSet;
static SET(symbol)           pRootPathSet;
static SET(symbol)           pExcludeSet;

static MakTarget newMakTarget(symbol pFile)
{ MakTarget pTarget = (MakTarget)NewMem(SizeOf(MakTarget));
  pTarget->pFile   = pFile;
  pTarget->pType   = (symbol)NULL;
  pTarget->pSrcRow = OT_CREATE_ADT(symbol);
  pTarget->pDepRow = OT_CREATE_ADT(symbol);
  pTarget->pIncSet = HS_CREATE_ADTSET(symbol);
  return pTarget;
}

static void freeMakTarget(MakTarget pTarget)
{
  OT_DEL_T(pTarget->pSrcRow);
  OT_DEL_T(pTarget->pDepRow);
  HS_DROP_SET(pTarget->pIncSet);
  FreeMem(pTarget);
}

static void initGenMak(int argc, char* argv[])
{
  CTX_init_genmak(argc,argv);
  initSymbols();
  MAP_init();
  pDstMap      = MAP_newPrimMap();
  pDepLibSet   = HS_CREATE_ADTSET(symbol);
  pIncDirSet   = HS_CREATE_ADTSET(symbol);
  pSrcDirSet   = HS_CREATE_ADTSET(symbol);
  pInstallSet  = HS_CREATE_ADTSET(symbol);
  pRootPathSet = HS_CREATE_ADTSET(symbol);
  pExcludeSet  = HS_CREATE_ADTSET(symbol);
}

static void quitGenMak(void)
{ MAPIT pItr; symbol pTargetSym; MakTarget pTarget;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
    freeMakTarget(pTarget);
  MAP_freeMap(pDstMap);
  HS_DROP_SET(pDepLibSet);
  HS_DROP_SET(pIncDirSet);
  HS_DROP_SET(pSrcDirSet);
  HS_DROP_SET(pInstallSet);
  HS_DROP_SET(pRootPathSet);
  HS_DROP_SET(pExcludeSet);
  MAP_quit();
  freeSymbols();
  CTX_quit();
}

static void fillInstallSet(void)
{ PIT    pItr = PIT_make(CTX_TARGETS); 
  string szTarget;
  //PIT_sep(pItr,":");
  while( ( szTarget = PIT_read(pItr) ) != NULL )
  { 
    HS_SET_ELM(stringToSymbol(szTarget),pInstallSet);
  }
  PIT_drop(pItr);
}

static void fillRootPathSet(void)
{ PIT    pItr = PIT_make(CTX_ROOTPATH); 
  string szPath;
  //PIT_sep(pItr,":");
  while( ( szPath = PIT_read(pItr) ) != NULL )
  { 
    HS_SET_ELM(stringToSymbol(szPath),pRootPathSet);
  }
  PIT_drop(pItr);
}

static void fillExcludeSet(void)
{ PIT    pItr = PIT_make(CTX_EXCLUDE); 
  string szPath;
  //PIT_sep(pItr,":");
  while( ( szPath = PIT_read(pItr) ) != NULL )
  { 
    HS_SET_ELM(stringToSymbol(szPath),pExcludeSet);
  }
  PIT_drop(pItr);
}

static bool IsExcluded(symbol pFile)
{ HS_Itr pItr;
  symbol pPattern;
  HS_FORALL(pPattern,pItr,pExcludeSet)
  {
    if( Str_matches(symbolToString(pFile),symbolToString(pPattern)) )
    {
      HS_DROP_ITR(pItr); return True;
    }
  }
  return False;
}

static symbol GetRelatedFile
              (
                symbol pSrcSym, string szSuffix, 
                string szDirSepRelated, short nTypeRelated
              )
{ HS_Itr pDItr, pRItr;
  SET(symbol) pDirSet = HS_CREATE_ADTSET(symbol);
  string szBase, szFile, szPath, szExt, szTmp;
  symbol pRootSym, pDirSym, pFile = (symbol)NULL;
  bool   bFound;
  HS_UNION(pDirSet,pIncDirSet,pSrcDirSet);
  szBase = BaseFile(symbolToString(pSrcSym));
  if( strlen(szSuffix) == 0 )
    szExt = FileSuffix(symbolToString(pSrcSym));
  else
    szExt = StrCopy(szSuffix);
  bFound = False;
  HS_FORALL(pRootSym,pRItr,pRootPathSet)
  {
    HS_FORALL(pDirSym,pDItr,pDirSet)
    {
      szPath = Str_printf
               (
                 "%s%s%s%s%s",
                 symbolToString(pRootSym), symbolToString(pDirSym),
                 DirSep(), szBase, szExt
               );
      if( IsPath(szPath) )
      {
        if( nTypeRelated == RELATED_SOURCE_PATH ) 
        { size_t len;
          szTmp = StrCopy(symbolToString(pRootSym));
          len = strlen(szTmp);
          if( len > 0 ) szTmp[len-1] = '\0';
          szFile = Str_printf
                   (
                     "%s%s%s%s%s%s",
                     szTmp, szDirSepRelated, 
                     symbolToString(pDirSym), szDirSepRelated, 
                     szBase, szExt
                   );
          FreeMem(szTmp);
        }
        else
        if( nTypeRelated == RELATED_SOURCE_DIR ) 
        {
          szFile = Str_printf
                   (
                     "%s%s%s%s",
                     symbolToString(pDirSym), szDirSepRelated, szBase, szExt
                   );
        }
        else
        {
          szFile = Str_printf("%s%s",szBase,szExt);
        }
        pFile = stringToSymbol(szFile);
        FreeMem(szPath); FreeMem(szFile);
        bFound = True;
        HS_DROP_ITR(pDItr); break;
      }
      else FreeMem(szPath);
    }
    if( bFound )
    {
      HS_DROP_ITR(pRItr); break;
    }
  }
  HS_DROP_SET(pDirSet);
  FreeMem(szBase); FreeMem(szExt);
  return pFile;
}

static bool IsDepInclude(MakTarget pCurTarget, symbol pIncSym)
{ MakTarget   pDepTarget;
  symbol      pDepSym;
  long        lCnt = OT_CNT(pCurTarget->pDepRow), lI;
  for( lI=0; lI < lCnt; ++lI )
  {
    pDepSym = OT_GET(symbol,pCurTarget->pDepRow,lI);
    if( MAP_defined(pDstMap,pDepSym) )
    {
      pDepTarget = MAP_apply(MakTarget,pDstMap,pDepSym);
      if( HS_MBR_ELM(pIncSym,pDepTarget->pIncSet) )
      {
        return True;
      }
    }
  }
  return False;
}

static MakTarget addTarget(string szLine)
{ string szSuffix = FileSuffix(szLine+2), 
         szBase   = BaseFile(szLine+2),
         szFile   = Str_printf("%s%s",szBase,szSuffix);
  symbol pFile    = stringToSymbol(szFile);
  if( ! IsExcluded(pFile) && ! MAP_defined(pDstMap,pFile) )
  { MakTarget pTarget = newMakTarget(pFile);
    MAP_dfndom(pDstMap,pFile,pTarget);
    FreeMem(szBase); FreeMem(szSuffix); FreeMem(szFile);
    return pTarget;
  }
  FreeMem(szBase); FreeMem(szSuffix); FreeMem(szFile);
  return (MakTarget)NULL;
}

static void addSource(string szLine, MakTarget pTarget)
{ 
  if( pTarget != (MakTarget)NULL )
  { string szSuffix  = FileSuffix(szLine+2), 
           szBase    = BaseFile(szLine+2),
           szPrefix  = FilePrefix(szLine+2),
           szSrcDir  = BaseFile(szPrefix),
           szFile    = Str_printf("%s%s",szBase,szSuffix);
    symbol pFile     = stringToSymbol(szFile);
    if( ! IsExcluded(pFile) )
    {
      if( MAP_defined(pDstMap,pFile) )
      { MakTarget pRefTarget = MAP_apply(MakTarget,pDstMap,pFile);
        if( pRefTarget->pType == stringToSymbol(PRJ_TYP_C) )
        {
          OT_PUSH(OT_GET(symbol,pRefTarget->pSrcRow,0),pTarget->pSrcRow);
          HS_UNION(pTarget->pIncSet,pTarget->pIncSet,pRefTarget->pIncSet);
        }
        else OT_PUSH(pFile,pTarget->pSrcRow);
      }
      else 
      { 
        OT_PUSH(pFile,pTarget->pSrcRow);
        HS_SET_ELM(stringToSymbol(szSrcDir),pSrcDirSet);
      }
    }
    FreeMem(szBase); FreeMem(szSuffix); FreeMem(szPrefix); 
    FreeMem(szSrcDir); FreeMem(szFile);
  }
}

static void addLibraryIncludes(MakTarget pTarget)
{ 
  if( pTarget != (MakTarget)NULL )
  { 
    if( ( pTarget->pType == stringToSymbol(PRJ_TYP_DLL) || 
          pTarget->pType == stringToSymbol(PRJ_TYP_LIB) ) )
    { long lCnt = OT_CNT(pTarget->pSrcRow), lI;
      for( lI=0; lI < lCnt; ++lI )
      { symbol pFile = OT_GET(symbol,pTarget->pSrcRow,lI), pIncSym;
        pIncSym = GetRelatedFile(pFile,".h","/",RELATED_SOURCE_DIR);
        if( pIncSym != (symbol)NULL && ! HS_MBR_ELM(pIncSym,pTarget->pIncSet) )
        { string szDir  = symbolToString(pIncSym), 
                 szTmp1 = strstr(szDir,"/"), szTmp2;
          HS_SET_ELM(pIncSym,pTarget->pIncSet);
          if( szTmp1 != (string)NULL )
          {
            *szTmp1 = '\0';
            szTmp2 = StrCopy(szDir);
            *szTmp1 = '/';
            HS_SET_ELM(stringToSymbol(szTmp2),pIncDirSet);
            HS_SET_ELM(stringToSymbol(szTmp2),pSrcDirSet);
            FreeMem(szTmp2);
          }
        }
      }
    }
  }
}

static void addLibrary(string szLine, MakTarget pTarget)
{ 
  if( pTarget != (MakTarget)NULL )
  { string szSuffix = FileSuffix(szLine+2), 
           szBase   = BaseFile(szLine+2),
           szFile   = Str_printf("%s%s",szBase,szSuffix);
    symbol pFile    = stringToSymbol(szFile);
    if( ! IsExcluded(pFile) )
    {
      if( MAP_defined(pDstMap,pFile) )
      { MakTarget pRefTarget = MAP_apply(MakTarget,pDstMap,pFile);
        if( pRefTarget->pType == stringToSymbol(PRJ_TYP_C) )
        {
          OT_PUSH(OT_GET(symbol,pRefTarget->pSrcRow,0),pTarget->pSrcRow);
        }
        else 
        {
          OT_PUSH(pFile,pTarget->pDepRow);
        }
      }
      else 
      {
        OT_PUSH(pFile,pTarget->pDepRow);
      }
    }
    FreeMem(szBase); FreeMem(szSuffix); FreeMem(szFile);
  }
}

static void addInclude(string szLine, MakTarget pTarget)
{ 
  if( pTarget != (MakTarget)NULL )
  { string szSuffix = FileSuffix(szLine+2), 
           szBase   = BaseFile(szLine+2),
           szPrefix = FilePrefix(szLine+2),
           szSrcDir = BaseFile(szPrefix),
           szFile   = Str_printf("%s/%s%s",szSrcDir,szBase,szSuffix),
           szTmp    = Str_printf("%s%s",szSrcDir,szBase);
    if( ! IsExcluded(stringToSymbol(szTmp)) )
    {
      HS_SET_ELM(stringToSymbol(szFile),pTarget->pIncSet);
      HS_SET_ELM(stringToSymbol(szSrcDir),pIncDirSet);
      HS_SET_ELM(stringToSymbol(szSrcDir),pSrcDirSet);
    }
    FreeMem(szBase); FreeMem(szSuffix); FreeMem(szPrefix);
    FreeMem(szSrcDir); FreeMem(szFile); FreeMem(szTmp);
  }
}

static void addType(string szLine, MakTarget pTarget)
{ 
  if( pTarget != (MakTarget)NULL )
  { 
    pTarget->pType = stringToSymbol(szLine+1);
  }
}

static void fillDepLibSet(void)
{ HS_Itr    pItr; 
  symbol    pFile, pDepFile;
  MakTarget pTarget;
  bool      bReady = False;
  HS_FORALL(pFile,pItr,pInstallSet)
  {
    if( MAP_defined(pDstMap,pFile) )
    { long lCnt, lI;
      pTarget = MAP_apply(MakTarget,pDstMap,pFile);
      lCnt    = OT_CNT(pTarget->pDepRow);
      for( lI=0; lI < lCnt; ++lI )
      {
        pDepFile = OT_GET(symbol,pTarget->pDepRow,lI);
        if( MAP_defined(pDstMap,pDepFile) )
          HS_SET_ELM(pDepFile,pDepLibSet);
      }
    }
  }
  while( ! bReady )
  { SET(symbol) pTmpSet;
    pTmpSet = HS_COPY(pDepLibSet);
    HS_FORALL(pFile,pItr,pTmpSet)
    {
      if( MAP_defined(pDstMap,pFile) )
      { long lCnt, lI;
        pTarget = MAP_apply(MakTarget,pDstMap,pFile);
        lCnt    = OT_CNT(pTarget->pDepRow);
        for( lI=0; lI < lCnt; ++lI )
        {
          pDepFile = OT_GET(symbol,pTarget->pDepRow,lI);
          if( MAP_defined(pDstMap,pDepFile) &&
              !HS_MBR_ELM(pDepFile,pDepLibSet) )
            HS_SET_ELM(pDepFile,pDepLibSet);
        }
      }
    }
    bReady = HS_CARD(pTmpSet) == HS_CARD(pDepLibSet);
    HS_DROP_SET(pTmpSet);
  }
}

static void loadProject(void)
{ FILE*     pSysIn = OpnFile(CTX_PROJECT,"rt");
  MakTarget pTarget = (MakTarget)NULL;
  string    szLine;
  fillRootPathSet();
  fillInstallSet();
  fillExcludeSet();
  while( ( szLine = Line_get(pSysIn) ) != NULL )
  { 
    if( strlen(szLine) > 0 )
    { char cC = *szLine;
      switch( cC )
      {
        case 'T':
          pTarget = addTarget(szLine);
          break;
        case 'S':
          addSource(szLine,pTarget);
          break;
        case 'L':
          addLibrary(szLine,pTarget);
          break;
        case 'I':
          addInclude(szLine,pTarget);
          break;
        case ';':
          addType(szLine,pTarget);
          addLibraryIncludes(pTarget);
          pTarget = (MakTarget)NULL;
          break;
        default:
          break;
      }
    }
    FreeMem(szLine);
  }
  fclose(pSysIn);
  fillDepLibSet();
}

static void genVPATH(FILE* pSysOut)
{ string szBase  = BaseFile(CTX_PROJECT),
         szFile  = strlen(CTX_XOUTPUT) > 0
                   ? Str_printf("%s.VPATH",CTX_XOUTPUT) 
                   : Str_printf("%s.VPATH",szBase);
  FILE*  pCmdOut = (FILE*)NULL;
  HS_Itr pItr; 
  symbol pSrcDir;
  bool   bFirst  = True;
  HS_FORALL(pSrcDir,pItr,pSrcDirSet)
  {
    if( bFirst )
    {
      pCmdOut = OpnFile(szFile,"wt");
      fprintf(pCmdOut,"\nVPATH =");
    }
    bFirst = False;
    fprintf(pCmdOut," %s",symbolToString(pSrcDir));
  }
  if( ! bFirst ) 
  {
    fprintf(pCmdOut,"\n\n");
    fclose(pCmdOut);
  }
  FreeMem(szBase); FreeMem(szFile);
}

static void genLINKS(FILE* pSysOut)
{ string      szBase  = BaseFile(CTX_PROJECT),
              szFile  = strlen(CTX_XOUTPUT) > 0
                        ? Str_printf("%s.LINKS",CTX_XOUTPUT) 
                        : Str_printf("%s.LINKS",szBase);
  FILE*       pCmdOut;
  MAPIT       pItr; 
  HS_Itr      pIItr;
  SET(symbol) pInstSet = HS_CREATE_ADTSET(symbol);
  MakTarget   pTarget;
  symbol      pTargetSym, pIncSym;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( ( pTarget->pType == stringToSymbol(PRJ_TYP_EXE) || 
          pTarget->pType == stringToSymbol(PRJ_TYP_LIB)  ) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    {
      HS_UNION(pInstSet,pInstSet,pTarget->pIncSet);
    }
  }
  if( HS_CARD(pInstSet) > 0 )
  {
    pCmdOut = OpnFile(szFile,"wt");
    HS_FORALL(pIncSym,pIItr,pInstSet)
    { string szFile   = symbolToString(pIncSym),
             szPrefix = FilePrefix(szFile);
      long   lLen     = strlen(szPrefix);
      fprintf
      (
        pCmdOut,"\nAC_LINK_FILES(%s, %s)",szFile,szFile+(lLen==0?0:lLen+1)
      );
      FreeMem(szPrefix);
    }
    fprintf(pCmdOut,"\n");
  }
  FreeMem(szBase); FreeMem(szFile);
  HS_DROP_SET(pInstSet);
}

static void genINCLUDES(FILE* pSysOut)
{ HS_Itr pItr; symbol pIncDir;
  bool bFirst = True;
  HS_FORALL(pIncDir,pItr,pIncDirSet)
  {
    if( bFirst ) fprintf(pSysOut,"\nINCLUDES =");
    bFirst = False;
    fprintf(pSysOut," -I%s",symbolToString(pIncDir));
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
}

static void genHEADERS(FILE* pSysOut)
{ MAPIT       pItr; 
  HS_Itr      pIItr;
  SET(symbol) pInstSet = HS_CREATE_ADTSET(symbol);
  MakTarget   pTarget;
  symbol      pTargetSym, pIncSym;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( ( pTarget->pType == stringToSymbol(PRJ_TYP_EXE) || 
          pTarget->pType == stringToSymbol(PRJ_TYP_LIB) ||
          pTarget->pType == stringToSymbol(PRJ_TYP_DLL)  ) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    {
      HS_UNION(pInstSet,pInstSet,pTarget->pIncSet);
    }
  }
  if( HS_CARD(pInstSet) > 0 )
  {
    fprintf(pSysOut,"\niHEADERS =");
    HS_FORALL(pIncSym,pIItr,pInstSet)
    { string szFile    = symbolToString(pIncSym),
             szPrefix  = FilePrefix(szFile),
             szPPrefix = FilePrefix(szPrefix);
      long   lLen      = strlen(szPrefix),
             lPLen     = strlen(szPPrefix);
      if( lLen == 0 )
        fprintf(pSysOut," %s",szFile);
      else
      {
        if( lLen > lPLen )
          fprintf(pSysOut," %s",szFile+lPLen);
        else
          fprintf(pSysOut," %s",szFile+lLen+1);
      }
      FreeMem(szPrefix); FreeMem(szPPrefix);
    }
    fprintf(pSysOut,"\n\n");
  }
  HS_DROP_SET(pInstSet);
}

static void genPROGRAMS(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget;
  symbol    pTargetSym;
  bool      bFirst = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_EXE) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    {
      if( bFirst ) fprintf(pSysOut,"\nbin_PROGRAMS =");
      bFirst = False;
      fprintf(pSysOut," %s",symbolToString(pTargetSym));
    }
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
}

static void genXXX_PROGRAMS(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget, pDepTarget;
  symbol    pTargetSym;
  bool      bFirst = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_EXE) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { long   lCnt = OT_CNT(pTarget->pSrcRow), lI;
      symbol pIncSym, pDepSym;
      HS_Itr pIItr;
      bFirst = False;
      fprintf(pSysOut,"\n%s_SOURCES =",symbolToString(pTargetSym));
      for( lI=0; lI < lCnt; ++lI )
      {
        fprintf
        (
          pSysOut," %s",symbolToString(OT_GET(symbol,pTarget->pSrcRow,lI))
        );
      }
      HS_FORALL(pIncSym,pIItr,pTarget->pIncSet)
      { string szFile   = symbolToString(pIncSym),
               szPrefix = FilePrefix(szFile);
        long   lLen     = strlen(szPrefix);
        fprintf(pSysOut," %s",szFile+(lLen==0?0:lLen+1));
        FreeMem(szPrefix);
      }
      fprintf(pSysOut,"\n\n");
      lCnt = OT_CNT(pTarget->pDepRow);
      if( lCnt > 0 )
      {
        fprintf(pSysOut,"\n%s_LDADD =",symbolToString(pTargetSym));
        for( lI=0; lI < lCnt; ++lI )
        {
          pDepSym = OT_GET(symbol,pTarget->pDepRow,lI);
          if( MAP_defined(pDstMap,pDepSym) )
          {
            pDepTarget = MAP_apply(MakTarget,pDstMap,pDepSym);
            if( pDepTarget->pType == stringToSymbol(PRJ_TYP_DLL) )
            { string szDepBase, szTmp;
              szDepBase = BaseFile(symbolToString(pDepSym));
              szTmp     = Str_printf("%s.la",szDepBase);
              pDepSym = stringToSymbol(szTmp);
              FreeMem(szDepBase); FreeMem(szTmp);
            }
          }
          fprintf
          (
            pSysOut," %s",symbolToString(pDepSym)
          );
        }
        fprintf(pSysOut,"\n\n");
      }
    }
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
}

static void genXXX_LTLIBRARIES(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget, pDepTarget;
  symbol    pTargetSym;
  bool      bFirst = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_DLL) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { long   lCnt   = OT_CNT(pTarget->pSrcRow), lI;
      string szBase = BaseFile(symbolToString(pTargetSym)),
             szDepBase, szTmp;
      symbol pIncSym, pDepSym;
      HS_Itr pIItr;
      bFirst = False;
      fprintf(pSysOut,"\n%s_la_SOURCES =",szBase);
      for( lI=0; lI < lCnt; ++lI )
      {
        fprintf
        (
          pSysOut," %s",symbolToString(OT_GET(symbol,pTarget->pSrcRow,lI))
        );
      }
      HS_FORALL(pIncSym,pIItr,pTarget->pIncSet)
      { string szFile   = symbolToString(pIncSym),
               szPrefix = FilePrefix(szFile);
        long   lLen     = strlen(szPrefix);
        fprintf(pSysOut," %s",szFile+(lLen==0?0:lLen+1));
        FreeMem(szPrefix);
      }
      fprintf(pSysOut,"\n\n");
      lCnt = OT_CNT(pTarget->pDepRow);
      if( lCnt > 0 )
      {
        //fprintf(pSysOut,"\n%s_LDADD =",symbolToString(pTargetSym));
        fprintf(pSysOut,"\n%s_la_LDADD =",szBase);
        for( lI=0; lI < lCnt; ++lI )
        {
          pDepSym = OT_GET(symbol,pTarget->pDepRow,lI);
          if( MAP_defined(pDstMap,pDepSym) )
          {
            pDepTarget = MAP_apply(MakTarget,pDstMap,pDepSym);
            if( pDepTarget->pType == stringToSymbol(PRJ_TYP_DLL) )
            {
              szDepBase = BaseFile(symbolToString(pDepSym));
              szTmp     = Str_printf("%s.la",szDepBase);
              pDepSym = stringToSymbol(szTmp);
              FreeMem(szDepBase); FreeMem(szTmp);
            }
          }
          fprintf
          (
            pSysOut," %s",symbolToString(pDepSym)
          );
        }
        fprintf(pSysOut,"\n\n");
      }
      FreeMem(szBase);
    }
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
}

static void genXXX_LIBRARIES(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget;
  symbol    pTargetSym;
  bool      bFirst = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_LIB) &&
        ( HS_CARD(pInstallSet) == 0 || 
          HS_MBR_ELM(pTargetSym,pInstallSet) ||
          HS_MBR_ELM(pTargetSym,pDepLibSet) ) )
    { long   lCnt   = OT_CNT(pTarget->pSrcRow), lI;
      string szBase = BaseFile(symbolToString(pTargetSym));
      symbol pIncSym;
      HS_Itr pIItr;
      bFirst = False;
      if( CTX_DYNAMIC && 
          ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
        fprintf(pSysOut,"\n%s_la_SOURCES =",szBase);
      else
        fprintf(pSysOut,"\n%s_a_SOURCES =",szBase);
      for( lI=0; lI < lCnt; ++lI )
      {
        fprintf
        (
          pSysOut," %s",symbolToString(OT_GET(symbol,pTarget->pSrcRow,lI))
        );
      }
      HS_FORALL(pIncSym,pIItr,pTarget->pIncSet)
      { string szFile   = symbolToString(pIncSym),
               szPrefix = FilePrefix(szFile);
        long   lLen     = strlen(szPrefix);
        fprintf(pSysOut," %s",szFile+(lLen==0?0:lLen+1));
        FreeMem(szPrefix);
      }
      fprintf(pSysOut,"\n\n");
      FreeMem(szBase);
    }
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
}

static void genLIBRARIES(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget;
  symbol    pTargetSym;
  string    szFile, szBase;
  bool      bFirst1 = True,
            bFirst2 = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_LIB) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { 
      szFile = symbolToString(pTargetSym);
      szBase = BaseFile(szFile);
      if( bFirst1 ) 
      {
        if( CTX_DYNAMIC )
          fprintf(pSysOut,"\nlib_LTLIBRARIES =");
        else
          fprintf(pSysOut,"\nlib_LIBRARIES =");
      }
      bFirst1 = False;
      if( CTX_DYNAMIC )
        fprintf(pSysOut," %s.la",szBase);
      else
        fprintf(pSysOut," %s",szFile);
      FreeMem(szBase);
    }
  }
  fprintf(pSysOut,"\n\n");
  if( ! bFirst1 && CTX_DYNAMIC && strlen(CTX_VERSION) > 0 )
  {
    MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
    {
      if( pTarget->pType == stringToSymbol(PRJ_TYP_LIB) && 
          ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
      {
        szFile = symbolToString(pTargetSym);
        szBase = BaseFile(szFile);
        fprintf(pSysOut,"\n%s_la_LDFLAGS = -version-info %s",szBase,CTX_VERSION);
        FreeMem(szBase);
      }
    }
    fprintf(pSysOut,"\n\n");
  }
  if( HS_CARD(pInstallSet) > 0 )
  {
    MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
    {
      if( pTarget->pType == stringToSymbol(PRJ_TYP_LIB) &&
          ! HS_MBR_ELM(pTargetSym,pInstallSet)          &&
          HS_MBR_ELM(pTargetSym,pDepLibSet)              )
      {
        if( bFirst2 ) fprintf(pSysOut,"\nnoinst_LIBRARIES =");
        bFirst2 = False;
        fprintf(pSysOut," %s",symbolToString(pTargetSym));
      }
    }
    if( ! bFirst1 || ! bFirst2 ) fprintf(pSysOut,"\n\n");
  }
}

static void genLTLIBRARIES(FILE* pSysOut)
{ MAPIT     pItr; 
  MakTarget pTarget;
  symbol    pTargetSym;
  string    szFile, szBase;
  bool      bFirst = True;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_DLL) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { 
      szFile = symbolToString(pTargetSym);
      szBase = BaseFile(szFile);
      if( bFirst ) fprintf(pSysOut,"\nlib_LTLIBRARIES =");
      bFirst = False;
      fprintf(pSysOut," %s.la",szBase);
      FreeMem(szBase);
    }
  }
  if( ! bFirst ) fprintf(pSysOut,"\n\n");
  if( ! bFirst && CTX_DYNAMIC && strlen(CTX_VERSION) > 0 )
  {
    MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
    {
      if( pTarget->pType == stringToSymbol(PRJ_TYP_DLL) && 
          ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
      { 
        szFile = symbolToString(pTargetSym);
        szBase = BaseFile(szFile);
        fprintf(pSysOut,"\n%s_la_LDFLAGS = -version-info %s",szBase,CTX_VERSION);
        FreeMem(szBase);
      }
    }
    fprintf(pSysOut,"\n\n");
  }
}

static string szInstallCmd =
"install-data-local:\
\n\tinstall -d $(prefix)/include\
\n\tfor i in $(iHEADERS); do install -m 444 $$i $(prefix)/include; done\
\n\tif [ -d man ] ; then install -d $(prefix)/man; fi\
\n\tif [ -d man ] ; then for i in man/* ; do if [ $$i != \"man/*\" ]; then install $$i $(prefix)/man; fi; done; fi\
\n\tif [ -d tutorial ] ; then cp -r tutorial $(prefix); fi;\
\n\tif [ -d doc ] ; then cp -r doc $(prefix); fi;\
";

/*necessary for cdps*/

static void genMakeFile(void)
{ string szBase  = BaseFile(CTX_PROJECT),
         szFile  = strlen(CTX_XOUTPUT) > 0
                   ? Str_printf("%s.am",CTX_XOUTPUT) 
                   : Str_printf("%s.am",szBase);
  FILE*  pSysOut = OpnFile(szFile,"wt");
  //ausgelagert nach configure.in:
  //fprintf(pSysOut,"CFLAGS=-funsigned-char @CFLAGS@\n");
  genVPATH(pSysOut);
  //not needed becourse of install statements
  //genLINKS(pSysOut);
  genINCLUDES(pSysOut);
  genLIBRARIES(pSysOut);
  genXXX_LIBRARIES(pSysOut);
  genLTLIBRARIES(pSysOut);
  genXXX_LTLIBRARIES(pSysOut);
  genPROGRAMS(pSysOut);
  genXXX_PROGRAMS(pSysOut);
  genHEADERS(pSysOut);
  fprintf(pSysOut,"\n%s\n",szInstallCmd);
  fclose(pSysOut);
  FreeMem(szBase); FreeMem(szFile);
}

static void genDefFiles(void)
{ MAPIT       pItr; 
  MakTarget   pTarget;
  symbol      pTargetSym, pSrcSym, pExpSym;
  string      szBase, szDefPath, szTmp, szLine;
  FILE*       pSysOut = NULL, *pSysIn = NULL;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( pTarget->pType == stringToSymbol(PRJ_TYP_DLL) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { long lCnt = OT_CNT(pTarget->pSrcRow), lI;
      szBase    = BaseFile(symbolToString(pTarget->pFile));
      szDefPath = Str_printf("%s%s.def",CTX_WOUTPUT,szBase);
      pSysOut = OpnFile(szDefPath,"wt");
      FreeMem(szBase); FreeMem(szDefPath);
      fprintf(pSysOut,"EXPORTS\n");
      for( lI=0; lI < lCnt; ++lI )
      {
        pSrcSym = OT_GET(symbol,pTarget->pSrcRow,lI);
        pExpSym = GetRelatedFile(pSrcSym,".exp",DirSep(),RELATED_SOURCE_PATH);
        if( pExpSym != (symbol)NULL )
        {
          pSysIn = OpnFile(symbolToString(pExpSym),"rt");
          while( ( szLine = Line_get(pSysIn) ) != NULL )
          { 
            if( strlen(szLine) > 0 )
            {
              szTmp = strstr(szLine,":");
              if( szTmp != (string)NULL )
                fprintf(pSysOut,"%s\n",szTmp+1);
            }
            FreeMem(szLine);
          }
          fclose(pSysIn);
        }
      }
      fclose(pSysOut);
    }
  }
}

static void genDspFiles(void)
{ MAPIT       pItr; 
  HS_Itr      pIItr;
  MakTarget   pTarget;
  symbol      pTargetSym, pSrcSym, pDirSym;
  string      szBase, szDspPath, szSrcPath, szTmp;
  FILE*       pSysOut = NULL;
  MAP_forItrAsg(pTargetSym,pTarget,pItr,pDstMap)
  {
    if( ( pTarget->pType == stringToSymbol(PRJ_TYP_EXE) || 
          pTarget->pType == stringToSymbol(PRJ_TYP_DLL) || 
          pTarget->pType == stringToSymbol(PRJ_TYP_LIB)  ) && 
        ( HS_CARD(pInstallSet) == 0 || HS_MBR_ELM(pTargetSym,pInstallSet) ) )
    { long lCnt = OT_CNT(pTarget->pSrcRow), lI;
      // Sources
      szBase    = BaseFile(symbolToString(pTarget->pFile));
      szDspPath = Str_printf("%s%s.dsp.src",CTX_WOUTPUT,szBase);
      pSysOut = OpnFile(szDspPath,"wt");
      FreeMem(szBase); FreeMem(szDspPath);
      for( lI=0; lI < lCnt; ++lI )
      {
        pSrcSym = OT_GET(symbol,pTarget->pSrcRow,lI);
        pDirSym = GetRelatedFile(pSrcSym,"","\\",RELATED_SOURCE_DIR);
        if( pDirSym != (symbol)NULL )
        {
          fprintf(pSysOut,"# Begin Source File\n\n");
          fprintf(pSysOut,"SOURCE=..\\%s\n",symbolToString(pDirSym));
          fprintf(pSysOut,"# End Source File\n");
        }
      }
      fclose(pSysOut);
      // Header
      szBase    = BaseFile(symbolToString(pTarget->pFile));
      szDspPath = Str_printf("%s%s.dsp.inc",CTX_WOUTPUT,szBase);
      pSysOut = OpnFile(szDspPath,"wt");
      FreeMem(szBase); FreeMem(szDspPath);
      HS_FORALL(pSrcSym,pIItr,pTarget->pIncSet)
      {
        if( ! IsDepInclude(pTarget,pSrcSym) )
        {
          szSrcPath = symbolToString(pSrcSym);
          szTmp = strstr(szSrcPath,"/");
          if( szTmp != (c_string)NULL ) *szTmp = '\\';
          szBase = Str_printf("..\\%s", szSrcPath);
          if( szTmp != (c_string)NULL ) *szTmp = '/';
          fprintf(pSysOut,"# Begin Source File\n\n");
          fprintf(pSysOut,"SOURCE=%s\n",szBase);
          fprintf(pSysOut,"# End Source File\n");
          FreeMem(szBase);
        }
      }
      fclose(pSysOut);
    }
  }
}

int main(int argc, string argv[])
{
  initGenMak(argc,argv);
  loadProject();
  genMakeFile();
  genDefFiles();
  genDspFiles();
  quitGenMak();
  BUG_CORE;
  return(0);
}
