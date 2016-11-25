// ===========================================================================
// es_field.cpp                                                 ______ /  ECL
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
//              +-csField     -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "store/es_field.hpp"
#include "store/es_row.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_var.hpp"

#endif /*__INTERFACE__*/






#ifdef __INTERFACE__

// ===========================================================================
// Definition csField
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csField
//
// ===========================================================================

class __ECL_DLLEXPORT__ csField : public csVar {
   ECL_DECLARE(csField,csVar)
   friend class csRow;

public:
   // Initialisierung als int-Variable
   csField(csRow *row, int& buf, int width = 11, int flags = 0);
   // Initialisierung als double-Variable
   csField(csRow *row, double& buf, int width = 21, int prec = 3, int flags = fThousandSep);
   // Initialisierung als cTime-Variable
   csField(csRow *row, cTime& buf, int flags = 0);
   // Initialisierung als cDate-Variable
   csField(csRow *row, cDate& buf, int flags = 0);
   // Initialisierung als cDateTime-Variable
   csField(csRow *row, cDateTime& buf, int flags = 0);
   // Initialisierung als char-Variable
   csField(csRow *row, char& buf, int flags = 0);
   // Initialisierung als String-Variable
   csField(csRow *row, char *buf, int size, int flags = 0);
   // Initialisierung als beliebige Variable; Puffer wird automatisch allokiert
   csField(csRow *row, TYPE type, int size, int width = 0, int prec = 0, int flags = 0);
   // Destruktor
   ~csField();


   // Flags
   // =====

   enum FLAGS { fStart = csStorage::fUser,
      fUser          = fStart << 0     // Benutzerdefinierte Flags
   };


   // Allgemeines
   // ===========

   // Zugeordnetes csRow-Objekt erfragen
   inline csRow *getRow() const
      { return row; }
   // Zugeordneter Index in csRow erfragen
   inline int getRowIndex() const
      { return row_index; }


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um zu pruefen, ob das Feld Read-Only ist
   bool onCheckReadOnly() const;


protected:

   // Intern: Konstruktor ohne 'buffer'-Initialisierung
   csField(csRow *row, int size, int width, int prec, int flags, TYPE type);

   // Intern: Setzen des Puffers und des NULL-Zustandes (fuer csRow)
   void initFrom(const void *data, int size, bool null)
      { csVar::initFrom(data, size, null); }
   // Intern: Verbindung zum csRow-Objekt trennen
   void unlink(bool remove_from_row);


private:

   csRow *row;
   int row_index;

};

#endif /*__INTERFACE__*/


// Implementierung csField
// ===========================================================================

csField::csField(csRow *row, int& buf, int width, int flags) :
   csVar(buf, width, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, double& buf, int width, int prec, int flags) :
   csVar(buf, width, prec, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, cTime& buf, int flags) :
   csVar(buf, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, cDate& buf, int flags) :
   csVar(buf, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, cDateTime& buf, int flags) :
   csVar(buf, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, char& buf, int flags) :
   csVar(buf, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, char *buf, int size, int flags) :
   csVar(buf, size, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, TYPE type, int size, int width, int prec, int flags) :
   csVar(type, size, width, prec, flags)
{
   csField::row = row;
   csField::row_index = row->addField(this);
}

csField::csField(csRow *row, int size, int width, int prec, int flags, TYPE type) :
   csVar(size, width, prec, flags, type)
{
   csField::row = row;
   csField::row_index = row->addField(this);
   setBuffer(0);
}

csField::~csField()
{
   unlink(true);
}

void csField::unlink(bool remove_from_row)
{
   if ( row != 0 && remove_from_row )
      row->removeField(this);
   row = 0;
}


// Ueberschriebene Events
// ======================

bool csField::onCheckReadOnly() const
{
   if ( row != 0 ) {
      switch ( row->getTAMode() ) {
      case csRow::RW_INSERT:
      case csRow::RW_UPDATE:
         break;
      default:
         return true;
      }
   }

   return csVar::onCheckReadOnly();
}


