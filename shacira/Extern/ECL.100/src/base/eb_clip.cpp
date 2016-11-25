// ===========================================================================
// eb_clip.cpp                                   ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cClipboard        - Verwaltung des Clipboards.
//     |
//     +-cClipboardData    - Verwaltung von Daten fuer das Clipboard.
//
//    cClipboardFormat     - Beschreibung des Clipboard-Formates.
//
// ===========================================================================

#include "base/eb_clip.hpp"
#include "base/eb_array.hpp"
#include "base/eb_thread.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"

#endif /*__INTERFACE__*/



#ifdef __INTERFACE__

// ===========================================================================
// Definition cClipboardFormat
// ---------------------------------------------------------------------------
//
//  cClipboardFormat
//
// ===========================================================================

class __ECL_DLLEXPORT__ cClipboardFormat {

public:

   // Default-Konstruktor
   inline cClipboardFormat()
      { version = 0; }
   // Konstruktor
   inline cClipboardFormat(const cString& fmt, int ver = 0)
      { format = fmt; version = ver; }
   // Copy-Konstruktor
   inline cClipboardFormat(const cClipboardFormat& other)
      { format = other.format; version = other.version; }

   // Zuweisungsoperator
   cClipboardFormat& operator=(const cClipboardFormat& other)
      { format = other.format; version = other.version; return *this; }


   // Attribute
   // =========

   // Formatkennung erfragen
   inline cString getFormat() const
      { return format; }
   // Versionsnummer erfragen
   inline int getVersion() const
      { return version; }


   // Vergleich
   // =========

   // Vergleich zweiter Formate
   int compare(const cClipboardFormat& other) const;

   // Vergleichsoperatoren
   bool operator==(const cClipboardFormat& other) const
      { return compare(other) == 0; }
   bool operator!=(const cClipboardFormat& other) const
      { return compare(other) != 0; }
   bool operator<(const cClipboardFormat& other) const
      { return compare(other) <  0; }
   bool operator>(const cClipboardFormat& other) const
      { return compare(other) >  0; }
   bool operator<=(const cClipboardFormat& other) const
      { return compare(other) <= 0; }
   bool operator>=(const cClipboardFormat& other) const
      { return compare(other) >= 0; }


   // Standardformate
   // ===============

   // Undefiniertes Format
   static cClipboardFormat getFmtUndef();
   // Standard-TEXT-Format
   static cClipboardFormat getFmtText();
   // Standard-BITMAP-Format
   static cClipboardFormat getFmtBitmap();


private:

   cString format;      // Kennung des Datenformates
   int version;         // Version des Datenformates

};

#endif /*__INTERFACE__*/

// Implementierung cClipboardFormat
// ===========================================================================

int cClipboardFormat::compare(const cClipboardFormat& other) const
{
   int dist = format.compareNoCase(other.format);
   return dist == 0 ? version - other.version : dist;
}

// Standardformate
// ===============

cClipboardFormat cClipboardFormat::getFmtUndef()
{
   static cClipboardFormat fmt_undef(0);
   return fmt_undef;
}

cClipboardFormat cClipboardFormat::getFmtText()
{
   static cClipboardFormat fmt_text(".std_text");
   return fmt_text;
}

cClipboardFormat cClipboardFormat::getFmtBitmap()
{
   cClipboardFormat fmt_bitmap(".std_bitmap");
   return fmt_bitmap;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cClipboardData
// ---------------------------------------------------------------------------
//
// cBase
//  +--cClipboardData
//
// ===========================================================================

class __ECL_DLLEXPORT__ cClipboardData : public cBase {
   friend class cClipboard;

public:

   enum INSERT_TYPE {
      cbiUndef,      // Einfuege-Typ nicht genauer spezifiziert
      cbiNoChange,   // Einfuege-Typ nicht aendern (nur bei reset)
      cbiDrag,       // Daten durch DragSource erzeugt
      cbiCopy,       // Daten durch Copy-To-Clipboard erzeugt
      cbiMove        // Daten durch Move-To-Clipboard erzeugt
   };

   // Default-Konstruktor
   cClipboardData(INSERT_TYPE cbi = cbiUndef);
   // Konstruktor
   cClipboardData(const cClipboardFormat& format, INSERT_TYPE cbi = cbiUndef);
   // Destruktor
   ~cClipboardData();

   // Format der Clipboard-Daten erfragen
   inline cClipboardFormat getFormat() const
      { return format; }
   // Einfuege-Typ erfragen
   inline INSERT_TYPE getInsertType() const
      { return cbi; }

   // Clipboard-Daten loeschen
   void clear();
   // Clipboard-Daten neu initialisieren
   void reset(const cClipboardFormat& format, INSERT_TYPE cbi = cbiNoChange);

   // String-Objekt zu Clipboard-Daten hinzufuegen
   void addObject(cString signature, cString name, cString text);
   // Daten-Objekt zu Clipboard-Daten hinzufuegen
   void addObject(cString signature, cString name, void *data, int size);

   // Anzahl der Daten-Objekte erfragen
   int getObjectCount() const;
   // Signatur des Daten-Objektes an Position 'n' erfragen
   cString getObjectSignature(int n) const;
   // Name des Daten-Objektes an Position 'n' erfragen
   cString getObjectName(int n) const;

   // String-Objekt an Position 'n' erfragen
   cString getObjectDataStr(int n) const;
   // Groesse des Daten-Objektes an Position 'n' erfragen
   int getObjectDataSize(int n) const;
   // Zeiger auf Daten des Daten-Objektes an Position 'n' erfragen
   void *getObjectDataPtr(int n) const;
   // Daten des Daten-Objektes an Position 'n' erfragen
   bool getObjectData(int n, void *buf, int buf_size) const;


public: // should be protected:

   // Intern: Initialisierung aus Clipboard-Textdaten
   bool initFromStreamedText(void *streamed_text);
   // Intern: Initialisierung aus Clipboard-Rohdaten
   bool initFromStreamedData(void *streamed_data);
   // Intern: Format aus Clipboard-Rohdaten ermitteln
   static cClipboardFormat getFormatFromStreamed(void *streamed_data);
   // Intern: Laenge der Clipboard-Rohdaten ermitteln
   int getStreamedDataSize() const;
   // Intern: Laenge der Clipboard-Rohdaten von Objekt 'n' ermitteln
   int getStreamedObjectSize(int n) const;
   // Intern: Erzeugen der Clipboard-Rohdaten
   bool getStreamedData(void *buf) const;
   // Intern: Laenge der Clipboard-Textdaten ermitteln
   int getStreamedTextSize() const;
   // Intern: Erzeugen der Clipboard-Textdaten
   bool getStreamedText(void *buf) const;


private:

   cClipboardFormat format;   // Kennung des Datenformates
   INSERT_TYPE cbi;           // Kennung des Einfuege-Typs

   // Zeiger auf Array mit Clipboard-Datenobjekten
   struct OBJECT_ARRAY;
   OBJECT_ARRAY *objects;

};

#endif /*__INTERFACE__*/


// Implementierung cClipboardData
// ===========================================================================

// Interne Speicherung der Clipboard-Daten-Objekte
// -----------------------------------------------

struct CDOBJECT {
   CDOBJECT(cString sig = 0, cString nam = 0)
      { signature = sig; name = nam; data = 0; size = 0; }
   ~CDOBJECT()
      { delete data; }
   cString signature;
   cString name;
   char *data;
   int size;
};

struct cClipboardData::OBJECT_ARRAY {
   cArray<CDOBJECT,const CDOBJECT&> array;
};

// ---

cClipboardData::cClipboardData(INSERT_TYPE cbi) :
   format(cClipboardFormat::getFmtUndef())
{
   __ECL_ASSERT1__(cbi != cbiNoChange);
   cClipboardData::cbi = cbi;
   cClipboardData::objects = new0 OBJECT_ARRAY;
}

cClipboardData::cClipboardData(const cClipboardFormat& fmt, INSERT_TYPE cbi) :
   format(fmt)
{
   __ECL_ASSERT1__(cbi != cbiNoChange);
   cClipboardData::cbi = cbi;
   cClipboardData::objects = new0 OBJECT_ARRAY;
}

cClipboardData::~cClipboardData()
{
   delete objects;
}

void cClipboardData::clear()
{
   objects->array.removeAll();
}

void cClipboardData::reset(const cClipboardFormat& format, INSERT_TYPE cbi)
{
   objects->array.removeAll();
   cClipboardData::format = format;
   if ( cbi != cbiNoChange )
      cClipboardData::cbi = cbi;
}

void cClipboardData::addObject(cString signature, cString name, cString data)
{
   int n = objects->array.add(CDOBJECT(signature, name));
   int size = data.getLength() + 1;
   objects->array[n].data = new0 char[size];
   objects->array[n].size = size;
   memcpy(objects->array[n].data, Nvl(data, ""), size);
}

void cClipboardData::addObject(cString signature, cString name, void *data, int size)
{
   int n = objects->array.add(CDOBJECT(signature, name));
   objects->array[n].data = new0 char[size];
   objects->array[n].size = size;
   if ( data != 0 && size > 0 )
      memcpy(objects->array[n].data, data, size);
}

int cClipboardData::getObjectCount() const
{
   return objects->array.getSize();
}

cString cClipboardData::getObjectSignature(int n) const
{
   return __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ?
      objects->array[n].signature
    : cString();
}

cString cClipboardData::getObjectName(int n) const
{
   return __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ?
      objects->array[n].name
    : cString();
}

void * cClipboardData::getObjectDataPtr(int n) const
{
   return __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ?
      objects->array[n].data
    : 0;
}

cString cClipboardData::getObjectDataStr(int n) const
{
   return __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ?
      cString((const char *)objects->array[n].data)
    : cString();
}

int cClipboardData::getObjectDataSize(int n) const
{
   return __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ?
      objects->array[n].size
    : 0;
}

bool cClipboardData::getObjectData(int n, void *buf, int buf_size) const
{
   if ( __ECL_ASSERT1__(objects != 0 && n >= 0 && n < objects->array.getSize()) ) {
      memcpy(buf, objects->array[n].data, min(buf_size,objects->array[n].size));
      return true;
   } else {
      return false;
   }
}


// Internas
// ========

// Format des ECL-Clipboard-Formates
// ---------------------------------
//
// 0             32   36                       (36+L1)
// :             :    :                        :
// +-------------+----+------+-------+---------+----+------+-------+---------
// | CBF_ECL_HDR | L1 | SIG1 | NAME1 | OBJECT1 | L2 | SIG2 | NAME2 | OBJ ...
// |             |    |                        |    |
// +-------------+----+------------------------+----+------------------------
//  |             |    |      |       |
//  |             |    |      |       +-- Objekt-Daten
//  |             |    |      +-- Objekt-Name ('\0'-terminiert)
//  |             |    +-- Signatur ('\0'-terminiert)
//  |             +-- Laenge Objekt-Daten (int)
//  +-- Header

struct CBF_ECL_HDR {                // Header:
   char format_name[32];            //  - Name des Formates
   int  version;                    //  - Versionsnummer
   int  obj_count;                  //  - Anzahl folgender Objekte
   cClipboardData::INSERT_TYPE cbi; //  - Einfuege-Typ
};

bool cClipboardData::initFromStreamedText(void *streamed_text)
{
   clear();

   if ( __ECL_ASSERT1__(streamed_text != 0) ) {
      reset(cClipboardFormat::getFmtText());
      addObject(0, 0, (const char*)streamed_text);
      return true;
   }

   return false;
}

bool cClipboardData::initFromStreamedData(void *streamed_data)
{
   clear();

   if ( __ECL_ASSERT1__(streamed_data != 0) ) {
      CBF_ECL_HDR *hdr = (CBF_ECL_HDR*)streamed_data;
      int obj_count = hdr->obj_count;
      reset(cClipboardFormat(hdr->format_name, hdr->version), hdr->cbi);

      char *ptr = (char*)(hdr + 1);
      for ( int i = 0 ; i < obj_count ; i++ ) {
         int len = *((int*)ptr); ptr += sizeof(int);
         char *ptr2 = ptr; ptr += len;
         cString sig = (const char*)ptr2;
         int len_str = sig.getLength() + 1;
         ptr2 += len_str; len -= len_str;
         cString name = (const char*)ptr2;
         len_str = name.getLength() + 1;
         ptr2 += len_str; len -= len_str;
         addObject(sig, name, ptr2, len);
      }

      return true;
   }

   return false;
}

cClipboardFormat cClipboardData::getFormatFromStreamed(void *streamed_data)
{
   if ( __ECL_ASSERT1__(streamed_data != 0) ) {
      CBF_ECL_HDR *hdr = (CBF_ECL_HDR*)streamed_data;
      return cClipboardFormat(hdr->format_name, hdr->version);
   } else {
      return cClipboardFormat::getFmtUndef();
   }
}

int cClipboardData::getStreamedDataSize() const
{
   int size = sizeof(CBF_ECL_HDR);
   int obj_count = getObjectCount();

   for ( int i = 0 ; i < obj_count ; i++ )
      size += getStreamedObjectSize(i);

   return size;
}

int cClipboardData::getStreamedObjectSize(int n) const
{
   return
      sizeof(int)
   +  getObjectSignature(n).getLength() + 1
   +  getObjectName(n).getLength() + 1
   +  getObjectDataSize(n);
}

bool cClipboardData::getStreamedData(void *buf) const
{
   int obj_count = getObjectCount();

   if ( __ECL_ASSERT1__(buf != 0) ) {

      CBF_ECL_HDR *hdr = (CBF_ECL_HDR*)buf;
      strxcpy(hdr->format_name, format.getFormat(), sizeof hdr->format_name);
      hdr->version = format.getVersion();
      hdr->obj_count = obj_count;
      hdr->cbi = cbi;

      char *ptr = (char*)(hdr + 1);
      for ( int i = 0 ; i < obj_count ; i++ ) {
         int sig_size = getObjectSignature(i).getLength() + 1;
         int nam_size = getObjectName(i).getLength() + 1;
         int obj_size = getObjectDataSize(i);
         *((int*)ptr) = sig_size + nam_size + obj_size; ptr += sizeof(int);
         strxcpy(ptr, Nvl(getObjectSignature(i),""), sig_size); ptr += sig_size;
         strxcpy(ptr, Nvl(getObjectName(i),""), nam_size); ptr += nam_size;
         getObjectData(i, ptr, obj_size); ptr += obj_size;
      }

      return true;

   }

   return false;
}

int cClipboardData::getStreamedTextSize() const
{
   return getObjectCount() == 1 ?
      getObjectDataSize(0)
    : 0;
}

bool cClipboardData::getStreamedText(void *buf) const
{
   return __ECL_ASSERT1__(buf != 0 && getStreamedTextSize() > 0) ?
      getObjectData(0, buf, getStreamedTextSize())
    : false;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cClipboard
// ---------------------------------------------------------------------------
//
// cBase
//  +--cClipboard
//
// ===========================================================================

class __ECL_DLLEXPORT__ cClipboard : public cBase {

public:

   // Konstruktor
   cClipboard();
   // Destruktor
   ~cClipboard();

   // Ist das Clipboard geoeffnet?
   bool isOpen() const;
   // Ist das Clipboard leer? (Keine Eintraege in egal welchem Format)
   bool isEmpty() const;
   // Ist ein bestimmtes Format vorhanden?
   bool isAvailable(const cClipboardFormat& format) const;

   // Inhalt des Clipboards loeschen
   void empty();

   // Daten im ECL-Format erfragen
   bool getData(cClipboardData& data);
   // Daten in bestimmtem Format 'format' erfragen
   bool getData(cClipboardData& data, const cClipboardFormat& format);
   // Daten ins Clipboard schreiben (empty_cb = true, CB wird vorher geleert)
   bool setData(const cClipboardData& data, bool empty_cb = true);


private:

   bool is_open;

};

#endif /*__INTERFACE__*/


// Implementierung cClipboard
// ===========================================================================

#if defined __ECL_W32__

   // Unterstuetze Standardformate, wie CF_TEXT, werden uminterpretiert.
   // Ansonsten wird nur der spezielle Typ "CBF_ECL" unterstuetzt.

   // Kennung des registrierten Formates "CBF_ECL"
   __declspec(dllexport) unsigned int EclClipboardFormat()
   {
      static unsigned int cbf_ecl = 0;
      if ( cbf_ecl == 0 ) {
         cbf_ecl = RegisterClipboardFormat("CBF_ECL");
         __ECL_ASSERT2__(cbf_ecl != 0, ("cClipboard: Registering clipboard format failed"));
      }
      return cbf_ecl;
   }

   // Wrapper-Klasse fuer Windows Global Memory Objekte
   class cGlobalMem {
      void *p; HGLOBAL hg;
   public:
      cGlobalMem(HGLOBAL handle)
         { p = GlobalLock(hg = handle); }
      ~cGlobalMem()
         { GlobalUnlock(hg); }
      operator void *()
         { return p; }
   };

#endif

cClipboard::cClipboard()
{
   #if defined __ECL_W32__

      // Try to acquire the clipboard until timeout
      int timeout = 25; // timeout = 25 * 100 ms = 2.5 sec
      while ( (is_open = !!OpenClipboard(NULL)) == false && timeout-- > 0 )
         cThread::sleep(100);
      __ECL_ASSERT2__(is_open, ("cClipboard: Timeout while trying to access the clipboard"));

      // Pre-register our own clipboard format, if not already done
      EclClipboardFormat();

   #else
   #endif
}

cClipboard::~cClipboard()
{
   #if defined __ECL_W32__
      __ECL_ASSERT1__(CloseClipboard());
   #else
   #endif
}

bool cClipboard::isOpen() const
{
   #if defined __ECL_W32__
      return is_open;
   #else
   #endif
}

bool cClipboard::isEmpty() const
{
   #if defined __ECL_W32__
      return EnumClipboardFormats(0) == 0;
   #else
   #endif
}

bool cClipboard::isAvailable(const cClipboardFormat& format) const
{
   #if defined __ECL_W32__
      if ( format == cClipboardFormat::getFmtText() ) {
         return !!IsClipboardFormatAvailable(CF_TEXT);
      } else if ( format == cClipboardFormat::getFmtBitmap() ) {
         return !!IsClipboardFormatAvailable(CF_BITMAP);
      } else if ( IsClipboardFormatAvailable(EclClipboardFormat()) ) {
         HGLOBAL hg = GetClipboardData(EclClipboardFormat());
         if ( __ECL_ASSERT1__(hg != NULL) )
            return format == cClipboardData::getFormatFromStreamed(cGlobalMem(hg));
      }
   #else
   #endif

   return false;
}

void cClipboard::empty()
{
   #if defined __ECL_W32__
      __ECL_ASSERT1__(EmptyClipboard());
   #else
   #endif
}

bool cClipboard::getData(cClipboardData& data)
{
   #if defined __ECL_W32__

      if ( IsClipboardFormatAvailable(EclClipboardFormat()) ) {
         HGLOBAL hg = GetClipboardData(EclClipboardFormat());
         if ( __ECL_ASSERT1__(hg != NULL) )
            return data.initFromStreamedData(cGlobalMem(hg));
      }

   #else
   #endif

   return false;
}

bool cClipboard::getData(cClipboardData& data, const cClipboardFormat& format)
{
   #if defined __ECL_W32__

      if ( format == cClipboardFormat::getFmtText()
        || format == cClipboardFormat::getFmtUndef() )
      {
         if ( IsClipboardFormatAvailable(CF_TEXT) ) {
            HGLOBAL hg = GetClipboardData(CF_TEXT);
            if ( __ECL_ASSERT1__(hg != NULL) )
               return data.initFromStreamedText(cGlobalMem(hg));
         }
      }

      if ( format == cClipboardFormat::getFmtBitmap()
        || format == cClipboardFormat::getFmtUndef() )
      {
         if ( IsClipboardFormatAvailable(CF_BITMAP) ) {
            // ...
         }
      }

   #else
   #endif

   return getData(data);
}

bool cClipboard::setData(const cClipboardData& data, bool empty_cb)
{
   if ( empty_cb )
      empty();

   cClipboardFormat format = data.getFormat();

   #if defined __ECL_W32__

      if ( format == cClipboardFormat::getFmtText() ) {

         int size = data.getStreamedTextSize();
         if ( size > 0 ) {
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, size);
            if ( __ECL_ASSERT1__(hg != NULL) ) {
               data.getStreamedText(cGlobalMem(hg));
               SetClipboardData(CF_TEXT, hg);
               // GlobalFree durch SetClipboardData!!!
               return true;
            }
         }

      } else if ( format == cClipboardFormat::getFmtBitmap() ) {

         // ...

      } else if ( !format.getFormat().isEmpty() ) {

         int size = data.getStreamedDataSize();
         if ( size > 0 ) {
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, size);
            if ( __ECL_ASSERT1__(hg != NULL) ) {
               data.getStreamedData(cGlobalMem(hg));
               SetClipboardData(EclClipboardFormat(), hg);
               // GlobalFree durch SetClipboardData!!!
               return true;
            }
         }

      }

   #else
   #endif

   return false;
}

