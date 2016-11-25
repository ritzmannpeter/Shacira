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
*/

/*DOC_INTERFACE*/
#define SCN_TOK_Other "[other]"

AbstractType( Scn_T ); /* Abstract scanner type */

/*I------------------------------ Basics ------------------------------------ */

string Scn_LanguageId(Scn_T x)
/* language name of scanner definition 'x' */
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
  res->StaEdg  = (short  *)BytCopy(scn->StaEdg,(scn->States+1) * sizeof(short  ));
  res->StaFin  = (short  *)BytCopy(scn->StaFin,scn->States     * sizeof(short  ));
  res->EdgeC   = (wc_char*)BytCopy(scn->EdgeC, SCN_Edges(scn)  * sizeof(wc_char));
  res->EdgeS   = (short  *)BytCopy(scn->EdgeS, SCN_Edges(scn)  * sizeof(short  ));
  res->TokId   = (string *)NewMem(             scn->Tokens     * sizeof(string ));
  for(i = 0; i < scn->Tokens; i++)
    res->TokId[i] = StrCopy(scn->TokId[i]);
  res->Flags   = (byte*)BytCopy(scn->Flags,  scn->Tokens     * sizeof(byte  ));
  return Scn_ADT(res);
}

void Scn_free(Scn_T x)
/* frees scanner definition 'x' */
{ scn_t scn = Scn_IMP(x); int i;
  FreeMem(scn->Name);
  FreeMem(scn->StaEdg);
  FreeMem(scn->StaFin);
  FreeMem(scn->EdgeC);
  FreeMem(scn->EdgeS);
  for(i = 0; i < scn->Tokens; i++)
    FreeMem(scn->TokId[i]);
  FreeMem(scn->TokId);
  FreeMem(scn->Flags);
  FreeMem(scn);
}

/*I----------------------------- Binary Image ------------------------------- */

Scn_T Scn_fget_bin(BinImg_T img)
/* loads a scanner definition 
   from binary image 'img' (reentrant)
*/
{ int i; scn_t scn;
  scn = New(scn_t);
  fgetString(img,&scn->Name);
  fgetWord(img,&scn->States);
  fgetWord(img,&scn->Tokens);
  scn->StaEdg = (short*)NewMem( (scn->States+1) * sizeof(short) );
  for (i = 0; i < scn->States+1; i++) fgetWord(img,&scn->StaEdg[i]);
  scn->StaFin = (short*)NewMem( scn->States * sizeof(short) );
  for (i = 0; i < scn->States; i++) fgetWord(img,&scn->StaFin[i]);
  scn->EdgeC = (wc_char*)NewMem( sizeof(wc_char )  * SCN_Edges(scn) );
  for (i = 0; i < SCN_Edges(scn); i++)
  { unsigned long ul;
    fgetULong(img,&ul);
    scn->EdgeC[i] = (wc_char)ul;
  }
  scn->EdgeS = (short*)NewMem( sizeof(short) * SCN_Edges(scn) );
  for (i = 0; i < SCN_Edges(scn); i++) fgetWord(img,&scn->EdgeS[i]);
  scn->TokId = (string*)NewMem( sizeof(string) * scn->Tokens );
  for (i = 0; i < scn->Tokens; i++) fgetString(img,&scn->TokId[i]);
  scn->Flags = (byte*)NewMem( sizeof(byte) * scn->Tokens );
  for (i = 0; i < scn->Tokens; i++) fgetByte(img,&scn->Flags[i]);
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

void Scn_fput_bin(BinImg_T img, Scn_T x)
/* unloads scanner definition 'x'
   to binary image 'img' (reentrant)
*/
{ int i; scn_t scn = Scn_IMP(x);
  fputString(img,scn->Name);
  fputWord(img,scn->States);
  fputWord(img,scn->Tokens);
  for (i = 0; i < scn->States+1 ; i++) fputWord  (img,scn->StaEdg[i]);
  for (i = 0; i < scn->States   ; i++) fputWord  (img,scn->StaFin[i]);
  for (i = 0; i < SCN_Edges(scn); i++) fputULong (img,(unsigned long)scn->EdgeC [i]);
  for (i = 0; i < SCN_Edges(scn); i++) fputWord  (img,scn->EdgeS [i]);
  for (i = 0; i < scn->Tokens   ; i++) fputString(img,scn->TokId [i]);
  for (i = 0; i < scn->Tokens   ; i++) fputByte  (img,scn->Flags[i]);
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

void Scn_C_Source(FILE* fp, c_string fid, Scn_T x)
/* writes source for scanner definition 'x' to file 'fp';
   produces a source header if filename 'fid' is not empty
*/
{ int i; scn_t scn = Scn_IMP(x);
  if( !STR_EMPTY(fid) )
    fprintf(fp,"/* [%s] Scanner table for '%s'  */\n\n", fid, scn->Name);
  fprintf(fp,"#include \"scn_io.h\"\n\n");
  fprintf(fp,"#include \"scn_imp.h\"\n\n");
  fprintf(fp,"static short StaEdg[%d] =\n",scn->States+1);
  fprintf(fp,"/* first edge per state */\n");
  fprintf(fp,"{\n  ");
  for (i = 0; i < scn->States+1; i++)
  {
    fprintf(fp,"%3d",scn->StaEdg[i]);
    if (             i+1 < scn->States+1) fprintf(fp,",");
    if (i%10 != 9 && i+1 < scn->States+1) fprintf(fp," ");
    if (i%10 == 9 && i+1 < scn->States+1) fprintf(fp,"\n  ");
  }
  fprintf(fp,"\n};\n\n");
  fprintf(fp,"static short StaFin[%d] =\n",scn->States);
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
  fprintf(fp,"static wc_char EdgeC[%d] =\n",SCN_Edges(scn));
  fprintf(fp,"/* lowest character per edge */\n");
  fprintf(fp,"{ /*State*/\n");
  for (i = 0; i < scn->States; i++)
  { int j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
    fprintf(fp,"  /* %3d */", i);
    for (j = 0; j < ed; j++)
    { int bgn = scn->StaEdg[i];
      fprintf(fp,"  %9ld",scn->EdgeC[bgn+j]);
      if (             bgn+j+1 < SCN_Edges(scn)) fprintf(fp,",");
      if (j%8 == 7 && bgn+j+1 < SCN_Edges(scn) && j+1 < ed)
        fprintf(fp,"\n           ");
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"};\n\n");
  fprintf(fp,"static short EdgeS[%d] =\n",SCN_Edges(scn));
  fprintf(fp,"/* follow (state+1) per edge */\n");
  fprintf(fp,"{ /*State*/\n");
  for (i = 0; i < scn->States; i++)
  { int j, ed = scn->StaEdg[i+1] - scn->StaEdg[i];
    fprintf(fp,"  /* %3d */", i);
    for (j = 0; j < ed; j++)
    { int bgn = scn->StaEdg[i];
      fprintf(fp," %3d",scn->EdgeS[bgn+j]);
      if (             bgn+j+1 < SCN_Edges(scn)) fprintf(fp,",");
      if (j%10 == 9 && bgn+j+1 < SCN_Edges(scn) && j+1 < ed)
        fprintf(fp,"\n           ");
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"};\n\n");
  fprintf(fp,"static string Tokens[%d] =\n", scn->Tokens);
  fprintf(fp,"/* token -> string */\n");
  fprintf(fp,"{\n");
  for (i = 0; i < scn->Tokens; i++)
    fprintf(fp,"  \"%s\"%s\n",scn->TokId[i],i+1<scn->Tokens?",":"");
  fprintf(fp,"};\n\n");
  fprintf(fp,"static byte Flags[%d] =\n", scn->Tokens);
  fprintf(fp,"/* token -> newid */\n");
  fprintf(fp,"{\n  ");
  for (i = 0; i < scn->Tokens; i++)
  {
    fprintf(fp,"0x%02x", scn->Flags[i]);
    if (i+1 < scn->Tokens)                fprintf(fp,", ");
    if (i%10 == 9 && (i+1 < scn->Tokens)) fprintf(fp,"\n  ");
  }
  fprintf(fp,"\n};\n\n");
  fprintf(fp,"static ConcreteImp(scn_t) Scanner =\n");
  fprintf(fp,"/* the scanner structure */\n");
  fprintf(fp,"{\n");
  fprintf(fp,"  \"%s\", /* Name    */\n",scn->Name   );
  fprintf(fp,"  %2d,%*s /* States  */\n",scn->States , strlen(scn->Name), "");
  fprintf(fp,"  %2d,%*s /* Tokens  */\n",scn->Tokens , strlen(scn->Name), "");
  fprintf(fp,"  StaEdg,\n");
  fprintf(fp,"  StaFin,\n");
  fprintf(fp,"  EdgeC,\n");
  fprintf(fp,"  EdgeS,\n");
  fprintf(fp,"  Tokens,\n");
  fprintf(fp,"  Flags,\n");
  fprintf(fp,"};\n\n");
  fprintf(fp,"void Scn_get_%s(Scn_T *scn)\n",scn->Name);
  fprintf(fp,"/* simulates a Scn_get */\n");
  fprintf(fp,"{\n");
  fprintf(fp,"  *scn = Scn_copy(Scn_ADT(&Scanner));\n");
  fprintf(fp,"}\n");
}

void Scn_C_Modul(c_string Environ, Scn_T x)
/* creates source [$'Environ'/]<Language>_lim.c 
   for scanner definition 'x'
*/
{ FILE *tf; char fid[11];
  scn_t scn = Scn_IMP(x);
  sprintf(fid,"%.4s_lim.c",scn->Name);
  tf = OpenPath(Environ,fid,"","wt");
  Scn_C_Source(tf,fid,x);
  fclose(tf);
}
