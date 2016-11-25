/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prs_io.c]       LALR(1) Parser/Generator: parse table input/output      */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "prs_dfn.h"
#include "binimg.h"

#include "prs_imp.h"
#include "pathes.h"
#include "literal.h"
#include "sink.h"

/*!!
   This module provides functions that 
   1) generate a C module for a given parse table
   2) unload a parse table to a binary image file 
   3) load a parse table from a binary image file.
*/


/* ====================== Types, Globals & Constants ======================== */


typedef struct _PRFRM { /* Druckformat Basistyp */
  int mcols;      /* maximale Spaltenanzahl */
  char format[7]; /* Formatstring           */
  char sep;       /* Trennzeichen           */
  int indent;     /* Einrueckung            */
} PRFRM;


#define PR_FRM_INT        0
#define PR_FRM_LONG       1
#define PR_FRM_CHAR       2
#define PR_FRM_STRING     3

#define SFX_PARSETAB      "_ParseTab"
#define SFX_SNAMES        "_SNames"
#define SFX_STARTIDS      "_StartIds"
#define SFX_TOKKIND       "_TokKind"
#define SFX_NTCLASS       "_NtClass"
#define SFX_ERRORNT       "_ErrorNt"
#define SFX_KFGHEAD       "_KfgHead"  
#define SFX_PSYMBOLS      "_PSymbols"
#define SFX_PSYMFRMS      "_PSymFrms"
#define SFX_KFGPRODS      "_KfgProds"   
#define SFX_MSTSHIFT      "_MstShifts"  
#define SFX_DTLSHIFT      "_DtlShifts"  
#define SFX_GOTO          "_GoTos"  
#define SFX_GOTODFT       "_GoToDfts"  
#define SFX_ACTDFT        "_ActDfts"  
#define SFX_ACTEXP        "_ActExps"  


/* ============================= Auxiliary ================================== */

static void PrintArray
            (
              FILE* fp, StdCPtr array, int cnt, PRFRM* frmdef, int format
            )
/* prints an array with type and format 'format' */
{ int i;

  BUG_NULL(fp); BUG_NULL(array);
  BUG_VMIN(cnt,0); BUG_VRNG(format,PR_FRM_INT,PR_FRM_STRING);
  for( i=0; i < cnt; ++i )
  {
    if( ! ( i % frmdef[format].mcols ) )
      fprintf(fp,"\n%*s",frmdef[format].indent,"");
    if( format == PR_FRM_INT )
      fprintf(fp,frmdef[format].format,((int*)array)[i]);
    else
    if( format == PR_FRM_LONG )
      fprintf(fp,frmdef[format].format,((long*)array)[i]);
    else
    if( format == PR_FRM_CHAR )
    { string t = LIT_c_char_lit(((string)array)[i]);
      fprintf(fp,frmdef[PR_FRM_STRING].format,t);
      FreeMem(t);
    }
    else
    if( format == PR_FRM_STRING )
    { string t = LIT_c_str_lit(((string*)array)[i]);
      fprintf(fp,frmdef[format].format,t);
      FreeMem(t);
    }
    if( i < cnt - 1 ) fprintf(fp,"%c ",frmdef[format].sep);
  }
}

static void SetFormat(PRFRM* frmdef, int format, char sep, int indent)
/* specifies variable format arguments */
{
  BUG_VRNG(format,PR_FRM_INT,PR_FRM_STRING); BUG_VMIN(indent,-1);
  frmdef[PR_FRM_STRING+1].indent = frmdef[format].indent;
  frmdef[PR_FRM_STRING+1].sep    = frmdef[format].sep;
  frmdef[format].indent          = indent;
  frmdef[format].sep             = sep;
}

static void ResetFormat(PRFRM* frmdef, int format)
/* reset variable format arguments to default values */
{
  BUG_VRNG(format,PR_FRM_INT,PR_FRM_STRING);
  frmdef[format].indent = frmdef[PR_FRM_STRING+1].indent;
  frmdef[format].sep    = frmdef[PR_FRM_STRING+1].sep;
}

/* ========================= C-Modul Printing =============================== */

static void printKfgGlobals(FILE* fp, KFGHEAD* Kfg, PRFRM* frmdef, int indent)
{
  SetFormat(frmdef,PR_FRM_STRING,',',indent);
  FNL(fp);
  fprintf(fp,"static string %s%s[] = {",Kfg->language,SFX_SNAMES);
  PrintArray(fp,Kfg->SNames,Kfg->TkCnt+Kfg->NtCnt,frmdef,PR_FRM_STRING);
  FPNLSNL(fp,"};"); FNL(fp);
  ResetFormat(frmdef,PR_FRM_STRING); SetFormat(frmdef,PR_FRM_INT,',',indent);
  fprintf(fp,"static int %s%s[] = {",Kfg->language,SFX_STARTIDS);
  PrintArray(fp,Kfg->StartIds,Kfg->StartCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  if( Kfg->TkCnt )
  {
    fprintf(fp,"static int %s%s[] = {",Kfg->language,SFX_TOKKIND);
    PrintArray(fp,Kfg->TokKind,Kfg->TkCnt,frmdef,PR_FRM_INT);
    FPNLSNL(fp,"};"); FNL(fp);
  }
  fprintf(fp,"static int %s%s[] = {",Kfg->language,SFX_NTCLASS);
  PrintArray(fp,Kfg->NtClass,Kfg->NtCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  fprintf(fp,"static c_bool %s%s[] = {",Kfg->language,SFX_ERRORNT);
  PrintArray(fp,Kfg->ErrorNt,Kfg->NtCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  fprintf(fp,"static KFGHEAD %s%s = {",Kfg->language,SFX_KFGHEAD);
  FNLIND(fp);
  fprintf(fp,"\"%s\",",Kfg->language);
  FNLIND(fp);
  fprintf(fp,"%d, %d, %s%s,",Kfg->TkCnt,Kfg->NtCnt,Kfg->language,SFX_SNAMES);
  FNLIND(fp);
  fprintf(fp,"%d, %s%s,",Kfg->StartCnt,Kfg->language,SFX_STARTIDS);
  FNLIND(fp);
  if( Kfg->TkCnt )
    fprintf(fp,"%s%s,",Kfg->language,SFX_TOKKIND);
  else fprintf(fp,"(int*)NULL,");
  FNLIND(fp);
  fprintf(fp,"%s%s,",Kfg->language,SFX_NTCLASS);
  FNLIND(fp);
  fprintf(fp,"%s%s",Kfg->language,SFX_ERRORNT);
  FPNLSNL(fp,"};");
  ResetFormat(frmdef,PR_FRM_INT);
}

static void printKfgProds
            (
              FILE* fp, KFGPROD* Prods, int ProdCnt, string language, 
              PRFRM* frmdef, int indent
            )
{ int LstSemIdx = 0, idx, i;

  BUG_NULL(Prods);
  BUG_VMIN(ProdCnt,0);
  for( i = ProdCnt-1; i >= 0; --i ) if( Prods[i].symcnt )
  {
    LstSemIdx = i; break;
  }
  SetFormat(frmdef,PR_FRM_INT,',',indent);

  FNL(fp);
  fprintf(fp,"static int %s%s[] = {",language,SFX_PSYMBOLS);
  for( i=0; i < ProdCnt; ++i ) if( Prods[i].symcnt )
  {
    PrintArray(fp,Prods[i].symbols,Prods[i].symcnt,frmdef,PR_FRM_INT);
    if( i < LstSemIdx ) fprintf(fp,",");
  }
  FPNLSNL(fp,"};"); FNL(fp);

  fprintf(fp,"static int %s%s[] = {",language,SFX_PSYMFRMS);
  for( i=0; i < ProdCnt; ++i ) if( Prods[i].symcnt )
  {
    PrintArray(fp,Prods[i].symfrms,Prods[i].symcnt,frmdef,PR_FRM_INT);
    if( i < LstSemIdx ) fprintf(fp,",");
  }
  FPNLSNL(fp,"};"); FNL(fp);

  fprintf(fp,"static KFGPROD %s%s[] = {",language,SFX_KFGPRODS);
  for( i=0, idx=0; i < ProdCnt; idx += Prods[i].symcnt, ++i )
  {
    FNLIND(fp);
    fprintf
    (
      fp,"{ \"%s\", %d, %d, %d, ",
      Prods[i].pname,Prods[i].method,Prods[i].id,Prods[i].symcnt
    );
    if( Prods[i].symcnt ) 
      fprintf
      (
        fp,"&%s%s[%d], &%s%s[%d]",
        language,SFX_PSYMBOLS,idx,
        language,SFX_PSYMFRMS,idx
      );
    else                  
      fprintf(fp,"(int*)NULL, (int*)NULL");
    fprintf(fp," }%s", ( i < ProdCnt-1 ) ? "," : "");
  }
  FPNLSNL(fp,"};");
  ResetFormat(frmdef,PR_FRM_INT);
}

static void printLalr1Tabs
            (
              FILE* fp,LALR_1* tabs, string language, 
              PRFRM* frmdef, int indent
            )
{
  SetFormat(frmdef,PR_FRM_INT,',',indent);
  FNL(fp);
  fprintf(fp,"static int %s%s[] = {",language,SFX_MSTSHIFT);
  PrintArray(fp,tabs->MstShift,tabs->MstShiftCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  if( tabs->DtlShiftCnt )
  {
    fprintf(fp,"static int %s%s[] = {",language,SFX_DTLSHIFT);
    PrintArray(fp,tabs->DtlShift,tabs->DtlShiftCnt,frmdef,PR_FRM_INT);
    FPNLSNL(fp,"};"); FNL(fp);
  }
  fprintf(fp,"static int %s%s[] = {",language,SFX_GOTO);
  PrintArray(fp,tabs->GoTo,tabs->GoToCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  fprintf(fp,"static int %s%s[] = {",language,SFX_GOTODFT);
  PrintArray(fp,tabs->GoToDft,tabs->GoToDftCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  fprintf(fp,"static int %s%s[] = {",language,SFX_ACTDFT);
  PrintArray(fp,tabs->ActDft,tabs->ActDftCnt,frmdef,PR_FRM_INT);
  FPNLSNL(fp,"};"); FNL(fp);
  if( tabs->ActExpCnt )
  {
    fprintf(fp,"static int %s%s[] = {",language,SFX_ACTEXP);
    PrintArray(fp,tabs->ActExp,tabs->ActExpCnt,frmdef,PR_FRM_INT);
    FPNLSNL(fp,"};");
  }
  ResetFormat(frmdef,PR_FRM_INT);
}

/* ========================== Put and Get =================================== */

static void fputKfgGlobals(BinImg_T img, KFGHEAD* Kfg)
{ int symcnt, i;

  fputString(img,Kfg->language);
  fputInt(img,Kfg->TkCnt);
  fputInt(img,Kfg->NtCnt);
  symcnt = Kfg->TkCnt + Kfg->NtCnt;
  for( i=0; i < symcnt; ++i )        fputString(img,Kfg->SNames[i]);
  fputInt(img,Kfg->StartCnt);
  for( i=0; i < Kfg->StartCnt; ++i ) fputInt(img,Kfg->StartIds[i]);
  for( i=0; i < Kfg->TkCnt; ++i )    fputInt(img,Kfg->TokKind[i]);
  for( i=0; i < Kfg->NtCnt; ++i )    fputInt(img,Kfg->NtClass[i]);
  for( i=0; i < Kfg->NtCnt; ++i )    fputInt(img,Kfg->ErrorNt[i]);
}

static void fputKfgProds(BinImg_T img, KFGPROD* Prods, int ProdCnt)
{ int i, j;

  BUG_NULL(Prods);
  BUG_VMIN(ProdCnt,0);
  fputInt(img,ProdCnt);
  for( i=0; i < ProdCnt; ++i )
  {
    fputString(img,Prods[i].pname);
    fputInt(img,Prods[i].id);
    fputInt(img,Prods[i].method);
    fputInt(img,Prods[i].symcnt);
    for( j=0; j < Prods[i].symcnt; ++j ) fputInt(img,Prods[i].symbols[j]);
    for( j=0; j < Prods[i].symcnt; ++j ) fputInt(img,Prods[i].symfrms[j]);
  }
}

static void fputLalr1Tabs(BinImg_T img, LALR_1* tabs)
{ int i;

  fputInt(img,tabs->MstShiftCnt);
  for( i=0; i < tabs->MstShiftCnt; ++i ) fputInt(img,tabs->MstShift[i]);
  fputInt(img,tabs->DtlShiftCnt);
  for( i=0; i < tabs->DtlShiftCnt; ++i ) fputInt(img,tabs->DtlShift[i]);
  fputInt(img,tabs->GoToCnt);
  for( i=0; i < tabs->GoToCnt; ++i )     fputInt(img,tabs->GoTo[i]);
  fputInt(img,tabs->GoToDftCnt);
  for( i=0; i < tabs->GoToDftCnt; ++i )  fputInt(img,tabs->GoToDft[i]);
  fputInt(img,tabs->ActDftCnt);
  for( i=0; i < tabs->ActDftCnt; ++i )   fputInt(img,tabs->ActDft[i]);
  fputInt(img,tabs->ActExpCnt);
  for( i=0; i < tabs->ActExpCnt; ++i )   fputInt(img,tabs->ActExp[i]);
}

static void fgetKfgGlobals(BinImg_T img, KFGHEAD* Kfg)
{ int symcnt, i;

  fgetString(img,&Kfg->language);
  fgetInt(img,&Kfg->TkCnt);
  fgetInt(img,&Kfg->NtCnt);
  symcnt            = Kfg->TkCnt + Kfg->NtCnt;
  Kfg->SNames       = (string*)NewMem(sizeof(string)*symcnt);
  for( i=0; i < symcnt; ++i )        fgetString(img,&Kfg->SNames[i]);
  fgetInt(img,&Kfg->StartCnt);
  Kfg->StartIds     = (int*)NewMem(sizeof(int)*Kfg->StartCnt);
  for( i=0; i < Kfg->StartCnt; ++i ) fgetInt(img,&Kfg->StartIds[i]);
  if( Kfg->TkCnt )
  {
    Kfg->TokKind    = (int*)NewMem(sizeof(int)*Kfg->TkCnt);
    for( i=0; i < Kfg->TkCnt; ++i )  fgetInt(img,&Kfg->TokKind[i]);
  }
  else Kfg->TokKind = (int*)NULL;
  Kfg->NtClass      = (int*)NewMem(sizeof(int)*Kfg->NtCnt);
  for( i=0; i < Kfg->NtCnt; ++i )    fgetInt(img,&Kfg->NtClass[i]);
  Kfg->ErrorNt      = (bool*)NewMem(sizeof(bool)*Kfg->NtCnt);
  for( i=0; i < Kfg->NtCnt; ++i )    fgetInt(img,&Kfg->ErrorNt[i]);
}

static void fgetKfgProds(BinImg_T img, KFGPROD* Prods, int ProdCnt)
{ int i, j;

  for( i=0; i < ProdCnt; ++i )
  {
    fgetString(img,&Prods[i].pname);
    fgetInt(img,&Prods[i].id);
    fgetInt(img,&Prods[i].method);
    fgetInt(img,&Prods[i].symcnt);
    if( Prods[i].symcnt )
    {
      Prods[i].symbols = (int*)NewMem(sizeof(int)*Prods[i].symcnt);
      for( j=0; j < Prods[i].symcnt; ++j ) fgetInt(img,&Prods[i].symbols[j]);
      Prods[i].symfrms = (int*)NewMem(sizeof(int)*Prods[i].symcnt);
      for( j=0; j < Prods[i].symcnt; ++j ) fgetInt(img,&Prods[i].symfrms[j]);
    }
    else Prods[i].symbols = Prods[i].symfrms = (int*)NULL;
  }
}

static void fgetLalr1Tabs(BinImg_T img, LALR_1* tabs)
{ int i;

  fgetInt(img,&tabs->MstShiftCnt);
  tabs->MstShift      = (int*)NewMem(sizeof(int)*tabs->MstShiftCnt);
  for( i=0; i < tabs->MstShiftCnt; ++i )   fgetInt(img,&tabs->MstShift[i]);
  fgetInt(img,&tabs->DtlShiftCnt);
  if( tabs->DtlShiftCnt )
  {
    tabs->DtlShift    = (int*)NewMem(sizeof(int)*tabs->DtlShiftCnt);
    for( i=0; i < tabs->DtlShiftCnt; ++i ) fgetInt(img,&tabs->DtlShift[i]);
  }
  else tabs->DtlShift = (int*)NULL;
  fgetInt(img,&tabs->GoToCnt);
  tabs->GoTo          = (int*)NewMem(sizeof(int)*tabs->GoToCnt);
  for( i=0; i < tabs->GoToCnt; ++i )       fgetInt(img,&tabs->GoTo[i]);
  fgetInt(img,&tabs->GoToDftCnt);
  tabs->GoToDft       = (int*)NewMem(sizeof(int)*tabs->GoToDftCnt);
  for( i=0; i < tabs->GoToDftCnt; ++i )    fgetInt(img,&tabs->GoToDft[i]);
  fgetInt(img,&tabs->ActDftCnt);
  tabs->ActDft        = (int*)NewMem(sizeof(int)*tabs->ActDftCnt);
  for( i=0; i < tabs->ActDftCnt; ++i )     fgetInt(img,&tabs->ActDft[i]);
  fgetInt(img,&tabs->ActExpCnt);
  if( tabs->ActExpCnt )
  {
    tabs->ActExp      = (int*)NewMem(sizeof(int)*tabs->ActExpCnt);
    for( i=0; i < tabs->ActExpCnt; ++i )   fgetInt(img,&tabs->ActExp[i]);
  }
  else tabs->ActExp   = (int*)NULL;
}

/* ============== Parser/Generator Input/Output Interface =================== */

/*I------------------------------ C-Module ---------------------------------- */

void PLR_CTab_Source(FILE* fp, c_string fid, PLR_Tab PTab)
/* writes source for parse table 'PTab' to file 'fp';
   produces a source header if filename 'fid' is not empty
*/
{ int indent = 2;
  PRFRM frmdef[PR_FRM_STRING+2] = {
    { 8, "%d",      ',',  2 },
    { 8, "%ld",     ',',  2 },
    { 8, "'%c'",    ',',  2 },
    { 5, "%s",      ',',  2 },
    { 0, "",        '\0', 0 }
  };

  BUG_NULL(PTab); BUG_NULL(PLR_T_IMP(PTab)->Kfg);
  BUG_NULL(PLR_T_IMP(PTab)->Kfg->language);
  if( !STR_EMPTY(fid) )
    fprintf
    (
      fp,"/* [%s] Parser table for '%s'  */\n\n",
      fid ,PLR_T_IMP(PTab)->Kfg->language
    );
  FNL(fp); FNL(fp);
  fprintf(fp,"#include \"prs.h\"");
  FNL(fp); FNL(fp);
  fprintf(fp,"#include \"prs_imp.h\"");
  FNL(fp); FNL(fp);
  printKfgGlobals(fp,PLR_T_IMP(PTab)->Kfg,frmdef,2);
  printKfgProds
  (
    fp, PLR_T_IMP(PTab)->Prod,PLR_T_IMP(PTab)->ProdCnt,
    PLR_T_IMP(PTab)->Kfg->language, frmdef, 2
  );
  printLalr1Tabs
  (
    fp,&PLR_T_IMP(PTab)->tabs,PLR_T_IMP(PTab)->Kfg->language,frmdef,2
  );
  FNL(fp);
  fprintf
  (
    fp,"static PARSETAB %s%s = {",PLR_T_IMP(PTab)->Kfg->language,SFX_PARSETAB
  );
  FNLIND(fp);
  fprintf
  (
    fp,"&%s%s, %d, %s%s,",
    PLR_T_IMP(PTab)->Kfg->language,SFX_KFGHEAD,
    PLR_T_IMP(PTab)->ProdCnt,
    PLR_T_IMP(PTab)->Kfg->language,SFX_KFGPRODS
  );
  FNLIND(fp); FPCHR(fp,'{'); FTAB(fp,indent+2);
  fprintf
  (
    fp,"%d, %s%s, %d, ",
    PLR_T_IMP(PTab)->tabs.MstShiftCnt,
    PLR_T_IMP(PTab)->Kfg->language,SFX_MSTSHIFT,
    PLR_T_IMP(PTab)->tabs.DtlShiftCnt
  );
  if( PLR_T_IMP(PTab)->tabs.DtlShiftCnt )
    fprintf(fp,"%s%s,",PLR_T_IMP(PTab)->Kfg->language,SFX_DTLSHIFT);
  else fprintf(fp,"(int*)NULL,");
  FTAB(fp,indent+2);
  fprintf
  (
    fp,"%d, %s%s, %d, %s%s,",
    PLR_T_IMP(PTab)->tabs.GoToCnt,
    PLR_T_IMP(PTab)->Kfg->language,SFX_GOTO,
    PLR_T_IMP(PTab)->tabs.GoToDftCnt,
    PLR_T_IMP(PTab)->Kfg->language,SFX_GOTODFT
  );
  FTAB(fp,indent+2);
  fprintf
  (
    fp,"%d, %s%s, %d, ",
    PLR_T_IMP(PTab)->tabs.ActDftCnt,
    PLR_T_IMP(PTab)->Kfg->language,SFX_ACTDFT,
    PLR_T_IMP(PTab)->tabs.ActExpCnt
  );
  if( PLR_T_IMP(PTab)->tabs.ActExpCnt )
    fprintf(fp,"%s%s",PLR_T_IMP(PTab)->Kfg->language,SFX_ACTEXP);
  else fprintf(fp,"(int*)NULL");
  FNLIND(fp); fprintf(fp,"}"); 
  FPNLSNL(fp,"};"); FNL(fp);
  fprintf(fp,"PLR_Tab PLR_get_%s()\n",PLR_T_IMP(PTab)->Kfg->language);
  fprintf(fp,"/* simulates a PLR_getTab */");
  FNL(fp); FPCHR(fp,'{'); FNLIND(fp);
  fprintf
  (
    fp,"return( PLR_copyTab(&%s%s) );",
    PLR_T_IMP(PTab)->Kfg->language,SFX_PARSETAB
  );
  FPNLSNL(fp,"}");
}

void PLR_CTab_Modul(string Environ, PLR_Tab PTab, c_bool shortform)
#define PLR_printCTab PLR_CTab_Modul
/* creates source [$'Environ'/]<Language>_pim.c for parse table 'PTab' */
{ FILE* fp; c_string fid;

  BUG_NULL(PTab); BUG_NULL(PLR_T_IMP(PTab)->Kfg);
  BUG_NULL(PLR_T_IMP(PTab)->Kfg->language);
  if( shortform )
    fid = Str_printf("%.4s_pim.c",PLR_T_IMP(PTab)->Kfg->language);
  else
    fid = Str_printf("%s_pim.c",PLR_T_IMP(PTab)->Kfg->language);
  fp = OpenPath(Environ,fid,"","wt");
  PLR_CTab_Source(fp,fid,PTab);
  fclose(fp);
  FreeMem(fid);
}

void PLR_Src_Source(FILE* fp, c_string fid, PLR_Tab PTab)
/* writes source for parse table 'PTab' to file 'fp';
   produces a source header if filename 'fid' is not empty
*/
{ int cnt, scnt, i, j;
  if( !STR_EMPTY(fid) )
    fprintf
    (
      fp,"# [%s] Parser table for '%s'\n\n", 
      fid, PLR_T_IMP(PTab)->Kfg->language
    );
  fprintf(fp,"# CFG Definition\n\nKFGHEAD\n");
  fprintf(fp,"Name=%s\n",PLR_T_IMP(PTab)->Kfg->language);
  fprintf(fp,"TkCnt=%d\n",PLR_T_IMP(PTab)->Kfg->TkCnt);
  fprintf(fp,"NtCnt=%d\n",PLR_T_IMP(PTab)->Kfg->NtCnt);
  fprintf(fp,"SNames\n");
  cnt = PLR_T_IMP(PTab)->Kfg->TkCnt + PLR_T_IMP(PTab)->Kfg->NtCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp," %s\n",PLR_T_IMP(PTab)->Kfg->SNames[i]);
  }
  fprintf(fp,"StartIds\n");
  cnt = PLR_T_IMP(PTab)->Kfg->StartCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Kfg->StartIds[i]);
  }
  fprintf(fp,"TokKind\n");
  cnt = PLR_T_IMP(PTab)->Kfg->TkCnt + PLR_T_IMP(PTab)->Kfg->NtCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Kfg->TokKind[i]);
  }
  cnt = PLR_T_IMP(PTab)->Kfg->NtCnt;
  fprintf(fp,"NtClass\n");
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Kfg->NtClass[i]);
  }
  fprintf(fp,"ErrorNt\n");
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Kfg->ErrorNt[i]);
  }
  fprintf(fp,"\n# Productions\n\n");
  cnt = PLR_T_IMP(PTab)->ProdCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"KFGPROD\n");
    fprintf(fp,"pname=%s\n",PLR_T_IMP(PTab)->Prod[i].pname);
    fprintf(fp,"method=%d\n",PLR_T_IMP(PTab)->Prod[i].method);
    fprintf(fp,"id=%d\n",PLR_T_IMP(PTab)->Prod[i].id);
    scnt = PLR_T_IMP(PTab)->Prod[i].symcnt;
    fprintf(fp,"symbols\n");
    for( j=0; j < scnt; ++j )
    {
      fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Prod[i].symbols[j]);
    }
    fprintf(fp,"symfrms\n");
    for( j=0; j < scnt; ++j )
    {
      fprintf(fp,"%d\n",PLR_T_IMP(PTab)->Prod[i].symfrms[j]);
    }
  }
  fprintf(fp,"\n# LALR(1) tables\n\n");
  fprintf(fp,"MstShift\n");
  cnt = PLR_T_IMP(PTab)->tabs.MstShiftCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.MstShift[i]);
  }
  fprintf(fp,"DtlShift\n");
  cnt = PLR_T_IMP(PTab)->tabs.DtlShiftCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.DtlShift[i]);
  }
  fprintf(fp,"GoTo\n");
  cnt = PLR_T_IMP(PTab)->tabs.GoToCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.GoTo[i]);
  }
  fprintf(fp,"GoToDft\n");
  cnt = PLR_T_IMP(PTab)->tabs.GoToDftCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.GoToDft[i]);
  }
  fprintf(fp,"ActDft\n");
  cnt = PLR_T_IMP(PTab)->tabs.ActDftCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.ActDft[i]);
  }
  fprintf(fp,"ActExp\n");
  cnt = PLR_T_IMP(PTab)->tabs.ActExpCnt;
  for( i=0; i < cnt; ++i )
  {
    fprintf(fp,"%d\n",PLR_T_IMP(PTab)->tabs.ActExp[i]);
  }
  fprintf(fp,"\n");
}

void PLR_Src_Modul(string Environ, PLR_Tab PTab)
#define PLR_printCTab PLR_CTab_Modul
/* creates source [$'Environ'/]<Language>.ptbl for parse table 'PTab' */
{ FILE* fp; c_string fid;

  BUG_NULL(PTab); BUG_NULL(PLR_T_IMP(PTab)->Kfg);
  BUG_NULL(PLR_T_IMP(PTab)->Kfg->language);
  fid = Str_printf("%s.ltbl",PLR_T_IMP(PTab)->Kfg->language);
  fp = OpenPath(Environ,fid,"","wt");
  PLR_Src_Source(fp,fid,PTab);
  fclose(fp);
  FreeMem(fid);
}

/*I---------------------------- Binary Image -------------------------------- */

void PLR_fputTab_bin(BinImg_T img, PLR_Tab PTab)
/* unloads parse table 'PTab' 
   to binary image 'img' (reentrant)
*/
{ 
  BUG_NULL(PTab); BUG_NULL(PLR_T_IMP(PTab)->Kfg);
  fputKfgGlobals(img,PLR_T_IMP(PTab)->Kfg);
  fputKfgProds(img,PLR_T_IMP(PTab)->Prod,PLR_T_IMP(PTab)->ProdCnt);
  fputLalr1Tabs(img,&PLR_T_IMP(PTab)->tabs);
}

void PLR_putTab_bin(PLR_Tab PTab)
/* unloads parse table 'PTab' 
   to the current ( previously opened ) image 
*/
{ 
  PLR_fputTab_bin(BIN_getCurImage(),PTab);
}

void PLR_putTab(string Environ, PLR_Tab PTab)
/* unloads parse table 'PTab' to image [$'Environ'/]<Language>.pim */
{ BinImg_T img; string hd;

  BUG_NULL(PTab); BUG_NULL(PLR_T_IMP(PTab)->Kfg);
  BUG_NULL(PLR_T_IMP(PTab)->Kfg->language);
  img = fputBgn(Environ,PLR_T_IMP(PTab)->Kfg->language,".pim");
  hd = Str_printf
       (
         "[%s.pim] Binary Parser Image for %s\n",
         PLR_T_IMP(PTab)->Kfg->language,PLR_T_IMP(PTab)->Kfg->language
       );
  fputHeader(img,hd,"pim",1,0);
  PLR_fputTab_bin(img,PTab);
  FreeMem(hd);
  fputEnd(img);
}

PLR_Tab PLR_fgetTab_bin(BinImg_T img)
/* loads a parse table 
   from binary image 'img' (reentrant)
*/
{ PARSETAB* tab = (PARSETAB*)NewMem(sizeof(PARSETAB));

  tab->Kfg  = (KFGHEAD*)NewMem(sizeof(KFGHEAD));
  fgetKfgGlobals(img,tab->Kfg);
  fgetInt(img,&tab->ProdCnt);
  tab->Prod = (KFGPROD*)NewMem(sizeof(KFGPROD)*tab->ProdCnt);
  fgetKfgProds(img,tab->Prod,tab->ProdCnt);
  fgetLalr1Tabs(img,&tab->tabs);
  return( tab );
}

PLR_Tab PLR_getTab_bin(void)
/* loads a parse table 
   from the current ( previously opened ) image 
*/
{ 
  return PLR_fgetTab_bin(BIN_getCurImage());
}

PLR_Tab PLR_getTab(string Language)
/* loads a parse table named 'Language' 
   from image [$PATH/]<Language>.pim 
*/
{ PARSETAB* tab; 
  BinImg_T  img = fgetBgn("PATH",Language,".pim");
  fgetHeader(img,"pim",1,0);
  tab = (PARSETAB*)PLR_fgetTab_bin(img);
  fgetEnd(img);
  return( tab );
}

PLR_Tab PLR_getTab_env(string Environ, string Language)
/* loads a parse table named 'Language' 
   from image [$'Environ'/]<Language>.pim 
*/
{ PARSETAB* tab; 
  BinImg_T  img = fgetBgn(Environ,Language,".pim");
  fgetHeader(img,"pim",1,0);
  tab = (PARSETAB*)PLR_fgetTab_bin(img);
  fgetEnd(img);
  return( tab );
}

PLR_Tab PLR_getETab(Any_T Environ, string Language)
/* like PLR_getTab / PLR_getTab_env; 
   can be used as embedded language parser contructor
   ( see function 'PT_setEParser' )
*/
{
  if( STR_EMPTY((string)Environ) )
    return PLR_getTab(Language);
  else
    return PLR_getTab_env((string)Environ,Language);
}
