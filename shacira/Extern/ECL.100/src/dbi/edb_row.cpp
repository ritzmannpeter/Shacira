// ===========================================================================
// edb_row.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csRow
//           |
//           +-cdbRow         -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <ctype.h>

#include "dbi/edb_row.hpp"
#include "dbi/edb_field.hpp"
#include "dbi/edb_dictionary.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_row.hpp"
#include "dbi/edb_query.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

#ifdef __ECL_DEBUG__
   #define ACTION_TIMEOUT   -1   /* endless */
#else
   #define ACTION_TIMEOUT 7500   /* msec */
#endif

enum ACTIONS {
   ACTION_FETCH,     // Ausfuehren der Aktionen von onFetch()
   ACTION_ADDROW,    // Ausfuehren der Aktionen von onAdd()
   ACTION_EDIT,      // Ausfuehren der Aktionen von onEdit()
   ACTION_REMOVE,    // Ausfuehren der Aktionen von onRemove()
   ACTION_CANCEL,    // Ausfuehren der Aktionen von onCancel()
   ACTION_INSERT,    // Ausfuehren der Aktionen von onSave(INSERT)
   ACTION_UPDATE,    // Ausfuehren der Aktionen von onSave(UPDATE)
   ACTION_DELETE     // Ausfuehren der Aktionen von onSave(DELETE)
};




// Lokale Funktionen
// ===========================================================================

cString AdaptValue(cString value, int fld = -42, csQuery *query = 0)
{
   if ( fld > -42 && query != 0 ) {
      // Quotes abhaengig vom Query-Feldtyp...
      switch ( query->getFieldType(fld) ) {
      case csQuery::tChar:
      case csQuery::tString:
         if ( value[0] != '\'' )
            value = "'" + value + "'";
         break;
      }
   }

   if ( value[0] != '\'' && value[0] != '$' && value[0] != '{' && !isdigit(value[0]) )
      value = "'" + value + "'";

   return value;
}

cString ReplaceKeyVals(cString stmt, SQL::VALUES key_values)
{
   int pos = 0;

   do {
      pos = stmt.getPos("$**");
      if ( pos >= 0 ) {
         cString value = key_values.getValue(atoi(stmt.getMid(pos+3, 1)));
         if ( !__ECL_ASSERT1__(!value.isEmpty()) )
            value = "[ERROR IN SQL STMT]";
         stmt = stmt.getLeft(pos) + value + stmt.getMid(pos+4);
      }
   } while ( pos >= 0 );

   return stmt;
}




// ===========================================================================
// Lokale Klasse cDbDictWrapper
// ---------------------------------------------------------------------------
//
// cDbDictWrapper
//
// ===========================================================================

/*
class cDbDictWrapper {
   cdbDictionary *dict;
public:
   cDbDictWrapper()
      { dict = 0; }
   ~cDbDictWrapper()
      { delete dict; }
   cdbDictionary *getDict(cdbDatabase& db)
      { if ( !dict ) dict = new cdbDictionary(db);
        return dict; }
} DbDict;
*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbRow
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csRow
//         +--cdbRow
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbRow : public csRow, public cdbTAObject {
   ECL_DECLARE(cdbRow,csRow)
   friend class cdbField;

public:
   // Aktuellen Datensatz aus Query uebernehmen oder neuen Datensatz anlegen
   cdbRow(cdbQuery *query, int flags = 0);
   // Ueber cString-'key' definierten Datensatz aus Query erzeugen
   cdbRow(cdbQuery *query, cString key, int flags = 0);
   // Copy-Konstruktor
   cdbRow(const cdbRow& other);
   // Destruktor
   ~cdbRow();


   // Flags
   // =====

   enum FLAGS { fStart = csBaseStorage::fUser,
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


   // Hilfsfunktionen
   // ===============

   // WHERE-Bedingung aus Schluesselnamen und -werten basteln
   static SQL::WHERE makeCondExact(SQL::FIELDS key_fields, SQL::FIELDS key_values, csQuery *query = 0);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Felder des Datensatzes (erneut) einzulesen
   bool onFetch();
   // Wird aufgerufen, um das Einfuegen zu starten (-> false, falls nicht moeglich)
   bool onAdd();
   // Wird aufgerufen, um die Bearbeitung zu starten (-> false, falls nicht moeglich)
   bool onEdit();
   // Wird aufgerufen, um den Datensatz zu loeschen (-> false, falls nicht moeglich)
   bool onRemove();
   // Wird aufgerufen, um die Aenderungen zu speichern (-> false, falls nicht moeglich)
   bool onSave(INFO commit_info);
   // Wird aufgerufen, um die Aenderungen zu verwerfen (-> false, falls nicht moeglich)
   bool onCancel(INFO rollback_info);

   // Wird aufgerufen, um den Beginn einer Transaktion zu markieren
   bool onBeginTA();
   // Wird aufgerufen, um die letzte (alle) Transaktion(en) zu speichern
   bool onCommitTA(bool commit_all);
   // wird aufgerufen, um die Transaktion zu verwerfen
   bool onRollbackTA();


   // Ausfuehrung (aus cdbTAObject)
   // -----------------------------

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   cdbCursorEx *cu_fetch;     // Zeiger auf Fetch-Cursor (oder 0)
   cdbCursor *cu_edit;        // Zeiger auf Edit-Cursor (oder 0)

   SQL::FIELDS key_fields;    // Namen der Schluesselfelder
   SQL::FIELDS fields;        // Namen aller Felder
   SQL::SELECT select;        // SQL-SELECT-String

   cErrBase last_error;       // Zuletzt aufgetretener Fehler
   bool last_rc;              // Ergebnis der letzten DB-Operation

   // Intern: Feld hinzufuegen (fuer cdbField-Konstruktor)
   void addField(cdbField *field);

   // Ausfuehren der Aktionen bei onFetch()
   void execFetch(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onAdd()
   void execAddRow(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onEdit()
   void execEdit(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onSave(INSERT)
   void execInsert(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onSave(UPDATE)
   void execUpdate(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onSave(DELETE)
   void execDelete(cdbDatabase *db);

   // Wird aufgerufen, wenn ta->end() beendet ist
   void onEvtEndTA(void *error);

};

#endif /*__INTERFACE__*/


// Implementierung cdbRow
// ===========================================================================

cdbRow::cdbRow(cdbQuery *query, int flags) :
   csRow(query, flags),
   cdbTAObject(new0 cdbTransaction(*query->getTA())),
   last_error(cErrBase::errNoError)
{
   if ( !query->hasQueryInfos() ) {
      // Try to get some more infos about the query...
      query->open();
      for ( int fld = 0 ; fld < query->getFieldCount() ; fld++ )
         query->getFieldType(fld);
      query->close();
   }

   key_fields = SQL::FIELDS(query->getFieldName(cdbQuery::fldKey));
   cu_fetch = 0; cu_edit = 0;
}

cdbRow::cdbRow(cdbQuery *query, cString key, int flags) :
   csRow(query, key, flags),
   cdbTAObject(new0 cdbTransaction(*query->getTA())),
   last_error(cErrBase::errNoError)
{
   if ( !query->hasQueryInfos() ) {
      // Try to get some more infos about the query...
      query->open();
      for ( int fld = 0 ; fld < query->getFieldCount() ; fld++ )
         query->getFieldType(fld);
      query->close();
   }

   key_fields = SQL::FIELDS(query->getFieldName(cdbQuery::fldKey));
   cu_fetch = 0; cu_edit = 0;
}

cdbRow::cdbRow(const cdbRow& other) :
   csRow(other),
   cdbTAObject(new0 cdbTransaction(*other.getTA())),
   last_error(cErrBase::errNoError)
{
   cdbQuery *other_query = (cdbQuery*)other.getQuery();
   key_fields = SQL::FIELDS(other_query->getFieldName(cdbQuery::fldKey));
   cu_fetch = 0; cu_edit = 0;
}

cdbRow::~cdbRow()
{
   delete cu_fetch;
   delete cu_edit;
   delete getTA(); // Wirklich eigene TA verwenden? Nicht besser: Wahlweise eigene verwenden oder fremde MITverwenden????
}


void cdbRow::addField(cdbField *field)
{
   fields = fields + SQL::FIELD(field->getFieldName());
}


// Hilfsfunktionen
// ===============

SQL::WHERE cdbRow::makeCondExact(SQL::FIELDS key_fields, SQL::FIELDS key_values, csQuery *query)
{
   SQL::WHERE where;
   cString base_table_alias;

   // Wenn die Basistabelle einen Aliasnamen verwendet, diesen merken.
   // Wird spaeter vor alle Feldnamen gestellt, die kein Table-Alias benutzen

   if ( query != 0 && query->ECL_ISKINDOF(cdbQuery) ) {
      cdbQuery *db_query = ECL_CAST(cdbQuery,query);
      SQL::TABLE base_table = db_query->getSQL().getFrom().getBaseTable();
      if ( !base_table.getTableAlias().isEmpty() )
         base_table_alias = base_table.getTableAlias();
   }

   int key_field_count = key_fields.getFieldCount();
   __ECL_ASSERT1__(key_field_count == key_values.getFieldCount());

   for ( int i = 0 ; i < key_field_count ; i++ ) {
      SQL::FIELD field = key_fields.getField(i);
      cString name = key_fields.getField(i);
      if ( !base_table_alias.isEmpty() && field.getTableName().isEmpty() )
         name = base_table_alias + "." + name;
      cString value = AdaptValue(key_values.getField(i), i, query);
      where = where & SQL::COND(name + "=" + value);
   }

   return where;
}


// Aktionen bei onFetch
// ====================

void cdbRow::execFetch(cdbDatabase *db)
{
   try {

      cdbQuery *query = (cdbQuery*)getQuery();
      SQL::SELECT query_select = query->getSQL();

      SQL::HINTS  hints      = query_select.getHints();
      SQL::FROM   from       = SQL::FROM(query_select.getFrom().getBaseTable());
      SQL::FIELDS key_values = SQL::FIELDS(getKey());
      SQL::WHERE  where      = makeCondExact(key_fields, key_values, query);

      // 15.07.2001 TBD: Wozu die Hints aufnehmen? Ist das nicht eher falsch?
      select = SQL::SELECT(/*hints,*/ fields, from, where);

      delete cu_fetch;
      cu_fetch = new0 cdbCursorEx(*db);
      cu_fetch->compile(SQL::STMT(select));
      cu_fetch->exec();

      last_rc = cu_fetch->fetch();

   } catch ( const cErrBase& err ) {
      last_error = err;
   }
}


// Aktionen bei onEdit()
// ====================

void cdbRow::execEdit(cdbDatabase * db)
{
   try {

      cdbQuery *query = (cdbQuery*)getQuery();
      SQL::SELECT query_select = query->getSQL();

      SQL::HINTS  hints      = query_select.getHints();
      SQL::FROM   from       = SQL::FROM(query_select.getFrom().getBaseTable());
      SQL::FIELDS key_values = SQL::FIELDS(getKey());
      SQL::WHERE  where      = makeCondExact(key_fields, key_values, query);

      cdbCursorEx cu(*db);
      cu.setLockMode(cdbCursor::cLocked);
      cu.compile(SQL::STMT(SQL::SELECT(/*hints,*/ fields, from, where)));
      cu.exec();

      if ( cu.fetch() ) {
         for ( int i = 0 ; i < cu.getFieldCount() ; i++ ) {
            cdbField *field = (cdbField*)getField(i);
            if ( field != 0 ) {
               field->setFlags(cdbField::fStoreFixLen, cu.getFieldFixedLength(i));
               field->setFlags(cdbField::fThousandSep, false);
               switch ( cu.getFieldType(i) ) {
               case csStorage::tInt:
                  {
                     int value;
                     field->setType(cdbField::tInt);
                     field->newBuffer(sizeof(int));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tDouble:
                  {
                     double value;
                     field->setType(cdbField::tDouble);
                     field->setFlags(cdbField::fThousandSep);
                     field->newBuffer(sizeof(double));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tTime:
                  {
                     cTime value;
                     field->setType(cdbField::tTime);
                     field->newBuffer(sizeof(cTime));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tDate:
                  {
                     cDate value;
                     field->setType(cdbField::tDate);
                     field->newBuffer(sizeof(cDate));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tDateTime:
                  {
                     cDateTime value;
                     field->setType(cdbField::tDateTime);
                     field->newBuffer(sizeof(cDateTime));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tChar:
                  {
                     char value;
                     field->setType(cdbField::tChar);
                     field->newBuffer(sizeof(char));
                     field->initFrom(&value, sizeof value, !cu.get(i, value));
                  }
                  break;
               case csStorage::tString:
                  {
                     cString value;
                     int buffer_size = cu.getFieldSize(i) + 1;
                     field->setType(cdbField::tString);
                     field->newBuffer(buffer_size);
                     bool ok = cu.get(i, value);
                     field->initFrom((const char *)value, value.getLength()+1, !ok);
                  }
                  break;
               }
            }
         }
      }

      last_rc = true;

   } catch ( const cErrBase& err ) {
      last_rc = false;
      last_error = err;
   }
}


// Aktionen bei onAdd()
// ====================

void cdbRow::execAddRow(cdbDatabase * db)
{
   try {

      cdbQuery *query = (cdbQuery*)getQuery();
      SQL::SELECT query_select = query->getSQL();

      SQL::HINTS  hints = query_select.getHints();
      SQL::FROM   from  = SQL::FROM(query_select.getFrom().getBaseTable());

      delete cu_fetch;
      cu_fetch = new0 cdbCursorEx(*db);
      cu_fetch->compile(SQL::STMT(SQL::SELECT(hints, fields, from)));
      cu_fetch->exec();
      /*
      cdbCursor cu(*db);
      cu.compile(SQL::STMT(SQL::SELECT(hints, fields, from)));
      cu.exec();
      */

      for ( int i = 0 ; i < cu_fetch->/*cu.*/getFieldCount() ; i++ ) {
         cdbField *field = (cdbField*)getField(i);
         switch ( cu_fetch->/*cu.*/getFieldType(i) ) {
         case csVar::tInt:
            field->setType(cdbRow::tInt);
            field->newBuffer(sizeof(int));
            break;
         case csVar::tDouble:
            field->setType(cdbRow::tDouble);
            field->setFlags(cdbField::fThousandSep);
            field->newBuffer(sizeof(double));
            break;
         case csVar::tTime:
            field->setType(cdbRow::tTime);
            field->newBuffer(sizeof(cTime));
            break;
         case csVar::tDate:
            field->setType(cdbRow::tDate);
            field->newBuffer(sizeof(cDate));
            break;
         case csVar::tDateTime:
            field->setType(cdbRow::tDateTime);
            field->newBuffer(sizeof(cDateTime));
            break;
         case csVar::tChar:
            field->setType(cdbRow::tChar);
            field->newBuffer(sizeof(char));
            break;
         case csVar::tString:
            field->setType(cdbRow::tString);
            field->newBuffer(cu_fetch->/*cu.*/getFieldSize(i) + 1);
            break;
         }
         // 18.01.2002 -TE- Bestehende Not-Null-Bedingung des Feldes beruecksichtigen,
         // damit explizit zu Not-Null gesetzte Felder diesen Status auch beibehalten
         bool not_null = !cu_fetch->getFieldNullable(i) || field->getFlags(csVar::fNotNull);
         field->setFlags(csVar::fNotNull, not_null);
         field->setFlags(csVar::fIsNull, !not_null);
      }

      last_rc = true;
      cu_fetch->close();

   } catch ( const cErrBase& err ) {
      last_rc = false;
      last_error = err;
   }
}


// Aktionen bei onSave(INSERT)
// ===========================

void cdbRow::execInsert(cdbDatabase * db)
{
   try {

      int i;
      cdbQuery *query = (cdbQuery*)getQuery();

      SQL::FIELDS field_list;
      SQL::VALUES value_list;
      SQL::SELECT select     = query->getSQL();
      SQL::TABLE  insert_tbl = select.getFrom().getBaseTable();
      SQL::VALUES key_values = SQL::VALUES(getKey());

      int key_field_count = key_fields.getFieldCount();
      __ECL_ASSERT1__(key_field_count == key_values.getValueCount());

      for ( i = 0 ; i < key_field_count ; i++ ) {
         field_list = field_list + SQL::FIELD(key_fields.getField(i).getFieldName(false));
         value_list = value_list + SQL::VALUE(key_values.getValue(i));
      }

      SQL::FIELDS fields = select.getFields();
      int field_count = fields.getFieldCount();

      for ( i = key_field_count ; i < field_count ; i++ ) {
         cString value = query->getNewRowDefValue(i);
         if ( !value.isEmpty() ) {
            field_list = field_list + SQL::FIELD(fields.getField(i).getFieldName(false));
            value_list = value_list + SQL::VALUE(value);
         }
      }

      SQL::STMT stmt = SQL::STMT(
         SQL::INSERT(
            insert_tbl.getTableName(),
            field_list,
            value_list
         )
      );

      cdbCursor cu(*db);
      cu.compile(stmt);
      cu.exec();

      // Evtl. zusaetzliche Statements ausfuehren

      for ( i = 0 ; !cString(stmt).isEmpty() ; i++ ) {
         stmt = query->getNewRowAddStmt(i);
         if ( !cString(stmt).isEmpty() ) {
            // -TE- 25.11.2001: Die Marker gelten jetzt fuer die gesamte Werteliste
            // des INSERT-Statements. Es koennen jedoch nur die ersten 10 Werte dieser
            // Liste eingebunden werden.
            stmt = ReplaceKeyVals(stmt, value_list);
            cu.compile(stmt);
            cu.exec();
         }
      }

      last_rc = true;

   } catch ( const cErrBase& err ) {
      last_rc = false;
      last_error = err;
   }
}


// Aktionen bei onSave(UPDATE)
// ===========================

void cdbRow::execUpdate(cdbDatabase * db)
{
   try {

      int i;
      cdbQuery *query = (cdbQuery*)getQuery();
      SQL::SELECT query_select = query->getSQL();

      SQL::SET    set;
      SQL::TABLE  update_tbl = query_select.getFrom().getBaseTable();
      SQL::FIELDS key_values = SQL::FIELDS(getKey());
      SQL::WHERE  where      = makeCondExact(key_fields, key_values, query);

      bool any_modified = false;
      bool key_modified = false;

      for ( i = 0 ; i < getFieldCount() ; i++ ) {
         cdbField *field = (cdbField*)getField(i);
         if ( __ECL_ASSERT1__(field != 0)
           && field->getFlags(csField::fModified) )
         {
            any_modified = true;
            cString fld_name = field->getFieldName();
            cString fld_value = field->isNull() ? "NULL" : "?";
            set = set + SQL::ASSIGN(fld_name + "=" + fld_value);
            int idx = key_fields.findField(fld_name);
            if ( idx >= 0 ) {
               if ( field->get(fld_value) ) {
                  fld_value = AdaptValue(fld_value, i, query);
                  key_values.setField(idx, fld_value);
                  key_modified = true;
               }
            }
         }
      }

      if ( any_modified ) {

         SQL::STMT stmt = SQL::STMT(
            SQL::UPDATE(update_tbl, set, where)
         );

         cdbCursor cu(*db);
         cu.compile(stmt);

         int bind_idx = 0;
         for ( i = 0 ; i < getFieldCount() ; i++ ) {
            cdbField *field = (cdbField*)getField(i);
            if ( __ECL_ASSERT1__(field != 0)
              && field->getFlags(csField::fModified)
              && !field->isNull() )
            {
               cu.bind(bind_idx++, field);
            }
         }

         cu.exec();

      }

      if ( key_modified )
         setKey(key_values);

      last_rc = true;

   } catch ( const cErrBase& err ) {
      last_error = err;
   }
}


// Aktionen bei onSave(DELETE)
// ===========================

void cdbRow::execDelete(cdbDatabase *db)
{
   try {

      cdbQuery *query = (cdbQuery*)getQuery();
      SQL::SELECT query_select = query->getSQL();

      SQL::TABLE  delete_tbl = query_select.getFrom().getBaseTable();
      SQL::FIELDS key_values = SQL::FIELDS(getKey());
      SQL::WHERE  where      = makeCondExact(key_fields, key_values, query);

      SQL::STMT stmt = SQL::STMT(
         SQL::DELETE(delete_tbl, where)
      );

      cdbCursor cu(*db);
      cu.compile(stmt);
      cu.exec();

      last_rc = true;

   } catch ( const cErrBase& err ) {
      last_error = err;
   }
}


// Ueberschriebene Events
// ======================

bool cdbRow::onFetch()
{
   last_error = cErrBase(cErrBase::errNoError);

   cdbTAObject::callAction(ACTION_FETCH);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onAdd()
{
   last_error = cErrBase(cErrBase::errNoError);

   cdbTAObject::callAction(ACTION_ADDROW);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onEdit()
{
   last_error = cErrBase(cErrBase::errNoError);

   cdbTAObject::callAction(ACTION_EDIT);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onRemove()
{
   last_error = cErrBase(cErrBase::errNoError);

   cdbTAObject::callAction(ACTION_REMOVE);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onSave(INFO commit_info)
{
   last_error = cErrBase(cErrBase::errNoError);

   switch ( commit_info ) {
   case INSERT:   callAction(ACTION_INSERT); break;
   case UPDATE:   callAction(ACTION_UPDATE); break;
   case DELETE:   callAction(ACTION_DELETE); break;
   }

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onCancel(INFO /*rollback_info*/)
{
   last_error = cErrBase(cErrBase::errNoError);

   cdbTAObject::callAction(ACTION_CANCEL);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return last_rc;
}

bool cdbRow::onBeginTA()
{
   getTA()->begin();
   // ... Ende der Operation NICHT abwarten!
   return true;
}

bool cdbRow::onCommitTA(bool commit_all)
{
   last_error = cErrBase(cErrBase::errNoError);

   if ( commit_all ) {
      getTA()->saveAll(EVENT(this, (EVFUNC_P)onEvtEndTA));
   } else {
      getTA()->end(cdbTransaction::teCommit, EVENT(this, (EVFUNC_P)onEvtEndTA));
   }

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return true;
}

bool cdbRow::onRollbackTA()
{
   last_error = cErrBase(cErrBase::errNoError);

   getTA()->end(cdbTransaction::teRollback, EVENT(this, (EVFUNC_P)onEvtEndTA));

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return true;
}

void cdbRow::onEvtEndTA(void *error)
{
   last_error = *((cErrBase*)error);
}


// Ausfuehrung (aus cdbTAObject)
// -----------------------------

void cdbRow::onExecAction(cdbDatabase *db, int func)
{
   switch ( func ) {
   case ACTION_FETCH:   execFetch(db); break;
   case ACTION_ADDROW:  execAddRow(db); break;
   case ACTION_EDIT:    execEdit(db); break;
   case ACTION_REMOVE:  break;
   case ACTION_INSERT:  execInsert(db); break;
   case ACTION_UPDATE:  execUpdate(db); break;
   case ACTION_DELETE:  execDelete(db); break;
   case ACTION_CANCEL:  break;
   }
}

void cdbRow::onStopAction()
{
}

cString cdbRow::onGetSignature()
{
   return "ROW FROM " + cString(select.getFrom());
}

