// ===========================================================================
// ew_gridctls.cpp                                              ______ /  ECL
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
//              +-cwGrid   - Grid-Control
//
// ===========================================================================

#include "win/ew_gridctls.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_listctls.hpp"
#include "store/es_var.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwGrid
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwGrid
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwGrid : public cwListCtl {
   ELO_DECLARE(cwGrid,cwListCtl)
   friend class ccwGrid;

public:

   // Konstruktor
   inline cwGrid() : cwListCtl(0) { init(); }
   // Destruktor
   virtual ~cwGrid();


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
      wsDatabase        = wsStart << 0,   // Verwendung als Datenbank-Grid
      wsCanSizeRows     = wsStart << 1,   // Zeilen veraenderbar?
      wsCanSizeCols     = wsStart << 2,   // Spalten veraenderbar?
      wsCanSizeRowHead  = wsStart << 3,   // Zeilenkopf veraenderbar?
      wsCanSizeColHead  = wsStart << 4,   // Spaltenkopf veraenderbar?
      wsUser            = wsStart << 5    // Benutzerdefinierte Styles
   };


protected:

   // Hinzugefuegte Events
   // ====================

   // Darf die Groesse von Spalte 'col' veraendert werden?
   virtual bool onCanSizeColumn(int col);
   // Darf die Groesse von Zeile 'row' veraendert werden?
   virtual bool onCanSizeRow(int row);
   // Darf die Groesse der Spaltenkoepfe veraendert werden?
   virtual bool onCanSizeColumnHead();
   // Darf die Groesse der Zeilenkoepfe veraendert werden?
   virtual bool onCanSizeRowHead();

   // Wird aufgerufen, wenn sich die aktuelle Spalte geaendert hat
   virtual void onChangedColumn(int old_col, int new_col);
   // Wird aufgerufen, wenn sich die aktuelle Zeile geaendert hat
   virtual void onChangedRow(int old_row, int new_row);
   // Wird aufgerufen, wenn sich die aktuelle Zelle geaendert hat
   virtual void onChangedCell(int old_col, int new_col, int old_row, int new_row);

   // Wird aufgerufen, wenn eine Zelle angeklickt wurde
   virtual void onClickCell(int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn ein Spaltenkopf angeklickt wurde
   virtual void onClickColumnHead(int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn ein Zeilenkopf angeklickt wurde
   virtual void onClickRowHead(int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn die linke obere Ecke angeklickt wurde
   virtual void onClickCorner(const cwCmdMouse& cmd);


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

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   bool onRemoveElem(cwListElem *elem, bool invd);
   // Wird aufgerufen, um alle Elemente von der Anzeige zu entfernen
   bool onRemoveAllElems(cwListElem *parent, bool invd);

   // Wird aufgerufen, um ein Element ueber dessen Index zu ermitteln
   cwListElem * onGetElemWithIndex(int idx) const;

   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);

   // Wird aufgerufen, um zu erfragen, ob mehrere Zeilen pro Datensatz unterstuetzt werden
   bool onAllowsMultipleRows() const;
   // Wird aufgerufen, wenn sich die Spalten- oder Zeilenzahl (pro DS) geaendert hat
   void onSetupRowCol(const SETUP_ROWCOL_INFO& info);
   // Wird aufgerufen, um in Spalte das Feld 'fld' zur Anzeige vorzubereiten
   void onSetupField(int fld, const SETUP_FIELD_INFO& info);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);

   // Attach mit Wrapper-Objekt durchfuehren
   void onAttach(int id, void *wnd);


protected:

   // Interner Konstruktor
   cwGrid(void *wnd);


private:

   // Intern: Eigene Styles
   int own_style;

   // Intern: Initialisierung
   void init();

   // Intern: 'n' Zeilen zum Grid hinzufuegen
   bool appendRows(int n);
   // Intern: 'n' Zeilen vor Zeile 'before_row' in das Grid einfuegen
   bool insertRows(int n, int before_row);
   // Intern: 'n' Zeilen beginnend mit Zeile 'from_row' loeschen
   bool removeRows(int n, int from_row);
   // Intern: Joins fuer Element an Position 'idx' einstellen
   void setupJoins(int idx);

   // Intern: Spalte(n) markieren
   void selectCols(int from_col, int to_col);
   // Intern: Zeile(n) markieren
   void selectRows(int from_row, int to_row);
   // Intern: Bereich markieren
   void selectArea(int from_col, int to_col, int from_row, int to_row);
   // Intern: Selektion loeschen
   void clearSelection();

};

#endif /*__INTERFACE__*/


// Implementierung cwGrid
// ===========================================================================

#if defined __ECL_W32__
   // Maske fuer eigene Style-Bits
   #define WS_OWN_MASK ( \
      wsDatabase         \
    | wsCanSizeCols      \
    | wsCanSizeRows      \
    | wsCanSizeColHead   \
    | wsCanSizeRowHead   \
   )
#endif

cwGrid::cwGrid(void *wnd) :
   cwListCtl(wnd)
{
   own_style = 0;
}

cwGrid::~cwGrid()
{
}

void cwGrid::init()
{
   own_style = 0;

   #if defined __ECL_W32__
      _wnd = new WCGridCtrl(this);
   #elif defined __ECL_OS2__
   #endif
}


// Internes
// ========

bool cwGrid::appendRows(int n)
{
   #if defined __ECL_W32__
      while ( n-- > 0 ) {
         if ( !__ECL_ASSERT1__(((WCGridCtrl*)_wnd)->AppendRow() == 0) )
            return false;
      }
   #endif

   return true;
}

bool cwGrid::insertRows(int n, int before_row)
{
   #if defined __ECL_W32__
      while ( n-- > 0 ) {
         if ( !__ECL_ASSERT1__(((WCGridCtrl*)_wnd)->InsertRow(before_row) == 0) )
            return false;
      }
   #endif

   return true;
}

bool cwGrid::removeRows(int n, int from_row)
{
   #if defined __ECL_W32__
      while ( n-- > 0 ) {
         if ( !__ECL_ASSERT1__(((WCGridCtrl*)_wnd)->DeleteRow(from_row) == 0) )
            return false;
      }
   #endif

   return true;
}

void cwGrid::setupJoins(int idx)
{
   #if defined __ECL_W32__

      int row_count = getRowCount();
      int col_count = getColumnCount();
      WCGridCtrl *ug = (WCGridCtrl*)_wnd;
      cwListElem *elem = getElemWithIndex(idx);

      if ( row_count > 1 )
         ug->JoinCells(-1, idx*row_count, -1, idx*row_count + row_count - 1);

      for ( int r = 0 ; r < row_count ; r++ ) {
         for ( int c = 0 ; c < col_count ; c++ ) {
            /*TBD: Weg hier! Bloss wohin?*/ if ( r == 1 ) ug->QuickSetBackColor(c, idx*row_count + r, RGB(240,240,240));
            int fld = getFieldFromColumn(c, r);
            cString value;
            if ( fld >= 0 && elem->get(fld, value) ) {
               int join_x = getJoinColumns(fld);
               int join_y = getJoinRows(fld);
               if ( join_x > 0 || join_y > 0 ) {
                  ug->JoinCells(c, idx*row_count + r, c + join_x, idx*row_count + r + join_y);
                  /*TBD: Weg hier! Multiline-Flag in csQuery! */ug->QuickSetCellTypeEx(c, idx*row_count+r, UGCT_NORMALMULTILINE);
               }
            }
         }
      }

   #endif
}

void cwGrid::selectCols(int from_col, int to_col)
{
   #if defined __ECL_W32__
      WCGridCtrl *ug = (WCGridCtrl*)_wnd;
      ug->EnableUpdate(FALSE);
      ug->GotoCol(from_col);
      ug->SetMultiSelectMode(TRUE);
      ug->SetCurrentCellMode(2/*UG_CELLMODE_HIGHLIGHT*/);
      ug->SelectRange(from_col, 0, to_col, ug->GetNumberRows()-1);
      ug->EnableUpdate(TRUE);
   #endif
}

void cwGrid::selectRows(int from_row, int to_row)
{
   #if defined __ECL_W32__
      WCGridCtrl *ug = (WCGridCtrl*)_wnd;
      ug->EnableUpdate(FALSE);
      ug->GotoRow(from_row);
      ug->SetMultiSelectMode(TRUE);
      ug->SetCurrentCellMode(2/*UG_CELLMODE_HIGHLIGHT*/);
      ug->SelectRange(0, from_row, ug->GetNumberCols()-1, to_row);
      ug->EnableUpdate(TRUE);
   #endif
}

void cwGrid::selectArea(int from_col, int to_col, int from_row, int to_row)
{
   #if defined __ECL_W32__
      WCGridCtrl *ug = (WCGridCtrl*)_wnd;
      ug->EnableUpdate(FALSE);
      // ug->GotoCell(from_col, to_col);
      ug->SetMultiSelectMode(TRUE);
      ug->SetCurrentCellMode(2/*UG_CELLMODE_HIGHLIGHT*/);
      ug->SelectRange(from_col, from_row, to_col, to_row);
      ug->EnableUpdate(TRUE);
   #endif
}

void cwGrid::clearSelection()
{
   #if defined __ECL_W32__
      WCGridCtrl *ug = (WCGridCtrl*)_wnd;
      ug->EnableUpdate(FALSE);
      ug->ClearSelections();
      ug->SetCurrentCellMode(1/*UG_CELLMODE_FOCUS*/);
      ug->SetMultiSelectMode(FALSE);
      ug->EnableUpdate(TRUE);
   #endif
}


// Allgemeines
// ===========

void cwGrid::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                         int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);

   #if defined __ECL_W32__

      if ( style & WS_OWN_MASK )
         own_style = (style & WS_OWN_MASK);

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style = WS_CHILD | WS_VISIBLE | WS_BORDER /*| LVS_REPORT | LVS_ALIGNTOP | LVS_OWNERDATA*/;
      //if ( style & wsCnrSingleSel ) mfc_style |= LVS_SINGLESEL;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCGridCtrl*)_wnd)->CreateGrid(mfc_style, mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create grid control"));

   #else
      // ...
   #endif
}

void cwGrid::setIconList(const cwIconList& ilist)
{
   #if defined __ECL_W32__
      //((WCTreeCtrl*)_wnd)->SetImageList((WCImageList*)ccwIconList::__getIList(&ilist), LVSIL_SMALL);
   #else
      // ...
   #endif
}


// Hinzugefuegte Events
// ====================

bool cwGrid::onCanSizeColumn(int /*col*/)
{
   return !!getStyles(wsCanSizeCols);
}

bool cwGrid::onCanSizeRow(int row)
{
   if ( getStyles(wsDatabase) ) {
      int row_count = getRowCount();
      if ( row % row_count != row_count - 1 )
         return false;
   }

   return !!getStyles(wsCanSizeRows);
}

bool cwGrid::onCanSizeColumnHead()
{
   return !!getStyles(wsCanSizeColHead);
}

bool cwGrid::onCanSizeRowHead()
{
   return !!getStyles(wsCanSizeRowHead);
}

void cwGrid::onChangedColumn(int old_col, int new_col)
{
}

void cwGrid::onChangedRow(int old_row, int new_row)
{
   if ( getStyles(wsDatabase) ) {
      int row_count = getRowCount();
      if ( row_count > 0 ) {
         old_row = (old_row / row_count) * row_count;
         new_row = (new_row / row_count) * row_count;
         #if defined __ECL_W32__
            WCGridCtrl *ug = (WCGridCtrl*)_wnd;
            ug->QuickSetText(-1, old_row, "");
            ug->QuickSetText(-1, new_row, ">");
         #endif
      }
   }
}

void cwGrid::onChangedCell(int old_col, int new_col, int old_row, int new_row)
{
}

void cwGrid::onClickCell(int col, int row, const cwCmdMouse& cmd)
{
   if ( getStyles(wsDatabase) ) {
      if ( cmd.wasClickLeftButton() ) {
         clearSelection();
      } else if ( cmd.wasClickRightButton() ) {
         clearSelection();
         int row_count = getRowCount();
         if ( row_count > 0 ) {
            row = (row / row_count) * row_count;
            selectRows(row, row + row_count - 1);
            if ( cmd.wasClickUp() ) {
               onContextMenu(cmd);
            }
         }
      }
   }

   if ( cmd.wasClickDbl() && cmd.wasClickLeftButton() ) {
      #if defined __ECL_W32__
         ((WCGridCtrl*)_wnd)->StartEdit();
      #endif
   }
}

void cwGrid::onClickColumnHead(int col, int row, const cwCmdMouse& cmd)
{
}

void cwGrid::onClickRowHead(int col, int row, const cwCmdMouse& cmd)
{
   int idx = row;

   if ( getStyles(wsDatabase) ) {
      int row_count = getRowCount();
      if ( row_count > 0 ) {
         row = (row / row_count) * row_count;
         selectRows(row, row + row_count - 1);
         idx = row / row_count;
      }
   }

   if ( cmd.wasClickLeftButton() ) {
      if ( cmd.wasClickDbl() ) {
         onListElemSelected(getElemWithIndex(idx));
      } else if ( cmd.wasClickDown() ) {
         onSelectionChanged(getElemWithIndex(idx));
      }
   } else if ( cmd.wasClickRightButton() && cmd.wasClickUp() ) {
      onContextMenu(cmd);
   }
}

void cwGrid::onClickCorner(const cwCmdMouse& cmd)
{
}


// Ueberschriebene Events
// ======================

void cwGrid::onSelectionChanged(cwListElem *elem)
{
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onSelectionChanged(elem);
}

void cwGrid::onListElemSelected(cwListElem *elem)
{
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onListElemSelected(elem);
}


// Selektion
// ---------

int cwGrid::onGetSelectedElemCount(bool /*walk*/) const
{
   /*TBD:*/return getCursoredElem() != 0 ? 1 : 0;

/*
   #if defined __ECL_W32__
      if ( getStyles(wsCnrSingleSel) ) {
         return 1;
      } else {
         return ((WCListCtrl*)_wnd)->GetSelectedCount();
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onGetSelectedElemCount(walk);
   #endif
*/
   return 0;
}

cwListElem * cwGrid::onGetSelectedElem(cwListElem *elem, bool /*walk*/) const
{
   /*TBD:*/return elem == 0 ? getCursoredElem() : 0;

/*
   #if defined __ECL_W32__
      int idx = elem ? getElemCountFromBegin(elem) : -1;
      return getElemWithIndex(((WCListCtrl*)_wnd)->GetNextItem(idx, LVNI_SELECTED));
   #else if defined __ECL_OS2__
      // ???
   #endif
*/
   return 0;
}

bool cwGrid::onSelectElem(cwListElem *elem, bool sel)
{
   /*TBD:*/return setCursoredElem(elem);

/*
   #if defined __ECL_W32__
      if ( getStyles(wsCnrSingleSel) ) {
         return setCursoredElem(elem);
      } else {
         int idx = getElemCountFromBegin(elem);
         int val = sel ? LVIS_SELECTED : 0;
         return __ECL_ASSERT1__(((WCListCtrl*)_wnd)->SetItemState(idx, val, LVIS_SELECTED) != FALSE);
      }
   #else if defined __ECL_OS2__
      return SetLbxSelection(getElemCountFromBegin(elem), sel);
   #endif
*/
   return true;
}

bool cwGrid::onSelectAllElems(bool sel, cwListElem * /*parent*/, bool /*walk*/)
{
/*
   #if defined __ECL_W32__
      if ( __ECL_ASSERT1__(!getStyles(wsCnrSingleSel)) ) {
         int val = sel ? LVIS_SELECTED : 0;
         return __ECL_ASSERT1__(((WCListCtrl*)_wnd)->SetItemState(-1, val, LVIS_SELECTED) != FALSE);
      } else {
         return false; // Kein SelectAll moeglich...
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onSelectAllElems(sel, parent, walk);
   #endif
*/
   return true;
}


// Cursor
// ------

cwListElem * cwGrid::onGetCursoredElem() const
{
   #if defined __ECL_W32__
      int row_count = getRowCount();
      if ( row_count > 0 ) {
         int idx = ((WCGridCtrl*)_wnd)->GetCurrentRow() / row_count;
         return getElemWithIndex(idx);
      }
   #else
   #endif

   return 0;
}

bool cwGrid::onSetCursoredElem(cwListElem *elem)
{
   if ( !elem )
      return false;

   #if defined __ECL_W32__
      int row = getElemCountFromBegin(elem) * getRowCount();
      return ((WCGridCtrl*)_wnd)->GotoRow(row) == 0;
   #else
      return true;
   #endif
}


// Einfuegen/Loeschen
// ------------------

bool cwGrid::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem * /*parent*/, bool /*invd*/)
{
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      int idx, row_count = getRowCount();

      if ( ref_elem == 0 && pos < 0 ) {
         if ( appendRows(row_count) ) {
            ((WCGridCtrl*)_wnd)->elems.add(new_elem);
            setupJoins(((WCGridCtrl*)_wnd)->elems.getSize() - 1);
            return true;
         } else {
            return false;
         }
      } else if ( ref_elem == 0 && pos > 0 ) {
         idx = 0;
         if ( !insertRows(row_count, idx*row_count) ) idx = -1;
      } else if ( pos < 0 ) {
         idx = getElemCountFromBegin(ref_elem);
         if ( !insertRows(row_count, idx*row_count) ) idx = -1;
      } else {
         idx = getElemCountFromBegin(ref_elem) + 1;
         if ( !insertRows(row_count, idx*row_count) ) idx = -1;
      }

      if ( __ECL_ASSERT1__(idx >= 0) ) {
         ((WCGridCtrl*)_wnd)->elems.insertAt(idx, new_elem);
         setupJoins(idx);
         return true;
      } else {
         return false;
      }

   #else if defined __ECL_OS2__
      // ???
   #endif

   return true;
}

bool cwGrid::onRemoveElem(cwListElem *elem, bool /*invd*/)
{
   int idx = getElemCountFromBegin(elem);
   int row_count = getRowCount();
   bool rc = false;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCGridCtrl *ug = (WCGridCtrl*)_wnd;
         if ( ug->m_hWnd != 0 ) {
            ug->EnableUpdate(FALSE);
            ug->elems.removeAt(idx);
            rc = removeRows(row_count, idx*row_count);
            ug->EnableUpdate(TRUE);
         }
      #else if defined __ECL_OS2__
         // ???
      #endif
   }

   return rc;
}

bool cwGrid::onRemoveAllElems(cwListElem * /*parent*/, bool /*invd*/)
{
   bool rc = false;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCGridCtrl *ug = (WCGridCtrl*)_wnd;
         if ( ug->m_hWnd != 0 ) {
            ug->EnableUpdate(FALSE);
            ug->elems.removeAll();
            ug->ClearSelections();
            rc = removeRows(ug->GetNumberRows(), 0);
            ug->EnableUpdate(TRUE);
         }
      #else if defined __ECL_OS2__
         // ???
      #endif
   }

   return rc;
}


// Elementverwaltung
// -----------------

cwListElem * cwGrid::onGetElemWithIndex(int idx) const
{
   return _wnd != 0 && idx >= 0 && idx < ((WCGridCtrl*)_wnd)->elems.getSize() ?
      ((WCGridCtrl*)_wnd)->elems[idx]
    : 0;
}


// Abfrage
// -------

bool cwGrid::onQueryStarted(csQuery *query)
{
   if ( query != 0 ) {
      #if defined __ECL_W32__
         ((WCGridCtrl*)_wnd)->SetPaintMode(FALSE);
      #endif
   }

   return cwListCtl::onQueryStarted(query);
}

bool cwGrid::onQueryEnded(csQuery *query)
{
   bool ok = cwListCtl::onQueryEnded(query);

   if ( query != 0 && !query->getFlags(csQuery::fStopReq) ) {
      #if defined __ECL_W32__
         ((WCGridCtrl*)_wnd)->SetPaintMode(TRUE);
      #endif
   }

   return ok;
}

bool cwGrid::onAllowsMultipleRows() const
{
   return true;
}

void cwGrid::onSetupRowCol(const SETUP_ROWCOL_INFO& info)
{
   #if defined __ECL_W32__
      ((WCGridCtrl*)_wnd)->SetNumberCols(info.new_column_count);
   #else if defined __ECL_OS2__
      // ???
   #endif
}

void cwGrid::onSetupField(int fld, const SETUP_FIELD_INFO& info)
{
   #if defined __ECL_W32__

      WCGridCtrl *ug = (WCGridCtrl*)_wnd;

      char title[128];
      strxcpy(title, info.query->getTitleText(fld), sizeof title);

      if ( info.disp_row == 0 ) {

         CUGCell cell;
         ug->GetColDefault(info.disp_col, &cell);
         cell.SetDataType(UGCELLDATA_STRING);

         switch ( info.query->getFieldHAlign(fld) ) {
         case csQuery::haLeft:   cell.SetAlignment(UG_ALIGNLEFT); break;
         case csQuery::haCenter: cell.SetAlignment(UG_ALIGNCENTER); break;
         case csQuery::haRight:  cell.SetAlignment(UG_ALIGNRIGHT); break;
         }

         switch ( info.query->getFieldVAlign(fld) ) {
         case csQuery::vaTop:    cell.SetAlignment(UG_ALIGNTOP); break;
         case csQuery::vaCenter: cell.SetAlignment(UG_ALIGNVCENTER); break;
         case csQuery::vaBottom: cell.SetAlignment(UG_ALIGNBOTTOM); break;
         }

         ug->SetColDefault(info.disp_col, &cell);

         int pix_width = 75;
         TEXTMETRIC tm;
         CClientDC cdc(ug);
         if ( cdc.GetOutputTextMetrics(&tm) )
            pix_width = info.query->getFieldWidth(fld) * tm.tmAveCharWidth;

         #define __Add_Pix_Border__
         #ifdef __Add_Pix_Border__
            pix_width += 10;
         #endif

         csFilter *flt = info.query->getFilter(fld);
         if ( flt != 0 && flt->getValueCount() > 0 )
            pix_width += GetSystemMetrics(SM_CXVSCROLL);

         ug->QuickSetText(info.disp_col, -1, title);
         ug->SetColWidth(info.disp_col, min_max(pix_width, 35, 375));

      }

   #else if defined __ECL_OS2__
      // ???
   #endif
}

int cwGrid::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      //DWORD style = ((WCWnd*)_wnd)->GetStyle();
      //
      //if ( (mask & wsCnrSingleSel) && (style & LVS_SINGLESEL) )
      //   rc |= wsCnrSingleSel;
      //if ( (mask & wsCnrMultipleSel) && (style & LVS_SINGLESEL) == 0 )
      //   rc |= wsCnrMultipleSel;
      //if ( (mask & wsCnrExtendedSel) && (style & LVS_SINGLESEL) == 0 )
      //   rc |= wsCnrExtendedSel;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwListCtl::onGetStyles(mask) | own_style;
}

void cwGrid::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   if ( add & WS_OWN_MASK )
      own_style |= (add & WS_OWN_MASK);
   if ( remove & WS_OWN_MASK )
      own_style &= ~(add & WS_OWN_MASK);

   #if defined __ECL_W32__

      //if ( add & wsCnrSingleSel ) {
      //   os_add[0] |= LVS_SINGLESEL;
      //} else if ( add & wsCnrMultipleSel ) {
      //   os_remove[0] |= LVS_SINGLESEL;
      //} else if ( add & wsCnrExtendedSel ) {
      //   os_remove[0] |= LVS_SINGLESEL;
      //}

      cwListCtl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwGrid::onAttach(int id, void *wnd)
{
   #if defined __ECL_W32__
      BOOL success = ((WCGridCtrl*)_wnd)->AttachGrid((WCWnd*)wnd, id);
      __ECL_ASSERT2__(!success, ("Could not attach grid %d", id));
   #endif
}

