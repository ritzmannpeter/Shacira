// ===========================================================================
// et_tomate.cpp                                 ECL (ET's Tiny Class Library)
//                                                        Autor: Markus Wuertz
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cTomate
//
//    cTomConsole
//
//    cTomThread
//
// Datentypen:
//    Tom_TYPE
//    Tom_FUNC
//    Tom_NAMES
//
//
// Darueber hinaus werden fogende GLOBALE FUNKTIONEN exportiert:
//    ...
//
// Macros:
//    ...
//
// ===========================================================================


#include "tom/et_tomate.hpp"

/*
*  Uebersetzungsvarianten:
*
*  #undef PTRSIZE    - Zeiger werden nicht unterstuertzt ???
*  #define PTRSIZE 2 - Zeiger werden mit 16-Bit dargestellt (unsigned short)
*  #define PTRSIZE 4 - Zeiger werden mit 32-Bit dargestellt (unsigned long)
*/
#define PTRSIZE 4
#define INTSIZE 4

#define USE_MORE 1      // <more> bei langen Ausgaben 0=aus, 1=ein
#define USE_CHECK 0     // Kontrolle des alten Tabellenendes (funktioniert
                        // nicht bei DLL)


#ifdef __INTERFACE__

#ifdef NO_ECL
#define USE_THREAD 0
#else
#define USE_THREAD 1    // Tomate-Thread (aus ECL) 0=aus, 1=ein
#endif

#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <conio.h>

#if USE_THREAD
   // bisher einzige Abhaengigkeit von der restlichen ECL
   #include "base/eb_thread.hpp"
#endif


// ===========================================================================
// Definition cTomConsole
// ---------------------------------------------------------------------------
//
// cTomConsole -  (virtuelle) Konsolenklasse, die Defaultimplementierung
//                benutzt die 0815-Funktionen aus conio.h
//
// ---------------------------------------------------------------------------

#if defined __ECL_ICC__
   // Hier sind cgets und cputs als Makros definiert... Was fatal ist
   // fuer die Verwendung dieser Namen als Klassen-Komponenten...
   #undef cputs
   #undef cgets
   inline int cputs(const char *s) { return _cputs((char *)(void *)s); }
   inline char *cgets(char *b) { return _cgets(b); }
#endif

class __ECL_DLLEXPORT__ cTomConsole {
public:
   // von der Tomate benutzte Funktionen:
   virtual int io_getch();
   virtual int io_cputs(const char *str);
   virtual char *io_cgets(char *buf);
   virtual int io_vprintf(const char *fmt, va_list arg);
   // (noch) nicht benutzte Funktionen ...
   virtual int io_putch(int ch);
   virtual int io_kbhit();
};


// ---------------------------------------------------------------------------
// Exportierte Datentypen
// ---------------------------------------------------------------------------

/*
 *  TYPNAME:
 *     Tom_TYPE - die alles erschlagende Struktur der Tom-Tabellen
 *
 *  TYPDEFINITION:
 *     [RECORD
 *        func [char*(*)(char*,Tom_TYPE*)] - Adresse der Aktionsfunktion
 *        value [int] - Integer-Parameter
 *        ptr1 [void*] - erster Zeiger-Parameter, am Tabellenende Zeiger
 *                          auf Initialisierungs-Funktion oder NULL.
 *        ptr2 [void*] - zweiter Zeiger-Parameter, am Tabellenende Zeiger
 *                          auf Deinitialisierungs-Funktion oder NULL.
 *        minlen [int] - Mindestlaenge des Tokens, besondere Faelle sind:
 *                          = 0 --> Tabellenende
 *                          = -1 --> Default-Eintrag, passt immer
 *                          ACHTUNG: 0 und -1 werdem getauscht werden !!!
 *                          = -2 --> Dummy-Eintrag, passt niemals
 *                          = -3 --> Protect-Eintrag, hat kein Token
 *        token [char*] - Token (mit Hilfe-Text), besondere Faelle sind:
 *                          Tabellenende: Prompt, ggf. mit %d oder NULL
 *                              wenn kein spezielles Prompt gewuenscht ist
 *                          Default/Dummy-Eintrag: nur fuer Ausgabe
 *                          Protect-Eintrag: immer NULL, sprich nix
 *     ]
 *
 *  BEMERKUNGEN:
 *     Der Aufbau der Struktur ist nicht Teil der Tomate-Schnittstelle. Die
 *     Komponenten und deren Bedeutung kann sich jederzeit wieder aendern!!!
 */
typedef struct _tomtype {
   char *(*func) ( char*, struct _tomtype* );
   int  value;
   void *ptr1;
   void *ptr2;
   int minlen;
   char *token;
} Tom_TYPE;


/**
 * TYPNAME
 *    Tom_FUNC - Typ der handelsueblichen Tomaten-Funktionen
 *
 * TYPDEFINITION:
 *    ...
 */
typedef char *(*Tom_FUNC) ( char*, Tom_TYPE* ) ;


/*
 *  TYPNAME:
 *     Tom_NAMES - Verbindung zwischen Variablen und symbolischen Namen
 *
 *  TYPDEFINITION:
 *     [RECORD
 *        var [void*] - Zeiger auf Variable
 *        sym [Tom_TYPE *] - Tom-Tabelle mit Symbolen dazu
 *     ]
 *
 *  BEMERKUNGEN:
 *     Bei Tom_VIEW, Tom_SET und Tom_RESET wird bei den Typen _ENUM und _MASK
 *     statt der Variablen-Adresse immer ein Zeiger auf eine Tom_NAMES-Struk-
 *     tur uebergeben um die Verbindung zu den symbolischen Namen zu schaffen.
 */
typedef struct {
   void *var;
   Tom_TYPE *sym;
} Tom_NAMES;



// ---------------------------------------------------------------------------
// Konstanten zur Kennzeichnung der Datentypen / sonstige Konstanten
// ---------------------------------------------------------------------------

enum {
   _char,      // (signed) char
   _short,     // (signed) short int
   _int,       // (signed) int
   _long,      // (signed) long int
   _uchar,     // unsigned char
   _ushort,    // unsigned short int
   _uint,      // unsigned int
   _ulong,     // unsigned long int
   _bool,      // bool
   _float,     // float
   _double,    // double
   _ldouble,   // long double

   _ptr,       // void*
   _TEXT,      // char*
   _STR,       // char[]

   _ENUM,      // Aufzaehltyp (int)
   _MASK,      // Bitmasken (unsigned int)

   _DEG,       // Radiant??? / Grad??? (double)

   _ENUM_O,    // Aufzaehltyp OHNE Tom_NAMES-Struktur
   _MASK_O,    // Maskentyp OHNE Tom_NAMES-Struktur

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   Tom_BREAK = 22222    // besonderer Abbruch-Level fuer Tom_Jump
};



// ---------------------------------------------------------------------------
// DIE TOMATEN - HAUPTKLASSE
// ---------------------------------------------------------------------------

class __ECL_DLLEXPORT__ cTomate {

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Parametrisierungs- und interne Konstanten
private:
   enum {
      TOM_ISTACK_MAX =   10,  // Schachtelungstiefe fuer Eingabedateien

      TOM_BUF_MAX    =  100,  /* Laenge des Eingabepuffers */
      TOM_TOK_MAX    =   32,  /* max. Tokenlaenge fuer Ausgabe */
      TOM_STK_MAX    =   10,  /* Groesse des Zeilenstack */
      TOM_PRM_MAX    =   40,  /* maximale Pfadlaenge im Prompt */

      TOM_OCON       = 0x01,  /* Masken fuer TomOMode */
      TOM_OFILE      = 0x02
   };
   #define TOM_AUTO_VAR "ECL_AUTOMATE"


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Sonstige Konstanten
public:
   enum {
      // Diese Konstanten stehen beim Aufruf irgendwelcher Gate-Funktionen in
      // der Komponente "value" des beigepackten Tom-Tabellen-Eintrages.
      // Nur so, just for fun, aus Langeweile ...
      TOM_IDINIT    = 1,   // Kennzeichnung fuer Tom_GATES/init-Funktion
      TOM_IDEXIT    = 2,   // Kennzeichnung fuer Tom_GATES/exit-Funktion
      TOM_IDPARAM   = 3,   // Kennzeichnung fuer Tom_GPARAM-Funktion
      TOM_IDLEVEL   = 4,   // Kennzeichnung fuer Tom_GLEVEL-Funktion
      TOM_IDPROTECT = 5,   // Kennzeichnung fuer Tom_PROTECT-Funktionen

      // Werte von TOM_ENDE & TOM_DEFAULT am 16.05.2000 geaendert !!!
      // Dadurch werden alte (falsche) Default-Eintraege zu einem Tabellenende !!!
      TOM_DEFAULT    =    0,  /* minlen fuer Default-Eintrag, neuer Code */
      TOM_DEFAULT1   =   -1,  /* minlen fuer Default-Eintrag, alter Code */
      TOM_DUMMY      =   -2,  /* minlen fuer Dummy-Eintraege */
      TOM_PROTECT    =   -3,  /* minlen fuer Protect-Eintraege */
      TOM_ENDE       =   -4   /* minlen fuer Tabellenende, frueher 0 */
   };


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // interne Datentypen
private:
   /*
    *
    * TYPNAME:
    *    Tom_ENV - Garten-Typ fuer Tomaten-Umgebungsvariable
    *
    * BESCHREIBUNG:
    *    Dieser Typ ist *NICHT* Teil irgendeiner Schnittstelle !!!
    *
    */

   typedef struct _tomenv {
      /* Allgemeiner Teil mit der Umgebungsverzeigerung: */
      struct _tomenv *envold;  /* Zeiger auf vorangehende Umgebung */
      jmp_buf jmpbuf;          /* Zustandsvariable fuer longjmp */
      int level;               /* Nummer der Umgebung */

      /* Identifikation der Funktion aus der die Umgebung ist: */
      bool start;              /* true = Tom_Start, false = Tom_Level */

      Tom_TYPE *shortcut;      /* Benutzerdefinierte immer-Befehle,
                                  wird nur in Tom_Start gesetzt */

      /* nur in Tom_Level-Umgebungen definierte Komponenten: */
      Tom_TYPE *curtt;         /* aktuelle Tom-Tabelle */
      char *prompt;            /* Prompt der Umgebung */
   } Tom_ENV;

   /* Struktur fuer Zeilenstack: */
   typedef struct {
      char *line;
      char **script;
   } Tom_LINE;


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // offizielle Schnittstelle
public:
   // ehemals: void Tom_Init ( ToCo_INTERFACE *toco );
   cTomate(cTomConsole *toco=NULL);
   // ehemals: void Tom_Exit ( void );
   ~cTomate();

   // Kommandozeile hinterlegen
   static void Arg( int argc, char **argv );

   // klassischer Tomate-Start
   static void Start ( Tom_TYPE *root, Tom_TYPE *global );

   #if USE_THREAD
      // Tomate in einem eigenen Thread starten
      void Thread ( Tom_TYPE *root, Tom_TYPE *global );
   #endif

   static int _vprintf ( char* , va_list );     // Aufrufmacro: Tom_vprintf
   static char *_GetS ( char*, char* );         // Aufrufmacro: Tom_GetS
   static int _Jump ( int );                    // Aufrufmacro: Tom_Jump
   static bool _GetLong ( char**, long* );      // Aufrufmacro: Tom_GetLong
   static bool _GetInt ( char**, int* );        // Aufrufmacro: Tom_GetInt
   static bool _GetDouble ( char**, double* );  // Aufrufmacro: Tom_GetDouble
   static bool _GetArg ( char**, char*, int );  // Aufrufmacro: Tom_GetArg
   static bool _GetStr ( char**, char*, int );  // Aufrufmacro: Tom_GetStr
   // int Tom_printf ( char*, ... );            // globale (Igitt) Funktion
   static char *_PutEnum( int, Tom_TYPE* );     // Aufrufmacro: Tom_PutEnum

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // interne Aktionsfunktionen fuer die Tomaten-Tabellen-Konstruktions-Macros
public:
   static char *_Param ( char *line, Tom_TYPE *tt );
   static char *_With ( char *line, Tom_TYPE *tt );
   static char *_Level ( char *line, Tom_TYPE *tt );
   static char *_Script ( char *line, Tom_TYPE *tt );
   static char *_Alias ( char *line, Tom_TYPE *tt );
   static char *_Dummy ( char *line, Tom_TYPE *tt );
   static char *_DummyEnd ( char *line, Tom_TYPE *tt );

   static char *_Set ( char *line, Tom_TYPE *tt );
   static char *_Reset ( char *line, Tom_TYPE *tt );
   static char *_View ( char *line, Tom_TYPE *tt );
   static char *_Const ( char *line, Tom_TYPE *tt );


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // "echte" interne Funktionen ...
private:
   static void Tom_LnPush ( char *, char ** );
   static char *Tom_LnPop ( void );

   static char *TomCompTokens ( char*, char*, int );
   static Tom_TYPE *TomFindToken ( Tom_TYPE*, char*, char** );
   static Tom_TYPE *TomEscape ( Tom_TYPE*, char*, char** );
   static char *TomPutWord ( char* );
   static char *TomPutEnum ( int*, Tom_TYPE* );
   static char *TomGetEnum ( char*, int*, Tom_TYPE* );
   static char *TomPutMask ( unsigned int*, unsigned int*, Tom_TYPE* );
   static char *TomGetMask ( char*, unsigned int*, unsigned int*, Tom_TYPE* );
   static char *TomPutPath ( Tom_ENV*, char*, int, int );
   static void TomTokList ( Tom_TYPE* );


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // ... und Daten
private:
   static bool TomQuiet;                        // Ausgabe unterdruecken
   static bool TomPrompt;                       // true fuer Pfad-Prompt, false sonst

   static int TomOMode;                         // Ausgabemode: b0=Con, b1=File
   static FILE *TomOFile;                       // Ausgabestrom
   static FILE *TomIFile;                       // Eingabestrom

   static FILE *TomIStack[TOM_ISTACK_MAX];      // Stack fuer Eingabedateien
   static int TomIStackPtr;                     // Index in TomIStack

   static int TomMore;                          // Eingestellte More-Zeilenzahl
   static int TomMCnt;                          // aktueller More-Zeilenzaehler
   static char TomBuf[TOM_BUF_MAX];             // Eingabepuffer

   static bool TomDefCon;                       // true bei Standard-Konsole
   static cTomConsole *TomCon;                  // Konsolen-Treiber

   static Tom_LINE TomLnStack[TOM_STK_MAX];     // Feld fuer Zeilenstack
   static int TomLnSP;                          // Zeilenstack-Zeiger

   static Tom_ENV *Tom_Env;                     // Umgebungs-Struktur

   static int TomTID;                           // Thread-ID

   static int TomArgC;                          // Kommandozeile
   static char **TomArgV;

   // Helferlein, die die Tomate verstaendlicher lesbarer machen
   static const char * const TomTypes[];        // Typenbezeichner
   static const int TomSizes[];                 // Groessen der Datentypen (fuer Tom-Tools)
   static const bool TomHelp[];                 // Typen mit Minimal-Hilfe ## und die anderen ???
   static const Tom_TYPE cTomate::TomBools[];   // erlaubte Bool-Werte


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Zugriffsfunktionen fuer die internen Variablen (zur besonderen Verwendung)
public:
   // Umgebungsinformationen fuer ToTo_Tree
   static void getTomEnv( char **prompt, int *level, Tom_TYPE **tomtab );
   static const int *getTomSizes();
   // Thread-ID festhalten
   static void setTid(int tid);


   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // interne Tomaten-Konstruktionen zur Steuerung der Tomate
private:
   // Wurzel der immer-und-ueberall erreichbaren Tom-Befehle
   static const Tom_TYPE TomInternal[];

   // Aktionsfunktion der Tomatensteuerung
   static char *_tomcontrol( char *line , Tom_TYPE *tt );
   // Kennungen der verfuegbaren Funktionalitaeten
   enum {
      TOM_ECHO,
      TOM_VIEW,
      TOM_PATH,
      TOM_GOTO,
      TOM_OUTF,
      TOM_WAIT,
      TOM_CHWD,
      TOM_RUNS,
      TOM_VSET,
      TOM_VGET,
      TOM_VINS,
      TOM_VCMD
   };
   // weitere Tabellenteile ...
   static const Tom_TYPE _tompath[];      // Moeglichkeiten des PATH-Befehls
   static const Tom_TYPE _tomquiet[];     // Moeglichkeiten des QUIET-Befehls
   static const Tom_TYPE _tomofile[];     // Moeglichkeiten der Ausgabeumleitung
   static const Tom_TYPE _tomfunc[];      // immer-und-ueberall Tom-Befehlen
   static const char _tomhelp[];          // Text der bei HELP ausgegeben wird
   static const char _tomversion[];       // Text der bei VERSION ausgegeben wird
};



// ===========================================================================
// Definition cTomThread
// ---------------------------------------------------------------------------
//
// cTomThread -
//
// ---------------------------------------------------------------------------

class cTomThread : public cThread {
   Tom_TYPE *root;
   Tom_TYPE *global;
public:
   cTomThread() : cThread( cThread::tdAutoDel) {}
   void setParameter(Tom_TYPE *r, Tom_TYPE *g) { root = r; global = g; }

   virtual int onMain(void *extra);
};


// ---------------------------------------------------------------------------
// globale Funktionen / Macros fuer statische Funktionen
// ---------------------------------------------------------------------------

//## TBD Doku

__ECL_EXP1__ int __ECL_EXP2__ Tom_printf ( char*, ... );

#define Tom_vprintf( fmt , ap )        cTomate::_vprintf( fmt , ap )
#define Tom_GetS( prompt, str )        cTomate::_GetS( prompt, str )
#define Tom_Jump( level )              cTomate::_Jump( level )
#define Tom_GetLong( line, value )     cTomate::_GetLong( line, value )
#define Tom_GetInt( line, value )      cTomate::_GetInt( line, value )
#define Tom_GetDouble( line, value )   cTomate::_GetDouble( line, value )
#define Tom_GetArg( line, buf, size )  cTomate::_GetArg( line, buf, size )
#define Tom_GetStr( line, buf, size )  cTomate::_GetStr( line, buf, size )
#define Tom_PutEnum( var, tt )         cTomate::_PutEnum( var, tt )
// macht ein statischer Start Sinn? Frueher war es jedenfalls moeglich ...
#define Tom_Start( root, global )      cTomate::Start( root, global )



// ---------------------------------------------------------------------------
// Macros zur Konstruktion der Tomate-Tabellen
// ---------------------------------------------------------------------------

/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_COMMENT - Kommentare in Tabelle erzeugen
*
*  AUFRUF:
*     Tom_COMMENT( comment )
*
*  PARAMETER:
*     comment IN [char *] - beliebiger Text der bei '?' an dieser Stelle
*        in der Tabelle ausgegeben wird.
*
**.EC.***********************************************************************/

/**
 * Dummy-Zeile die lediglich einen Text (Kommentar) anzeigt
 */
#define Tom_COMMENT( str ) \
               (Tom_FUNC) cTomate::_Dummy , 0 , NULL , NULL , cTomate::TOM_DUMMY, str ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_PROMT - Tabellenende bei Eingabestufen
*     Tom_GATES - Tabellenende bei Eingabestufen mit Ein/Ausgangskontrolle
*     Tom_ENDE - Ende bei allen anderen Tabellen
*
*  AUFRUF:
*     Tom_PROMPT( prompt )
*     Tom_GATES( init, exit, prompt )
*     Tom_ENDE()
*
*  PARAMETER:
*     prompt IN [char *] - Prompt-String, ein %d wird durch die Nummer der
*        aktuellen Eingabestufe ersetzt (oder NULL fuer ein Default-Prompt).
*     init IN [char *(*)(char*,Tom_TYPE*)] - Adresse einer Benutzerfunktion
*        die beim Betreten einer Eingabestufe zur Initialisierung aufgerufen
*        wird oder NULL wenn darauf verzichtet wird.
*     exit IN [char *(*)(char*,Tom_TYPE*)] - Adresse einer Benutzerfunktion
*        die beim Verlassen einer Eingabestufe zur Deinitialisierung aufge-
*        rufen wird oder NULL wenn darauf verzichtet wird.
*
*  BEMERKUNGEN:
*     Eines dieser Macros muss am Ende JEDER Tabelle stehen. Die Funktionen
*     init und exit muessen folgender Definition entsprechen:
*
*     AUFRUF:
*        rest = init( line , tt )
*        rest = exit( line , tt )
*
*     PARAMETER:
*        rest RESULT [char *] - NULL falls das Betreten bzw. das Verlassen
*           der Eingabestufe nicht erlaubt ist, sonst noch nicht ausgewer-
*           teter Teil der uebergebenen Eingabezeile (oder sonst eine Zeile
*           mit der weitergearbeitet werden soll).
*        line IN [char *] - Eingabezeile fuer Parameterauswertung, wird
*           i. d. R. immer zurueckgegeben, wenn der Funktionswert nicht
*           NULL ist.
*        tt IN [Tom_TYPE *] - Variable mit dem Tom-Tabellen-Eintrag, der
*           die Definition der Gate-Funktion(en) und es Prompts enthaelt.
*           Folgende Komponente ist immer belegt:
*
*              tt->value = TOM_IDINIT - beim Aufruf der Init-Funktion.
*              tt->value = TOM_IDEXIT - beim Aufruf der Exit-Funktion.
*
*           Beim Aufruf einer Init-Funktion koennen noch die folgenden
*           Komponenten (sinnvoll) geaendert werden:
*
*              tt->token [char *] - Prompt-String mit dem sich diese
*                 Eingabestufe melden soll (dynamische Prompts).
*              tt->ptr2 [char *(*)(char*,Tom_TYPE*)] - Zeiger auf die
*                 Exit-Funktion, die beim Verlassen der Eingabestufe
*                 aufgerufen werden soll.
*
*           Als Default sind die in der Tabellen-Definition angegebenen
*           Werte eingetragen.
*
**.EC.***********************************************************************/

/**
 * Tabellenende mit Prompt (bei Eingabestufen)
 */
#define Tom_PROMPT( str ) \
               (Tom_FUNC) cTomate::_DummyEnd , 0 , NULL , NULL , cTomate::TOM_ENDE, str

/**
 * Tabellenende mit Prompt und Initialisierungs/Deinitialisierungsfunktionen
 */
#define Tom_GATES( onEnter , onLeave , str ) \
               (Tom_FUNC) cTomate::_DummyEnd , 0 , (void *) onEnter , (void *) onLeave , cTomate::TOM_ENDE, str

/**
 * Tabellenende ohne Prompt (bei einfachen Parameterstufen)
 */
#define Tom_ENDE( ) \
               (Tom_FUNC) cTomate::_DummyEnd , 0 , NULL , NULL , cTomate::TOM_ENDE, NULL


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_LEVEL - Verweis auf naechste Eingabestufe
*     Tom_PARAM - Verweis auf naechste Tokenstufe
*
*  BESCHREIBUNG:
*     Mit diesen Elementar-Macros wird die Baumstruktur der Tomate realisiert,
*     mit Tom_LEVEL erreichte Eingabestufen muessen wieder explizit mit '.'
*     oder '/' verlassen werden.
*
*  AUFRUF:
*     Tom_LEVEL( tomtab, minlen, token )
*     Tom_PARAM( tomtab, minlen, token )
*
*  PARAMETER:
*     tomtab IN [Tom_TYPE *] - die Tom-Tabelle der naechsten Stufe
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
**.EC.***********************************************************************/

/**
 * Verweis auf naechste Eingabestufe
 */
#define Tom_LEVEL( tomptr , min , token ) \
               (Tom_FUNC) cTomate::_Level , 0 , (void*)(tomptr) , NULL , min , token ,

/**
 * Verweis auf naechste Tokenstufe
 */
#define Tom_PARAM( tomptr , min , token ) \
               (Tom_FUNC) cTomate::_Param , 0 , (void*)(tomptr) , NULL , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_GLEVEL - Verweis auf naechste Eingabestufe (mit Gatefunktion)
*     Tom_GPARAM - Verweis auf naechste Tokenstufe (mit Gatefunktion)
*
*  BESCHREIBUNG:
*     Diese Macros sind Varianten von Tom_PARAM und Tom_LEVEL mit einer
*     Gate-Funktion, die nach erkennen des aktuellen Tokens immer auf-
*     gerufen wird, noch bevor die nachfolgende Tom-Tabelle bearbeitet
*     wird.
*
*  AUFRUF:
*     Tom_GLEVEL( tomtab, gate, minlen, token )
*     Tom_GPARAM( tomtab, gate, minlen, token )
*
*  PARAMETER:
*     tomtab IN [Tom_TYPE *] - die Tom-Tabelle der naechsten Stufe
*     gate IN [char *(*)(char*,Tom_TYPE*)] - Adresse der Gatefunktion
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BEMERKUNGEN:
*     Der Funktionswert NULL von gate hat, im Gegensatz zu anderen Gate-
*     funktionen, keinen unmittelbaren Abbruch zur Folge. Lediglich die
*     Textzeile wird geloescht. Definition der Funktion gate:
*
*     AUFRUF:
*        rest = gate( line , tt )
*
*     PARAMETER:
*        rest RESULT [char *] - noch nicht ausgewerteter Teil der ueber-
*           gebenen Eingabezeile, NULL verwirft nur die Eingabe.
*        line IN [char *] - Eingabezeile fuer Parameterauswertung, wird
*           i. d. R. immer zurueckgegeben.
*        tt IN [Tom_TYPE *] - Variable mit dem Tom-Tabellen-Eintrag, der
*           die Definition der Gate-Funktion enthaelt. Folgende Komponente
*           ist immer belegt:
*
*              tt->value = TOM_IDPARAM - beim Aufruf der Param-Funktion.
*              tt->value = TOM_IDLEVEL - beim Aufruf der Level-Funktion.
*
*           Es kann folgende Komponente (sinnvoll) geaendert werden:
*
*              tt->ptr1 [Tom_TYPE *] - Zeiger auf die nachgeschaltete
*                 Tom-Tabelle mit der Definition der Parameter- bzw.
*                 Eingabestufe, die erreicht werden soll. Default ist
*                 der Wert aus der Tabellen-Definition.
*
*     Bei Tom_LEVEL ist diese Gate-Funktion unabhaengig von via Tom_GATES
*     definierten Funktionen, d.h. um einen Level koennen sich bis zu drei
*     Gate-Funktionen tummeln. Damit kann man viele schweinische Dinge
*     machen, nicht?
*
**.EC.***********************************************************************/

#define Tom_GPARAM( tomptr , gate , min , token ) \
               (Tom_FUNC) cTomate::_Param , 0 , (void*)(tomptr) , (void*)(gate) , min , token ,

#define Tom_GLEVEL( tomptr , gate , min , token ) \
               (Tom_FUNC) cTomate::_Level , 0 , (void*)(tomptr) , (void*)(gate) , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_WITH - Verweis auf naechste Tokenstufe (mit besonderen Parametern)
*
*  BESCHREIBUNG:
*     Noch eine trickreiche Variante von Tom_PARAM mit der zwei (!) unter-
*     schiedliche Tokenstufen vermischt werden koennen: Mit dem aktuellen
*     Tabelleneintrag wird die Aktionsfunktion der mit tomtab nachfolgenden
*     Stufe aufgerufen!
*
*  AUFRUF:
*     Tom_WITH( value , ptr1 , tomtab, minlen, token )
*
*  PARAMETER:
*     value IN [int] - Tabelleneintrag 'value'
*     ptr1 IN [void*] - Tabelleneintrag 'ptr1'
*     tomtab IN [Tom_TYPE *] - die Tom-Tabelle der naechsten Stufe
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BEMERKUNGEN:
*     Es koennen in der nachgeschalteten Tabelle nur Aktionsfunktionen ver-
*     wendet werden, die sich am Parameter ptr2 = NULL nicht stoeren, egal
*     ob vom Benutzter oder intern definiert.
*
*
**.EC.***********************************************************************/

#define Tom_WITH( value , ptr1 , tomptr , min , token ) \
               (Tom_FUNC) cTomate::_With , (int)(value) , (void*)(ptr1) , (void*)(tomptr) , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_SET - Variable eines bestimmten Typs setzen
*     Tom_RESET - Bitmaske in Variable ruecksetzen
*
*  AUFRUF:
*     Tom_SET( type, ptr, minlen, token )
*     Tom_RESET( type, ptr, minlen, token )
*
*  PARAMETER:
*     type IN [int] - Variablentyp
*     ptr IN [void*] - Zeiger auf die Variable bzw. Variablenreferenz
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BEMERKUNGEN:
*     Die Typen _TEXT und _PTR koennen nicht veraendert werden. Beim Typ
*     _STR wird der gesamte Rest der Eingabezeile unabhaengig von der
*     Groesse des char-Feldes kopiert.
*     Tom_RESET ist nur fuer Variablen vom Typ _MASK definiert und unter-
*     scheidet sich von Tom_SET nur dadurch, dass der in Tom_MASK angegebene
*     Wert fuer 'value' negiert wird (_ON wird zu _OFF und umgekehrt).
*
**.EC.***********************************************************************/

#define Tom_SET( type , varptr , min , token ) \
               (Tom_FUNC) cTomate::_Set , (int)(type) , (void*)(varptr) , NULL , min , token ,

#define Tom_RESET( type , varptr , min , token ) \
               (Tom_FUNC) cTomate::_Reset , (int)(type) , (void*)(varptr) , NULL , min , token ,

#define Tom_SET_ENUM( tomptr , varptr , min , token ) \
               (Tom_FUNC) cTomate::_Set , (int)_ENUM_O , (void*)(varptr) , (void*)(tomptr) , min , token ,

/* ## Erweiterung ???
#define Tom_SET_MASK( tomptr , varptr , min , token ) \
               Tom_Set , (int)_MASK_O , (void*)(varptr) , (void*)(tomptr) , min , token ,

#define Tom_RESET_MASK( tomptr , varptr , min , token ) \
               Tom_Set , (int)_MASK_O , (void*)(varptr) , (void*)(tomptr) , min , token ,
*/


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_VIEW - Variable eines bestimmten Typs anzeigen
*     Tom_VIEW_ENUM - Enum-Variable anzeigen
*     Tom_VIEW_MASK - Bitmaske anzeigen
*
*  AUFRUF:
*     Tom_VIEW( type, ptr, minlen, token )
*     Tom_VIEW_ENUM( symbols, ptr, minlen, token )
*     Tom_VIEW_MASK( symbols, ptr, minlen, token )
*
*  PARAMETER:
*     type IN [int] - Variablentyp
*     symbols IN [Tom_TYPE*] - Tom-Tabelle mit den Symbolinformationen
*     ptr IN [void*] - Zeiger auf die Variable
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BEMERKUNGEN:
*     Ausser beim Typ _TEXT wird immer noch der vollstaendige Tokenname und
*     der Variablentyp mit ausgegeben.
*
**.EC.***********************************************************************/

#define Tom_VIEW( type , varptr , min , token ) \
               (Tom_FUNC) cTomate::_View , (int)(type) , (void*)(varptr) , NULL , min , token ,

#define Tom_VIEW_ENUM( tomptr , varptr , min , token ) \
               (Tom_FUNC) cTomate::_View , (int)_ENUM_O , (void*)(varptr) , (void*)(tomptr) , min , token ,

#define Tom_VIEW_MASK( tomptr , varptr , min , token ) \
               (Tom_FUNC) cTomate::_View , (int)_MASK_O , (void*)(varptr) , (void*)(tomptr) , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_CONST - Variable mit Konstante belegen
*
*  AUFRUF:
*     Tom_CONST( type, ptr, value, minlen, token )
*
*  PARAMETER:
*     type IN [int] - Variablentyp
*     ptr IN [void*] - Zeiger auf die Variable
*     value IN [???] - Konstante entsprechend dem Variablentyp
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BEMERKUNGEN:
*     Initialisierungen fuer _STR sind nicht moeglich. Alle Initialisierungs-
*     werte in 'value' werden als 'void*' abgespeichert, Reibungsverluste
*     massgeblicher Stellen sind bei der hin- und her-casterei moeglich!
*
**.EC.***********************************************************************/

#define Tom_CONST( type , varptr , value , min , token ) \
               (Tom_FUNC) cTomate::_Const , (int)(type) , (void*)(varptr) , (void*)(value) , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_ENUM - Komponente eines Enum-Typs definieren
*     Tom_MASK - Bitmaske eines Masken-Typs definieren
*
*  BESCHREIBUNG:
*     Eine Enum- oder Masken-Definition besteht aus einer Tom-Tabelle die
*     ausser dem Tom_ENDE() am Schluss nur aus Tom_ENUM- bzw. Tom_MASK-
*     Macros bestehen.
*
*  AUFRUF:
*     Tom_ENUM( value, minlen, token )
*     Tom_MASK( value, mask, minlen, token )
*
*  PARAMETER:
*     value IN [int] - Wert der Enum-Komponente
*     mask IN [unsigned int] - Bitmaske
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
*  BESCHREIBUNG:
*     Fuer 'value' in Tom_MASK gibt's noch Konstanten: _ON und _OFF
*
**.EC.***********************************************************************/

#define Tom_ENUM( value , min , token ) \
               (Tom_FUNC) cTomate::_Dummy , (int)(value) , NULL , NULL , min , token ,

#define Tom_MASK( value , mask , min , token ) \
               (Tom_FUNC) cTomate::_Dummy , (int)(value) , (void*)(mask) , NULL , min , token ,


/**.SC.***********************************************************************
*
*  KONSTANTENNAME:
*     _ON - Bits in einer Maske setzen
*     _OFF - Bits in einer Maske ruecksetzen
*
**.EC.***********************************************************************/

#define _OFF   0
#define _ON   ~0


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_SCRIPT - Befehlssequenz abarbeiten
*     Tom_ALIAS - Token durch Befehlszeile ersetzen
*
*  BESCHREIBUNG:
*     'tomtab' ist der Level (!) von dem aus die Script-Befehle abgearbeitet
*     werden. Die Befehlsliste muss mit NULL enden.
*
*  AUFRUF:
*     Tom_SCRIPT( script, tomtab, minlen, token )
*     Tom_ALIAS( cmdline, minlen, token )
*
*  PARAMETER:
*     script IN [char **] - Befehlsliste, mit NULL abgeschlossen.
*     cmdline IN [char *] - Befehlszeile die nach dem Token weiter
*        ausgefuehrt werden soll.
*     tomtab IN [Tom_TYPE *] - Level (!) auf den sich die Befehle beziehen.
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
**.EC.***********************************************************************/

#define Tom_SCRIPT( script , tomptr , min , token ) \
               (Tom_FUNC) cTomate::_Script , 0 , (void*)(script) , (void*)(tomptr) , min , token ,

#define Tom_ALIAS( cmdline , min , token ) \
               (Tom_FUNC) cTomate::_Alias , 0 , (void*)(cmdline) , NULL , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_PROTECT - Tabellenbereiche schuetzen
*
*  AUFRUF:
*     Tom_PROTECT( func )
*
*  PARAMETER:
*     func IN [char *(*)(char*,Tom_TYPE*)] - Adresse einer Benutzerfunktion
*        die an dieser Stelle bei *JEDEM* Abarbeiten einer Tom-Tabelle da-
*        rueber entscheidet, ob die nachfolgenden Tabelleneintraege beachtet
*        werden. Wird als Funktionsadresse NULL angegeben, dann gelten alle
*        eventuell bestehenden Sperren nicht mehr.
*
*  BEMERKUNGEN:
*     Die Definition der Funktion func entspricht folgendem Schema:
*
*     AUFRUF:
*        rest = func( line , tt )
*
*     PARAMETER:
*        rest RESULT [char *] - NULL sperrt die nachfolgenden Tabellen-
*           Eintraege, jeder andere Wert gibt sie frei.
*        line IN [char *] - Dummy-Parameter, garantiert nicht NULL.
*        tt IN [Tom_TYPE *] - Tom-Tabellen-Eintrag mit der Definition der
*           Schutzfunktion. Folgende Komponente ist immer fest belegt:
*
*              tt->value = TOM_IDPROTECT
*
**.EC.***********************************************************************/

#define Tom_PROTECT( func ) \
               (Tom_FUNC) func , cTomate::TOM_IDPROTECT , NULL , NULL , cTomate::TOM_PROTECT , NULL ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_USER - Benutzerfunktion ohne Parameter
*     Tom_USER_W   - ... mit int
*     Tom_USER_WW  - ... mit zwei int
*     Tom_USER_WP  - ... mit int und void*
*     Tom_USER_WPP - ... mit int und zwei void*
*     Tom_USER_P   - ... mit void*
*     Tom_USER_PP  - ... mit zwei void*
*
*  BESCHREIBUNG:
*     Es wird eine benutzerdefinierte Funktion aufgerufen:
*
*     AUFRUF:
*         rest = func( line , tt )
*
*     PARAMETER:
*         rest RESULT [char *] - noch nicht ausgewerteter Teil der ueber-
*            gebenen Eingabezeile ('line' bei Funktionen ohne Parameter
*            und NULL wenn alles verbraucht oder wegen einem Fehler ver-
*            worfen wurde).
*         line IN [char *] - Eingabezeile fuer Parameterauswertung.
*         tt IN [Tom_TYPE *] - Parameterstruktur aus der Tom-Tabelle, mit
*            den Initialisierungen wie im Konstruktionsmacro angegeben.
*
*     Der Aufruf der eigentlich zu testenden Funktionen erfolgt immer aus
*     solchen Benutzerfunktionen heraus.
*
*  AUFRUF:
*     Tom_USER( func, minlen, token )
*     Tom_USER_P( func, ptr1, minlen, token )
*     Tom_USER_PP( func, ptr1, ptr2, minlen, token )
*     Tom_USER_W( func, value, minlen, token )
*     Tom_USER_WP( func, value, ptr1, minlen, token )
*     Tom_USER_WPP( func, value, ptr1, ptr2, minlen, token )
*
*  PARAMETER:
*     func IN [char*(*)()] - Zeiger auf Benutzerfunktion
*     value IN [int] - Initialisierung fuer value-Komponente.
*     ptr1 IN [void*] - Initialisierung fuer ptr1-Komponente.
*     ptr2 IN [void*] - Initialisierung fuer ptr2-Komponente.
*     minlen IN [int] - signifikante Laenge
*     token IN [char *] - Tokenstring
*
**.EC.***********************************************************************/

#define Tom_USER( func , min , token ) \
               (Tom_FUNC) func , 0 , NULL , NULL , min , token ,

#define Tom_USER_W( func , value , min , token ) \
               (Tom_FUNC) func , (int)(value) , NULL , NULL , min , token ,

#define Tom_USER_WW( func , value , value2, min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(int)(value2) , NULL , min , token ,

#define Tom_USER_WP( func , value , ptr1 , min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(ptr1) , NULL , min , token ,

#define Tom_USER_WPP( func , value , ptr1 , ptr2 , min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(ptr1) , (void*)(ptr2) , min , token ,

#define Tom_USER_P( func , ptr1 , min , token ) \
               (Tom_FUNC) func , 0 , (void*)(ptr1) , NULL , min , token ,

#define Tom_USER_PP( func , ptr1 , ptr2 , min , token ) \
               (Tom_FUNC) func , 0 , (void*)(ptr1) , (void*)(ptr2) , min , token ,


/**.SC.***********************************************************************
*
*  MACRONAME:
*     Tom_U     - alias fuer Tom_USER
*     Tom_UW    - alias fuer Tom_USER_W
*     Tom_UWW   - alias fuer Tom_USER_WW
*     Tom_UWP   - alias fuer Tom_USER_WP
*     Tom_UWPP  - alias fuer Tom_USER_WPP
*     Tom_UP    - alias fuer Tom_USER_P
*     Tom_UPP   - alias fuer Tom_USER_PP
*
**.EC.***********************************************************************/

//## Dokumentieren -->
#define Tom_SENUM( tomptr , varptr , min , token ) \
               (Tom_FUNC) cTomate::Tom_Set , (int)_ENUM_O , (void*)(varptr) , (void*)(tomptr) , min , token ,

#define Tom_VENUM( tomptr , varptr , min , token ) \
               (Tom_FUNC) cTomate::_View , (int)_ENUM_O , (void*)(varptr) , (void*)(tomptr) , min , token ,
//## Erweiterungen ---> _MASK_O

#define Tom_U( func , min , token ) \
               (Tom_FUNC) func , 0 , NULL , NULL , min , token ,

#define Tom_UW( func , value , min , token ) \
               (Tom_FUNC) func , (int)(value) , NULL , NULL , min , token ,

#define Tom_UWW( func , value , value2, min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(int)(value2) , NULL , min , token ,

#define Tom_UWP( func , value , ptr1 , min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(ptr1) , NULL , min , token ,

#define Tom_UWPP( func , value , ptr1 , ptr2 , min , token ) \
               (Tom_FUNC) func , (int)(value) , (void*)(ptr1) , (void*)(ptr2) , min , token ,

#define Tom_UP( func , ptr1 , min , token ) \
               (Tom_FUNC) func , 0 , (void*)(ptr1) , NULL , min , token ,

#define Tom_UPP( func , ptr1 , ptr2 , min , token ) \
               (Tom_FUNC) func , 0 , (void*)(ptr1) , (void*)(ptr2) , min , token ,


#endif /*__INTERFACE__*/




// #ifdef __ICC__
// #  pragma info(noobs)  /* Ignoriere fehlende Prototypen */
// #endif
//
// #ifdef __IC386__
// #  define P2LONG(p) ( (long)((void near *)(p)) )
// #  define P2FPTR(p) ( (void near *)(p) )
// #else
#define P2LONG(p) ( (long)((void *)(p)) )
#define P2FPTR(p) p
// #endif



#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


// /* Folgendes wegen chdir() - Besser ueber IOFILE, das ist aber im CNC-Kern (noch) nicht verfuegbar */
// #if defined(__ICC__) || defined(_MSC_VER)
// #include <direct.h>
// #define chwdir(dir) _chdir(dir)
// #elif defined(__RMOS__)
// #include <direct.h>
// #define chwdir(dir) chdir(dir)
// #else
// #define chwdir(dir) -1
// #endif



// ---------------------------------------------------------------------------
// statische Variablen der Tomatenklasse
// ---------------------------------------------------------------------------

bool cTomate::TomQuiet = false;                       /* Ausgabe unterdruecken */
bool cTomate::TomPrompt = true;                       /* true fuer Pfad-Prompt, false sonst */

int cTomate::TomOMode = TOM_OCON;                     /* Ausgabemode: b0=Con, b1=File */
FILE *cTomate::TomOFile = NULL;                       /* Ausgabestrom */
FILE *cTomate::TomIFile = NULL;                       /* Eingabestrom */

FILE *cTomate::TomIStack[TOM_ISTACK_MAX];             /* Stack fuer Eingabedateien */
int cTomate::TomIStackPtr = 0;                        /* Index in TomIStack */

int cTomate::TomMore = 24;                            /* Eingestellte More-Zeilenzahl */
int cTomate::TomMCnt = 0;                             /* aktueller More-Zeilenzaehler */
char cTomate::TomBuf[TOM_BUF_MAX];                    /* Eingabepuffer */

bool cTomate::TomDefCon = true;                      /* Standard-Konsole aktiv */
cTomConsole *cTomate::TomCon = new cTomConsole;      /* Konsolen-Treiber */


cTomate::Tom_ENV *cTomate::Tom_Env = NULL;            /* Umgebungs-Struktur */

cTomate::Tom_LINE cTomate::TomLnStack[TOM_STK_MAX];   /* Feld fuer Zeilenstack */
int cTomate::TomLnSP = 0;                             /* Zeilenstack-Zeiger */

int cTomate::TomTID = -1;                             // Thread-ID

int cTomate::TomArgC = 0;                             // Kommandozeile
char **cTomate::TomArgV = NULL;

const char * const cTomate::TomTypes[] = {            // Typenbezeichner
   "char","short","int","long",
   "unsigned char","unsigned short","unsigned int","unsigned long",
   "bool","float","double","long double",
   "void*","char*","char[]",
   "ENUM","MASK","DEG","ENUM2","MASK2"
};

const int cTomate::TomSizes[] = {                     // Groessen der Datentypen
   sizeof(char), sizeof(short), sizeof(int), sizeof(long),
   sizeof(unsigned char), sizeof(unsigned short), sizeof(unsigned int), sizeof(unsigned long),
   sizeof(bool), sizeof(float), sizeof(double), sizeof(long double),
   sizeof(void*), 0, 0,
   sizeof(int), sizeof(int), sizeof(double), sizeof(int), sizeof(int)
};

const bool cTomate::TomHelp[] = {                     // ## Typen mit Minimal-Hilfe ???
   true, true, true, true,
   true, true, true, true,
   true, true, true, true,
   true, true, true,
   false, false, false,false, false
};




const Tom_TYPE cTomate::TomBools[] = {                // erlaubte Bool-Werte
   Tom_ENUM( false , 1,"False - 0" )
   Tom_ENUM( true ,  1,"True - not 0" )
   Tom_ENUM( false , 3,"OFF - Synonym for False" )
   Tom_ENUM( true ,  2,"ON - Synonym for True" )
   Tom_ENUM( false , 1,"No - Synonym for False" )
   Tom_ENUM( true ,  1,"Yes - Synonym for True" )
   Tom_ENDE()
};


// ---------------------------------------------------------------------------
// Default-Implementierung cTomConsole
// ---------------------------------------------------------------------------

int cTomConsole::io_getch()
{
   return getch();
}

int cTomConsole::io_cputs(const char *str)
{
   return cputs((char*)str);
}

char *cTomConsole::io_cgets(char *buf)
{
   fflush(stdout);
   return cgets(buf);
}

int cTomConsole::io_vprintf(const char *fmt, va_list arg)
{
   return vprintf(fmt, arg);
}

int cTomConsole::io_putch(int ch)
{
   return putch(ch);
}

int cTomConsole::io_kbhit()
{
   return kbhit();
}


// ---------------------------------------------------------------------------
// Implementierung cTomThread
// ---------------------------------------------------------------------------

int cTomThread::onMain(void * /*extra*/)
{
   try {
      cTomate::setTid( getThreadId() );
      cTomate::Start( root, global );
   } catch (...) {
      Tom_printf("TomThread: Unknown exception\n");
      //cTomate::TomCon->io_getch();
      throw;
   }
   return 0;
}


// ---------------------------------------------------------------------------
// Implementierung cTomate
// ---------------------------------------------------------------------------

cTomate::cTomate( cTomConsole *toco )
{
   if (toco != NULL) {
      if (TomDefCon) {
         delete TomCon;
         TomDefCon = false;
      }
      TomCon = toco;
   } else if (!TomDefCon) {
      TomCon = new cTomConsole;
      TomDefCon = true;
   }

   if (getenv(TOM_AUTO_VAR) != NULL) {
      const char *fspec = getenv( TOM_AUTO_VAR );
      if ((TomIFile = fopen(fspec, "r")) == NULL) {
         printf( "%s not found\n",fspec );
      } else {
         printf( "%s\n",fspec );
      }
   } else {
      printf( "%s not set\n",TOM_AUTO_VAR );
   }
}


cTomate::~cTomate()
{
   if (TomDefCon) {
      delete TomCon;
   }
}


// Umgebungsinformationen fuer ToTo_Tree
void cTomate::getTomEnv( char **prompt, int *level, Tom_TYPE **tomtab )
{
   *prompt = Tom_Env->prompt;
   *level = Tom_Env->level;
   *tomtab = Tom_Env->curtt;
}

const int *cTomate::getTomSizes()
{
   return TomSizes;
}

// Thread-ID festhalten
void cTomate::setTid(int tid)
{
   TomTID = tid;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Arg - Kommandozeile hinterlegen
*
*  AUFRUF:
*     Tom_Arg( argc, argv );
*
*  PARAMETER:
*     argc IN [int] - Anzahl der Argumente
*     argv IN [char **] - Vektor
*
**.EF.***********************************************************************/

void cTomate::Arg( int argc, char **argv )
{
   TomArgC = argc;
   TomArgV = argv;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Start - Einsprungfunktion in die magische Tomate-Welt
*
*  AUFRUF:
*     Tom_Start( root, global );
*
*  PARAMETER:
*     root IN [Tom_TYPE *] - Zeiger auf die Wurzel der Hauptstruktur
*     global IN [Tom_TYPE *] - Zeiger auf die immer-und-ueberall Befehle
*        oder NULL wenn es solche Befehle nicht gibt.
*
**.EF.***********************************************************************/

void cTomate::Start( Tom_TYPE *root , Tom_TYPE *global )
{
   Tom_TYPE rootref;
   Tom_ENV envnew;

   if (Tom_Env) {
      memcpy( &envnew, Tom_Env , sizeof(Tom_ENV) );
   } else {
      envnew.level = 0;
   }
   envnew.start = true;
   envnew.shortcut = global;
   envnew.envold = Tom_Env;
   Tom_Env = &envnew;

   rootref.ptr1 = root;
   rootref.ptr2 = NULL;
   _Level( "" , &rootref );

   Tom_Env = Tom_Env->envold;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Thread - Tomete in eigenem Thread starten ...
*
*  AUFRUF:
*     Tom_Thread( root, global );
*
*  PARAMETER:
*     root IN [Tom_TYPE *] - Zeiger auf die Wurzel der Hauptstruktur
*     global IN [Tom_TYPE *] - Zeiger auf die immer-und-ueberall Befehle
*        oder NULL wenn es solche Befehle nicht gibt.
*
**.EF.***********************************************************************/

#if USE_THREAD
void cTomate::Thread( Tom_TYPE *root , Tom_TYPE *global )
{
   cTomThread *tom_thread;
   tom_thread = new cTomThread;
   tom_thread->setParameter(root,global);
   tom_thread->start();
}
#endif




/*.Sf.***********************************************************************
*
*  FUNKTION:
*     Tom_LnPush - Zeiger auf Zeilenstack ablegen
*     Tom_LnPop - Zeiger von Zeilenstack holen
*
*  AUFRUF:
*     Tom_LnPush( line , script );
*     result = Tom_LnPop( );
*
*  PARAMETER:
*     result RESULT [char *] - Zeiger auf Zeile oder NULL wenn Stack leer
*     line IN [char *] - aktuelle Zeile die auf dem Stack abgelegt wird
*     script IN [char **] - aktuelles Script fuer den Stack
*
**.Ef.***********************************************************************/

void cTomate::Tom_LnPush( char *line , char **script )
{
   if ((TomLnSP+1) < TOM_STK_MAX) {
      TomLnStack[TomLnSP].line = line;
      TomLnStack[TomLnSP].script = script;
      TomLnSP++;
   } else {
      Tom_printf( "Tom_LnPush: line stack overflow\n" );
   }
}


char *cTomate::Tom_LnPop( void )
{
   char *line;

   if (TomLnSP) {
      if ( (TomLnStack[TomLnSP-1].script == NULL) ) {
         line = TomLnStack[--TomLnSP].line;
         return line ? line : Tom_LnPop();
      } else {
         line = *TomLnStack[TomLnSP-1].script++;
         return line ? line : (TomLnStack[TomLnSP-1].script = NULL, ".");
      }
   }

   return NULL;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Jump - Rueckspruenge in vorangegangene Eingabestufen
*
*  AUFRUF:
*     curlevel = Tom_Jump( newlevel );
*
*  PARAMETER:
*     curlevel RESULT [int] - aktuelle Eingabestufe falls newlevel 0 ist.
*     newlevel IN [int] - Nummer der neuen Eingabestufe:
*        = 0: Nummer der aktuellen Eingabestufe zurueckgeben
*        > 0: absolute Eingabestufe (wie im Prompt angezeigt, 1 fuehrt
*                zur allerhoechsten Eingabestufe zurueck)
*        < 0: relative Eingabestufe (-1 fuehrt zur letzten Stufe zurueck)
*        Tom_BREAK - aktuelle Eingabestufe (Abbruch einer Funktion)
*
*  BEMERKUNGEN:
*     Pfui, der anstaendige Programmierer benutzt diese Funktion selbst-
*     verstaendlich nicht. Sollte er doch gegen seinen Willen dazu gezwungen
*     werden ist zu beachten, dass eventuelle Gate-Funktionen am Ausgang
*     uebersprungener Eingabestufen nicht mehr aufgerufen werden und dass
*     laufende Skripts abgebrochen werden.
*
**.EF.***********************************************************************/

int cTomate::_Jump( int newlevel )
{
   int fromlevel = (newlevel == Tom_BREAK) ? -1 : Tom_Env->level;

   if (newlevel) {
      if (newlevel > 0) {
         while ((Tom_Env->envold && newlevel<Tom_Env->level) || Tom_Env->start) {
            Tom_Env = Tom_Env->envold;
         }
      } else {
         while ((Tom_Env->envold && newlevel++ < 0) || Tom_Env->start) {
            Tom_Env = Tom_Env->envold;
         }
      }
      /* Spruenge brechen allerhand ab... */
      TomLnSP = 0;
      TomMCnt = 0;
      longjmp( Tom_Env->jmpbuf , fromlevel );
   }

   return Tom_Env->level;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_vprintf - tomatespezifische vprintf-Funktion
*
*  AUFRUF:
*     result = Tom_vprintf( fmt , arg );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl der ausgegebenen Zeichen
*     fmt IN [char *] - Formatstring
*     arg IN [va_list] - Argumentliste bei Tom_vprintf
*
*  BEMERKUNGEN:
*     Die seitenweise Ausgabe (mit %more gesteuert) beruecksichtigt alle
*     '\n' im Formatstring fmt.
*
**.EF.***********************************************************************/

int cTomate::_vprintf( char *fmt , va_list ap )
{
   int len = 0;
   int nl = 0;
   char *nlp = fmt;
   int key;

   if (!TomQuiet) {
      while ((nlp = strchr(nlp,'\n')) != NULL) {
         nl++; nlp++;
      }

#if USE_MORE
      if (TomMore && (TomMCnt += nl)>=TomMore && (TomOMode==TOM_OCON)) {
         TomCon->io_cputs( "<more>" );
         key = TomCon->io_getch();
         TomCon->io_cputs( "\b\b\b\b\b\b      \b\b\b\b\b\b");
         if ( key == ' ' || key == EOF ) {
            TomMCnt = nl;
         } else if (key == '\r') {
            TomMCnt -= nl;
         } else {
            Tom_Jump( Tom_BREAK );
         }
      }
#endif

      if (TomOFile != NULL && (TomOMode & TOM_OFILE)) {
         vfprintf( TomOFile , fmt , ap );
      }
      if (TomOFile == NULL || (TomOMode & TOM_OCON)) {
         len = TomCon->io_vprintf( fmt , ap );
      }
   }

   return len;

}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_printf - tomatespezifische printf-Funktion
*
*  AUFRUF:
*     result = Tom_printf( fmt, ... );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl der ausgegebenen Zeichen
*     fmt IN [char *] - Formatstring
*     ... - variable Argumentliste bei Tom_printf
*
*  BEMERKUNGEN:
*     Die seitenweise Ausgabe (mit %more gesteuert) beruecksichtigt alle
*     '\n' im Formatstring fmt.
*
**.EF.***********************************************************************/

int Tom_printf( char *fmt , ...  )
{
   int len;
   va_list ap;

   va_start( ap , fmt );
   len = cTomate::_vprintf( fmt , ap );
   va_end( ap );

   return len;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_GetS - tomatespezifische gets-Funktion
*
*  BESCHREIBUNG: ???
*     Ueber die normale C-Funktion hinausgehend wird vor der Eingabe ein
*     Prompt ausgegeben. Waehrend der Script-Abarbeitung werden die vor-
*     definierten Zeilen als Eingaben geliefert, am Ende einer Alias-
*     Sequenz der Rest der urspruenglichen Eingabezeile.
*
*  AUFRUF:
*     result = Tom_GetS( prompt, str );
*
*  PARAMETER:
*     result RESULT [char *] - Eingabetext (nicht unbedingt str!)
*     prompt IN [char *] - Prompt
*     str IN [char *] - Eingabepuffer wie bei cgets:
*        str[0] - maximale Zahl der Eingabezeichen (Pufferlaenge-3)
*        str[1] - eingegebene Zeichenzahl
*        str[2..str[0]+2] - Eingabezeile, mit '\0' abgeschlossen
*
**.EF.***********************************************************************/

char *cTomate::_GetS( char *prompt , char *str )
{
   char *line;

   if ((line = Tom_LnPop()) != NULL) {
      return line;
   } else {
      bool oldquiet = TomQuiet;
      int oldomode = TomOMode;

      TomQuiet = false;
      TomOMode |= TOM_OCON;
      TomMCnt = 0;

      str[2] = '\0';

      while (TomIFile != NULL && str[2] == '\0') {
         if (fgets(str + 2, str[0], TomIFile) == NULL) {
            fclose( TomIFile );
            if ( TomIStackPtr > 0 ) {
               TomIFile = TomIStack[--TomIStackPtr];
            } else {
               TomIFile = NULL;
            }
         } else {
            str[1] = char(strlen(str + 2));
            if (str[1] > 0 && str[str[1]+1] == '\n') {
               str[str[1]+1] = '\0';
               str[1]--;
            }
            if (str[2] == '#') {
               str[2] = '\0';
               continue;
            }
            if (TomOFile != NULL && (TomOMode & TOM_OFILE)) {
               fprintf( TomOFile , "%s\n",str+2 );
            }
            TomOMode = oldomode;
            TomQuiet = oldquiet;
            return str+2;
         }
      }

      if (TomIFile == NULL) {
         Tom_printf( prompt,Tom_Env->level );
         Tom_printf( " " );
      }

      if (TomIFile == NULL) {
         TomCon->io_cgets( str );
      }
      Tom_printf( "\n" );
      if (TomOFile != NULL && (TomOMode & TOM_OFILE)) {
         fprintf( TomOFile , "%s\n",str+2 );
      }
      TomOMode = oldomode;
      TomQuiet = oldquiet;
      return str+2;
   }
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_GetArg - Argument-Wort aus String in Puffer kopieren
*     Tom_GetStr - String aus String in Puffer kopieren (Haeh?)
*
*  AUFRUF:
*     result = Tom_GetArg( line, s, n );
*
*  PARAMETER:
*     result RESULT [bool] - true wenn Wort/String gefunden, false sonst
*     line INOUT [char **] - Stringzeiger, wird hochgesetzt wenn Wort ok
*     s OUT [char *] - Puffer fuer Kopie des Wortes
*     n IN [int] - Pufferlaenge (Wort + '\0') oder 0 falls grenzenlos
*
*  BEMERKUNGEN:
*     Tom_GetStr erwartet ein Argument-Wort oder eine in " oder ' einge-
*     schlossene Zeichenkette. Innerhalb der Anfuehrungszeichen werden dann
*     die folgenden Escapesequenzen ausgewertet:
*        \n - Newline
*        \" - Anfuehrungszeichen
*        \' - Hochkomma
*        \\ - Backslash
*
**.EF.***********************************************************************/

bool cTomate::_GetArg( char **line , char *s , int n )
{
   bool ok;

   if ( n== 0) {
      n = INT_MAX;
   }

   while (isspace(**line)) { (*line)++; };
   if ( (ok = (**line != '\0')) != 0) {
      while (isgraph(**line)) {
         if ( n > 0 ) {
            *s++ = **line; n--;
         }
         (*line)++;
      }
   } else {
      Tom_printf( "Missing argument\n" );
   }
   *s = '\0';

   return ok;
}


bool cTomate::_GetStr( char **line , char *s , int n )
{
   bool ok;
   char next,delim;

   if ( n== 0) n = INT_MAX;
   while (isspace(**line)) (*line)++;

   if ( (ok = (**line == '"' || **line=='\'')) != 0) {
      delim = *(*line)++;
      while ( **line != '\0' && **line != delim ) {
         if (**line == '\\') {
            (*line)++;
            switch (**line) {
               case '\'':
               case '"':
               case '\\': next = **line; break;
               case 'n':  next = '\n'; break;
               default: (*line)--; next = '\\'; break;
            }
         } else {
            next = **line;
         }
         if ( n > 0 ) {
            *s++ = next; n--;
         }
         (*line)++;
      }
      if (**line == '"') (*line)++;
   } else if ( (ok = (**line != '\0')) != 0) {
      while (isgraph(**line)) {
         if ( n > 0 ) {
            *s++ = **line; n--;
         }
         (*line)++;
      }
   } else if ( (ok = (**line != '\0')) != 0) {
      while (isgraph(**line)) {
         if ( n > 0 ) {
            *s++ = **line; n--;
         }
         (*line)++;
      }
   } else {
      Tom_printf( "Missing string\n" );
   }

   *s = '\0';

   return ok;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_GetLong - long aus String in Variable
*     Tom_GetInt - int aus String in Variable
*     Tom_GetDouble - double aus String in Variable
*
*  AUFRUF:
*     result = Tom_GetLong( line, l );
*     result = Tom_GetInt( line, i );
*     result = Tom_GetDouble( line, d );
*
*  PARAMETER:
*     result RESULT [bool] - true wenn Zahl korrekt ist, false sonst
*     line INOUT [char **] - Stringzeiger, wird hochgesetzt wenn Zahl korrekt
*     l OUT [long *] - long-Zielvariable
*     i OUT [int *] - int-Zielvariable
*     d OUT [double *] - double-Zielvariable
*
*  BEMERKUNGEN:
*     Eine korrekte Zahl muss fuer diese Funktion mit dem Stringende oder
*     einem isspace() abgeschlossen sein. Ferner wird der Fehler in der
*     von strtol der iC86-Bibliothek umschifft. Bei fehlerhaften Zahlen
*     kommt n'Fehlertext!
*
**.EF.***********************************************************************/

bool cTomate::_GetLong( char **line , long *l )
{
   char *rest;
   bool ok;

   while (isspace(**line)) { (*line)++; };
   *l = strtol( *line , &rest , 0 );
   for(; *rest == '0'; rest++);
   if ( (ok = (*line != rest) && (*rest == '\0' || isspace(*rest))) != 0 ) {
      *line = rest;
   } else {
      Tom_printf( "Error in [long]: %s\n",TomPutWord(*line) );
   }

   return ok;
}


bool cTomate::_GetInt( char **line , int *i )
{
   char *rest;
   bool ok;

   while (isspace(**line)) { (*line)++; };
   *i = (int)strtol( *line , &rest , 0 );
   for(; *rest == '0'; rest++);
   if ( (ok = (*line != rest) && (*rest == '\0' || isspace(*rest))) != 0 ) {
      *line = rest;
   } else {
      Tom_printf( "Error in [int]: %s\n",TomPutWord(*line) );
   }

   return ok;
}


bool cTomate::_GetDouble( char **line , double *d )
{
   char *rest;
   bool ok;

   while (isspace(**line)) { (*line)++; };
   *d = strtod( *line , &rest );
   for(; *rest == '0'; rest++);
   if ( (ok = (*line != rest) && (*rest == '\0' || isspace(*rest))) != 0 ) {
      *line = rest;
   } else {
      Tom_printf( "Error in [double]: %s\n",TomPutWord(*line) );
   }

   return ok;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_PutEnum - int in symbolischen Namen umsetzen
*
*  AUFRUF:
*     result = Tom_PutEnum( value, tomtab );
*
*  PARAMETER:
*     result RESULT [char *] - String mit symbolischem Namen
*     value IN [int] - darzustellender Wert
*     tomtab IN [Tom_TYPE *] - Tom-Tabelle mit Enum-Definition
*
*  BEMERKUNGEN:
*     Falls der Wert von value in der Tom-Tabelle nicht definiert ist: Wenn
*     die Tom-Tabelle mit Tom_PROMPT(fmt) abschlieﬂt wird der Wert mit
*     printf(fmt,value) formatiert, sonst wird "(undefined)" geliefert.
*
**.EF.***********************************************************************/

char *cTomate::_PutEnum(int value, Tom_TYPE *tt)
{
   return TomPutEnum(&value,tt);
}


// ---------------------------------------------------------------------------
// lokale/private Funktionen
// ---------------------------------------------------------------------------

char *cTomate::TomCompTokens( char *str1 , char *str2 , int min )
{
   while ( *str1 && *str2 && isgraph(*str2) &&
           toupper(*str1) == toupper(*str2) ) {
      str1++; str2++; min--;
   }

   return ( min <= 0 ) ? str1 : NULL;
}


Tom_TYPE *cTomate::TomFindToken( Tom_TYPE *tab , char *str , char **rest )
{
   bool protect = false;

   while ( tab->minlen != TOM_ENDE ) {
      *rest = str;
      switch (tab->minlen) {

      case TOM_DEFAULT:
      case TOM_DEFAULT1:
         if (protect) {
            Tom_printf( "PROTECT!!! " );
            return NULL;
         }
         return tab;

      case TOM_PROTECT:
         if ( tab->func != NULL &&
              ( (*tab->func)( str , tab )) == NULL ) {
            protect = true;
         } else {
            protect = false;
         }
         break;

      default:
         if ( tab->minlen > 0 &&
              (*rest=TomCompTokens( str,tab->token,tab->minlen )) != NULL &&
              !isgraph( **rest ) ) {
            if (protect) {
               Tom_printf( "PROTECT!!! " );
               return NULL;
            }
            return tab;
         }
         break;

      }
      tab++;
   }
   /* Abfrage wegen Tausch der Werte von TOM_ENDE und Tom_DEFAULT */
#if USE_CHECK
   if (tab->func != _DummyEnd) {
      Tom_printf(" WARNING: Old style table cause problems '%s'\n",tab->token );
      return NULL;
   }
#endif

   *rest = str;
   return NULL;
}


Tom_TYPE *cTomate::TomEscape( Tom_TYPE *tab , char *str , char **rest )
{
   while ( tab->minlen != TOM_ENDE ) {
      if( tab->minlen != TOM_PROTECT ) {  /*NB* 7.10.95*/
         if ((*rest=TomCompTokens( str,tab->token,tab->minlen )) != NULL) {
            return tab;
         }
      }
      tab++;
   }

   *rest = str;
   return NULL;
}


/*
 * Aus der uebergebenen Zeile das erste Wort in einen statischen Puffer
 * kopieren (maximal TOM_TOK_MAX Zeichen). Liefert Zeiger auf den Puffer.
 */
char *cTomate::TomPutWord( char *word )
{
   static char buf[TOM_TOK_MAX];
   int i = 0;

   if (*word == '\0') {
      return "?";
   }

   while (isgraph(*word) && (i<TOM_TOK_MAX-1)) {
      buf[i++] = *word++;
   }
   buf[i] = '\0';

   return buf;
}


char *cTomate::TomPutEnum( int *var , Tom_TYPE *tomtab )
{
   static char buf[TOM_TOK_MAX];

   while ( tomtab->minlen != TOM_ENDE ) {
      if (*var == tomtab->value) {
         return TomPutWord( tomtab->token );
      }
      tomtab++;
   }

   if (tomtab->token == NULL) {
      return "(undefined)";
   } else {
      sprintf(buf,tomtab->token,*var);
      return buf;
   }
}


char *cTomate::TomPutMask( unsigned int *var , unsigned int *valid , Tom_TYPE *tomtab )
{
   unsigned int mask;

   while ( tomtab->minlen != TOM_ENDE ) {
      mask = (unsigned int)(P2LONG(tomtab->ptr1));
      if ( tomtab->minlen > 0 &&       /* COMMENT etc. ignorieren -MW- 18.11.99 */
           (mask & *var) == (mask & (unsigned int)tomtab->value) &&
           (mask & *valid) == mask ) {
         *valid &= ~mask;
         return TomPutWord( tomtab->token );
      }
      tomtab++;
   }
   return "";
}


void cTomate::TomTokList( Tom_TYPE *tomtab )
{
   bool protect = false;

   while ( tomtab->minlen != TOM_ENDE ) {
      if ( tomtab->minlen == TOM_PROTECT ) {
         protect = tomtab->func != NULL &&
                   (*tomtab->func)("",tomtab) == NULL;
      } else if (tomtab->token != NULL) {
         Tom_printf( "%s%s%s\n",protect ? "(( " : "   ",
            tomtab->token,
            protect ? " ))" : "" );
      }
      tomtab++;
   }
}


char *cTomate::TomGetEnum( char *line , int *var , Tom_TYPE *tomtab )
{
   char *rest;
   Tom_TYPE *tt;

   if (*line == '?') {
      Tom_printf( "Possible constants are ...\n" );
      TomTokList( tomtab );
      rest = ++line;
   } else if ( (tt=TomFindToken( tomtab , line , &rest )) != NULL ) {
      *(int*)var = tt->value;
   } else if (*line == '\0') {
      Tom_printf( "Missing constant\n" );
      rest = NULL;
   } else {
      Tom_printf( "Unknown constant '%s'\n",TomPutWord(line) );
      rest = NULL;
   }

   return rest;
}


char *cTomate::TomGetMask( char *line , unsigned int *value , unsigned int *mask , Tom_TYPE *tomtab )
{
   char *rest,*rest2;
   Tom_TYPE *tt;

   *value = *mask = 0;
   if (*line == '?') {
      Tom_printf( "Possible masks are ...\n" );
      TomTokList( tomtab );
      rest = ++line;
   } else if ( (tt=TomFindToken( tomtab , line , &rest )) != NULL ) {
      *mask  = (unsigned int)(P2LONG(tt->ptr1));
      *value = (tt->value & *mask);
      // 13.01.2000 -MW- es koennen mehrere Masken angegeben werden
      line = rest; while ( isspace(*line) ) line++;
      while ( (tt=TomFindToken( tomtab , line , &rest2 )) != NULL ) {
         *mask  |= (unsigned int)(P2LONG(tt->ptr1));
         *value |= (tt->value & *mask);
         line = rest = rest2; while ( isspace(*line) ) line++;
      }
   } else if (*line == '\0') {
      Tom_printf( "Missing mask\n" );
      rest = NULL;
   } else {
      Tom_printf( "Unknown mask '%s'\n",TomPutWord(line) );
      rest = NULL;
   }

   return rest;
}


/*
 * Pfadstring fuer Ausgabe zusammenbasteln...
 */
char *cTomate::TomPutPath( Tom_ENV *env, char *buf, int curlen , int maxlen )
{
   size_t prolen;

   if (env->start) {
      *buf = '\0';
   } else {
      prolen = (int) strcspn( env->prompt , "[" );
      if (prolen+curlen+5 < (size_t)maxlen) {
         TomPutPath( env->envold, buf, curlen+(int)prolen+1, maxlen);
         strncat( buf, env->prompt, prolen );
         strcat( buf, curlen?"/":">" );
      } else {
         strcpy( buf, ".../" );
      }
      /*Tom_printf( "buf = '%s', len = %d/%d\n",buf,curlen,maxlen );*/
   }

   return buf;
}


/* --- exportierte Funktionen der Macros --- */



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_With - Verwurstelung zweier Tokenstufen
*
*  AUFRUF:
*     rest = Tom_With( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit:
*       (int)tt->value, (void*)tt->ptr1 - Tabellenparametern dieser Stufe
*       (Tom_TYPE*)tt->ptr2 - Nachgeordnete Tabelle mit Aktionsfunktion
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_With( char *line , Tom_TYPE *tt )
{
   Tom_TYPE param_tt;
   Tom_TYPE *func_tt;
   char *rest;

   param_tt.value  = tt->value;
   param_tt.ptr1   = tt->ptr1;
   param_tt.ptr2   = NULL;
   param_tt.minlen = tt->minlen;
   param_tt.token  = tt->token;

   while (isspace(*line)) { line++; };
   if (*line == '?') {
      Tom_printf( "Possible extensions are ...\n" );
      TomTokList( (Tom_TYPE*)tt->ptr2 );
      line++;
   } else if ((func_tt = TomFindToken( (Tom_TYPE*)tt->ptr2 , line , &rest )) != NULL) {
      param_tt.func = func_tt->func;
      return (*param_tt.func)( rest , &param_tt );
   } else if (*line == '\0') {
      Tom_printf( "Missing extension\n" );
   } else {
      Tom_printf( "Unknown extension '%s'\n",TomPutWord(line) );
      line = NULL;
   }

   return line;


}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Param - Parameterstufe (ohne Eingabe)
*
*  AUFRUF:
*     rest = Tom_Param( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweisen:
*        (Tom_TYPE*)tt->ptr1 - naechste Tabellenstufe
*        (char *(*)(char*,Tom_TYPE*))tt->ptr2 - Gate-Funktion oder NULL
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Param( char *line , Tom_TYPE *tt )
{
   Tom_TYPE param_tt;
   char *rest;

   memcpy( &param_tt , tt , sizeof(Tom_TYPE) );

   if ( param_tt.ptr2 ) {
      param_tt.value = TOM_IDPARAM;
      line = (* (char *(*) (char*,Tom_TYPE*) ) P2FPTR(param_tt.ptr2))( line , &param_tt );
      if (line == NULL) {
         Tom_printf( "Access denied\n" );
         return NULL;
      }
   }

   while (isspace(*line)) { line++; };
   if (*line == '?') {
      Tom_printf( "Possible parameters are ...\n" );
      TomTokList( (Tom_TYPE*)param_tt.ptr1 );
      line++;
   } else if ((tt=TomFindToken( (Tom_TYPE*)param_tt.ptr1 , line , &rest )) != NULL) {
      return (*tt->func)( rest , tt );
   } else if (*line == '\0') {
      Tom_printf( "Missing parameter\n" );
   } else {
      Tom_printf( "Unknown parameter '%s'\n",TomPutWord(line) );
      line = NULL;
   }

   return line;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Level - Eingabestufe
*
*  AUFRUF:
*     rest = Tom_Level( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweis:
*        (Tom_TYPE*)tt->ptr1 - naechste Tabellenstufe
*        (char *(*)(char*,Tom_TYPE*))tt->ptr2 - Gate-Funktion oder NULL
*
*  BEMERKUNGEN:
*     Weitere Verweise im letzten Eintrag der naechsten Tabellenstufe:
*        (char *(*)(char*,Tom_TYPE*))tt->ptr1 - init-Funktion oder NULL
*        (char *(*)(char*,Tom_TYPE*))tt->ptr2 - exit-Funktion oder NULL
*        tt->token - Prompt-String, ggf. mit %d fuer Eingabestufe
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Level( char *line , Tom_TYPE *tt )
{
   Tom_TYPE end_tt;
   char *rest = line;
   bool quit = false;
   Tom_ENV envnew;
   int fromlevel;
   char path[TOM_PRM_MAX];

   /* das erste Gate (kann die Tabelle noch aendern) */
   memcpy( &end_tt , tt , sizeof(Tom_TYPE) );
   if ( end_tt.ptr2 ) {
      end_tt.value = TOM_IDLEVEL;
      line = (* (char *(*) (char*,Tom_TYPE*) ) P2FPTR(end_tt.ptr2))
         ( line ? line : "" , &end_tt );
      if (line == NULL) {
         line = "";
      }
   }

   /* Tom_Level-Umgebung festhalten, Teil 1 */
   memcpy( &envnew, Tom_Env , sizeof(Tom_ENV) );
   envnew.level++;
   envnew.start = false;
   envnew.curtt = (Tom_TYPE*)end_tt.ptr1;

   tt = envnew.curtt;
   while( tt->minlen != TOM_ENDE ) { tt++; }
   memcpy( &end_tt, tt, sizeof(Tom_TYPE) );
#if USE_CHECK
   /* Abfrage wegen Tausch der Werte von TOM_ENDE und Tom_DEFAULT */
   if (tt->func != (Tom_FUNC)cTomate::_DummyEnd) {
      Tom_printf("WARNING: Old style table cause problems '%s'\n",tt->token );
      end_tt.token = "WARNING: COMMANDS LOST";
   }
#endif

   if ( end_tt.ptr1 ) {
      end_tt.value = TOM_IDINIT;
      line = (* (char *(*) (char*,Tom_TYPE*) ) P2FPTR(end_tt.ptr1))
         ( line ? line : "" , &end_tt );
      if (line == NULL) {
         Tom_printf( "Access denied\n" );
         return NULL;
      }
   }

   /* Tom_Level-Umgebung festhalten, Teil 2 */
   envnew.prompt = end_tt.token ? end_tt.token : "?[%d]";
   envnew.envold = Tom_Env;
   Tom_Env = &envnew;

   /* Pfad-Prompt zusammenbasteln */
   TomPutPath( Tom_Env, path, 0, TOM_PRM_MAX );

   #if defined __ECL_VCPP__
      #pragma warning(disable:4611) /* setjmp nicht portabel */
   #endif

   if ( (fromlevel=setjmp(envnew.jmpbuf)) != 0 ) {
      /* Ruecksprung von irgendwo */
      if (fromlevel != -1) {
         Tom_printf( "Back to %d from %d\n",Tom_Env->level,fromlevel );
      } else {
         Tom_printf( "*Break*\n" );
      }
      line = NULL;
   }

   #if defined __ECL_VCPP__
      #pragma warning(default:4611) /* setjmp nicht portabel */
   #endif

   do {
      if ((line == NULL) || (*line == '\0')) {
         TomBuf[0] = TOM_BUF_MAX-3;
         line = Tom_GetS( TomPrompt ? path : Tom_Env->prompt , TomBuf );
      }

      while (isspace(*line)) { line++; };
      if (*line == '?') {
         Tom_printf( "Possible commands are ...\n" );
         TomTokList( Tom_Env->curtt );
         line++;
      } else if (*line == '.') {
         quit = true;
         line++;
      } else if (*line == '/') {
         if (Tom_Env->envold->start) {
            line++;
         } else {
            quit = true;
         }
      } else if ((tt=TomFindToken( Tom_Env->curtt , line , &rest )) != NULL) {
         line = (*tt->func)( rest , tt );
      } else if ( (tt=TomEscape( (Tom_TYPE*)TomInternal,line,&rest )) != NULL ||
               Tom_Env->shortcut != NULL &&
               (tt=TomEscape( Tom_Env->shortcut , line , &rest )) != NULL ) {
         line = (*tt->func)( rest , tt );
      } else if (*line != '\0') {
         Tom_printf( "Unknown command '%s'\n",TomPutWord(line) );
         line = NULL;
      }

      if (quit && end_tt.ptr2) {
         end_tt.value = TOM_IDEXIT;
         line = (* (char *(*) (char*,Tom_TYPE*) ) P2FPTR(end_tt.ptr2))
            ( line , &end_tt );
         if (line == NULL) {
            Tom_printf( "Exit denied\n" );
            quit = false;
         }
      }
   } while (!quit);

   Tom_Env = Tom_Env->envold;
   return line;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Dummy - Suess und lieblich ist die Untaetigkeit ...
*     Tom_DummyEnd - Suess und lieblich ist die Untaetigkeit ...
*
*  AUFRUF:
*     rest = Tom_Dummy( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - s'kommt immer line zurueck
*     line IN [char *] - Rest der Eingabezeile
*     tt IN [Tom_TYPE *] - zugeordneter Tom-Tabellen-Eintrag
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Dummy( char *line , Tom_TYPE * /*tt*/ )
{
   return line;
}

char *cTomate::_DummyEnd( char *line , Tom_TYPE * /*tt*/ )
{
   return line;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Alias - Befehlssequenz abarbeiten
*
*  AUFRUF:
*     rest = Tom_Alias( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweis:
*        (char *)tt->ptr1 - Befehlszeile fuer Token
*
*  BEMERKUNGEN:
*     Alias-Befehle koennen nicht geschachtelt werden. Der Versuch wird mit
*     dem Abbruch der ersten Alias-Sequenz bestraft.
*
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Alias( char *line , Tom_TYPE *tt )
{
   Tom_LnPush( line , NULL );
   return (char*)tt->ptr1;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Script - Befehlssequenz abarbeiten
*
*  AUFRUF:
*     rest = Tom_Script( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweis:
*        (char**)tt->ptr1 - Script-Adresse
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Script( char *line , Tom_TYPE *tt )
{
   Tom_TYPE script;
   bool oldquiet = TomQuiet;

   script.ptr1 = tt->ptr2;
   script.ptr2 = NULL;
   Tom_LnPush( line , (char**)tt->ptr1 );
   line = _Level( Tom_LnPop() , &script );

   TomQuiet = oldquiet;

   return line;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_View - Variablen ausgeben
*
*  AUFRUF:
*     rest = Tom_View( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweisen:
*        tt->value - Konstante mit dem Variablentyp
*        (???*)tt->ptr1 - Zeiger auf Variable
*        (Tom_TYPE*)tt->ptr2 - Zeiger auf Enum-Definition bei ENUM-Typen
*
*  BEMERKUNGEN:
*     Es wird immer der Tokenname und der Typ mit ausgegeben:
*        "<token> [<typ>] = <value>"
*     Ausgenommen hiervon ist der TEXT-Typ, der ohne jegliches schmueckendes
*     Beiwerk ausgegeben wird und sich dadurch fuer die Ausgabe von Hilfs-
*     texten und Erklaerungen besonders qualifiziert.
*
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_View( char *line , Tom_TYPE *tt )
{
   unsigned int oldvalid,valid,value;

   if (tt->value == _TEXT) {
      Tom_printf( "%s",(char*)tt->ptr1 );
      return line;
   }

   Tom_printf( "%s [%s] = ",TomPutWord( tt->token ),TomTypes[tt->value] );

   switch (tt->value) {
   case _uchar:
      Tom_printf( "%u (%02x)\n",*(unsigned char*)tt->ptr1,*(unsigned char*)tt->ptr1 ); break;
   case _ushort:
      Tom_printf( "%u (%04x)\n",*(unsigned short*)tt->ptr1,*(unsigned short*)tt->ptr1 ); break;
   case _uint:
      Tom_printf( INTSIZE==2 ? "%u (%04x)\n" : "%u (%08x)\n",
                  *(unsigned int*)tt->ptr1,*(unsigned int*)tt->ptr1 ); break;
   case _ulong:
      Tom_printf( "%lu (%08lx)\n",*(unsigned long*)tt->ptr1,*(unsigned long*)tt->ptr1 ); break;
   case _char:
      Tom_printf( "%d\n",*(char*)tt->ptr1 ); break;
   case _short:
      Tom_printf( "%d\n",*(short*)tt->ptr1 ); break;
   case _int:
      Tom_printf( "%d\n",*(int*)tt->ptr1 ); break;
   case _long:
      Tom_printf( "%ld\n",*(long*)tt->ptr1 ); break;
   case _bool:
      Tom_printf( "%s (%d)\n",
                  *(bool*)tt->ptr1 ? "true" : "false",
                  *(bool*)tt->ptr1 ); break;
   case _float:
      Tom_printf( "%.4g\n",*(float*)tt->ptr1 ); break;
   case _double:
      Tom_printf( "%.4g\n",*(double*)tt->ptr1 ); break;
   case _ldouble:
      Tom_printf( "%.4g\n",*(long double*)tt->ptr1 ); break;
   case _ptr:
      Tom_printf( "%p\n",*(void**)tt->ptr1 ); break;
   case _STR:
      Tom_printf( "%s\n",(char*)tt->ptr1 ); break;

   case _ENUM:
      Tom_printf( "%s (%d)\n",
                  TomPutEnum( (int*)((Tom_NAMES*)tt->ptr1)->var ,
                              ((Tom_NAMES*)tt->ptr1)->sym ),
                  *(int*)((Tom_NAMES*)tt->ptr1)->var ); break;
   case _MASK:
      value = *(unsigned int*)((Tom_NAMES*)tt->ptr1)->var;
      valid = ~(unsigned int)0;
      Tom_printf( INTSIZE==2 ? "(%04x)" : "(%08x)",value );
      do {
         oldvalid = valid;
         Tom_printf( " %s",TomPutMask( &value , &valid ,
                                       ((Tom_NAMES*)tt->ptr1)->sym ) );
      } while (oldvalid != valid);
      Tom_printf( "\n" );
      break;
   case _DEG:
      Tom_printf( "%.4g\n",*(double*)tt->ptr1 * 180.0 / 3.1415926536 ); break;
   case _ENUM_O:
      Tom_printf( "%s (%d)\n",
                  TomPutEnum( (int*)tt->ptr1 , (Tom_TYPE*)tt->ptr2 ),
                  *(int*)tt->ptr1 ); break;
   case _MASK_O: // ## ungetestete Erweiterung !!!
      value = *(unsigned int*)tt->ptr1;
      valid = ~(unsigned int)0;
      Tom_printf( INTSIZE==2 ? "(%04x)" : "(%08x)",value );
      do {
         oldvalid = valid;
         Tom_printf( " %s",TomPutMask( &value , &valid ,
                                       (Tom_TYPE*)tt->ptr2 ) );
      } while (oldvalid != valid);
      Tom_printf( "\n" );
      break;
   default:
      Tom_printf( "Tom_View: unknown type %d\n",tt->value ); break;
   }

   return line;
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Set - Variablen mit Wert aus Eingabezeile setzen
*
*  AUFRUF:
*     rest = Tom_Set( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweisen:
*        tt->value - Konstante mit Variablentyp
*        (???*)tt->ptr1 - Zeiger auf Variable bzw. Variablenbeschreibung
*
*   BEMERKUNGEN:
*      Die Typen char, int, long, BYTE, WORD, LONG und PTR werden mit
*      strtol bzw. strtoul eingelesen. EMUM und BOOL beziehen die gueltigen
*      Eingaben aus einer benutzerdefinierten bzw. vorgegebenenTom-Tabelle.
*      Bei STR wird der gesamte Zeilenrest an die Variablenadresse kopiert,
*      eine Laengenpruefung findet nicht statt (Vorsicht!). Der Typ TEXT
*      kann nicht veraendert werden (PTR-Typ dafuer verwenden).
*
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Set( char *line , Tom_TYPE *tt )
{
   long num;
   unsigned int mask,value;
   double dblnum;
   char *rest = line;

   while (isspace(*line)) { line++; };
   if (*line == '?' && TomHelp[tt->value]) {
      Tom_printf( "Type is [%s]\n",TomTypes[tt->value] );
      line++;
   } else {
      switch (tt->value) {
      case _ptr:
      case _uchar:
      case _ushort:
      case _uint:
      case _ulong:
         num = strtoul( line, &rest, 0 );
         for(; *rest == '0'; rest++);
         if (line == rest || (*rest && !isspace(*rest)) ) {
            Tom_printf( "Error in [%s]: %s\n",
                        TomTypes[tt->value],TomPutWord(line) );
            rest = NULL;
         } else if (tt->value == _uchar) {
            *(unsigned char*)tt->ptr1 = (unsigned char)num;
      #if PTRSIZE == 2
         } else if (tt->value == _ushort || tt->value == _ptr ) {
      #else
         } else if (tt->value == _ushort) {
      #endif
            *(unsigned short*)tt->ptr1 = (unsigned short)num;
         } else if (tt->value == _uint) {
            *(unsigned int*)tt->ptr1 = (unsigned int)num;
      #if PTRSIZE == 4
         } else if (tt->value == _ulong || tt->value == _ptr ) {
      #else
         } else if (tt->value == _ulong) {
      #endif
            *(unsigned long*)tt->ptr1 = (unsigned long)num;
         };
         line = rest; break;
      case _char:
      case _short:
      case _int:
      case _long:
         num = strtol( line , &rest , 0 );
         for(; *rest == '0'; rest++);
         if (line == rest || (*rest && !isspace(*rest)) ) {
            Tom_printf( "Error in [%s]: %s\n",
                        TomTypes[tt->value],TomPutWord(line) );
            rest = NULL;
         } else if (tt->value == _char) {
            *(char*)tt->ptr1 = (char)num;
         } else if (tt->value == _short) {
            *(short*)tt->ptr1 = (short)num;
         } else if (tt->value == _int) {
            *(int*)tt->ptr1 = (int)num;
         } else if (tt->value == _long) {
            *(long*)tt->ptr1 = (long)num;
         };
         line = rest; break;
      case _STR:
         strcpy( (char*)tt->ptr1 , line ); line = NULL; break;
      case _ENUM_O:
         line = TomGetEnum( line , (int*)tt->ptr1 , (Tom_TYPE*)tt->ptr2 ); break;
      case _ENUM:
         line = TomGetEnum( line , (int*)((Tom_NAMES*)tt->ptr1)->var ,
                                   ((Tom_NAMES*)tt->ptr1)->sym ); break;
      case _MASK_O:  // ## ungetestete Erweiterung !!!
         line = TomGetMask( line , &value , &mask , (Tom_TYPE*)tt->ptr2 );
         *(unsigned int*)tt->ptr1 = (value & mask) |
            (*(unsigned int*)tt->ptr1 & ~mask);
         break;
      case _MASK:
         line = TomGetMask( line , &value , &mask , ((Tom_NAMES*)tt->ptr1)->sym );
         *(unsigned int*)((Tom_NAMES*)tt->ptr1)->var = (value & mask) |
            (*(unsigned int*)((Tom_NAMES*)tt->ptr1)->var & ~mask);
         break;
      case _bool:
         line = TomGetEnum( line , (int*)tt->ptr1 , (Tom_TYPE*)TomBools ); break;
      case _ldouble:
      case _double:
      case _float:
      case _DEG:
         dblnum = strtod( line , &rest );
         if (tt->value == _DEG) dblnum *= 3.1415926536 / 180.0;
         for(; *rest == '0'; rest++);
         if (line == rest || (*rest && !isspace(*rest)) ) {
            Tom_printf( "Error in [%s]: %s\n",
                        TomTypes[tt->value],TomPutWord(line) );
            rest = NULL;
         } else if (tt->value == _float) {
            *(float*)tt->ptr1 = (float)dblnum;
         } else if (tt->value == _ldouble) {
            *(long double*)tt->ptr1 = (long double) dblnum;
         } else {
            *(double*)tt->ptr1 = (double)dblnum;
         };
         line = rest; break;
      default:
         Tom_printf( "Tom_Set: unknown type %d\n",tt->value ); break;
      }
   }

   return line;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Reset - Masken-Variablen mit Wert aus Eingabezeile ruecksetzen
*
*  AUFRUF:
*     rest = Tom_Reset( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweisen:
*        tt->value - Konstante mit Variablentyp
*        (???*)tt->ptr1 - Zeiger auf Variable bzw. Variablenbeschreibung
*
*  BEMERKUNGEN:
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Reset( char *line , Tom_TYPE *tt )
{
   unsigned int mask,value;

   while (isspace(*line)) { line++; };
   if (*line == '?' && TomHelp[tt->value]) {
      Tom_printf( "Type is [%s]\n",TomTypes[tt->value] );
      line++;
   } else {
      switch (tt->value) {
      case _MASK:
         line = TomGetMask( line , &value , &mask ,
             ((Tom_NAMES*)tt->ptr1)->sym );
         *(unsigned int*)((Tom_NAMES*)tt->ptr1)->var &= ~(value & mask);
         break;
      case _MASK_O:   // ## ungetestete Erweiterung !!!
         line = TomGetMask( line , &value , &mask ,
             (Tom_TYPE*)tt->ptr2 );
         *(unsigned int*)tt->ptr1 &= ~(value & mask);
         break;
      default:
         Tom_printf( "Tom_Reset: unknown type %d\n",tt->value ); break;
      }
   }

   return line;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     Tom_Const - Variable mit Konstante belegen
*
*  AUFRUF:
*     rest = Tom_Const( line, tt );
*
*  PARAMETER:
*     rest RESULT [char *] - Zeilenrest
*     line IN [char *] - Eingabezeile
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit Verweis und Wert:
*        tt->value - Konstante mit Variablentyp
*        (???*)tt->ptr1 - Zeiger auf Variable
*        (???)tt->ptr2 - Konstante (mit Cast als void*)
*
*  BEMERKUNGEN:
*     Fuer STR und TEXT sind keine Konstanten moeglich.
*
*     Funktion und Parameter *NICHT* Teil der Schnittstelle, Benutzung *NUR*
*     ueber Tomate-Macros erlaubt !!!
*
**.EF.***********************************************************************/

char *cTomate::_Const( char *line , Tom_TYPE *tt )
{
   long value = P2LONG(tt->ptr2);

   switch (tt->value) {
   case _uchar:
   case _char:
      *(char*)tt->ptr1 = (char)value; break;
   case _ushort:
   case _short:
      *(short*)tt->ptr1 = (short)value; break;
   case _ulong:
   case _long:
      *(long*)tt->ptr1 = (long)value; break;
   case _int:
   case _uint:
   case _ENUM:
   case _MASK:
   case _ENUM_O:
   case _MASK_O:
      *(int*)tt->ptr1 = (int)value; break;
   case _bool:
      *(bool*)tt->ptr1 = value ? true : false; break;
   case _ptr:
      *(void**)tt->ptr1 = tt->ptr2; break;
   case _double:
      *(double*)tt->ptr1 = (double)value; break;
   case _ldouble:
      *(long double*)tt->ptr1 = (long double)value; break;
   case _float:
      *(float*)tt->ptr1 = (float)value; break;
   case _DEG:
      *(double*)tt->ptr1 = (double)value * 3.1415926536 / 180.0; break;
   default:
      Tom_printf( "Tom_Const: illegal type %d\n",tt->value ); break;
   }

   return line;
}


/*.SC.************************************************************************
*
*  Tomate-Steuerung:
*
*  Tomate-Steuerbefehle gehoeren zu den immer-und-ueberall-Befehlen und
*  werden mit '%' eingeleitet, gefolgt von einer der exzellenten Tomate-
*  Funktionen. Tomato-al-gusto, sozusagen, und zwar al dente:
*
*     %Help - Versionsnummer, allgemeine Hilfe und Einstellungen ausgeben.
*
*     %Echo <text> - Text (bis zum Zeilenende) ausgeben
*
*     %More 0 - Seitenweise Ausgabe bei Tom_printf ausschalten
*     %More n - alle n Zeilen die Ausgabe anhalten, Tasten sind:
*                  SPACE - naechste Seite anzeigen
*                  CR - naechste Zeile anzeigen
*                  jede andere Taste bricht die Ausgabe ab!
*
*     %Goto <level> - direkter Ruecksprung in hoehere Eingabestufen
*
*     %Path - Weg zur aktuellen Eingabestufe anzeigen
*     %Path ON - Prompt mit Pfad ausgeben
*     %Path OFF - Prompt ohne Pfad ausgeben, ggf. mit Level-Zaehler
*
*     %Quiet ON - Ausgabe bei Tom_printf einschalten
*     %Quiet OFF - Ausgabe bei Tom_printf ausschalten
*
*     %> <file> - Ausgabeumleitung in Datei einschalten
*     %> - Ausgabeumleitung ausschalten, Datei schliessen
*     %> ON | OFF | ONLY - Aktivierung der Ausgabeumleitung
*
**.EC.***********************************************************************/

/*
 * Versionstext der HELP einleitet:
 */
const char cTomate::_tomversion[] = "\
*** VERSION IN UEBERARBEITUNG ***\n\
Copyright (c) 1992-2000 by M.Wuertz\n\
Unfreigegebene Version 1.999 (18.04.2000)\n\n";

/*
 * Text der bei HELP ausgegeben wird:
 */
const char cTomate::_tomhelp[] = "\
Common comands:\n\
   ? - show possible parameters/commands\n\
   . - one level back\n\
   / - go to first level\n\
Page mode control keys:\n\
   SPACE - show next page\n\
   CR - show next line\n\
   any other key - abort!\n";

/*
const char cTomate::_tomhelp[] = "\
Allgemeine Steuerfunktionen sind:\n\
'?' - erlaubte Eingaben an dieser Stelle anzeigen\n\
'%' - Einleitungszeichen fuer Tom-Befehle\n\
'.' - zurueck zur naechsthoeheren Eingabestufe\n\
'/' - zurueck zur allerhoechsten Eingabestufe\n\n\
Steuertasten bei der seitenweisen Ausgabe sind:\n\
SPACE - naechste Seite ausgeben\n\
CR - naechste Zeile ausgeben\n\
(andere Tasten brechen die Ausgabe ab)\n\n\
\n";
*/


/*
 * Tom-Steuerung je nach gewaehlter Steuerfunktion, mit diversen
 * Referenzen auf lokale Variable und Funktionen des Tomate-Moduls
 */
char *cTomate::_tomcontrol( char *line , Tom_TYPE *tt )
{
   bool oldquiet;
   Tom_ENV *env;
   int val;
   char buffer[256];

   while (isspace(*line)) { line++; }

   switch (tt->value) {
   case TOM_ECHO:
      if (*line == '"') {
         char buf[TOM_BUF_MAX];
         Tom_GetStr(&line, buf, sizeof(buf));
         Tom_printf("%s", buf);
      } else {
         Tom_printf( "%s\n",line ); line = NULL;
      }
      break;
   case TOM_WAIT: //## Haeh?
//    if (!Tom_GetInt( &line , &val )) {
//       line = NULL;
//    }
      break;
   case TOM_CHWD:
//    if ( chwdir(line) != 0 ) {
//       Tom_printf( "Could not changed to '%s'\n",line );
//    }
      line = NULL;
      break;
   case TOM_RUNS:
      if ( TomIFile != NULL ) {
         if ( TomIStackPtr >= TOM_ISTACK_MAX ) {
            Tom_printf( "Warning: Script files nested too deeply\n" );
            fclose(TomIFile);
         } else {
            TomIStack[TomIStackPtr++] = TomIFile;
         }
      }
      sprintf( buffer, "%s.tsc", line );
      if ( (TomIFile=fopen(buffer, "r")) == NULL ) {
         Tom_printf( "Could not open script file '%s'\n", buffer );
      }
      line = NULL;
      break;
   case TOM_OUTF:
      if (*line == '\0') {
         /* Abfrage auf NULL *NB*/
         if( TomOFile != NULL ) {
            fclose( TomOFile );
            TomOMode = TOM_OCON;
            TomOFile = NULL;
         } else {
            Tom_printf( "No redirection active!\n" );
         }
      } else if (Tom_GetArg(&line,buffer,sizeof(buffer))) {
         if ((TomOFile=fopen(buffer,"w")) == NULL) {
            Tom_printf( "File %s: errno %d\n",buffer,errno);
            TomOMode = TOM_OCON;
            line = NULL;
         } else {
            TomOMode = TOM_OCON + TOM_OFILE;
         }
      }
      break;
   case TOM_VIEW:
      Tom_printf("%s",_tomversion);
	
	  oldquiet = TomQuiet;
      TomQuiet = false;
	  Tom_printf("Current settings:\n   ");
      if (TomTID != -1) Tom_printf("TID [%d]  ",TomTID);
      Tom_printf( "Outfile [%s]  Quiet [%s]  Level [%d]  ",
                  TomOMode&TOM_OFILE ? "ON" : "OFF",
                  oldquiet ? "ON" : "OFF" ,
                  Tom_Env->level );
      Tom_printf( TomMore ?
                  "More [%d lines]\n" :
                  "More [OFF]\n" , TomMore );
      TomQuiet = oldquiet;

	  Tom_printf( "Escape sequences:\n" );
      TomTokList( (Tom_TYPE*)TomInternal );
      if (Tom_Env->shortcut != NULL) {
         TomTokList( Tom_Env->shortcut );
      }

	  Tom_printf("%s",_tomhelp);
      break;
   case TOM_PATH:
      env = Tom_Env;
      while (env) {
         if (env->start) {
            Tom_printf( "-------- Tom_Start --------" );
         } else {
            Tom_printf( "[%d] = ",env->level );
            Tom_printf( env->prompt,env->level );
         }
         Tom_printf( "\n" );
         env = env->envold;
      }
      break;
   case TOM_GOTO:
      if (!Tom_GetInt( &line , &val )) {
         line = NULL;
      } else {
         Tom_Jump( val?val:Tom_BREAK );
         /* wird nie erreicht */
      }
      break;
   case TOM_VSET:
      if (Tom_GetStr(&line,buffer,sizeof(buffer))) {
         putenv(buffer);
      }
      break;
   case TOM_VGET:
      if (Tom_GetStr(&line,buffer,sizeof(buffer))) {
         char *env = getenv(buffer);
         if (env) {
            Tom_printf("%s=%s\n",buffer,env);
         } else {
            Tom_printf("%s not defined\n",buffer);
         }
      }
      break;
   case TOM_VINS:
      if (Tom_GetStr(&line,buffer,sizeof(buffer))) {
         char *env = getenv(buffer);
         if (env) {
            Tom_LnPush( line , NULL );
            line = env;
         }
      }
      break;
   case TOM_VCMD:
      if (Tom_GetInt(&line,&val)) {
         if (TomArgV && val >= 0 && val < TomArgC) {
            Tom_LnPush( line , NULL );
            line = TomArgV[val];
         }
      }
      break;

   default:
      Tom_printf( "TomControl: undefined function\n" ); break;
   }

   return line;
}

/*
 * Tom-Tabelle mit den Moeglichkeiten des PATH-Befehls:
 */
const Tom_TYPE cTomate::_tompath[] = {
   Tom_CONST( _bool , &TomPrompt , false , 3,"OFF - Disable path prompt" )
   Tom_CONST( _bool , &TomPrompt , true ,  2,"ON  - Enable path prompt" )
   Tom_UW( _tomcontrol , TOM_PATH ,        -1,"(Default: Detailed path" )
   Tom_ENDE()
};


/*
 * Tom-Tabelle mit den Moeglichkeiten des QUIET-Befehls:
 */
const Tom_TYPE cTomate::_tomquiet[] = {
   Tom_CONST( _bool , &TomQuiet , false ,  3,"OFF - Disable output" )
   Tom_CONST( _bool , &TomQuiet , true ,   2,"ON  - Enable output" )
   Tom_ENDE()
};

/*
 * Tom-Tabelle mit den Moeglichkeiten der Ausgabeumleitung:
 */
const Tom_TYPE cTomate::_tomofile[] = {
   Tom_CONST( _uint, &TomOMode, TOM_OCON,           3,"OFF    - Disable redirection" )
   Tom_CONST( _uint, &TomOMode, TOM_OCON+TOM_OFILE, 2,"ON     - Enable redirection" )
   Tom_CONST( _uint, &TomOMode, TOM_OFILE,          4,"ONLY   - Redirected output only" )
   Tom_UW( _tomcontrol, TOM_OUTF,                   -1,"<file> - Open file and enable" )
   Tom_COMMENT(                                       "(Default: Closed and disabled)" )
   Tom_ENDE()
};

/*
 * Tom-Tabelle mit den eigentlichen immer-und-ueberall Tom-Befehlen:
 */
const Tom_TYPE cTomate::_tomfunc[] = {
   //Tom_VIEW( _TEXT, _tomhelp ,      1,"Help         - Show General help" )
   //Tom_VIEW( _TEXT, _tomversion ,   1,"Version      - Show Latest news" )
   Tom_UW( _tomcontrol , TOM_VIEW , 1,"Help         - Help, I need somebodys help ..." )
   Tom_COMMENT(                       "More 0       - Disable paged output" )
   Tom_SET( _uint , &TomMore ,      1,"More <lines> - Enable paged output" )
   Tom_PARAM( _tomofile,            1,"> ...        - Redirect output" )
   Tom_UW( _tomcontrol , TOM_ECHO , 1,"Echo <text>  - Display text" )
   Tom_PARAM( _tomquiet,            1,"Quiet ...    - Output control" )
   Tom_PARAM( _tompath,             1,"Path ...     - Path settings" )
   Tom_UW( _tomcontrol , TOM_WAIT , 1,"Wait <ticks> - Delay tomate" )
   Tom_UW( _tomcontrol , TOM_CHWD , 3,"CHDir <dir>  - Change working directory" )
   Tom_UW( _tomcontrol , TOM_GOTO , 2,"GOto <level> - Return to level" )
   Tom_UW( _tomcontrol , TOM_VSET , 1,"Set <var>=<value> - Set value")
   Tom_UW( _tomcontrol , TOM_VGET , 1,"View <var>   - View value")
   Tom_UW( _tomcontrol , TOM_VINS , 1,"Insert <var> - Insert value")
   Tom_UW( _tomcontrol , TOM_VCMD , 1,"Cmdln <nr>   - Insert commandline parameter")
   //Tom_UW( _tomcontrol , TOM_VIEW , 1,"Info         - View Tomate settings" )
   Tom_ENDE()
};

/*
 * Wurzel der immer-und-ueberall erreichbaren Tom-Befehle:
 */
const Tom_TYPE cTomate::TomInternal[] = {
   Tom_PARAM( _tomfunc , 1,"% ... - Tomate control functions" )
   Tom_UW( _tomcontrol , TOM_RUNS , 1,"@ ... - Run tomate script (*.tsc)" )
   Tom_ENDE()
};




