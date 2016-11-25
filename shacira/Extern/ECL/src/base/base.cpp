// ===========================================================================
// base/base.cpp                                                ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================

/*****************************************************************************
Ueberarbeitung der ECL-Debug-Maske

Anforderungen
- "kompatibel" zu den bisherigen Masken
- Es wird Modul und Fehlerklasse unterschieden
- Nach Modul/Fehlerklasse gefiltert erfolgen unterschiedliche Reaktionen

Realisierung

[snip] 
... bereits doxygenisiert ...
[snip]

Fehlerklasse und Modulgruppe werden als eine einzige (kombinierte) Bitmaske
bei den Aufrufmacros angegeben. Sowohl Fehlerklasse als auch Modulgruppe kann
auch weggelassen werden. Wenn beide fehlen (mask==0) kann nur mit dem 
Einzelmodulnamen gearbeitet werden, der in den Macros automatisch
durch die entsprechenden Preprozessor-Konstante __FILE__ belegt wird.
  
Die Reaktionen koennen global oder mit einem Detailfilter festgelegt werden.
- Global: ein (debug_mask & mask) bestimmt "grob", ob die Ausgabe erfolgt,
  es ist zentral festgelegt, welche der Reaktionen erfolgen.
- Detailfilter: Es gibt eine verkettete Liste, die nach der "Grobentscheidung"
  noch eine feinere Ueberpruefung von Fehlerklasse/Modulgruppe (Bitmaske) und
  ggf. Einzelmodul (String) vornimmt. Fuer jeden Einzelfall sind unterschiedliche
  Reaktionen moeglich (z.B. nur Protokollierung, oder auch echtes 'Assert').
      struct MATCH_PATTERN {
         unsigned long and;   // 'mask & and' wird berechnet, 
         unsigned long match; // Ergebnis muss 'match' sein.
         const char *modul;   // falls modul != 0 muss file mit modul enden
         // [...] -> irgendwas, das die Reaktionen festlegt
         MATCH_PATTERN *next; // naechstes Listenelement
      };

WEITERE ERGAENZUNGEN
- ERLEDIGT - Statistik-Modul: Zaehlen kann per Bit zentral deaktiviert werden 
  OFFEN - bei
  der Deinitialisierung von cBase erfolgt wahlweise automatisch ein show() /
  als 'Ausgabe' des Statistik-Moduls koennte z.B. unter Windows auch eine
  zentrale Registry-Statistik weitergefuehrt werden.
*****************************************************************************/


// Interface header
#include "base/base_ex.h"

// Standard headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>

// Other ECL headers
#include "base/logfile.h"


#if defined __ECL_W32__
   #include <windows.h>
   #include <ctime>
#endif

#if __ECL_DEBUG__ > 0 && _MSC_VER >= 1200
   #include <crtdbg.h>
#endif

#if __ECL_DEBUG__ > 0
   #define __Use_Real_Assertion__
#endif

// Redefinition (because of #undef at the end of base.h)
#define __ECL_DEBUG_ENABLE_STATISTIC__ 2
#define __ECL_DEBUG_FORCE_RECENT__     4

/**
* @defgroup baseclass Base Classes
*/

/**
* @defgroup collections Collections
*/

/**
* @defgroup math Mathmatical
*/

/**
* @defgroup ipc Interprocess Communication
*/

/**
* @defgroup elo Elements and Operations (ELO)
*/

/**
* @defgroup system System Related
*/




namespace ecl {




// ===========================================================================
// Doxygen documentation of cBase
// ===========================================================================

/**
@class   cBase base.h "base/base.h"
@ingroup baseclass
@brief   Steuerklasse der ECL (3 = verheiratet)

Es wird definitiv Zeit, daﬂ cBase ordentlich dokumentiert wird ...

The supported target system is detected by defining exactly one of the
following macros. Alien platforms result in a preprocessor #error instruction.
  - __ECL_OS2__
  - __ECL_W32__
  - __ECL_LINUX__ (if __ECL_GNUC__ and not __ECL_W32__)

The supported compiler is detected by defining exactly one of the following
macros. Alien compilers result in a preprocessor #error instruction.
  - __ECL_ICC__
  - __ECL_VCPP__ (1100 = VS5.0, 1200 = VS6.0, 1300 = VS7.0, 1310 = VS7.1)
  - __ECL_BCPP__
  - __ECL_GNUC__
  - __ECL_MINGW__ (if __ECL_GNUC__ and __ECL_W32__)

Additional the base module contains mechanisms to support debugging during
development of the ECL itself as well as during use of the ECL by applications.
The following key words will explain the underlying concept:

<b>debug flag</b> @n
This is a synonym for the compiler switch __ECL_DEBUG__. See the section
"Globals" -> "Defines" for details. (If somebody knows how to insert
a link to there, please tell me. I'm just not motived to study the doxygen
documentation for it. Thanks. -MW-)

<b>debug mask</b> @n
The debug mask is a bitmask characterizing a debug message. Every debug message
compiled with one of the macros is assigned to a debug mask. During execution
the mask of each message is compared with a configured mask and in case of a
match the debug message is sent to the configured output devices.

The following bits are used to classify the severity of the message:
- dbgInfo -> Information. Just for fun, e.g. to trace the program flow. It
  is mainly used for debugging during development of the ECL itself.
- dbgWarn -> Warnings. Indicates a possible error, but without direct
  effects on the program flow. For example a function is called with
  nonsense parameters that have been detected and fixed to a default
  value. cString().getLeft(-7353) is handled as cString().getLeft(0),
  but the faulty call may indicate a logic error somewhere else.
- dbgError -> Errors. Real errors that should not happen and effect
  the program flow. For example an inconsistent, internal reference
  counter of a cString. Or a resource required for operation was not
  available. Error messages are frequently followed by a throw.
- dbgAssert -> Assertion. This is not a own severity class, but a 
  (historical named) qualifier additional to dbgError. If this bit is
  set, it is recommended to explicit report the error to the User e.g.
  with a message box.

The following bits specify a module group:
- dbgCore -> The core classes are the "internals" of the ECL, hidden
  by cBase. For example messages of cBase::doConfig() or during
  initialization or deinitialization of the ECL.
- dbgBase -> Base class related. The bread and butter of the ecl like
  cString.
- dbgApp -> Application class related. An example is cCmdLine where
  errors through wrong formatted parameters are not really surprising.
- dbgIpc -> Inter process communication

There are some bits with special functions:
- dbgAny -> Special in debug output filter: usually the condition for matching
  two bitmasks is '<tt>(mask & and) == match</tt>'. If the any-bit is
  set in match, the condition '<tt>(mask & and) != 0</tt>' is sufficient.

The other bits are preserved from the old debug mask for compatibility, some
of them will survive and be integrated in the new debug mask, others will be
removed later:
- dbgTrcDb -> Trace: Methoden der Datenbankklassen
- dbgTrcWin -> Trace: Methoden der Windowklassen
- dbgTrcApp -> Trace: Methoden der Anwendungsklassen
- dbgTrcBase -> Trace: Methoden der Basisklassen
- dbgDb -> Datenbankklassen-Spezifisches
- dbgWin -> Windowklassen-Spezifisches
- dbgSql -> Alle SQL-Befehle
- dbgSqlRaw -> SQL-Befehle im DB-spezifischen Format
- dbgMsg -> Meldungs-Spezifisches
- dbgUser -> Frei fuer Benutzer

<b>debug message</b> @n
The debug message is the text assigned with a debug mask during compilation.
In most cases, internally the name of the current source file __FILE__ and
the code line number __LINE__ are available too. There are mostly two 
different styles available:
- static text with a constant string like "no handle available".
- dynamic text with a printf style text like ("errno = %d",errno).

<b>output mask</b> @n
Very similar to the debug mask this is a bitmask characterizing the output
devices a debug message is sent to:
- outCOut -> std::cout
- outCErr -> std::cerr
- outCLog -> std::clog
- outEOut -> ecl print function that has been configured with setPrintFunc().
  Remember: The prototype cBase::PRINT_FUNC of the print function may change in the future!
- outELog -> ecl logfile that has been configured with setLogfile(). (Possibly
  setLogfile() will become obsolete and replaced by doConfig().)

No bitmask without special bits:
- outNul -> This device is the "No output device". Since output_mask == 0 is used
  to remove filters, this device is needed to explicit filter debug masks to
  nowhere.
- outAssert -> If this bit is set, a "real" assert() is generated. In Visual
  Studio this causes a message box with the option to "jump" to the erroneous
  position.

<b>debug filter</b> @n
A debug filter defines a condition consisting of a <b>debug mask</b> pattern (with an
optional filename and) assigns this condition to an <b>output mask</b>. This is used
to select where <b>debug messages</b> are to be sent. For details see doConfig().

@remarks
Take a look at the globals section for the preprocessor macros.

@todo
cBase is currently a building site ...
- See seperate todo list of doConfig().
*/




// ===========================================================================
// Doxygen documentation of preprocessor macros
// ===========================================================================

/**
@def __ECL_DEBUG__
Compiler switch to control debug functionality.
  - @b =0 for release build. Most of the ecl debug macros compile to empty 
    or minimal code to decrease code size and execution overhead.
  - @b >0 for debug build. The full debug capability is compiled. However
    most features can be configured with doConfig() to be inactive.

Usually the switch is either 0 or 1 and outside the ecl base module the
switch should only compared against "== 0" or "!= 0" or "> 0". Inside the
ecl base module several booster bits are defined:
  - @b __ECL_DEBUG_ENABLE_STATISTIC__ defines the macro __ECL_STATISTIC__()
    to count construction calls of several ecl classes with the function
    cBase::DbgStatistic().
  - @b __ECL_DEBUG_FORCE_RECENT__ disables the support of some 'old' /
    'obsolete' / 'deprecated' ecl features (restricted compatibility). You
    may get more compiler warnings or errors in older code.
*/

/**
@def __ECL_DEBUG_ENABLE_STATISTIC__
Booster bit of __ECL_DEBUG__, see there.
*/

/**
@def __ECL_DEBUG_FORCE_RECENT__
Booster bit of __ECL_DEBUG__, see there.
*/

/**
@def __ECL_ASSERT__(cond, mask)
Test for @a cond which must evaluate to be not 0.
@a cond is evalutated in both, debug AND release build, but only in debug
build a <b>debug message</b> is issued if @a cond is 0 (if @a cond fails). 
@code
if (__ECL_ASSERT__( handle != 0 , dbgError|dbgBase )) {
   // normal workflow
} else {
   // error workflow
}
@endcode
*/

/**
@def __ECL_ASSERT_PRINTF__(cond, mask, prnf)
Behaves exactly like __ECL_ASSERT__(cond, mask) except the <b>debug message</b>
comprise an additional printf-style formatted text passed in @a prnf.
@code
__ECL_ASSERT_PRINTF__( handle , dbgWarn|dbgBase , ("Operation failed, errno=%d",errno) );
@endcode
*/

/**
@def __ECL_IFDEBUG__(stmt)
Statement @a stmt is only compiled in the debug build. A ";" behind the macro
is not necessary.
@code
__ECL_IFDEBUG__(cstr = "Test initialization in debug build")
@endcode
*/

/**
@def __ECL_DEBUG_TEXT__(mask, const_text)
Debug message @a const_text that is compiled @b only in debug build, output depends on
@a mask. 
@code
__ECL_DEBUG_TEXT__(dbgError, "Something is wrong")
@endcode
*/

/**
@def __ECL_RELEASE_TEXT__(mask, const_text)
Behaves exactly like __ECL_DEBUG_TEXT__ except the message is compiled in debug *AND*
release build.
*/

/**
@def __ECL_DEBUG_PRINTF__(mask, prnf)
Variable debug message @a prnf that is compiled @b only in debug build, output depends 
on @a mask.
@code
__ECL_DEBUG_PRINTF__(dbgError, ("errno=%d",errno))
@endcode
*/

/**
@def __ECL_RELEASE_PRINTF__(mask, prnf)
Behaves exactly like __ECL_DEBUG_PRINTF__ except the message is compiled in debug *AND*
release build.
*/

/**
@def __ECL_STATISTIC__(label)
If ECL is compiled with booster bit __ECL_DEBUG_ENABLE_STATISTIC__ this macro expands
to a call of the cBase statistic module and increments @a label. This is used in 
several constructors to obtain information on the usage of the classes.
*/

/**
@def __ECL_ASSERT1__(c)
Obsolete (but not deprecated). Correlates to __ECL_ASSERT__(cond, mask) with internal
coded mask. If you replace an old macro, you MUST NOT simply write
__ECL_ASSERT__(c,cBase::dbgAssert). You have to define the serverity bit dbgWarn or
dbgError (dbgInfo is very unlikely) and a module bit like dbgBase. The bit dbgAssert
may be used to highlight dbgError as very serious.
*/

/**
@def __ECL_ASSERT2__(c,p)
Obsolete (but not deprecated). Correlates to __ECL_ASSERT_PRINTF__(cond, mask, prnf)
with internal coded mask. If you replace an old macro, remember the notes on @a mask
from __ECL_ASSERT1__(c). Sometimes this macro have been used for "unconditional" debug
messages with constant 0 or false for c. Replace these by __ECL_DEBUG_TEXT__(mask, text)
or __ECL_DEBUG_PRINTF__(mask, prnf).
*/




// ===========================================================================
// Modullokale Daten (static) / Forward-Deklaration modullokaler Funktionen
// ===========================================================================

// base_singleton ------------------------------------------------------------
// - cCore() Singleton mit Zugriffsfunktion
static cBase::cCore __core__;
cBase::cCore &BASE_CORE()
{
   return __core__;
}


// debug_mask ----------------------------------------------------------------
// - ist das Top-Level-Kriterium das die Debug-Ausgaben steuert
// - wird im cCore() Konstruktor mit Umgebungsvariable ECL_DBG initialisiert
// - sobald die neuen Filter aktiv sind wird in debug_mask eine Gesamtmaske
//   mit allen relevanten bits berechnet. Nur wenn dieses Kriterium ueberhaupt
//   erfuellt ist, wird die Liste der Filter geprueft.
static unsigned long debug_mask = cBase::dbgError;

// debug_filter --------------------------------------------------------------
// - ist der Detail-Filter, der die Debug-Ausgaben steuert (oder 0)
// - wird durch cBase::doConfig("filter ...") verwaltet
// - wird von ~cCore() bereinigt
static cBase::cFilter *debug_filter = 0;

// debug_statistic -----------------------------------------------------------
// - Statistik-Modul das je nach Compilerschalter Konstruktor-Aufrufe zaehlt
// - wird bei Erstbenutzung durch cBase::DbgStatistic angelegt
// - wird von ~cCore() bereinigt
static cBase::cStatistic *debug_statistic = 0;

// output_mask ---------------------------------------------------------------
// - legt fest, auf welchen Geraeten die Ausgabe erfolgt, wenn keine
//   besondere Maske per debug_filter festgelegt ist.
static unsigned long output_mask = cBase::outEOut|cBase::outELog;

// log_file ------------------------------------------------------------------
// - Stellt das Debug-Ausgabegeraet "elog" dar
// - wird ggf. im cCore() Konstruktor mit Umgebungsvariable ECL_LOG initialisiert
// - wird von ~cCore() bereinigt
//static cLogfile *log_file = 0;
static const int LOG_FILES_MAX_COUNT = 4;
static cLogfile *log_files[LOG_FILES_MAX_COUNT] = { 0,0,0,0 };
static int log_files_used = 0;

// ecl_print_func ------------------------------------------------------------
// - Stellt das Debug-Ausgabegeraet "eout" dar
// - kann mit setPrintFunc() dynamisch geaendert werden
static void DefaultEclPrintFunc(const char *text);
static cBase::PRINT_FUNC ecl_print_func = DefaultEclPrintFunc;
// - Die alte Ausgabe-Funktion mit variablen Argumenten wird (inzwischen) *immer*
//   mit fmt="%s\n" aufgerufen und der Prototyp wird nur noch aus Kompatibilitaet
//   EINE GEWISSE ZEIT Unterstuetzt. TBD: Entfaellt spaeter ganz!!!
static cBase::OLD_PRINT_FUNC old_print_func = 0; // frueher: = DefaultPrintFunc;




// print_flag verhindert ungewollte Rekursionen in der Debug-Ausgabe
static int old_print_flag = false; // altes Flag, TBD: rauswerfen




// *ALTE* Funktion um Masken auszuwerten. TBD: rauswerfen ...
static unsigned long getMask(const char *str, cBase::cCore::MASK_NAME *tab, unsigned long def);
// *ALTE* Klartextnamen fuer die Debug-Maske, TBD: rauswerfen
// Achtung: debug_symbol_names ist die neuere Version der Maske !!!
static cBase::cCore::MASK_NAME debug_mask_names[] = {
   {cBase::dbgInfo   , "info"   },
   {cBase::dbgWarn   , "warn"   },
   {cBase::dbgError  , "error"  },
   {cBase::dbgAssert , "assert" },

   {cBase::dbgCore   , "core"   },
   {cBase::dbgBase   , "base"   },
   {cBase::dbgApp    , "app"    },

   {cBase::dbgAny    , "any"    },
   {(unsigned long)-1, "all"    },
   //{0,               , "nul"    },

   // alte Konstanten
   {cBase::dbgTrcBase, "TrcBase"},
   {cBase::dbgTrcDb  , "TrcDb"  },
   {cBase::dbgTrcWin , "TrcWin" },
   {cBase::dbgTrcApp , "TrcApp" },
   {cBase::dbgDb     , "Db"     },
   {cBase::dbgWin    , "Win"    },
   {cBase::dbgSql    , "Sql"    },
   {cBase::dbgSqlRaw , "SqlRaw" },
   {cBase::dbgMsg    , "Msg"    },
   {0L               , 0        } 
};

// Klartextnamen fuer die Output-Maske
static cBase::cCore::MASK_NAME output_mask_names[] = {
   cBase::outCOut    , "cout",
   cBase::outCErr    , "cerr",
   cBase::outCLog    , "clog",
   cBase::outEOut    , "eout",
   cBase::outELog    , "elog",
   cBase::outNul     , "nul",
   cBase::outAssert  , "assert",
   0                 , "remove",
   ~0UL              , "all",
   0                 , 0
};

static cBase::cParser::SYMBOL debug_symbol_names[] = {
   //{(unsigned long)-1, "all"    },
   {cBase::dbgInfo|cBase::dbgWarn|cBase::dbgError|cBase::dbgAssert|
    cBase::dbgCore|cBase::dbgBase|cBase::dbgIpc|cBase::dbgApp|
    cBase::dbgTrcBase|cBase::dbgTrcDb|cBase::dbgTrcWin|cBase::dbgTrcApp|
    cBase::dbgDb|cBase::dbgWin|cBase::dbgSql|cBase::dbgSqlRaw|cBase::dbgMsg, "all" },

   {cBase::dbgInfo   , "info"   },
   {cBase::dbgWarn   , "warn"   },
   {cBase::dbgError  , "error"  },
   {cBase::dbgAssert , "assert" },

   {cBase::dbgCore   , "core"   },
   {cBase::dbgBase   , "base"   },
   {cBase::dbgIpc    , "ipc"    },
   {cBase::dbgApp    , "app"    },

   {cBase::dbgAny    , "any"    },
   //{0,               , "nul"    },
   // alte Konstanten
   {cBase::dbgTrcBase, "TrcBase"},
   {cBase::dbgTrcDb  , "TrcDb"  },
   {cBase::dbgTrcWin , "TrcWin" },
   {cBase::dbgTrcApp , "TrcApp" },
   {cBase::dbgDb     , "Db"     },
   {cBase::dbgWin    , "Win"    },
   {cBase::dbgSql    , "Sql"    },
   {cBase::dbgSqlRaw , "SqlRaw" },
   {cBase::dbgMsg    , "Msg"    },
   {0L               , 0        } 
};

// Klartextnamen fuer die Output-Maske
static cBase::cParser::SYMBOL output_symbol_names[] = {
   cBase::outCOut    , "cout",
   cBase::outCErr    , "cerr",
   cBase::outCLog    , "clog",
   cBase::outEOut    , "eout",
   cBase::outELog<<1 , "elog1",
   cBase::outELog<<2 , "elog2",
   cBase::outELog<<3 , "elog3",
   //cBase::outELog<<4 , "elog4",
   //cBase::outELog<<5 , "elog5",
   //cBase::outELog<<6 , "elog6",
   //cBase::outELog<<7 , "elog7",
   cBase::outELog    , "elog",
   cBase::outNul     , "nul",
   cBase::outAssert  , "assert",
   0                 , "remove",
   ~0                , "all",
   0                 , 0
};




// ===========================================================================
// cBase::cCore Implementierung
// ===========================================================================


// Debug-Maske fuer Ausgaben in cBase & Hilfsklassen
const unsigned long CORE_ERROR = cBase::dbgCore | cBase::dbgError;
const unsigned long CORE_WARN  = cBase::dbgCore | cBase::dbgWarn;
const unsigned long CORE_INFO  = cBase::dbgCore | cBase::dbgInfo;


// Konstruktor / Initialisierung
cBase::cCore::cCore() :
   _include_depth_limit(10)
{
   // Fehler in der Umgebungsvariablen ECL_CFG werden mit Dateiname "ecl startup(n)" angezeigt
   _include_file = "ecl startup";
   _include_line_count = 0;

   // TBD: rauswerfen, aber warnen wenn die Umgebungsvariable noch gesetzt ist?
   char *dbg = getenv("ECL_DBG");
   if (dbg != 0)
      debug_mask = getMask(dbg, debug_mask_names, cBase::dbgError);

   // TBD: rauswerfen, aber warnen wenn die Umgebungsvariable noch gesetzt ist?
   char *log = getenv("ECL_LOG");
   if (log != 0) {
      //if (log_file == 0) log_file = new0 cLogfile;
      //log_file->setParam(log);
      
      if (log_files_used == 0) log_files_used++;
      if (log_files[0] == 0) log_files[0] = new0 cLogfile;
      log_files[0]->setParam(log);
   }
   
   char *cfg = getenv("ECL_CFG");
   if (cfg != 0) {
      cCore::parseConfig(cfg);
   }

   //#if __ECL_DEBUG__
   //   if (dbg != 0)
   //      __ECL_DEBUG_PRINTF__( dbgInfo|dbgCore,("Init ECL_DBG=%s", dbg) )
   //   if (log != 0)
   //      __ECL_DEBUG_PRINTF__( dbgInfo|dbgCore,("Init ECL_LOG=%s", log) )
   //   if (cfg != 0)
   //      __ECL_DEBUG_PRINTF__( dbgInfo|dbgCore,("Init ECL_CFG=%s", cfg) )
   //#endif

   // Initialisierung fuer cDateTime & Co.
   #if defined __ECL_W32__
// PR GNUC
   #if defined __GNUC__
      tzset(); // Sets time environment variables.
   #else
      _tzset(); // Sets time environment variables.
   #endif
// PR GNUC
   #endif

   // Fehler durch explizite Aufrufe von doConfig() werden mit Dateiname
   // "ecl config(n)" angezeigt, die Zeilenzahl ist die Nummer des Aufrufes.
   _include_file = "ecl config";
   _include_line_count = 0;
}


// Destruktor / Deinitialisierung
cBase::cCore::~cCore()
{
   // Fehler im hinterlegten "letzen Willen" (Exit-Script) werden mit
   // Dateiname "ecl shutdown(n)" mit Testamentszeilenzaehler angezeigt.
   _include_file = "ecl shutdown";
   _include_line_count = 0;

   execLastWill();

   delete debug_statistic;
   delete debug_filter;
   
   //delete log_file;
   for (int i = 0; i < log_files_used; i++) {
      delete log_files[i];
   }
}




void cBase::cCore::printMasked(const char *text)
{
   printMasked(output_mask, text);
}

void cBase::cCore::printMasked(unsigned long mask, const char *text)
{
   cCriticalGuard g(_print_masked_critical);
   
   if (text == 0) text = "";
   setLastPrintText(text);

   if (mask & outCOut) {
      std::cout << text << std::endl;
   }
   if (mask & outCErr) {
      std::cerr << text << std::endl;
   }
   if (mask & outCLog) {
      std::clog << text << std::endl;
   }

   //if ((mask & outELog) && log_file != 0) {
   //   log_file->write(text);
   //}
   if (mask & maskELog) {
      for (int i = 0; i < log_files_used; i++) {
         if ((mask & (outELog << i)) && log_files[i] != 0) {
            log_files[i]->write(text);
         }
      }
   }
   // Die Ausgabefunktion ist die letzte die aufgerufen wird, weil sie
   // von aussen konfiguriert werden kann und evtl. nicht funktioniert.
   if (mask & outEOut) {
      try {
         ecl_print_func(text);
      } catch (...) {
         // Bei Problemen mit der Ausgabefunktion kann hoechstens noch in
         // logfile #0 eine Fehlermeldung ausgegeben werden.
         if ((mask & outELog) && log_files[0] != 0) {
            log_files[0]->write("BASE_CORE PRINT EXCEPTION: debug print function failed");
         }
      }
   }
}




void cBase::cCore::addLastWill(const char *cmd)
{
   _last_will.addTail(cString(cmd)) ;
}

void cBase::cCore::execLastWill()
{
   while (_last_will.isEmpty() == false) {
      cCore::parseConfig(_last_will.getHead());
      _last_will.removeHead();
   }
}




// config_string in mit '\n' getrennte Zeilen aufbrechen
bool cBase::cCore::parseConfig(const cString &config_string)
{
   cString batch(config_string);
   while (batch.isEmpty() == false) {
      cString line = cStrEnv::replace(batch.getPart(0,"\n"));
      batch = batch.getTail(1,"\n");
      if (parseLine(line) == false) {
         return false;
      }
   }
   return true;
}

// Einzelne Zeile mit ggf. mehreren Kommandos
bool cBase::cCore::parseLine(const cString &config_line)
{
   cBase::cParser p(config_line);
   
   cString error;
   while (p == true && error.isEmpty()) {
      _include_line_count++;

      cmdClear(p, error) ||
      cmdAtExit(p, error) ||
      cmdInclude(p, error) ||
      cmdSet(p, error) ||
      cmdFilter(p, error) ||
      cmdLogfile(p, error) ||
      cmdEcho(p, error);

      if (error.isEmpty()) {
         if (isEoln(p)) {  // checks also for comments with # or //
            return true;
         }
         p.isChar(';');
      }
   }
   cBase::DbgMessage(CORE_ERROR, _include_file, _include_line_count, (error.isEmpty()?"syntax error":error));
   return false;
}


// BEFEHL: "clear"
bool cBase::cCore::cmdClear(cBase::cParser &p, cString &) // cString &error
{
   if (p.isStr("clear") == false) {
      p.ok();
      return false;
   }

   delete debug_statistic;
   debug_statistic = 0;

   delete debug_filter;
   debug_filter = 0;

   // TBD: Konstante dafuer
   debug_mask = cBase::dbgError;
   // TBD: Konstante dafuer
   output_mask = cBase::outEOut|cBase::outELog;

   // _include_line_count = 0; ??

   return true;
}


// BEFEHL: "atexit" <command>
bool cBase::cCore::cmdAtExit(cBase::cParser &p, cString &) // cString &error
{
   if (p.isStr("atexit") == false) {
      p.ok();
      return false;
   }

   cString cmd;
   getStringTail(p,cmd);
   addLastWill(cmd.ccp());
   return true;
}


// BEFEHL: ("include" | "@") <filename>
bool cBase::cCore::cmdInclude(cBase::cParser &p, cString &error)
{
   cBase::cParser::SYMBOL cmdlist[] = { 
      1, "include",
      2, "@",
      0, 0
   };
   
   long cmd = -1;
   if (p.getStdSymbol(cmdlist,cmd) == false) {
      p.ok();
      return false;
   }

   cString filespec;
   FILE *file = 0;
   if (getStringTail(p,filespec) == false || filespec.isEmpty()) {
      error = "no filespec";
   } else if (_include_depth_limit <= 0) {
      error = "include depth limit reached";
   } else if ((file = fopen(filespec.ccp(), "r")) == 0) {
      error = "include file " + filespec + " not found";
   }

   if (error.isEmpty()) {
      const char *saved_include_file = _include_file;
      int saved_include_line_count = _include_line_count;
      _include_depth_limit--;
      _include_file = filespec;
      _include_line_count = 0;

      char line[256];
      while (!feof(file)) {
         if (fgets(line, sizeof(line), file)) {
            if (strchr(line,'\n')) *strchr(line,'\n') = '\0';
            // Fehler werden nur gemeldet, aber die weitere Bearbeitung
            // der Include-Datei wird dadurch nicht abgebrochen !!!
            if (parseConfig(line) == false) {
               error = "error in include file " + filespec;
            }
         }
      }

      _include_depth_limit++;
      _include_file = saved_include_file;
      _include_line_count = saved_include_line_count;
   }

   if (file) {
      fclose(file);
   }
   return true;
}

// BEFEHL: "set" "var=value"
bool cBase::cCore::cmdSet(cBase::cParser &p, cString &) // cString &error
{
   if (p.isStr("set") == false) {
      p.ok();
      return false;
   }

   cString env;
   if (getStringTail(p,env) && env.isEmpty() == false) {
      _putenv((char*)(const char *)env); // GnuC erwartet char*
   } else {
      p.ok(false);
   }
   return true;
}

// BEFEHL: "logfile" <logfile>
bool cBase::cCore::cmdLogfile(cBase::cParser &p, cString &) // cString &error
{
   if (p.isStr("logfile") == false) {
      p.ok();
      return false;
   }

   unsigned long file_number = 0;
   if (p.isChar('#').getULong(file_number)) {
      if (file_number >= LOG_FILES_MAX_COUNT) file_number = 0;
   } else {
      p.ok();
   }
   
   cString param;
   getStringTail(p,param);

   //if (log_file == 0) log_file = new0 cLogfile;
   //log_file->setParam(param.ccp());
   
   if ((int)file_number >= log_files_used) log_files_used = file_number+1;
   if (log_files[file_number] == 0) log_files[file_number] = new0 cLogfile;
   log_files[file_number]->setParam(param.ccp());
   
   return true;
}

// BEFEHL: "filter" ["top"] ["&" andmask] ["=" matchmask] ["@" filename] [">" outmask]
bool cBase::cCore::cmdFilter(cBase::cParser &p, cString &) // cString &error
{
   if (p.isStr("filter") == false) {
      p.ok();
      return false;
   }

   long mand = 0, match = ~0, out = output_mask;
   bool add_at_end = true;
   cString file;

   // keyword "top" allows to place a filter in front of all others
   if (p.isStr("top")) {
      add_at_end = false;
   } else {
      p.ok();
   }

   p.isChar('&').setSymbolList(debug_symbol_names).getBitmaskExpr(mand).ok();
   p.isChar('=').setSymbolList(debug_symbol_names).getBitmaskExpr(match).ok();
   p.isChar('@').getStr(file).ok();
   p.isChar('>').setSymbolList(output_symbol_names).getBitmaskExpr(out).ok();

   if (match != cBase::dbgAny)
      match &= mand;
   if (debug_filter == 0) {
      debug_filter = new0 cBase::cFilter;
   }
   debug_filter->addFilter(mand, match, file.ccp(), out, add_at_end);
   return true;
}

// BEFEHL: "echo" ( any_text | ">" outmask | "statistic" | "status" | "filter" )
bool cBase::cCore::cmdEcho(cBase::cParser &p, cString &) // cString &error
{
   cBase::cParser::SYMBOL keylist[] = { 
      1, ">",
      2, "status",
      3, "filter",
      4, "statistic",
      0, 0
   };

   if (p.isStr("echo") == false) {
      p.ok();
      return false;
   }

   long key = -1;
   p.getStdSymbol(keylist, key).ok();
   switch (key) {
   case 1: // > outmask
      {
         long out = 0;
         if (p.setSymbolList(output_symbol_names).getBitmaskExpr(out)) {
            output_mask = out;
         }
      }
      break;
   case 2: // status
      BASE_CORE().printMasked("status not yet implemented");
      break;
   case 3: // filter
      if (debug_filter == 0) {
         BASE_CORE().printMasked("no filter");
      } else {
         debug_filter->show();
      }
      break; 
   case 4: // statistic
      if (debug_statistic == 0) {
         BASE_CORE().printMasked("no statistic");
      } else {
         debug_statistic->show();
      }
      break;
   case -1:
   default: // any_text
      {
         cString text;
         getStringTail(p,text);
         BASE_CORE().printMasked(cStrEnv::replace(text));
      }
   }
   
   return true;
}


bool cBase::cCore::isEoln(cBase::cParser &p)
{
   return (p.skipSpace() == '\0' || p[0] == '#' || (p[0] == '/' && p[1] == '/'));
}

bool cBase::cCore::getStringTail(cBase::cParser &p, cString &str)
{
   p.skipSpace();
   if (p[0] == '"' || p[0] == '\'') {
      p.getStr(str);
   } else {
      cString result;
      while (p[0] != '\0' && p[0] != '\n' && p[0] != ';' && p[0] != '#' && (p[0] != '/' || p[1] != '/')) {
         result += p[0];
         p += 1;
      }
      str = result.trim();
   }
   return p;
}





// ===========================================================================
// cBase::cStatistic Implementierung
// ===========================================================================

cBase::cStatistic::cStatistic() :
   _statistic_map(new0 cMap<cString, const cString &, long, long>)
{
}

cBase::cStatistic::~cStatistic()
{
   delete _statistic_map;
}
   
long cBase::cStatistic::increment(const cString &key)
{
   _critical.enter();

   long count = 0;
   _statistic_map->lookup(key, count);
   if (count < LONG_MAX) count++;
   _statistic_map->setAt(key, count);

   _critical.leave();
   return count;
}

long cBase::cStatistic::decrement(const cString &key)
{
   _critical.enter();

   long count = 0;
   _statistic_map->lookup(key, count);
   if (count > LONG_MIN) count--;
   _statistic_map->setAt(key, count);

   _critical.leave();
   return count;
}

long cBase::cStatistic::maximum(const cString &key, long value)
{
   _critical.enter();

   long current = 0;
   if (_statistic_map->lookup(key, current) == false || value > current) {
      _statistic_map->setAt(key, value);
   } else {
      value = current;
   }

   _critical.leave();
   return value;
}

long cBase::cStatistic::minimum(const cString &key, long value)
{
   _critical.enter();

   long current = 0;
   if (_statistic_map->lookup(key, current) == false || value < current) {
      _statistic_map->setAt(key, value);
   } else {
      value = current;
   }

   _critical.leave();
   return value;
}

long cBase::cStatistic::assign(const cString &key, long value)
{
   _critical.enter();

   _statistic_map->setAt(key, value);
   
   _critical.leave();
   return value;
}

long cBase::cStatistic::query(const cString &key)
{
   _critical.enter();

   long value = 0;
   _statistic_map->lookup(key, value);
   
   _critical.leave();
   return value;
}

bool cBase::cStatistic::exist(const cString &key)
{
   _critical.enter();

   long value = 0;
   bool rc = _statistic_map->lookup(key, value);
   
   _critical.leave();
   return rc;
}

void cBase::cStatistic::show()
{
   _critical.enter();

   long value;
   cString key;
   IPOSITION pos = _statistic_map->getStartPosition();
   while (pos) {
      _statistic_map->getNextAssoc(pos, key, value);
      BASE_CORE().printMasked((Str((int)value).padLeft(6) + ", " + key).ccp());
   }

   _critical.leave();
}

/**
* Interface to the statistic module: @a what is the operation to perform on @a label:
* - 1: increment @a label by 1(beginning with 0, @a value is ignored)
* - -1: decrement @a label by 1 (beginning with 0, @a value is ignored)
* - 2: store maximum of all @a values in @a label.
* - -2: store minimum of all @a values in @a label.
* - 0 and all other: store @a value in @a label.
*
* You can use doConfig() with the command "echo statistic" to get a list of all
* stored @a labels and the associated counters or values on the debug output.
* (Preliminary, command may change)
*/
long cBase::DbgStatistic(const char *label, int what, long value)
{
   // Statistik-Modul wird erst bei Erstbenutzung angelegt
   if (debug_statistic == 0) debug_statistic = new0 cStatistic;
   switch (what) {
   case -2:
      return debug_statistic->minimum(label, value);
   case -1:
      return debug_statistic->decrement(label);
   case 1:
      return debug_statistic->increment(label);
   case 2:
      return debug_statistic->maximum(label, value);
   case 0:
   default:
      return debug_statistic->assign(label, value);
   }
}




// ===========================================================================
// cBase::cFilter Implementierung
// ===========================================================================

cBase::cFilter::cFilter() :
   _filter(0) 
{
}

cBase::cFilter::~cFilter()
{
   FILTER *filter = _filter;
   while (filter) {
      filter = freeFilter(filter);
   }
}

unsigned long cBase::cFilter::matchFilter(unsigned long mask, const char *file)
{
   FILTER *filter = _filter;
   while (filter) {
      if ( ( (mask & filter->mand) == filter->match || 
             (mask & filter->mand) && (filter->match & dbgAny) )  
           && isMatching(filter->file, file) ) {
         return filter->out;
      }
      filter = filter->next;
   }
   return 0;
}

void cBase::cFilter::addFilter(unsigned long mand, unsigned long match, const char *file, unsigned long out, bool atend)
{
   FILTER *elem = unlinkEqualFilter(mand, match, file);

   if (elem == 0 && out != 0) {
      // Neuer Filtereintrag
      elem = new0 FILTER;
      elem->mand = mand;
      elem->match = match;
      if (file && *file) {
         elem->file = new0 char[strlen(file)+1];
         strcpy(elem->file, file);
      } else {
         elem->file = 0;
      }
      elem->out = out;
      elem->next = 0;
   } else if (elem != 0) {
      if (out == 0) {
         // Filtereintrag loeschen
         elem = freeFilter(elem);
      } else {
         // Filtereintrag modifizieren
         elem->out = out;
      }
   }

   if (elem != 0) {
      if (atend && _filter != 0) {
         // ans Ende der Liste
         FILTER *tail = _filter;
         while (tail->next != 0) {
            tail = tail->next;
         }
         tail->next = elem;
      } else {
         // an den Anfang der Liste
         elem->next = _filter;
         _filter = elem;
      }
   }

   debug_mask = calcDebugMask();
}

void cBase::cFilter::show()
{
   FILTER *filter = _filter;
   while (filter) {
      cString text = cString("filter &") + cParser::getSymbolBitmask(filter->mand, debug_symbol_names);
      if (filter->mand != filter->match) 
         text += cString(" =") + cParser::getSymbolBitmask(filter->match, debug_symbol_names);
      if (filter->file) 
         text += cStringf(" @%s",filter->file);
      text += cString(" >") + cParser::getSymbolBitmask(filter->out, output_symbol_names);
      BASE_CORE().printMasked(text.ccp());
      filter = filter->next;
   }
}


cBase::cFilter::FILTER *cBase::cFilter::freeFilter(FILTER *filter)
{
   FILTER *ret = filter->next;
   if (filter->file != 0) delete[] filter->file;
   delete filter;
   
   return ret;
}

cBase::cFilter::FILTER *cBase::cFilter::unlinkEqualFilter(unsigned long mand, unsigned long match, const char *file)
{
   FILTER *pred = 0;
   FILTER *filter = _filter;
   while (filter) {
      if (filter->mand == mand && filter->match == match && isEqual(filter->file, file)) {
         if (pred == 0) {
            _filter = filter->next;
         } else {
            pred->next = filter->next;
         }
         filter->next = 0;
         return filter;
      }
      pred = filter;
      filter = filter->next;
   }
   return 0;
}

unsigned long cBase::cFilter::calcDebugMask() const
{
   unsigned long mask = 0;
   FILTER *filter = _filter;
   while (filter) {
      if (filter->mand == 0 && filter->match == 0) {
         // Wenn das Paar (mand,match) immer trifft und nur nach file
         // entschieden wird -> debug_mask vollstaendig oeffnen.
         mask = ~0UL;
         break;
      }
      mask |= filter->mand;
      filter = filter->next;
   }
   return mask;
}

bool cBase::cFilter::isMatching(const char *pattern, const char *current)
{
   if (pattern == 0 || *pattern == 0)
      return true;
   int patlen, curlen;
   if (current == 0 || (patlen=strlen(pattern)) > (curlen=strlen(current)))
      return false;
   return _stricmp(current+curlen-patlen, pattern) == 0;
}
   
bool cBase::cFilter::isEqual(const char *f1, const char *f2)
{
   if ((f1 == 0 || *f1 == 0) && (f2 == 0 || *f2 == 0))
      return true;
   if (f1 == 0 || f2 == 0)
      return false;
   return _stricmp(f1, f2) == 0;
}




// ===========================================================================
// cBase::cParser Implementierung
//
// Klassen die auch ueber Texte konfiguriert werden koennen und die evtl.
// auf cBase::cParser umgestellt werden koennen, damit ein einheitliches
// Verhalten in der ECL erreicht wird:
//
//    cCmdLine (Optionstokens & symbolische Bitmasken)
//    cLogfile (da weiss eigentlich keiner was davon ... hihi)
//    cErrBase (einlesen der Meldungstexte)
//    cDate, cTime (bessere Konstruktoren ueber Zeichenketten)
//    ...
// ===========================================================================

cBase::cParser& cBase::cParser::operator+=(size_t offset)
{
   if (_ok) {
      while (*_ptr && offset) {
         _ptr++;
         offset--;
      }
      _ok = (offset == 0);
   }
   return *this;
}

char cBase::cParser::skipSpace()
{
   if (_ptr) {
      while (_skip_space && isspace(*_ptr)) _ptr++;
      return *_ptr;
   } else {
      _ok = false;
      return 0;
   }
}

cBase::cParser& cBase::cParser::getChar(char &ch)
{
   if (_ok) {
      ch = skipSpace();
      if (*_ptr) _ptr++;
   }
   return *this;
}

cBase::cParser& cBase::cParser::isChar(char ch, bool ignore_case)
{
   if (_ok && (skipSpace() == ch || (ignore_case == true && toupper(skipSpace()) == toupper(ch)))) {
      if (*_ptr) _ptr++;
   } else {
      _ok = false;
   }
   return *this;
}

cBase::cParser& cBase::cParser::isStr(const char *str, bool ignore_case)
{
   if (_ok && str && skipSpace() == *str) {
      const char *from = _ptr;
      if (ignore_case == true) {
         while (*str && toupper(*_ptr) == toupper(*str)) { str++; _ptr++; }
      } else {
         while (*str && *_ptr == *str) { str++; _ptr++; }
      }
      if (*str == '\0') return *this;
      _ptr = from;
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getULong(unsigned long &value, int base)
{
   if (_ok && skipSpace() && (_skip_space || !isspace(*_ptr))) {
      char *endp;
      unsigned long temp = strtoul(_ptr, &endp, base);
      if (endp > _ptr) {
         value = temp;
         _ptr = (const char *)endp;
         return *this;
      }
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getULong(unsigned long &value, unsigned long from, unsigned long to, int base)
{
   if (_ok && skipSpace()) {
      unsigned long temp;
      const char *save_ptr = _ptr;      
      if ((getULong(temp,base) == true) && (temp >= from) && (temp <= to)) {
         value = temp;
         return *this;
      }      
      _ptr = save_ptr;
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getLong(long &value, int base)
{
   if (_ok && skipSpace() && (_skip_space || !isspace(*_ptr))) {
      char *endp;
      long temp = strtol(_ptr, &endp, base);
      if (endp > _ptr) {
         value = temp;
         _ptr = (const char *)endp;
         return *this;
      }
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getLong(long &value, long from, long to, int base)
{
   if (_ok && skipSpace()) {
      long temp;
      const char *save_ptr = _ptr;      
      if ((getLong(temp,base) == true) && (temp >= from) && (temp <= to)) {
         value = temp;
         return *this;
      }      
      _ptr = save_ptr;
   }
   _ok = false;
   return *this;
}
   

cBase::cParser& cBase::cParser::getStr(cString &value)
{
   if (_ok && (skipSpace() == '"' || *_ptr == '\'')) {
      const char *from = _ptr++;
      while (*_ptr && *_ptr != *from) _ptr++;
      if (*_ptr) {
         value = cString(from+1, (_ptr++)-from-1);
         return *this;
      }
      _ptr = from;
   } else if (_ok) {
      const char *from = _ptr;
      while (*_ptr && !isspace(*_ptr)) _ptr++;
      if (_ptr > from)  {
         value = cString(from, _ptr-from);
         return *this;
      }
      _ptr = from;
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getStdSymbol(SYMBOL* sym, long &value, bool ignore_case)
{
   if (_ok && sym && skipSpace()) {
      while (sym->name) {
         int cmp = ignore_case ? 
                   cString::_strnicmp(sym->name, _ptr, strlen(sym->name)) :
                   strncmp(sym->name, _ptr, strlen(sym->name));
         if (cmp == 0) {
            _ptr += strlen(sym->name);
            value = sym->value;
            return *this;
         }
         sym++;
      }
   }
   _ok = false;
   return *this;
}

cBase::cParser& cBase::cParser::getBitmaskExpr(long &value)
{
   cBase::cParser::SYMBOL oplist[] = { 1,"+", 2,"-", 3,"|", 4,"&", 5,"&~", 6, "^", 0,0 };
   if (_ok && (getLong(value) == true || (ok(),getSymbol(value)) == true)) {
      long opera;
      while (getStdSymbol(oplist, opera)) {
         long other;
         if (getLong(other) == true || (ok(),getSymbol(other)) == true) {
            switch (opera) {
            case 1: value += other; break;
            case 2: value -= other; break;
            case 3: value |= other; break;
            case 4: value &= other; break;
            case 5: value &= ~other; break;
            case 6: value ^= other; break;
            }
         } else {
            _ok = false;
            return *this;
         }
      }
      _ok = true;
      return *this;
   }
   _ok = false;
   return *this;
}

cString cBase::cParser::getSymbolBitmask(long value, SYMBOL *sym)
{
   cString result;
   while (value) {
      SYMBOL *search = sym;
      while (search->name) {
         if ((value & search->value) == search->value) {
            if (result.isEmpty() == false) result += "|";
            result += search->name;
            value ^= search->value;
            break;
         }
         search++;
      }
      if (search->name == 0) {
         if (result.isEmpty() == false) result += "|";
         result += cStringf("0x%x",value);
         value = 0;
      }
   }
   return result.isEmpty() ? "0" : result;
}


// ===========================================================================
// cBase::cCritical Implementierung
// ===========================================================================

cBase::cCritical::cCritical()
{
#ifdef __linux__
#else
   _critical_section = new0 CRITICAL_SECTION;
   InitializeCriticalSection((CRITICAL_SECTION*)_critical_section);
#endif
}

cBase::cCritical::~cCritical()
{
#ifdef __linux__
#warning "method not ported for target linux"
#else
   DeleteCriticalSection((CRITICAL_SECTION*)_critical_section);
   delete (CRITICAL_SECTION*)_critical_section;
#endif
}

void cBase::cCritical::enter()
{
#ifdef __linux__
#warning "method not ported for target linux"
#else
   EnterCriticalSection((CRITICAL_SECTION*)_critical_section);
#endif
}

void cBase::cCritical::leave()
{
#ifdef __linux__
#warning "method not ported for target linux"
#else
   LeaveCriticalSection((CRITICAL_SECTION*)_critical_section);
#endif
}

// ===========================================================================
// Implementierung cBase
// ===========================================================================


// ---------------------------------------------------------------------------
// Memory-Leak-Detection
// ---------------------------------------------------------------------------

// Wird (z.Zt.) sowieso nur von Visual Studio >= 6.0 unterst¸tzt, und das
// zuletzt auch in einer Form, die nicht wirklich weiterhin eine Hilfsklasse
// __ECL_cAutoLeakReport__ erfordert. ‹berfl¸ssige Pfunde entfernt.

#if __ECL_DEBUG__ > 0 \
    && (defined __ECL_MAKE_DLL__ || defined __ECL_MAKE_LIB__) \
    && defined __ECL_W32__ \
    && __ECL_VCPP__ >= 1200
   void cBase::setMemoryLeakDetect(bool enable)
   {
      if (enable)
         _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF);
      else
         _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & ~_CRTDBG_LEAK_CHECK_DF);
   }
#else
   void cBase::setMemoryLeakDetect(bool)
   {
      // do nothing
   }
#endif


// ---------------------------------------------------------------------------
// "Attribute" setzen/lesen
// ---------------------------------------------------------------------------


// Historische Attribute die nur noch zur Kompatibilitaet unterstuetzt werden,
// koennen fuer Haertetests per Compilerschalter deaktiviert werden.
#if (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0

   //! Klassische Debug-Maske ueber Symbole setzen. TBD: rauswerfen
   void cBase::setDebugMask(const char *str)
   {
      setDebugMask(getMask(str, debug_mask_names, 0));
   }

   //! Klassische Debug-Maske numerisch setzen. Wurden einmal die neuen Debug-Filter
   //! aktiviert, werden Aufrufe von setDebugMask() ignoriert.
   void cBase::setDebugMask(unsigned long mask)
   {
      // TBD: wie wird die Maske zusammen mit Debug-Filtern gehandhabt?
      // Wird dadurch die Filterliste deaktiviert & freigegeben?
      if (debug_filter != 0) {
         __ECL_DEBUG_TEXT__(dbgCore|dbgWarn, "Attempt to set debug mask while debug filter active ignored");
      } else {
         debug_mask = mask;
      }
   }

   //! Klassische Debug-Maske lesen. TBD: rauswerfen
   unsigned long cBase::getDebugMask()
   {
      return debug_mask;
   }

   //! @a Obsolete. Set debug output function for device "eout". This function is
   //! only provided for compatibility to support the deprecated function prototype
   //! <tt>int PrintFunction(const char *fmt, ...)</tt>
   //! with the (never really needed) variable argument list. Setting a old style
   //! print function will always cause a warning and is completely ignored if a
   //! new stype print function is configured. This function
   //! is provided for compatibility and may be removed at a later moment.
   void cBase::setPrintFunc(OLD_PRINT_FUNC printf)
   {
      if (ecl_print_func == DefaultEclPrintFunc) {
         old_print_func = printf;
         __ECL_DEBUG_TEXT__(dbgCore|dbgWarn, "Old style print function configured");
      } else {
         __ECL_DEBUG_TEXT__(dbgCore|dbgWarn, "Old style print function ignored since new style already configured");
      }
   }

#endif // (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0


//! Set debug output function for device "eout". The print function prototype is
//! <tt>void PrintFunction(const char *text)</tt>
//! where @a text should not end with a '\\n'. Set to 0 to reactivate the default
//! implementation 
void cBase::setPrintFunc(PRINT_FUNC printf)
{
   ecl_print_func = (printf ? printf : DefaultEclPrintFunc);
}

//! Logdatei auswaehlen und aktivieren
void cBase::setLogfile(const char *fname, bool append)
{
   //if (log_file == 0) log_file = new0 cLogfile;
   //log_file->setFile(fname,append);
   
   if (log_files_used == 0) log_files_used++;
   if (log_files[0] == 0) log_files[0] = new0 cLogfile;
   log_files[0]->setFile(fname,append);
   
   // auch in der Ausgabemaske aendern!
   //if (fname && *fname) {
   //   output_mask |= outELog;
   //} else {
   //   output_mask &= ~outELog;
   //}
}

//! Groesse der Logdatei festlegen. TBD: rauswerfen
void cBase::setLogfileDimension(int max_gen, long max_size)
{
   //if (log_file == 0) log_file = new0 cLogfile;
   //log_file->setLimits(max_gen, max_size);
   
   if (log_files_used == 0) log_files_used++;
   if (log_files[0] == 0) log_files[0] = new0 cLogfile;
   log_files[0]->setLimits(max_gen, max_size);
}


// ---------------------------------------------------------------------------
// Debug-Ausgaben
// ---------------------------------------------------------------------------


static void DefaultEclPrintFunc(const char *text)
{
   if (old_print_func != 0) {
      // Kompatibilitaetsmodus: wenn eine alte Ausgabefunktion mit variabler
      // Argumentliste konfiguriert ist, wird diese benutzt.
      old_print_func("%s\n", text);
   } else {
      #if defined __ECL_VCPP__
         OutputDebugString(text);
         OutputDebugString("\n");
      #else
         fprintf(stderr, "%s\n", text);
      #endif
   }
}



/**
Factory method for printf-style format strings. The returned char * has
been allocated with new char[] and @b must be released with delete[] when
it is not needed any more. Print buffer is limited to 2048 bytes.
*/
char *cBase::DbgFormatFactory(const char *fmt, ...)
{
   char *result = new0 char[2048];
   va_list ap;
   va_start(ap, fmt);
   vsprintf(result, fmt, ap);
   va_end(ap);

   return result;
}

// Platformabhaengige Implementierungen fuer "echte" Asserts werden in einem
// Macro versteckt, damit DbgMessage() uebersichtlich bleibt.
#ifndef __Use_Real_Assertion__

   // No "real asserts"
   #define ECL_REAL_ASSERT(file, line, cond, text)

#elif __ECL_VCPP__ > 1300

   // Microsoft VS7.1 and newer
/// PR 22.12.07
///   #define ECL_REAL_ASSERT(file, line, cond, text) _assert(cond, file, line);
   #define ECL_REAL_ASSERT(file, line, cond, text) _ASSERT(cond);

#elif __ECL_VCPP__ >= 1200

   // Microsoft VS6.0 and VS7.0
   // VCPP Message-Box:
   // [Abbrechen]   -> _CrtDbgReport kehrt nicht zurueck
   // [Wiederholen] -> Rueckgabe 1 -> Ausfuehrung anhalten
   // [Ignorieren]  -> Rueckgabe 0 -> Weitermachen
   #define ECL_REAL_ASSERT(file, line, cond, text) \
      if ( _CrtDbgReport(_CRT_ASSERT, file, line, "ecl", (text?"%s\nDetails: %s":"%s"), cond, text) == 1 )  _CrtDbgBreak();

#elif defined __ECL_GNUC__

   // The template for this implementation of "real asserts" has been taken
   // from <assert.h> of GCC 3.3.1 (SuSE Linux). Function name has been
   // replaced by additional message text. No guarantee of compatibility!
   // __assert_fail (__STRING(expr), __FILE__, __LINE__, __ASSERT_FUNCTION)
   #define ECL_REAL_ASSERT(file, line, cond, text) \
      __assert_fail( cond, file, line, text );
   
#else

   // Generic assert from C Standard Library. The additional information
   // must be taken from another ECL output device, e.g. a logfile.
   #define ECL_REAL_ASSERT(file, line, cond, text) assert(0);

#endif


/**
Generic debug output function.
*/
bool cBase::DbgMessage(unsigned long mask, const char *file, int line, const char *static_text, char *dynamic_text)
{
   // Die innerhalb einer Debug-Ausgabe verwendeten Teile der ECL sollten so stabil
   // uns sicher sein, dass es zu keinem rekursiven Aufruf der Debug-Ausgabe kommt:
   // - Sollte 'assert(recursion_protection)' dennoch zuschlagen, bitte unbedingt
   //   versuchen die Ursache zu ermitteln (und -MW- benachrichtigen).
   // - Notfalls kann die assert()-Anweisung auf eigenes Risiko auskommentiert werden,
   //   vielleicht laeufts dann ja, auch wenn das eigentliche Problem ungeloest ist.
   
   //static bool recursion_protection = true;
   //assert(recursion_protection);

   unsigned long outmask = output_mask;
   if ( /*recursion_protection &&*/ (debug_mask & mask) && 
        (debug_filter == 0 || (outmask=debug_filter->matchFilter(mask,file)) != 0) ) {

      //recursion_protection = false;
      // Um den Rekursionsschutz zu testen, die folgende Zeile aktivieren:
      // DbgMessage(1, "selftest", -1, "static_text");

      // Ausgabeformatierung (intern wird cString verwendet!) immer VC konform,
      // weil man so durch einen Click im Studio zur Fehlerstelle gelangt. Wenn
      // es fuer andere Platformen oder Compiler andere sinnvolle Formate gibt
      // spricht nichts dagegen, diese auch zu implementieren (‹bersetzungsschalter
      // oder zur Laufzeit geeignet konfigurierbar).

      // Datename (relativer Pfad am Anfang vorher entfernen)
      while (file && (*file == '.' || *file == '\\' || *file == '/')) 
         file++;

      cString text;
      // Wenn ein Dateiname angegeben ist, ist Zeilenanfang "<file>(<line>) : "
      if (file != 0) {
         text += file;
         text += "(";
         text += Str(line);
         text += ") : ";
      }

      // Fehlerklasse
      if (mask & dbgError) 
         text += "ERROR ";
      else if (mask & dbgWarn)
         text += "WARNING ";
      else if (mask & dbgInfo)
         text += "INFO ";
      // Spezialbits
      if (mask & dbgAssert)
         text += "ASSERT ";
      // Abschluss von Fehlerklasse & Spezialbits
      if (mask & (dbgError|dbgWarn|dbgInfo|dbgAssert))
         text += ": ";

      // Textkomponenten
      text += cString(static_text);
      text += (static_text && dynamic_text) ? " : " : "";
      text += cString(dynamic_text);

      // Ausgabe an alle aktivierten Geraete
      BASE_CORE().printMasked(outmask, text.ccp());

      // Falls konfiguriert noch ein "echtes" Assert ausloesen!
      if (outmask & outAssert) {
         ECL_REAL_ASSERT(file, line, static_text, dynamic_text)
      }

      //recursion_protection = true;
   }
   delete[] dynamic_text;
   return false;
}

/**
Get the last debug output message that has been displayed. Filtered messages
are not stored.
*/
const char *cBase::getLastMessage()
{
   return BASE_CORE().getLastPrintText().ccp();
}

 
/**
Embedded and defined environment variables "%env%" are replaced in the 
command string (non recursive). If a the configuration command is executed 
without any error, true is returned. In case of an error a debug message
has been triggered and false is returned.

During start of the ECL the environment variable "ECL_CFG" is read and
the contained string is executed with doConfig(). Usually the instruction
is "include <some ecl config file>" to read a configuration from a file.

The @a config_string in EBNF:
@verbatim
config_string = config_line { "\\n" config_line } ;
config_line = [ command { ";" command } ] [ comment ] ;
comment = ( "//" | "#" ) ?any chars up to the end of config_line? ;

command = 
   "atexit" command_tail |
   "echo" ( "statistic" | "status" | "filter" | ">" outmask | command_tail ) |
   "filter" ["top"] ["&" andmask] ["=" matchmask] ["@" filename] [">" outmask] |
   ( "include" | "@" ) command_tail |
   "logfile" ["#" file_number] command_tail |
   "set" command_tail |
   "clear" ;

filename = ? ... ? ;
   (* das Dateiende wird geprueft: ex.cpp passt zu elo_ex.cpp und string_ex.cpp *)

outmask = bit_expression ;
   (* Valid symbols in outputmask are "cout", "cerr", "clog", 
   "eout", "elog", "elog1", "elog2", "elog3", "nul",
   "assert", "remove" and "all" *)
andmask = bit_expression ;
matchmask = bit_expression ;
   (* Valid symbols in andmask and matchmask are "info", "warn",
   "error", "assert", "core", "base", "app", "any" and "all".
   The following symbols are for compatibility and are to be
   reworked: "TrcBase", "TrcDb", "TrcWin", "TrcApp", "Db", "Win",
   "Sql", "SqlRaw" and "Msg" *)

bit_expression = bit_value { bit_operator bit_value } ;
bit_value = ?either a valid dec/hex/oct number or a valid symbol? ;
bit_operator = '+' | '-' | '|' | '&' | '&~' | '~' ;

file_number = ?a valid dec/hex/oct number from 0 to 3? ;


command_tail = (* rest of the command line *)
   '"' ?any chars except delimiter? '"' |
   "'" ?any chars except delimiter? "'" |
   ?any chars up to ";", "//" or "#"? ;
@endverbatim

The configuration commands are:

  - <tt>@b atexit command</tt>\n
    Deposit commands that are executed on termination of the ECL. The commands are
    exectued with doConfig() in the order of the @a atexit commands.
  - <tt>@b echo > outmask</tt>\n
    Defines the default output mask used for echo itself. And
    following filter definitions also use this mask as default if there is no explicit
    output mask. Initial value of the default output mask is "elog|eout"
  - <tt>@b echo filter|statistic|status</tt>\n
    Internal ECL informations (depending on the keyword) are printed on the devices 
    of the default output mask. Keywords are:
    - filter: The list of defined debug output filters.
    - statistic: Use counters of several classes (if enabled by compiler switch).
    - status: Status information about the ecl (not yet implemented).
  - <tt>@b echo text</tt>\n
    Print the text on the devices of the default output mask. Can be used for startup
    or termination messages in the logfile.
  - <tt>@b filter [top] & andmask = matchmask @ filespec > outmask</tt>\n
    Specifies a debug output filter. The debug mask provided with a debug message is "anded"
    with @a andmask and then compared with @a matchmask. If it matches and the file of the
    debug message equals to @a filespec the message is handled as @a outmask specifies. If
    @a andmask is missing, 0 is assumed. If @a matchmask is missing, @a andmask is assumed.
    If @a matchmask is "any" it is sufficient that the anded value is not zero.
    If @a filespec is missing, the file of the message don't care. If @a outmask is missing
    the current default output mask is assumed. If "remove" is used as output mask an already
    existing, matching filter is removed. Filters are usually checked in the order they were
    specified (that means, they are added at the end of the filter list). With the keyword
    "top" immediately after the command "filter" a new filter is placed at the beginning of the
    filter list and is checked before all previously defined filters are processed.
  - <tt>@b include filespec</tt>\n
    Includes the configuration commands in @a filespec. A valid synonym for "include" is "@".
    A maximum of 10 include files may be nested.
  - <tt>@b logfile [# file_number] [parameters] filename</tt>\n
    Set a logfile. Currently up to 4 different logfiles can be configured with
    file_number from 1 to 3 and without a file_number. If file_number is outside the valid range, it is
    ignored (the number of logfiles is currently limited to 4. If this is not
    enough, it could be changed).
    These files are used for elog and elog1 to elog3 output. The optional parameters can configure the
    logfile generations (gen=n), logfile size (size=n), append mode (app=0/1) and
    enable/disable timestamps (time=0/1). They are described in cLogfile::setParam().
    (Preliminary, command syntax may change).
  - <tt>@b set variable=value</tt>\n
    Assigns a value to an environment variable. This may be used e.g. to define
    ECL_ERRMSG which specifies the location for the error message file somewhere
    else in the ECL.
  - <tt>@b clear</tt>\n
    Reset debug filters and statistics to initial values.

@b andmask is a bitmask expression consisting of symbolic names ("info",
"warn", "error", "assert", "base", "app", "all") or numeric constants 
(decimal "###", octal "0###" or hexadecimal "0x###" where "###" is any number of
valid digits) strictily connected from left to right with operators 
(addition "+", subtraction "-", or/bit-set "|", and "&", and-complement/bit-reset "&~", xor "^").

@b matchmask is like @a andmask with the additional symbol "any".

@b outmask is a bitmask expression similar to @a andmask with the symbols "cout", 
"cerr", "clog", "eout" representing specific devices. "elog", "elog1", 
"elog2", "elog3" are the different logfiles.
"all" selects all devices and logfiles. "nul" redirects output to nowhere. "remove" can be used
to remove a filter from the list.

@b Todo: @n
- Configurable output format (timestamp or not, file(date) or not).
- Optimization of output format (remove path up to /ecl/src).
- Some cBase::setXYZ() stuff not yet accessible with doConfig().
*/
bool cBase::doConfig(const char *config_string)
{
   return BASE_CORE().parseConfig(config_string);
}




// ===========================================================================
// ===========================================================================
// Das ist die DEADLINE - alles unterhalb ist vielleicht zum Tod verdammt.
// Alles oberhalb gilt als aufgeraumt und ueberabeitet und ueberlebt sicher.
// ===========================================================================
// ===========================================================================


#if (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0

static void PrintOut(char *buf)
{
   //if ( log_file != 0 )
   //   log_file->write(buf);
   
   if ( log_files[0] != 0 )
      log_files[0]->write(buf);

   ecl_print_func(buf);

   // LineWidth abgeschafft!
   //if ( LineWidth < 0 ) {
   //   print_func("%s\n", buf);
   //} else {
   //   char *ptr = buf;
   //   while ( (int)strlen(ptr) > LineWidth ) {
   //      char save = ptr[LineWidth-1]; ptr[LineWidth-1] = '\0';
   //      print_func("%s\n", ptr);
   //      ptr = &ptr[LineWidth-1]; *ptr = save;
   //   }
   //   if ( *ptr )
   //      print_func("%s\n", ptr);
   //}
}


static void PrintIt(const char *fmt, va_list ap)
{
   char buf[2048];

   // In den Puffer kommen die Datenmassen von draussen rein. Wenn er schon
   // mal zu mindestens 97.6% gefuellt wurde ist Gefahr eines Ueberlaufs so
   // gross, dass eine Fehlermeldung angebracht ist ... wahrscheinlich ist
   // das Kind dann sowieso schon im Brunnen, aber vielleicht kann man ja
   // noch irgendwo einen Hinweis auf die Fehlerursache lesen ...

   // Was um Himmels Willen hat mich nur geritten, als ich den Scheiss hier
   // verbrochen hab? Eigentlich muss man nur den Funktionswert von vsprintf
   // mit der Pufferlaenge vergleichen und man weiss, ob's geklappt hat :-(

   const unsigned long MAGIC = 0xDEADC0DE;
   *(unsigned long*)(buf + 2000) = MAGIC;

   old_print_flag = true;
   vsprintf(buf, fmt, ap);
   if (*(unsigned long*)(buf + 2000) != MAGIC) {
      // Der Text im Puffer wird 'versaut'
      strcpy(buf + 2000, "*cBase::Dbg overflow*");
   }
   PrintOut(buf);
   old_print_flag = false;

   // Mit einem assert wird versucht, auf das Problem aufmerksam zu machen
   __ECL_ASSERT__( *(unsigned long*)(buf + 2000) == MAGIC , CORE_ERROR );
}


static void PrintIt(const char *str)
{
   char buf[2048], *start = buf; //FormatTime(buf);
   strxcpy(start, str, sizeof buf - (start - buf));

   old_print_flag = true;
   PrintOut(buf);
   old_print_flag = false;
}




// Gemeinsamkeiten
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgVOut(unsigned long mask, const char *fmt, va_list ap)
{
   if ( !old_print_flag && ((debug_mask & mask) || mask == 0) ) {
      PrintIt(fmt, ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgOut(unsigned long mask, const char *fmt, ...)
{
   va_list ap;
   va_start(ap, fmt);
   DbgVOut(mask, fmt, ap);
   va_end(ap);
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters). Use a
//! debug mask with cBase::dbgError set.
void cBase::DbgError(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgError) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

bool cBase::DbgAssert1(const char *expr, const char *file, int line, char *factory_text)
{
   #ifdef __Use_Real_Assertion__
      if ( debug_mask & dbgAssert ) {
         #if __ECL_VCPP__ > 1300
/// PR 22.12.07
///            _assert(expr, file, line);
            _ASSERT(expr);
         #elif __ECL_VCPP__ >= 1200
            // VCPP Message-Box:
            // [Abbrechen]   -> _CrtDbgReport kehrt nicht zurueck
            // [Wiederholen] -> Rueckgabe 1 -> Ausfuehrung anhalten
            // [Ignorieren]  -> Rueckgabe 0 -> Fehlermeldung und weitermachen
            if ( _CrtDbgReport(_CRT_ASSERT, file, line, "ecl", (factory_text?"%s\nMessage: %s":"%s"), expr, factory_text) == 1 ) {
               _CrtDbgBreak();
            }
         #else
            assert(expr);
            //_assert((void*)expr, (void*)file, line);
         #endif
      }
   #endif

   #if defined __ECL_VCPP__
      // Formatiere gemaess VCPP-Fehlermeldungsformat (Visual-Studio: Doppelklick fuehrt zu Fehlerstelle)
      if (factory_text == 0) {
         return DbgAssert2("%s(%d) : ECL_ASSERT '%s' failed", file, line, expr);
      } else {
         DbgAssert2("%s(%d) : ECL_ASSERT '%s' failed : %s", file, line, expr, factory_text);
         delete[] factory_text;
         return false;
      }
   #else
      // "Normale" Formatierung
      if (factory_text == 0) {
         return DbgAssert2("Expression '%s' failed in module %s, line %d", expr, file, line);
      } else {
         DbgAssert2("Expression '%s' failed in module %s, line %d: %s", expr, file, line, factory_text);
         delete[] factory_text;
         return false;
      }
   #endif
}

bool cBase::DbgAssert2(const char *fmt, ...)
{
   if ( !old_print_flag ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }

   return false;
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters). Use a
//! debug mask with cBase::dbgInfo set.
void cBase::DbgInfo(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgInfo) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgTrcBase(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgTrcBase) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgTrcDb(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgTrcDb) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgTrcWin(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgTrcWin) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgTrcApp(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgTrcApp) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgBase(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgBase) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgDb(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgDb) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgWin(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgWin) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgSql(const char *sql)
{
   if ( !old_print_flag && (debug_mask & dbgSql) ) {
      PrintIt(sql);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgSqlRaw(const char *sql)
{
   if ( !old_print_flag && (debug_mask & dbgSqlRaw) ) {
      PrintIt(sql);
   }
}

//! Obsolete debug output, will be removed later. Don't use any more, 
//! please use new debug macros (which supply e.g. filters).
void cBase::DbgMsg(const char *fmt, ...)
{
   if ( !old_print_flag && (debug_mask & dbgMsg) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}


/* Wo zur Hoelle wird DbgPrint ueberhaupt verwendet ???
#if defined __ECL_OS2__ || defined __ECL_LINUX__
   #define PASCAL
#endif

extern "C" {
   void PASCAL DbgPrint(const char *fmt, ...)
   {
      va_list ap;
      va_start(ap, fmt);
      cBase::DbgVOut(0, fmt, ap);
      va_end(ap);
   }
};
*/

#endif // (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0




// ---------------------------------------------------------------------------
// Attribute lesen/setzen
// ---------------------------------------------------------------------------


// VERALTET - VERALTET - VERALTET - VERALTET - VERALTET - VERALTET - VERALTET
//
// getMask() ab jetzt lokal in base.cpp.
//
// Schmankerl: Bitmasken im Klartext aus einer Zeichenkette ermitteln.
//
// @verbatim
//    [ <bitmaske> { " " <bitmaske> } ]
//    <bitmaske> ::= ( <token> | <C-Zahl> ) [ "<" <dezimal-shift> ] @endverbatim
//
// - Die Tabelle ordnet Bitmustern ein Token mit max. 15 Zeichen zu.
// - (Teil-)Bitmasken durch !isalnum() getrennt, vorzugsweise ein Leerzeichen
// - fuer str=0 wird ein Default-Wert uebergeben
//- Sehr tolerant: versucht nach jedem Fehler neu aufzusetzen
//
static unsigned long getMask(const char *str, cBase::cCore::MASK_NAME *tab, unsigned long def)
{
   if (!str) {
      return def;
   }

   unsigned long mask = 0L, tok;
   char buf[16];
   char *ptr;
   while (*str) {
      while (isspace(*str)) { str++; }
      if (isdigit(*str)) {
         // Token ist eine Zahl
         tok = strtoul(str,&ptr,0);
         str = (const char *)ptr;
      } else {
         // Token in buf kopieren
         int i=0;
         ptr = (char*)str;
         while (isalnum(*ptr)) {
            buf[i<15 ? i++ : i] = *ptr++;
         };
         buf[i] = '\0';
         // Token aus buf in Tabelle suchen
         i=0;
         while (tab[i].name && cString::_stricmp(buf,tab[i].name)) {
            i++;
         }
         if (tab[i].name) {
            // Token gefunden
            tok = tab[i].mask;
            str = ptr;
         } else {
            // Kein Token gefunden oder Token nicht in der Liste ->
            // *ein* Zeichen ueberlesen -> alle !isalnum()-Zeichen koennen
            // somit Tokens trennen
            tok = 0;
            str++;
         }
      }
      // noch shiften?
      if (*str == '<' && isdigit(*(++str))) {
         mask = mask | (tok << strtol(str,&ptr,10));
         str = (const char *)ptr;
      } else {
         mask = mask | tok;
      }
   }
   return mask;
}


}; // namespace ecl





