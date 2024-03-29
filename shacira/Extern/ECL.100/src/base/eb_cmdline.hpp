/*.SH.*/

/*
 *  Headerfile for module eb_cmdline
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_cmdline.cpp on Monday March 18 2002  20:52:54
 */

#ifndef __eb_cmdline__
#define __eb_cmdline__

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

#endif

/*.EH.*/
