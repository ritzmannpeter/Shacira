// ===========================================================================
// es_base.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage  - Basisklasse fuer Storage- und Abfrageklassen.
//
// ===========================================================================

#include "store/es_base.hpp"
#include <stdio.h>




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_object.hpp"
#include "base/eb_res.hpp"
#include "base/eb_time.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csBaseStorage
// ---------------------------------------------------------------------------
//
// Basisklasse fuer alle Storage- und Abfrageklassen. Die "permanent"-Eigen-
// schaft wird von den csBaseStorage-Verbraucher-Klassen dazu benutzt, beim
// Loeschen ihrer selbst zu entscheiden, ob die csBaseStorage-Klasse ebenfalls
// geloescht werden darf (bzw. muss).
//
// cBase
//  +--csBaseStorage
//
// ===========================================================================

class __ECL_DLLEXPORT__ csBaseStorage : public cEclObject {
   ECL_DECLARE(csBaseStorage,cEclObject)

public:

   // Default-Konstruktor
   csBaseStorage();
   // Konstruktor ueber 'flags'
   csBaseStorage(int _flags);
   // Copy-Konstruktor
   csBaseStorage(const csBaseStorage& other);
   // Destruktor
   virtual ~csBaseStorage();


   // Typen
   // =====

   enum TYPE {
      tNone,       // Nicht spezifizierter Typ
      tInt,        // Integer-Zahl
      tDouble,     // Fliesspunkt-Zahl
      tTime,       // Uhrzeit
      tDate,       // Datum
      tDateTime,   // Datum und Uhrzeit (Timestamp)
      tWeek,       // Kalenderwoche
      tChar,       // Zeichen
      tString,     // String
      tIcon,       // Icon
      tBitmap,     // Bitmap
      tUser        // Benutzerdefinierter Typ
   };


   // Flags
   // =====

   enum FLAGS { fStart = 1,
      fPermanent   = fStart << 0,  // Objekt nicht automatisch loeschen
      fUser        = fStart << 1   // Benutzerdefinierte Flags
   };

   // Storage-Flags setzen (oder ruecksetzen)
   void setFlags(int mask, bool set = true);
   // Storage-Flags ruecksetzen
   inline void resetFlags(int mask)
      { setFlags(mask, false); }
   // Storage-Flags ermitteln
   inline int getFlags(int mask) const
      { return onGetFlags(mask); }

   // Darf dieses Objekt NICHT automatisch geloescht werden?
   inline bool isPermanent() const
      { return flags & fPermanent; }


   // Zahlen-Formatierung
   // ===================

   // Integer-Wert formatieren
   static void formatValue(char *buf, int value,
                           int width = 11, int prec = 0,
                           bool thsnd_sep = false, bool pad_left = false);

   // Double-Wert formatieren
   static void formatValue(char *buf, double value,
                           int width = 21, int prec = -1,
                           bool thsnd_sep = true, bool pad_left = false);


protected:

   // Kopieren von einem anderen csBaseStorage-Objekt
   inline void copyFrom(const csBaseStorage& other)
      { flags = other.flags; }

   // Sichern der Flags
   inline int saveFlags() const
      { return flags; }
   // Sichern der Flags
   inline void restoreFlags(int orig_flags)
      { flags = orig_flags; }


   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um Storage-Flags zu erfragen
   virtual int onGetFlags(int mask) const;


private:

   int flags;

};

#endif /*__INTERFACE__*/


// Implementierung csBaseStorage
// ===========================================================================

csBaseStorage::csBaseStorage()
{
   flags = 0;
}

csBaseStorage::csBaseStorage(int _flags)
{
   flags = _flags;
}

csBaseStorage::csBaseStorage(const csBaseStorage& other)
{
   flags = other.flags;
}

csBaseStorage::~csBaseStorage()
{
}

void csBaseStorage::setFlags(int mask, bool set)
{
   if ( set ) {
      flags |= mask;
   } else {
      flags &= ~mask;
   }
}

int csBaseStorage::onGetFlags(int mask) const
{
   return flags & mask;
}


// Formatierung
// ============

void csBaseStorage::formatValue(char *buf, int value, int width, int prec, bool thsnd_sep, bool pad_left)
{
   if ( thsnd_sep ) {
      cString::convDbl2Str(buf, double(value), prec);
   } else if ( pad_left ) {
      sprintf(buf, "%0*d", width, value);
   } else {
      sprintf(buf, "%d", value);
   }
}

void csBaseStorage::formatValue(char *buf, double value, int width, int prec, bool thsnd_sep, bool pad_left)
{
   if ( thsnd_sep ) {
      cString::convDbl2Str(buf, value, prec);
   } else if ( pad_left ) {
      if ( prec >= 0 ) {
         sprintf(buf, "%0*.*g", width, prec, value);
      } else {
         sprintf(buf, "%0*g", width, value);
      }
   } else {
      if ( prec >= 0 ) {
         sprintf(buf, "%.*lf", prec, value);
      } else {
         sprintf(buf, "%g", value);
      }
   }
}

