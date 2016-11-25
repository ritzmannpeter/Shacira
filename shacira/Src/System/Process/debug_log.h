// ==========================================================================
// debug_log.h
// Autor: Markus Wuertz
// --------------------------------------------------------------------------
//
// Assignment of file id to log file name:
//
//    DEBUG_LOG()->assignIdToFile( <id> , <filespec> )
//
//    <id> - int to identify the logfile. There is no limitation how many
//       files are assigned to numbers. If a id is already used, the old
//       assignment is overwritten.
//    <filespec> - file path and file name. If 0 is passed, an existing 
//       assignment is removed.
//
// Change logfile settings (size of each file, number of files):
//
//    DEBUG_LOG()->setLimits( <id> , <max_gen> , <max_size> )
//
//    <id> - number of the logfile
//    <max_size> - maximum size of the current logfile. If this size is
//       reached, the logfile is renamed to a name containing a counter
//       and logging is continued in a new, empty file.
//    <max_gen> - This is the number of renamed logfiles (with counters
//       in the name). If this limit is reached, the oldest file will be
//       deleted.
//
//    Example: If the logfile is "C:\log\errors.log" and the default values
//    for <max_gen>=3 and <max_size>=524288 (512 KByte) are used, a maximum
//    amount of 2 MB disk space is used, divided into 4 files:
//    "C:\log\errors.log" (currently written), "C:\log\errors.001",
//    "C:\log\errors.002" and "C:\log\errors.003" (oldest file).
//
// To write a constant message in the logfile:
//
//    DEBUG_LOG_TEXT( <id> , <text> )
//
//    <id> - number of the logfile
//    <text> - string constant
//
//    Example: DEBUG_LOG_TEXT(1, "Application startet") writes a line like:
//    "2005-03-04 13:21:22  main.cpp(23):  Application started"
//    with a timestamp and the current file and line of the macro call.
//
// To write a printf formatted message in the logfile:
//
//    DEBUG_LOG_PRINTF( <id> , (<fmt>, ...) )
//
//    <id> - number of the logfile
//    (<fmt>, ...) - format string and parameters ENCLOSED IN BRACKETS.
//
//    Example: DEBUG_LOG_PRINTF(1, ("Error code = %d", error_code)) may become
//    "2005-03-04 13:21:22  somefile.cpp(123):  Error code = 456"
//
// ==========================================================================

#ifndef __debug_log_h__
#define __debug_log_h__

// Comment out the following #define to use the current and new ecl version
//#define USE_HISTORIC_ECL

// include files
#ifdef USE_HISTORIC_ECL
   #include "base/eb_base.hpp"
   #include "base/eb_map.hpp"
#else
   #include "base/logfile.h"
   #include "base/map.h"
   using namespace ecl;
#endif
#include "base/singleton.h"


// Macros
#define DEBUG_LOG_PRINTF(id, format) \
   cDebugLog::getInstance()->writeDynamic( __FILE__, __LINE__, id, cDebugLog::getInstance()->allocMessage format )

#define DEBUG_LOG_TEXT( id, text ) \
   cDebugLog::getInstance()->writeStatic( __FILE__, __LINE__, id, text )


// --------------------------------------------------------------------------
// Class
// --------------------------------------------------------------------------

#ifdef USE_HISTORIC_ECL
   class cDebugLog : public cSingleton<cDebugLog>
#else
   class cDebugLog : public ecl::tSingleton<cDebugLog>
#endif
{
public:
   // Construction / Destruction
   cDebugLog();
   ~cDebugLog();

   // ---------------------------------------------------------------
   // Configure the LogFiles
   // ---------------------------------------------------------------

   // Assign an ID to a Logfile for future use. Existing assignments are
   // overwritten. If file_spec == 0 assignements are removed.
   // With append = false the logfile is initially deleted.
   void assignIdToFile(int id, const char *file_spec, bool append = true);

   // Set the limits of a Logfile assigned to id:
   // max_gen -  number of separate logfiles (called generations) until
   //            the oldest logfile is removed. If value is 0, there is
   //            no limitation. Default is 3.
   // max_size - maximum file size in bytes of a single logfile until a
   //            new file is started. All 'older' files are renamed (and
   //            stay in the same directory). Minimum file size is 1024.
   //            Default is 512 KB (512*1024 Bytes).
   // Returns an error flag: true=if no file assigned to id, false=ok.
   bool setLimits(int id, int max_gen, long max_size);

   // Returns number of file generations for id (or -1 if id is is invalid)
   int getMaxGen(int id);
   // Returns maximum file size for id (or -1 if id is invalid)
   long getMaxSize(int id);
   // Return the name of the file assigned to id (or 0 if id is invalid)
   const char *getFile(int id);


   // ---------------------------------------------------------------
   // Write to LogFiles
   // ---------------------------------------------------------------

   // Factory message. According to the printf-sytle format in fmt, the
   // arguments are written in a dynamically allocated buffer.
   const char *allocMessage(const char *fmt, ...);

   
   void writeStatic(const char *file, int line, int id, const char *static_message);
   void writeDynamic(const char *file, int line, int id, const char *dynamic_message);


   // ---------------------------------------------------------------
   // General settings
   // ---------------------------------------------------------------
   
   // Maximum length of a debug message
   void setMaxMessageLength(size_t maxlen) { _max_message_length = maxlen; }
   size_t getMaxMessageLength() { return _max_message_length; }

private:
   // map with logfiles
   typedef cMap<int, int, cLogfile*, cLogfile*> FILEMAP;
   FILEMAP _file_map;

   // Maximum length of a debug message, used to allocate print buffer memory.
   // Default value is 1024 bytes.
   size_t _max_message_length;

   // Internal flag to report if the allocated print buffer is to small
   bool _buffer_overflow;
};


// inline function for comfortable access to the class instance
inline cDebugLog *DEBUG_LOG() { return cDebugLog::getInstance(); }


#endif // __debug_log_h__
