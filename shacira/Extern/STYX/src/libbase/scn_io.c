/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_io.c]             Scanner Definition Primimitives                   */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* TODO                                                                     */
/*                                                                          */
/* - Add a Scn_usageEof together with a character set size                  */
/* - cdefeof --> cdeftok                                                    */

#include "standard.h"
#include "binimg.h"

#include "scn_imp.h"
#include "pathes.h"
#include "sink.h"
#include "line_scn.h"

/*!!
   Beside copying and disposing of scanner definitions 
   this module provides functions that 
   1) generate a C module for a given scanner definition
   2) unload a scanner definition to a binary image file 
   3) load a scanner definition from a binary image file.
*/

/*I------------------------------ Types & Macros ---------------------------- */

/*!
  <p><b>Identifier of other other</b>
  <p><br>Separator between token ID and pattern<b>
*/

/*DOC_INTERFACE*/
#define SCN_TOK_Other            "[other]"
#define SCN_SEP_TOK_ID_PATTERN   '@'

AbstractType( Scn_T ); /* Abstract scanner type */

/*I------------------------------ Basics ------------------------------------ */

string Scn_LanguageId(Scn_T x)
/* language or group name of scanner definition 'x' */
{
  return Scn_IMP(x)->Name;
}

Scn_T Scn_copy(Scn_T x)
/* copies scanner definition 'x' */
{ scn_t scn = Scn_IMP(x); int i;
  scn_t res;
  res = New(scn_t);
  res->Name    = StrCopy(scn->Name);
  res->States  = scn->States;
  res->Tokens  = scn->Tokens;
  res->Groups  = scn->Groups;
  res->dyckcnt = scn->dyckcnt;
  if( scn->Groups == 0 )
  {
    res->StaEdg  = (long   *)BytCopy(scn->StaEdg,(scn->States+1) * sizeof(long   ));
    res->StaFin  = (short  *)BytCopy(scn->StaFin,scn->States     * sizeof(short  ));
    res->EdgeC   = (wc_char*)BytCopy(scn->EdgeC, SCN_Edges(scn)  * sizeof(wc_char));
    res->EdgeS   = (long   *)BytCopy(scn->EdgeS, SCN_Edges(scn)  * sizeof(long   ));
    res->TokId   = (string *)NewMem(             scn->Tokens     * sizeof(string ));
    for(i = 0; i < scn->Tokens; i++)
      res->TokId[i] = StrCopy(scn->TokId[i]);
    res->Flags   = (byte   *)BytCopy(scn->Flags, scn->Tokens     * sizeof(byte   ));
    if( scn->Switch != (short*)NULL )
      res->Switch = (short*)BytCopy(scn->Switch, scn->Tokens * sizeof(short));
    else
      res->Switch = (short  *)NULL;
    res->GrpScn = (scn_t*)NULL;
  }
  else
  {
    res->StaEdg  = (long   *)NULL;
    res->StaFin  = (short  *)NULL;
    res->EdgeC   = (wc_char*)NULL;
    res->EdgeS   = (long   *)NULL;
    res->TokId   = (string *)NULL;
    res->Flags   = (byte   *)NULL;
    res->Switch  = (short  *)NULL;
    res->GrpScn  = (scn_t*)NewMem(scn->Groups * sizeof(scn_t));
    for(i = 0; i < scn->Groups; i++)
      res->GrpScn[i] = Scn_copy(scn->GrpScn[i]);
  }
  if( res->dyckcnt > 0 )
  {
    res->dyckidx = (short*)BytCopy(scn->dyckidx,scn->dyckcnt * sizeof(short   ));
    res->dyckpat = (scn_t*)NewMem(scn->dyckcnt * sizeof(scn_t));
    for( i = 0; i < scn->dyckcnt; ++i )
      res->dyckpat[i] = Scn_copy(scn->dyckpat[i]);
  }
  else
  {
    res->dyckidx = (short*)NULL;
    res->dyckpat = (scn_t*)NULL;
  }
  return Scn_ADT(res);
}

void Scn_free(Scn_T x)
/* frees scanner definition 'x' */
{ scn_t scn = Scn_IMP(x); int i;
  FreeMem(scn->Name);
  if( scn->Groups == 0 )
  {
    FreeMem(scn->StaEdg);
    FreeMem(scn->StaFin);
    FreeMem(scn->EdgeC);
    FreeMem(scn->EdgeS);
    for(i = 0; i < scn->Tokens; i++)
      FreeMem(scn->TokId[i]);
    FreeMem(scn->TokId);
    FreeMem(scn->Flags);
    if( scn->Switch != (short*)NULL )
      FreeMem(scn->Switch);
  }
  else
  {
    for(i = 0; i < scn->Groups; i++)
      Scn_free(scn->GrpScn[i]);
    FreeMem(scn->GrpScn);
  }
  if( scn->dyckcnt > 0 )
  {
    FreeMem(scn->dyckidx);
    for(i = 0; i < scn->dyckcnt; i++)
      Scn_free(scn->dyckpat[i]);
    FreeMem(scn->dyckpat);
  }
  FreeMem(scn);
}

/*I----------------------------- Binary Image ------------------------------- */

Scn_T Scn_fget_bin(BinImg_T img)
/* loads a scanner definition 
   from binary image 'img' (reentrant)
*/
{ byte flg; int i; scn_t scn; unsigned long ul;
  scn = New(scn_t);
  fgetString(img,&scn->Name);
  fgetWord(img,&scn->States);
  fgetWord(img,&scn->Tokens);
  fgetWord(img,&scn->Groups);
  if( scn->Groups == 0 )
  {
    scn->StaEdg = (long*)NewMem( (scn->States+1) * sizeof(long) );
    for (i = 0; i < scn->States+1; i++) fgetLong(img,&scn->StaEdg[i]);
    scn->StaFin = (short*)NewMem( scn->States * sizeof(short) );
    for (i = 0; i < scn->States; i++) fgetWord(img,&scn->StaFin[i]);
    scn->EdgeC = (wc_char*)NewMem( sizeof(wc_char ) * SCN_Edges(scn) );
    for (i = 0; i < SCN_Edges(scn); i++)
    { 
      fgetULong(img,&ul);
      scn->EdgeC[i] = (wc_char)ul;
    }
    scn->EdgeS = (long*)NewMem( sizeof(long) * SCN_Edges(scn) );
    for (i = 0; i < SCN_Edges(scn); i++) fgetLong(img,&scn->EdgeS[i]);
    scn->TokId = (string*)NewMem( sizeof(string) * scn->Tokens );
    for (i = 0; i < scn->Tokens; i++) fgetString(img,&scn->TokId[i]);
    scn->Flags = (byte*)NewMem( sizeof(byte) * scn->Tokens );
    for (i = 0; i < scn->Tokens; i++) fgetByte(img,&scn->Flags[i]);
    fgetByte(img,&flg);
    if( flg )
    {
      scn->Switch = (short*)NewMem(scn->Tokens*sizeof(short));
      for (i = 0; i < scn->Tokens; i++) fgetWord(img,&scn->Switch[i]);
    }
    else
      scn->Switch = (short*)NULL;
    scn->GrpScn = (scn_t*)NULL;
  }
  else
  {
    scn->StaEdg  = (long   *)NULL;
    scn->StaFin  = (short  *)NULL;
    scn->EdgeC   = (wc_char*)NULL;
    scn->EdgeS   = (long   *)NULL;
    scn->TokId   = (string *)NULL;
    scn->Flags   = (byte   *)NULL;
    scn->Switch  = (short  *)NULL;
    scn->GrpScn  = (scn_t*)NewMem(scn->Groups * sizeof(scn_t));
    for(i = 0; i < scn->Groups; i++)
      scn->GrpScn[i] = Scn_fget_bin(img);
  }
  fgetWord(img,&scn->dyckcnt);
  if( scn->dyckcnt > 0 )
  {
    scn->dyckidx = (short*)NewMem(scn->dyckcnt * sizeof(short));
    scn->dyckpat = (scn_t*)NewMem(scn->dyckcnt * sizeof(c_string));
    for( i = 0; i < scn->dyckcnt; ++i )
      fgetWord(img,&scn->dyckidx[i]);
    for( i = 0; i < scn->dyckcnt; ++i )
      scn->dyckpat[i] = Scn_fget_bin(img);
  }
  else
  {
    scn->dyckidx = (short*)NULL;
    scn->dyckpat = (scn_t*)NULL;
  }
  return scn;
}

Scn_T Scn_get_bin(void)
/* loads a scanner definition 
   from the current ( previously opened ) image
*/
{ 
  return Scn_fget_bin(BIN_getCurImage());
}

void Scn_get(string Language, Scn_T *x)
/* loads a scanner definition named 'Language' into 'x'
   from image [$PATH/]<Language>.lim
*/
{ BinImg_T img = fgetBgn("PATH",Language,".lim");
  fgetHeader(img,"lim",1,0);
  *x = Scn_fget_bin(img);
  fgetEnd(img);
}

void Scn_get_env(string Environ, string Language, Scn_T *x)
/* loads a scanner definition named 'Language' into 'x'
   from image [$'Environ'/]<Language>.lim
*/
{ BinImg_T img = fgetBgn(Environ,Language,".lim");
  fgetHeader(img,"lim",1,0);
  *x = Scn_fget_bin(img);
  fgetEnd(img);
}

void Scn_get_file(string file, Scn_T *x)
/* loads a scanner definition from 'file' into 'x'
*/
{ BinImg_T img = fgetBgn("",file,"");
  fgetHeader(img,"lim",1,0);
  *x = Scn_fget_bin(img);
  fgetEnd(img);
}

void Scn_fput_bin(BinImg_T img, Scn_T x)
/* unloads scanner definition 'x'
   to binary image 'img' (reentrant)
*/
{ int i; scn_t scn = Scn_IMP(x);
  fputString(img,scn->Name);
  fputWord(img,scn->States);
  fputWord(img,scn->Tokens);
  fputWord(img,scn->Groups);
  if( scn->Groups == 0 )
  {
    for (i = 0; i < scn->States+1 ; i++) fputLong  (img,scn->StaEdg[i]);
    for (i = 0; i < scn->States   ; i++) fputWord  (img,scn->StaFin[i]);
    for (i = 0; i < SCN_Edges(scn); i++) fputULong (img,(unsigned long)scn->EdgeC[i]);
    for (i = 0; i < SCN_Edges(scn); i++) fputLong  (img,scn->EdgeS [i]);
    for (i = 0; i < scn->Tokens   ; i++) fputString(img,scn->TokId [i]);
    for (i = 0; i < scn->Tokens   ; i++) fputByte  (img,scn->Flags [i]);
    if( scn->Switch != (short*)NULL )
    {
      fputByte(img,1);
      for (i = 0; i < scn->Tokens; i++) fputWord(img,scn->Switch[i]);
    }
    else fputByte(img,0);
  }
  else
  {
    for(i = 0; i < scn->Groups; i++)
      Scn_fput_bin(img,scn->GrpScn[i]);
  }
  fputWord(img,scn->dyckcnt);
  if( scn->dyckcnt > 0 )
  {
    for (i = 0; i < scn->dyckcnt; i++) fputWord(img,scn->dyckidx[i]);
    for (i = 0; i < scn->dyckcnt; i++) Scn_fput_bin(img,scn->dyckpat[i]);
  }
}

void Scn_put_bin(Scn_T x)
/* unloads scanner definition 'x'
   to the current ( previously opened ) image
*/
{ 
  Scn_fput_bin(BIN_getCurImage(),x);
}

void Scn_put(c_string Environ, Scn_T x)
/* unloads scanner definition 'x'
   to image [$'Environ'/]<Language>.lim
*/
{ string hd; scn_t scn = Scn_IMP(x);
  BinImg_T img = fputBgn(Environ,scn->Name,".lim");
  hd = Str_printf
       (
         "[%s.lim] Binary scanner image for '%s'\n", scn->Name, scn->Name
       );
  fputHeader(img,hd,"lim",1,0);
  Scn_fput_bin(img,x);
  FreeMem(hd);
  fputEnd(img);
}

/*I----------------------------- C-Module ----------------------------------- */

static void Scn_C_SourceScanner(FILE* fp, Scn_T x)
/* writes source for ( group ) scanner definition 'x' to file 'fp'
*/
{ int i; scn_t scn = Scn_IMP(x);
  if( scn->Groups == 0 )
  {
    fprintf(fp,"static long %sStaEdg[%d] =\n",scn->Name,scn->States+1);
    fprintf(fp,"/* first edge per state */\n");
    fprintf(fp,"{\n  ");
    for (i = 0; i < scn->States+1; i++)
    {
      fprintf(fp,"%9ld",scn->StaEdg[i]);
      if (             i+1 < scn->States+1) fprintf(fp,",");
      if (i%6 != 5 && i+1 < scn->States+1) fprintf(fp," ");
      if (i%6 == 5 && i+1 < scn->States+1) fprintf(fp,"\n  ");
    }
    fprintf(fp,"\n};\n\n");
    fprintf(fp,"static short %sStaFin[%d] =\n",scn->Name,scn->States);
    fprintf(fp,"/* finite token per state */\n");
    fprintf(fp,"{\n  ");
    for (i = 0; i < scn->States; i++)
    {
      fprintf(fp,"%3d",scn->StaFin[i]);
      if (             i+1 < scn->States) fprintf(fp,",");
      if (i%10 != 9 && i+1 < scn->States) fprintf(fp," ");
      if (i%10 == 9 && i+1 < scn->States) fprintf(fp,"\n  ");
    }
    fprintf(fp,"\n};\n\n");
    fprintf(fp,"static wc_char %sEdgeC[%ld] =\n",scn->Name,SCN_Edges(scn));
    fprintf(fp,"/* lowest character per edge */\n");
    fprintf(fp,"{ /*State*/\n");
    for (i = 0; i < scn->States; i++)
    { long j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
      fprintf(fp,"  /* %3d */", i);
      for (j = 0; j < ed; j++)
      { long bgn = scn->StaEdg[i];
        fprintf(fp,"  %9ld",(long int)scn->EdgeC[bgn+j]);
        if (             bgn+j+1 < SCN_Edges(scn)) fprintf(fp,",");
        if (j%6 == 5 && bgn+j+1 < SCN_Edges(scn) && j+1 < ed)
          fprintf(fp,"\n           ");
      }
      fprintf(fp,"\n");
    }
    fprintf(fp,"};\n\n");
    fprintf(fp,"static long %sEdgeS[%ld] =\n",scn->Name,SCN_Edges(scn));
    fprintf(fp,"/* follow (state+1) per edge */\n");
    fprintf(fp,"{ /*State*/\n");
    for (i = 0; i < scn->States; i++)
    { long j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
      fprintf(fp,"  /* %3d */", i);
      for (j = 0; j < ed; j++)
      { long bgn = scn->StaEdg[i];
        fprintf(fp," %9ld",scn->EdgeS[bgn+j]);
        if (             bgn+j+1 < SCN_Edges(scn)) fprintf(fp,",");
        if (j%6 == 5 && bgn+j+1 < SCN_Edges(scn) && j+1 < ed)
          fprintf(fp,"\n           ");
      }
      fprintf(fp,"\n");
    }
    fprintf(fp,"};\n\n");
    fprintf(fp,"static string %sTokens[%d] =\n", scn->Name,scn->Tokens);
    fprintf(fp,"/* token -> string */\n");
    fprintf(fp,"{\n");
    for (i = 0; i < scn->Tokens; i++)
      fprintf(fp,"  \"%s\"%s\n",scn->TokId[i],i+1<scn->Tokens?",":"");
    fprintf(fp,"};\n\n");
    fprintf(fp,"static byte %sFlags[%d] =\n", scn->Name,scn->Tokens);
    fprintf(fp,"/* token -> newid */\n");
    fprintf(fp,"{\n  ");
    for (i = 0; i < scn->Tokens; i++)
    {
      fprintf(fp,"0x%02x", scn->Flags[i]);
      if (i+1 < scn->Tokens)                fprintf(fp,", ");
      if (i%10 == 9 && (i+1 < scn->Tokens)) fprintf(fp,"\n  ");
    }
    fprintf(fp,"\n};\n\n");
    if( scn->Switch != (short*)NULL )
    {
      fprintf(fp,"static short %sSwitch[%d] =\n", scn->Name,scn->Tokens);
      fprintf(fp,"/* token -> group to activate */\n");
      fprintf(fp,"{\n  ");
      for (i = 0; i < scn->Tokens; i++)
      {
        fprintf(fp,"%3d",scn->Switch[i]);
        if (             i+1 < scn->Tokens) fprintf(fp,",");
        if (i%10 != 9 && i+1 < scn->Tokens) fprintf(fp," ");
        if (i%10 == 9 && i+1 < scn->Tokens) fprintf(fp,"\n  ");
      }
      fprintf(fp,"\n};\n\n");
    }
  }
  else
  {
    fprintf(fp,"static scn_t %sGrpScn[%d] =\n", scn->Name,scn->Groups);
    fprintf(fp,"/* group -> scanner */\n");
    fprintf(fp,"{\n");
    for( i=0; i < scn->Groups; ++i )
      fprintf(fp,"  &%sScanner%s\n",scn->GrpScn[i]->Name,i+1<scn->Groups?",":"");
    fprintf(fp,"};\n\n");
  }
  if( scn->dyckcnt > 0 )
  {
    for( i=0; i < scn->dyckcnt; ++i )
    {
      fprintf(fp,"/* dyck scanner '%s' */\n\n",scn->dyckpat[i]->Name);
      Scn_C_SourceScanner(fp,scn->dyckpat[i]);
    }
    fprintf(fp,"static short %sDyckTokens[%d] =\n", scn->Name,scn->dyckcnt);
    fprintf(fp,"/* dyck token reference ( left paranthesis ) */\n");
    fprintf(fp,"{\n  ");
    for( i=0; i < scn->dyckcnt; ++i )
    {
      fprintf(fp,"%d",scn->dyckidx[i]);
      if (i+1 < scn->dyckcnt)                fprintf(fp,", ");
      if (i%10 == 9 && (i+1 < scn->dyckcnt)) fprintf(fp,"\n  ");
    }
    fprintf(fp,"\n};\n\n");
    fprintf(fp,"static scn_t %sDyckScanners[%d] =\n", scn->Name,scn->dyckcnt);
    fprintf(fp,"/* dyck scanners */\n");
    fprintf(fp,"{\n  ");
    for( i=0; i < scn->dyckcnt; ++i )
    {
      fprintf(fp,"  &%sScanner%s\n",scn->dyckpat[i]->Name,i+1<scn->dyckcnt?",":"");
    }
    fprintf(fp,"\n};\n\n");
  }
  fprintf(fp,"static ConcreteImp(scn_t) %sScanner =\n",scn->Name);
  fprintf(fp,"/* the scanner structure */\n");
  fprintf(fp,"{\n");
  fprintf(fp,"  \"%s\", /* Name    */\n",scn->Name   );
  fprintf(fp,"  %2d,%*s /* States  */\n",scn->States , (int)strlen(scn->Name), "");
  fprintf(fp,"  %2d,%*s /* Tokens  */\n",scn->Tokens , (int)strlen(scn->Name), "");
  if( scn->Groups == 0 )
  {
    fprintf(fp,"  %sStaEdg,\n",scn->Name);
    fprintf(fp,"  %sStaFin,\n",scn->Name);
    fprintf(fp,"  %sEdgeC,\n",scn->Name);
    fprintf(fp,"  %sEdgeS,\n",scn->Name);
    fprintf(fp,"  %sTokens,\n",scn->Name);
    fprintf(fp,"  %sFlags,\n",scn->Name);
  }
  else
  {
    fprintf(fp,"  (long*)NULL,\n");
    fprintf(fp,"  (short*)NULL,\n");
    fprintf(fp,"  (wc_char*)NULL,\n");
    fprintf(fp,"  (long*)NULL,\n");
    fprintf(fp,"  (c_string*)NULL,\n");
    fprintf(fp,"  (c_byte*)NULL,\n");
  }
  fprintf(fp,"  %2d,%*s /* Groups  */\n",scn->Groups , (int)strlen(scn->Name), "");
  if( scn->Groups == 0 )
  {
    fprintf(fp,"  (scn_t*)NULL,\n");
    if( scn->Switch != (short*)NULL )
      fprintf(fp,"  %sSwitch,\n",scn->Name);
    else
      fprintf(fp,"  (short*)NULL,\n");
  }
  else
  {
    fprintf(fp,"  %sGrpScn,\n",scn->Name);
    fprintf(fp,"  (short*)NULL,\n");
  }
  fprintf(fp,"  %d, /* Dyck */\n",scn->dyckcnt);
  if( scn->dyckcnt > 0 )
  {
    fprintf(fp,"  %sDyckTokens,\n",scn->Name);
    fprintf(fp,"  %sDyckScanners\n",scn->Name);
  }
  else
  {
    fprintf(fp,"  (short*)NULL,\n");
    fprintf(fp,"  (scn_t*)NULL\n");
  }
  fprintf(fp,"};\n\n");
}


void Scn_C_Source(FILE* fp, c_string fid, Scn_T x)
/* writes source for scanner ( group ) definition 'x' to file 'fp';
   produces a source header if filename 'fid' is not empty
*/
{ int i; scn_t scn = Scn_IMP(x);
  if( !STR_EMPTY(fid) )
    fprintf(fp,"/* [%s] Scanner table for '%s'  */\n\n", fid, scn->Name);
  fprintf(fp,"#include \"scn_io.h\"\n\n");
  fprintf(fp,"#include \"scn_imp.h\"\n\n");
  for( i=0; i < scn->Groups; ++i )
  {
    fprintf(fp,"/* group scanner '%s' */\n\n",scn->GrpScn[i]->Name);
    Scn_C_SourceScanner(fp,scn->GrpScn[i]);
  }
  fprintf(fp,"/* scanner group '%s' */\n\n",scn->Name);
  Scn_C_SourceScanner(fp, x);
  fprintf(fp,"\n");
  fprintf(fp,"void Scn_get_%s(Scn_T *scn)\n",scn->Name);
  fprintf(fp,"/* simulates a Scn_get */\n");
  fprintf(fp,"{\n");
  fprintf(fp,"  *scn = Scn_copy(Scn_ADT(&%sScanner));\n",scn->Name);
  fprintf(fp,"}\n");
}

void Scn_C_Modul(c_string Environ, Scn_T x, c_bool shortform)
/* creates source [$'Environ'/]<Language>_lim.c 
   for scanner ( group ) definition 'x'
*/
{ FILE *tf; c_string fid;
  scn_t scn = Scn_IMP(x);
  if( shortform )
    fid = Str_printf("%.4s_lim.c",scn->Name);
  else
    fid = Str_printf("%s_lim.c",scn->Name);
  tf = OpenPath(Environ,fid,"","wt");
  Scn_C_Source(tf,fid,x);
  fclose(tf);
  FreeMem(fid);
}


static void Scn_Src_SourceScanner
            (
              FILE* fp, Scn_T x, c_string prefix, c_string suffix
            )
/* writes source for ( group ) scanner definition 'x' to file 'fp'
*/
{ int i; scn_t scn = Scn_IMP(x);
  c_string nl = ( !STR_EMPTY(prefix) && !STR_EMPTY(suffix) ) ? "\\n" : "";
  fprintf(fp,"%sName=%s%s%s\n",prefix,scn->Name,nl,suffix);
  if( scn->Groups == 0 )
  {
    fprintf(fp,"%sStaEdg%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->States+1; i++)
    {
      fprintf(fp,"%s%ld%s%s\n",prefix,scn->StaEdg[i],nl,suffix);
    }
    fprintf(fp,"%sStaFin%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->States; i++)
    {
      fprintf(fp,"%s%d%s%s\n",prefix,scn->StaFin[i],nl,suffix);
    }
    fprintf(fp,"%sEdgeC%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->States; i++)
    { long j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
      for (j = 0; j < ed; j++)
      { long bgn = scn->StaEdg[i];
        fprintf(fp,"%s%ld%s%s\n",prefix,(long int)scn->EdgeC[bgn+j],nl,suffix);
      }
    }
    fprintf(fp,"%sEdgeS%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->States; i++)
    { long j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
      for (j = 0; j < ed; j++)
      { long bgn = scn->StaEdg[i];
        fprintf(fp,"%s%ld%s%s\n",prefix,scn->EdgeS[bgn+j],nl,suffix);
      }
    }
    fprintf(fp,"%sTokId%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->Tokens; i++)
      fprintf(fp,"%s %s%s%s\n",prefix,scn->TokId[i],nl,suffix);
    fprintf(fp,"%sFlags%s%s\n",prefix,nl,suffix);
    for (i = 0; i < scn->Tokens; i++)
    {
      fprintf(fp,"%s%d%s%s\n", prefix,(int)scn->Flags[i],nl,suffix);
    }
    if( scn->Switch != (short*)NULL )
    {
      fprintf(fp,"%sSwitch%s%s\n",prefix,nl,suffix);
      for (i = 0; i < scn->Tokens; i++)
      {
        fprintf(fp,"%s%d%s%s\n",prefix,scn->Switch[i],nl,suffix);
      }
    }
  }
  if( scn->dyckcnt > 0 )
  {
    for( i=0; i < scn->dyckcnt; ++i )
    {
      fprintf
      (
        fp,"%s# dyck scanner '%s'%s%s%s\n\n%sDyck%s%s\n",
        prefix,scn->dyckpat[i]->Name,nl,nl,suffix,prefix,nl,suffix
      );
      Scn_Src_SourceScanner(fp,scn->dyckpat[i],prefix,suffix);
    }
    fprintf(fp,"%sDyckToken%s%s\n",prefix,nl,suffix);
    for( i=0; i < scn->dyckcnt; ++i )
    {
      fprintf(fp,"%s%d%s%s\n",prefix,scn->dyckidx[i],nl,suffix);
    }
  }
}


void Scn_Src_Source
     (
       FILE* fp, c_string fid, Scn_T x, c_string prefix, c_string suffix
     )
/* writes source for scanner ( group ) definition 'x' to file 'fp';
   produces a source header if filename 'fid' is not empty;
   encapsulates output lines with 'prefix' and 'suffix'
*/
{ int i; scn_t scn = Scn_IMP(x);
  c_string nl = ( !STR_EMPTY(prefix) && !STR_EMPTY(suffix) ) ? "\\n" : "";
  if( !STR_EMPTY(fid) )
    fprintf
    (
      fp,"%s# [%s] Scanner table for '%s'%s%s%s\n\n",
      prefix,fid,scn->Name,nl,nl,suffix
    );
  for( i=0; i < scn->Groups; ++i )
  {
    fprintf
    (
      fp,"%s# group scanner '%s'%s%s%s\n\n%sGroup%s%s\n",
      prefix,scn->GrpScn[i]->Name,nl,nl,suffix,prefix,nl,suffix
    );
    Scn_Src_SourceScanner(fp,scn->GrpScn[i],prefix,suffix);
  }
  fprintf
  (
    fp,"%s# scanner group '%s'%s%s%s\n\n%sLanguage%s%s\n",
    prefix,scn->Name,nl,nl,suffix,prefix,nl,suffix
  );
  Scn_Src_SourceScanner(fp,x,prefix,suffix);
  fprintf(fp,"%s%s%s\n",prefix,nl,suffix);
}

void Scn_Src_Modul(c_string Environ, Scn_T x, string Template)
/* creates source [$'Environ'/]<Language>.ltbl
   for scanner ( group ) definition 'x';
   it uses the template file for the export, if 'Template' is a regular file 
*/
{ FILE *tf = NULL; c_string fid;
  scn_t scn = Scn_IMP(x);
  fid = Str_printf("%s.ltbl",scn->Name);
  tf = OpenPath(Environ,fid,"","wt");
  if( STR_EMPTY(Template) ) Scn_Src_Source(tf,fid,x,"","");
  else
  { FILE* pf = NULL; c_string line;
    pf = OpnFile(Template,"rt");
    while( (line=Line_get(pf)) != (c_string)NULL )
    { c_string prefix, suffix;
      if( Line_split(line,"@TABLE@",&prefix,&suffix) )
      {
        fprintf(tf,"%sltbl%s%s\n",prefix?prefix:"",scn->Name,suffix?suffix:"");
      }
      else
      if( Line_split(line,"@LINE@",&prefix,&suffix) )
      {
        if( prefix != (c_string)NULL && suffix != (c_string)NULL )
          Scn_Src_Source(tf,fid,x,prefix,suffix);
        else
        if( prefix != (c_string)NULL )
          Scn_Src_Source(tf,fid,x,prefix,"");
        else
        if( suffix != (c_string)NULL )
          Scn_Src_Source(tf,fid,x,"",suffix);
        else
          Scn_Src_Source(tf,fid,x,"","");
      }
      else fprintf(tf,"%s\n",line);
      if( prefix != (c_string)NULL ) FreeMem(prefix);
      if( suffix != (c_string)NULL ) FreeMem(suffix);
      FreeMem(line);
    }
    fclose(pf);
  }
  fclose(tf);
  FreeMem(fid);
}
