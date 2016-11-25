// ==========================================================================
// debug_log.cpp
// ==========================================================================

// Interface
#include "debug_log.h"

// System includes
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>



// --------------------------------------------------------------------------
// Static variables
// --------------------------------------------------------------------------

//size_t cDebugLog::_max_message_length = 1024;
//cDebugLog::FILEMAP cDebugLog::_file_map;
//bool cDebugLog::_buffer_overflow = false;

// Die folgende Instanziierung sorgt dafuer, dass der Destruktor aufgerufen wird!
//static cDebugLog __auto_cleanup__;


// --------------------------------------------------------------------------
// Implementation of methods
// --------------------------------------------------------------------------

cDebugLog::cDebugLog() :
   _max_message_length(1024),
   _buffer_overflow(false)
{
}

cDebugLog::~cDebugLog()
{
   int id;
   cLogfile *lf;
   IPOSITION pos = _file_map.getStartPosition();
   while (pos) {
      _file_map.getNextAssoc(pos, id, lf);
      delete lf;
   }
   _file_map.removeAll();
}


void cDebugLog::assignIdToFile(int id, const char *file_spec, bool append)
{
   if (file_spec != 0) {
      cLogfile *lf = 0;
      if (_file_map.lookup(id, lf) == false) {
         lf = new0 cLogfile;
         _file_map.setAt(id, lf);
      }
      lf->setFile(file_spec, append);
      #ifndef USE_HISTORIC_ECL
         // neue ECL hat Timestamp integriert&aktiviert -> ausschalten
         lf->setTimestamp(false);
      #endif
   } else {
      cLogfile *lf = 0;
      if (_file_map.lookup(id, lf)) {
         delete lf;
         _file_map.removeKey(id);
      }
   }
}

bool cDebugLog::setLimits(int id, int max_gen, long max_size)
{
   cLogfile *lf = 0;
   if (_file_map.lookup(id, lf)) {
      lf->setLimits(max_gen, max_size);
      return false;
   } else {
      return true;
   }
}

int cDebugLog::getMaxGen(int id)
{
   cLogfile *lf = 0;
   if (_file_map.lookup(id, lf)) {
      int max_gen;
      long max_size;
      lf->getLimits(max_gen, max_size);
      return max_gen;
   } else {
      return -1;
   }
}

long cDebugLog::getMaxSize(int id)
{
   cLogfile *lf = 0;
   if (_file_map.lookup(id, lf)) {
      int max_gen;
      long max_size;
      lf->getLimits(max_gen, max_size);
      return max_size;
   } else {
      return -1;
   }
}

const char *cDebugLog::getFile(int id)
{
   cLogfile *lf = 0;
   if (_file_map.lookup(id, lf)) {
      return lf->getFile();
   } else {
      return 0;
   }
}

const char *cDebugLog::allocMessage(const char *fmt, ...)
{
   char *buffer = new char[_max_message_length];
   
   va_list ap;
   va_start(ap, fmt);
   size_t buffer_usage = _vsnprintf(buffer, _max_message_length-1, fmt, ap);
   va_end(ap);

   _buffer_overflow = (buffer_usage > _max_message_length);

   return buffer;
}

void cDebugLog::writeStatic(const char *file, int line, int id, const char *static_message)
{
   // Internen Pufferueberlauf (rekursiv) melden
   if (_buffer_overflow) {
      writeStatic(file, line, id, "*** Internal debug print buffer overflow caused by the subsequent message:" );
      _buffer_overflow = false;
   }

   // Pfad vom Dateinamen entfernen ('\' oder '/' als Trennzeichen erlaubt)
   const char * filename = NULL;
   if (file == NULL) {
      filename = "FILE_NAME_ERROR";
   } else {
      filename = strrchr(file,'\\');
   }
   if (filename == NULL) {
      filename = strrchr(file, '/');
   }
   if (filename == NULL) {
      filename = file;
   } else {
      filename++; 
   }

   // Zeitstempel formattieren (Ortszeit nach ISO 8601: "jjjj-mm-tt hh:mm:ss")
   char timestamp[32];
   time_t now = time(0);
   struct tm * local = localtime(&now);
   strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local);

   // Gesamtmeldung zusammenbauen (32 byte fuer Zeilennummer und Formattierung):
   // "jjjj-mm-tt hh:mm:ss  filename(line):  message"
   size_t max_final_length = strlen(static_message) + strlen(filename) + strlen(timestamp) + 32;
   char *final_message = new char[max_final_length];
   _snprintf(final_message, max_final_length, "%s  %s(%d):  %s",timestamp, filename, line, static_message);

   cLogfile *lf = 0;
   if (_file_map.lookup(id, lf)) {
      // Ausgabe in durch id festgelegtes Logfile
      lf->write(final_message);
   } else {
      // Standardausgabe auf stderr wenn die Datei nicht definiert ist!!!
      fprintf(stderr, "%s\n", final_message);
   }

   // Resourcen wieder freigeben
   delete[] final_message;
}

void cDebugLog::writeDynamic(const char *file, int line, int id, const char *dynamic_message)
{
   // Meldung wie gewohnt ausgeben ...
   writeStatic(file, line, id, dynamic_message);

   // ... aber danach den Puffer wieder freigeben!
   delete[] (char*)dynamic_message;
}

