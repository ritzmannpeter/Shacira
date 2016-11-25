// ===========================================================================
// eb_cmdarg.cpp                                 ECL (ET's Tiny Class Library)
//                                                Originalautor: Thomas Epting
//                                        Verhunzung/Erweiterung: Norman Bring
//                               Weitere Verhunzung/Erweiterung: Markus Wuertz
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
// cBase
//    |
//    +--cCmdArg        - Verwaltung von Argumenten der Kommandozeile.
//    |  |
//    |  +--cCmdOptions - Kommandozeilenargumente-Optionsschluesselauswertung
//    |
//    +--cErrBase
//       |
//       +--cErrCmdArg  - Fehlerobjekte bei cCmdArg.
//
//
// Anmerkungen cCmdArg:
//
// 1) vor der uebergebenen Kommandozeile wird eine gegebenenfalls vorhandene
//    Umgebungsvariable ausgewertet (Umgebungsvariablenpraefix + Modulname)
// 2) Voreinstellung fuer den Modulnamen ist der Programmname ohne Pfad & Ext.
// 3) Mit '@' koennen Optionsdateien (geschachtelt) eingefuegt werden,
//    Defaulterweiterung ist einstellbar.
//
//
// Anmerkungen cCmdOptions (Die 3 heiligen Gesetze der Optionen):
//
// 1. Eine Option wird mit '/' oder '-' eingeleitet.
// 2. Die Optionstoken haben eine signifikante Mindestlaenge und enden mit dem
//    ersten nicht sichtbaren Zeichen oder "=" (ermoeglicht Kommentare, eine
//    Hilfefunktion kann einfach die Texte aus der Tokenliste ausgeben).
// 3. Mit '=' getrennt kann jeder Option ein Wert mitgegeben werden.
//
// Beispiele:
//
//    cCmdOption::OPTION keys[] = {
//       123, 1, "Option",
//       456, 4, "FILE=Ausgabedatei",
//       0,   0, "(weitere Erklaerung)",  /* minlen=0 -> Zeile wird ignoriert */
//       0,   0, NULL                     /* token=NULL markiert Tabellenende */
//    };
//
//    Zulaessige (normale) Parameter:
//       "-Option"   -> true = getOption( key=123, value=NULL )
//       "/Opt="     -> true = getOption( key=123, value="" )
//       "-O=Muster" -> true = getOption( key=123, value="Muster" )
//
//    Zeilenende (keine weiteren Argumente):
//       <EOL>       -> false = getOption( key=keyNoOption, value=NULL )
//    Optionen ohne '/' oder '-':
//       "Strichlos" -> false = getOption( key=keyNoOption, value="Strichlos" )
//    unbekannte Optionen (oder zu wenig Zeichen):
//       "/Bad"       -> false = getOption( key=keyNotFonud, value="Bad" )
//       "/FIL=*.c" -> false = getOption( key=keyNotFound, value="FIL=*.c")
//
// ===========================================================================

#include "base/eb_cmdarg.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Diverse Defaulteinstellungen
// ---------------------------------------------------------------------------

#define DEFAULT_ENV_PREFIX ""
#define DEFAULT_EXTENSION  ".OPT"
#define DEFAULT_MODULE     "<unknown>"


#ifdef __INTERFACE__

#include "base/eb_err.hpp"

// ===========================================================================
// Deklaration cErrCmdArg
// ---------------------------------------------------------------------------
//
// cBase
//  +--cErrBase
//      +--cErrCmdArg
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrCmdArg : public cErrBase {

public:
   cErrCmdArg(int err, const char *str = NULL, int line=-1);

   enum ERR_CODE { errBase = ERR_PREFIX('C','M','D'),
      errMissingFile    = errBase + errWarn ,
      errIllState       = errBase + errFatal,
      errFileNestingOV
   };
};

#endif /*__INTERFACE__*/


// Implementierung cErrCmdArg
// ===========================================================================

cErrCmdArg::cErrCmdArg(int err, const char *str, int line) :
   cErrBase(err)
{
   if ( str ) {
      setParam(0, str);
   };
   if ( line >= 0 ) {
      setParam(1, (long)line);
   };
}


#ifdef __INTERFACE__

#include "base/eb_str.hpp"
#include "base/eb_file.hpp"

// ===========================================================================
// Deklaration cCmdArg
// ---------------------------------------------------------------------------
//
// cBase
//   +--cCmdArg
//
// ===========================================================================

class __ECL_DLLEXPORT__ cCmdArg : public cBase {
#if defined __ECL_ICC__
   public:  // Der ICC braucht das irgendwie... :-(
#endif
   // lokale Typen
   enum STATES {
      AS_INIT,
      AS_RESET,
      AS_ENVVAR,
      AS_CMDLINE,
      AS_NEWFILE,
      AS_OPTFILE,
      AS_FINISHED
   };
private:
   struct __ECL_DLLEXPORT__ OPTFILE_STACK {
      STATES state;
      cFile *file_hnd;
      cString workstr;
      cString module;
      short line;
   };

   // lokale Variablen
   STATES ArgState;              /* Aktueller Zustand des Moduls */
   STATES LastState;             /* Zuletzt eingenommener Zustand */
   cString ArgPath;
   cString ArgModule;
   cString ActModuleName;
   short LineNo;
   cString WorkString;           /* Arbeitsbereich, enth. aktuelle Zeile */
   const char * WorkPtr;         /* Zeiger in WorkString */
   const char * LastWorkPtr;     /* Letzter Wert des Zeigers in WorkString */

   cString CmdlineString;        /* uebergebene Kommandozeile */
   cString ActualField;          /* Arbeitsbereich, enth. aktuellen Parameter */
   //cString ExtraString;  //## raus?

   int  ArgC;                    // uebergebener Parametervektor
   char **ArgV;

   short OptfileStackInd;
   OPTFILE_STACK OptfileStack[ 3 ];    // Stackgroesse kann HIER geaendert werden !!!
                                       // (frueher die Konstante OPTFILE_STACK_MAX)

   cString default_extension;    // Default-Dateierweiterung
   cString envvar_prefix;        // Praefix fuer Umgebungsvariable

private:
   // Multifunktionskonstruktor
   void cCmdArg_ALL(int argc, char *argv[], char *cmdline,
                    char *module, char *def_ext, char *env_pre);

public:
   cCmdArg( int argc, char *argv[],
            char *module=NULL, char *def_ext=NULL, char *env_pre=NULL )
      { cCmdArg_ALL( argc, argv, NULL, module, def_ext, env_pre ); }
   cCmdArg( char *cmdline,
            char *module=NULL, char *def_ext=NULL, char *env_pre=NULL )
      { cCmdArg_ALL( 0, NULL, cmdline, module, def_ext, env_pre ); }
   virtual ~cCmdArg();

   // Ermitteln des naechsten Argumentes
   const char *getNext();
   // Zuletzt ermitteltes Argument nochmals lesen
   const char *getAgain() { return ActualField; }

   // Ermittelt den aktuellen Modulnamen
   const char *getModule() { return ArgModule; }
   // Pfad aus dem das Modul gestartet wurde
   const char *getPath() { return ArgPath; }

private:
   void NextField(void);
   void RestoreField(void);
   void StateReset(void);
   void StateEnvvar(void);
   void StateCmdline(void);
   void StateNewfile(void);
   void StateOptfile(void);

};

#endif /*__INTERFACE__*/


// Abteilung "Historische Leichen"
#define INFO(str)  /*printf( "[cmdarg] "str"\n" )*/
//#define OPTFILE_STACK_MAX  3


// Implementierung cErrCmdArg
// ===========================================================================

void cCmdArg::cCmdArg_ALL(int argc, char *argv[], char *cmdline,
                          char *module, char *def_ext, char *env_pre)
{
   // diverse interne Variablen
   OptfileStackInd = 0;
   LineNo = 0;
   ArgState = AS_RESET;
   WorkPtr = LastWorkPtr = WorkString = "";

   // die eigentlichen Parameter übernehmen
   ArgC = argc; ArgV = argv;
   CmdlineString = cmdline;

   // optionale Angaben expandieren
   if ( def_ext != NULL ) {
      default_extension = def_ext;
   } else {
      default_extension = DEFAULT_EXTENSION;
   };

   if (env_pre != NULL) {
      envvar_prefix = env_pre;
   } else {
      envvar_prefix = DEFAULT_ENV_PREFIX;
   };

   if (module != NULL) {
      ArgModule = module;
   } else if (argc < 1) {
      ArgModule = DEFAULT_MODULE;
   } else {
      // Modulname aus argv[0] ohne Pfad und Extension
      char *end , *ptr;
      ptr = end = argv[0] + strlen(argv[0]);
      while (ptr > argv[0] && ptr[-1] != '\\' && ptr[-1] != '/') {
         if (*ptr == '.') end = ptr;
         ptr--;
      };
      ArgModule = cString(ptr,end-ptr);
      ArgPath = cString(argv[0], ptr-argv[0]-1);
   };
   ActModuleName = ArgModule;
}


cCmdArg::~cCmdArg()
{
   while (OptfileStackInd--) {
      delete OptfileStack[ OptfileStackInd ].file_hnd;
   }
}


// NextField - Naechstes Feld von WorkString in ActualField kopieren
// ---------------------------------------------------------------------------

void cCmdArg::NextField(void)
{
   char *bptr;

   INFO("NextField");

   while ( isspace(*WorkPtr) ) WorkPtr++;

   LastWorkPtr = WorkPtr;

   if ( (bptr = strchr(WorkPtr, ' ')) == NULL ) {
      ActualField = WorkPtr;
      WorkPtr = strchr(WorkPtr, '\0');
   } else {
      *bptr = '\0'; ActualField = WorkPtr; *bptr = ' ';
      WorkPtr = bptr + 1;
   }
}

void cCmdArg::RestoreField(void)
{
   INFO("RestoreField");

   WorkPtr = LastWorkPtr;
   ActualField = "";
}


// StateReset - Behandelt den Reset-Zustand
// ---------------------------------------------------------------------------

void cCmdArg::StateReset(void)
{
   cString env_var;
   char *p;

   INFO("StateReset");

   env_var = envvar_prefix + ArgModule;

   if( NULL == (p = getenv(env_var)) ) p = "";

   WorkString = cString(p) + CmdlineString;
   WorkPtr = LastWorkPtr = WorkString;

   ActModuleName = env_var;
   LastState = AS_INIT;
   ArgState = AS_ENVVAR;
}


// StateEnvVar - Behandelt die Verarbeitung der Umgebungsvariablen
// ---------------------------------------------------------------------------

void cCmdArg::StateEnvvar(void)
{
   short i;

   INFO("StateEnvVar");

   NextField();

   if ( ActualField.getLength() == 0 ) {
      WorkString = "";
      for (i = 1; i < ArgC; i++) {
         WorkString += " ";
         WorkString += ArgV[i];
      }
      WorkPtr = LastWorkPtr = WorkString;
      ActModuleName = ArgModule;
      ArgState = AS_CMDLINE;
   } else if (ActualField[0] == '@') {
      RestoreField();
      ArgState = AS_NEWFILE;
   }
}


// StateCmdLine - Behandelt die Verarbeitung der Kommandozeile
// ---------------------------------------------------------------------------

void cCmdArg::StateCmdline(void)
{
   INFO("StateCmdLine");

   NextField();

   if ( ActualField.getLength() == 0 ) {
      ArgState = AS_FINISHED;
   } else if ( ActualField[0] == '@' ) {
      RestoreField();
      ArgState = AS_NEWFILE;
   }
}


// StateNewFile - Behandelt das Oeffnen neuer Optionsdateien
// ---------------------------------------------------------------------------

void cCmdArg::StateNewfile(void)
{
   cFile* fh;

   INFO("StateNewFile");

   NextField();
   ActualField = ActualField.getMid(1, ActualField.getLength()-1 );

   if (ActualField.getLength() == 0 ) {
      throw cErrCmdArg(cErrCmdArg::errMissingFile, ActModuleName, LineNo);
   } else if (OptfileStackInd >= sizeof(OptfileStack) / sizeof(OptfileStack[0])) {
      throw cErrCmdArg(cErrCmdArg::errFileNestingOV, ActModuleName, LineNo);
   } else {

      if (NULL == strchr( ActualField, '.' ) ) {
         ActualField += default_extension;
      }

      fh = new0 cFile(ActualField, "r");

      OptfileStack[OptfileStackInd].state    = LastState;
      OptfileStack[OptfileStackInd].file_hnd = fh;
      OptfileStack[OptfileStackInd].line     = LineNo;
      OptfileStack[OptfileStackInd].workstr =  WorkPtr;
      OptfileStack[OptfileStackInd].module = ActModuleName;

      OptfileStackInd++;
      ActModuleName = ActualField;
      LineNo = 0;
      WorkString = "";
      WorkPtr = LastWorkPtr = WorkString;

   }

   ArgState = AS_OPTFILE;

   //##ExtraString = ActualField;
   ActualField = "";
}


// StateOptFile - Behandelt die Verarbeitung von Optionsdateien
// ---------------------------------------------------------------------------

void cCmdArg::StateOptfile(void)
{
   cFile *fh;

   INFO("StateOptFile");

   fh = OptfileStack[OptfileStackInd - 1].file_hnd;
   NextField();

   if (ActualField.getLength() == 0) {
      if (fh->Eof()) {
         OptfileStackInd--;
         ArgState = OptfileStack[OptfileStackInd].state;
         WorkString = OptfileStack[OptfileStackInd].workstr;
         LineNo = OptfileStack[OptfileStackInd].line;
         ActModuleName = OptfileStack[OptfileStackInd].module;
         delete fh;
      } else {
         char temp_buffer[256];
         try {
            WorkString = fh->Gets( temp_buffer, sizeof(temp_buffer), true );
         } catch ( const cErrFile& err ) {
            if (err != cErrFile::errEOF) {
               throw;
            } else {
               WorkString = "";
            };
         };
         LineNo++;
      }
      WorkPtr = LastWorkPtr = WorkString;
   } else if (ActualField[0] == '@') {
      RestoreField();
      ArgState = AS_NEWFILE;
   }
}


// getNext - Ermitteln des naechsten Argumentes
// ---------------------------------------------------------------------------

const char *cCmdArg::getNext()
{
   STATES state;

   INFO("Arg_Get");

   ActualField = "";

   while ( ActualField.getLength() == 0 && ArgState != AS_FINISHED ) {

      state = ArgState;
      switch (ArgState) {
         case AS_INIT:       throw cErrCmdArg(cErrCmdArg::errIllState);
         case AS_RESET:      StateReset();                    break;
         case AS_ENVVAR:     StateEnvvar();                   break;
         case AS_CMDLINE:    StateCmdline();                  break;
         case AS_NEWFILE:    StateNewfile();                  break;
         case AS_OPTFILE:    StateOptfile();                  break;
      }

      LastState = state;
   }

   if ( ActualField.getLength() == 0 )
      return NULL;
   return ActualField;
}


// ===========================================================================
//	Deklaration cCmdOptions
// ---------------------------------------------------------------------------
//
// cBase
//    +--cCmdArg
//       +--cCmdOptions
//
// ===========================================================================

#ifdef __INTERFACE__

class __ECL_DLLEXPORT__ cCmdOptions : public cCmdArg {
public:
   // Definition eines Optionstokens
   typedef struct {
      int key;                // Kennung der Option
      unsigned short minlen;  // signifikante Mindestlaenge, 0=Kommentar
      char *token;            // Token, NULL=Tabellenende
   } OPTION;
   // key wenn die Option nicht in der Liste gefunden wurde
   enum {
      keyNoOption,   // '/' & '-' fehlen, value -> erstes Zeichen
      keyNotFound    // unbekannte Option, value -> HINTER '/' bzw. '-'
   };

private:
   const OPTION *option_list; // Optionstabelle

public:
   // Konstruktoren wie bei cCmdArg (Argumentvektor oder Kommandozeile)
   cCmdOptions( int argc, char *argv[],
                char *module=NULL, char *def_ext=NULL, char *env_pre=NULL );
   cCmdOptions( char *cmdline,
                char *module=NULL, char *def_ext=NULL, char *env_pre=NULL );
   //virtual ~cCmdOptions();

   // festlegen der Optionstabelle
   void setOptions( const OPTION *opt ) { option_list = opt; }
   // erfragen der Optionstabelle
   const OPTION *getOptions() { return option_list; }

   // naechste Option auswerten
   bool getOption( int &key, const char* &value );


private:
   const OPTION *findToken( const char *str, const char **rest );

};

#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Implementierung cCmdOptions

cCmdOptions::cCmdOptions( int argc, char *argv[], char *module, char *def_ext, char *env_pre ) :
   cCmdArg( argc, argv, module, def_ext, env_pre )
{
   option_list = NULL;
}

cCmdOptions::cCmdOptions( char *cmdline, char *module, char *def_ext, char *env_pre ) :
   cCmdArg( cmdline, module, def_ext, env_pre )
{
   option_list = NULL;
}


// Token in der Optionstabelle suchen

const cCmdOptions::OPTION *cCmdOptions::findToken( const char *line, const char **rest )
{
   if (!option_list) return NULL;   // keine Optionsliste definiert

   const OPTION *tab = option_list;
   const char *ls,*ts;
   int ml;

   while ( tab->token ) {
      ls = line; ts = tab->token; ml = tab->minlen;
      while ( *ls && *ts && isgraph(*ts) && *ts != '=' && toupper(*ls) == toupper(*ts) ) {
         ls++; ts++; ml--;
      }
      if ((*ls == '\0' || *ls == '=') && ml <= 0 && tab->minlen != 0) {
         *rest = ls;
         return tab;
      }
      tab++;
   }

   *rest = line;
   return NULL; // nicht gefunden :-(
}


// naechste Option auswerten

bool cCmdOptions::getOption( int &key, const char * &value )
{
   const char *str = getNext();
   const char *rest;

   // keine mit '/' oder '-' eingeleitete Option
   if ( !str || (*str != '/' && *str != '-') ) {
      key = keyNoOption;
      value = str;
      return false;
   }

   const OPTION *tab = findToken( ++str, &rest );

   if ( tab ) {
      key = tab->key;
      if ( *rest == '=' ) {
         value = ++rest;
      } else {
         value = NULL;
      }
      return true;
   } else {
      key = keyNotFound;
      value = str;
      return false;
   }
}


