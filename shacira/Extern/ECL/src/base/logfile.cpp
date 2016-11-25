// ===========================================================================
// base/logfile.cpp                                             ______ /  ECL
// Autore: Markus Wuertz                                       /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/logfile.h"

// ECL headers
#include "base/base_ex.h"

// Standard headers
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <sys/stat.h> /* stat(), fstat() */




namespace ecl {




// Implementierung cLogfile
// ===========================================================================

/**
 * Logdatei festlegen und aktivieren oder Logdatei deaktivieren.
 * 
 * @param fname  Zeiger auf Dateiname (oder 0, um Logdatei zu deaktivieren)
 * @param append true: Anhaengen an bestehende Logdatei
 *               false: Bestehende Logdatei loeschen
 */
cLogfile::cLogfile(const char *fname, bool append)
{
   _use_timestamp = true;
   _max_logfile_size = DEF_LOGFILE_SIZE;
   _max_logfile_gen = DEF_LOGFILE_GEN;
   setFile(fname,append);
}

/**
 * Logdatei festlegen und aktivieren oder Logdatei deaktivieren.
 * 
 * @copydoc cLogfile()
 */
void cLogfile::setFile(const char *fname, bool append)
{
   if ( fname && fname[0] ) {
      _logfile_name = fname;
      if ( !append ) {
         FILE *fp = fopen(_logfile_name.ccp(), "w");
         if ( fp ) fclose(fp);
      }
   } else {
      _logfile_name = cString();
   }
}

const char *cLogfile::getFile()
{
   return _logfile_name.ccp();
}


void cLogfile::setTimestamp(bool enable)
{
   _use_timestamp = enable;
}

bool cLogfile::getTimestamp() const
{
   return _use_timestamp;
}


void cLogfile::setLimits(int max_gen, long max_size)
{
   _max_logfile_gen = max_gen;
   if ( _max_logfile_gen < 0 ) 
      _max_logfile_gen = 0;
   if ( _max_logfile_gen > 999 ) 
      _max_logfile_gen = 999;

   _max_logfile_size = max_size;
   if ( _max_logfile_size < 1024 && _max_logfile_size != 0 ) 
      _max_logfile_size = 1024;
}

void cLogfile::getLimits(int &max_gen, long &max_size)
{
   max_gen  = _max_logfile_gen;
   max_size = _max_logfile_size;
}


// local helper: get timestamp
// buf must be currently at least 22 bytes
static char *FormatTime(char *buf)
{
   time_t lntime; time(&lntime);
   struct tm *tmtime = localtime(&lntime);
   sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d  ",
      1900 + tmtime->tm_year, tmtime->tm_mday, tmtime->tm_mon + 1, 
      tmtime->tm_hour, tmtime->tm_min, tmtime->tm_sec);

   return buf;
}


void cLogfile::write(const char *text)
{
   if ( _logfile_name.isEmpty() == false ) {
      struct stat buf;
      FILE *logfile;

      if ( _max_logfile_size && stat(_logfile_name.ccp(), &buf) == 0 && buf.st_size > _max_logfile_size ) 
         theNextGeneration();

      if ( (logfile = fopen(_logfile_name.ccp(), "a")) != 0 ) {
         if (_use_timestamp) {
            char stamp[32];
            fprintf(logfile,FormatTime(stamp));
         }
         fprintf(logfile, "%s\n", text);
         fclose(logfile);
      }
   }
}


void cLogfile::theNextGeneration()
{
   cString path,name,ext;
   cStrFile(_logfile_name).splitFileSpec(path,name,ext);

   // Aelteste Generation loeschen
   if ( _max_logfile_gen < 1 ) {
      remove(_logfile_name.ccp());
   } else {
      remove((path+name+cStringf(".%03d",_max_logfile_gen)+ext).ccp());
   }

   // Alle Generationen dazwischen "shiften"
   for ( int gen = _max_logfile_gen - 1 ; gen > 0 ; gen-- ) {
      rename((path+name+cStringf(".%03d",gen)+ext).ccp(),
             (path+name+cStringf(".%03d",gen+1)+ext).ccp());
   }

   // Bisher aktuelles Logfile in *.001 umbenennen
   rename(_logfile_name.ccp(), (path+name+".001"+ext).ccp());

}


/**
 * Das Format der Parameterzeile ist:
 * "{ gen=<n>|size=<n>|app=<n>|time=<n> } [file=][<fname>]"
 * - gen: Anzahl der Dateigenerationen setzen
 * - size: Größe einer Einzeldatei (0 = keine Beschränkung)
 * - app: Anfügen (append) an bestehende Datei (default 1=ein, 0=aus)
 * - time: Datum & Uhrzeit ausgeben (default 1=ein, 0=aus)
 * - file: Basisname der Logdateien
 */
void cLogfile::setParam(const char *param)
{
   cBase::cParser::SYMBOL keylist[] = {
      1,"gen=",
      2,"size=",
      3,"time=",
      4,"app=",
      0,0
   };

   cBase::cParser p(param);
   long key = -1;
   long value = 0;
   bool append = true;
   while (p.getStdSymbol(keylist,key).getLong(value)) {
      switch (key) {
      case 1: _max_logfile_gen = value; break;
      case 2: _max_logfile_size = value; break;
      case 3: _use_timestamp = (value != 0); break;
      case 4: append = (value != 0); break;
      }
   }
   p.ok().isStr("file=");
   const char *fname = p[0] ? (const char *)p : getFile();
   setFile(fname, append);
}


}; // namespace ecl


