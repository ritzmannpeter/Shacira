// ===========================================================================
// es_store.cpp                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csStorage         - Beschreibung eines Speicherortes.
//           |
//           +-csNoStorage    - Keine Speicherung (Dummy).
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <ctype.h>                               /* String functions       */

#include "store/es_store.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_event.hpp"
#include "store/es_base.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csStorage
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//
// ===========================================================================

class __ECL_DLLEXPORT__ csStorage : public csBaseStorage, public cEventSource {
   ECL_DECLARE(csStorage,csBaseStorage)

public:

   // Default-Konstruktor
   csStorage();
   // Initialisierung ueber TYPE
   csStorage(TYPE type, int flags = 0);
   // Initialisierung ueber TYPE, width und prec
   csStorage(TYPE type, int width, int prec, int flags = 0);
   // Copy-Konstruktor
   csStorage(const csStorage& other);


   // Flags
   // =====

   enum FLAGS { fStart = csBaseStorage::fUser,
      fNotNull     = fStart << 0,  // Objekt darf nicht NULL sein
      fModified    = fStart << 1,  // Feldinhalt wurde geaendert
      fLeftPad     = fStart << 2,  // Zahlen links mit 0en auffuellen
      fRightPad    = fStart << 3,  // Zahlen rechts mit 0en auffuellen
      fThousandSep = fStart << 4,  // Zahlen mit Tausender-Separator
      fUpcaseOnly  = fStart << 5,  // Nur Grossbuchstaben zulassen
      fLowcaseOnly = fStart << 6,  // Nur Kleinbuchstaben zulassen
      fIsWeek      = fStart << 7,  // Datum als Kalenderwoche interpretieren
      fDeleteBuf   = fStart << 8,  // Pufferspeicher im Destruktor freigeben
      fDispFixLen  = fStart << 9,  // Feste Anzeigebreite (not yet supported)
      fStoreFixLen = fStart << 10, // Feste Laenge bei Speicherung (z.B. SQL-CHAR(n))
      fUser        = fStart << 11  // Benutzerdefinierte Flags
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cEventSource::evtUser,
      evtValueModified,       // (EVFUNC) Wert der Storage hat sich geaendert
      evtUser                 // Ab hier benutzerdefinierte Events
   };


   // Eigenschaften
   // =============

   // Typ erfragen
   inline TYPE getType() const
      { return onGetType(); }
   // Anzeigebreite erfragen
   inline int getWidth() const
      { return onGetWidth(); }
   // Anzahl Nachkommastellen erfragen
   inline int getPrec() const
      { return onGetPrec(); }

   // Anzeigebreite setzen
   inline void setWidth(int width)
      { csStorage::width = width; }
   // Anzahl Nachkommastellen setzen
   inline void setPrec(int prec)
      { csStorage::prec = prec; }

   // Sind keine NULL-Werte erlaubt?
   inline bool isNotNull() const
      { return !!getFlags(fNotNull); }
   // Sind NULL-Werte erlaubt?
   inline bool isNullable() const
      { return !getFlags(fNotNull); }
   // Feld links vom Dezimalpunkt bis Anzeigebreite aufgefuellt?
   inline bool isLeftPadded() const
      { return !!getFlags(fLeftPad); }
   // Feld rechts vom Dezimalpunkt bis Anzeigebreite aufgefuellt?
   inline bool isRightPadded() const
      { return !!getFlags(fRightPad); }
   // Tausender-Separator
   inline bool hasThousandSep() const
      { return !!getFlags(fThousandSep); }


   // Werte erfragen
   // ==============

   // Wert evtl. neu laden
   inline bool refetch()
      { return onRefetch(); }

   // Ermittelt den int-Wert
   inline bool get(int& buf) const
      { return onGetInt(buf); }
   // Ermittelt den double-Wert
   inline bool get(double& buf) const
      { return onGetDouble(buf); }
   // Ermittelt den cTime-Wert
   inline bool get(cTime& buf) const
      { return onGetTime(buf); }
   // Ermittelt den cDate-Wert
   inline bool get(cDate& buf) const
      { return onGetDate(buf); }
   // Ermittelt den cDateTime-Wert
   inline bool get(cDateTime& buf) const
      { return onGetDateTime(buf); }
   // Ermittelt den char-Wert
   inline bool get(char& buf) const
      { return onGetChar(buf); }
   // Ermittelt den cString-Wert
   inline bool get(cString& buf) const
      { return onGetString(buf); }


   // Werte setzen
   // ============

   // int-Wert schreiben
   inline bool put(int buf)
      { return onPutInt(buf); }
   // double-Wert schreiben
   inline bool put(double buf)
      { return onPutDouble(buf); }
   // cTime-Wert schreiben
   inline bool put(cTime buf)
      { return onPutTime(buf); }
   // cDate-Wert schreiben
   inline bool put(cDate buf)
      { return onPutDate(buf); }
   // cDateTime-Wert schreiben
   inline bool put(cDateTime buf)
      { return onPutDateTime(buf); }
   // char-Wert schreiben
   inline bool put(char buf)
      { return onPutChar(buf); }
   // cString-Wert schreiben
   inline bool put(const char *buf)
      { return onPutString(buf); }


   // Pufferspeicher
   // ==============
   // Ist der Pufferspeicher kompatibel und vorhanden, kann ein Benutzer
   // folgendermassen auf den Pufferinhalt zugreifen:
   //
   //    csStorage *store = ...;
   //    if ( store->isBufferCompatible() ) {
   //       UEBERGABETYP var;
   //       *((UEBERGABETYP*)store->getBuffer()) = var;
   //       var = *((UEBERGABETYP*)store->getBuffer());
   //    }

   // Hat die Storage einen eigenen Pufferspeicher?
   inline bool hasBuffer() const
      { return !!(onGetBufferStyle() & bstPresent); }
   // Ist der Puffer vorhanden UND kompatibel zum Uebergabetyp?
   inline bool isBufferCompatible() const
      { return (onGetBufferStyle() & (bstPresent|bstCompatible)) == (bstPresent|bstCompatible); }
   // Adresse des Pufferspeichers ermitteln
   inline void *getBuffer()
      { return onGetBuffer(); }
   // Puffergroesse in Bytes ermitteln (auch wenn kein eigener Pufferspeicher!)
   inline int getBufferSize() const
      { return onGetBufferSize(); }


   // Sonstiges
   // =========

   // Maximale Laenge fuer Eingabemaske ermitteln
   inline int getMaskLength() const
      { return onGetMaskLength(); }

   // Modus "Ueberschreiben" erzwingen?
   inline bool forceOverwrite() const
      { return onCheckForceOverwrite(); }
   // Modus "Grossbuchstaben" erzwingen?
   inline bool forceUppercase() const
      { return onCheckForceUppercase(); }
   // Modus "Kleinbuchstaben" erzwingen?
   inline bool forceLowercase() const
      { return onCheckForceLowercase(); }

   // Automatisches Zeichen an Maskenposition 'pos' ermitteln
   inline char getAutomaticChar(int pos) const
      { return onGetAutomaticChar(pos); }
   // Ist 'ch' an Maskenposition 'pos' ein erlaubtes Zeichen?
   inline bool isAllowedChar(int pos, char ch) const
      { return onCheckAllowedChar(pos, ch); }

   // Ist das Feld Read-Only (keine Aenderungen moeglich)?
   inline bool isReadOnly() const
      { return onCheckReadOnly(); }

   // Enthaelt das Feld einen NULL-Wert?
   inline bool isNull() const
      { return onCheckNull(); }
   // NULL-Zustand setzen
   inline void setNull()
      { setNull(true); }
   // Modifizieren des NULL-Zustandes
   inline void setNull(bool null)
      { onSetNull(null);
        signalModify(); }


protected:

   // Zusaetzliche Events
   // ===================

   // Eigenschaften
   // -------------

   // Wird aufgerufen, um den Typ des Feldes zu erfragen
   virtual TYPE onGetType() const;
   // Wird aufgerufen, um die Anzeigebreite des Feldes zu erfragen
   virtual int onGetWidth() const;
   // Wird aufgerufen, um die Anzahl Nachkommstellen des Feldes zu erfragen
   virtual int onGetPrec() const;


   // Werte erfragen
   // --------------

   // Wird aufgerufen, um den Wert evtl. neu zu laden
   virtual bool onRefetch();

   // Wird aufgerufen, um einen int-Wert zu lesen
   virtual bool onGetInt(int& buf) const;
   // Wird aufgerufen, um einen double-Wert zu lesen
   virtual bool onGetDouble(double& buf) const;
   // Wird aufgerufen, um einen cTime-Wert zu lesen
   virtual bool onGetTime(cTime& buf) const;
   // Wird aufgerufen, um einen cDate-Wert zu lesen
   virtual bool onGetDate(cDate& buf) const;
   // Wird aufgerufen, um einen cDateTime-Wert zu lesen
   virtual bool onGetDateTime(cDateTime& buf) const;
   // Wird aufgerufen, um einen char-Wert zu lesen
   virtual bool onGetChar(char& buf) const;
   // Wird aufgerufen, um einen cString-Wert zu lesen
   virtual bool onGetString(cString& buf) const = 0;


   // Werte setzen
   // ------------

   // Wird aufgerufen, um einen int-Wert zu schreiben
   virtual bool onPutInt(int buf);
   // Wird aufgerufen, um einen double-Wert zu schreiben
   virtual bool onPutDouble(double buf);
   // Wird aufgerufen, um einen cTime-Wert zu schreiben
   virtual bool onPutTime(cTime buf);
   // Wird aufgerufen, um einen cDate-Wert zu schreiben
   virtual bool onPutDate(cDate buf);
   // Wird aufgerufen, um einen cDateTime-Wert zu schreiben
   virtual bool onPutDateTime(cDateTime buf);
   // Wird aufgerufen, um einen char-Wert zu schreiben
   virtual bool onPutChar(char buf);
   // Wird aufgerufen, um einen cString-Wert zu schreiben
   virtual bool onPutString(cString buf) = 0;


   // Pufferspeicher
   // --------------

   // Beschreibung des Puffers
   enum BUFFER_STYLE {
      bstPresent           = 0x0001,   // Puffer vorhanden?
      bstCompatible        = 0x0002    // Puffer kompatibel zum Uebergabetyp?
   };

   // Wird aufgerufen, um die Adresse des Pufferspeichers zu ermitteln
   virtual void *onGetBuffer();
   // Wird aufgerufen, um Puffergroesse (Bytes) ermitteln
   virtual int onGetBufferSize() const;
   // Pruefen, ob der Pufferspeicher kompatibel zum Uebergabetyp ist
   virtual int onGetBufferStyle() const;


   // Sonstiges
   // ---------

   // Maximale Laenge fuer Eingabemaske ermitteln
   virtual int onGetMaskLength() const;

   // Wird aufgerufen, um den Modus "Ueberschreiben" zu ermitteln
   virtual bool onCheckForceOverwrite() const;
   // Wird aufgerufen, um den Modus "Grossbuchstaben" zu ermitteln
   virtual bool onCheckForceUppercase() const;
   // Wird aufgerufen, um den Modus "Kleinbuchstaben" zu ermitteln
   virtual bool onCheckForceLowercase() const;

   // Wird aufgerufen, um das automatische Zeichen an Position 'pos' zu ermitteln
   virtual char onGetAutomaticChar(int pos) const;
   // Wird aufgerufen, um zu pruefen, ob 'ch' an 'pos' erlaubt ist
   virtual bool onCheckAllowedChar(int pos, char ch) const;

   // Wird aufgerufen, um zu pruefen, ob das Feld Read-Only ist
   virtual bool onCheckReadOnly() const
      { return false; }

   // Wird aufgerufen, um zu pruefen, ob das Feld einen NULL-Wert enthaelt
   virtual bool onCheckNull() const = 0;
   // Wird aufgerufen, um den NULL-Zustand zu setzen
   virtual void onSetNull(bool null) = 0;


protected:

   // Kopieren der Basisklasse
   void copyFrom(const csStorage& other)
      { csBaseStorage::copyFrom(other);
        type = other.type;
        width = other.width;
        prec = other.prec; }
   // Setzen der Typinformationen
   void setType(TYPE _type)
      { type = _type; }
   // Aenderung des Wertes signalisieren
   void signalModify()
      { callEvent(evtValueModified);
        setFlags(fModified); }

private:
   TYPE type;
   int width, prec;

};

#endif /*__INTERFACE__*/


// Implementierung csStorage
// ===========================================================================

csStorage::csStorage() :
   csBaseStorage(), cEventSource()
{
   type = tNone;
   width = prec = 0;
}

csStorage::csStorage(TYPE type, int flags) :
   csBaseStorage(flags), cEventSource()
{
   csStorage::type = type;

   switch ( type ) {
    case tInt:     width = 11; prec = 0; break;
    case tDouble:  width = 15; prec = 3; setFlags(fThousandSep); break;
    default:       width = 0; prec = 0; break;
   }
}

csStorage::csStorage(TYPE type, int width, int prec, int flags) :
   csBaseStorage(flags), cEventSource()
{
   csStorage::type = type;
   csStorage::width = width;
   csStorage::prec = prec;
}

csStorage::csStorage(const csStorage& other) :
   csBaseStorage(other), cEventSource()
{
   type = other.type;
   width = other.width;
   prec = other.prec;
}


// Zusaetzliche Events
// ===================


// Eigenschaften
// -------------

csBaseStorage::TYPE csStorage::onGetType() const
{
   return type;
}

int csStorage::onGetWidth() const
{
   return width;
}

int csStorage::onGetPrec() const
{
   return prec;
}


// Werte erfragen
// --------------

bool csStorage::onRefetch()
{
   return true;
}

bool csStorage::onGetInt(int& buf) const
{
   bool rc = false;
   cString str;

   //int orig_flags = saveFlags();
   //resetFlags(fLeftPad|fRightPad|fThousandSep);

   if ( onGetString(str) ) {
      buf = atoi(str);
      rc = true;
   }

   //restoreFlags(orig_flags);
   return rc;
}

bool csStorage::onGetDouble(double& buf) const
{
   bool rc = false;
   cString str;

   //int orig_flags = saveFlags();
   //resetFlags(fLeftPad|fRightPad|fThousandSep);

   if ( onGetString(str) ) {
      buf = atof(str);
      rc = true;
   }

   //restoreFlags(orig_flags);
   return rc;
}

bool csStorage::onGetTime(cTime& buf) const
{
   bool rc = false;
   cString str;

   if ( onGetString(str) ) {
      buf = cTime(str);
      rc = true;
   }

   return rc;
}

bool csStorage::onGetDate(cDate& buf) const
{
   bool rc = false;
   cString str;

   if ( onGetString(str) ) {
      buf = cDate(str);
      rc = true;
   }

   return rc;
}

bool csStorage::onGetDateTime(cDateTime& buf) const
{
   bool rc = false;
   cString str;

   if ( onGetString(str) ) {
      buf = cDateTime(str);
      rc = true;
   }

   return rc;
}

bool csStorage::onGetChar(char& buf) const
{
   cString str;

   if ( onGetString(str) && !str.isEmpty() ) {
      buf = str[0];
      return true;
   }

   return false;
}


// Werte setzen
// ------------

bool csStorage::onPutInt(int buf)
{
   return onPutString(Str(buf));
}

bool csStorage::onPutDouble(double buf)
{
   return onPutString(Str(buf));
}

bool csStorage::onPutTime(cTime buf)
{
   return onPutString(buf.getStr());
}

bool csStorage::onPutDate(cDate buf)
{
   return onPutString(buf.getStr());
}

bool csStorage::onPutDateTime(cDateTime buf)
{
   return onPutString(buf.getStr());
}

bool csStorage::onPutChar(char buf)
{
   return onPutString(Str(buf));
}


// Pufferspeicher
// --------------

void * csStorage::onGetBuffer()
{
   // Default: Kein eigener Pufferspeicher
   return 0;
}

int csStorage::onGetBufferSize() const
{
   // Default: Puffergroesse = Groessen der Uebergabetypen

   switch ( getType() ) {
    case tInt:      return sizeof(int);
    case tDouble:   return sizeof(double);
    case tTime:     return sizeof(cTime);
    case tDate:     return sizeof(cDate);
    case tDateTime: return sizeof(cDateTime);
    case tWeek:     return sizeof(cDate);
    case tChar:     return sizeof(char);
    case tString:   return 30; // Willkuerlicher Default-Wert
   }

   return 0;
}

int csStorage::onGetBufferStyle() const
{
   // Default: Puffer nicht vorhanden und inkompatibel
   return 0;
}


// Sonstiges
// ---------

int csStorage::onGetMaskLength() const
{
   switch ( getType() ) {
    case tInt:      return getWidth();
    case tDouble:   return getWidth();
    case tTime:     return 8;    // HH:MM:SS
    case tDate:     return 10;   // DD.MM.YYYY
    case tDateTime: return 19;   // DD.MM.YYYY HH:MM:SS
    case tWeek:     return 10;   // KW WW/YYYY
    case tChar:     return 1;
    case tString:   return getBufferSize() - 1;
   }

   return 0;
}

bool csStorage::onCheckForceOverwrite() const
{
   switch ( getType() ) {
    case tTime:     return true;
    case tDate:     return true;
    case tDateTime: return true;
    case tWeek:     return true;
   }

   return false;
}

bool csStorage::onCheckForceUppercase() const
{
   switch ( getType() ) {
    case tInt:
    case tDouble:
    case tTime:
    case tDate:
    case tDateTime:
    case tWeek:
      return true;
   }

   return !!getFlags(fUpcaseOnly);
}

bool csStorage::onCheckForceLowercase() const
{
   return !!getFlags(fLowcaseOnly);
}

bool csStorage::onCheckAllowedChar(int pos, char ch) const
{
   TYPE type = getType();
   if ( type == tDate && getFlags(fIsWeek) )
      type = tWeek;

   const char week[] = "KW 09/0009";

   switch ( type ) {
    case tInt:      return ch == '-' || isdigit(ch);
    case tDouble:   return ch == '.' || ch == ',' || ch == '-' || isdigit(ch);
    case tTime:     return !!(pos == 2 || pos == 5 ? (ch==':') : isdigit(ch));
    case tDate:     return !!(pos == 2 || pos == 5 ? (ch=='.') : isdigit(ch));
    case tDateTime: if ( pos == 2 || pos == 5 ) return ch == '.';
                    if ( pos == 13 || pos == 16 ) return ch == ':';
                    return !!(pos == 10 ? (ch==' ') : isdigit(ch));
    case tWeek:     return !!(pos < 3 || pos == 5 ? ch==week[pos] : isdigit(ch));
    case tChar:     return true;
    case tString:   return true;
   }

   return false;
}

char csStorage::onGetAutomaticChar(int pos) const
{
   TYPE type = getType();
   if ( type == tDate && getFlags(fIsWeek) )
      type = tWeek;

   static const char time[] = "__:__:__";
   static const char date[] = "__.__.____";
   static const char dtme[] = "__.__.____ __:__:__";
   static const char week[] = "KW __/____";

   switch ( type ) {
    case tTime:     if ( pos <  8 && time[pos] != '_' ) return time[pos]; break;
    case tDate:     if ( pos < 10 && date[pos] != '_' ) return date[pos]; break;
    case tDateTime: if ( pos < 19 && dtme[pos] != '_' ) return dtme[pos]; break;
    case tWeek:     if ( pos < 10 && week[pos] != '_' ) return week[pos]; break;
   }

   return '\0';
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition csNoStorage
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csNoStorage
//
// ===========================================================================

class __ECL_DLLEXPORT__ csNoStorage : public csStorage {
   ECL_DECLARE(csNoStorage,csStorage)

public:
   csNoStorage() :
      csStorage() { }
   csNoStorage(int flags) :
      csStorage(tNone, flags) { }

protected:

   bool onGetString(cString&) const
      { return false; }
   bool onPutString(cString)
      { return true; }

   int onGetBufferSize() const
      { return 0; }
   int onGetMaskLength() const
      { return 0; }

   bool onCheckNull() const
      { return true; }
   void onSetNull(bool)
      { }

};

#endif /*__INTERFACE__*/


