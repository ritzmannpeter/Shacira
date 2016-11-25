// ===========================================================================
// base/error.cpp                                               ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/error.h"

// Standard headers
#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cctype>

// Other ECL headers
#include "base/string.h"




namespace ecl {




// ===========================================================================
// Lokale Klasse cMessage
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMessage
//
// ===========================================================================

class cMessage {

public:
   cMessage(cErrBase::ERR_TYPE code, const char *msg);
   cMessage(const char *code, const char *msg);
  ~cMessage();


// Konvertierung Fehlercode
// ========================
// Str2Code() - Ermittelt die numerische Form des Codes aus der Textform
// Code2Str() - Erzeugt die Textform des Codes

   static cErrBase::ERR_TYPE convStr2Code(const char *str);
   static size_t convCode2Str(char *str, cErrBase::ERR_TYPE code, size_t len);


// Verzeigerung
// ============


private:
   cMessage *next;
   static cMessage *first, *last;
   static bool initialized;
   static int file_not_found;
   void add(cErrBase::ERR_TYPE code, const char *msg);

public:
   static void initialize();
   static void cleanup();
   static bool readFile(const char *fname);
   static bool includeFile(const char *from_fname, const char *incl_fname);
   static cMessage *find(cErrBase::ERR_TYPE code);
   static int getFileNotFound() { return file_not_found; }

// Meldungsdaten
// =============

   cErrBase::ERR_TYPE getCode() const { return code; }
   const char *getMsg() const { return msg; }

private:
   cErrBase::ERR_TYPE code;
   char *msg;

};


// Implementierung cMessage
// ===========================================================================

cMessage * cMessage::first = 0;
cMessage * cMessage::last = 0;
bool cMessage::initialized = false;
int cMessage::file_not_found = 0;

cMessage::cMessage(cErrBase::ERR_TYPE code, const char *msg)
{
   add(code, msg);
}

cMessage::cMessage(const char *code, const char *msg)
{
   cErrBase::ERR_TYPE num_code = convStr2Code(code);

// if ( num_code == cErrBase::errMalformed ) {
//    fprintf(stderr, "<invalid error code %s>\n", code);
// } else {
      add(num_code, msg);
// }
}

cMessage::~cMessage()
{
   delete[] msg; // -TE- 02.03.2001 delete -> delete[]
}


// Konvertierung Fehlercode
// ========================

cErrBase::ERR_TYPE cMessage::convStr2Code(const char *str)
{
   cErrBase::ERR_TYPE code = 0;

   while ( *str && *str != '-' )
      code = 256 * code + *str++;

   if ( *str++ ) {
      switch ( toupper(*str++) ) {
       case 'I':  code = 256*code; break;
       case 'W':  code = 256*code + 64; break;
       case 'E':  code = 256*code + 128; break;
       case 'F':  code = 256*code + 192; break;
       default:   return cErrBase::errMalformed;
      }

      if ( *str++ == '-' ) {
         cErrBase::ERR_TYPE sub_code = atoi(str);
         if ( sub_code < 1 || sub_code > 64 )
            return cErrBase::errMalformed;
         code += sub_code - 1;
      }
   }

   return code;
}

size_t cMessage::convCode2Str(char *str, cErrBase::ERR_TYPE code, size_t len)
{
   char buf[16];

   sprintf(buf, "%c%c%c-%c-%02d",
      (char)((code & 0xff000000) >> 24),
      (char)((code & 0x00ff0000) >> 16),
      (char)((code & 0x0000ff00) >> 8),
      "IWEF"[(code & 0x000000c0) >> 6],
      (int)(code & 0x3f) + 1);

   strxcpy(str, buf, len);
   return strlen(buf);
}


// Verzeigerung
// ============

void cMessage::initialize()
{
   // Fuer das automatische Aufrufen von cMessage::cleanup() Sorge tragen...
   class cAutoCleanup { public: ~cAutoCleanup() { cMessage::cleanup(); } };
   static cAutoCleanup auto_cleanup;

   if ( !initialized ) {

      // Das Oeffnen der Meldungsdatei wird aus Performancegruenden
      // nur ein einziges Mal versucht.

      initialized = true;

      const char *fname = getenv("ECL_ERRMSG");
      if ( !fname )
         fname = "ERROR.MSG";

      char buf[512];
      const char *fend;

      while (*fname) {
         // naechsten Dateinamen in buf kopieren
         if ( (fend = strchr(fname,';')) == 0 ) {
            fend = fname+strlen(fname);
         }
         if (fend-fname >= sizeof(buf)) {
            strncpy(buf,fname,sizeof(buf)-1);
            buf[sizeof(buf)-1] = '\0';
         } else {
            strncpy(buf,fname,fend-fname);
            buf[fend-fname] = '\0';
         }

         readFile(buf);

         fname = *fend ? fend+1 : fend;
      } /*while (*fname)*/

   }
}

void cMessage::cleanup()
{
   cMessage *msg = first;

   while ( msg ) {
      cMessage *to_del = msg;
      msg = msg->next;
      delete to_del;
   }
}

bool cMessage::readFile(const char *fname)
{
   FILE *fp;
   char buf[512];

   if ( (fp = fopen(fname, "r")) != 0 ) {
      while ( fgets(buf, sizeof buf, fp) > 0 ) {
         char *newln = strchr(buf, '\n');
         if ( *newln )
            *newln = '\0';
         if ( cString::_strnicmp(buf, "!include", 8) == 0 ) {
            includeFile(fname, buf + 9);
         } else if ( isalpha(*buf) ) {
            char *msg = strchr(buf, ' ');
            if ( msg ) {
               *msg++ = '\0';
               while ( msg && *msg == ' ' )
                  msg++;
            }
            new0 cMessage(buf, msg);
         }
      }
      return true;
   }

   file_not_found++;
   return false;
}

bool cMessage::includeFile(const char *from_fname, const char *incl_fname)
{
   while ( *incl_fname == ' ' )
      incl_fname++;

   if ( readFile(incl_fname) )
      return true;

   bool rc = false;

   #if defined __ECL_VCPP__
      char drive[_MAX_DRIVE], dir[_MAX_DIR];
      _splitpath(from_fname, drive, dir, 0, 0);
      char inc_dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
      _splitpath(incl_fname, 0, inc_dir, fname, ext);
      char incl_fname2[_MAX_PATH]; strcat(dir, inc_dir);
      _makepath(incl_fname2, drive, dir, fname, ext);
      file_not_found--;
      rc = readFile(incl_fname2);
   #endif

   return rc;
}

void cMessage::add(cErrBase::ERR_TYPE code, const char *msg)
{
   cMessage::code = code;

   if ( msg && (cMessage::msg = new0 (char[strlen(msg)+1])) != 0 ) {
      strcpy(cMessage::msg, msg);
   } else {
      cMessage::msg = 0;
   }

   next = 0;

   if ( !first )
      first = this;

   if ( !last ) {
      last = this;
   } else {
      last->next = this;
      last = this;
   }
}

cMessage * cMessage::find(cErrBase::ERR_TYPE code)
{
   for ( cMessage *m = first ; m ; m = m->next ) {
      if ( m->code == code )
         return m;
   }

   return 0;
}




// Implementierung cErrBase
// ===========================================================================

/**
 * Lesen der Fehlermeldungsdatei erzwingen.
 *
 * Normalerweise wird die Fehlermeldungsdatei beim ersten Formatieren
 * einer Fehlermeldung gelesen. Durch Aufruf dieser statischen Funktion
 * kann das Lesen der Fehlermeldungsdatei zu einem definierten Zeitpunkt
 * erzwungen werden.
 */
void cErrBase::initialize()
{
   cMessage::initialize();
}

void cErrBase::ealloc(ERR_TYPE err)
{
   if ( (xerr = new0 XERR) != 0 ) {
      xerr->err_code = err;
      xerr->refc = 1;
      for ( int i = 0 ; i < sizeof xerr->param / sizeof xerr->param[0] ; i++ )
         xerr->param[i] = 0;
   }
}

void cErrBase::eclone(const cErrBase &other)
{
   xerr = other.xerr;
   if (xerr != 0) {
      xerr->refc++;
   }
}

void cErrBase::efree()
{
   if ( xerr != 0 && --xerr->refc == 0 ) {
      for ( int i = 0 ; i < sizeof xerr->param / sizeof xerr->param[0] ; i++ ) {
         delete[] xerr->param[i];
      }
      delete xerr;
   }
}


// Ausgabe
// =======

std::ostream& operator<<(std::ostream& os, cErrBase const& err)
{
   char buf[1024] = "";
   return os << err.getString(buf, sizeof buf);
}

void cErrBase::DbgOut(const char *add_text) const
{
   char buf[1024] = "";
   getString(buf, sizeof buf, add_text);
   __ECL_RELEASE_TEXT__(cBase::dbgBase | cBase::dbgError, buf);
}


// Umwandlung
// ==========

void cErrBase::catMsg(char *& buf, size_t& size, const char *msg, size_t max) const
{
   if ( buf && size && msg ) {
      if ( max == 0 )
         max = strlen(msg);
      size_t len = size-1 < max ? size-1 : max;
      strxcpy(buf, msg, len+1); size -= len; buf += len;
   }
}

void cErrBase::fmtMsg(char *& buf, size_t& size, const char *msg) const
{
   const char *msg2;

   while ( size && (msg2 = strchr(msg, '$')) != 0 ) {
      if ( msg2 > msg )
         catMsg(buf, size, msg, msg2 - msg); msg = msg2 + 1;
      if ( *msg == '$' ) {
         catMsg(buf, size, "$"); msg++;
      } else if ( *msg == '\0' ) {
         catMsg(buf, size, "$");
      } else if ( isdigit(*msg) ) {
         int p = *msg++ - '1';
         if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
            if ( *msg == '{' && strchr(msg, '}') ) {
               size_t len = strchr(msg, '}') - msg; msg++;
               if ( xerr->param[p] ) {
                  char cond[512]; strxcpy(cond, msg, len);
                  fmtMsg(buf, size, cond);
               }
               msg += len;
            } else if ( xerr->param[p] ) {
               catMsg(buf, size, xerr->param[p]);
            }
         }
      }
   }

   if ( size && *msg )
      catMsg(buf, size, msg);
}

const char *cErrBase::getString(char *buffer, size_t size, const char *add_text) const
{
   char *buf = buffer;

   cMessage::initialize();

   size_t len = cMessage::convCode2Str(buf, xerr?xerr->err_code:errNoError, size);
   size -= len; buf += len;

   if ( add_text && size > 4 ) {
      catMsg(buf, size, ": ");
      catMsg(buf, size, add_text);
   }

   if ( size > 4 ) {
      cMessage *msg = cMessage::find(xerr?xerr->err_code:errNoError);
      const char *text;

      if ( msg && msg->getMsg() ) {
         text = msg->getMsg();
      } else if (cMessage::getFileNotFound()) {
         text = "<message file not found>$1{ P1=$1}$2{ P2=$2}$3{ P3=$3}$4{ P4=$4}";
      } else {
         text = "<no message text found>$1{ P1=$1}$2{ P2=$2}$3{ P3=$3}$4{ P4=$4}";
      };
      catMsg(buf, size, ": ");
      fmtMsg(buf, size, text);
   }

   return buffer;
}


// Setzen und erfragen von Fehlerparametern
// ========================================

void cErrBase::setParam(int p, char ch)
{
   if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      if ( (xerr->param[p] = new0 (char[2])) != 0 ) {
         xerr->param[p][0] = ch;
         xerr->param[p][1] = '\0';
      }
   }
}

void cErrBase::setParam(int p, const char *txt)
{
   if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      if ( txt && (xerr->param[p] = new0 (char[strlen(txt)+1])) != 0 ) {
         strcpy(xerr->param[p], txt);
      } else {
         xerr->param[p] = 0;
      }
   }
}

void cErrBase::setParam(int p, long num, NUM_FMT fmt)
{
   if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      char buf[64];
      switch ( fmt ) {
       case fmtDec:  sprintf(buf, "%ld", num); break;
       case fmtHex:  sprintf(buf, "%lx", num); break;
       default:      strcpy(buf, "0?"); break;
      }
      if ( (xerr->param[p] = new0 (char[strlen(buf)+1])) != 0 )
         strcpy(xerr->param[p], buf);
   }
}

void cErrBase::setParam(int p, void *ptr)
{
   if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      char buf[64];
      sprintf(buf, "%p", ptr);
      if ( (xerr->param[p] = new0 (char[strlen(buf)+1])) != 0 )
         strcpy(xerr->param[p], buf);
   }
}

const char *cErrBase::getParam(int p) const
{
   if ( xerr != 0 && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      return xerr->param[p];
   } else {
      return 0;
   }
}




}; // namespace ecl


