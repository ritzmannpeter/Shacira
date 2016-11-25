// ===========================================================================
// es_row.cpp                                    ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csRow             -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "store/es_row.hpp"
#include "store/es_field.hpp"
#include "base/eb_array.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csRow
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csRow
//
// ===========================================================================

class __ECL_DLLEXPORT__ csRow : public csBaseStorage, public cEventSource {
   ECL_DECLARE(csRow,csBaseStorage)
   friend class csField;

public:
   // Aktuellen Datensatz aus Query uebernehmen oder neuen Datensatz anlegen
   csRow(csQuery *query, int flags = 0);
   // Ueber cString-'key' definierten Datensatz aus Query erzeugen
   csRow(csQuery *query, cString key, int flags = 0);
   // Copy-Konstruktor
   csRow(const csRow& other);
   // Destruktor
   ~csRow();


   // Flags
   // =====

   enum FLAGS { fStart = csBaseStorage::fUser,
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


   // Allgemeines
   // ===========

   // Liefert den Schluesselwert des Datensatzes
   inline cString getKey() const
      { return key; }
   // Liefert einen Zeiger auf die zugrundeliegende Abfrage
   inline csQuery *getQuery() const
      { return query; }


   // Felder
   // ======

   // Anzahl Felder erfragen
   int getFieldCount() const;
   // Feld erfragen
   csField *getField(int idx) const;


   // Aktuelle Werte lesen
   // ====================

   bool fetch();


   // Transaktionen
   // =============
   // Moegliche Transaktionen auf Datensaetze sind Einfuegen, Bearbeiten und
   // Loeschen. Um eine dieser Varianten zu waehlen, muss in den jeweiligen
   // Transaktionsmodus gewechselt und anschliessend entweder save() oder
   // cancel() aufgerufen werden.
   //
   //    EINFUEGEN, BEARBEITEN:     | EINFUEGEN, LOESCHEN:
   //   ----------------------------+--------------------------
   //    if ( row.edit() ) {        | if ( row.add() ) {
   //       ...                     |    ...
   //       if ( UserSays() == OK ) |    row.save();}
   //          row.save();          | }
   //       else                    | if ( row.remove() ) {
   //          row.cancel();        |    ...
   //    }                          |    row.save();}
   //                               | }

   enum TA_MODE {    // Transaktionsmodus:
      READONLY,      // - Datensatz wird nur gelesen
      RW_INSERT,     // - Datensatz wird eingefuegt
      RW_UPDATE,     // - Datensatz wird bearbeitet
      RW_DELETE,     // - Datensatz wird geloescht
      DELETED        // - Datensatz ist geloescht
   };

   // Aktuellen Transaktionsmodus ermitteln
   TA_MODE getTAMode() const
      { return ta_mode; }

   // Neuen Datensatz hinzufuegen (RW_INSERT)
   bool add();
   // Wechselt in den Bearbeiten-Modus (RW_UPDATE)
   bool edit();
   // Wechselt in den Loesch-Modus (RW_DELETE)
   bool remove();
   // Fuehrt aktuelle Aenderungen durch (Uebernehmen-Funktion)
   bool apply();
   // Speichert aktuelle Aenderungen, zurueck zu READONLY
   bool save();
   // Bricht aktuelle Aenderungen ab, zurueck zu READONLY
   bool cancel();


protected:

   // Hilfsfunktionen fuer abgeleitete Klassen
   // ========================================

   // Schluesselwert des Datensatzes manipulieren (z.B. bei edit oder add)
   void setKey(const cString& new_key);


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, wenn ein Feld zum Datensatz hinzugefuegt wird
   virtual void onFieldAdded(csField *field);

   enum INFO {    // Zusatzinformationen:
      INSERT,     // - Funktion wird waehrend INSERT aufgerufen
      UPDATE,     // - Funktion wird waehrend UPDATE aufgerufen
      DELETE      // - Funktion wird waehrend DELETE aufgerufen
   };

   // Wird aufgerufen, um die Felder des Datensatzes (erneut) einzulesen
   virtual bool onFetch() = 0;
   // Wird aufgerufen, um das Einfuegen zu starten (-> false, falls nicht moeglich)
   virtual bool onAdd() = 0;
   // Wird aufgerufen, um die Bearbeitung zu starten (-> false, falls nicht moeglich)
   virtual bool onEdit() = 0;
   // Wird aufgerufen, um den Datensatz zu loeschen (-> false, falls nicht moeglich)
   virtual bool onRemove() = 0;
   // Wird aufgerufen, um die Aenderungen zu speichern (-> false, falls nicht moeglich)
   virtual bool onSave(INFO commit_info) = 0;
   // Wird aufgerufen, um die Aenderungen zu verwerfen (-> false, falls nicht moeglich)
   virtual bool onCancel(INFO rollback_info) = 0;

   // Wird aufgerufen, um den Beginn einer Transaktion zu markieren
   virtual bool onBeginTA() = 0;
   // Wird aufgerufen, um die letzte (alle) Transaktion(en) zu speichern
   virtual bool onCommitTA(bool commit_all) = 0;
   // wird aufgerufen, um die Transaktion zu verwerfen
   virtual bool onRollbackTA() = 0;


private:

   TA_MODE ta_mode;
   csQuery *query;
   cString key;
   void *fields;

   // Intern: Feld hinzufuegen (fuer csField-Konstruktor)
   int addField(csField *field);
   // Intern: Feld loeschen (fuer csField-Destruktor)
   void removeField(csField *field);

};

#endif /*__INTERFACE__*/


// Implementierung csRow
// ===========================================================================

typedef cArray<csField*,csField*> FIELD_ARRAY;

csRow::csRow(csQuery *query, int flags) :
   csBaseStorage(flags)
{
   csRow::query = query;
   csRow::ta_mode = READONLY;
   csRow::fields = 0;

   if ( query != 0 ) {
      query->requestLock();
      if ( query->hasData() )
         query->get(csQuery::fldKey, key);
   }
}

csRow::csRow(csQuery *query, cString key, int flags) :
   csBaseStorage(flags)
{
   csRow::query = query;
   csRow::ta_mode = READONLY;
   csRow::key = key;
   csRow::fields = 0;

   query->requestLock();
}

csRow::csRow(const csRow& other) :
   csBaseStorage(other)
{
   query = other.query;
   key = other.key;
   ta_mode = other.ta_mode;

   query->requestLock();

   fields = new0 FIELD_ARRAY;
   FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;

   int count = other.getFieldCount();
   fa->setSize(count);

   for ( int i = 0 ; i < count ; i++ )
      (*fa)[i] = other.getField(i);
}

csRow::~csRow()
{
   if ( fields != 0 ) {

      FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;
      int count = fa->getSize();

      for ( int i = 0 ; i < count ; i++ ) {
         csField *field = (*fa)[i];
         if ( field != 0 ) {
            if ( field->getFlags(csField::fPermanent) ) {
               field->unlink(false);
            } else {
               delete field;
            }
         }
      }

      delete (FIELD_ARRAY*)fields;

   }

   query->releaseLock(true);
}


// Felder
// ======

int csRow::addField(csField *field)
{
   if ( fields == 0 )
      fields = new0 FIELD_ARRAY;

   FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;
   int size = fa->getSize() + 1;
   fa->setSize(size);
   (*fa)[size-1] = field;

   onFieldAdded(field);

   return size - 1;
}

void csRow::removeField(csField *field)
{
   if ( __ECL_ASSERT1__(fields != 0) ) {
      FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;
      int count = fa->getSize();
      for ( int i = 0 ; i < count ; i++ )
         if ( (*fa)[i] == field )
            (*fa)[i] = 0;
   }
}

int csRow::getFieldCount() const
{
   FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;
   return fa == 0 ? 0 : fa->getSize();
}

csField * csRow::getField(int idx) const
{
   FIELD_ARRAY *fa = (FIELD_ARRAY*)fields;
   return fa == 0 || idx < 0 || idx >= fa->getSize() ? 0 : (*fa)[idx];
}


// Aktuelle Werte lesen
// ====================

bool csRow::fetch()
{
   return ta_mode == READONLY ? onFetch() : false;
}


// Transaktionen
// =============

bool csRow::add()
{
   if ( ta_mode == READONLY ) {
      key = query->onGetNewRowKey();
      if ( onBeginTA() && onAdd() ) {
         ta_mode = RW_INSERT;
         return true;
      }
   }

   return false;
}

bool csRow::edit()
{
   if ( ta_mode == READONLY && onBeginTA() && onEdit() ) {
      ta_mode = RW_UPDATE;
      return true;
   }

   return false;
}

bool csRow::remove()
{
   if ( ta_mode == READONLY && onBeginTA() && onRemove() ) {
      ta_mode = RW_DELETE;
      return true;
   }

   return false;
}

bool csRow::apply()
{
   switch ( ta_mode ) {

   case READONLY:
      return onCommitTA(true);

   case RW_INSERT:
      if ( onSave(INSERT) && onCommitTA(true) ) {
         query->onRowAdded(this);
         ta_mode = RW_UPDATE;
         return true;
      }
      break;

   case RW_UPDATE:
      if ( onSave(UPDATE) && onCommitTA(true) ) {
         query->onRowChanged(this);
         return true;
      }
      break;

   case RW_DELETE:
      // Apply nicht moeglich
      break;

   }

   return true;
}

bool csRow::save()
{
   switch ( ta_mode ) {

   case READONLY:
      // Nichts zu tun
      return true;

   case RW_INSERT:
      if ( onSave(INSERT) && onCommitTA(false) ) {
         query->onRowAdded(this);
         ta_mode = READONLY;
         return true;
      }
      break;

   case RW_UPDATE:
      if ( onSave(UPDATE) && onCommitTA(false) ) {
         query->onRowChanged(this);
         ta_mode = READONLY;
         return fetch(); // 17.01.2002 -TE- Aktualisierten Datensatz neu laden
      }
      break;

   case RW_DELETE:
      if ( onSave(DELETE) && onCommitTA(false) ) {
         query->onRowRemoved(this);
         ta_mode = DELETED;
         return true;
      }
      break;

   }

   return false;
}

bool csRow::cancel()
{
   switch ( ta_mode ) {

   case READONLY:
      // Nichts zu tun
      return true;

   case RW_INSERT:
      if ( onCancel(INSERT) && onRollbackTA() ) {
         ta_mode = READONLY;
         return true;
      }
      break;

   case RW_UPDATE:
      if ( onCancel(UPDATE) && onRollbackTA()  ) {
         ta_mode = READONLY;
         return true;
      }
      break;

   case RW_DELETE:
      if ( onCancel(DELETE) && onRollbackTA()  ) {
         ta_mode = READONLY;
         return true;
      }
      break;

   }

   return false;
}


// Hilfsfunktionen fuer abgeleitete Klassen
// ========================================

void csRow::setKey(const cString& new_key)
{
   cBase::DbgOut(0, "csRow::setKey(%s -> %s)", (const char *)key, (const char *)new_key);
   key = new_key;
}


// Zusaetzliche Events
// ===================

void csRow::onFieldAdded(csField * /*field*/)
{
}

