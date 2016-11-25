/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_abs.c]           Abstract Scanner Interface                         */
/*                                                                          */
/* Copyright (c) 2002 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "symbols.h"


/*!
   <p>This module [scn_abs] provides an abstract scanner interface for the
   term generation module <a href="ptm_gen.htm">[ptm_gen]</a>. 
   <p>It can be used to integrate an externally defined scanner with the STYX term
   generation facility.
*/

/*I----------------------------- The Types --------------------------------- */

ExternalDecl(AbsScn_T); /* Abstract scanner interface type */


/*!! 
  Types of the scanner (interface) functions 
*/
/*DOC_INTERFACE*/
typedef void     (*SF_scan      )(Abs_T scanner);
typedef short    (*SF_tok       )(Abs_T scanner);
typedef symbol   (*SF_symbol    )(Abs_T scanner);
typedef long     (*SF_pos       )(Abs_T scanner);
typedef c_bool   (*SF_flag      )(Abs_T scanner);
typedef void     (*SF_defID     )(Abs_T scanner, short id);
typedef void     (*SF_defTxtID  )(Abs_T scanner, c_string text, short id);
typedef void     (*SF_defWCTxtID)(Abs_T scanner, wc_string text, short id);
typedef Any_T    (*SIF_eTerm    )
                 (
                   Abs_T CurPTCfg, c_string language, c_string StartSymbol
                 );
typedef c_bool   (*SIF_eAccept  )(Abs_T CurPTCfg);


ConcreteImp(AbsScn_T) /* Scanner interface type (implementation) */
{
  Abs_T         extScn;     /* ext. scanner                      */
  SF_scan       nextTok;    /* CB for Stream_next                */
  SF_tok        tokID;      /* CB for Stream_ctid                */
  SF_symbol     tokSym;     /* CB for Stream_csym                */
  SF_symbol     streamSym;  /* CB for Stream_cfil                */
  SF_pos        tokRow;     /* CB for Stream_clin                */
  SF_pos        tokCol;     /* CB for Stream_ccol                */
  SF_flag       unicode;    /* CB for Stream_unicode             */
  SF_defID      defEofID;   /* CB for Stream_defEofId            */
  SF_defID      defErrID;   /* CB for Stream_defErrId            */
  SF_defTxtID   defTokID;   /* CB for Stream_defTokId            */
  SF_defTxtID   defKeyID;   /* CB for Stream_defKeyId            */
  SF_defWCTxtID defWCKeyID; /* CB for Stream_defWCKeyId          */
  Abs_T         CurPTCfg;   /* current parse term configuration  */
  SIF_eTerm     eTerm;      /* CB for the construction of        */
                            /* an embedded language token        */
  SIF_eAccept   eAccept;    /* CB for the recognition of         */
                            /* an embedded language accept token */
};


/*I---------------------------- Init & Quit -------------------------------- */

AbsScn_T AS_init(void)
/* creates an abstract scanner interface */
{ AbsScn_T sconfig = New(AbsScn_T);
  sconfig->extScn     = (Abs_T)NULL;
  sconfig->nextTok    = (SF_scan)NULL;
  sconfig->tokID      = (SF_tok)NULL;
  sconfig->tokSym     = (SF_symbol)NULL;
  sconfig->streamSym  = (SF_symbol)NULL;
  sconfig->tokRow     = (SF_pos)NULL;
  sconfig->tokCol     = (SF_pos)NULL;
  sconfig->unicode    = (SF_flag)NULL;
  sconfig->defEofID   = (SF_defID)NULL;
  sconfig->defErrID   = (SF_defID)NULL;
  sconfig->defTokID   = (SF_defTxtID)NULL;
  sconfig->defKeyID   = (SF_defTxtID)NULL;
  sconfig->defWCKeyID = (SF_defWCTxtID)NULL;
  sconfig->CurPTCfg   = (Abs_T)NULL;
  sconfig->eTerm      = (SIF_eTerm)NULL;
  sconfig->eAccept    = (SIF_eAccept)NULL;
  return sconfig;
}

void AS_quit(AbsScn_T sconfig)
/* removes abstract scanner interface 'sconfig' */
{
  if( sconfig != (AbsScn_T)NULL ) 
    FreeMem(sconfig);
}


/*I-------------- Specification of the external scanner interface ---------- */

void AS_setScanner(AbsScn_T sconfig, Abs_T scanner)
/* specifies the external 'scanner' of the abstract interface 'sconfig' 
   ( see Scn_Stream )
*/
{
  BUG_NULL(sconfig);
  sconfig->extScn = scanner;
}

/*!
  <p>An external defined scanner must provide the following interface 
     functions. They have to be assigned to the abstract scanner interface 
     before initializing the term generation. That module calls them
     during the construction of the derivation tree.
*/

void AS_setFunNextTok(AbsScn_T sconfig, SF_scan nextTok)
/* specifies 'nextTok' as corresponding function for Stream_next 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->nextTok = nextTok;
}

void AS_setFunTokID(AbsScn_T sconfig, SF_tok tokID)
/* specifies 'tokID' as corresponding function for Stream_ctid 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->tokID = tokID;
}

void AS_setFunTokSym(AbsScn_T sconfig, SF_symbol tokSym)
/* specifies 'tokSym' as corresponding function for Stream_csym 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->tokSym = tokSym;
}

void AS_setFunStreamSym(AbsScn_T sconfig, SF_symbol streamSym)
/* specifies 'streamSym' as corresponding function for Stream_cfil 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->streamSym = streamSym;
}

void AS_setFunTokRow(AbsScn_T sconfig, SF_pos tokRow)
/* specifies 'tokRow' as corresponding function for Stream_clin 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->tokRow = tokRow;
}

void AS_setFunTokCol(AbsScn_T sconfig, SF_pos tokCol)
/* specifies 'tokCol' as corresponding function for Stream_ccol 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->tokCol = tokCol;
}

void AS_setFunUnicode(AbsScn_T sconfig, SF_flag unicode)
/* specifies 'tokCol' as corresponding function for Stream_ccol 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->unicode = unicode;
}

void AS_setFunDefEofID(AbsScn_T sconfig, SF_defID defEofID)
/* specifies 'defEofID' as corresponding function for Stream_defEofId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->defEofID = defEofID;
}

void AS_setFunDefErrID(AbsScn_T sconfig, SF_defID defErrID)
/* specifies 'defErrID' as corresponding function for Stream_defErrId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->defErrID = defErrID;
}

void AS_setFunDefTokID(AbsScn_T sconfig, SF_defTxtID defTokID)
/* specifies 'defTokID' as corresponding function for Stream_defTokId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->defTokID = defTokID;
}

void AS_setFunDefKeyID(AbsScn_T sconfig, SF_defTxtID defKeyID)
/* specifies 'defKeyID' as corresponding function for Stream_defKeyId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->defKeyID = defKeyID;
}

void AS_setFunDefWCKeyID(AbsScn_T sconfig, SF_defWCTxtID defWCKeyID)
/* specifies 'defWCKeyID' as corresponding function for Stream_defWCKeyId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->defWCKeyID = defWCKeyID;
}

/*!
  <p>An external defined scanner must call the following handler
     to construct an embedded language token. 
     This handler will be set by the term construction module.
*/

void AS_setETermInfo
     (
       AbsScn_T sconfig, Abs_T CurPTCfg, SIF_eTerm eTerm, SIF_eAccept eAccept
     )
/* specifies 'eTerm' as embedded language token constructor and
   'eAccept' as embedded language accept token recognizer
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  sconfig->CurPTCfg = CurPTCfg;
  sconfig->eTerm    = eTerm;
  sconfig->eAccept  = eAccept;
}


/*I-------------- Accessing the external scanner interface ----------------- */

Abs_T AS_getScanner(AbsScn_T sconfig)
/* get the external scanner of the abstract interface 'sconfig' */
{
  BUG_NULL(sconfig);
  return sconfig->extScn;
}

SF_scan AS_getFunNextTok(AbsScn_T sconfig)
/* get the corresponding function for Stream_next 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->nextTok;
}

SF_tok AS_getFunTokID(AbsScn_T sconfig)
/* get the corresponding function for Stream_ctid 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->tokID;
}

SF_symbol AS_getFunTokSym(AbsScn_T sconfig)
/* get the corresponding function for Stream_csym 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->tokSym;
}

SF_symbol AS_getFunStreamSym(AbsScn_T sconfig)
/* get the corresponding function for Stream_cfil 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->streamSym;
}

SF_pos AS_getFunTokRow(AbsScn_T sconfig)
/* get the corresponding function for Stream_clin 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->tokRow;
}

SF_pos AS_getFunTokCol(AbsScn_T sconfig)
/* get the corresponding function for Stream_ccol 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->tokCol;
}

SF_flag AS_getFunUnicode(AbsScn_T sconfig)
/* get the corresponding function for Stream_ccol 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->unicode;
}

SF_defID AS_getFunDefEofID(AbsScn_T sconfig)
/* get the corresponding function for Stream_defEofId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->defEofID;
}

SF_defID AS_getFunDefErrID(AbsScn_T sconfig)
/* get the corresponding function for Stream_defErrId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->defErrID;
}

SF_defTxtID AS_getFunDefTokID(AbsScn_T sconfig)
/* get the corresponding function for Stream_defTokId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->defTokID;
}

SF_defTxtID AS_getFunDefKeyID(AbsScn_T sconfig)
/* get the corresponding function for Stream_defKeyId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->defKeyID;
}

SF_defWCTxtID AS_getFunDefWCKeyID(AbsScn_T sconfig)
/* get the corresponding function for Stream_defWCKeyId 
   in the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->defWCKeyID;
}

SIF_eTerm AS_getFunETerm(AbsScn_T sconfig)
/* get the embedded language token constructor
   from the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->eTerm;
}

SIF_eAccept AS_getEofETerm(AbsScn_T sconfig)
/* get the embedded language accept token recognizer
   from the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->eAccept;
}

Abs_T AS_getCurPTCfg(AbsScn_T sconfig)
/* get the current parse term configuration
   from the abstract interface 'sconfig'
*/
{
  BUG_NULL(sconfig);
  return sconfig->CurPTCfg;
}
