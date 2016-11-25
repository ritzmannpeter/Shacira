// ===========================================================================
// ew_cnrctls.cpp                                               ______ /  ECL
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
//              +-cwContainer - Container-Control
//
// ===========================================================================

#include "win/ew_cnrctls.hpp"

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
// Definition cwContainer
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwContainer
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwContainer : public cwListCtl {
   ELO_DECLARE(cwContainer,cwListCtl)
   friend class ccwContainer;

public:

   // Konstruktor
   inline cwContainer() : cwListCtl(0) { init(); }
   // Destruktor
   virtual ~cwContainer();


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwListCtl::wflUser,
      wflUser           = wflStart << 1   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwListCtl::wsUser,
      // Selektionsart
      wsCnrSingleSel    = (wsStart<<0),              // Maximal 1 selektiertes Element
      wsCnrMultipleSel  = (wsStart<<1),              // Mehrere selektierte Elemente
      wsCnrExtendedSel  = (wsStart<<0)|(wsStart<<1), // Auswahl erweitern mit SHIFT (Default)
      wsCnrSelMask      = (wsStart<<0)|(wsStart<<1), // Zum Ausmaskieren der Sel-Styles
      // Container-Views (exklusiv):
      wsCnrColumnView   = (wsStart<<2),              // View: Tabellarisch (Spalten) (Default)
      wsCnrIconView     = (wsStart<<3),              // View: Frei anordenbare Icons
      wsCnrListView     = (wsStart<<2)|(wsStart<<3), // View: Icons in Listenform angeordnet
      wsCnrViewMask     = (wsStart<<2)|(wsStart<<3), // Zum Ausmaskieren der View-Styles
      // Nur fuer ColumnView:
      wsCnrNoHeader     = wsStart << 4,      // Keine Spaltentitel anzeigen
      wsCnrNoHeaderBtn  = wsStart << 5,      // Spaltentitel nicht wie Buttons
      wsCnrNoHeaderDrag = wsStart << 6,      // Spaltentitel nicht anordenbar
      wsCnrFullRowSel   = wsStart << 7,      // Stets ganze Zeile selektieren
      wsCnrGridLines    = wsStart << 8,      // Tabellenrahmen um Elemente
      // Nur fuer IconView:
      wsCnrSmallIcons   = wsStart << 4,      // Kleine Icons verwenden
      wsCnrAutoArrange  = wsStart << 5,      // Icons automatisch anordnen
      // Weitere:
      wsCnrCheckBtns    = wsStart << 9,      // Checkbuttons sind moeglich
      wsUser            = wsStart << 10      // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0,
               int style = wsChild | wsVisible | wsTabStop | wsCnrColumnView | wsCnrExtendedSel,
               const cdRect& rect = cdRect());
   // Liste zugeordneter Icons initialisieren
   void setIconList(const cwIconList& ilist);


   // Spalten
   // =======

   // Anzahl Spalten erfragen
   int getColumnCount() const;

   // Neue Spaltenbreite in Pixel setzen (-1 = Autosize)
   bool setColumnWidth(int col, int pix_width = -1, bool use_header = false);
   // Spaltenbreite in Pixel erfragen
   int getColumnWidth(int col) const;

   // Anordnung der Spalten setzen ('order' enthaelt Indizes in Reihenfolge der Spalten)
   bool setColumnOrder(int count, int order[]);
   // Anordnung der Spalten erfragen
   bool getColumnOrder(int count, int order[]) const;


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um den Klick auf einen Spaltentitel bekanntzugeben
   virtual void onColumnClick(int column_idx);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, wenn ein Element selektiert wurde
   void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   void onListElemSelected(cwListElem *elem);

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

   // Wird aufgerufen, um sicherzustellen, dass Element 'elem' sichtbar ist
   bool onEnsureElemVisible(cwListElem *elem, bool partial_ok);
   // Wird aufgerufen, um sicherzustellen, dass Feld 'fld' sichtbar ist
   bool onEnsureFieldVisible(int fld, bool partial_ok);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   bool onRemoveElem(cwListElem *elem, bool invd);
   // Wird aufgerufen, um alle Elemente von der Anzeige zu entfernen
   bool onRemoveAllElems(cwListElem *parent, bool invd);

   // Wird aufgerufen, um ein Element ueber dessen Index zu ermitteln
   cwListElem * onGetElemWithIndex(int idx) const;
   // Wird aufgerufen, um das Rechteck fuer das Edit-Control zu ermitteln
   cdRect onGetEditRect(cwListElem *elem, int fld) const;

   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);

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

   // Wird aufgerufen, wenn sich die Spalten- oder Zeilenzahl (pro DS) geaendert hat
   void onSetupRowCol(const SETUP_ROWCOL_INFO& info);
   // Wird aufgerufen, um in Spalte das Feld 'fld' zur Anzeige vorzubereiten
   void onSetupField(int fld, const SETUP_FIELD_INFO& info);

   // Fenster wird erzeugt
   bool onCreate();

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwContainer(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwContainer
// ===========================================================================

cwContainer::cwContainer(void *wnd) :
   cwListCtl(wnd)
{
}

cwContainer::~cwContainer()
{
}

void cwContainer::init()
{
   #if defined __ECL_W32__
      _wnd = new WCListCtrl(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwContainer::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                         int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= LVS_ALIGNTOP | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_EDITLABELS;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCListCtrl*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create list control"));
      ((WCListCtrl*)_wnd)->SetExtendedStyle(mfc_style[1]);

   #else
      // ...
   #endif
}

void cwContainer::setIconList(const cwIconList& ilist)
{
   #if defined __ECL_W32__
      ((WCListCtrl*)_wnd)->SetImageList((WCImageList*)ccwIconList::__getIList(&ilist), LVSIL_SMALL);
   #else
      // ...
   #endif
}


// Spalten
// =======

int cwContainer::getColumnCount() const
{
   #if defined __ECL_W32__
      WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      CHeaderCtrl* mfc_hdr = mfc_list->GetHeaderCtrl();
      return mfc_hdr != 0 ? mfc_hdr->GetItemCount() : 0;
   #else
      // ...
   #endif
}

bool cwContainer::setColumnWidth(int col, int pix_width, bool use_header)
{
   if ( __ECL_ASSERT1__(col >= 0 && col < getColumnCount()) ) {
      #if defined __ECL_W32__
         if ( pix_width < 0 )
            pix_width = use_header ? LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE;
         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
         return !!mfc_list->SetColumnWidth(col, pix_width);
      #else
         // ...
      #endif
   }

   return false;
}

int cwContainer::getColumnWidth(int col) const
{
   if ( __ECL_ASSERT1__(col >= 0 && col < getColumnCount()) ) {
      #if defined __ECL_W32__
         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
         return mfc_list->GetColumnWidth(col);
      #else
         // ...
      #endif
   }

   return 0;
}

bool cwContainer::setColumnOrder(int count, int order[])
{
   if ( __ECL_ASSERT1__(count > 0 && order != 0)
     && __ECL_ASSERT1__(count == getColumnCount()) )
   {
      #if defined __ECL_W32__
         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
         return !!mfc_list->SetColumnOrderArray(count, order);
      #else
         // ...
      #endif
   }

   return false;
}

bool cwContainer::getColumnOrder(int count, int order[]) const
{
   if ( __ECL_ASSERT1__(count > 0 && order != 0)
     && __ECL_ASSERT1__(count == getColumnCount()) )
   {
      #if defined __ECL_W32__
         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
         return !!mfc_list->GetColumnOrderArray(order, count);
      #else
         // ...
      #endif
   }

   return false;
}


// Hinzugefuegte Events
// ====================

void cwContainer::onColumnClick(int /*column_idx*/)
{
}


// Ueberschriebene Events
// ======================

void cwContainer::onSelectionChanged(cwListElem *elem)
{
   //cBase::DbgOut(0, "cwContainer::onSelectionChanged(%s)", elem ? (const char *)elem->getKey() : "<NULL>");
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onSelectionChanged(elem);
}

void cwContainer::onListElemSelected(cwListElem *elem)
{
   //cBase::DbgOut(0, "cwContainer::onListElemSelected(%s)", elem ? (const char *)elem->getKey() : "<NULL>");
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onListElemSelected(elem);
}


// Selektion
// ---------

int cwContainer::onGetSelectedElemCount(bool /*walk*/) const
{
   #if defined __ECL_W32__
      if ( getStyles(wsCnrSelMask) == wsCnrSingleSel ) {
         return 1;
      } else {
         return ((WCListCtrl*)_wnd)->GetSelectedCount();
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onGetSelectedElemCount(walk);
   #endif
}

cwListElem * cwContainer::onGetSelectedElem(cwListElem *elem, bool /*walk*/) const
{
   #if defined __ECL_W32__
      int idx = elem ? getElemCountFromBegin(elem) : -1;
      return getElemWithIndex(((WCListCtrl*)_wnd)->GetNextItem(idx, LVNI_SELECTED));
   #else if defined __ECL_OS2__
      // ???
   #endif
}

bool cwContainer::onSelectElem(cwListElem *elem, bool sel)
{
   #if defined __ECL_W32__
      if ( getStyles(wsCnrSelMask) == wsCnrSingleSel ) {
         return setCursoredElem(elem);
      } else {
         int idx = getElemCountFromBegin(elem);
         int val = sel ? LVIS_SELECTED : 0;
         return __ECL_ASSERT1__(((WCListCtrl*)_wnd)->SetItemState(idx, val, LVIS_SELECTED) != FALSE);
      }
   #else if defined __ECL_OS2__
      return SetLbxSelection(getElemCountFromBegin(elem), sel);
   #endif
}

bool cwContainer::onSelectAllElems(bool sel, cwListElem * /*parent*/, bool /*walk*/)
{
   #if defined __ECL_W32__
      if ( __ECL_ASSERT1__(getStyles(wsCnrSelMask) != wsCnrSingleSel) ) {
         int val = sel ? LVIS_SELECTED : 0;
         return __ECL_ASSERT1__(((WCListCtrl*)_wnd)->SetItemState(-1, val, LVIS_SELECTED) != FALSE);
      } else {
         return false; // Kein SelectAll moeglich...
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onSelectAllElems(sel, parent, walk);
   #endif
}


// Cursor
// ------

cwListElem * cwContainer::onGetCursoredElem() const
{
   #if defined __ECL_W32__
      return getElemWithIndex(((WCListCtrl*)_wnd)->GetNextItem(-1, LVNI_FOCUSED));
   #else if defined __ECL_OS2__
      return GetItemHandle(GetLbxSelection(LIT_CURSOR));
   #endif
}

bool cwContainer::onSetCursoredElem(cwListElem *elem)
{
   bool rc = false;

   if ( elem != 0 ) {
      #if defined __ECL_W32__
         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
         int idx = getElemCountFromBegin(elem);
         int state = LVIS_FOCUSED | (getStyles(wsCnrSelMask) == wsCnrSingleSel ? LVIS_SELECTED : 0);
         elem->setFlags(cwListElem::eflPreventSelect, true);
         rc = __ECL_ASSERT1__(mfc_list->SetItemState(idx, state, state) != FALSE);
         if ( rc ) rc = __ECL_ASSERT1__(mfc_list->EnsureVisible(idx, TRUE) != FALSE);
         elem->setFlags(cwListElem::eflPreventSelect, false);
      #else if defined __ECL_OS2__
         return Select(elem);
      #endif
   }

   return rc;
}


// Sichtbarkeit
// ------------

bool cwContainer::onEnsureElemVisible(cwListElem *elem, bool partial_ok)
{
   #if defined __ECL_W32__
      WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      int idx = getElemCountFromBegin(elem);
      return __ECL_ASSERT1__(mfc_list->EnsureVisible(idx, partial_ok) != FALSE);
   #else if defined __ECL_OS2__
      // ...
   #endif
}

bool cwContainer::onEnsureFieldVisible(int fld, bool /*partial_ok*/)
{
   int col = getColumnFromField(fld);

   if ( col >= 0 ) {

      #if defined __ECL_W32__

         WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      	int iColWidth = mfc_list->GetColumnWidth(col);
      	if ( col >= getColumnCount() || iColWidth < 5 )
            return false;

      	int offset = 0;
      	for ( int i = 0 ; i < col ; i++ )
            offset += mfc_list->GetColumnWidth(i);

      	CRect rect, subRect;
      	mfc_list->GetItemRect(0, &rect, LVIR_BOUNDS);
      	subRect.SetRect(offset + rect.left, 0, offset + iColWidth + rect.left, 0);

      	CRect rcClient;
      	mfc_list->GetClientRect(&rcClient);

      	if ( subRect.left < rcClient.left ) {
      		CSize sz(rcClient.left + subRect.left, 0);
      		mfc_list->Scroll(sz);
      		return true;
      	} else if ( subRect.right > rcClient.right ) {
      		CSize sz(subRect.right - rcClient.right, 0);
      		mfc_list->Scroll(sz);
      		return true;
      	}

      	return true;

      #else if defined __ECL_OS2__

         // ...

      #endif

   }

   return false;
}


// Einfuegen/Loeschen
// ------------------

bool cwContainer::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem * /*parent*/, bool /*invd*/)
{
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      int idx, new_idx;
      WCListCtrl *mfc_ctrl = (WCListCtrl*)_wnd;

      if ( ref_elem == 0 && pos < 0 ) {
         new_idx = mfc_ctrl->elems.getSize();
         mfc_ctrl->elems.add(new_elem);
         idx = mfc_ctrl->InsertItem(new_idx, new_elem->getName());
      } else if ( ref_elem == 0 && pos > 0 ) {
         mfc_ctrl->elems.insertAt(new_idx = 0, new_elem);
         idx = ((WCListCtrl*)_wnd)->InsertItem(new_idx, new_elem->getName());
      } else if ( pos < 0 ) {
         // WICHTIG: -1, da neues Element schon in Liste eingehaengt und von getElemCount...() beruecksichtigt
         mfc_ctrl->elems.insertAt(new_idx = getElemCountFromBegin(ref_elem)-1, new_elem);
         idx = ((WCListCtrl*)_wnd)->InsertItem(new_idx, new_elem->getName());
      } else {
         mfc_ctrl->elems.insertAt(new_idx = getElemCountFromBegin(ref_elem)+1, new_elem);
         idx = ((WCListCtrl*)_wnd)->InsertItem(getElemCountFromBegin(ref_elem)+1, new_elem->getName());
      }

      if ( __ECL_ASSERT1__(idx >= 0) ) {
         return true;
      } else {
         mfc_ctrl->elems.removeAt(new_idx);
         return false;
      }

   #else if defined __ECL_OS2__
      // ???
   #endif
}

bool cwContainer::onRemoveElem(cwListElem *elem, bool /*invd*/)
{
   bool rc = false;

   #if defined __ECL_W32__
      WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      if ( mfc_list != 0 && mfc_list->m_hWnd != 0 ) {
         int idx = getElemCountFromBegin(elem);
         rc = __ECL_ASSERT1__(mfc_list->DeleteItem(idx) != 0);
         if ( rc ) mfc_list->elems.removeAt(idx);
      }
   #else if defined __ECL_OS2__
      // ???
   #endif

   return rc;
}

bool cwContainer::onRemoveAllElems(cwListElem * /*parent*/, bool /*invd*/)
{
   bool rc = true;

   #if defined __ECL_W32__
      WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      if ( mfc_list != 0 && mfc_list->m_hWnd != 0 ) {
         rc = __ECL_ASSERT1__(mfc_list->DeleteAllItems() != 0);
         if ( rc ) mfc_list->elems.removeAll();
      }
   #else if defined __ECL_OS2__
      // ???
   #endif

   return rc;
}


// Elementverwaltung
// -----------------

cwListElem * cwContainer::onGetElemWithIndex(int idx) const
{
   return _wnd != 0 && idx >= 0 && idx < ((WCListCtrl*)_wnd)->elems.getSize() ?
      ((WCListCtrl*)_wnd)->elems[idx]
    : 0;
}

cdRect cwContainer::onGetEditRect(cwListElem *elem, int fld) const
{
   #if defined __ECL_W32__

      CListCtrl *mfc_list = (WCListCtrl*)_wnd;

      if ( mfc_list != 0 && mfc_list->m_hWnd != 0 ) {
         int nItem = getElemCountFromBegin(elem);
         int nCol = getColumnFromField(fld);
      	int nColumnCount = getColumnCount();
      	int iColWidth = mfc_list->GetColumnWidth(nCol);

      	if ( nCol < nColumnCount && iColWidth > 4 ) {
            int offset = 0;
            for ( int i = 0 ; i < nCol ; i++ )
               offset += mfc_list->GetColumnWidth(i);

            CRect rect;
            mfc_list->GetItemRect(nItem, &rect, LVIR_BOUNDS);

            // Why? rect.bottom--;
            rect.left += offset;
            rect.right = rect.left + mfc_list->GetColumnWidth(nCol);
            return cdRect(rect.left, rect.bottom, rect.right, rect.top);
         }
      }

   #else if defined __ECL_OS2__
      // ???
   #endif

   return cdRect();
}


// Abfrage
// -------

bool cwContainer::onQueryStarted(csQuery *query)
{
/*TEST*/
//   ((WCListCtrl*)_wnd)->SetExtendedStyle(((WCListCtrl*)_wnd)->GetExtendedStyle()
//      | LVS_EX_FULLROWSELECT | /*LVS_EX_GRIDLINES |*/ LVS_EX_HEADERDRAGDROP);
/*TEST*/

   setRedraw(false);
   return cwListCtl::onQueryStarted(query);
}

bool cwContainer::onQueryEnded(csQuery *query)
{
   bool ok = cwListCtl::onQueryEnded(query);
   if ( query != 0 && !query->getFlags(csQuery::fStopReq) )
      setRedraw(true);
   return ok;
}

// ---

bool cwContainer::onQuery1Started(cwListElem *elem, csQuery *query)
{
   setRedraw(false);
   return cwListCtl::onQuery1Started(elem, query);
}

bool cwContainer::onQuery1Data(cwListElem *elem, csQuery *query)
{
   if ( elem != 0 && cwListCtl::onQuery1Data(elem, query) ) {
      elem->refresh(query);
      return true;
   }

   return false;
}

bool cwContainer::onQuery1Ended(cwListElem *elem, csQuery *query)
{
   bool ok = cwListCtl::onQuery1Ended(elem, query);
   setRedraw(true);

   #if defined __ECL_W32__
      WCListCtrl *mfc_list = (WCListCtrl*)_wnd;
      if ( mfc_list != 0 && mfc_list->m_hWnd != 0 ) {
         int idx = getElemCountFromBegin(elem);
         mfc_list->Update(idx);
      }
   #else if defined __ECL_OS2__
      // ???
   #endif

   return ok;
}

// ---

bool cwContainer::onInsQueryStarted(cwListElem *before, cwListElem *parent, csQuery *query)
{
   setRedraw(false);
   return cwListCtl::onInsQueryStarted(before, parent, query);
}

bool cwContainer::onInsQueryData(cwListElem *before, cwListElem *parent, csQuery *query)
{
   cwListElem *new_elem = new1(this) cwListElem(query);

   if ( new_elem->getUserDataLen() > 0 )
      query->getUserData(new_elem->getUserDataBuf(), new_elem->getUserDataLen());

   return insertElemBefore(new_elem, before, parent);
}

bool cwContainer::onInsQueryEnded(cwListElem *before, cwListElem *parent, csQuery *query)
{
   bool ok = cwListCtl::onInsQueryEnded(before, parent, query);
   setRedraw(true);
   return ok;
}

// ---

void cwContainer::onSetupRowCol(const SETUP_ROWCOL_INFO& info)
{
   #if defined __ECL_W32__
      // Ueberfluessige Spalten entfernen
      int old_column_count = info.old_column_count;
      while ( old_column_count > info.new_column_count )
         ((WCListCtrl*)_wnd)->DeleteColumn(--old_column_count);
   #else if defined __ECL_OS2__
      // ???
   #endif
}

void cwContainer::onSetupField(int /*fld*/, const SETUP_FIELD_INFO& info)
{
   #if defined __ECL_W32__

      LVCOLUMN lvc;
      char title[128];
      const cString& dt = info.descr->title;
      strxcpy(title, dt.isEmpty() ? "" : dt, sizeof title);

      switch ( info.descr->halign ) {
      case csQuery::haLeft:   lvc.fmt = LVCFMT_LEFT; break;
      case csQuery::haRight:  lvc.fmt = LVCFMT_RIGHT; break;
      case csQuery::haCenter: lvc.fmt = LVCFMT_CENTER; break;
      }

      int pix_width = 75;
      TEXTMETRIC tm;
      CClientDC cdc((WCListCtrl*)_wnd);
      if ( cdc.GetOutputTextMetrics(&tm) )
         pix_width = info.descr->disp_width * tm.tmAveCharWidth;

      #define __Add_Pix_Border__
      #ifdef __Add_Pix_Border__
         pix_width += 10;
      #endif

      lvc.mask     = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
      lvc.cx       = min_max(pix_width, 35, 375);
      lvc.pszText  = title;
      lvc.iSubItem = info.disp_col;

      if ( info.add ) {
         ((WCListCtrl*)_wnd)->InsertColumn(info.disp_col, &lvc);
      } else {
         ((WCListCtrl*)_wnd)->SetColumn(info.disp_col, &lvc);
      }

   #else if defined __ECL_OS2__
      // ???
   #endif
}


// Sonstiges
// =========

bool cwContainer::onCreate()
{
   ((CListCtrl*)_wnd)->ModifyStyle(0, LVS_EDITLABELS);
   return cwListCtl::onCreate();
}


// Window-Styles
// =============

#if defined __ECL_W32__
   #define LVS_SEL_MASK LVS_SINGLESEL
   #define LVS_VIEW_MASK LVS_TYPEMASK
   #define LVS_ISSEL(m,s) (((m) & LVS_SEL_MASK) == s)
   #define LVS_ISVIEW(m,s) (((m) & LVS_VIEW_MASK) == s)
#endif

int cwContainer::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCListCtrl*)_wnd)->GetStyle();
      DWORD ex_style = ((WCListCtrl*)_wnd)->GetExtendedStyle();

      if ( (mask & wsCnrSelMask) == wsCnrSingleSel && LVS_ISSEL(style,LVS_SINGLESEL) ) {
         rc = (rc & ~wsCnrSelMask) | wsCnrSingleSel;
      } else if ( (mask & wsCnrSelMask) == wsCnrExtendedSel && !LVS_ISSEL(style,LVS_SINGLESEL) ) {
         rc = (rc & ~wsCnrSelMask) | wsCnrExtendedSel;
      } else if ( (mask & wsCnrSelMask) == wsCnrMultipleSel && !LVS_ISSEL(style,LVS_SINGLESEL) ) {
         rc = (rc & ~wsCnrSelMask) | wsCnrMultipleSel;
      }

      if ( (mask & wsCnrViewMask) == wsCnrIconView && (LVS_ISVIEW(style,LVS_ICON) || LVS_ISVIEW(style,LVS_SMALLICON)) ) {
         rc = (rc & ~wsCnrViewMask) | wsCnrIconView;
      } else if ( (mask & wsCnrViewMask) == wsCnrListView && LVS_ISVIEW(style,LVS_LIST) ) {
         rc = (rc & ~wsCnrViewMask) | wsCnrListView;
      } else if ( (mask & wsCnrViewMask) == wsCnrColumnView && LVS_ISVIEW(style,LVS_REPORT) ) {
         rc = (rc & ~wsCnrViewMask) | wsCnrColumnView;
      }

      if ( (mask & wsCnrCheckBtns) && (ex_style & LVS_EX_CHECKBOXES) )
         rc |= wsCnrCheckBtns;

      if ( LVS_ISVIEW(style,LVS_ICON) || LVS_ISVIEW(style,LVS_SMALLICON) ) {

         if ( (mask & wsCnrSmallIcons) && LVS_ISVIEW(style,LVS_SMALLICON) )
            rc |= wsCnrSmallIcons;
         if ( (mask & wsCnrAutoArrange) && (style & LVS_AUTOARRANGE) )
            rc |= wsCnrAutoArrange;

      } else if ( style & LVS_REPORT ) {

         if ( (mask & wsCnrNoHeader) && (style & LVS_NOCOLUMNHEADER) )
            rc |= wsCnrNoHeader;
         if ( (mask & wsCnrNoHeaderBtn) && (style & LVS_NOSORTHEADER) )
            rc |= wsCnrNoHeaderBtn;
         if ( (mask & wsCnrNoHeaderDrag) && !(ex_style & LVS_EX_HEADERDRAGDROP) )
            rc |= wsCnrNoHeaderDrag;
         if ( (mask & wsCnrFullRowSel) && !(ex_style & LVS_EX_FULLROWSELECT) )
            rc |= wsCnrFullRowSel;
         if ( (mask & wsCnrGridLines) && !(ex_style & LVS_EX_GRIDLINES) )
            rc |= wsCnrGridLines;

      }

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwListCtl::onGetStyles(mask);
}

void cwContainer::onMakeStyles(int styles, int os_styles[]) const
{
   cwListCtl::onMakeStyles(styles, os_styles);

   #if defined __ECL_W32__

      if ( (styles & wsCnrSelMask) == wsCnrSingleSel ) {
         os_styles[0] = (os_styles[0] & ~LVS_SEL_MASK) | LVS_SINGLESEL;
      } else if ( (styles & wsCnrSelMask) == wsCnrMultipleSel ) {
         os_styles[0] = (os_styles[0] & ~LVS_SEL_MASK);
      } else if ( (styles & wsCnrSelMask) == wsCnrExtendedSel || (styles & wsCnrSelMask) == 0) {
         os_styles[0] = (os_styles[0] & ~LVS_SEL_MASK);
      }

      if ( (styles & wsCnrViewMask) == wsCnrListView ) {
         os_styles[0] = (os_styles[0] & ~LVS_VIEW_MASK) | LVS_LIST;
      } else if ( (styles & wsCnrViewMask) == wsCnrIconView ) {

         if ( styles & wsCnrSmallIcons ) {
            os_styles[0] = (os_styles[0] & ~LVS_VIEW_MASK) | LVS_SMALLICON;
         } else {
            os_styles[0] = (os_styles[0] & ~LVS_VIEW_MASK) | LVS_ICON;
         }

         if ( styles & wsCnrAutoArrange )
            os_styles[0] |= LVS_AUTOARRANGE;

      } else if ( (styles & wsCnrViewMask) == wsCnrColumnView || (styles & wsCnrViewMask) == 0 ) {

         os_styles[0] = (os_styles[0] & ~LVS_VIEW_MASK) | LVS_REPORT;

         if ( styles & wsCnrNoHeader )
            os_styles[0] |= LVS_NOCOLUMNHEADER;
         if ( styles & wsCnrNoHeaderBtn )
            os_styles[0] |= LVS_NOSORTHEADER;
         if ( !(styles & wsCnrNoHeaderDrag) )
            os_styles[1] |= LVS_EX_HEADERDRAGDROP;
         if ( styles & wsCnrFullRowSel )
            os_styles[1] |= LVS_EX_FULLROWSELECT;
         if ( styles & wsCnrGridLines )
            os_styles[1] |= LVS_EX_GRIDLINES;

      }

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwContainer::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      DWORD style = ((WCListCtrl*)_wnd)->GetStyle();
      DWORD ex_style = ((WCListCtrl*)_wnd)->GetExtendedStyle();
      DWORD cur_view = style & LVS_VIEW_MASK, new_view = cur_view;

      if ( (add & wsCnrSelMask) == wsCnrSingleSel ) {
         os_add[0] |= LVS_SINGLESEL;
      } else if ( (add & wsCnrSelMask) == wsCnrMultipleSel ) {
         os_remove[0] |= LVS_SINGLESEL;
      } else if ( (add & wsCnrSelMask) == wsCnrExtendedSel ) {
         os_remove[0] |= LVS_SINGLESEL;
      }

      if ( (add & wsCnrViewMask) == wsCnrListView ) {
         os_add[0] = (os_add[0] & ~LVS_VIEW_MASK) | (new_view = LVS_LIST);
      } else if ( (add & wsCnrViewMask) == wsCnrIconView ) {
         os_add[0] = (os_add[0] & ~LVS_VIEW_MASK) | (new_view = LVS_ICON);
      } else if ( (add & wsCnrViewMask) == wsCnrColumnView ) {
         os_add[0] = (os_add[0] & ~LVS_VIEW_MASK) | (new_view = LVS_REPORT);
      }

      // Remove von wsCnrXxxxSel und wsCnrXxxxView wird ignoriert,
      // da jeweils nur einer der Styles gueltig sein kann.

      if ( cur_view == LVS_ICON || new_view == LVS_ICON ) {

         if ( (add & wsCnrSmallIcons) || (style & LVS_SMALLICON) && !(remove & wsCnrSmallIcons) ) {
            os_add[0] = (os_add[0] & ~LVS_VIEW_MASK) | LVS_SMALLICON;
         } else {
            os_add[0] = (os_add[0] & ~LVS_VIEW_MASK) | LVS_ICON;
         }

         if ( add & wsCnrAutoArrange )
            os_add[0] |= LVS_AUTOARRANGE;
         if ( remove & wsCnrAutoArrange )
            os_remove[0] |= LVS_AUTOARRANGE;

      } else if ( cur_view == LVS_REPORT || new_view == LVS_REPORT ) {

         if ( add & wsCnrNoHeader )
            os_add[0] |= LVS_NOCOLUMNHEADER;
         if ( add & wsCnrNoHeaderBtn )
            os_add[0] |= LVS_NOSORTHEADER;
         if ( add & wsCnrNoHeaderDrag )
            ex_style &= ~LVS_EX_HEADERDRAGDROP;
         if ( add & wsCnrFullRowSel )
            ex_style |= LVS_EX_FULLROWSELECT;
         if ( add & wsCnrGridLines )
            ex_style |= LVS_EX_GRIDLINES;

         if ( remove & wsCnrNoHeader )
            os_remove[0] |= LVS_NOCOLUMNHEADER;
         if ( remove & wsCnrNoHeaderBtn )
            os_remove[0] |= LVS_NOSORTHEADER;
         if ( remove & wsCnrNoHeaderDrag )
            ex_style |= LVS_EX_HEADERDRAGDROP;
         if ( remove & wsCnrFullRowSel )
            ex_style &= ~LVS_EX_FULLROWSELECT;
         if ( remove & wsCnrGridLines )
            ex_style &= ~LVS_EX_GRIDLINES;

      }

      cwListCtl::onModifyStyles(add, remove, os_add, os_remove);

      if ( ex_style != ((WCListCtrl*)_wnd)->GetExtendedStyle() )
         ((WCListCtrl*)_wnd)->SetExtendedStyle(ex_style);

   #elif defined __ECL_OS2__

      // ...

   #endif
}


