// ===========================================================================
// db_explorer.cpp                               ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Datenbank-Explorer
//
// ===========================================================================

#include "store/es_query.hpp"
#include "dbi/edb_dictionary.hpp"
#include "dbi/edb_transaction.hpp"
#include "dbi/edb_query.hpp"

#include "resource.h"
#include "win/ew_application.hpp"
#include "win/ew_frames.hpp"
#include "win/ew_views.hpp"
#include "win/ew_treectls.hpp"
#include "win/ew_cnrctls.hpp"




// ===========================================================================
// TREE_ELEM_DATA
// ---------------------------------------------------------------------------
//
// ===========================================================================

enum TREE_ELEM_TYPE {
   etOther,
   etCatTables,
   etCatViews,
   etTableView
};

struct TREE_ELEM_DATA {
   TREE_ELEM_TYPE type;
   cdbDictTable dict_table;
};




// ===========================================================================
// cFieldQuery
// ---------------------------------------------------------------------------
//
// cBase
//  +-csBaseStorage
//     +-csQuery
//        +-cFieldQuery
//
// ===========================================================================

class cFieldQuery : public csQuery {

   cdbDictTable dict_table;
   cdbDictField dict_field;
   int idx;

public:

   cFieldQuery(cdbDictTable& tab) :
      dict_table(tab)
   {
      idx = -1;
   }

protected:

   bool onRewind()
   {
      idx = -1;
      return true;
   }

   bool onFetch()
   {
      if ( ++idx < dict_table.getFieldCount() ) {
         dict_field = dict_table.getField(idx);
         return true;
      } else {
         return false;
      }
   }

   int onGetQueryFieldCount() const
   {
      return 6;
   }

   TYPE onGetFieldType(int fld) const
   {
      switch ( fld ) {
      case 0:        return tString;
      case 1:        return tString;
      case 2:        return tString;
      case 3:        return tString;
      case 4:        return tString;
      case 5:        return tInt;
      }
      return csQuery::onGetFieldType(fld);
   }

   cString onGetTitleText(int fld) const
   {
      switch ( fld ) {
      case 0:        return "Name";
      case 1:        return "PK?";
      case 2:        return "Null?";
      case 3:        return "Type";
      case 4:        return "Width";
      case 5:        return "Size";
      }

      return csQuery::onGetTitleText(fld);
   }

   int onGetFieldBufferSize(int fld) const
   {
      switch ( fld ) {
      case fldDescr: return 32;
      case fldName:  return 32;
      case 0:        return 32;
      case 1:        return 5;
      case 2:        return 16;
      case 3:        return 16;
      case 4:        return 8;
      }

      return csQuery::onGetFieldBufferSize(fld);
   }

   bool onGetInt(int fld, int& buf) const
   {
      if ( fld == 5 )
         buf = dict_field.getBufferSize();
      return true;
   }

   csQuery::HALIGN onGetFieldHAlign(int fld) const
   {
      return fld == 4 ? haRight : csQuery::onGetFieldHAlign(fld);
   }

   int onGetFieldPrec(int fld) const
   {
      return fld == 4 ? 1 : csQuery::onGetFieldPrec(fld);
   }

   bool onGetString(int fld, cString& buf) const
   {
      const char *data_types[] = {
         "Short",
         "Long",
         "Float",
         "Double",
         "Char",
         "String",
         "Rowid",
         "Date",
         "Time",
         "TimeStamp"
      };

      switch ( fld ) {
      case fldKey:      buf = Str(idx); break;
      case fldDescr:
      case fldName:
      case 0:           buf = dict_field.getFieldName(); break;
      case 1:           buf = dict_field.isPrimaryKey() ? "PK" : ""; break;
      case 2:           buf = dict_field.isNullable() ? "Null" : "Not Null"; break;
      case 3:           buf = data_types[dict_field.getDataType()]; break;
      case 4:           buf = Str(dict_field.getFieldSize());
                        if ( dict_field.getDigits() > 0 ) buf += "," + Str(dict_field.getDigits());
                        break;

      }

      return true;
   }

};




// ===========================================================================
// cTreeQuery
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Queries, die zum Befuellen des Tree-Views verwendet werden.
//
// cBase
//  +-csBaseStorage
//     +-csQuery
//        +-cTreeQuery
//
// ===========================================================================

class cTreeQuery : public csQuery {

protected:

   int onGetUserDataLen() const
   {
      return sizeof(TREE_ELEM_DATA);
   }

};




// ===========================================================================
// cTableQuery
// ---------------------------------------------------------------------------
//
// cBase
//  +-csBaseStorage
//     +-csQuery
//        +-cTreeQuery
//           +-cTableQuery
//
// ===========================================================================

class cTableQuery : public cTreeQuery {

   cdbDictionary dict;
   cdbDictTable dict_table;
   bool views;
   int idx;

public:

   cTableQuery(cdbDatabase& db, bool views) :
      dict(db)
   {
      cTableQuery::views = views;
      cTableQuery::idx = -1;
   }

   ~cTableQuery()
   {
   }

   cdbDictTable getDictTable()
   {
      return dict_table;
   }

protected:

   bool onRewind()
   {
      idx = -1;
      return true;
   }

   bool onFetch()
   {
      while ( ++idx < dict.getTableCount() ) {
         dict_table = dict.getTable(idx);
         if ( views && dict_table.getType() == cdbDictTable::ttView )
            return true;
         if ( !views && dict_table.getType() == cdbDictTable::ttTable )
            return true;
      }

      return false;
   }

   int onGetFieldBufferSize(int fld) const
   {
      return fld == fldKey ? csQuery::onGetFieldBufferSize(fld) : 64;
   }

   bool onGetString(int fld, cString& buf) const
   {
      buf = fld == fldKey ? Str(idx) : dict_table.getTableName();
      return true;
   }

   void *onGetUserData(void *buf, int buf_size) const
   {
      memset(buf, 0, buf_size);
      TREE_ELEM_DATA *ted = (TREE_ELEM_DATA*)buf;
      ted->dict_table = dict_table;
      ted->type = etTableView;
      return buf;
   }

};




// ===========================================================================
// cCategoryQuery
// ---------------------------------------------------------------------------
//
// cBase
//  +-csBaseStorage
//     +-csQuery
//        +-cTreeQuery
//           +-cCategoryQuery
//
// ===========================================================================

class cCategoryQuery : public cTreeQuery {

   cdbDatabase *db;
   int idx;

public:

   cCategoryQuery(cdbDatabase *db)
   {
      cCategoryQuery::db = db;
      cCategoryQuery::idx = -1;
   }

protected:

   bool onRewind()
   {
      idx = -1;
      return true;
   }

   bool onFetch()
   {
      if ( ++idx < 2 ) {
         return true;
      } else {
         return false;
      }
   }

   int onGetFieldBufferSize(int fld) const
   {
      return fld == fldKey ? csQuery::onGetFieldBufferSize(fld) : 64;
   }

   bool onGetString(int fld, cString& buf) const
   {
      if ( fld == fldKey ) {
         buf = Str(idx);
      } else {
         switch ( idx ) {
         case 0: buf = "Tabellen"; break;
         case 1: buf = "Views"; break;
         }
      }
      return true;
   }

   int onGetRecordStyle() const
   {
      return csQuery::onGetRecordStyle() | rstHasSubquery;
   }

   csQuery * onNewRecordSubquery() const
   {
      return new cTableQuery(*db, idx == 1);
   }

   void *onGetUserData(void *buf, int) const
   {
      TREE_ELEM_DATA *ted = (TREE_ELEM_DATA*)buf;
      ted->type = idx == 0 ? etCatTables : etCatViews;
      return buf;
   }

};




// ===========================================================================
// cFloater
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwDockable
//          +--cwMiniFrame
//              +--cFloater
//
// ===========================================================================

class cFloater : public cwMiniFrame {

   cwContainer cnr;

public:

   void setQuery(csQuery *query)
   {
      cnr.setQuery(query);
      //cnr.refresh();
   }

protected:

   bool onCreate()
   {
      cnr.create(this, 1, 0, 0);
      setClient(&cnr);
      return cwMiniFrame::onCreate();
   }

};




// ===========================================================================
// cListView
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwView
//          +--cListView
//
// ===========================================================================

class cListView : public cwView {

   cwContainer cnr;

public:

   void setQuery(csQuery *query)
   {
      cnr.setFlags(cwContainer::wflColumnsInit, 0);
      cnr.setQuery(query);
      //cnr.refresh();
   }

protected:

   bool onCreate()
   {
      cnr.create(this, 1, 0, 0);
      setClient(&cnr);
      return cwView::onCreate();
   }

};




// ===========================================================================
// cTreeView
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwView
//          +--cTreeView
//
// ===========================================================================

class cTreeView : public cwView {

   cwTree tree;
   cListView *list_view;
   cFloater *fields;
   cdbTransaction *ta;

public:

   cTreeView(cdbTransaction *ta, cListView& list_view, cFloater& fields)
   {
      cTreeView::ta = ta;
      cTreeView::list_view = &list_view;
      cTreeView::fields = &fields;
   }

protected:

   bool onCreate()
   {
      cCategoryQuery *query = new cCategoryQuery(ta->getDB());
      tree.create(this, 1, 0, query, cwTree::wsRootLines);

      tree.addEvent(cwTree::evtSelectionChanged, this, (EVFUNC_P)onEvtSelChanged);

      setClient(&tree);
      return cwView::onCreate();
   }

   void onEvtSelChanged(void *p1)
   {
      cwListElem *elem = (cwListElem*)p1;

      if ( elem == 0 ) {
         list_view->setQuery(0);
      } else {
         TREE_ELEM_DATA *ted = (TREE_ELEM_DATA*)elem->getUserDataBuf();

         if ( ted->type == etTableView ) {
            cString select = "SELECT {PK=0,NAME=0,DESCR=0} * FROM " + elem->getName();
            list_view->setQuery(new cdbQuery(ta, 0, select));
            fields->setQuery(new cFieldQuery(ted->dict_table));
         }
      }
   }

};




// ===========================================================================
// cwApplication
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwApplication
//      +--cDbExplorerApp
//
// ===========================================================================

class cDbExplorerApp : public cwApplication {

   cwFrame frame;
   cTreeView *tree_view;
   cListView list_view;
   cFloater fields;
   cdbTransaction *ta;

public:

   cDbExplorerApp() : cwApplication("MY_APP")
   {
   }

   bool onInit()
   {
      cBase::setDebugMask("ERROR ASSERT");

      ta = new cdbTransaction(cdbDatabase::ODBC, "FBS", "fbs", "fortea2");
      //ta = new cdbTransaction(cdbDatabase::ODBC, "NWIND", "admin", "");

      tree_view = new cTreeView(ta, list_view, fields);

      frame.setView(&list_view);
      frame.addView(tree_view, cwFrame::vpLeft, 256);

      frame.create(cResource(IDR_MAINFRAME), cwFrame::fsDockAny);

      fields.create(&frame, cwMiniFrame::dksAlignBottom, "Felder");
      fields.dockWindow(cwMiniFrame::dpBottom);

      tree_view->refresh();

      frame.show();
      frame.forceUpdate();

      setMainWindow(&frame);

      return true;
   }

   int onExit()
   {
      delete tree_view;
      delete ta;
      return 0;
   }

   void onFileNew()
   {
   }

   void onFileOpen()
   {
   }

};




// ===========================================================================
// theApp
// ---------------------------------------------------------------------------
//
// ===========================================================================

cDbExplorerApp theApp;

