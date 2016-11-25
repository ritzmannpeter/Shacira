// ===========================================================================
// edb_field.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csStorage
//           |
//           +-csVar
//              |
//              +-csField
//                 |
//                 +-cdbField       -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_field.hpp"
#include "dbi/edb_row.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_field.hpp"

#endif /*__INTERFACE__*/






#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbField
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csField
//              +--cdbField
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbField : public csField {
   ECL_DECLARE(cdbField,csField)
   friend class cdbRow;

public:
   // Default-Konstruktor
   cdbField(cdbRow *row, cString field_name, int flags = 0);
   // Default-Konstruktor
   cdbField(cdbRow *row, cString field_name, int width, int prec, int flags = 0);
   // Default-Konstruktor
   cdbField(cdbRow *row, cString field_name, TYPE type, int flags = 0);
   // Default-Konstruktor
   cdbField(cdbRow *row, cString field_name, TYPE type, int width, int prec, int flags = 0);
   // Destruktor
   ~cdbField();


   // Flags
   // =====

   enum FLAGS { fStart = csStorage::fUser,
      fUser        = fStart << 0   // Benutzerdefinierte Flags
   };


   // Allgemein
   // =========

   // Name des zugeordneten Feldes erfragen
   inline cString getFieldName() const
      { return field_name; }


protected:

   // Ueberschriebene Events
   // ======================

   // Eigenschaften
   // -------------

   // Wird aufgerufen, um den Typ des Feldes zu erfragen
   TYPE onGetType() const;
   // Wird aufgerufen, um die Anzeigebreite des Feldes zu erfragen
   int onGetWidth() const;
   // Wird aufgerufen, um die Anzahl Nachkommstellen des Feldes zu erfragen
   int onGetPrec() const;


   // Werte erfragen
   // --------------

   // Variable als int abfragen
   bool onGetInt(int& buf) const;
   // Variable als double abfragen
   bool onGetDouble(double& buf) const;
   // Variable als cTime abfragen
   bool onGetTime(cTime& buf) const;
   // Variable als cDate abfragen
   bool onGetDate(cDate& buf) const;
   // Variable als cDateTime abfragen
   bool onGetDateTime(cDateTime& buf) const;
   // Variable als char abfragen
   bool onGetChar(char& buf) const;
   // Variable als String abfragen
   bool onGetString(cString& buf) const;


   // Sonstiges
   // ---------

   // Groesse des Pufferspeichers ermitteln
   int onGetBufferSize() const;
   // Sinnvolle maximale Groesse eines Eingabefeldes ermitteln
   int onGetMaskLength() const;
   // Ist die Variable NULL?
   bool onCheckNull() const;


protected:

   // Intern: Setzen des Puffers und des NULL-Zustandes (fuer cdbRow)
   void initFrom(const void *data, int size, bool null)
      { csField::initFrom(data, size, null); }


private:

   cdbRow *row;
   cString field_name;

};

#endif /*__INTERFACE__*/


// Implementierung cdbField
// ===========================================================================

cdbField::cdbField(cdbRow *row, cString field_name, int flags) :
   csField(row, 0, 0, -1, flags, tNone)
{
   cdbField::field_name = field_name;
   cdbField::row = row;
   row->addField(this);
}

cdbField::cdbField(cdbRow *row, cString field_name, int width, int prec, int flags) :
   csField(row, 0, width, prec, flags, tNone)
{
   cdbField::field_name = field_name;
   cdbField::row = row;
   row->addField(this);
}

cdbField::cdbField(cdbRow *row, cString field_name, TYPE type, int flags) :
   csField(row, 0, 0, -1, flags, type)
{
   cdbField::field_name = field_name;
   cdbField::row = row;
   row->addField(this);
}

cdbField::cdbField(cdbRow *row, cString field_name, TYPE type, int width, int prec, int flags) :
   csField(row, 0, width, prec, flags, type)
{
   cdbField::field_name = field_name;
   cdbField::row = row;
   row->addField(this);
}

cdbField::~cdbField()
{
   cdbField::row = 0;
}


// Ueberschriebene Events
// ======================

// Eigenschaften
// -------------

cdbField::TYPE cdbField::onGetType() const
{
   TYPE demand_type = csField::onGetType();
   return demand_type == tNone && row != 0 && row->cu_fetch != 0 ?
      row->cu_fetch->getFieldType(getRowIndex())
    : demand_type;
}

int cdbField::onGetWidth() const
{
   int demand_width = csField::onGetWidth();
   return demand_width <= 0 && row != 0 && row->cu_fetch != 0 ?
      row->cu_fetch->getFieldWidth(getRowIndex())
    : demand_width;
}

int cdbField::onGetPrec() const
{
   int demand_prec = csField::onGetPrec();
   return demand_prec < 0 && row != 0 && row->cu_fetch != 0 ?
      row->cu_fetch->getFieldPrec(getRowIndex())
    : demand_prec;
}


// Werte erfragen
// --------------

bool cdbField::onGetInt(int& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetInt(buf);;
}

bool cdbField::onGetDouble(double& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetDouble(buf);;
}

bool cdbField::onGetTime(cTime& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetTime(buf);;
}

bool cdbField::onGetDate(cDate& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetDate(buf);;
}

bool cdbField::onGetDateTime(cDateTime& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetDateTime(buf);;
}

bool cdbField::onGetChar(char& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetChar(buf);;
}

bool cdbField::onGetString(cString& buf) const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->get(getRowIndex(), buf)
    : csField::onGetString(buf);;
}


// Sonstiges
// ---------

int cdbField::onGetBufferSize() const
{
   return row != 0 && row->cu_fetch ?
      row->cu_fetch->getFieldBufferSize(getRowIndex())
    : csField::onGetBufferSize();
}

int cdbField::onGetMaskLength() const
{
   return row != 0 && row->cu_fetch ?
      row->cu_fetch->getFieldWidth(getRowIndex())
    : csField::onGetMaskLength();
}

bool cdbField::onCheckNull() const
{
   return row != 0 && row->getTAMode() == cdbRow::READONLY && row->cu_fetch != 0 ?
      row->cu_fetch->isNull(getRowIndex())
    : csField::onCheckNull();
}


