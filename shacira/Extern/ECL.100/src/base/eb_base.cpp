// ===========================================================================
// eb_base.cpp                                                  ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase                   - Basis aller Klassen.
//     |
//     +-cData                - Basisklasse fuer anonyme Daten.
//
// Grundkonfiguration ueber Umgebungsvariablen:
//
//    - ECL_DBG: Defaultwert der Maske fuer Debug-Ausgaben [0]
//    - ECL_LEN: Ausgabelaenge einer Zeile im Debug-Modus [132]
//
// ===========================================================================

#include "base/eb_base.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <io.h>                                  /* unlink()               */
#include <sys/stat.h>                            /* stat(), fstat()        */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stdarg.h>
#include <ctype.h>

#if defined __ECL_W32__
   #include <windows.h>
   #include <time.h>
#endif

#if defined __ECL_DEBUG__ > 0 && _MSC_VER >= 1200
   #include <crtdbg.h>
#endif

#if __ECL_DEBUG__ > 0
   #define __Use_Real_Assertion__
   #ifdef __Use_Real_Assertion__
      #include <assert.h>
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ==========================================================================

#if _MSC_VER >= 1300
   #if defined ECL_DLL_WIN_EXPORTS
      #pragma warning(disable:4995) /* name was marked as #pragma deprecated */
      #include <iostream.h>
   #else
      #include <iostream>
      using std::istream;
      using std::ostream;
      using std::cin;
      using std::cout;
      using std::cerr;
      using std::endl;
   #endif
#else
   #include <iostream.h>
#endif

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


// Current Compiler / Target System
// ===========================================================================

#if defined __OS2__
   #define __ECL_OS2__
#elif defined _WIN32 || defined __WIN32__
   #define __ECL_W32__
#else
   #error "Unsupported target system for ECL"
#endif

#if defined __IBMCPP__
   #define __ECL_ICC__
#elif _MSC_VER >= 1100
   #define __ECL_VCPP__ _MSC_VER
#elif __BCPLUSPLUS__ >= 0x0540
   #define __ECL_BCPP__ __BCPLUSPLUS__
#else
   #error "Unsupported compiler for ECL"
#endif

#if !defined __ECL_DEBUG__
   #if defined __ECL_VCPP__
      #if defined _DEBUG
         #define __ECL_DEBUG__ 1
      #else
         #define __ECL_DEBUG__ 0
      #endif
   #else
      #define __ECL_DEBUG__ 0    /* 0 = Release, 1 = Debug */
   #endif
#endif

#if defined __ECL_ICC__

   #define __ECL_DLLEXPORT__        _Export
   #define __ECL_OPEXP__            /* empty */
   #define __ECL_EXP1__             /* empty */
   #define __ECL_EXP2__             _Export
   #define __ECL_THREADLNK__        _Optlink
   #define __ECL_SHOW_LEAKS__()     /* TBD: ??? */

   #define dbg_new(s,f,l)           ::operator new(s)
   #define dbg_delete(p,f,l)        ::operator delete(p)

   #define __ECL_MAKE_DLL__         /* TBD: ??? */
   #define __ECL_MAKE_LIB__         /* TBD: ??? */
   #define __ECL_MAKE_EXE__         /* TBD: ??? */

#elif defined __ECL_VCPP__

   #pragma warning(disable:4514) /* Nichtreferenzierte Inline-Funktion wurde entfernt */
   #pragma warning(disable:4710) /* Funktion ist keine Inline-Funktion */
   #pragma warning(disable:4786) /* Bezeichner auf 255 Zeichen begrenzt in Debug-Information */

   #if __ECL_VCPP__ < 1200
      #pragma warning(disable:4201) /* Nicht dem Standard entsprechende Erweiterungen */
   #endif

   #define __ECL_EXP2__             /* empty */
   #define __ECL_THREADLNK__        __cdecl

   #if defined __ECL_DEBUG__ > 0 && _MSC_VER >= 1200 && _MSC_VER < 1300
      #include <crtdbg.h>
      #define __ECL_SHOW_LEAKS__()     _CrtDumpMemoryLeaks()
      #define dbg_new(s,f,l)        ::operator new(s, _NORMAL_BLOCK, f, l)
      #define dbg_delete(p,f,l)     ::operator delete(p, _NORMAL_BLOCK, f, l)
      inline void *operator new(size_t size, int line, const char *file)
         { return dbg_new(size, file, line); }
      inline void operator delete(void *ptr, int line, const char *file)
         { dbg_delete(ptr, file, line); }
   #else
      #define __ECL_SHOW_LEAKS__()
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
   #define __ECL_SHOW_LEAKS__()     /* TBD: ??? */

   #define dbg_new(s,f,l)           ::operator new(s)
   #define dbg_delete(p,f,l)        ::operator delete(p)

   #define __ECL_MAKE_DLL__         /* TBD: ??? */
   #define __ECL_MAKE_LIB__         /* TBD: ??? */
   #define __ECL_MAKE_EXE__         /* TBD: ??? */

#endif

#if defined __ECL_DEBUG__ == 0
   #undef __ECL_SHOW_LEAKS__
   #define __ECL_SHOW_LEAKS__()  /* empty */
#endif


// Dynamic Memory Allocation
// ===========================================================================

#if defined __ECL_DEBUG__ > 0 && __ECL_VCPP__ >= 1200 && __ECL_VCPP__ < 1300
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

// Assertion (nur Bedingung)
// Liefert false im Fehlerfall
#if __ECL_DEBUG__ > 0
   #define __ECL_ASSERT1__(c) \
      ( (c) ? true : cBase::DbgAssert1(#c, __FILE__, __LINE__) )
#else
   #define __ECL_ASSERT1__(c) \
      (c)
#endif

// Assertion (Bedingung + Meldung)
// Liefert false im Fehlerfall
#if __ECL_DEBUG__ > 0
   #define __ECL_ASSERT2__(c,p) \
      ( __ECL_ASSERT1__(c) ? true : cBase::DbgAssert2 p )
#else
   #define __ECL_ASSERT2__(c,p) \
      (c)
#endif

#if defined __ECL_ICC__
   // Typ bool, Gestaltung konform mit ANSI-C++-Typ bool.
   enum { false = 0, true = 1 };
   #define bool int
#endif

// Typ EBHDL, muss long und Pointer aufnehmen koennen
typedef unsigned long EBHDL;

// Speziell fuer MakeHead
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

inline char * strxcpy(char *s1, const char *s2, size_t len)
   { strncpy(s1, s2, len); s1[len-1] = '\0'; return s1; }

inline char * strpadcpy(char *s1, const char *s2, size_t len)
   { for ( char *s = s1 ; len-- ; s++ ) if ( *s2 ) *s = *s2++; else *s = ' '; return s1; }

inline const char *Nvl(const char *s, const char *r)
   { return s ? s : r; }

inline const char *Evl(const char *s, const char *r)
   { return s ? (*s ? s : r) : r; }

inline char *rtrim(char *s)
   { for ( char *p=s+strlen(s) ; p>s && *(p-1)==' ' ; ) *(--p) = '\0'; return s; }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cBase
// ---------------------------------------------------------------------------
//
// Die Basis aller Klassen.
//
// cBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cBase {

public:
   typedef int (*PRINT_FUNC)(const char * fmt, ... );

   struct MASK_NAME {
      unsigned long mask;
      const char *name;
   };

   enum DBG_MASK {
      dbgError    = 0x00000001,     // Fehlermeldungen
      dbgInfo     = 0x00000002,     // Allgemeine Infos
      dbgTrcBase  = 0x00000004,     // Trace: Methoden der Basisklassen
      dbgTrcDb    = 0x00000008,     // Trace: Methoden der Datenbankklassen
      dbgTrcWin   = 0x00000010,     // Trace: Methoden der Windowklassen
      dbgTrcApp   = 0x00000200,     // Trace: Methoden der Anwendungsklassen
      dbgBase     = 0x00000020,     // Basisklassen-Spezifisches
      dbgDb       = 0x00000040,     // Datenbankklassen-Spezifisches
      dbgWin      = 0x00000080,     // Windowklassen-Spezifisches
      dbgSql      = 0x00000100,     // Alle SQL-Befehle
      dbgSqlRaw   = 0x00000800,     // SQL-Befehle im DB-spezifischen Format
      dbgMsg      = 0x00000400,     // Meldungs-Spezifisches
      dbgAssert   = 0x00008000,     // ECL-Assertions "weiterwerfen"
      dbgUser     = 0x00010000      // Frei fuer Benutzer
   };

   static void DbgOut(unsigned long mask, const char *fmt, ...);
   static void DbgVOut(unsigned long mask, const char *fmt, va_list ap);
   static void DbgError(const char *fmt, ...);
   static bool DbgAssert1(const char *expr, const char *file, int line);
   static bool DbgAssert2(const char *fmt, ...);
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

   static void setPrintFunc(PRINT_FUNC _printf);
   static void setLogfile(const char *fname, bool append = true);
   static void setLogfileDimension(int max_gen, long max_size);

   static void setDebugWindow(EBHDL hwnd = NULL);
   static void paintDebugWindow();

   static unsigned long getMask(const char *string, MASK_NAME *tab, unsigned long def);
};

#endif /*__INTERFACE__*/


// Implementierung cBase
// ===========================================================================

// Klartextnamen fuer die Debug-Maske
static cBase::MASK_NAME dbg_mask_name[] = {
   {cBase::dbgError  , "Error"  },
   {cBase::dbgInfo   , "Info"   },
   {cBase::dbgTrcBase, "TrcBase"},
   {cBase::dbgTrcDb  , "TrcDb"  },
   {cBase::dbgTrcWin , "TrcWin" },
   {cBase::dbgTrcApp , "TrcApp" },
   {cBase::dbgBase   , "Base"   },
   {cBase::dbgDb     , "Db"     },
   {cBase::dbgWin    , "Win"    },
   {cBase::dbgSql    , "Sql"    },
   {cBase::dbgSqlRaw , "SqlRaw" },
   {cBase::dbgMsg    , "Msg"    },
   {cBase::dbgAssert , "Assert" },
   {cBase::dbgUser   , "User"   },
   {0L                , NULL     }   // NULL markiert das Tabellenende
};

#if __ECL_DEBUG__ > 0 && (defined __ECL_MAKE_DLL__ || defined __ECL_MAKE_LIB__)
   // Automatisch Memory-Leaks anzeigen
   class __ECL_cAutoLeakReport__ {
   public:
   #if defined __ECL_W32__ && __ECL_VCPP__ >= 1200
      __ECL_cAutoLeakReport__()
         { _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF); }
   #else
      ~__ECL_cAutoLeakReport__()
         { __ECL_SHOW_LEAKS__(); }
   #endif
   } __ECL_AutoLeakReport__;
#endif

// cBase::debug mit Wert der Umgebungsvariablen ECL_DBG initialisieren
unsigned long debug = cBase::getMask(getenv("ECL_DBG"),
                                     dbg_mask_name,cBase::dbgError);

// LineWidth mit Wert der Umgebungsvariablen ECL_LEN initialisieren
// 11.03.2002 -TE- Neu: Bei LineWidth < 0 werden Zeilen nicht zerstueckelt
static char *BaseLen = getenv("ECL_LEN");
static int LineWidth = BaseLen ? atoi(BaseLen) : -1;

static int print_flag = false;

// Logfile
static cLogfile log_file;
static bool log_file_active = false;

#if defined __ECL_W16__

// Windows-Spezifika
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


static const int MaxLines = 42;
static char TextBuf[MaxLines][132/*LineWidth*/+32];
static const char Heading[] = "DATE      TIME      MESSAGE";

static HWND DebugHwnd = NULL;
static int LineCount = 0;

static int Printf(const char *, ...)
{
   // unbenutzt...
   return 0;
}

static cBase::PRINT_FUNC PrintFunc = (cBase::PRINT_FUNC) Printf;

static void PrintOut(const char *line, bool with_time)
{
   if ( LineCount < MaxLines )
      LineCount++;

   for ( int l=LineCount-2 ; l>=0 ; l-- )
      strcpy(TextBuf[l+1], TextBuf[l]);

   if ( with_time ) {
      time_t lntime; time(&lntime);
      struct tm *tmtime = localtime(&lntime);
      sprintf(TextBuf[0], "%02d.%02d.%02d %02d:%02d:%02d %s",
         tmtime->tm_mday, tmtime->tm_mon + 1, tmtime->tm_year,
         tmtime->tm_hour, tmtime->tm_min, tmtime->tm_sec,
         line);
   } else {
      sprintf(TextBuf[0], "                 +%s", line);
   }

   if (log_file_active) log_file.write(TextBuf[0]);

   // String von IBM-PC-Zeichensatz nach Windows-ANSI konvertieren
   OemToAnsi((LPSTR)TextBuf[0], (LPSTR)TextBuf[0]);

   // Gesamten Clientbereich updaten
   InvalidateRect(DebugHwnd, NULL, true);
}

static void PrintIt(const char *fmt, va_list ap)
{
   char buf[2048], *ptr = buf;
   bool with_time = true;

   print_flag = true;

   vsprintf(buf, fmt, ap);

   while ( strlen(ptr) > LineWidth ) {
      char save = ptr[LineWidth-1]; ptr[LineWidth-1] = '\0';
      PrintOut(ptr, with_time); with_time = false;
      ptr = &ptr[LineWidth-1]; *ptr = save;
   }

   if ( *ptr )
      PrintOut(ptr, with_time);

   print_flag = false;
}

static void PrintIt(const char *str)
{
   char buf[2048], *ptr = buf;
   bool with_time = true;

   print_flag = true;

   strxcpy(buf, str, sizeof buf);

   while ( strlen(ptr) > LineWidth ) {
      char save = ptr[LineWidth-1]; ptr[LineWidth-1] = '\0';
      PrintOut(ptr, with_time); with_time = false;
      ptr = &ptr[LineWidth-1]; *ptr = save;
   }

   if ( *ptr )
      PrintOut(ptr, with_time);

   print_flag = false;
}

void cBase::setDebugWindow(EBHDL hwnd)
{
   DebugHwnd = (HWND)hwnd;
}

void cBase::paintDebugWindow()
{
   if ( debug ) {
      PAINTSTRUCT paint;
      HDC hdc = BeginPaint(DebugHwnd, &paint);

      TEXTMETRIC tm;
      int height = GetTextMetrics(hdc, &tm) ? tm.tmHeight : 10;

      TextOut(hdc, 0, 0, Heading, lstrlen(Heading));

      for ( int l=0 ; l<LineCount ; l++)
         TextOut(hdc, 0, height * (l+1), TextBuf[l], strlen(TextBuf[l]));

      EndPaint(DebugHwnd, &paint);
   }
}

#else

// Normale Betriebssysteme
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static int Printf(const char *fmt, ...)
{
   int num;
   va_list ap;

   va_start(ap, fmt);
   num = vfprintf(stderr, fmt, ap);
   va_end(ap);

   return num;
}

static cBase::PRINT_FUNC PrintFunc = (cBase::PRINT_FUNC) Printf;

static char *FormatTime(char *buf)
{
   bool show_timestamp = true; // TBD: Konfigurierbar!!!

   if ( show_timestamp ) {
      time_t lntime; time(&lntime);
      struct tm *tmtime = localtime(&lntime);
      sprintf(buf, "%02d.%02d.%04d %02d:%02d:%02d ",
         tmtime->tm_mday, tmtime->tm_mon + 1, 1900 + tmtime->tm_year,
         tmtime->tm_hour, tmtime->tm_min, tmtime->tm_sec);
   } else {
      *buf = '\0';
   }

   return buf + strlen(buf);
}

static void PrintOut(char *buf)
{
	if ( log_file.getFile() != 0 )
	   log_file.write(buf);

   if ( LineWidth < 0 ) {
      PrintFunc("%s\n", buf);
   } else {
      char *ptr = buf;

      while ( (int)strlen(ptr) > LineWidth ) {
         char save = ptr[LineWidth-1]; ptr[LineWidth-1] = '\0';
         PrintFunc("%s\n", ptr);
         ptr = &ptr[LineWidth-1]; *ptr = save;
      }

      if ( *ptr )
         PrintFunc("%s\n", ptr);
   }
}

static void PrintIt(const char *fmt, va_list ap)
{
   char buf[2048];

   print_flag = true;
   vsprintf(FormatTime(buf), fmt, ap);
   PrintOut(buf);
   print_flag = false;
}

static void PrintIt(const char *str)
{
   char buf[2048];

   print_flag = true;
   strxcpy(FormatTime(buf), str, sizeof buf);
   PrintOut(buf);
   print_flag = false;
}

#if defined __ECL_W32__

   static const int MaxLines = 42;
   static const int MaxLineLen = 132;
   static char TextBuf[MaxLines][MaxLineLen+32];
   static const char Heading[] = "DATE         TIME      MESSAGE";

   static HWND DebugHwnd = NULL;
   static int LineCount = 0;

   static int DrawText(const char *fmt, ...)
   {
      int num;
      char line[1024];
      va_list ap;

      va_start(ap, fmt);
      num = vsprintf(line, fmt, ap);
      va_end(ap);

      if ( LineCount < MaxLines )
         LineCount++;

      for ( int l=LineCount-2 ; l>=0 ; l-- ) {
         strcpy(TextBuf[l+1], TextBuf[l]);
         strcpy(TextBuf[0], line);
         char *nl = strchr(TextBuf[0], '\n');
         if ( nl != 0 ) *nl = '\0';
      }

      // String von IBM-PC-Zeichensatz nach Windows-ANSI konvertieren
      OemToAnsi((LPSTR)TextBuf[0], (LPSTR)TextBuf[0]);

      // Gesamten Clientbereich updaten
      InvalidateRect(DebugHwnd, NULL, TRUE);

      return num;
   }

   void cBase::setDebugWindow(EBHDL hwnd)
   {
      DebugHwnd = (HWND)hwnd;
      PrintFunc = DrawText;
      LineWidth = MaxLineLen;
   }

   void cBase::paintDebugWindow()
   {
      if ( debug ) {
         PAINTSTRUCT paint;
         HDC hdc = BeginPaint(DebugHwnd, &paint);

         TEXTMETRIC tm;
         int height = GetTextMetrics(hdc, &tm) ? tm.tmHeight : 10;

         TextOut(hdc, 0, 0, Heading, lstrlen(Heading));

         for ( int l=0 ; l<LineCount ; l++)
            TextOut(hdc, 0, height * (l+1), TextBuf[l], strlen(TextBuf[l]));

         EndPaint(DebugHwnd, &paint);
      }
   }

#else

   void cBase::setDebugWindow(EBHDL /*hwnd*/)
   {
      // ...
   }

   void cBase::paintDebugWindow()
   {
      // ...
   }

#endif

#endif

// Gemeinsamkeiten
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Schmankerl: Bitmasken im Klartext aus einer Zeichenkette ermitteln.
//
//    [ <bitmaske> { " " <bitmaske> } ]
//    <bitmaske> ::= ( <token> | <C-Zahl> ) [ "<" <dezimal-shift> ]
//
// - Die Tabelle ordnet Bitmustern ein Token mit max. 15 Zeichen zu.
// - (Teil-)Bitmasken durch !isalnum() getrennt, vorzugsweise ein Leerzeichen
// - fuer str=NULL wird ein Default-Wert uebergeben
// - Sehr tolerant: versucht nach jedem Fehler neu aufzusetzen
//
unsigned long cBase::getMask(const char *str, MASK_NAME *tab, unsigned long def)
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
         while (tab[i].name && stricmp(buf,tab[i].name)) {
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

// Neu&toll: GetDebugString mit Klartexteingabe:
//
void cBase::setDebugMask(const char *str)
{
   debug = getMask(str, dbg_mask_name, 0);
}

void cBase::setDebugMask(unsigned long mask)
{
   debug = mask;
}

unsigned long cBase::getDebugMask()
{
   return debug;
}

void cBase::setLogfile(const char *fname, bool append)
{
   log_file_active = (fname != 0);
   log_file.setFile(fname,append);
}

void cBase::setLogfileDimension(int max_gen, long max_size)
{
   log_file.setLimits(max_gen, max_size);
}

void cBase::setPrintFunc(PRINT_FUNC _printf)
{
   PrintFunc = (_printf ? _printf : Printf);
}

void cBase::DbgVOut(unsigned long mask, const char *fmt, va_list ap)
{
   if ( !print_flag && ((debug & mask) || mask == 0) ) {
      PrintIt(fmt, ap);
   }
}

void cBase::DbgOut(unsigned long mask, const char *fmt, ...)
{
   va_list ap;
   va_start(ap, fmt);
   DbgVOut(mask, fmt, ap);
   va_end(ap);
}

void cBase::DbgError(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgError) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

bool cBase::DbgAssert1(const char *expr, const char *file, int line)
{
   #ifdef __Use_Real_Assertion__
      if ( debug & dbgAssert )
         _assert((void*)expr, (void*)file, line);
   #endif

   #if defined __ECL_VCPP__
      // Formatiere gemaess VCPP-Fehlermeldungsformat (Visual-Studio: Doppelklick fuehrt zu Fehlerstelle)
      return DbgAssert2("%s(%d) : Assertion : Expression '%s' failed", file, line, expr);
   #else
      // "Normale" Formatierung
      return DbgAssert2("Expression '%s' failed in module %s, line %d", expr, file, line);
   #endif
}

bool cBase::DbgAssert2(const char *fmt, ...)
{
   if ( !print_flag ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }

   return false;
}

void cBase::DbgInfo(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgInfo) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgTrcBase(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgTrcBase) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgTrcDb(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgTrcDb) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgTrcWin(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgTrcWin) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgTrcApp(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgTrcApp) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgBase(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgBase) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgDb(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgDb) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgWin(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgWin) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

void cBase::DbgSql(const char *sql)
{
   if ( !print_flag && (debug & dbgSql) ) {
      PrintIt(sql);
   }
}

void cBase::DbgSqlRaw(const char *sql)
{
   if ( !print_flag && (debug & dbgSqlRaw) ) {
      PrintIt(sql);
   }
}

void cBase::DbgMsg(const char *fmt, ...)
{
   if ( !print_flag && (debug & dbgMsg) ) {
      va_list ap;
      va_start(ap, fmt);
      PrintIt(fmt, ap);
      va_end(ap);
   }
}

#if defined __ECL_OS2__
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




#ifdef __INTERFACE__

// ===========================================================================
// Definition cData
// ---------------------------------------------------------------------------
//
// cBase
//  +--cData
//
// ===========================================================================

class __ECL_DLLEXPORT__ cData : public cBase {

// Informationen zur Klasse
// ========================
// GetDataInfo() - Liefert einen eindeutigen 32-Bit-Wert, der die Datenklasse
//    beschreibt (in Form eines 4-Zeichen Eyecatchers)
//
// GetDataSize() - Liefert die Groesse des Datenbereiches (unabhaengig von der
//    tatsaechlichen Groesse des Objektes!)

public:
   virtual long GetDataInfo() const { return 0x5f5f5f5fL /*'____'*/; }
   virtual long GetDataSize() const { return 0; }


// Informationen zur Instanz
// =========================
// GetDataStart() - Liefert einen char-Zeiger auf die Startadresse (d.h. das
//    erste Byte) des Datenbereiches

   virtual char *GetDataStart() { return (char *)this; }

};

#endif /*__INTERFACE__*/



#ifdef __INTERFACE__

// ===========================================================================
// Definition cLogfile
// ---------------------------------------------------------------------------
//
// cLogfile
//
// ===========================================================================

class __ECL_DLLEXPORT__ cLogfile {

public:
   // Logdatei festlegen und aktivieren, ggf. löschen (append == false)
   // oder Logdatei deaktivieren (fname == 0).
   cLogfile(const char *fname = 0, bool append = true);
   void setFile(const char *fname = 0, bool append = true);
   // Protokolldatei ermitteln (0 = deaktiviert)
   const char *getFile();
   // Logdateigenerationen und Dateigroesse (0 = kein Limit) festlegen
   void setLimits(int max_gen, long max_size);
   // Logdateigenerationen und Dateigroesse ermitteln
   void getLimits(int &max_gen, long &max_size);
   // Zeile in Logdatei schreiben ('\n' wird angefügt!)
   void write(const char *text);

private:
   enum {
      MAX_LOGFILE_NAME = 132,
      DEF_LOGFILE_SIZE = 524288, // Standarddateigroesse: 512 KByte
      DEF_LOGFILE_GEN  = 3       // Standardgenerationenzahl
   };

   char logfile_name[MAX_LOGFILE_NAME];
   long max_logfile_size;  // Groesse einer einzelnen Datei
   int max_logfile_gen;    // Anzahl Generationen

   void theNextGeneration();
};

#endif /*__INTERFACE__*/


// Implementierung cLogfile
// ===========================================================================

cLogfile::cLogfile(const char *fname, bool append)
{
   max_logfile_size = DEF_LOGFILE_SIZE;
   max_logfile_gen = DEF_LOGFILE_GEN;
   setFile(fname,append);
}

void cLogfile::setFile(const char *fname, bool append)
{
   if ( fname && fname[0] ) {
      strncpy(logfile_name, fname, sizeof logfile_name);
      logfile_name[sizeof logfile_name - 1] = '\0';
      if ( !append ) {
         FILE *fp = fopen(logfile_name, "w");
         if ( fp ) fclose(fp);
      }
   } else {
      logfile_name[0] = '\0';
   }
}

const char *cLogfile::getFile()
{
   return logfile_name[0] ? logfile_name : 0;
}

void cLogfile::setLimits(int max_gen, long max_size)
{
   max_logfile_gen = max_gen;
   if ( max_logfile_gen < 0 ) max_logfile_gen = 0;
   if ( max_logfile_gen > 999 ) max_logfile_gen = 999;

   max_logfile_size = max_size;
   if ( max_logfile_size < 1024 &&
        max_logfile_size != 0 ) max_logfile_size = 1024;
}

void cLogfile::getLimits(int &max_gen, long &max_size)
{
   max_gen  = max_logfile_gen;
   max_size = max_logfile_size;
}

void cLogfile::write(const char *text)
{
   if ( logfile_name[0] ) {
      struct stat buf;
      FILE *logfile;

      if ( max_logfile_size &&
           stat(logfile_name, &buf) == 0 &&
           buf.st_size > max_logfile_size ) theNextGeneration();

      if ( (logfile = fopen(logfile_name, "a")) != NULL ) {
         fprintf(logfile, "%s\n", text);
         fclose(logfile);
      }
   }
}

void cLogfile::theNextGeneration()
{
   char base_name[MAX_LOGFILE_NAME], *point;
   char fname1[MAX_LOGFILE_NAME+4], fname2[MAX_LOGFILE_NAME+4];

   // Basisnamen der Logdatei ermitteln. Dazu Dateiname bei letztem
   // Punkt beenden, damit die "Generations"-Extensions (.001, .002, ...)
   // angehaengt werden koennen

   strcpy(base_name, logfile_name);
   if ( (point = strrchr(base_name, '.')) != NULL )
      *point = '\0';

   // Aelteste Generation loeschen

   if ( max_logfile_gen < 1 ) {
      unlink(logfile_name);
   } else {
      sprintf(fname1, "%s.%03d", base_name, max_logfile_gen);
      unlink(fname1);
   }

   // Alle Generationen dazwischen "shiften"

   for ( int gen = max_logfile_gen - 1 ; gen > 0 ; gen-- ) {
      sprintf(fname1, "%s.%03d", base_name, gen);
      sprintf(fname2, "%s.%03d", base_name, gen+1);
      rename(fname1, fname2);
   }

   // Bisher aktuelles Logfile in *.001 umbenennen

   sprintf(fname2, "%s.001", base_name);
   rename(logfile_name, fname2);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cOsBase
// ---------------------------------------------------------------------------
//
// Basisklasse zur Realisierung von betriebssystemspezifischen Objekten
// (OS-Objekt), die typischerweise ueber ein Identifikations-Handle verfuegen.
// Ueber die spezielle Methode getHandleFrom() kann die Implementierung des
// OS-Objektes auf normalerweise verdeckte Handles anderer OS-Objekte zu-
// greifen.
//
// cBase
//  +--cOsBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cOsBase : public cBase {

protected:

   class __ECL_DLLEXPORT__ cOsHandle {

   public:
   #if defined __ECL_OS2__

      cOsHandle(unsigned long h = 0)
         { cOsHandle::h = h; }
      unsigned long * operator & ()
         { return &h; }
      operator unsigned long () const
         { return h; }
      void invalidate()
         { h = 0; }
      bool isNull() const
         { return h == 0; }
      bool isValid() const
         { return h != 0; }

   private:
      unsigned long h;

   #elif defined __ECL_W32__

      cOsHandle(void *h = NULL)
         { cOsHandle::h = h; }
      void ** operator & ()
         { return &h; }
      operator void * () const
         { return h; }
      void invalidate()
         { h = NULL; }
      bool isNull() const
         { return h == NULL; }
      bool isValid() const
         { return h != NULL; }

   private:
      void *h;

   #endif

   };

   // Handle des betriebssystem-spezifischen Objektes
   cOsHandle handle;

   // Erfragen von Handles anderer betriebssystem-spezifischer Objekte
   static const cOsHandle getHandleFrom(const cOsBase& other)
      { return other.handle; }
   // Setzen von Handles anderer betriebssystem-spezifischer Objekte (Gefaehrlich!!!)
   static void setHandleOf(cOsBase& other, const cOsHandle& h)
      { other.handle = h; }

};

#endif /*__INTERFACE__*/

#ifdef __ECL_BCPP__

cBase::cBase()
{
   destructed = 0;
};

cBase::~cBase()
{
   if (destructed == 0) {
      destructed = 1;
   } else {
      Sleep(200);
      Beep(100,300);
   }
}

#endif



