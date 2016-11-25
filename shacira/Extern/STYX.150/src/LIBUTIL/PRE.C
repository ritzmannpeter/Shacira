/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [pre.c]                   Preprocessing Facility                           */
/*                                                                            */
/* Copyright (c) 1993 by Lars D\olle, Heike Manns                             */
/*----------------------------------------------------------------------------*/

#include "standard.h"   

#include "pathes.h"   
#include "symbols.h"   
#include "hmap.h"   


/*!!
   This module, [pre], realises a simple text processor. It supports the
   usage of macros which will be expanded during processing - by the result
   of the corresponding special replacement functions.

   The following rules describes the source text format:

   Text :: Literal
        :: "&&"
        :: "&" MacroName "&"
        :: "&" "IF" FlagName "&" Text 
          ["&" "ELSE" "&" Text]
           "&" "FI" "&"
        :: Text Text

   Literal   :: Each printable ASCII-character beside "&", additionally "\n" und "\f".
   MacroName :: (Literal-"&"-" "-"\n"-"\f")+ .
                Beside that the reserved words "IF","ELSE","FI" are not allowed.
   FlagName  :: like MacroName; MacroName and FlagName must be disjunct sets.

   Now the interpretation can be specified as follows:

   A literal identifies itself, i.e. will be taken as is.

   '&&' will be expanded to '&'.

   '&MacroName&' forces the call of the corresponding evaluation function to output
   the replacement text for the macro. The left border is the column with the first "&".
   
   With the IF-THEN-ELSE-FI construction conditional generation becomes possible.
   FlagName refers to the corresponding boolean evaluation function. On true the text
   after '&IF FlagName& will be processed, otherwise the optional '&ELSE&'-part.

   Internally the following generalisation of the grammar will be used:

   Text :: Literal
        :: "&&"
        :: "&" MacroName "&"
        :: "&" KeyWord [FlagName] "&"
        :: Text Text

*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                               Symbol Table                                 */
/*                               - Level 2 -                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define aMacro    1
#define aFlag     2
#define aKeyWord  3

static MAPTY                          gloty;
static MAP(symbol, void (*Meaning)()) gloact;
static MAP(symbol, int  Meaning)      gloknd;

void PRE_dfnMacro(string MacroName, void (* Macro)())
/* defines macro with name 'MacroName' and meaning 'Macro' */
{ symbol s = stringToSymbol(MacroName);
  bug1(!MAP_defined(gloknd,s),
       "duplicated symbol definition '%s'",MacroName);
  MAP_dfndom(gloknd,s,aMacro);
  MAP_dfndom(gloact,s, Macro);
}

void PRE_dfnFlag(string FlagName, int (* Flag)())
/* defines flag with name 'FlagName' and meaning 'Flag' */
{ symbol s = stringToSymbol(FlagName);
  bug1(!MAP_defined(gloknd,s),
       "duplicated symbol definition '%s'",FlagName);
  MAP_dfndom(gloknd,s,aFlag);
  MAP_dfndom(gloact,s, Flag);
}

static void dfnKeyWord(string KeyWord, void (* KeyAct)(string Parm))
/* Defines keyword with name KeyWord and meaning KeyAct */
{ symbol s = stringToSymbol(KeyWord);
  bug1(!MAP_defined(gloknd,s),
       "duplicated symbol definition '%s'",KeyWord);
  MAP_dfndom(gloknd,s,aKeyWord);
  MAP_dfndom(gloact,s, KeyAct );
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                           Character Separation                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

static string fileid;
static FILE *SysIn,*SysOut;

static int cLineNo;                                 /* Current Line Number   */
static int cColumnNo;                               /* Current Column Number */
static int cC;                                      /* Current Character     */

static int tLineNo;                        /* Line number of current token   */
static int tColumnNo;                      /* Column number of current token */
static int tToken;                         /* Current token                  */

static int ErrorCount = 0;    /* Error counting                              */
#define MaxErrors 25          /* Large enought, anyway                       */

static void syntax(string Reason)
/* Emit a syntactical error message                                          */
/* Note that we require the source to be bug-free.                           */
/* Thus, if we ever reach this routine while generating, we better terminate */
{
  fprintf(STDERR,"\n");
  fprintf(STDERR,"%s(%d,%d): %s\n", fileid,tLineNo,tColumnNo,Reason);
  ErrorCount += 1;
  assert0(ErrorCount < MaxErrors,"too many errors. Validate source");
}

static void getChar(void)
/* gets on character, keeps cursor location */
{
  bug0(cC != EOF, "reading past end of file");
  cColumnNo += 1;
  if (cC == '\n')
  { cLineNo += 1; cColumnNo  = 1; }
  cC = fgetc(SysIn);
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              Token Separation                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define MacChar '&'                         /* Macro Character                */

#define MacTok (-2)            /* Value for tToken if we got a &...&          */

#define MaxMacroChars 129      /* Maximum number of characters between &'s    */
static char MacroLine[MaxMacroChars]; /* Buffer for text between &'s          */

static void getToken(void)
/* gets one token, which is either a literal character, EOF or &ANY& */
{ char *s;
  retry: /* on error */

    tLineNo   = cLineNo;
    tColumnNo = cColumnNo;
  
  if (cC == MacChar)
  { int topmac = 0; /* first free location in MacroLine */
    for( getChar(); cC != MacChar && ! iscntrl(cC); getChar() )
      if (topmac < MaxMacroChars-1)
        MacroLine[topmac++] = cC;
    if (topmac >= MaxMacroChars-1)
    {
      syntax("macro too long");
      goto retry;
    }
    if (cC == '&')
      getChar();
    else
    {
      MacroLine[topmac] = '\0';
      syntax("non-terminated macro"); fprintf(STDERR,">%s<\n",MacroLine);
      goto retry;
    }
    MacroLine[topmac] = '\0';
    for (s = MacroLine; *s; s++)
      //if (*s > 126)
      if( ! ( isascii(*s) && isprint(*s) ) )
      {
        syntax("macro contains invalid characters");
        goto retry;
      }
    tToken = MacTok;
    return;
  }
  if (cC == EOF)
  {
    tToken = cC; return;
  }
  //if (cC == '\n' || cC == '\f' || ' ' <= cC && cC <= 126)
  if (cC == '\n' || cC == '\f' || ( isascii(cC) && isprint(cC) ) )
  {
    tToken = cC; getChar(); return;
  }
  syntax("invalid character");
  goto retry;
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              Keyword Semantik                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define MaxStackEntries 10 /* Maximum level for IF-FI-nesting */
static struct StackEntry
{
  int    sLine;                             /* line and ...                   */
  int    sColumn;                           /* column of starting IF          */
  bool   sCond;                             /* evaluated condition            */
  bool   sBranch;                           /* true after IF false after ELSE */
} Stack[MaxStackEntries];
static int TopStack;

static bool Generating; /* whether we actually have to generate output */

static void UpdateGenerating(void)
/* whether the source is to appear in output */
{ int i;
  Generating = True;
  for (i = 0; i < TopStack; i++)
    Generating &= (Stack[i].sBranch == Stack[i].sCond);
}

static void doIF(string Flag)
/* process the Keyword "IF" */
{ symbol Fsy = stringToSymbol(Flag);
  assert0(TopStack < MaxStackEntries,"IF - nesting too deep");
  Stack[TopStack].sLine   = tLineNo;
  Stack[TopStack].sColumn = tColumnNo;
  Stack[TopStack].sBranch = True;
  if( !MAP_defined(gloknd,Fsy) || MAP_apply(int, gloknd, Fsy) != aFlag)
    syntax("Flag not recognized");
  else
    Stack[TopStack].sCond = MAP_apply(bool(*)(), gloact,Fsy)();
  TopStack += 1;
  UpdateGenerating();
}

static void doELSE(string Parm)
/* process the Keyword "ELSE" */
{
  if (*Parm) syntax("ELSE has not parameters");
  if (TopStack <= 0 || !Stack[TopStack-1].sBranch)
  {
    syntax("ELSE without IF"); return; 
  }
  Stack[TopStack-1].sBranch = False;
  UpdateGenerating();
}

static void doFI(string Parm)
/* process the Keyword "FI" */
{
  if (*Parm) syntax("FI has not parameters");
  if (TopStack <= 0)
  {
    syntax("FI without IF"); return; 
  }
  else
    TopStack -= 1;
  UpdateGenerating();
}

static void doSTX(string environ, string file, string ext, FILE *fileout)
/* call before reading */
{
  fileid = MkPath(environ,file,ext,'$');
  SysIn  = OpenPath(environ,file,ext,"rt");
  SysOut = fileout;
  cC = fgetc(SysIn);
  cLineNo   = 1;
  cColumnNo = 1;
  tLineNo   = 1;
  tColumnNo = 1;
  TopStack  = 0;
  UpdateGenerating();
}

static void doETX(void)
/* called when eof reached */
{
  for (;TopStack > 0; TopStack--)
  {
    fprintf(STDERR,"\n");
    fprintf(STDERR,"%s(%d,%d): IF without FI\n",
                   fileid,Stack[TopStack-1].sLine,Stack[TopStack-1].sColumn);
    ErrorCount += 1;
  }
  fclose(SysIn);
}

static void initKeyWords(void)
{
  dfnKeyWord("IF"  ,doIF  );
  dfnKeyWord("ELSE",doELSE);
  dfnKeyWord("FI"  ,doFI  );
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              Macro - Semantik                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

static void ProcessMacro(void)
/* Processes MacroLine */
{ char *FirstWord, *Remainder; /* To contain the separation result */
  { char *scan_in = MacroLine;
    char *scan_end = MacroLine+strlen(MacroLine);
    if (strlen(MacroLine) == 0)
    {
      if (Generating)
        fputc(MacChar,SysOut);
      return;
    }
    /* We separate the MacroLine into two words.                     */
    /* To this end, we remove leading and trailing spaces and        */
    /* the spaces behind the first word.                             */
    for (; MacroLine < scan_end && scan_end[-1] == ' '; scan_end-- );
    *scan_end = '\0';
    for (; *scan_in && *scan_in == ' '; scan_in++ );
    FirstWord = scan_in;
    for (; *scan_in && *scan_in != ' '; scan_in++ );
    scan_end = scan_in;
    for (; *scan_in && *scan_in == ' '; scan_in++ );
    Remainder = scan_in;
    *scan_end = '\0';
  }
  { symbol id = stringToSymbol(FirstWord);
    if (!MAP_defined(gloknd,id))
      syntax("unknown macro");
    else
    switch (MAP_apply(int,gloknd,id))
    {
      case aMacro   : if (*Remainder) syntax("Text after a macro");
                      if (Generating) MAP_apply(void(*)(),gloact,id)();
                      break;
      case aKeyWord : /* we process in any case, thus we shift the burden */
                      /* of mode distinction to the keyword handler       */
                      MAP_apply(void(*)(string),gloact,id)(Remainder);
                      if (cC == '\n') getChar();
                      break;
      case aFlag    : syntax("Flag must not be the first word");
                      break;
      default       : bug(False,"Did you define some new kinds symbols?");
    }
  }
}

void PRE_Process(string environ, string file, string ext, FILE *fileout)
/* preprocesses module [$'environ'/'file''ext'] to file 'fileout' */
{
  doSTX(environ,file,ext,fileout);
  for (getToken(); tToken != EOF; getToken())
    if (tToken == MacTok)
      ProcessMacro();
    else
    if (Generating)
    {
      fputc(tToken,SysOut);
    }
  doETX();
}

void PRE_init(void)
/* enter the preprocessor module */
{
  gloty  = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  gloact = MAP_newMap( gloty );
  gloknd = MAP_newMap( gloty );
  initKeyWords();
}

void PRE_quit(void)
/* leave the preprocessor module */
{
  FreeMem(fileid);
  MAP_freeMap( gloact );
  MAP_freeMap( gloknd );
  MAP_freeTyp( gloty  );
}

int PRE_tColumnNo(void)
/* column number of current token */
{
  return tColumnNo;
}
