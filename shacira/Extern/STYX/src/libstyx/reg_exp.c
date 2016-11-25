/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [reg_exp.c]           Regular Expression Evaluation                      */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "symbols.h"
#include "scn_base.h"
#include "scn_imp.h"
#include "scn_gen.h"
#include "literal.h"
#include "otab.h"
#include "hmap.h"
#include "hset.h"
#include "sink.h"
#include "gstream.h"

#include "rexp_lim.h"

/*!
  <p>[reg_exp] implements a regular expression evaluator based on the
  following regular expression syntax.
  
  <p><b>Literal</b>
  <ul>
  <li>printable extended ascii character without quotes 
      ( quotes = { "'`\ } )
  <li>\ quote 
  <li>\r, \n, \t
  <li>\ hexdigit hexdigit
      ( single byte character )
  <li>\ (x|X) hexdigit hexdigit hexdigit hexdigit hexdigit hexdigit hexdigit hexdigit
      ( ucs4 character )
  </ul>
  <p><b>Construction</b>
  
  <table noborder cellspacing=10>
  <tr><td><b>Character set</b></td><td>' Literal ... '</td></tr>
  <tr><td><b>String</b></td><td>" Literal ... "</td></tr>
  <tr><td><b>Any character</b></td><td>.</td></tr>
  <tr><td><b>Character range</b></td>
      <td>Expression .. Expression <br>( single character expressions )</td></tr>
  <tr><td><b>Subexpression</b></td><td>( Expression )</td></tr>
  <tr><td><b>Option</b></td><td>[ Expression ]</td></tr>
  <tr><td>&nbsp;</td><td>Expression ?</td></tr>
  <tr><td><b>Iteration ( 0.. )</b></td><td>{ Expression }</td></tr>
  <tr><td>&nbsp;</td><td>Expression *</td></tr>
  <tr><td><b>Iteration ( 1.. )</b></td><td>Expression +</td></tr>
  <tr><td><b>Iteration ( n )</b></td><td>Expression Number</td></tr>
  <tr><td><b>Iteration ( n..m )</b></td><td>Expression Number, Number</td></tr>
  <tr><td><b>Union</b></td><td>Expression | Expression</td></tr>
  <tr><td><b>Difference</b></td><td>Expression - Expression</td></tr>
  <tr><td><b>Concatenation</b></td><td>Expression Expression</td></tr>
  </table>
*/

/*I-------------------- Types ------------------------------------------- */

ExternalType(Reg_T) // Abstract regular expression evaluation type
{
  Scn_T pRScn; // common Regular Expression Scanner 
  Scn_T pVScn; // special Regular Expression Scanner 
};


/*I-------------------- Creating & Disposing ---------------------------- */

static RegSet_T REG_String(c_string s)
{ RegSet_T reg; long len; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  reg = RegSet_StringN(tstring,len);
  FreeMem(tstring); 
  return reg;
}

static RegSet_T REG_Cset(c_string s)
{ RegSet_T reg; long len; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  reg = RegSet_CsetN(tstring,len);
  FreeMem(tstring); return reg;
}

static RegSet_T REG_self(RegSet_T pRegSet)
{
  return pRegSet;
}

static RegSet_T REG_plus(RegSet_T pRegSet)
{ RegSet_T pRes = RegSet_Plus(pRegSet);
  RegSet_Free(pRegSet);
  return pRes;
}

static RegSet_T REG_option(RegSet_T pRegSet)
{ RegSet_T pRes = RegSet_Option(pRegSet);
  RegSet_Free(pRegSet);
  return pRes;
}

static RegSet_T REG_star(RegSet_T pRegSet)
{ RegSet_T pRes = RegSet_Star(pRegSet);
  RegSet_Free(pRegSet);
  return pRes;
}

static RegSet_T REG_concat(RegSet_T pLeft, RegSet_T pRight)
{
  if( pLeft == (RegSet_T)NULL ) return pRight;
  else
  if( pRight == (RegSet_T)NULL ) return pLeft;
  else
  { RegSet_T pRes = RegSet_Concat(pLeft,pRight);
    RegSet_Free(pLeft); RegSet_Free(pRight);
    return pRes;
  }
}

static RegSet_T REG_diff(RegSet_T pLeft, RegSet_T pRight)
{ RegSet_T pRes = RegSet_Difference(pLeft,pRight);
  RegSet_Free(pLeft); RegSet_Free(pRight);
  return pRes;
}

static RegSet_T REG_union(RegSet_T pLeft, RegSet_T pRight)
{ RegSet_T pRes = RegSet_Union(pLeft,pRight);
  RegSet_Free(pLeft); RegSet_Free(pRight);
  return pRes;
}

static RegSet_T REG_range(RegSet_T pLeft, RegSet_T pRight)
{ RegSet_T pRes = (RegSet_T)NULL;
  wc_char  al, bu, x;
  if(RegSet_isChar(pLeft) && RegSet_isChar(pRight))
  {
    al = RegSet_charVal(pLeft);
    bu = RegSet_charVal(pRight);
    if (al > bu)
    { 
      x = al; al = bu; bu = x; 
    }
    pRes = RegSet_Range(al,bu);
  }
  RegSet_Free(pLeft); RegSet_Free(pRight);
  return pRes;
}

static RegSet_T REG_sigma(void)
/* FIXME: charset size */
{
  return RegSet_Range((wc_char)0,(wc_char)((wc_char)(SCN_CHAR_SET_SIZE)-(wc_char)1));
}

static RegSet_T REG_plus_limited(RegSet_T pRegSet, int nMax)
{ RegSet_T pRes = RegSet_Plus_ntimes(pRegSet,nMax);
  RegSet_Free(pRegSet);
  return pRes;
}

static RegSet_T REG_plus_range(RegSet_T pRegSet, int nMin, int nMax)
{ RegSet_T pRes = (RegSet_T)NULL;
  if( pRegSet != (RegSet_T)NULL )
  { int nI;
    pRes = REG_plus_limited(RegSet_Copy(pRegSet),nMin);
    for( nI=nMin+1; nI <= nMax; ++nI )
    { RegSet_T pTmp = REG_option(RegSet_Copy(pRegSet));
      pRes = REG_concat(pRes,pTmp);
    }
    RegSet_Free(pRegSet);
  }
  return pRes;
}

static void REG_freeExps(ROW(RegSet_T) pRegRow)
{ long lCnt = OT_CNT(pRegRow), lI;
  for( lI=0; lI < lCnt; ++lI )
    RegSet_Free(OT_GET(RegSet_T,pRegRow,lI));
  OT_CLEAR(pRegRow);
}

static RegSet_T REG_consExps(ROW(RegSet_T) pRegRow)
{ RegSet_T pRes = (RegSet_T)NULL, pRegSet;
  long     lCnt = OT_CNT(pRegRow), lI;
  if( lCnt == 0 ) pRes = RegSet_Empty();
  else
    for( lI=0; lI < lCnt; ++lI )
    {
      pRegSet = OT_GET(RegSet_T,pRegRow,lI);
      if( lI > 0 && pRes == (RegSet_T)NULL ) 
        RegSet_Free(pRegSet);
      else pRes = REG_concat(pRes,pRegSet);
    }
  OT_CLEAR(pRegRow);
  return pRes;
}

static void REG_getLimits(c_string szToken, int* pnMin, int* pnMax)
{ int nI;
  *pnMax = *pnMin = atoi(szToken);
  for( nI=0; szToken[nI] != '\0'; ++nI )
    if( szToken[nI] == ',' ) break;
  if( szToken[nI] != '\0' )
    for( ; szToken[nI] != '\0'; ++nI )
      if( isdigit(szToken[nI]) ) break;
  if( szToken[nI] != '\0' )
    *pnMax = atoi(&szToken[nI]);
}

static RegSet_T REG_Exp(Scn_Stream pStream, int cEnd)
{ ROW(RegSet_T) pRegRow = OT_CREATE_ADT(RegSet_T);
  RegSet_T      (*pBRegFun)(RegSet_T pL, RegSet_T pR) = NULL;
  RegSet_T      (*pURegFun)(RegSet_T pRegSet) = NULL;
  RegSet_T      pRes = (RegSet_T)NULL, pRegSet1, pRegSet2;
  long          lRng = 0;
  int           cSym = 0;
  for(Stream_next(pStream); Stream_ctid(pStream) > 0; Stream_next(pStream))
  { c_string szTxt = symbolToString(Stream_csym(pStream));
/*
  if( !Stream_unicode(pStream) ) printf("TXT=%s\n",szTxt);
  else GS_fprint_utf8(STDOUT,szTxt,C_True);
*/
    if (Stream_ctid(pStream) == 4) 
    { int nMin = -1, nMax = -1;
      if( OT_CNT(pRegRow) == 0 ) break;
      REG_getLimits(szTxt,&nMin,&nMax);
      pRegSet1 = OT_TOP(RegSet_T,pRegRow); OT_POP(pRegRow); 
      pRegSet1 = REG_plus_range(pRegSet1,nMin,nMax);
      if( pRegSet1 == (RegSet_T)NULL ) break;
      OT_PUSH(pRegSet1,pRegRow);
    }
    else
    if (Stream_ctid(pStream) == 1) 
    { 
      if( szTxt[0] == '+' || szTxt[0] == '*' || szTxt[0] == '?' )
      {
        if( OT_CNT(pRegRow) == 0 ) break;
        pRegSet1 = OT_TOP(RegSet_T,pRegRow); OT_POP(pRegRow); 
        pRegSet1 = szTxt[0]=='+'
                   ? REG_plus(pRegSet1)
                   : szTxt[0]=='*'
                     ? REG_plus(pRegSet1) : REG_option(pRegSet1);
        if( pRegSet1 == (RegSet_T)NULL ) break;
        OT_PUSH(pRegSet1,pRegRow);
      }
      else
      if( szTxt[0] == '.' && szTxt[1] == '.' ) 
      {
        if( OT_CNT(pRegRow) == 0 ) break;
        lRng = OT_CNT(pRegRow)+1;
      }
      else
      if( szTxt[0] == '|' || szTxt[0] == '-' )
      {
        if( OT_CNT(pRegRow) == 0 ) break;
        pBRegFun = szTxt[0] == '|' ? REG_union : REG_diff;
        pRegSet1 = REG_consExps(pRegRow);
        if( pRegSet1 == (RegSet_T)NULL ) break;
        pRegSet2 = REG_Exp(pStream,cEnd);
        if( pRegSet2 == (RegSet_T)NULL ) break;
        pRegSet1 = (*pBRegFun)(pRegSet1,pRegSet2);
        if( pRegSet1 == (RegSet_T)NULL ) break;
        OT_PUSH(pRegSet1,pRegRow);
        if( cEnd >= 0 ) { cSym = cEnd; break; }
      }
      else
      if( szTxt[0] == '.' ) 
      {
        pRegSet1 = REG_sigma();
        if( pRegSet1 == (RegSet_T)NULL ) break;
        OT_PUSH(pRegSet1,pRegRow);
      }
      else
      {
        if( szTxt[0] == '(' ) pURegFun = REG_self;
        else
        if( szTxt[0] == '{' ) pURegFun = REG_star;
        else
        if( szTxt[0] == '[' ) pURegFun = REG_option;
        else
        if( szTxt[0] == ')' || szTxt[0] == '}' || szTxt[0] == ']' )
        {
          cSym = (int)(szTxt[0]==')'?'(':szTxt[0]=='}'?'{':'['); break;
        }
        else C_BUG;
        pRegSet1 = REG_Exp(pStream, (int)szTxt[0]);
        if( pRegSet1 == (RegSet_T)NULL ) break;
        pRegSet1 = (*pURegFun)(pRegSet1);
        if( pRegSet1 == (RegSet_T)NULL ) break;
        OT_PUSH(pRegSet1,pRegRow);
      }
    }
    else
    { 
      pRegSet1 = ( Stream_ctid(pStream) == 2 )
                 ? REG_Cset(szTxt) : REG_String(szTxt);
      if( pRegSet1 == (RegSet_T)NULL ) break;
      OT_PUSH(pRegSet1,pRegRow);
    }
    if( lRng == OT_CNT(pRegRow) )
    {
      pRegSet1 = OT_TOP(RegSet_T,pRegRow); OT_POP(pRegRow);
      pRegSet2 = OT_TOP(RegSet_T,pRegRow); OT_POP(pRegRow);
      pRegSet1 = REG_range(pRegSet1,pRegSet2);
      if( pRegSet1 == (RegSet_T)NULL ) break;
      OT_PUSH(pRegSet1,pRegRow);
      lRng = 0;
    }
  }
  if( Stream_ctid(pStream) == -1 ) cSym = -1;
/*
  printf("RNG=%ld,SYM=%ld,END=%ld\n",lRng,cSym,cEnd);
*/
  if( lRng > 0 || cSym != cEnd ) REG_freeExps(pRegRow);
  else pRes = REG_consExps(pRegRow);
  OT_DEL_T(pRegRow);
  return pRes;
}

static Scn_T REG_Scanner
             (
               Scn_T pRScn, c_string szRegExp, long lLen, c_string szCharSet, c_byte ucFlags
             )
{ Scn_Stream pStream = (Scn_Stream)NULL;
  RegSet_T   pRegSet = (RegSet_T)NULL;
  Scn_T      pVScn   = (Scn_T)NULL;
  if( STR_EMPTY(szCharSet) )
  {
    if( lLen < 0 )
      pStream = Stream_string(pRScn, szRegExp);
    else
    { c_string szTmp = SubStrCopy(szRegExp,lLen);
      pStream = Stream_string(pRScn, szTmp);
      FreeMem(szTmp);
    }
  }
  else
  { Scn_Stream_Itr pItr = (Scn_Stream_Itr)NULL;
    GStream_T      pGS  = (GStream_T)NULL;
    pGS = GS_stream_string_new(szRegExp,lLen<0?strlen(szRegExp)+1:lLen,szCharSet);
    if( pGS != (GStream_T)NULL )
      pItr = Stream_Itr_new
             (
               GS_stream_get_wcrc, GS_fun_destruct(pGS), GS_ucs4_to_utf8, 
               GS_fun_seek(pGS), pGS, "<CSRegExp>"
             );
    if( pItr != (Scn_Stream_Itr)NULL )
    {
      pStream = Stream_bgn(pRScn,pItr);
      Stream_Itr_free(pItr);
    }
  }
  if( pStream != (Scn_Stream)NULL )
  {
    Stream_defEofId(pStream, -1);
    Stream_defErrId(pStream,  0);
    Stream_defTokId(pStream, "Opr"  , 1);
    Stream_defTokId(pStream, "Set"  , 2);
    Stream_defTokId(pStream, "Seq"  , 3);
    Stream_defTokId(pStream, "OprEx", 4);
    pRegSet = REG_Exp(pStream, -1);
    Stream_close(pStream);
    Stream_free(pStream);
    if( pRegSet != (RegSet_T)NULL )
    {
      Scn_dfnBegin("REG");
      Scn_dfnToken("exp",ucFlags,pRegSet);
      pVScn = Scn_dfnEnd(False);
      RegSet_Free(pRegSet);
    }
  }
  return pVScn;
}

void REG_drop(Reg_T pReg)
/* removes regular expression evaluator 'pReg' */
{
  if( pReg != (Reg_T)NULL )
  {
    Scn_free(pReg->pRScn);
    if( pReg->pVScn != (Scn_T)NULL ) Scn_free(pReg->pVScn);
    FreeMem(pReg);
  }
}

Reg_T REG_create
      (
        c_string szRegExp,  long   lLen, 
        c_string szCharSet, c_bool bIgnCase
      )
#define REG_CREATE(exp)  REG_create((exp),-1,(c_string)NULL,C_False)
#define IREG_CREATE(exp) REG_create((exp),-1,(c_string)NULL,C_True)
/* creates a regular expression evaluator from string 'szRegExp' 
   'lLen'     : -1 or string size in bytes, incl. terminating bytes
   'szCharSet': NULL,"" or character set name 
                ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   'szCharSet' = NULL,"" --> single byte string
   'lLen' = -1 --> null-terminated single byte or utf8 string
   RC: evaluator or NULL
*/
{ Reg_T  pReg = New(Reg_T); 
  c_byte ica  = (c_byte)(bIgnCase?SCN_FLG_IgnoreCase:0);
  Scn_get_rexp(&pReg->pRScn);
  pReg->pVScn = REG_Scanner(pReg->pRScn,szRegExp,lLen,szCharSet,ica);
  if( pReg->pVScn == (Scn_T)NULL )
  {
    REG_drop(pReg); return (Reg_T)NULL;
  }
  return pReg;
}

c_bool REG_recreate
       (
         Reg_T    pReg,      c_string szRegExp, long lLen, 
         c_string szCharSet, c_bool   bIgnCase
       )
#define REG_RECREATE(reg,exp)  REG_recreate((reg),(exp),-1,(c_string)NULL,C_False)
#define IREG_RECREATE(reg,exp) REG_recreate((reg),(exp),-1,(c_string)NULL,C_True)
/* updates regular expression evaluator 'pReg' 
   from string 'szRegExp' 
   ( 'lLen', 'szCharSet' --> see function 'REG_create' )
   RC: true <--> OK
*/
{ c_byte ica  = (c_byte)(bIgnCase?SCN_FLG_IgnoreCase:0);
  BUG_NULL(pReg);
  if( pReg->pVScn != (Scn_T)NULL )
    Scn_free(pReg->pVScn);
  pReg->pVScn = REG_Scanner(pReg->pRScn,szRegExp,lLen,szCharSet,ica);
  return( pReg->pVScn != (Scn_T)NULL );
}

/*I------------------------- Evaluation --------------------------------- */

c_string REG_match
         (
           Reg_T    pReg, 
           c_string szTxt,  long lTxtLen, c_string szCharSet, 
           long*    lPatLen
         )
#define REG_MATCH(reg,txt,len) REG_match((reg),(txt),-1,(c_string)NULL,(len))
/* applies regular expression evaluator 'pReg' to string 'szTxt'
   ( 'lTxtLen', 'szCharSet' --> see function 'REG_create' )
   RC: start postion of first matched value in 'szTxt' or NULL 
   'lPatLen' != NULL --> length of first matched value in bytes
*/
{ c_string     szRes = (c_string)NULL, szTok;
  long         lIdx  = 0, lTmp;
  GStream_T    pGS   = (GStream_T)NULL;
  BUG_NULL(pReg);
  if( pReg->pVScn != (Scn_T)NULL && szTxt != (c_string)NULL )
  { Scn_Stream pStream = (Scn_Stream)NULL;
    if( STR_EMPTY(szCharSet) )
    {
      if( lTxtLen < 0 )
        pStream = Stream_string(pReg->pVScn, szTxt);
      else
      { c_string szTmp = SubStrCopy(szTxt,lTxtLen);
        pStream = Stream_string(pReg->pVScn, szTmp);
        FreeMem(szTmp);
      }
    }
    else
    { Scn_Stream_Itr pItr = (Scn_Stream_Itr)NULL;
      if( lTxtLen < 0 ) lTxtLen = strlen(szTxt)+1;
      pGS = GS_stream_string_new(szTxt,lTxtLen,szCharSet);
      if( pGS != (GStream_T)NULL )
        pItr = Stream_Itr_new
               (
                 GS_stream_get_wcrc, GS_fun_destruct(pGS), GS_ucs4_to_utf8, 
                 GS_fun_seek(pGS), pGS, "<CSMatch>"
               );
      if( pItr != (Scn_Stream_Itr)NULL )
      {
        pStream = Stream_bgn(pReg->pVScn,pItr);
        Stream_Itr_free(pItr);
      }
    }
    if( pStream != (Scn_Stream)NULL )
    {
      Stream_concat_other(pStream);
      Stream_defEofId(pStream, -1);
      Stream_defErrId(pStream,  0);
      Stream_defTokId(pStream, "exp", 1);
      for(Stream_next(pStream); Stream_ctid(pStream) >= 0; Stream_next(pStream))
      {
        szTok = symbolToString(Stream_csym(pStream));
        if (Stream_ctid(pStream) == 1) 
        {
          if( lPatLen != (long*)NULL ) 
          {
            if( STR_EMPTY(szCharSet) ) *lPatLen = strlen(szTok);
            else 
            {
              if( GS_stream_bytepos(pGS,(unsigned int*)((StdCPtr)&lTmp)) != 0 ) 
                break;
              assert0(lTmp <= lTxtLen,"");
              *lPatLen = lTmp - lIdx;
            }
          }
          szRes = szTxt + lIdx;
          break;
        }
        else 
        {
          if( STR_EMPTY(szCharSet) ) lIdx += strlen(szTok);
          else
          {
            if( GS_stream_bytepos(pGS,(unsigned int*)((StdCPtr)&lIdx)) != 0 )
              break;
            assert0(lIdx <= lTxtLen,"");
          }
        }
      }
      Stream_close(pStream);
      Stream_free(pStream);
    }
  }
  return szRes;
}

