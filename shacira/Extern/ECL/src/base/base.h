// ===========================================================================
// base/base.h                                                  ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase - zentrale Steuerklasse der ECL
//
//! @file  base/base.h
//! @brief Core functionality of the ECL
//
// Grundkonfiguration ueber Umgebungsvariablen:
//
//    -  ECL_DBG: Maske fuer Debug-Ausgaben, eine Liste aus den Tokens "Error",
//       "Info", "TrcBase", "TrcDb", "TrcWin", "TrcApp", "Base", "Db", "Win",
//       "Sql", "SqlRaw", "Msg", "Assert" und "User". Die Tokens koennen durch
//       Leerzeichen oder '+' getrennt werden (z.B. "error+assert"). Default
//       ist "Error".
//    -  ECL_LOG: Konfiguration der ECL-Logdatei, siehe cLogfile::setParam().
//    -  ECL_ERRMSG: Liste von Dateinamen (durch ';' getrennt) mit Fehler-
//       meldungstexten fuer das Error-Modul. Siehe cErrBase bzw. error.h.
//
// Generierter Code (hoechstens eines der Macros wird in base.h definiert,
// wird derzeit nur unter __ECL_VCPP__ unterstuetzt):
//    __ECL_MAKE_DLL__
//    __ECL_MAKE_LIB__
//    __ECL_MAKE_EXE__
//
// Generierter Code (dieses Macro ist *immer* definiert, ein Bezug darauf mit
// "#if defined __ECL_DEBUG__ > 0" ist daher immer "true" und damit Unsinn.
// Debug wird derzeit nur unter __ECL_VCPP__ automatisch unterstuetzt.)
//    __ECL_DEBUG__ (0 = Release, >0 = Debug)
//
// Compilerspezifische Einstellungen (alle Macros *müssen* fuer jeden
// Compiler definiert werden, auch wenn die Definition selbst "leer" ist)
//    __ECL_DLLEXPORT__
//    __ECL_OPEXP__
//    __ECL_EXP1__
//    __ECL_EXP2__
//    __ECL_THREADLNK__
//
// ===========================================================================


#ifndef __ecl_base__
#define __ecl_base__


// Standard headers
#include <cstdarg>




// Current Compiler / Target System
// ===========================================================================

#if defined __OS2__
   #define __ECL_OS2__
#elif defined _WIN32 || defined _WIN32
   #define __ECL_W32__
#elif defined __GNUC__
   #define __ECL_LINUX__   
#else
   #error "Unsupported target system for ECL"
#endif

#if defined __IBMCPP__
   #define __ECL_ICC__
#elif _MSC_VER >= 1100
   #define __ECL_VCPP__ _MSC_VER
#elif __BCPLUSPLUS__ >= 0x0540
   #define __ECL_BCPP__ __BCPLUSPLUS__
#elif defined __GNUC__
   #define __ECL_GNUC__
   #if defined __ECL_W32__
      #define __ECL_MINGW__
   #endif
#else
   #error "Unsupported compiler for ECL"
#endif

// Compiler switch to control debug functionality
#if !defined __ECL_DEBUG__
   #if defined __ECL_VCPP__
      #if defined _DEBUG
         #define __ECL_DEBUG__ 1
      #else
         #define __ECL_DEBUG__ 0
      #endif
   #else
      #define __ECL_DEBUG__ 0
   #endif
#endif

#define __ECL_DEBUG_ENABLE_STATISTIC__ 2
#define __ECL_DEBUG_FORCE_RECENT__     4


//
// Compiler specific settings
//
#if defined __ECL_ICC__

   #define __ECL_DLLEXPORT__        _Export
   #define __ECL_OPEXP__            /* empty */
   #define __ECL_EXP1__             /* empty */
   #define __ECL_EXP2__             _Export
   #define __ECL_THREADLNK__        _Optlink

   #define dbg_new(s,f,l)           ::operator new(s)
   #define dbg_delete(p,f,l)        ::operator delete(p)

   //Wenn ueberhaupt, maximal eines der folgenden Macros definieren!
   //#define __ECL_MAKE_DLL__         /* TBD: ??? */
   //#define __ECL_MAKE_LIB__         /* TBD: ??? */
   //#define __ECL_MAKE_EXE__         /* TBD: ??? */

   // Typ bool, Gestaltung konform mit ANSI-C++-Typ bool.
   enum { false = 0, true = 1 };
   #define bool int

#elif defined __ECL_VCPP__

   #pragma warning(disable:4514) /* Nichtreferenzierte Inline-Funktion wurde entfernt */
   #pragma warning(disable:4710) /* Funktion ist keine Inline-Funktion */
   #pragma warning(disable:4786) /* Bezeichner auf 255 Zeichen begrenzt in Debug-Information */

   #if __ECL_VCPP__ < 1200
      #pragma warning(disable:4201) /* Nicht dem Standard entsprechende Erweiterungen */
   #endif

   #define __ECL_EXP2__             /* empty */
   #define __ECL_THREADLNK__        __cdecl

   #if __ECL_DEBUG__ > 0 && _MSC_VER >= 1200 && _MSC_VER < 1300
      #include <crtdbg.h>
      #define dbg_new(s,f,l)        ::operator new(s, _NORMAL_BLOCK, f, l)
      #define dbg_delete(p,f,l)     ::operator delete(p, _NORMAL_BLOCK, f, l)
      inline void *operator new(size_t size, int line, const char *file)
         { return dbg_new(size, file, line); }
      inline void operator delete(void *ptr, int line, const char *file)
         { dbg_delete(ptr, file, line); }
   #else
      #define dbg_new(s,f,l)        ::operator new(s)
      #define dbg_delete(p,f,l)     ::operator delete(p)
   #endif

   #if defined _USRDLL
      #define __ECL_MAKE_DLL__
      #define __ECL_DLLEXPORT__        __declspec(dllexport)
      #define __ECL_OPEXP__            __declspec(dllexport)
      #define __ECL_EXP1__             __declspec(dllexport)
   #else
      #define __ECL_DLLEXPORT__
      #define __ECL_OPEXP__
      #define __ECL_EXP1__
      #if defined _LIB
         #define __ECL_MAKE_LIB__
      #else
         #define __ECL_MAKE_EXE__
      #endif
   #endif

#elif defined __ECL_BCPP__

   #define __ECL_DLLEXPORT__        /* empty */
   #define __ECL_OPEXP__            /* empty */
   #define __ECL_EXP1__             /* empty */
   #define __ECL_EXP2__             /* empty */
   #define __ECL_THREADLNK__        __cdecl

   #define dbg_new(s,f,l)           ::operator new(s)
   #define dbg_delete(p,f,l)        ::operator delete(p)

   //Wenn ueberhaupt, maximal eines der folgenden Macros definieren!
   //#define __ECL_MAKE_DLL__         /* TBD: ??? */
   //#define __ECL_MAKE_LIB__         /* TBD: ??? */
   //#define __ECL_MAKE_EXE__         /* TBD: ??? */

#elif defined __ECL_GNUC__

// PR GNUC
   #if defined _WIN32
      // same as under __ECL_VCPP__
      #define __ECL_EXP2__             /* empty */
      #define __ECL_THREADLNK__        __cdecl

      #if __ECL_DEBUG__ > 0 && _MSC_VER >= 1200 && _MSC_VER < 1300
         #include <crtdbg.h>
         #define dbg_new(s,f,l)        ::operator new(s, _NORMAL_BLOCK, f, l)
         #define dbg_delete(p,f,l)     ::operator delete(p, _NORMAL_BLOCK, f, l)
         inline void *operator new(size_t size, int line, const char *file)
            { return dbg_new(size, file, line); }
         inline void operator delete(void *ptr, int line, const char *file)
            { dbg_delete(ptr, file, line); }
      #else
         #define dbg_new(s,f,l)        ::operator new(s)
         #define dbg_delete(p,f,l)     ::operator delete(p)
      #endif

      #if defined _USRDLL
         #define __ECL_MAKE_DLL__
         #define __ECL_DLLEXPORT__        __declspec(dllexport)
         #define __ECL_OPEXP__            __declspec(dllexport)
         #define __ECL_EXP1__             __declspec(dllexport)
      #else
         #define __ECL_DLLEXPORT__
         #define __ECL_OPEXP__
         #define __ECL_EXP1__
         #if defined _LIB
            #define __ECL_MAKE_LIB__
         #else
            #define __ECL_MAKE_EXE__
         #endif
      #endif
   #else
      // Use pthread library on Linux
      #define __ECL_PTHREADS__
   
      #define __ECL_DLLEXPORT__        /* empty */
      #define __ECL_OPEXP__            /* empty */
      #define __ECL_EXP1__             /* empty */
      #define __ECL_EXP2__             /* empty */
      #define __ECL_THREADLNK__

      #define dbg_new(s,f,l)           ::operator new(s)
      #define dbg_delete(p,f,l)        ::operator delete(p)

      //Wenn ueberhaupt, maximal eines der folgenden Macros definieren!
      //#define __ECL_MAKE_DLL__         /* TBD: ??? */
      //#define __ECL_MAKE_LIB__         /* TBD: ??? */
      //#define __ECL_MAKE_EXE__         /* TBD: ??? */
      #endif
      #ifndef stricmp
      #define stricmp strcasecmp
      #endif
      #ifndef strnicmp
      #define strnicmp strncasecmp
      #endif
      #include <pthread.h>
// PR GNUC

#endif




// Dynamic Memory Allocation
// ===========================================================================

#if __ECL_DEBUG__ > 0 && __ECL_VCPP__ >= 1200 && __ECL_VCPP__ < 1300
   #define op_new0(s)            new(s, int line, const char *file)
   #define op_new1(s,p1)         new(s, p1, int line, const char *file)
   #define op_new2(s,p1,p2)      new(s, p1, p2, int line, const char *file)
   #define op_delete0(p)         delete(p, int line, const char *file)
   #define op_delete1(p,p1)      delete(p, p1, int line, const char *file)
   #define op_delete2(p,p1,p2)   delete(p, p1, p2, int line, const char *file)
   #define new0                  new(__LINE__, __FILE__)
   #define new1(p1)              new(p1, __LINE__, __FILE__)
   #define new2(p1,p2)           new(p1, p2, __LINE__, __FILE__)
#else
   #define op_new0(s)            new(s)
   #define op_new1(s,p1)         new(s, p1)
   #define op_new2(s,p1,p2)      new(s, p1, p2)
   #define op_delete0(p)         delete(p)
   #define op_delete1(p,p1)      delete(p, p1)
   #define op_delete2(p,p1,p2)   delete(p, p1, p2)
   #define new0                  new
   #define new1(p1)              new(p1)
   #define new2(p1,p2)           new(p1, p2)
#endif




// Utility Macros
// ===========================================================================

// Bisherige Assertion-Macros
// ---------------------------------------------------------------------------

#if (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0
   // Assertion (nur Bedingung)
   // Liefert false im Fehlerfall
   #if __ECL_DEBUG__ > 0
      #define __ECL_ASSERT1__(c) \
         ( (c) ? true : ecl::cBase::DbgAssert1(#c, __FILE__, __LINE__) )
   #else
      #define __ECL_ASSERT1__(c) \
         (c)
   #endif

   // Assertion (Bedingung + Meldung)
   // Liefert false im Fehlerfall
   #if __ECL_DEBUG__ > 0
      #define __ECL_ASSERT2__(c,p) \
         ( (c) ? true : ecl::cBase::DbgAssert1(#c, __FILE__, __LINE__, ecl::cBase::DbgFormatFactory p ) )
   #else
      #define __ECL_ASSERT2__(c,p) \
         (c)
   #endif
#endif


// Neue Assertion-Macros
// ---------------------------------------------------------------------------

#if __ECL_DEBUG__ > 0
   // Annahme 'cond' ueberpruefen: liefert true wenn sie erfuellt ist (ok),
   // liefert false wenn nicht (Fehlerausgabe erfolgt)
   #define __ECL_ASSERT__(cond, mask) \
      ( (cond) ? true : ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, #cond) )

   // Annahme 'cond' ueberpruefen: liefert true wenn sie erfuellt ist (ok),
   // liefert false wenn nicht (Fehlerausgabe erfolgt mit Zusatztext in prnf.
   // prnf ist eine printf-Parameterliste der Form '("fmtstring",...)' wobei
   // die Klammern im Macro-Parameter immer angegeben werden muessen!)
   #define __ECL_ASSERT_PRINTF__(cond, mask, prnf) \
      ( (cond) ? true : ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, #cond, ecl::cBase::DbgFormatFactory prnf) )

   // Statement wird nur in der Debug-Version ausgefuehrt
   #define __ECL_IFDEBUG__(stmt) stmt;
   
   // Textausgabe in Debug-Version abhaengig von mask (Stringkonstanten)
   #define __ECL_DEBUG_TEXT__(mask, const_text) ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, const_text, 0 );
   
   // Textausgabe in Debug-Version abhaengig von mask (printf-formatierter Text)
   #define __ECL_DEBUG_PRINTF__(mask, prnf) ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, 0, ecl::cBase::DbgFormatFactory prnf );

   // Debug-Booster: Statistic counter
   #if __ECL_DEBUG__ & __ECL_DEBUG_ENABLE_STATISTIC__
      #define __ECL_STATISTIC__(label) ecl::cBase::DbgStatistic(label);
      //#define __ECL_STATISTIC_MIN__(label,value) ecl::cBase::DbgStatistic(label,-2,value);
      //#define __ECL_STATISTIC_MAX__(label,value) ecl::cBase::DbgStatistic(label,2,value);
   #else
      #define __ECL_STATISTIC__(label)
      //#define __ECL_STATISTIC_MIN__(label,value)
      //#define __ECL_STATISTIC_MAX__(label,value)
   #endif

#else
   #define __ECL_ASSERT__(cond, mask) (cond)
   #define __ECL_ASSERT_PRINTF__(cond, mask, printf) (cond)
   #define __ECL_IFDEBUG__(stmt)
   #define __ECL_DEBUG_TEXT__(mask, const_text)
   #define __ECL_DEBUG_PRINTF__(mask, prnf)
   #define __ECL_STATISTIC__(label)
   //#define __ECL_STATISTIC_MIN__(label,value)
   //#define __ECL_STATISTIC_MAX__(label,value)
#endif

// Textausgabe in Debug- und Release-Version abhaengig von mask (Stringkonstanten)
#define __ECL_RELEASE_TEXT__(mask, const_text) ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, const_text, 0 );

// Textausgabe in Debug- und Release-Version abhaengig von mask (printf-formatierter Text)
#define __ECL_RELEASE_PRINTF__(mask, prnf) ecl::cBase::DbgMessage( mask, __FILE__, __LINE__, 0, ecl::cBase::DbgFormatFactory prnf );




// Sonstige Macros
// ---------------------------------------------------------------------------

// TBD: MakeHead ist nicht mehr zeitgemaess -> GLOBAL rauswerfen!
// - base\geo2d.cpp scheint das einzige ECL-Modul wo's noch vorkommt,
//   bei der Gelegenheit koennte man dieses mit CPPUNIT testen!
// - In WinFBS wird das Macro (wahrscheinlich) nur in 9 Dateien verwendet
//
//! Deprecated macro for MakeHead. Remove where you meet it!
#define GLOBAL


// Utility Macros / Templates
// ===========================================================================

#if defined max
   #undef max
#endif

#if defined __ECL_ICC__
   #define max(a,b) (((a) > (b)) ? (a) : (b))
#else
   template<class T> inline T max(T a, T b)
      { return (a > b) ? a : b; }
#endif

#if defined min
   #undef min
#endif

#if defined __ECL_ICC__
   #define min(a,b) (((a) < (b)) ? (a) : (b))
#else
   template<class T> inline T min(T a, T b)
      { return (a < b) ? a : b; }
#endif


// Utility Functions
// ===========================================================================

inline const char *Nvl(const char *s, const char *r)
   { return s ? s : r; }

inline const char *Evl(const char *s, const char *r)
   { return s ? (*s ? s : r) : r; }




namespace ecl {

// ===========================================================================
// Definition cBase
// ===========================================================================

class __ECL_DLLEXPORT__ cBase {

public:
   //! Datatype for user defined print function that is used as debug output
   //! device "eout". @a text should not end with '\\n',
   //! this must be added by the print function, the default implementation is
   //! <tt>fprintf(stderr, "%s\\n", text)</tt>.
   typedef void (*PRINT_FUNC)(const char *text);
   //! @a Obsolete. Datatype for user defined print function with variable
   //! argument list that is used as debug output device "eout". Use of
   //! these old style print functions will cause a warning. This type
   //! is provided for compatibility and may be removed at a later moment.
   typedef int (*OLD_PRINT_FUNC)(const char * fmt, ... );

   //! Constants to code a debug mask (concat with the operator |).
   enum DEBUG_MASK {
      // Meldungsklassen
      dbgInfo     = 0x00000001,     //!< Information
      dbgWarn     = 0x00000002,     //!< Warning
      dbgError    = 0x00000004,     //!< Errors
      dbgAssert   = 0x00000008,     //!< Assert (qualifier for errors)
      // Modulbereiche
      dbgCore     = 0x00000010,     //!< Core class related
      dbgBase     = 0x00000020,     //!< Base class related
      dbgApp      = 0x00000040,     //!< Application class related
      dbgIpc      = 0x00000080,     //!< Inter process communication
      // Spezialbits
      dbgAny      = 0x04000000,     //!< Special bit in debug filter
      // Kompatibilitaetsbits
      dbgTrcDb    = 0x00010000,     //!< Trace: Methoden der Datenbankklassen
      dbgTrcWin   = 0x00020000,     //!< Trace: Methoden der Windowklassen
      dbgTrcApp   = 0x00040000,     //!< Trace: Methoden der Anwendungsklassen
      dbgTrcBase  = 0x00080000,     //!< Trace: Methoden der Basisklassen
      dbgDb       = 0x00100000,     //!< Datenbankklassen-Spezifisches
      dbgWin      = 0x00200000,     //!< Windowklassen-Spezifisches
      dbgSql      = 0x00400000,     //!< Alle SQL-Befehle
      dbgSqlRaw   = 0x00800000,     //!< SQL-Befehle im DB-spezifischen Format
      dbgMsg      = 0x01000000,     //!< Meldungs-Spezifisches
      // Deprecated: dbgUser wird aber noch in der Tomate verwendet
      // Es gibt maximal noch 4 (!) benutzerdefinierbare Bits !!!
      dbgUser     = 0x10000000      //!< Frei fuer Benutzer
   };

   //! Bitmask to control debug output location
   enum OUTPUT_MASK {
      outCOut     = 0x00000001,  //!< std::cout
      outCErr     = 0x00000002,  //!< std::cerr
      outCLog     = 0x00000004,  //!< std::clog
      outEOut     = 0x00000008,  //!< ecl print function that has been configured
                                 //!< with setPrintFunc().
      outELog     = 0x00000010,  //!< ecl logfile that has been configured with setLogfile().
      maskELog    = 0x000000F0,  //   Mask for logfiles #0 to #7
      outNul      = 0x40000000,  //!< no device selected
      outAssert   = 0x80000000,  //!< generate "real" assert()
   };

   // Die Formatierung erfolgt in einen mit new char[] belegten Puffer !!!
   static char *DbgFormatFactory(const char *fmt, ...);
   // Neue Debug/Assert-Funktion (liefert immer false, macht ein "delete[] dynamic_text")
   static bool DbgMessage(unsigned long mask, const char *file, int line, const char *static_text=0, char *dynamic_text=0);
   // Die letzte mit DbgMessage() ausgegebene Meldung.
   static const char *getLastMessage();
   
   // Konfiguration der (neuen) Debug-Ausgabefunktion
   static void setPrintFunc(PRINT_FUNC _printf = 0);

   // Neue Statistik-Funktion. Falls aktiviert koennen beliebige, durch
   // einen Namen identifizierte Ereignisse zentral gezaehlt werden.
   // Einsatz: in __ECL_STATISTIC__ gekapselt werden Konstruktoraufrufe der ECL-Klassen gezaehlt
   static long DbgStatistic(const char *label, int what=1, long value=0);

   //! If an automatic memory leak detection is available, it can be activated
   //! with this method. Up to now this feature is supported only for Visual Studio.
   static void setMemoryLeakDetect(bool enable);


   #if (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0
      // Nach der Ausgbe wird factory_text mit delete[] wieder freigegeben !!!
      //! Obsolete implementation of __ECL_ASSERT1__ (if factory_text is 0) and __ECL_ASSERT2__
      //! (if factory_text generated with DbgFormatFactory()).
      static bool DbgAssert1(const char *expr, const char *file, int line, char *factory_text=0);
      //! Very obsolete implementation of __ECL_ASSERT2__.
      static bool DbgAssert2(const char *fmt, ...);

      static void DbgOut(unsigned long mask, const char *fmt, ...);
      static void DbgVOut(unsigned long mask, const char *fmt, va_list ap);
      static void DbgError(const char *fmt, ...);
      static void DbgInfo(const char *fmt, ...);
      static void DbgTrcBase(const char *fmt, ...);
      static void DbgTrcDb(const char *fmt, ...);
      static void DbgTrcWin(const char *fmt, ...);
      static void DbgTrcApp(const char *fmt, ...);
      static void DbgBase(const char *fmt, ...);
      static void DbgDb(const char *fmt, ...);
      static void DbgWin(const char *fmt, ...);
      static void DbgSql(const char *sql);
      static void DbgSqlRaw(const char *sql);
      static void DbgMsg(const char *fmt, ...);

      static void setDebugMask(unsigned long mask);
      static void setDebugMask(const char *str);
      static unsigned long getDebugMask();

      static void setPrintFunc(OLD_PRINT_FUNC _printf);
   #endif // (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__) == 0

   static void setLogfile(const char *fname, bool append = true);
   static void setLogfileDimension(int max_gen, long max_size);

public:
   //! Execute ecl configuration command.
   static bool doConfig(const char *config_string);

   // eingebettete Hilfsklassen
   class cCore;      // versteckte Kernfunktionalitaeten
   class cFilter;    // Detailiertere Debug-Ausgabefilter
   class cStatistic; // Zeug zur Konstruktoraufrufszaehlung
   class cParser;    // Krimskramsparser (Prototyp)
   class cCritical;  // Critical section protection
   class cCriticalGuard;

   // Langfristig soll cBase keine Basisklasse fuer irgendwas mehr sein.
   // Hier wird probehalber ein PRIVATER DEFAULTKONSTRUKTOR definiert,
   // um etwaige, historisch bedingte Ableitungen aufzuspüren.
   #if (__ECL_DEBUG__ & __ECL_DEBUG_FORCE_RECENT__)
      private: cBase();
   #endif

}; // cBase


}; // namespace ecl


// Diese Bits sind nur innerhalb von base.h gueltig! 
// (in base.cpp auch, aber da werden sie noch einmal definiert) 
#undef __ECL_DEBUG_ENABLE_STATISTIC__
#undef __ECL_DEBUG_FORCE_RECENT__


#endif //__ecl_base__

