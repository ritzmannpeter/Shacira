// ===========================================================================
// ew_treectls.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwControl
//           |
//           +-cwListCtl
//              |
//              +-cwTree   - Tree-Control
//
// ===========================================================================

#include "win/ew_treectls.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_listctls.hpp"
#include "store/es_var.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwTree
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwTree
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwTree : public cwListCtl {
   ELO_DECLARE(cwTree,cwListCtl)
   friend class ccwTree;

public:

   // Konstruktor
   inline cwTree() : cwListCtl(0) { init(); }
   // Destruktor
   virtual ~cwTree();


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, csStorage *store, csQuery *query,
               int style = 0, const cdRect& rect = cdRect());
   // Liste zugeordneter Icons initialisieren
   void setIconList(const cwIconList& ilist);


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwListCtl::wflUser,
      wflUser           = wflStart << 1   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwListCtl::wsUser,
      wsRootLines       = wsStart << 0,   // Tree hat Linien im Root-Level
      wsUser            = wsStart << 1    // Benutzerdefinierte Styles
   };


   // Verwaltung
   // ==========

   // Kindknoten von 'elem' aufklappen (Refresh erzwingen, wenn 'force_refresh' == true)
   void expandChilds(cwListElem *elem, bool force_refresh = false);
   // Kindknoten von 'elem' schliessen (Elemente loeschen, wenn 'remove_childs' == true)
   void collapseChilds(cwListElem *elem, bool remove_childs = false);
   // Ein bestimmtes Element sichtbar machen (evtl. durch Scroll/Aufklappen)
   void makeVisible(cwListElem *elem);


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, bevor ein Teilbaum aufklappt (true = Aenderung zulassen)
   virtual bool onTreeExpanding(cwListElem *elem);
   // Wird aufgerufen, nachdem ein Teilbaum aufgeklappt wurde
   virtual void onTreeExpanded(cwListElem *elem);
   // Wird aufgerufen, bevor ein Teilbaum zuklappt (true = Aenderung zulassen)
   virtual bool onTreeCollapsing(cwListElem *elem);
   // Wird aufgerufen, nachdem ein Teilbaum zugeklappt wurde
   virtual void onTreeCollapsed(cwListElem *elem);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, bevor sich die Selektion aendert (true = Aenderung zulassen)
   bool onSelectionChanging(cwListElem *elem);
   // Wird aufgerufen, wenn ein Element selektiert wurde
   void onSelectionChanged(cwListElem *elem);

   // Wird aufgrufen, um die Anzahl der selektierten Elemente zu ermitteln
   int onGetSelectedElemCount(bool walk) const;
   // Wird aufgerufen, um die selektierten Elemente zu ermitteln
   cwListElem *onGetSelectedElem(cwListElem *elem = 0, bool walk = false) const;
   // Wird aufgerufen, um die Selektion fuer ein einzelnes Element zu aendern
   bool onSelectElem(cwListElem *elem, bool sel);
   // Wird aufgerufen, um die Selektion fuer alle Elemente zu aendern
   bool onSelectAllElems(bool sel, cwListElem *parent, bool walk);

   // Wird aufgerufen, um das Element mit Cursor zu erfragen
   cwListElem *onGetCursoredElem() const;
   // Wird aufgerufen, um den Cursor auf ein Element zu setzen
   bool onSetCursoredElem(cwListElem *elem);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   bool onRemoveElem(cwListElem *elem, bool invd);
   // Wird aufgerufen, um alle Elemente von der Anzeige zu entfernen
   bool onRemoveAllElems(cwListElem *parent, bool invd);

   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz verfuegbar ist, um ihn zur Liste hinzuzufuegen
   bool onQueryData(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);
   // Wird aufgerufen, nachdem die Abfrage beendet wurde
   void onQueryPostEnd(csQuery *query);

   // Wird aufgerufen, wenn die Einzelabfrage gestartet wurde
   bool onQuery1Started(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einzelabfrage verfuegbar ist
   bool onQuery1Data(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn die Einzelabfrage beendet ist
   bool onQuery1Ended(cwListElem *elem, csQuery *query);

   // Wird aufgerufen, wenn die Einfuegeabfrage gestartet wurde
   bool onInsQueryStarted(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einfuegeabfrage verfuegbar ist
   bool onInsQueryData(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn die Einfuegeabfrage beendet ist
   bool onInsQueryEnded(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, nachdem die Einfuegeabfrage beendet wurde
   void onInsQueryPostEnd(cwListElem *before, cwListElem *parent, csQuery *query);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);

   // Wird aufgerufen, wenn ein Element des Controls geloescht wird
   void onDeletingElement(cwListElem *elem);
   // Wird aufgerufen, um die Anzahl zusaetzlich benoetigter Bytes im Element zu erfragen
   int onGetAddByteCount() const;
   // Wird aufgerufen, um die Abfrage zu erfragen, die das Element erzeugt hat
   csQuery *onGetQueryOfElem(const cwListElem *elem, bool sub_query) const;

   // Kontextmenu anzeigen
   bool onContextMenu(const cwCmdPosition& cmd);


protected:

   // Interner Konstruktor
   cwTree(void *wnd);

private:

   // Initialisierung
   void init();

   // Struktur mit Zusatzinformationen
   struct ADD_INFO;
   // Zeiger auf Struktur mit Zusatzinformationen ermitteln
   ADD_INFO *getAddInfoPtr(const cwListElem *elem) const;

};

#endif /*__INTERFACE__*/


// Implementierung cwTree
// ===========================================================================

struct cwTree::ADD_INFO {
   #if defined __ECL_W32__
      // cwTree merkt sich HTREEITEM - umgekehrt merkt sich das
      // HTREEITEM in ItemData einen Zeiger auf das cwListElem
      HTREEITEM hItem;
   #endif
   csQuery *sub_query;
};

cwTree::cwTree(void *wnd) :
   cwListCtl(wnd)
{
}

cwTree::~cwTree()
{
   // Cleanup bereits hier aufrufen, da onDeletingElements benoetigt wird!
   cleanup();
}

void cwTree::init()
{
   #if defined __ECL_W32__
      _wnd = new WCTreeCtrl(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}

cwTree::ADD_INFO * cwTree::getAddInfoPtr(const cwListElem *elem) const
{
   return (ADD_INFO*)elem->getAddDataPtr();
}


// Allgemeines
// ===========

void cwTree::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                    int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style = WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
      if ( style & wsRootLines ) mfc_style |= TVS_LINESATROOT;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCTreeCtrl*)_wnd)->Create(mfc_style, mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create tree control"));

   #else
      // ...
   #endif
}

void cwTree::setIconList(const cwIconList& ilist)
{
   #if defined __ECL_W32__
      ((WCTreeCtrl*)_wnd)->SetImageList((CImageList*)ccwIconList::__getIList(&ilist), TVSIL_NORMAL);
   #else
      // ...
   #endif
}


// Verwaltung
// ==========

void cwTree::expandChilds(cwListElem *elem, bool force_refresh)
{
   if ( __ECL_ASSERT1__(elem != 0) ) {

      csQuery *query = getQuery();

      #define __Use_Wanderer__
      #ifdef __Use_Wanderer__
         cwListElem *wanderer = elem;
         while ( wanderer != 0 && (query = getAddInfoPtr(wanderer)->sub_query) == 0 )
            wanderer = wanderer->getParent();
         if ( query == 0 )
            query = getQuery();
      #endif

      if ( query != 0 && (!elem->hasChilds() || force_refresh) ) {

         //csQuery *query = getQuery();
         query->setQueryFromKey(elem->getKey());
         insertNewListElems(query, 0, elem);

      } else {

         #if defined __ECL_W32__
            HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
            ((WCTreeCtrl*)_wnd)->Expand(hItem, TVE_EXPAND);
         #elif defined __ECL_OS2__
            // ...
         #endif

      }

   }
}

void cwTree::collapseChilds(cwListElem *elem, bool remove_childs)
{
   if ( __ECL_ASSERT1__(elem != 0) ) {

      #if defined __ECL_W32__
         HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
         UINT nCode = TVE_COLLAPSE | (remove_childs ? TVE_COLLAPSERESET : 0);
         ((WCTreeCtrl*)_wnd)->Expand(hItem, nCode);
      #elif defined __ECL_OS2__
         // ...
      #endif

      if ( remove_childs && elem->getFlags(cwListElem::eflChildsLoaded) ) {
         // TBD: Richtig so? Unter Win32 sind die Elemente schon alle aus dem
         // Control entfernt, removeAllElems() versucht aber auch, die Elemente zu loeschen
         deleteAllElems(elem);
         // Anschliessend Dummy-Element wieder einfuegen
         ((WCTreeCtrl*)_wnd)->InsertItem(0, 0, 0, hItem);
         elem->setFlags(cwListElem::eflChildsPossible, true);
         elem->setFlags(cwListElem::eflChildsLoaded, false);
      }
   }
}

void cwTree::makeVisible(cwListElem *elem)
{
   if ( __ECL_ASSERT1__(elem != 0) ) {

      #if defined __ECL_W32__
         HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
         __ECL_ASSERT1__(((WCTreeCtrl*)_wnd)->EnsureVisible(hItem));
      #elif defined __ECL_OS2__
         // ...
      #endif

   }
}


// Zusaetzliche Events
// ===================

bool cwTree::onTreeExpanding(cwListElem *elem)
{
   csQuery *query = getQuery();

   #define __Use_Wanderer__
   #ifdef __Use_Wanderer__
      cwListElem *wanderer = elem;
      while ( wanderer != 0 && (query = getAddInfoPtr(wanderer)->sub_query) == 0 )
         wanderer = wanderer->getParent();
      if ( query == 0 )
         query = getQuery();
   #endif

   if ( elem != 0 && elem->getFlags(cwListElem::eflChildsPossible) ) {

      csQuery *sub_query = getAddInfoPtr(elem)->sub_query;

      if ( query != 0 || sub_query != 0 ) {

         #if defined __ECL_W32__
            // Dummy-Element wieder loeschen...
            HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
            HTREEITEM hDummyItem = ((WCTreeCtrl*)_wnd)->GetNextItem(hItem, TVGN_CHILD);
            if ( hDummyItem != NULL ) {
               ((WCTreeCtrl*)_wnd)->DeleteItem(hDummyItem);
            }
         #elif defined __ECL_OS2__
            // ...
         #endif

         if ( sub_query != 0 ) {
            // Teilbaum fuellen mit Elementen aus Subquery
            insertNewListElems(sub_query, 0, elem);
         } else {
            // Teilbaum fuellen mit Teilabfrage, die auf aktuellem
            // Datensatz als Parent basiert
            query->setQueryFromKey(elem->getKey());
            insertNewListElems(query, 0, elem);
         }

      }

   }

   return true;
}

void cwTree::onTreeExpanded(cwListElem * /*elem*/)
{
}

bool cwTree::onTreeCollapsing(cwListElem * /*elem*/)
{
   return true;
}

void cwTree::onTreeCollapsed(cwListElem *elem)
{
   collapseChilds(elem, true);
}


// Ueberschriebene Events
// ======================

bool cwTree::onSelectionChanging(cwListElem * /*elem*/)
{
   return true;
}

void cwTree::onSelectionChanged(cwListElem *elem)
{
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onSelectionChanged(elem);
}


// Selektion
// ---------

int cwTree::onGetSelectedElemCount(bool /*walk*/) const
{
   #if defined __ECL_W32__
      return ((WCTreeCtrl*)_wnd)->GetSelectedItem() == NULL ? 0 : 1;
   #else if defined __ECL_OS2__
      // ...
   #endif
}

cwListElem * cwTree::onGetSelectedElem(cwListElem *elem, bool /*walk*/) const
{
   #if defined __ECL_W32__
      if ( elem != 0 ) {
         return (cwListElem*)0;
      } else {
         HTREEITEM hItem = ((WCTreeCtrl*)_wnd)->GetSelectedItem();
         return hItem != NULL ?
            (cwListElem*)((WCTreeCtrl*)_wnd)->GetItemData(hItem)
          : (cwListElem*)0;
      }
   #else if defined __ECL_OS2__
      // ???
   #endif
}

bool cwTree::onSelectElem(cwListElem *elem, bool sel)
{
   #if defined __ECL_W32__
      if ( elem && sel ) {
         HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
         return !!((WCTreeCtrl*)_wnd)->SelectItem(hItem);
      } else {
         return false;
      }
   #else if defined __ECL_OS2__
      // ...
   #endif
}

bool cwTree::onSelectAllElems(bool sel, cwListElem * /*parent*/, bool /*walk*/)
{
   #if defined __ECL_W32__
      if ( !sel ) {
         return !!((WCTreeCtrl*)_wnd)->SelectItem(NULL);
      } else {
         return __ECL_ASSERT1__(0); // Kein SelectAll moeglich
      }
   #else if defined __ECL_OS2__
      // ...
   #endif
}


// Cursor
// ------

cwListElem * cwTree::onGetCursoredElem() const
{
   return onGetSelectedElem();
}

bool cwTree::onSetCursoredElem(cwListElem *elem)
{
   return doSelectElem(elem, true);
}


// Einfuegen/Loeschen
// ------------------

bool cwTree::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool /*invd*/)
{
   // Einfuegen als Kind von parent (Top-level, wenn parent == 0)
   //
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      HTREEITEM hInsertAfter;

      if ( pos < 0 && ref_elem != 0 )
         ref_elem = ref_elem->getPrev();

      if ( ref_elem == 0 ) {
         hInsertAfter = pos > 0 ? TVI_FIRST : TVI_LAST;
      } else {
         hInsertAfter = getAddInfoPtr(ref_elem)->hItem;
      }

      HTREEITEM hParent = parent != 0 ?
         getAddInfoPtr(parent)->hItem
       : TVI_ROOT;

      HTREEITEM hItem = ((WCTreeCtrl*)_wnd)->InsertItem(
         new_elem->getName(),
         new_elem->getBitmapId(cEloBase::bsDefault),
         new_elem->getBitmapId(cEloBase::bsActive),
         hParent,
         hInsertAfter
      );

      getAddInfoPtr(new_elem)->hItem = hItem;

      if ( hItem != NULL ) {
         TV_ITEM tvi;
         tvi.mask      = TVIF_HANDLE | TVIF_PARAM | TVIF_CHILDREN;
         tvi.hItem     = hItem;
         tvi.lParam    = (DWORD)new_elem;
         tvi.cChildren = I_CHILDRENCALLBACK;
         ((WCTreeCtrl*)_wnd)->SetItem(&tvi);
         //((WCTreeCtrl*)_wnd)->SetItemData(hItem, (DWORD)new_elem);

         if ( new_elem->getFlags(cwListElem::eflChildsPossible) ) {
            // Dummy-Element einfuegen
            ((WCTreeCtrl*)_wnd)->InsertItem(0, 0, 0, hItem);
         }
      }

      return __ECL_ASSERT1__(hItem != NULL);

   #else if defined __ECL_OS2__
      // ???
   #endif
}

bool cwTree::onRemoveElem(cwListElem *elem, bool /*invd*/)
{
   bool rc = false;

   #if defined __ECL_W32__
      WCTreeCtrl *mfc_tree = (WCTreeCtrl*)_wnd;
      HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
      HTREEITEM hItemSel = mfc_tree->GetSelectedItem();
      if ( hItem == hItemSel )
         mfc_tree->SelectItem(NULL);
      rc = __ECL_ASSERT1__(mfc_tree->DeleteItem(hItem) != 0);
   #else if defined __ECL_OS2__
      // ???
   #endif

   return rc;
}

bool cwTree::onRemoveAllElems(cwListElem *parent, bool /*invd*/)
{
   #if defined __ECL_W32__
      if ( _wnd != 0 && ((WCTreeCtrl*)_wnd)->m_hWnd != 0 ) {
         if ( parent == 0 ) {
            // Alle Elemente loeschen
            ((WCTreeCtrl*)_wnd)->SelectItem(NULL); // Wichtig!
            return __ECL_ASSERT1__(((WCTreeCtrl*)_wnd)->DeleteAllItems() != 0);
         } else {
            // Alle Kinder von 'parent' loeschen
            HTREEITEM hItem = getAddInfoPtr(parent)->hItem;
            ((CTreeCtrl*)_wnd)->SelectItem(hItem); // Wichtig!
            if ( ((WCTreeCtrl*)_wnd)->ItemHasChildren(hItem) ) {
               HTREEITEM hNextItem;
               HTREEITEM hChildItem = ((WCTreeCtrl*)_wnd)->GetChildItem(hItem);
               while ( hChildItem != NULL ) {
                  hNextItem = ((WCTreeCtrl*)_wnd)->GetNextItem(hChildItem, TVGN_NEXT);
                  __ECL_ASSERT1__(((WCTreeCtrl*)_wnd)->DeleteItem(hChildItem));
                  hChildItem = hNextItem;
               }
            }
         }
      }
      return true;
   #else if defined __ECL_OS2__
      // ???
   #endif
}


// Abfrage
// -------

bool cwTree::onQueryStarted(csQuery *query)
{
   setRedraw(false);
   return cwListCtl::onQueryStarted(query);
}

bool cwTree::onQueryData(csQuery *query)
{
   cwListElem *new_elem = new1(this) cwListElem(query);

   if ( new_elem->getUserDataLen() > 0 )
      query->getUserData(new_elem->getUserDataBuf(), new_elem->getUserDataLen());

   csQuery *sub_query = query->newSubquery();
   getAddInfoPtr(new_elem)->sub_query = sub_query;
   sub_query->requestLock();

   if ( query->mayHaveChilds() ) {
      new_elem->setFlags(cwListElem::eflChildsPossible);
   } else {
      new_elem->setFlags(cwListElem::eflChildsLoaded);
   }

   if ( query->mustAutoViewChilds() ) {
      new_elem->setFlags(cwListElem::eflChildsAutoView);
   }

   return insertElemAtEnd(new_elem);
}

bool cwTree::onQueryEnded(csQuery *query)
{
   bool ok = cwListCtl::onQueryEnded(query);
   setRedraw(true);
   return ok;
}

void cwTree::onQueryPostEnd(csQuery * /*query*/)
{
   // Muessen irgendwelche Elemente automatisch aufgeklappt werden?

   for ( cwListElem *elem = getFirstElem() ; elem ; elem = getNextElem(elem) ) {
      if ( elem->getFlags(cwListElem::eflChildsAutoView) ) {
         elem->setFlags(cwListElem::eflChildsAutoView, false);
         expandChilds(elem);
      }
   }
}

// ---

bool cwTree::onQuery1Started(cwListElem *elem, csQuery *query)
{
   return cwListCtl::onQuery1Started(elem, query);
}

bool cwTree::onQuery1Data(cwListElem *elem, csQuery *query)
{
   if ( elem != 0 && cwListCtl::onQuery1Data(elem, query) ) {

      elem->refresh(query);

      #if defined __ECL_W32__
         HTREEITEM hItem = getAddInfoPtr(elem)->hItem;
         if ( hItem != NULL ) {
            TV_ITEM tvi;
            tvi.mask    = TVIF_HANDLE | TVIF_TEXT;
            tvi.hItem   = hItem;
            tvi.pszText = LPSTR_TEXTCALLBACK;
            ((WCTreeCtrl*)_wnd)->SetItem(&tvi);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif

      return true;

   }

   return false;
}

bool cwTree::onQuery1Ended(cwListElem *elem, csQuery *query)
{
   return cwListCtl::onQuery1Ended(elem, query);
}

// ---

bool cwTree::onInsQueryStarted(cwListElem *before, cwListElem *parent, csQuery *query)
{
   setRedraw(false);

   if ( parent && parent->getFlags(cwListElem::eflChildsPossible) ) {
      parent->setFlags(cwListElem::eflChildsPossible, false);

      #if defined __ECL_W32__
         // Dummy-Element wieder loeschen...
         HTREEITEM hItem = getAddInfoPtr(parent)->hItem;
         HTREEITEM hDummyItem = ((WCTreeCtrl*)_wnd)->GetNextItem(hItem, TVGN_CHILD);
         if ( hDummyItem != NULL ) {
            ((WCTreeCtrl*)_wnd)->DeleteItem(hDummyItem);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return cwListCtl::onInsQueryStarted(before, parent, query);
}

bool cwTree::onInsQueryData(cwListElem *before, cwListElem *parent, csQuery *query)
{
   cwListElem *new_elem = new1(this) cwListElem(query);

   if ( new_elem->getUserDataLen() > 0 )
      query->getUserData(new_elem->getUserDataBuf(), new_elem->getUserDataLen());

   csQuery *sub_query = query->newSubquery();
   getAddInfoPtr(new_elem)->sub_query = sub_query;
   sub_query->requestLock();

   if ( query->mayHaveChilds() ) {
      new_elem->setFlags(cwListElem::eflChildsPossible);
   } else {
      new_elem->setFlags(cwListElem::eflChildsLoaded);
   }

   if ( query->mustAutoViewChilds() ) {
      new_elem->setFlags(cwListElem::eflChildsAutoView);
   }

   return insertElemBefore(new_elem, before, parent);
}

bool cwTree::onInsQueryEnded(cwListElem *before, cwListElem *parent, csQuery *query)
{
   bool ok = cwListCtl::onInsQueryEnded(before, parent, query);
   setRedraw(true);

   if ( parent != 0 ) {
      parent->setFlags(cwListElem::eflChildsLoaded);

      #if defined __ECL_W32__
         HTREEITEM hItem = getAddInfoPtr(parent)->hItem;
         ((WCTreeCtrl*)_wnd)->Expand(hItem, TVE_EXPAND);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   if ( query != 0 ) // Default einstellen:
      query->setQueryFromTopLevel();

   return ok;
}

void cwTree::onInsQueryPostEnd(cwListElem * /*before*/, cwListElem *parent, csQuery * /*query*/)
{
   // Muessen irgendwelche Elemente automatisch aufgeklappt werden?

   if ( parent != 0 ) {
      for ( cwListElem *elem = parent->getFirstChild() ; elem ; elem = getNextElem(elem) ) {
         if ( elem->getFlags(cwListElem::eflChildsAutoView) ) {
            elem->setFlags(cwListElem::eflChildsAutoView, false);
            expandChilds(elem);
         }
      }
   }
}


// Window-Styles
// =============

int cwTree::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCTreeCtrl*)_wnd)->GetStyle();

      if ( (mask & wsRootLines) && (style & TVS_LINESATROOT) )
         rc |= wsRootLines;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwListCtl::onGetStyles(mask);
}

void cwTree::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsRootLines )
         os_add[0] |= TVS_HASLINES | TVS_LINESATROOT;

      if ( remove & wsRootLines )
         os_remove[0] |= TVS_HASLINES | TVS_LINESATROOT;

      cwListCtl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwTree::onDeletingElement(cwListElem *elem)
{
   csQuery *sub_query = getAddInfoPtr(elem)->sub_query;
   sub_query->releaseLock(true);
}

int cwTree::onGetAddByteCount() const
{
   return cwListCtl::onGetAddByteCount() + sizeof ADD_INFO;
}

bool cwTree::onContextMenu(const cwCmdPosition& cmd)
{
   #if defined __ECL_W32__

      WCTreeCtrl *tree = (WCTreeCtrl*)_wnd;

      POINT pt = { cmd.getPosX(), cmd.getPosY() };
      if ( cmd.isRelativeToScreen() )
	      tree->ScreenToClient(&pt);

	   UINT uFlags;
	   HTREEITEM hItem = tree->HitTest(pt, &uFlags);

      if ( hItem == NULL ) {
         tree->SelectItem(NULL);
      } else {
         tree->SelectItem(hItem);
      }

   #endif

   return cwListCtl::onContextMenu(cmd);
}

csQuery * cwTree::onGetQueryOfElem(const cwListElem *elem, bool sub_query) const
{
   if ( sub_query ) {
      return getAddInfoPtr(elem)->sub_query;
   } else {
      cwListElem *parent = elem->getParent();
      return parent == 0 ?
         getQuery()
       : parent->getSubquery();
   }
}


