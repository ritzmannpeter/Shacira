// ===========================================================================
// eb_eloex.cpp                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//     |
//     +--cEloBase
//         |
//         +--cEloOperation
//             |
//             +--cEloOperationCnr
//
// ===========================================================================

#include "base/eb_eloex.hpp"
#include "base/eb_list.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_elo.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cEloOperationCnr
// ---------------------------------------------------------------------------
//
// Erweitert das Konzept der ELO-Operationen um "echte" Sub-Operationen.
// Ein cEloOperationCnr-Objekt dient dabei als Container für eine Menge
// beliebiger anderer cEloOperation-Objekte.
//
// cEloBase
//  +--cEloOperation
//      +--cEloOperationCnr
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloOperationCnr : public cEloOperation {
   ELO_DECLARE(cEloOperationCnr,cEloOperation)

public:

   // Konstruktor
   cEloOperationCnr();
   // Destruktor
   ~cEloOperationCnr();


protected:

   // Sub-Operationen hinzufuegen
   // ===========================

   // Sub-Operation aufnehmen (direkt)
   void addSubOperation(cEloOperation *sub_op);
   // Sub-Operation aufnehmen (indirekt ueber Operation-Manager)
   void addSubOperation(cEloOperationManager *op_manager, cString op_sig);


   // Sub-Operationen suchen
   // ======================

   // Momentan gueltige Sub-Operation ueber Selektion und 'sub_op' suchen (non-const)
   cEloOperation *findSubOperation(const cEloSelection *selection, int sub_op);
   // Momentan gueltige Sub-Operation ueber Selektion und 'sub_op' suchen (const)
   const cEloOperation *findSubOperation(const cEloSelection *selection, int sub_op) const;


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um den Haupt-Hilfetext fuer die Statuszeile zu erfragen
   virtual cString onGetCnrHelpText(const cEloSelection *selection) const = 0;
   // Wird aufgerufen, um den Haupt-Text fuer Menueeintraege zu erfragen
   virtual cString onGetCnrMenuText(const cEloSelection *selection) const = 0;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Operation auf alle Elemente der Selektion auszufuehren
   void onExecOperation(cEloSelection *selection, int, cEloElement *);
   // Wird aufgerufen, um zu pruefen, ob die (Teil-)Operation "enabled" (zugaengig fuer Benutzer) ist
   bool onGetEnabledFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const;

   // Wird aufgerufen, um zu bestimmen, ob die Operationen Teil-Operationen erlaubt
   bool onGetSubOperations(const cEloSelection *selection) const;
   // Wird aufgerufen, um die aktuelle Anzahl Teil-Operationen zu erfragen
   int onGetSubOperationCount(const cEloSelection *selection) const;
   // Wird aufgerufen, um zu pruefen, ob die Operation ein spezifisches Target Unterstuetzt
   bool onSupportsTarget(const cEloElement *selected_elem, cEloElement *target) const;

   // Wird aufgerufen, um den Hilfetext fuer die Statuszeile zu erfragen
   cString onGetHelpText(const cEloSelection *, int) const;
   // Wird aufgerufen, um den Text fuer Menueeintraege zu erfragen
   cString onGetMenuText(const cEloSelection *, int) const;


private:

   // Zeiger auf zusaetzliche Daten
   struct ADD_INFO;
   ADD_INFO *info;

};

#endif /*__INTERFACE__*/


// Implementierung cEloOperationCnr
// ===========================================================================

struct cEloOperationCnr::ADD_INFO {
   cList<cEloOperation*,cEloOperation*> ops;
};

cEloOperationCnr::cEloOperationCnr()
{
   info = new0 ADD_INFO;
}

cEloOperationCnr::~cEloOperationCnr()
{
   delete info;
}


// Sub-Operationen hinzufuegen
// ===========================

void cEloOperationCnr::addSubOperation(cEloOperation *sub_op)
{
   if ( __ECL_ASSERT1__(sub_op != 0 && info->ops.find(sub_op) == 0) )
      info->ops.addTail(sub_op);
}

void cEloOperationCnr::addSubOperation(cEloOperationManager *op_manager, cString op_sig)
{
   if ( __ECL_ASSERT1__(op_manager != 0) ) {
      cEloOperation *op = op_manager->getOperation(op_sig);
      if ( __ECL_ASSERT1__(op != 0) )
         addSubOperation(op);
   }
}


// Ueberschriebene Events
// ======================

void cEloOperationCnr::onExecOperation(cEloSelection *selection, int sub_op, cEloElement *target)
{
   if ( sub_op >= 0 ) {
      cEloOperation *op = findSubOperation(selection, sub_op);
      if ( __ECL_ASSERT1__(op != 0) )
         op->execOperation(selection, -1, target);
   }
}

bool cEloOperationCnr::onGetEnabledFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const
{
   if ( sel != 0 && sel->getElementCount() > 0 ) {

      // 23.01.2002 -TE- Enabled-Flag fuer die Gesamt-Operation nur dann setzen,
      // wenn mindestens eine  der enthaltenen Operationen ebenfalls enabled ist.

      if ( sub_op < 0 ) {
         for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
            cEloOperation *op = info->ops.getNext(pos);
            if ( op->isEnabled(sel, -1, target) )
               return true;
         }
         return false;
      }

   }

   return false;
}

bool cEloOperationCnr::onGetSubOperations(const cEloSelection *selection) const
{
   // 23.01.2002 -TE- Sub-Operationen nur dann als vorhanden melden,
   // wenn mindestens eine der enthaltenen Operationen Enabled UND
   // deren Menu-Text nicht leer ist!

   if ( selection != 0 && selection->getElementCount() > 0 ) {
      for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
         cEloOperation *op = info->ops.getNext(pos);
         if ( op->isEnabled(selection) && !op->getMenuText(selection).isEmpty() )
            return true;
      }
   }

   return false;
}

int cEloOperationCnr::onGetSubOperationCount(const cEloSelection *selection) const
{
   int count = 0;

   for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
      cEloOperation *op = info->ops.getNext(pos);
      if ( selection->supportsOperation(op->getSignature()) )
         count++;
   }

   return count;
}

bool cEloOperationCnr::onSupportsTarget(const cEloElement *selected_elem, cEloElement *target) const
{
   // Liefert true, wenn mindestens eine der enthaltenen Operationen
   // den Target unterstuetzt

   for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
      cEloOperation *op = info->ops.getNext(pos);
      if ( op->supportsTarget(selected_elem, target) )
         return true;
   }

   return false;
}

cString cEloOperationCnr::onGetHelpText(const cEloSelection *selection, int sub_op) const
{
   if ( sub_op < 0 ) {
      return onGetCnrHelpText(selection);
   } else {
      const cEloOperation *op = findSubOperation(selection, sub_op);
      return __ECL_ASSERT1__(op != 0) ? op->getHelpText(selection) : 0;
   }
}

cString cEloOperationCnr::onGetMenuText(const cEloSelection *selection, int sub_op) const
{
   if ( sub_op < 0 ) {
      return onGetCnrMenuText(selection);
   } else {
      const cEloOperation *op = findSubOperation(selection, sub_op);
      return __ECL_ASSERT1__(op != 0) ? op->getMenuText(selection) : 0;
   }
}


// Sub-Operationen suchen
// ======================

cEloOperation * cEloOperationCnr::findSubOperation(const cEloSelection *selection, int sub_op)
{
   int count = -1;

   for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
      cEloOperation *op = info->ops.getNext(pos);
      if ( selection->supportsOperation(op->getSignature()) )
         count++;
      if ( count == sub_op )
         return op;
   }

   return 0;
}

const cEloOperation * cEloOperationCnr::findSubOperation(const cEloSelection *selection, int sub_op) const
{
   int count = -1;

   for ( IPOSITION pos = info->ops.getHeadPosition() ; pos != 0 ; ) {
      const cEloOperation *op = info->ops.getNext(pos);
      if ( selection->supportsOperation(op->getSignature()) )
         count++;
      if ( count == sub_op )
         return op;
   }

   return 0;
}


