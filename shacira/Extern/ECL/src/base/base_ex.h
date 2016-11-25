// ===========================================================================
// base/base_ex.h                                               ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die internen Hilfsklassen von cBase
// zur Verfuegung. Sie sind nur zur Benutzung innerhalb der ECL vorgesehen
// und koennen ohne Vorwarnung geaendert werden oder auch ganz entfallen!
// base_ex.h sollte ausschliesslich nur innerhalb von .cpp-Dateien verwendet
// werden und keinesfalls innerhalb anderer ECL-Header eingebunden werden.
//
//    cBase::cCore
//    cBase::cFilter
//    cBase::cStatistic
//    cBase::cParser
//    cBase::cCritical
//
// ===========================================================================

#ifndef __ecl_base_ex__
#define __ecl_base_ex__


// Platform dependant headers
#ifdef __ECL_W32__
   #include <windows.h> // InterlockedIncrement(), InterlockedDecrement()
#endif

// Other ECL headers
#include "base/base.h"
#include "base/list.h"
#include "base/map.h"
#include "base/string_ex.h"
#include "base/semaphore.h"

namespace ecl {

#ifdef __ECL_W32__
   // For thread safety on SMP and hyperthreading enabled machines.
   // Based on work of -PR- 2005-10-11 inside shacira.
   typedef volatile int ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n = v;
   #define __ECL_ATOMIC_GET__(n) (n)
   #define __ECL_ATOMIC_INCREMENT__(n) InterlockedIncrement((long*)&n)
   #define __ECL_ATOMIC_DECREMENT__(n) InterlockedDecrement((long*)&n)
#elif defined(__linux__)
   #include "asm/atomic.h"
   typedef atomic_t ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n.counter = v;
   #define __ECL_ATOMIC_GET__(n) atomic_read(&n)
   #define __ECL_ATOMIC_INCREMENT__(n) atomic_add_return(1,&n)
   #define __ECL_ATOMIC_DECREMENT__(n) atomic_sub_return(1,&n)
///   #define __ECL_ATOMIC_INCREMENT__(n) ++n
///   #define __ECL_ATOMIC_DECREMENT__(n) --n
#else
   typedef volatile int ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n = v;
   #define __ECL_ATOMIC_GET__(n) (n)
   #define __ECL_ATOMIC_INCREMENT__(n) ++n
   #define __ECL_ATOMIC_DECREMENT__(n) --n
#endif

// ===========================================================================
// cBase::cCritical - Critical section protection
// ===========================================================================

/**
* @class cBase::cCritical base_ex.h "base/base_ex.h"
* @brief Critical section protection
*
* A more simple implementation of some kind of mutex variable other than
* the "official" cMutexSem. It is used inside the ecl core for some thread
* safety, e.g. during debug outputs. cMutexSem can't be used here because
* it contains debug output code itself.
*/
class __ECL_DLLEXPORT__ cBase::cCritical
{
public:
   //! Constructor
   cCritical();
   //! Destructor
   ~cCritical();

   //! Enter critical section
   void enter();
   //! Leave critical section
   void leave();

private:
   void *_critical_section;

}; // cBase::cCritical




/**
* @class cBase::cCriticalGuard base_ex.h "base/base_ex.h"
* @brief Critical section protection as guard class
*
* Enter critical section in the constructor (block and wait if another 
* thread is already inside the cricital section) and leave the critical
* section automatically on destruction of the guard object.
*/
class __ECL_DLLEXPORT__ cBase::cCriticalGuard
{
public:
   //! Constructor
   cCriticalGuard(cCritical &critical) : _critical(critical) { _critical.enter(); }
   //! Destructor
   ~cCriticalGuard() { _critical.leave(); }

private: 
   // Kopieren verboten!
   cCriticalGuard(const cCriticalGuard &rhs);
   cCriticalGuard &operator=(const cCriticalGuard &rhs);

   // Mutexobjekt
   cCritical &_critical;
}; // cBase::cCriticalGuard




// ===========================================================================
// cBase::cCore - Zentrales Singleton Objekt zur ECL-Steuerung
// ===========================================================================

/**
* @class cBase::cCore base_ex.h "base/base_ex.h"
* @brief Singleton object to control the ECL.
*/
class cBase::cCore
{
public:
   //! During construction the following environment variables are analysed:
   //! - ECL_CFG the fabulous, new ECL configuration environment variable
   //!   is read and executed with doConfig().
   //! - ECL_DBG the classic debug mask is currently still provided for
   //!   compatibility. Later ECL_CFG will replace it completely!
   //! - ECL_LOG the classic log file definition is currently still provided
   //!   for compatibilty. Later ECL_CFG will replace it completely!
   cCore();
   //! During destruction a sequence of doConfig() commands is executed, that
   //! have been stored during construction (or later) with atexit commands.
   ~cCore();

   // ------------------------------------------------------------------------
   //! Send the text to all devices that are activated in the global output_mask
   //! (except 'outAssert').
   void printMasked(const char *text);
   //! Send the text to all devices that are activated in the mask
   //! (except 'outAssert').
   void printMasked(unsigned long mask, const char *text);

   //! Store the last printed text
   void setLastPrintText(const cString &text) { _last_print_text = text;}
   //! Get the last printed text
   const cString &getLastPrintText() const { return _last_print_text; }

   // ------------------------------------------------------------------------
   // Konfigurationsmodul

   //! Parse configuration string and execute contained commands.
   //! To do this the string is split in lines separated by '\\n' and parseLine()
   //! is called for each line. See cBase::doConfig() for command details.
   bool parseConfig(const cString &config_string);

   //! Parse configuration line and execute contained commands. Each line may contain
   //! several commands separated by ';'. See cBase::doConfig() for command details.
   bool parseLine(const cString &config_line);

   // ------------------------------------------------------------------------
   //! Is called from atexit to deposit another doConfig() command that is
   //! executed during destruction of the core singleton.
   void addLastWill(const char *cmd);
   
   //! Is called from the core destructor to execute the stored atexit commands.
   void execLastWill();

   //! This is an old and deprecated data structure used for the old, symbolic
   //! debug mask. It is hidden in cCore to disappear from the Visual Studio
   //! class browser and will be removed in the future.
   struct MASK_NAME {
      unsigned long mask;
      const char *name;
   };

private:
   // Einzelne Befehle des Konfigurationsmoduls:
   // - liefert false wenn das Befehlswort nicht erkannt wurde, true sonst
   // - error bzw. (bool)p liefern bei erkannten Befehlen Ausfuehrungsfehler
   bool cmdClear(cBase::cParser &p, cString &error);
   bool cmdAtExit(cBase::cParser &p, cString &error);
   bool cmdInclude(cBase::cParser &p, cString &error);
   bool cmdSet(cBase::cParser &p, cString &error);
   bool cmdFilter(cBase::cParser &p, cString &error);
   bool cmdLogfile(cBase::cParser &p, cString &error);
   bool cmdEcho(cBase::cParser &p, cString &error);

   // Parse string up to end of the current config_cmd, may be empty
   bool getStringTail(cBase::cParser &p, cString &str);
   // Is end of line or comment at end of line
   bool isEoln(cBase::cParser &p);

   // Last printed text
   cString _last_print_text;

   // aktuell bearbeitete Include-Datei inclusive Zeilenzaehler
   const char *_include_file;
   int _include_line_count;
   int _include_depth_limit;

   // Critical section 
   cCritical _print_masked_critical;

   // Befehlsfolge fuer doConfig() beim Beenden der ECL
   cList<cString, const cString &> _last_will;
};

// Zugriff auf das Singleton
cBase::cCore &BASE_CORE();




// ===========================================================================
// cBase::cFilter - Filter fuer Debug-Masken
// ===========================================================================

/**
* @class cBase::cFilter base_ex.h "base/base_ex.h"
* @brief List with filter definitions.
*/
class cBase::cFilter
{
public:
   //! Initialize empty list
   cFilter();
   //! Free all list items
   ~cFilter();

   //! @struct FILTER base_ex.h "base/base_ex.h"
   //! @brief Linked list for debug filters.
   struct FILTER {
      unsigned long mand;  //!< 'mask & mand' is calculated ...
      unsigned long match; //!< ... and must equal to 'match'
      char *file;          //!< optional tail of filename or 0 (not case sensitive)
      unsigned long out;   //!< output mask
      FILTER *next;        //!< next element
   };
   // (Since base.cpp should not depend too much on other ECL components,
   // cList<...> has not been used. And second, the handmade list is perhaps
   // a little more efficient.)

   //! Search for mask and file in the list of debug filters. Returns the
   //! associated output mask or 0 if not found.
   unsigned long matchFilter(unsigned long mask, const char *file);

   //! Add a new filter to the list, depending on the flag @a atend at the end
   //! or the at the beginning. An existing, identical filter (mand,match,file)
   //! is removed if @a out == 0, otherwise updated and placed at the end or the
   //! beginning.
   void addFilter(unsigned long mand, unsigned long match, const char *file, unsigned long out, bool atend = true);

   //! Show all filters on the default debug output devices. This must not
   //! be the format used to define the filters. The output is generated from
   //! the binary filter representations and is one possible definition formula.
   void show();

private:
   // Anker der Filterliste
   FILTER *_filter;

   // Filterelement freigeben, liefert das next-Element
   FILTER *freeFilter(FILTER *filter);
   // vorhandenen Filter ausketten, liefert den gefundenen Filter oder 0
   FILTER *unlinkEqualFilter(unsigned long mand, unsigned long match, const char *file);
   // Neue Top-Level Debug-Maske aus aktueller Filterliste berechnen
   unsigned long calcDebugMask() const;

   // Prueft ob current mit pattern endet (0 ist erlaubt)
   static bool isMatching(const char *pattern, const char *current);
   // Vergleicht die Dateinamen auf Gleichheit (0 ist erlaubt)
   static bool isEqual(const char *f1, const char *f2);
};




// ===========================================================================
// cBase::cStatistic - Statistiken fuehren
// ===========================================================================

/**
* @class cBase::cStatistic base_ex.h "base/base_ex.h"
* @brief Statistic module for (optional) internal access counting
*
* If the ECL is compiled with the booster bit @b __ECL_DEBUG_ENABLE_STATISTIC__
* set in the compiler switch __ECL_DEBUG__, the constructors of some (usually
* platform dependand) classes contains calls to the statistic module to count
* how much instances of the class are used (useful to decide what have to be
* done when porting to another platform).
*
* @note This class is intended to be only used inside the ECL.
* The interface may change without notice.
*/
class __ECL_DLLEXPORT__ cBase::cStatistic
{
public:
   //! Constructor
   cStatistic();
   //! Destructor
   ~cStatistic();
   
   //! Count up. Initial value for the first call for a label is 0. If LONG_MAX is
   //! reached, the counter keeps that value.
   long increment(const cString &label);
   //! Count down. Initial value for the first call for a label is 0. If LONG_MIN is
   //! reached, the counter keeps that value.
   long decrement(const cString &label);
   //! Store new value if greater than already stored value
   long maximum(const cString &label, long value);
   //! Store new value if less than already stored value
   long minimum(const cString &label, long value);
   //! Set value
   long assign(const cString &label, long value);
   //! Query value (returns 0 if label does not exist)
   long query(const cString &label);
   //! Check existance of label.
   bool exist(const cString &label);

   //! Show all labels and their values on the default debug output devices.
   void show();


private:
   cCritical _critical;
   cMap<cString, const cString &, long, long> *_statistic_map;
};




// ===========================================================================
// cBase::cParser - Parser fuer Konfigurationsstrings
// ===========================================================================

/**
* @class cBase::cParser base_ex.h "base/base_ex.h"
* @brief Simple parser for ecl configuration
*
* Most of the concrete parse methods assign the parsed value to a variable
* by reference and return *this, so multiple calls can be easily parsed by
* concatenation. Example:
* @code
* long value = 0;
* bool ok = cParser("hund 123").isStr("hund").getLong(value);
* // ok == true && value == 123
* @endcode
*
* @note This simple parser is intended to be only used inside the ECL for internal
* configuration. The interface may change without notice.
*/
class __ECL_DLLEXPORT__ cBase::cParser
{
public:
   //! Constructor that initializes the scan pointer to the text that is
   //! to be parsed.
   cParser(const char *ptr) : _ptr(ptr), _ok(ptr != 0), _sym(0), _skip_space(true) {}
   
   //! @name Access to parser attributes
   //@{
   //! Cast to bool to get the internal error state. Returns true if parsing 
   //! was successful and false if a syntax error occured. If the parser is in
   //! error state the scan pointer is frozen and parsing will always fail
   //! until the error state is cleared with ok().
   operator bool() const { return _ok; }
   
   //! Set the internal error state of the parser (by default to no error).
   cParser &ok(bool ok = true) { _ok = (_ptr != 0) && ok; return *this; }
   
   //! Cast to const char * to get the current (and in case of error state
   //! frozen) scan pointer position.
   operator const char *() const { return _ptr; }
   
   //! The array operator can be used to peek the next characters at the
   //! scan pointer. The index is not checked, so be careful! But since the
   //! scan pointer resides at the final '\\0' char, 0 is always a valid index.
   char operator[] (int index) const { return _ptr ? _ptr[index] : 0; }
   
   //! Increment the scan pointer. If @a offset is too large, the pointer
   //! resides on the final '\\0' and error state is reached.
   cParser& operator+=(size_t offset);
   //@}

   //! @name Elementar parsing (without symbols)
   //@{
   //! Skip whitespaces and return the first non-whitespace character (which
   //! may be '\\0'). The scan pointer resides ON that character. If skipping
   //! whitespaces is turned off with setSkipSpace(false), the next character
   //! is returned, don't care what it is.
   char skipSpace();

   //! Usually the parse methods still ignore leading whitespaces, but if
   //! required you can turn this feature off.
   cParser &setSkipSpace(bool on_off) { _skip_space = on_off; return *this; }

   //! Get next character. Whitespaces are skipped, scan pointer is behind the
   //! returned character.
   cParser& getChar(char &ch);
   
   //! Next must be a terminal @a ch. Case sensitivity can be selected with
   //! @a ignore_case and is turned of by default. Whitespaces are skipped
   //! (like getChar()). If @a ch matches, the scan pointer is behind the char,
   //! otherwise on that char and error state es reached.
   cParser& isChar(char ch, bool ignore_case = true);
   
   //! Like isChar(), but the complete string @a str must match.
   cParser& isStr(const char *str, bool ignore_case = true);
   
   //! Get unsigned long into @a value. If @a base is 0 (or missing), either
   //! decimal, octal (with leading '0') or hexadecimal (with leading '0x')
   //! numbers are allowed. Otherwise the specified base is used for parsing.
   //! In error state @a value remains unchanged (this may be used for default
   //! values).
   cParser& getULong(unsigned long &value, int base = 0);
   
   //! Like getULong(), but with lower and upper limit (from <= value <= to).
   cParser& getULong(unsigned long &value, unsigned long from, unsigned long to, int base = 0);
   
   //! Like getULong(), but with a signed long.
   cParser& getLong(long &value, int base = 0);
   
   //! Like getLong(), but with lower and upper limit (from <= value <= to).
   cParser& getLong(long &value, long from, long to, int base = 0);
   
   //! Get word delimitted with whitespaces. Enclosed in either "..." or '...'
   //! strings with embedded whitespaces are allowed.
   cParser& getStr(cString &value);
   //@}

   //! @struct SYMBOL base_ex.h "base/base_ex.h"
   //! @brief Struct for standard symbol implementation.
   struct SYMBOL {
      int value;        //!< Value assigned to symbol.
      const char *name; //!< Symbol text, must completely match (case insensitive).
   };

   //! @name blubber Symbol parsing
   //@{
   //! Parse a symbol from the text and assign it to @a value. Reimplementation
   //! of this virtual function allows the use any kind of symbols. The default
   //! implementation (used in cBase::cCore) is for example not sufficient for
   //! the use in cCmdLine. If no symbol matches error state must be reached
   //! and @a value must remain unchanged (this may be used for default values).
   virtual cParser &getSymbol(long &value) { return getStdSymbol(_sym, value); }

   //! Define the symbol list for the standard symbol matching. The end of the
   //! symbol list must be marked with an entry with @a name = 0. If no symbol
   //! list is initialized, getSymbol() will always lead to error
   //! state.
   cParser &setSymbolList(SYMBOL *sym) { _sym = sym; return *this; }

   //! Standard implementation of getSymbol() that uses SYMBOL*
   cParser &getStdSymbol(SYMBOL* sym, long &value, bool ignore_case = true);

   //! Parse simple expressions that lead typically to a binary coded bit mask:\n\n
   //! <b>Syntax in EBNF:</b>\n
   //! <tt>expression = number { operator number } ;\n
   //! number = ? matches either getLong() or getSymbol() ? ;\n
   //! operator = '+' | '-' | '|' | '&' | '&~' | '~' ; </tt>\n
   //!
   //! Most operators are common, except of '&~' which can be used to @b reset the
   //! 1-bits of the right number (like '|' can be used to set the 1-bits of the
   //! right number). Remember that there is no precedence
   //! of operators and values are strictly evaluated from left to right (and no
   //! brackets are possible). For example "a | b & c" is evaluated as
   //! "(a | b) & c" and not as "a | (b & c)"
   //! as you may expect it if you are familiar with C or C++.
   virtual cParser &getBitmaskExpr(long &value);

   //! Compose a symbolic representation of a binary bitmask
   static cString getSymbolBitmask(long value, SYMBOL *sym);
   //@}

private:
   bool _ok;
   bool _skip_space;
   const char *_ptr;
   SYMBOL *_sym;
};


}; // namespace ecl


#endif //__ecl_base_ex__

