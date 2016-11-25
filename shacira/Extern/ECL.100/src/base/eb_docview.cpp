// ===========================================================================
// eb_docview.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEloBase
//     |
//     +--cEloElement
//         |
//         +--cEloDocument
//         |
//         +--cEloSimpleView
//
//    cEloView
//
// ===========================================================================

#include "base/eb_docview.hpp"
#include "base/eb_list.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_elo.hpp"


// Forward-Deklarationen
// ===========================================================================

class cEloDocument;
class cEloView;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloDocument
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Dokumentobjekte.
//
// cEclObject
//  +--cEloBase
//      +--cEloElement
//          +--cEloDocument
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloDocument : public cEloElement {
   ECL_DECLARE(cEloDocument,cEloElement)

public:

   // Konstruktor ueber Elementbeschreibung (direkt)
   cEloDocument(const cEloElementDescription *elem_descr);
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cEloDocument(const cEloDescriptionManager *descr_manager, cString descr_sig);
   // Destruktor
   virtual ~cEloDocument();


   // Titel
   // =====

   // Dokument-Titel erfragen
   inline cString getTitle() const
      { return title; }
   // Dokument-Titel setzen
   void setTitle(cString title);


   // Modified-Flag
   // =============

   // Erfragen des Modified-Flags
   inline bool isModified() const
      { return modified; }
   // Modified-Flag setzen
   void setModified(bool modified = true);


   // Views
   // =====

   // View an Dokument "anhaengen"
   void addView(cEloView *view);
   // View wieder "entkoppeln"
   void removeView(cEloView *view);

   // Anzahl assoziierter Views ermitteln
   int getViewCount() const;
   // Assozierten View ueber Index ermitteln
   cEloView *getView(int index) const;

   // Alle assoziierten Views ueber ein Update benachrichtigen
   void updateAllViews(cEloView *from_view, cEloElement *elem, long hint);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, wenn sich der Titel des Dokumentes geaendert hat
   virtual void onTitleChanged();
   // Wird aufgerufen, wenn sich der Status des Modified-Flags geaendert hat
   virtual void onModifiedChanged();


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const
      { return cString(); }
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const
      { return getKey(); }
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const
      { return getName(); }


private:

   cString title;       // Der Dokument-Titel
   bool modified;       // Das Modified-Flag

   // Zeiger auf die geordnete Liste assoziierter Views (oder 0)
   struct ASSOCIATED_VIEWS;
   ASSOCIATED_VIEWS *views;

};

#endif /*__INTERFACE__*/


// Implementierung cEloDocument
// ===========================================================================

struct cEloDocument::ASSOCIATED_VIEWS {
   cList<cEloView*,cEloView*> list;
};

cEloDocument::cEloDocument(const cEloElementDescription *elem_descr) :
   cEloElement(elem_descr)
{
   views = 0;
   modified = false;
}

cEloDocument::cEloDocument(const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cEloElement(descr_manager, descr_sig)
{
   views = 0;
   modified = false;
}

cEloDocument::~cEloDocument()
{
   delete views;
}


// Titel
// =====

void cEloDocument::setTitle(cString title)
{
   if ( cEloDocument::title != title ) {
      cEloDocument::title = title;
      onTitleChanged();
   }
}


// Modified-Flag
// =============

void cEloDocument::setModified(bool modified)
{
   // setModified immer VOR updateAllViews aufrufen!

   if ( !cEloDocument::modified != !modified ) {
      cEloDocument::modified = !!modified;
      onModifiedChanged();
   }
}


// Views
// =====

void cEloDocument::addView(cEloView *view)
{
   if ( __ECL_ASSERT1__(view != 0 && view->getDocument() == 0) ) {
      if ( views == 0 )
         views = new0 ASSOCIATED_VIEWS;
      views->list.addTail(view);
      view->setDocument(this);
   }
}

void cEloDocument::removeView(cEloView *view)
{
   if ( __ECL_ASSERT1__(view != 0 && views != 0) ) {
      IPOSITION view_pos = views->list.find(view);
      if ( __ECL_ASSERT1__(view_pos != 0) ) {
         views->list.removeAt(view_pos);
         view->setDocument(0);
      }
   }
}

int cEloDocument::getViewCount() const
{
   return views != 0 ?
      views->list.getCount()
    : 0;
}

cEloView * cEloDocument::getView(int index) const
{
   if ( __ECL_ASSERT1__(views != 0) ) {
      IPOSITION view_pos = views->list.findIndex(index);
      if ( __ECL_ASSERT1__(view_pos != 0) )
         return views->list.getAt(view_pos);
   }

   return 0;
}

void cEloDocument::updateAllViews(cEloView *from_view, cEloElement *elem, long hint)
{
   // from_view - Initiator des Updates
   // elem - Modifiziertes Element (== this bei nicht lokaler Aenderung)
   // hint - Zusatzinformation (Kontextabhaengig)

   // Wichtig: Bei Aenderungen im Dokument: Vor updateAllViews erst setModified() aufrufen!

   if ( views != 0 ) {
      IPOSITION view_pos = views->list.getHeadPosition();
      if ( __ECL_ASSERT1__(view_pos != 0) ) {
         cEloView *view = views->list.getNext(view_pos);
         if ( view != from_view )
            view->onUpdate(from_view, elem, hint);
      }
   }
}


// Hinzugefuegte Events
// ====================

void cEloDocument::onTitleChanged()
{
   if ( views != 0 ) {
      IPOSITION view_pos = views->list.getHeadPosition();
      if ( __ECL_ASSERT1__(view_pos != 0) ) {
         cEloView *view = views->list.getNext(view_pos);
         view->onDocumentTitleChanged();
      }
   }
}

void cEloDocument::onModifiedChanged()
{
   if ( views != 0 ) {
      IPOSITION view_pos = views->list.getHeadPosition();
      if ( __ECL_ASSERT1__(view_pos != 0) ) {
         cEloView *view = views->list.getNext(view_pos);
         view->onDocumentModifedChanged();
      }
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloView
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Dokument-Views. Hat selbst keine Basisklasse und kann
// so (relativ) problemlos als zweite Basisklasse in einer Mehrfachvererbung
// herhalten. Eine vollstaendige (benutzbare) cEloView-Basisklasse ist mit
// cEloSimpleView realisiert.
//
// cEloView
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloView {
   friend cEloDocument;

public:

   // Konstruktor
   cEloView();


   // Allgemeines
   // ===========

   // Zugeordnetes Dokument ermitteln (0 falls kein Dokument zugeordnet)
   inline cEloDocument *getDocument() const
      { return document; }
   // Aktuelle Aktionsbeschreibung erfragen
   inline cEloActionDescription *getActionDescription() const
      { return onGetActionDescription(); }

   // Aktuelle Selektion ermitteln (const-Variante)
   inline const cEloSelection *getSelection() const
      { return &selection; }
   // Aktuelle Selektion ermitteln (non-const-Variante)
   inline cEloSelection *getSelection()
      { return &selection; }


protected:

   // Aktuelle Selektion
   cEloSelection selection;


   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um das Update des zugeordneten Dokumentes zu signalisieren
   //  hint = 0: Initiales Update (nachdem View an Dokument angehaengt wurde)
   virtual void onUpdate(cEloView *from_view, cEloElement *elem, long hint);

   // Wird aufgerufen, wenn ein Dokument an den View "angehaengt" wird
   virtual void onDocumentAdded();
   // Wird aufgerufen, wenn das Dokument vom View "entkoppelt" wird
   virtual void onDocumentRemoved();
   // Wird aufgerufen, wenn sich der Titel des Dokumentes aendert
   virtual void onDocumentTitleChanged();
   // Wird aufgerufen, wenn sich das Modifed-Flag des Dokumentes aendert
   virtual void onDocumentModifedChanged();

   // Wird aufgerufen, um die aktuelle Actionsbeschreibung zu erfragen
   virtual cEloActionDescription *onGetActionDescription() const;


private:

   // Zeiger auf die geordnete Liste assoziierter Views (oder 0)
   cEloDocument *document;

   // (Fuer cEloDocument:) Neues Dokument setzen
   void setDocument(cEloDocument *document);

};

#endif /*__INTERFACE__*/


// Implementierung cEloView
// ===========================================================================

cEloView::cEloView()
{
   document = 0;
}


// Allgemeines
// ===========

void cEloView::setDocument(cEloDocument *document)
{
   if ( cEloView::document != document ) {
      cEloView::document = document;
      if ( document == 0 ) {
         onDocumentRemoved();
      } else {
         onDocumentAdded();
         onUpdate(this, document, 0);
      }
   }
}


// Hinzugefuegte Events
// ====================

void cEloView::onUpdate(cEloView * /*from_view*/, cEloElement * /*elem*/, long /*hint*/)
{
}

void cEloView::onDocumentAdded()
{
}

void cEloView::onDocumentRemoved()
{
}

void cEloView::onDocumentTitleChanged()
{
}

void cEloView::onDocumentModifedChanged()
{
}

cEloActionDescription * cEloView::onGetActionDescription() const
{
   return 0; // Default: No Action Description
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloSimpleView
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Dokument-Views.
//
// cEclObject
//  +--cEloBase
//      +--cEloElement        cEloView
//          +--cEloSimpleView--+
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloSimpleView : public cEloElement, public cEloView {
   ECL_DECLARE(cEloSimpleView,cEloElement)

public:

   // Konstruktor ueber Elementbeschreibung (direkt)
   cEloSimpleView(const cEloElementDescription *elem_descr = 0);
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cEloSimpleView(const cEloDescriptionManager *descr_manager, cString descr_sig);
   // Destruktor
   virtual ~cEloSimpleView();

};

#endif /*__INTERFACE__*/


// Implementierung cEloSimpleView
// ===========================================================================

cEloSimpleView::cEloSimpleView(const cEloElementDescription *elem_descr) :
   cEloElement(elem_descr)
{
}

cEloSimpleView::cEloSimpleView(const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cEloElement(descr_manager, descr_sig)
{
}

cEloSimpleView::~cEloSimpleView()
{
}


