// ===========================================================================
// eb_cmdline.cpp                                               ______ /  ECL
// Autor. Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cCmdLine   - Kommandozeilen-Parser
//
// ---------------------------------------------------------------------------
//
// Verwendung in einer Konsolen-Applikation:
// - Optionstabelle OPTION[] definieren
// - cCmdLine mit der Optionstabelle als Parameter instantiieren.
// - cCmdLine::parseCommandLine(argc, argv) aufrufen.
//
// Verwendung im MFC Kontext:
// - CCommandLineInfo ableiten, mit cCmdLine als Member Variable.
// - In der Implementierung von
//      virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
//   die dazu kompatible Methode
//      bool cCmdLine::parseParam(const char *param, bool flag, bool last);
//   aufrufen. Die Aufgabe von cCmdLine::parseCommandLine(...) wird jetzt von
//      void CWinApp::ParseCommandLine( CCommandLineInfo& rCmdInfo );
//   erledigt. (cCmdLine::parseParam liefert true wenn der Parameter erkannt
//   und "verbraucht" wurde.)
// - Alle Theorie ist grau: MFC Benutzung noch nicht ausprobiert !!!
//
// Beispiel:
// - siehe Schluss der CPP Datei: #ifdef TEST_AND_EXAMPLE
//
//
// Allgemeines zum Kommandozeilen-Parser:
//
// - in der Kommandozeile muss jede Option mit '/' oder '-' markiert sein,
//   wahlweise gefolgt von '=' und einem Wert.
// - durch '@'<file> kann jederzeit eine Includedatei in den 'Argumentstrom'
//   eingefuegt werden
// - Nur in Includedateien: Kommentare sind mit ';' am Zeilenanfang moeglich.
//
//
// cCmdLine::OPTION - Klasse zur Definition der Optionen
//
// - eine Option endet (in der Tabelle) mit dem ersten nicht druckbaren
//   Zeichen in 'token' oder mit '=' (ohne '/' oder '-' am Anfang).
// - durch ' ' oder '=' getrennt kann so ein Hilfetext mit angegeben werden.
// - i.d.R. wird eine Variable angegeben, in der der Optionswert landet.
// - Unterstützte Datentypen: int, double, bool, cString
// - Die Option kann in der Anwendung auf eine signifikante Mindestlänge
//   von 'minlen' Zeichen verkürzt werden. Erfolgt keine Angabe, muss
//   immer die gesamte Option angegeben werden.
// - Wahlweise kann zu jeder Option auch ein Initialisierungswert angegeben
//   werden (in Stringform)
// - Wahlweise kann zu jeder Option auch ein Togglewert angegeben werden, der
//   verwendet wird, wenn die Option ohne "=<value>" benutzt wird.
// - ein 'token' ohne Angabe von 'value' dient nur als Hilfetext.
// - Wird immer in einer Tabelle bentutzt, mit Defaultkonstruktor am Ende:
//      cCmdLine::OPTION options[] = {
//         ...
//         cCmdLine::OPTION()
//      };
// - Ausser der Zuweisung von Werten an Variablen koennen durch Optionen auch
//   (globale) Callback-Funktionen oder Memberfunktionen einer Ableitung von
//   cCmdLine aufgerufen werden.
//
// Anmerkungen zu Callback- und aufrufbaren Memberfunktionen:
// - Prototyp: bool func(const char *token, const char *value);
// - Optionsvarianten:
//    /OPTION        token -> "OPTION", value = 0
//    /OPTION=       token -> "OPTION", value -> ""
//    /OPTION=WERT   token -> "OPTION", value -> "WERT"
//
// cCmdLine::SYMBOL - Klasse zur Definition symbolischer Namen:
//
// - der Name endet mit dem ersten nicht druckbaren Zeichen in 'token'.
// - durch ' ' getrennt kann so ein Hilfetext mit angegeben werden.
// - jedem Namen wird ein Wert 'value' zugewiesen.
// - Der Name kann in der Anwendung auf eine signifikante Mindestlänge
//   von 'minlen' Zeichen verkürzt werden. Erfolgt keine Angabe, muss
//   immer der gesamte Name angegeben werden.
// - ein 'token' ohne Angabe von 'value' dient nur als Hilfetext.
// - Wird immer in einer Tabelle bentutzt, mit Defaultkonstruktor am Ende:
//      cCmdLine::SYMBOL symbols[] = {
//         ...
//         cCmdLine::SYMBOL()
//      };
//
// Besonderheiten zur Beachtung bei cCmdLine::SYMBOL und cCmdLine::OPTION
// - 'minlen' sollte nie die Laenge des Namens ueberschreiten oder negativ
//   sein.
// - bei gleichem Namensanfang darauf achten, dass das Symbol mit mehr
//   signifikanten Zeichen immer zuerst definiert wird.
//
// ---------------------------------------------------------------------------
// Verbesserungsvorschlaege:
// - Default/Toggle bei Hilfe ausgeben: "(<Def>)" oder "(<Def>/<Tog>)" oder
//   es dem Hilfetext überlassen. Vorteil: Dynamische Werte möglich.
//
// - Eingebaute Hilfe: Ueber den Togglewert bzw. den Wert bei "/?" koennte man
//   einen Verbose-Mode aktivieren der z.B. auch die ENUM-Symbole anzeigt.
//   Ferner koennte man die TAB-Breite definieren und jedes \t durch entsprechende
//   Leerzeichen ersetzen.
// - Modulname & Pfad erfragen (siehe cCmdArg)
// - Praefix-Umgebungsvariable -> selbst mit 'parseCommandLine(char*) machen!
// - Optionskennzeichen '/' & '-' ueber char* konfigurierbar (get/set)
// - Kommentarzeichen ';' konfigurierbar
// - Include-Schachtelungstiefe konfigurierbar
// - getExpression ebenfalls zu strToExpression ummodeln ...
// ---------------------------------------------------------------------------


#include "base/eb_cmdline.hpp"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <ostream.h>

#include "base/eb_strex.hpp"


#ifdef __INTERFACE__
// ---------------------------------------------------------------------------
// cCmdLine - Command line parser
//
// cCmdLine::OPTION - option definition table entry
// cCmdLine::SYMBOL - symbolic name definition table entry
// ---------------------------------------------------------------------------

#include "base/eb_str.hpp"

class __ECL_DLLEXPORT__ cCmdLine : public cBase {

public:
   // Callback-Funktion zur freien Auswertung von Optionen
   typedef bool (*CALLBACK_FUNC)(const char *token, const char *value);
   // Member-Funktion zur freien Auswertung von Optionen (wie OptionHelp())
   typedef bool (cCmdLine::*MEMBER_FUNC)(const char *token, const char *value);


   // SYMBOL - Klasse zur Definition symbolischer Namen
   // ===========================================================

   class SYMBOL {
      friend cCmdLine;
   public:
      // Symbol mit Mindestlaenge
      SYMBOL(int value, int minlen, const char *token);
      // Symbol mit voller Laenge
      SYMBOL(int value, const char *token);
      // Kommentar
      SYMBOL(const char *comment);
      // Endmark
      SYMBOL();
   private:
      int value;           // Wert
      int minlen;          // signifikante Mindestlaenge
      const char *token;   // Symbolname, bis '\0' oder ' ' und Hilfetext
   }; // SYMBOL


   // OPTION - Klasse zur Definition der Optionen
   // =====================================================

   class OPTION {
      friend  cCmdLine;
   public:
      // Integer
      OPTION(int &int_var, int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Enum (Integer mit Symbolen & addition)
      OPTION(int &int_var, SYMBOL *enum_tab, int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Double
      OPTION(double &dbl_var, int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // cString
      OPTION(cString &cstr_var, int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Bool (1/0, True/False, Yes/No, Wahr/Falsch, Ja/Nein)
      OPTION(bool &bool_var, int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Callback-Funktion
      OPTION(bool (*func)(const char *,const char *), int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Member-Funktion
      OPTION(bool (cCmdLine::*func)(const char *,const char *), int minlen, const char *token,
             const char *val_default=0, const char *val_toggle=0);
      // Kommentar
      OPTION(char *token);
      // Endmark
      OPTION();
   private:
      void *var_address;      // Variablenadresse
      int var_type;           // Variablentyp
      int var_minlen;         // signifikante Mindestlaenge der Option
      const char *var_token;  // Optionsname, bis '\0' oder ' ' bzw. '=' und Hilfetext
      cString var_default;    // Initialisierungswert (Default value)
      cString var_toggle;     // Umschaltwert (Toggle value

      MEMBER_FUNC var_member; // MEMBER only: member function pointer
      SYMBOL *var_enum;       // ENUM only: table with symbolic names
   }; // OPTION


   // Kommandozeilenauswertung
   // ========================

   // Konstruktion mit Tabelle der Optionsdefinitionen
   cCmdLine(OPTION *option_table);

   // Parameter des Argument Vektors bearbeiten
   void parseCommandLine(int argc, char *argv[]);
   // Parameter des Argument Vektors bearbeiten, verbrauchte entfernen.
   void parseCommandLineRemove(int &argc, char *argv[]);

   // Parameter aus Kommandozeile bearbeiten
   void parseCommandLine(const char *line);

   // Parameter aus Datei bearbeiten
   void parseInclude(const char *filespec);

   // Einzelnen Parameter bearbeiten. Ist flag==true wurde ein einleitendes
   // '/' oder '-' von param entfernt, last==true beim letzen Parameter des
   // Vektors oder der Textzeile. Liefert true wenn parameter ok war.
   bool parseParam(const char *param, bool flag, bool last);

   // Wird von parseParam() fuer Parameter ohne '/' und '-' aufgerufen.
   virtual bool parseNoOption(const char *no_option, bool last);
   void setNoOptionCallback(bool (*func)(const char *, bool)) {
      no_option_callback = func;
   }

   // Symbol in Liste suchen (analog zu strtol :)
   static int strToSymbol(const char *ptr, char **endptr, const SYMBOL *sym);
   static int strToBool(const char *ptr, char **endptr);
   static int strToExpression(const char *ptr, char **endptr, const SYMBOL *sym);

   // Hilfe
   // =====

   // Hilfe ausgeben, print help
   void Help(int mode=0);
   // token = 0 / "INIT_" vorangestellt bei initialisierung???, value kann hilfe konfigurieren ????
   bool HelpOption(const char *token, const char *value);

   enum HELP {
      HLP_SYMBOLS = 0x0100    // ENUM Typen expandieren
   }; // HELP


   // Fehlerbehandlung
   // ================
   // (liefert true wenn durch Fehlerbehandlung der Parameter verbraucht wird)

   // Keine Option und nicht durch parseNoOption() oder Callback verbraucht,
   // wird von parseCommandLineRemove() nicht gemeldet.
   virtual bool errorNoOption(const char *arg_str);

   // Unbekannte, mit '/' oder '-' markierte Option,
   // wird von parseCommandLineRemove() nicht gemeldet.
   virtual bool errorUnknownOption(const char *arg_str);

   // Option 'token' wurde ohne Wert angegeben (und kein Togglewert definiert)
   virtual bool errorNoValue(const char *token);

   // Mit "=<value>" angegebener Wert ist fehlerhaft
   virtual bool errorBadValue(const char *token, const char *specific_message);

   // Fehler im Zusammenhang mit dem Include-Mechanismus
   virtual bool errorInclude(const char *filespec, const char *specific_message);

   // Aktuelle Include-Datei oder 0 bei Top-Level
   const char *getIncludeFile() { return include_file; } const


   // Interner Schnickschnack
   // =======================
   // (ein Teil davon nicht private, da von SYMBOL oder OPTION benoetigt)

   // Constants to identify the supported datatypes
   enum TYPES {
      TYP_DOUBLE,     // double
      TYP_INTEGER,    // int
      TYP_ENUM,       // int with symbolic names
      TYP_BOOL,       // bool
      TYP_CSTRING,    // cString
      TYP_CALLBACK,   // callback function: bool (*func)(const char *, const char *)
      TYP_MEMBER,     // member function: bool (*func)(const char *, const char *)
      TYP_COMMENT,    // just a comment within help
      TYP_ENDMARK     // last entry
   }; // TYPES

   // Aufspaltung in Token und Stringrest (mit zusaetzlichen Trennzeichen)
   static cString getToken(cString all, cString &rest, const cString &seps="=");

private:
   // Tokens vergleichen, other kann auf minlen verkuerzt sein
   static bool matchTokens(const cString &other, int minlen, const cString &master);
   // Symbol in Tabelle suchen, error zeigt Misserfolg an
   // static int _getSymbol(const SYMBOL symbols[], cString token, bool &error);
   // Ausdruck mit Symbolen berechnen, error enthaelt bei Misserfolg den fehlerhaften Teil
   static int _getExpression(const SYMBOL symbols[], cString expression, cString &error);

   // Variablen mit Defaultwerten initialisieren
   void InitializeVariables();

   // Auswertung der einzelnen Datentypen, liefert true falls ok/verbraucht.
   bool assignDouble(OPTION *option, const char *token, const char *value);
   bool assignInteger(OPTION *option, const char *token, const char *value);
   bool assignEnum(OPTION *option, const char *token, const char *value);
   bool assignBool(OPTION *option, const char *token, const char *value);
   bool assignString(OPTION *option, const char *token, const char *value);


   // Attribute
   // =========

   // Optionstabelle (bei Konstruktion angegeben)
   OPTION *option_table;
   // Umgebungsvariable mit
   // errorNoOption() unterdruecken
   bool ignore_unknown;
   // Include-Dateien zaehlen (Rekursionsschutz)
   int include_level;
   // aktuelle Include-Datei (fuer Fehlerlokalisation)
   const char *include_file;
   // Callback Variante fuer nicht-Options-Argumente
   bool (*no_option_callback)(const char *, bool);
};
#endif /*__INTERFACE__*/


#ifndef TEST_AND_EXAMPLE
   #define TEST_AND_EXAMPLE 0
#endif


// ---------------------------------------------------------------------------
// cCmdLine::SYMBOL Konstruktoren

// Symbol mit Mindestlaenge
cCmdLine::SYMBOL::SYMBOL(int value, int minlen, const char *token) :
   value(value), minlen(minlen), token(token) {}

// Symbol mit voller Laenge
cCmdLine::SYMBOL::SYMBOL(int value, const char *token) :
   value(value), token(token)
{
   cString dummy;
   SYMBOL::minlen = cCmdLine::getToken(token, dummy).getLength();
}

// Kommentar -> minlen = 0, token != 0
cCmdLine::SYMBOL::SYMBOL(const char *token) :
   value(0), minlen(0), token(token) {}

// Endmark -> token = 0
cCmdLine::SYMBOL::SYMBOL() :
   value(0), minlen(0), token(0) {}


// ---------------------------------------------------------------------------
// cCmdLine::OPTION Konstruktoren

// Integer
cCmdLine::OPTION::OPTION(int &int_var, int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(&int_var), var_type(TYP_INTEGER),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle) {}

// Enum (Integer mit Symbolen & addition)
cCmdLine::OPTION::OPTION(int &int_var, SYMBOL *enum_tab, int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(&int_var), var_type(TYP_ENUM),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle),
   var_enum(enum_tab) {} // nur fuer ENUM

// Double
cCmdLine::OPTION::OPTION(double &dbl_var, int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(&dbl_var), var_type(TYP_DOUBLE),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle) {}

// Bool
cCmdLine::OPTION::OPTION(bool &bool_var, int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(&bool_var), var_type(TYP_BOOL),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle) {}

// cString
cCmdLine::OPTION::OPTION(cString &cstr_var, int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(&cstr_var), var_type(TYP_CSTRING),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle) {}

// Callback-Funktion
cCmdLine::OPTION::OPTION(bool (*func)(const char *,const char *), int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(func), var_type(TYP_CALLBACK),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle) {}

// Member-Funktion
cCmdLine::OPTION::OPTION(bool (cCmdLine::*func)(const char *,const char *), int minlen, const char *token,
                         const char *val_default, const char *val_toggle) :
   var_address(0), var_type(TYP_MEMBER),
   var_minlen(minlen), var_token(token),
   var_default(val_default), var_toggle(val_toggle),
   var_member(func) {} // nur fuer MEMBER

// Kommentar
cCmdLine::OPTION::OPTION(char *token) :
   var_address(0), var_type(TYP_COMMENT),
   var_minlen(0), var_token(token) {}

// Endmark
cCmdLine::OPTION::OPTION() :
   var_address(0), var_type(TYP_ENDMARK),
   var_minlen(0), var_token(0) {}


// ---------------------------------------------------------------------------
// Hilfsfunktionen für Tokens etc.

static const char *cmpTokens(const char *other, int minlen, const char *token)
{
   while (*other && *token && isgraph(*token) && *token != '='
          && toupper(*other) == toupper(*token)) {
      other++; minlen--; token++;
   }
   return (minlen <= 0) ? other : 0;
}

int cCmdLine::strToSymbol(const char *ptr, char **endptr, const SYMBOL *sym)
{
   const char *end;

   if (endptr != 0) *endptr = (char*)ptr;
   while (ptr != 0 && isspace(*ptr)) ptr++;

   while (sym != 0 && ptr != 0 && sym->token != 0) {
      if (sym->minlen > 0 && (end = cmpTokens(ptr, sym->minlen, sym->token)) != 0) {
         if (endptr != 0) *endptr = (char*)end;
         return sym->value;
      }
      sym++;
   }

   return 0;
}

int cCmdLine::strToBool(const char *ptr, char **endptr)
{
   // Liste der symbolischen bool-Werte
   SYMBOL symbols_bool[] = {
      SYMBOL(0,1,"False"),
      SYMBOL(0,1,"Falsch"),
      SYMBOL(0,1,"No"),
      SYMBOL(0,1,"Nein"),
      SYMBOL(0,1,"0"),
      SYMBOL(1,1,"True"),
      SYMBOL(1,1,"Wahr"),
      SYMBOL(1,1,"Yes"),
      SYMBOL(1,1,"Ja"),
      SYMBOL(1,1,"1"),
      SYMBOL()
   };

   return strToSymbol(ptr, endptr, symbols_bool);
}

/*
int cCmdLine::_getSymbol(const SYMBOL *symbols, cString token, bool &error)
{
   cString dummy;
   while (symbols->token != 0) {
      if (symbols->minlen > 0 && matchTokens(token, symbols->minlen, cCmdLine::getToken(symbols->token,dummy,""))) {
         error = false;
         return symbols->value;
      }
      symbols++;
   }
   error = true;
   return 0;
}
*/

int cCmdLine::strToExpression(const char *ptr, char **endptr, const SYMBOL *sym)
{
   int value = 0;
   int operation = '+';

   while (ptr) {
      if (endptr != 0) *endptr = (char*)ptr;
      while (ptr != 0 && isspace(*ptr)) ptr++;

      int element;
      char *end;
      if (isdigit(*ptr)) {
         element = strtoul(ptr, &end, 0);
      } else {
         element = strToSymbol(ptr, &end, sym);
      }

      if (end == ptr) return value;

      switch (operation) {
      case '|': value |= element; break;
      case '-': value -= element; break;
      case '+': value += element; break;
      default:
         // unbekannte Operatoren ignorieren -> Stelle wird nie erreicht!
         assert(0);
         break;
      }

      while (isspace(*end)) end++;
      if (*end && strchr("+-|", *end) != 0) {
         operation = *end;
         ptr = end+1;
      } else {
         if (endptr != 0) *endptr = end;
         return value;
      }
   }

   // value ist immer 0 wenn ptr==0
   return value;
}


int cCmdLine::_getExpression(const SYMBOL *symbols, cString expression, cString &error)
{
   int value = 0;
   int operation = '+';

   while (!expression.isEmpty()) {
      cString next = getToken(expression, expression, "+-|");

      int element;
      char *end;

      if (isdigit(next[0])) {
         element = strtoul(next, &end, 0);
      } else {
         element = strToSymbol(next, &end, symbols);
      }

      if ((const char *)next == end || *end != '\0') {
         error = next;
         return value;
      }

      switch (operation) {
      case '|': value |= element; break;
      case '-': value -= element; break;
      case '+': value += element; break;
      default:
         // ignore unknown operators
         assert(0);
         break;
      }

      operation = expression[0];
      if (operation != 0) {
         expression = expression.getMid(1).trimLeft();
      }
   }
   error = cString();
   return value;
}

cString cCmdLine::getToken(cString all, cString &rest, const cString &seps)
{
   int pos = 0;
   all = all.trimLeft();
   while (isgraph(all[pos]) && strchr(seps, all[pos]) == 0) pos++;
   rest = all.getMid(pos).trimLeft();
   return all.getLeft(pos);
}

bool cCmdLine::matchTokens(const cString &other, int minlen, const cString &master)
{
   int pos = 0;
   while (other[pos] && master[pos] && toupper(other[pos]) == toupper(master[pos])) pos++;
   return pos >= minlen && !other[pos];
}


// ---------------------------------------------------------------------------
// Konstruktion

cCmdLine::cCmdLine(OPTION *option_table) :
   option_table(option_table)
{
   //cCmdLine::option_table = option_table;
   ignore_unknown = false;
   include_level = 10;
   no_option_callback = 0;
   include_file = 0;

   InitializeVariables();
}


void cCmdLine::InitializeVariables()
{
   OPTION *search = option_table;
   while (search->var_type != TYP_ENDMARK) {
      if (!search->var_default.isEmpty()) {
         cString dummy;
         cString init_token = "INIT_"+getToken(search->var_token, dummy);
         cString init_value = search->var_default;

         switch(search->var_type) {
         case TYP_DOUBLE:
            assignDouble(search, init_token, init_value);
            break;
         case TYP_INTEGER:
            assignInteger(search, init_token, init_value);
            break;
         case TYP_ENUM:
            assignEnum(search, init_token, init_value);
            break;
         case TYP_BOOL:
            assignBool(search, init_token, init_value);
            break;
         case TYP_CSTRING:
            assignString(search, init_token, init_value);
            break;
         case TYP_CALLBACK:
            (*(bool(*)(const char *,const char *))search->var_address)(init_token, init_value);
            break;
         case TYP_MEMBER:
            (this->*search->var_member)(init_token, init_value);
            break;
         default:
            // ignore undefined types
            assert(0);
            break;
         }
      } else if (search->var_type == TYP_BOOL) {
         // initialize all bool variables to false
         *((bool*)search->var_address) = false;
      }
      search++;
   }
}

// ---------------------------------------------------------------------------
// parsing the command line

void cCmdLine::parseCommandLine(int argc, char *argv[])
{
   for (int i = 1; i < argc; i++) {
      const char *param = argv[i];
      bool flag = false;
      bool last = ((i + 1) == argc);

      if (param[0] == '-' || param[0] == '/') {
         flag = true;
         ++param;
      }
      parseParam(param, flag, last);
   }
}

void cCmdLine::parseCommandLineRemove(int &argc, char *argv[])
{
   ignore_unknown = true; // report less errors

   int argmax = argc;

   for (int i = 1; i < argc; i++) {
      bool consumed = false;

      const char *param = argv[i];
	  bool flag = false;
	  bool last = ((i + 1) == argc);

      if (param[0] == '-' || param[0] == '/') {
         flag = true;
         ++param;
      }
      consumed = parseParam(param, flag, last);

      if (consumed == true) {
         // parameter consumed, modify the vector
         char *toend = argv[i];
         for (int j=i+1; j<argmax; j++) {
            argv[j-1] = argv[j];
         }
         argv[argmax-1] = toend;

         // attention: modify variables of outer loop
         argc--;
         i--;
      }
	}

   ignore_unknown = false;
}

void cCmdLine::parseCommandLine(const char *line)
{
   while (line != 0 && *line != '\0') {
      while (isspace(*line)) line++;
      const char *param_start = line;
      while (isgraph(*line)) line++;
      cString param_buffer(param_start,line-param_start);
      while (isspace(*line)) line++;

      const char *param = param_buffer;
      bool flag = false;
      bool last = *line == '\0';

      if (param[0] == '-' || param[0] == '/') {
         flag = true;
         ++param;
      }
      parseParam(param, flag, last);
   }
}

void cCmdLine::parseInclude(const char *filespec)
{
   if (include_level <= 0) {
      errorInclude(filespec,"Nesting depth exceeded");
   } else {
      include_level--;

      FILE *fp = fopen(filespec,"r");
      if (fp == 0) {
         errorInclude(filespec,"File not found");
      } else {
         const char *old_filespec = include_file;
         include_file = filespec;

         char buf[256];
         char *str = buf;
         while (str != 0) {
            str = fgets(buf, sizeof(buf), fp);
            if (str != 0) {
               while (isspace(*str)) str++;
               if (*str != ';') {
                  char *strip_nl = strchr(buf, '\n');
                  if (strip_nl) *strip_nl = '\0';
                  parseCommandLine(buf);
               }
            }
         }
         fclose(fp);

         include_file = old_filespec;
      }

      include_level++;
   }
}

bool cCmdLine::parseParam(const char *param, bool flag, bool last)
{
   // Parameter ohne '-' oder '/' bearbeiten
   if (flag == false) {
      if (param[0] == '@') {
         // durch '@' markierte Include-Datei bearbeiten
         parseInclude(param+1);
         return true;
      } else if ( parseNoOption(param, last) ||
           (no_option_callback != 0 && (*no_option_callback)(param, last)) ) {
         // virtuelle oder Callback Funktion hat Parameter verbraucht
         return true;
      } else {
         // Ausser bei parseCommandLineRemove() als Fehler melden
         return ignore_unknown ? false : errorNoOption(param);
      }
   }

   // Umgebungsvariablen ersetzen
   cString param_enved = cStrEnv(param).replace();

   // Aufspalten in token & value
   cString param_value;
   cString param_token = getToken(param_enved, param_value);

   OPTION *search = option_table;
   while (search->var_type != TYP_ENDMARK) {
      cString dummy;
      cString search_token = getToken(search->var_token, dummy);
      if ( search->var_type != TYP_COMMENT &&
           matchTokens(param_token, search->var_minlen, search_token) ) {

         // pointer to value or 0 if '=' is missing
         const char *param_value_ptr = param_value;
         if (*param_value_ptr == '=') {
            param_value_ptr++;
         } else  {
            // wenn kein Togglewert angegeben ist -> param_value = 0
            param_value_ptr = (const char *)search->var_toggle;
         }

         switch(search->var_type) {
         case TYP_DOUBLE:
            return assignDouble(search, param_token, param_value_ptr);
         case TYP_INTEGER:
            return assignInteger(search, param_token, param_value_ptr);
         case TYP_ENUM:
            return assignEnum(search, param_token, param_value_ptr);
         case TYP_BOOL:
            return assignBool(search, param_token, param_value_ptr);
         case TYP_CSTRING:
            return assignString(search, param_token, param_value_ptr);
         case TYP_CALLBACK:
            return (*(bool(*)(const char *,const char *))search->var_address)(param_token, param_value_ptr);
         case TYP_MEMBER:
            return (this->*search->var_member)(param_token, param_value_ptr);
         default:
            // ignore undefined types
            assert(0);
            break;
         }
      }
      search++;
   }

   // Ausser bei parseCommandLineRemove() als Fehler melden
   return ignore_unknown ? false : errorUnknownOption(param);
}


bool cCmdLine::parseNoOption(const char *param, bool last)
{

   param; last; // "warning C4100: unreferenced formal parameter" vermeiden :)
   return false;
}


bool cCmdLine::assignDouble(OPTION *option, const char *token, const char *value)
{
   if (value == 0) {
      return errorNoValue(token);
   }

   char *end;
   double double_value = strtod(value, &end);
   if (end > value && *end == '\0') {
      *((double*)option->var_address) = double_value;
      return true;
   } else {
      return errorBadValue(token,"bad double");
   }

}

bool cCmdLine::assignInteger(OPTION *option, const char *token, const char *value)
{
   if (value == 0) {
      return errorNoValue(token);
   }

   char *end;
   int int_value = strtol(value, &end, 0);
   if (end > value && *end == '\0') {
      *((int*)option->var_address) = int_value;
      return true;
   } else {
      return errorBadValue(token,"bad integer");
   }
}

bool cCmdLine::assignEnum(OPTION *option, const char *token, const char *value)
{
   if (value == 0) {
      return errorNoValue(token);
   }

   char *end;
   int enum_value = strToExpression(value, &end, option->var_enum);
   if (end > value && *end == '\0') {
      *((int*)option->var_address) = enum_value;
      return true;
   } else {
      return errorBadValue(token, cString("bad enum: ")+end);
   }

   /*
   cString error;
   int expression = getExpression(option->var_enum, value, error);
   if (!error.isEmpty()) {
      return errorBadValue(token, "bad enum: "+error);
   }

   *((int*)option->var_address) = expression;
   return true;
   */
}

bool cCmdLine::assignBool(OPTION *option, const char *token, const char *value)
{
   bool bool_value = false;

   if (value == 0 || strlen(value) == 0) {
      bool_value = true;
   } else {
      char *end;
      bool_value = (strToBool(value, &end) != 0);
      if (end == value || *end != '\0') {
         return errorBadValue(token, cString("bad bool: ")+value);
      }
   }

   *((bool*)option->var_address) = bool_value;
   return true;
}

bool cCmdLine::assignString(OPTION *option, const char *token, const char *value)
{
   if (value == 0) {
      return errorNoValue(token);
   }

   *((cString*)option->var_address) = value;
   return true;
}


// ------------------------------------------
// default implementaion of virtual functions

bool cCmdLine::errorNoOption(const char *argument)
{
   cerr << "CmdLine: ";
   if (include_file != 0) cerr << "File '" << include_file << "': ";
   cerr << "No option argument '" << argument << "' ignored" << endl;
   return false;
}

bool cCmdLine::errorUnknownOption(const char *token)
{
   cerr << "CmdLine: ";
   if (include_file != 0) cerr << "File '" << include_file << "': ";
   cerr << "Unknown option '" << token << "' ignored" << endl;
   return false;
}

bool cCmdLine::errorNoValue(const char *token)
{
   cerr << "CmdLine: ";
   if (include_file != 0) cerr << "File '" << include_file << "': ";
   cerr << "Option '" << token << "' without value ignored" << endl;
   return false;
}

bool cCmdLine::errorBadValue(const char *token, const char *specific_message)
{
   cerr << "CmdLine: ";
   if (include_file != 0) cerr << "File '" << include_file << "': ";
   cerr << "Option '" << token << "': " << specific_message << endl;
   return false;
}

bool cCmdLine::errorInclude(const char *filespec, const char *specific_message)
{
   cerr << "CmdLine: ";
   if (include_file != 0) cerr << "File '" << include_file << "': ";
   cerr << "Include '" << filespec << "': " << specific_message << endl;
   return false;
}


// ------------------------------------------
// help
//
// - Default- und Togglewerte auch ueber mode aktivieren
// - Hilfen für Help & Bool ?
// - Allgemeine Hilfe Hilfe ?

bool cCmdLine::HelpOption(const char *token, const char *value)
{
   // Symbolische Parametrisierung der Hilfe
   SYMBOL symbols_help[] = {
      SYMBOL(cCmdLine::HELP::HLP_SYMBOLS,1,"Symbols"),
      SYMBOL()
   };

   //cout << "TOKEN=" << token << "  VALUE=" << (value?value:"(NULL)") << endl;

   int mode = 0;
   if (value != 0) {
      char *end;
      mode = strToExpression(value, &end, symbols_help);
      if (end == value || *end != '\0') {
         return errorBadValue(token, cString("bad enum: ")+end);
      }
   }

   Help(mode);
   return true;
}

void cCmdLine::Help(int mode)
{
   if ((mode & 0x0F) == 0) mode |= 2;

   OPTION *search = cCmdLine::option_table;
   while (search->var_type != TYP_ENDMARK) {
      cString line;
      if (search->var_type == TYP_COMMENT) {
         line = search->var_token;
      } else {
         line = cString("\t") + search->var_token;
      }

      if (!search->var_default.isEmpty()) {
         line << " (" << search->var_default;
         if (!search->var_toggle.isEmpty()) {
            line << "/" << search->var_toggle;
         }
         line << ")";
      }

      line = line.replaceTab(mode & 0x0F);
      cout << line << endl;

      if (search->var_type == TYP_ENUM && (mode & HLP_SYMBOLS)) {
         const SYMBOL *symbols = search->var_enum;
         while (symbols->token != 0) {
            if (symbols->minlen == 0) {
               line = cString("\t") + symbols->token;
            } else {
               line = cString("\t\t") + symbols->token;
            }

            line = line.replaceTab(mode & 0x0F);
            cout << line << endl;

            symbols++;
         }
      }

      search++;
   }
}


// ------------------------------------------

#if TEST_AND_EXAMPLE

// show argument vector
void show_argvec(int argc, char *argv[])
{
   for (int i=0; i<argc; i++) {
      cout << "<" << argv[i] << "> ";
   }
   cout << endl;
}

bool function(const char *token, const char *value)
{
   if (value == 0) value = "NULL";
   cout << "function( " << token << ", " << value << " )" << endl;
   return true;
}


int main(int argc, char *argv[])
{
   double dbl_value = 0.0;
   int int_value = 0;
   int enum_value = -1;
   bool bool_value;
   cString cstr_value = "cString";

   cCmdLine::SYMBOL enum_symbols[] = {
      cCmdLine::SYMBOL("Symboltabelle auch mit Kommentaren"),
      cCmdLine::SYMBOL("\tAuch nochmal mit \\t eingerueckt"),
      cCmdLine::SYMBOL(1, 1,"Eins - nur erstes Zeichen signifikant"),
      cCmdLine::SYMBOL(2, 1,"Zwei - dito"),
      cCmdLine::SYMBOL(3, 1,"Drei - dito"),
      cCmdLine::SYMBOL(4, "Vier - ganzes Token signifikant"),
      cCmdLine::SYMBOL() // Endmark
   };

   cCmdLine::OPTION table[] = {
      cCmdLine::OPTION("Nur ein Kommentar in der Tabelle fuer zusaetzliche Hilfetexte"),
      cCmdLine::OPTION("\tMit \\t eingerueckter Kommentar"),
      cCmdLine::OPTION(int_value,1,"INT - Integer Beispiel",0,"12345"),
      cCmdLine::OPTION(dbl_value,1,"DBL - Double Beispiel","1.234"),
      cCmdLine::OPTION(bool_value,1,"BOOL - Bool Beispiel"),
      cCmdLine::OPTION(cstr_value,2,"CSTR - Zeichenkette","Default","Toggle"),
      cCmdLine::OPTION(enum_value,enum_symbols,1,"ENUM=(eins+zwei+drei+vier)"),
      cCmdLine::OPTION(function,1,"FUNC - Funktion"),
      cCmdLine::OPTION(cCmdLine::HelpOption,1,"? - Hilfe, Hilfe!",0,"3"),
      cCmdLine::OPTION() // Endmark
   };

   cout << "Aufruf: ";
   show_argvec(argc, argv);

   cout << "VOR Parse:  Integer = " << int_value <<
           "  Enum = " << enum_value <<
           "  Double = " << dbl_value <<
           "  Bool = " << bool_value <<
           "  cString = " << cstr_value << endl <<
           "--------------------------------" << endl;

   cCmdLine cmdline(table);
   cmdline.parseCommandLine(argc, argv);

   cout << cString(33,"Katze") << endl <<
           "NACH Parse:  Integer = " << int_value <<
           "  Enum = " << enum_value <<
           "  Double = " << dbl_value <<
           "  Bool = " << bool_value <<
           "  cString = " << cstr_value << endl <<
           "--------------------------------" << endl;

   int argc_remove = argc;
   cmdline.parseCommandLineRemove(argc_remove, argv);

   cout << "--------------------------------" << endl <<
           "Umsortiert: ";
   show_argvec(argc, argv);
   cout << "Reduziert: ";
   show_argvec(argc_remove, argv);

   return 0;
}

#endif

