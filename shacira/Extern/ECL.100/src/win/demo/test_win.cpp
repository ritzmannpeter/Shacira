// ===========================================================================
// test_win.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
// ===========================================================================

#include "win/demo/tw_direct_view.hpp"

#include "win/ew_application.hpp"
#include "win/ew_menus.hpp"
#include "win/ew_frames.hpp"
#include "win/ew_views.hpp"
#include "win/ew_draw.hpp"
#include "win/ew_dialogs.hpp"
#include "win/ew_statctls.hpp"
#include "win/ew_buttonctls.hpp"
#include "win/ew_editctls.hpp"
#include "win/ew_lboxctls.hpp"
#include "win/ew_cnrctls.hpp"
#include "win/ew_treectls.hpp"
#include "dbi/edb_query.hpp"
#include "dbi/edb_dictionary.hpp"
#include "resource.h"

cdbTransaction ecl_ta(cdbDatabase::ODBC, "NWIND", "admin", "");
cwIconList ecl_icons;




// ===========================================================================
// cPageEntry
// ---------------------------------------------------------------------------
//
// cBase
//  +-cwWindow
//     +-cwDialog
//        +-cwNotebookPage
//           +-cPageEntry
//
// ===========================================================================

class cPageEntry : public cwNotebookPage {
   cwEditField ef1, ef2, ef3, ef4, ef5, ef6;
   cwEditField ef1m1, ef1m2, ef4m1, ef4m2;
   cwEditBox eb1, eb2;
   cwButtonCtl pbSwap;

public:
   cPageEntry() : cwNotebookPage()
   {
      create(cResource(IDD_DLG_ENTRY));

      ef1.attach(this, IDC_EF_INT,     0);
      ef2.attach(this, IDC_EF_DOUBLE,  0);
      ef3.attach(this, IDC_EF_STRING,  0);
      ef4.attach(this, IDC_EF_STRING2, 0);
      ef5.attach(this, IDC_EF_DATE,    0);
      ef6.attach(this, IDC_EF_TIME,    0);

      eb1.attach(this, IDC_EB_ML1,    0);
      eb2.attach(this, IDC_EB_ML2,    0);

      ef1m1.attach(this, IDC_EF_INT_MIRR1,  0);
      ef1m2.attach(this, IDC_EF_INT_MIRR2,  0);

      ef4m1.attach(this, IDC_EF_DATE_MIRR1, 0);
      ef4m2.attach(this, IDC_EF_DATE_MIRR2, 0);

      pbSwap.attach(this, IDC_PB_SWAP);
   }

   bool onSetConstraint()
   {
      tieChild(1, sLeft, tOpposite);
      tieChild(2, sLeft, tOpposite);
      tieChild(IDC_INTERPRET, sLeft, tOpposite);

      setConstraint(&ef1, sRight, tPosition, 40);
      setConstraint(&ef1m1, sLeft, tOpposite, 30, &ef1);
      tieChild(&ef1m1, sRight, tSame);

      setConstraint(&ef2, sRight, tPosition, 40);
      setConstraint(&ef1m2, sLeft, tOpposite, 30, &ef2);
      tieChild(&ef1m2, sRight, tSame);

      setConstraint(&ef3, sRight, tPosition, 40);
      setConstraint(&ef4, sLeft, tOpposite, 30, &ef3);
      tieChild(&ef4, sRight, tSame);

      setConstraint(&ef5, sRight, tPosition, 40);
      setConstraint(&ef4m1, sLeft, tOpposite, 30, &ef5);
      tieChild(&ef4, sRight, tSame);

      // Sorgt dafuer, dass die rechte EditBox rechts wandern kann
      tieChild(&eb2, sRight, tSame);

      // Sorgt dafuer, dass der ganze Knopf wandern kann
      tieChild(&pbSwap, sRight, tSame);
      tieChild(&pbSwap, sLeft, tOpposite);

      setConstraint(&ef5, sRight, tPosition, 50);
      setConstraint(&ef4m1, sLeft, tOpposite, 30, &ef5);

      //setConstraint(&ef1, sRight, tOpposite, -20, &ef1m1);
      //tieChild(&ef1m1, sRight, tSame);
      /*
      setConstraint(&ef1m1, sLeft, tOpposite, -20, &ef1);
      tieChild(&ef2, sRight, tOpposite, &ef1m2);
      setConstraint(&ef4, sLeft, tOpposite, 0, &ef3);
      tieChild(&ef3, sHoriz, tSame);
      */
      //tieChild(&ef5, sHoriz, tSame);
      //tieChild(&ef6, sHoriz, tSame);
      //tieChild(&ef1m1, sHoriz, tSame);
      //tieChild(&ef1m2, sHoriz, tSame);
      //tieChild(&ef4m1, sHoriz, tSame);
      //tieChild(&ef4m2, sHoriz, tSame);

      return true;
   }
};




// ===========================================================================
// cDlgEntry
// ---------------------------------------------------------------------------
//
// cBase
//  +-cwWindow
//     +-cwDialog
//        +-cDlgEntry
//
// ===========================================================================

class cDlgEntry : public cwDialog {
   cwEditField ef1, ef2, ef3, ef4, ef5, ef6;
   cwEditField ef1m1, ef1m2, ef4m1, ef4m2;
   cwEditBox eb1, eb2;
   cwButtonCtl pbSwap;
   csVarInt vint;
   csVarDouble vdbl;
   csVarString vstr10, vstr50, vstr100, vstr200;
   csVarTime vtim;
   csVarDate vdat;

public:
   cDlgEntry(cwWindow *parent) :
      vstr10(10), vstr50(50), vstr100(100), vstr200(200)
   {
      create(cResource(IDD_DLG_ENTRY), parent);

      vint = 42;
      vdbl = 3.1415;
      vdat = cDate(); //vdat.setFlags(csVarDate::fIsWeek);
      vtim = cTime();

      vstr10  = "AHA"; vstr10.setFlags(csVarString::fUpcaseOnly | csVarString::fNotNull);
      vstr50  = "Das ist das Haus vom Nikolaus";
      vstr100 = "Das ist das Haus vom Nikolaus";
      vstr200 = "Das ist das Haus vom Nikolaus "
                "und auch das Haus vom Weihnachtsmann "
                "sowie das Haus vom Osterhasen "
                "(das muss man dem Haus schon lassen - "
                "es wohnen viele Leute drin!)";

      ef1.attach(this, IDC_EF_INT,     &vint);
      ef2.attach(this, IDC_EF_DOUBLE,  &vdbl);
      ef3.attach(this, IDC_EF_STRING,  &vstr10);
      ef4.attach(this, IDC_EF_STRING2, &vstr50);
      ef5.attach(this, IDC_EF_DATE,    &vdat);
      ef6.attach(this, IDC_EF_TIME,    &vtim);

      eb1.attach(this, IDC_EB_ML1,    &vstr100);
      eb2.attach(this, IDC_EB_ML2,    &vstr200);

      ef1m1.attach(this, IDC_EF_INT_MIRR1,  &vint);
      ef1m2.attach(this, IDC_EF_INT_MIRR2,  &vint);
      ef1m2.setInheritedValue("888888");

      ef4m1.attach(this, IDC_EF_DATE_MIRR1, &vdat);
      ef4m2.attach(this, IDC_EF_DATE_MIRR2, &vdat);

      pbSwap.attach(this, IDC_PB_SWAP);
      pbSwap.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)onEvtSwap);
   }

   void onEvtSwap()
   {
      csStorage *temp = ef4m1.getStorage();
      ef4m1.setStorage(ef4.getStorage());
      ef4.setStorage(temp);
   }
};




// ===========================================================================
// cDlgButton
// ---------------------------------------------------------------------------
//
// cBase
//  +-cwWindow
//     +-cwDialog
//        +-cDlgButton
//
// ===========================================================================

class cDlgButton : public cwDialog {

public:
   cDlgButton(cwWindow *parent)
   {
      create(cResource(IDD_DLG_BUTTON), parent);
   }
};




// ===========================================================================
// cDlgListCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +-cwWindow
//     +-cwDialog
//        +-cDlgListCtl
//
// ===========================================================================

class cDlgListCtl : public cwDialog {
   cwListBox ecl_listbox;
   cwSetBox setbox1, setbox2, setbox1m, setbox2m;
   cwComboBox cbx1, cbx1m;
   cwMultiComboBox cbx2, cbx3;
   cwContainer cnr;
   cwTree tree;
   cwButtonCtl pbRefresh;
   csVarString vset1, vset2;
   csVarInt vint;
   cwText txtSticky;

public:
   cDlgListCtl(cwWindow *parent) :
      vset1(10), vset2(10)
   {
      create(cResource(IDD_DLG_LISTCTL), parent);

      csEnumQuery *query1 = new csEnumQuery(
         "MON$Montag", "TUE$Dienstag", "WED$Mittwoch", "THU$Donnerstag",
         "FRI$Freitag", "SAT$Samstag", "SUN$Sonntag", NULL);

      ecl_listbox.attach(this, IDC_LIST1, 0, query1);

      vint = 1; // Preselection: "Katze"

      cbx1.attach(this, IDC_CBX1, &vint, new csEnumQuery("0$Hund", "1$Katze", "2$Maus", 0));
      cbx1m.attach(this, IDC_CBX1_MIRR, &vint, new csEnumQuery("0$Hund", "1$Katze", "2$Maus", 0));

      cbx2.attach(this, IDC_CBX2, 0, new cdbQuery(&ecl_ta, 0,
         SQL::SELECT("SELECT `KundenCode`,`Firma`,`PLZ`,`Ort`,`Strasse`,`Land` FROM Kunden")));
      cbx3.attach(this, IDC_CBX3, 0, new cdbQuery(&ecl_ta, 0,
         SQL::SELECT("SELECT LieferantenNr,Firma,PLZ,Ort,Land FROM Lieferanten")));

      setbox1.attach(this, IDC_SET1, &vset1, new csEnumQuery("H$Hund", "K$Katze", "M$Maus", 0));
      setbox2.attach(this, IDC_SET2, &vset2, new csEnumQuery("K$Kaffee", "B$Bier", "W$Wein", 0));
      setbox1m.attach(this, IDC_SET1_MIRR, &vset1, new csEnumQuery("H$Hund", "K$Katze", "M$Maus", 0));
      setbox2m.attach(this, IDC_SET2_MIRR, &vset2, new csEnumQuery("K$Kaffee", "B$Bier", "W$Wein", 0));

      cnr.attach(this, IDC_CNR, 0, new cdbQuery(&ecl_ta, 0, SQL::SELECT("SELECT * FROM Artikel")));
      pbRefresh.attach(this, IDC_CNR_REFRESH);
      pbRefresh.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)evtRefreshCnr);

      cdRect ss(0, 5, 1, 0);
      txtSticky.create(this, 12345, "BLABLA", wsChild|wsVisible|wsBorder, ss);
      txtSticky.setPresParam(ppFgndColor, cdColor(cdColor::Gray));
      pbRefresh.setSticky(&txtSticky);

      tree.attach(this, IDC_TREE, 0, new cdbQuery(&ecl_ta, 0,
         SQL::SELECT("SELECT PersonalNr,Nachname,Position FROM Personal"),
         SQL::WHERE("Vorgesetzter=?"), SQL::WHERE("Vorgesetzter IS NULL")));
   }

   void evtRefreshCnr()
      { cnr.refresh(); }

};





class cMyDialog : public cwDialog {
   cwListBox ecl_listbox;
   cwSetBox setbox1, setbox2;
   cwComboBox cbx;
   csVarString vset1, vset2;

public:
   cMyDialog(csQuery *query) :
      vset1(10), vset2(10)
   {
      ecl_listbox.attach(this, IDC_LIST1, 0, query);
      cbx.attach(this, IDC_CBX1, 0, new csEnumQuery("H$Hund", "K$Katze", "M$Maus", 0));
      setbox1.attach(this, IDC_SET1, &vset1, new csEnumQuery("H$Hund", "K$Katze", "M$Maus", 0));
      setbox2.attach(this, IDC_SET2, &vset2, new csEnumQuery("K$Kaffee", "B$Bier", "W$Wein", 0));
   }

   void evtButtonClick()
   {
      setbox1.setQuery(new csEnumQuery("H$Hund", "K$Katze", "M$Maus", 0));
   }
};

class cDlgMenu : public cwDialog {
   cwButtonCtl mnu1, mnu2, mnu3, mnu4;

public:
   cDlgMenu()
   {
      mnu1.attach(this, IDC_PB_ENTRY);
      mnu2.attach(this, IDC_PB_LIST);
      mnu3.attach(this, IDC_PB_NB_MODAL);
      mnu4.attach(this, IDC_PB_NB_MODELESS);

      mnu1.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)evtShowEntry);
      mnu2.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)evtShowListCtl);
      mnu3.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)evtShowNbModal);
      mnu4.addEvent(cwButtonCtl::evtButtonClicked, this, (EVFUNC)evtShowNbModeless);
   }

   void evtShowEntry()
      { cDlgEntry dlg(this); dlg.process(true); }
   void evtShowListCtl()
      { cDlgListCtl dlg(this); dlg.process(true); }
   void evtShowNbModal()
      { cwNotebookDlg dlg;
        cPageEntry page1;
        cwNotebookPage page2; page2.create(IDD_DLG_BUTTON);
        dlg.create(getParent(), "Test-Einstellnotizbuch", 0);
        dlg.addPage(&page1);
        dlg.addPage(&page2);
        dlg.process(); }
   void evtShowNbModeless()
      { cwNotebookDlg *dlg = new cwNotebookDlg;
        cwNotebookPage *page1 = new cPageEntry();
        cwNotebookPage *page2 = new cwNotebookPage(); page2->create(IDD_DLG_BUTTON);
        dlg->create(getParent(), "Test-Einstellnotizbuch", 0);
        dlg->addPage(page1);
        dlg->addPage(page2);
        dlg->show(); }
};


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
   int onGetFieldBufferSize(int fld) const
   {
      return fld == fldKey ? csQuery::onGetFieldBufferSize(fld) : 64;
   }
   bool onGetString(int fld, cString& buf) const
   {
      if ( fld == fldKey ) {
         buf = Str(idx);
      } else {
         buf = dict_field.getFieldName();
         if ( dict_field.isPrimaryKey() )
            buf = "*" + buf;
         if ( !dict_field.isNullable() )
            buf += " NOT NULL";
      }
      return true;
   }
};

class cTableQuery : public csQuery {
   cdbDictionary dict;
   cdbDictTable dict_table;
   int idx;
public:
   cTableQuery(cdbDatabase& db) :
      dict(db)
   {
      idx = -1;
   }
   bool onRewind()
   {
      idx = -1;
      return true;
   }
   bool onFetch()
   {
      if ( ++idx < dict.getTableCount() ) {
         dict_table = dict.getTable(idx);
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
      buf = fld == fldKey ? Str(idx) : dict_table.getTableName();
      return true;
   }
   int onGetRecordStyle() const
   {
      return csQuery::onGetRecordStyle() | rstHasSubquery;
   }
   csQuery * onNewRecordSubquery() const
   {
      return new cFieldQuery(*(cdbDictTable*)(void*)&dict_table);
   }
};

class cMyObj : public cdObject {

   class cdRoundRect : public cdObject {
   protected:
      void onDraw(cdSpace *space) const
      {

/*
         space->draw(c2dLineSeg(c2dPoint(-25,5), c2dPoint(-5,25)));
         space->draw(c2dLineSeg(c2dPoint(-5,25), c2dPoint(5,25)));
         space->draw(c2dLineSeg(c2dPoint(5,25), c2dPoint(25,5)));
         space->draw(c2dLineSeg(c2dPoint(25,5), c2dPoint(25,-5)));
         space->draw(c2dLineSeg(c2dPoint(25,-5), c2dPoint(5,-25)));
         space->draw(c2dLineSeg(c2dPoint(5,-25), c2dPoint(-5,-25)));
         space->draw(c2dLineSeg(c2dPoint(-5,-25), c2dPoint(-25,-5)));
         space->draw(c2dLineSeg(c2dPoint(-25,-5), c2dPoint(-25,5)));
*/
         space->draw(c2dArc(c2dPoint(-25,5), c2dPoint(-5,25), c2dPoint(-5,5)));
         space->draw(c2dLineSeg(c2dPoint(-5,25), c2dPoint(5,25)));
         space->draw(c2dArc(c2dPoint(5,25), c2dPoint(25,5), c2dPoint(5,5)));
         space->draw(c2dLineSeg(c2dPoint(25,5), c2dPoint(25,-5)));
         space->draw(c2dArc(c2dPoint(25,-5), c2dPoint(5,-25), c2dPoint(5,-5)));
         space->draw(c2dLineSeg(c2dPoint(5,-25), c2dPoint(-5,-25)));
         space->draw(c2dArc(c2dPoint(-5,-25), c2dPoint(-25,-5), c2dPoint(-5,-5)));
         space->draw(c2dLineSeg(c2dPoint(-25,-5), c2dPoint(-25,5)));
      }
   };

public:
   cMyObj(cdColor _color) : cdObject(_color)
   {
   }
protected:
   void onDraw(cdSpace *space) const
   {
      space->setPattern(cdPattern::Null);

      // Diagonale Linien durch Koordinatenursprung
      space->draw(c2dLine(c2dPoint(0,0), c2dPoint(1,1)));
      space->draw(c2dLine(c2dPoint(0,0), c2dPoint(-1,1)));

      space->draw(c2dBox(c2dPoint(-150,-150), c2dSize(300,300)));
      space->draw(c2dCircle(c2dPoint(0,0), 150));
      space->draw(c2dBox(c2dPoint(-100,-100), c2dSize(200,200)));
      space->draw(c2dCircle(c2dPoint(0,0), 100));
      space->draw(c2dCircle(c2dPoint(0,0), 50));
      //space.draw(c2dLineSeg(c2dPoint(-150,-150),c2dPoint(-100,-100)));
      //space.draw(c2dLineSeg(c2dPoint(100,-100),c2dPoint(150,-150)));
      //space.draw(c2dLineSeg(c2dPoint(100,100),c2dPoint(150,150)));
      //space.draw(c2dLineSeg(c2dPoint(-100,100),c2dPoint(-150,150)));

      space->setPattern(cdPattern::Diag1);
      space->draw(c2dBox(c2dPoint(-15,-125), c2dPoint(15,-75)));

      space->setFillColor(color);
      space->setPattern(cdPattern::Blank); space->draw(c2dCircle(c2dPoint(-200,200), 25));
      space->setPattern(cdPattern::Solid); space->draw(c2dCircle(c2dPoint(-150,200), 25));
      space->setPattern(cdPattern::Diag1); space->draw(c2dCircle(c2dPoint(-100,200), 25));
      space->setPattern(cdPattern::Diag2); space->draw(c2dCircle(c2dPoint( -50,200), 25));
      space->setPattern(cdPattern::Vert);  space->draw(c2dCircle(c2dPoint(   0,200), 25));
      space->setPattern(cdPattern::Horiz); space->draw(c2dCircle(c2dPoint(  50,200), 25));
      space->setPattern(cdPattern::Hatch); space->draw(c2dCircle(c2dPoint( 100,200), 25));
      space->setPattern(cdPattern::Cross); space->draw(c2dCircle(c2dPoint( 150,200), 25));
      space->setPattern(cdPattern::Null);  space->draw(c2dCircle(c2dPoint( 200,200), 25));

      cdMatrix old_tmat = space->getTransform();
      space->translate(c2dVector( 0,0));
      space->moveTo(c2dPoint(0,0)); space->draw(cdRoundRect());
      space->translate(c2dVector(50,0));
      space->moveTo(c2dPoint(0,0)); space->draw(cdRoundRect());
      space->setTransform(old_tmat);
      space->setColor(cdColor::Red);
      for ( int i = 0 ; i < 10 ; i++ ) {
         space->rotate(rad(5));
         space->scale(1.1);
         space->moveTo(c2dPoint(0,0)); space->draw(cdRoundRect());
      }
      space->setTransform(old_tmat);
   }
};

class cMyDoc : public cwDrawDocument {
public:
   cString onGetSignature() const { return "cMyDoc"; }
   virtual void drawObject(cdSpace& space) = 0;
};

class cMyDoc1 : public cwDrawDocument {
   cMyObj obj;
public:
   cMyDoc1() : obj(cdColor::Red)
      { addObject(&obj); }
   c2dBox onGetDrawArea() const
      { return c2dBox(c2dPoint(-225,-225), c2dPoint(225,225)); }
protected:
   cString onGetSignature() const
      { return "cMyDoc1"; }
};

class cMyDoc2 : public cwDrawDocument {
   cMyObj obj;
public:
   cMyDoc2() : obj(cdColor::DarkGreen)
      { addObject(&obj); }
   c2dBox onGetDrawArea() const
      { return c2dBox(c2dPoint(-230,-230), c2dPoint(230,230)); }
protected:
   cString onGetSignature() const
      { return "cMyDoc2"; }
};

cMyDoc1 MyDoc1;
cMyDoc2 MyDoc2;

class cMyView : public cwDrawView {
public:
   void onInit()
   {
      cwDrawView::onInit();
      setPresParam(ppBkgndColor, cdColor(204,217,227));
      MyDoc1.addView(this);
   }

   void toggleDoc()
   {
      if ( getDocument() == &MyDoc1 ) {
         MyDoc1.removeView(this);
         MyDoc2.addView(this);
      } else {
         MyDoc2.removeView(this);
         MyDoc1.addView(this);
      }
   }

   bool onCommand(const cwCmdEvt& cmd)
   {
      switch ( cmd.getId() ) {
      case ID_VIEW_ZOOM10:       zoom(10); return true;
      case ID_VIEW_ZOOM100:      zoom(100); return true;
      case ID_VIEW_ZOOM1000:     zoom(1000); return true;
      case ID_VIEW_ZOOM_WINDOW:  zoom(); return true;
      }
      return cwDrawView::onCommand(cmd);
   }

   void onChar(cwCmdChar& cmd)
   {
      if ( cmd.isChar() ) {
         switch ( cmd.getChar() ) {
         case '0': zoom(); break;
         case '1': zoom(10); break;
         case '2': zoom(100); break;
         case '3': zoom(1000); break;
         }
      }
   }

   cwPopupMenu menu;

   bool onContextMenu(const cwCmdPosition &cmd)
   {
      cwSubMenu sub_menu;
      sub_menu.create();
      sub_menu.addItem("Zoom Fenstergröße", ID_VIEW_ZOOM_WINDOW);
      sub_menu.addItem("Zoom 100%", ID_VIEW_ZOOM100);

      menu.create();
      menu.addItem("Blurb", cwCmdEvt::cmdFileOpen);
      menu.addItem("Slurp", cwCmdEvt::cmdFileNew);
      menu.addSeparator();
      menu.addItem("Zoom", ID_VIEW_ZOOM, &sub_menu);

      /*
      cdPoint pos = cmd.getPos();
      cwPopupMenu::MENU_ALIGN ma = cwPopupMenu::maDefault;
      if ( cmd.fromKeyboard() ) {
         pos = cdPoint(getClientSize() / 2);
         convWin2Screen(pos);
         ma = cwPopupMenu::maCenter;
      } else if ( cmd.isRelativeToWindow() ) {
         convWin2Screen(pos);
      }
      */
      return menu.showMenu(this, cmd);
   }

};

class cMyFloater : public cwMiniFrame {
   cwTree tree;
public:
   bool onCreate()
   {
      cdbQuery *query = new cdbQuery(&ecl_ta, 0,
         SQL::SELECT("SELECT PersonalNr,Nachname,Position FROM Personal"),
         SQL::WHERE("Vorgesetzter=?"), SQL::WHERE("Vorgesetzter IS NULL"));
      tree.create(this, 1, 0, query, cwTree::wsRootLines);
      setClient(&tree);
      return cwMiniFrame::onCreate();
   }
};

class cMyFloater2 : public cwMiniFrame {
   cwTree tree;
public:
   bool onCreate()
   {
      cTableQuery *query = new cTableQuery(*ecl_ta.getDB());
      tree.create(this, 1, 0, query, cwTree::wsRootLines);
      setClient(&tree);
      return cwMiniFrame::onCreate();
   }
};

class cMyFloater3 : public cwMiniFrame {
   cwContainer cnr;
   cwPopupMenu menu;
public:
   bool onCreate()
   {
      struct cMyQuery : public cdbQuery {
         cMyQuery(cdbTransaction *ta) : cdbQuery(ta, 0, "SELECT * FROM Artikel") {}
         bool onGetIconID(int& buf) const { return get(3, buf); }
      };
      cnr.create(this, 1, 0, new cMyQuery(&ecl_ta));
      cnr.setIconList(ecl_icons);
      setClient(&cnr);
      return cwMiniFrame::onCreate();
   }
   bool onCommand(const cwCmdEvt& cmd)
   {
      switch ( cmd.getId() ) {
      case 4242: cnr.refresh(); return true;
      }
      return cwMiniFrame::onCommand(cmd);
   }
   bool onContextMenu(const cwCmdPosition& cmd)
   {
      menu.create();
      menu.addItem("Refresh", 4242);
      return menu.showMenu(this, cmd);
   }
};

//#define __MDI_TEST__
#define __TAB_TEST__

class cMyApplication : public cwApplication {
#ifdef __MDI_TEST__
   cwMultiDocFrame ecl_frame1;
   cwMultiDocChild ecl_child1, ecl_child2, ecl_child3;
   cMyView c1_view1, c2_view1, c3_view1;
   cwView c2_view2;
   cwView c3_view2, c3_view3;
#else
   cwFrame ecl_frame1;
   cMyView ecl_view1;
   cDirectView ecl_view2;
#endif
   cMyFloater ecl_float1;
   cMyFloater2 ecl_float2;
   cMyFloater3 ecl_float3;

public:
   cMyApplication() : cwApplication("MY_APP")
   {
   }

   bool onInit()
   {
      cBase::setDebugMask("ERROR" /*0xffff*/);
      ecl_icons.create(cResource(IDB_BITMAP1), 16, 16, cdColor(255,255,255));
      ecl_icons.addIcons(cBitmap(IDB_BITMAP2), cdColor(255,255,255));
      ecl_icons.addIcons(cBitmap(IDB_BITMAP3), cdColor(255,255,255));

#ifndef __MDI_TEST__
#ifdef __TAB_TEST__
      ecl_frame1.setTabView(&ecl_view1, "Hauptseite");
      ecl_frame1.addTabView(&ecl_view2, "Seite 2");
#else
      ecl_frame1.setView(&ecl_view1);
      ecl_frame1.addView(&ecl_view2, cwFrame::vpLeft, 128);
#endif
#endif

      ecl_frame1.create(cResource(IDR_MAINFRAME), cwFrame::fsDockAny);


#ifdef __MDI_TEST__
#ifdef __TAB_TEST__
      ecl_child1.setTabView(&c1_view1, "View1");
      ecl_child1.create(&ecl_frame1, 0, "Fenschterle mit einer View");

      ecl_child2.setTabView(&c2_view1, "View1");
      ecl_child2.addTabView(&c2_view2, "View2");
      ecl_child2.create(&ecl_frame1, 0, "Fenschterle mit zwei Views");

      ecl_child3.setTabView(&c3_view1, "View1");
      ecl_child3.addTabView(&c3_view2, "View2");
      ecl_child3.addTabView(&c3_view3, "View3");
      ecl_child3.create(&ecl_frame1, 0, "Fenschterle mit drei Views");
#else
      ecl_child1.setView(&c1_view1);
      ecl_child1.create(&ecl_frame1, 0, "Fenschterle mit einer View");

      ecl_child2.setView(&c2_view1);
      ecl_child2.addView(&c2_view2, cwFrame::vpLeft, 128);
      ecl_child2.create(&ecl_frame1, 0, "Fenschterle mit zwei Views");

      ecl_child3.setView(&c3_view1);
      ecl_child3.addView(&c3_view2, cwFrame::vpLeft, 128);
      ecl_child3.addView(&c3_view3, cwFrame::vpTop, 128);
      ecl_child3.create(&ecl_frame1, 0, "Fenschterle mit drei Views");
#endif
#endif

      cdRect rect(cdPoint(128,384), cdVector(256,-256));

      ecl_float1.create(&ecl_frame1, cwMiniFrame::dksAlignRight, "Floater 1", rect);
      ecl_float1.dockWindow(cwMiniFrame::dpRight);
      ecl_float1.refresh();

      ecl_float2.create(&ecl_frame1, cwMiniFrame::dksAlignRight, "Floater 2", rect);
      ecl_float2.dockWindow(cwMiniFrame::dpRight, 50);
      ecl_float2.refresh();

      ecl_float3.create(&ecl_frame1, cwMiniFrame::dksAlignBottom, "Floater 3", rect);
      ecl_float3.dockWindow(cwMiniFrame::dpBottom);
      ecl_float3.refresh();

      ecl_frame1.show();
      ecl_frame1.forceUpdate();

      setMainWindow(&ecl_frame1);
      return true;
   }

   void onFileNew()
   {
#ifndef __MDI_TEST__
      ecl_view1.toggleDoc();
#else
      c1_view1.toggleDoc();
      c2_view1.toggleDoc();
      c3_view1.toggleDoc();
#endif
   }

   void onFileOpen()
   {
      cDlgMenu dlg_mnu;
      dlg_mnu.create(cResource(IDD_DLG_MENU), &ecl_frame1);
      dlg_mnu.process(true);
   }

};

cMyApplication theApp;


