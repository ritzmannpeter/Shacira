// ===========================================================================
// eb_dialogs.cpp                                ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwDialog          - Basisklasse fuer alle ECL-Dialoge
//        |  |
//        |  +-cwNotebookPage -
//        |
//        +-cwNotebookDlg     -
//
// ===========================================================================

#include "win/ew_dialogs.hpp"
#include "base/eb_list.hpp"

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

#include "win/ew_windows.hpp"
#include "win/ew_buttonctls.hpp"

#endif /*__INTERFACE__*/




// Constraints
// ===========================================================================
//
// Versuch der Dokumentation der Constraints:
//
//    +-----------------------+
//    |       +-----+         |
//    |       |  A  |         |
//    |       +-----+         |
//    |           +---+       |
//    |           | B |       |
//    | D         +---+       |
//    +-----------------------+
//
// tieChild(A, side, tSame, B)
//    Seite 'side' von A an Seite 'side' von B binden. D.h. egal wie und
//    durch was B bewegt wird, die Seite 'side' von A bewegt sich genauso.
//    Die Groesse von A wird nicht beeinflusst.
//
// tieChild(A, side, tOpposite, B)
//    Seite 'side' von A an Seite 'side' von B gegenueberliegende Seite
//    binden. D.h. egal wie und durch was B bewegt wird, die Seite 'side'
//    von A bewegt sich genauso wie die Gegenseite von B. Die Groesse von A
//    wird nicht beeinflusst.
//
// Entfaellt die Angabe von B, wird statt dessen der Dialog D angenommen.
//




// Lokale Funktionen
// ===========================================================================

#if defined __ECL_W32__

   static int ConvLMS(int sides)
   {
      int ox_lms = 0;
      if ( sides & cwDialog::sTop )     ox_lms |= OX_LMS_TOP;
      if ( sides & cwDialog::sBottom )  ox_lms |= OX_LMS_BOTTOM;
      if ( sides & cwDialog::sLeft )    ox_lms |= OX_LMS_LEFT;
      if ( sides & cwDialog::sRight )   ox_lms |= OX_LMS_RIGHT;
      return ox_lms;
   }

   static int ConvLMT(cwDialog::TIE tie)
   {
      int ox_lmt = OX_LMT_POSITION;
      if ( tie == cwDialog::tSame )     ox_lmt = OX_LMT_SAME;
      if ( tie == cwDialog::tOpposite ) ox_lmt = OX_LMT_OPPOSITE;
      return ox_lmt;
   }

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDialog
// ---------------------------------------------------------------------------
//
// Ueber diese Klassen werden die Dialogboxen des Systems verwaltet. Diese
// muessen als externe Resourcen in einer EXE- oder DLL-Datei vorliegen, die
// als cResource-Objekte im create-Aufruf angegeben werden.
//
//    Life-Cycle modal:          Life-Cycle modeless:
//
//    cwDialog dlg;              dlg = new cwDialog();
//    dlg.create(...);           dlg->create(...);
//    ...                        ...
//    dlg.process(...);          dlg->show();
//    ...                        ...
//    dlg deleted by C++         dlg->hide();
//                               delete dlg;
//
// cBase
//  +--cwWindow
//      +--cwDialog
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDialog : public cwWindow {
   ELO_DECLARE(cwDialog,cwWindow)
   friend class ccwDialog;

public:

   // Allgemeines
   // ===========

   // Konstruktor
   inline cwDialog() : cwWindow(0) { init(); }
   // Destruktor
   virtual ~cwDialog();

   // Verhalten beim Schliessen des Dialogs
   enum DISMISS {
      dmAbort,       // Dismiss abbrechen, zurueck zum Dialog
      dmStore,       // Aenderungen uebernehmen
      dmDiscard      // Aenderungen verwerfen
   };

   // Erzeugen des Dialogs
   void create(cResource res, cwWindow *parent = 0);
   // Ausfuehren des modalen Dialogs
   DISMISS process(bool center = false);


   // Navigation
   // ==========

   // Focus auf ein ueber cwWindow-Zeiger spezifiziertes Control setzen
   void gotoControl(cwWindow *ctrl);
   // Focus auf ein ueber Child-ID spezifiziertes Control setzen
   void gotoControl(int id);
   // Focus auf das naechste Control setzen
   void gotoNextControl();
   // Focus auf das vorangehende Control setzen
   void gotoPrevControl();


   // Default-Pushbutton
   // ==================

   // Neuen Default-Pushbutton ueber cwWindow-Zeiger setzen
   void setDefault(cwPushButton *pb);
   // Neuen Default-Pushbutton ueber Child-ID setzen
   void setDefaultID(int pb_id);
   // Child-ID des aktuellen Default-Pushbuttons erfragen
   int getDefaultID() const;


   // Constraints
   // ===========

   // Die Methoden zum Setzen von Constraints erhalten das zu manipulierende
   // Kindfenster wahlweise als cwWindow-Zeiger oder als Window-ID. Letztere
   // Methode hat den Vorteil, dass kein cwWindow-Objekt angelegt werden muss.

   enum SIDE {
      sLeft       = 0x00000001,        // Links
      sRight      = 0x00000002,        // Rechts
      sTop        = 0x00000004,        // Oben
      sBottom     = 0x00000008,        // Unten
      sHoriz      = sLeft | sRight,    // Links + Rechts
      sVert       = sTop | sBottom,    // Oben + Unten
      sAny        = sHoriz | sVert     // Alle Seiten
   };

   enum TIE {
      tSame,         // Binden an gleiche Seite von 'base'
      tOpposite,     // Binden an gegenueberliegende Seite von 'base'
      tPosition      // Binden an Relativposition
   };

   // "Binden" eines Child-Windows an eine Seite des Dialogs
   void tieChild(cwWindow *child, int sides, TIE tie = tSame, cwWindow *base = 0);
   // "Binden" eines Child-Windows (ueber ID) an eine Seite des Dialogs
   void tieChild(int child_id, int sides, TIE tie = tSame, int base_id = 0);
   // Constraint fuer ein Child-Window setzen
   void setConstraint(cwWindow *child, int sides, TIE tie = tSame, int offset = 0, cwWindow *base = 0);
   // Constraint fuer ein Child-Window (ueber ID) setzen
   void setConstraint(int child_id, int sides, TIE tie = tSame, int offset = 0, int base_id = 0);


protected:

   // Beenden des Dialogs
   // ===================

   // Beenden des Dialogs
   DISMISS dismiss(DISMISS dm);
   // Standard-Rueckfrage bei "Speichern"
   DISMISS defAskStore(); // war: DefAskStore
   // Standard-Rueckfrage bei "Abbrechen"
   DISMISS defAskDiscard(); // war: DefAskDiscard


   // Zusaetzliche Events
   // ===================

   // Wird beim Initialisieren des Dialogs aufgerufen
   virtual bool onInit();
   // Wird zum Setzen von Constraints aufgerufen (groessenaenderbare Seiten)
   virtual bool onSetConstraint();

   // Wird aufgerufen, um ein Child-Window an eine Seite des Dialogs zu "binden"
   virtual void onExecTieChild(cwWindow *child, int sides, TIE tie, cwWindow *base);
   // Wird aufgerufen, um ein Child-Window (ueber ID) an eine Seite des Dialogs zu "binden"
   virtual void onExecTieChild(int child_id, int sides, TIE tie, int base_id);
   // Wird aufgerufen, um ein Constraint fuer ein Child-Window zu setzen
   virtual void onExecSetConstraint(cwWindow *child, int sides, TIE tie, int offset0, cwWindow *base);
   // Wird aufgerufen, um ein Constraint fuer ein Child-Window (ueber ID) zu setzen
   virtual void onExecSetConstraint(int child_id, int sides, TIE tie, int offset, int base_id);

   // Rueckfrage bei "Speichern"
   virtual DISMISS onAskStore(); // war: AskStoreEvt
   // Rueckfrage bei "Abbrechen"
   virtual DISMISS onAskDiscard(); // war: AskDiscardEvt
   // Benutzer waehlt "OK"; Default-Aktion: dismiss(dmStore)
   virtual void onOk();
   // Benutzer waehlt "CANCEL"; Default-Aktion: dismiss(dmDiscard)
   virtual void onCancel();


   // Ueberschriebene Events
   // ======================

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onCreate();
   // Refresh durchfuehren (gibt false zurueck, wenn Abbruch)
   bool onRefresh(); // war: RefreshEvt
   // Beenden eines unterbrochenen "Schliessen"-Vorgangs
   void onResumeClose(); // war: ResumeClose
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommandUI(cwCmdUI& cmd);


protected:

   // Interner Konstruktor
   cwDialog(void *wnd);


private:
   DISMISS dm_code;     // Code beim Aufruf von dismiss

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDialog
// ===========================================================================

cwDialog::cwDialog(void *wnd) :
   cwWindow(wnd)
{
}

cwDialog::~cwDialog()
{
}

void cwDialog::init()
{
   #if defined __ECL_W32__
      _wnd = new WCDialog(this);
   #elif defined __ECL_OS2__
   #endif
}

void cwDialog::create(cResource res, cwWindow *parent)
{
   #if defined __ECL_W32__
      if ( _wnd == 0 )
         _wnd = new WCDialog(this);
      BOOL ok = ((WCDialog*)_wnd)->EclCreate(res.getID(), (CWnd*)__getWnd(parent));
      __ECL_ASSERT2__(ok, ("Unable to create modeless dialog from ressource id %d", res.getID()));
   #elif defined __ECL_OS2__
   #endif

   __attachDelayed();
}

cwDialog::DISMISS cwDialog::process(bool center)
{
   int rc = dmAbort;

   __ECL_ASSERT1__(_wnd != 0);

   refresh();

   if ( center )
      cwWindow::center();

   show();

   #if defined __ECL_W32__
      rc = ((WCDialog*)_wnd)->EclDoModal();
   #elif defined __ECL_OS2__
   #endif

   hide();

   return DISMISS(rc);
}


// Navigation
// ==========

void cwDialog::gotoControl(cwWindow *ctrl)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         if ( __ECL_ASSERT1__(ctrl != 0 && __getWnd(ctrl) != 0) ) {
            ((WCDialog*)_wnd)->GotoDlgCtrl((CWnd*)__getWnd(ctrl));
         }
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwDialog::gotoControl(int id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_ctrl = ((WCDialog*)_wnd)->GetDlgItem(id);
         if ( __ECL_ASSERT1__(mfc_ctrl != 0) ) {
            ((WCDialog*)_wnd)->GotoDlgCtrl(mfc_ctrl);
         }
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwDialog::gotoNextControl()
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((WCDialog*)_wnd)->NextDlgCtrl();
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwDialog::gotoPrevControl()
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((WCDialog*)_wnd)->PrevDlgCtrl();
      #elif defined __ECL_OS2__
      #endif
   }
}


// Default-Pushbutton
// ==================

void cwDialog::setDefault(cwPushButton *pb)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         if ( __ECL_ASSERT1__(pb != 0 && __getWnd(pb) != 0) ) {
            ((WCDialog*)_wnd)->SetDefID(((CWnd*)__getWnd(pb))->GetDlgCtrlID());
         }
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwDialog::setDefaultID(int pb_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((WCDialog*)_wnd)->SetDefID(pb_id);
      #elif defined __ECL_OS2__
      #endif
   }
}

int cwDialog::getDefaultID() const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         return ((WCDialog*)_wnd)->GetDefID();
      #elif defined __ECL_OS2__
      #endif
   }

   return IDOK;
}


// Constraints
// ===========

void cwDialog::tieChild(cwWindow *child, int sides, TIE tie, cwWindow *base)
{
   if ( child != 0 )
      onExecTieChild(child, sides, tie, base);
}

void cwDialog::tieChild(int child_id, int sides, TIE tie, int base_id)
{
   if ( child_id != 0 )
      onExecTieChild(child_id, sides, tie, base_id);
}

void cwDialog::setConstraint(cwWindow *child, int sides, TIE tie, int offset, cwWindow *base)
{
   if ( child != 0 )
      onExecSetConstraint(child, sides, tie, offset, base);
}

void cwDialog::setConstraint(int child_id, int sides, TIE tie, int offset, int base_id)
{
   if ( child_id != 0 )
      onExecSetConstraint(child_id, sides, tie, offset, base_id);
}


// Beenden des Dialogs
// ===================

cwDialog::DISMISS cwDialog::dismiss(DISMISS dm)
{
   cBase::DbgTrcWin("cwDialog::dismiss(%d)", dm);
   __ECL_ASSERT1__(_wnd != 0);

   dm_code = dm;

   switch ( dm_code ) {

   case dmStore:
      if ( allowStore() && (dm_code = onAskStore()) != dmAbort ) {
         if ( dm == dmStore && !store() || dm == dmDiscard && !discard() )
            return dmAbort;
         if ( allowClose(this) ) {
            #if defined __ECL_W32__
               ((WCDialog*)_wnd)->EclEndDialog(dm_code);
            #elif defined __ECL_OS2__
               WinDismissDlg(GetHandle(), dm_code);
            #endif
         }
      } else {
         dm_code = dmAbort;
      }
      break;

   case dmDiscard:
      if ( allowDiscard() && (dm_code = onAskDiscard()) != dmAbort ) {
         if ( dm == dmStore && !store() || dm == dmDiscard && !discard() )
            return dmAbort;
         if ( allowClose(this) ) {
            #if defined __ECL_W32__
               ((WCDialog*)_wnd)->EclEndDialog(dm_code);
            #elif defined __ECL_OS2__
               WinDismissDlg(GetHandle(), dm_code);
            #endif
         }
      } else {
         dm_code = dmAbort;
      }
      break;

   }

   return dm_code;
}

cwDialog::DISMISS cwDialog::defAskStore()
{
   __ECL_ASSERT1__(_wnd != 0);

// switch ( MsgBox(this, WDB_MBOX_STORE, MyModule) ) {
// case cwMsgDlg::Store:   return dmStore;
// case cwMsgDlg::Discard: return dmDiscard;
// }

   return dmAbort;
}

cwDialog::DISMISS cwDialog::defAskDiscard()
{
   __ECL_ASSERT1__(_wnd != 0);

// switch ( MsgBox(this, WDB_MBOX_DISCARD, MyModule) ) {
// case cwMsgDlg::Store:   return dmStore;
// case cwMsgDlg::Discard: return dmDiscard;
// }

   return dmAbort;
}


// Zusaetzliche Events
// ===================

bool cwDialog::onInit()
{
   cBase::DbgTrcWin("cwDialog::onInit()");

   #if defined __ECL_W32__
      WCDialog& dlg = *((WCDialog*)_wnd);
      dlg.lm.Attach((CWnd*)_wnd);
      dlg.lm.AddAllChildren();
      if ( onSetConstraint() )
         dlg.lm.RedrawLayout();
   #elif defined __ECL_OS2__
   #endif

   return true;
}

bool cwDialog::onSetConstraint()
{
   // Liefert 'true', wenn die neuen Constraints durchgefuehrt werden sollen
   return false;
}

void cwDialog::onExecTieChild(cwWindow *child, int sides, TIE tie, cwWindow *base)
{
   #if defined __ECL_W32__
      ((WCDialog*)_wnd)->lm.TieChild((CWnd*)__getWnd(child),
         ConvLMS(sides), ConvLMT(tie), (CWnd*)__getWnd(base));
   #elif defined __ECL_OS2__
   #endif
}

void cwDialog::onExecTieChild(int child_id, int sides, TIE tie, int base_id)
{
   #if defined __ECL_W32__
      ((WCDialog*)_wnd)->lm.TieChild(child_id, ConvLMS(sides), ConvLMT(tie), base_id);
   #elif defined __ECL_OS2__
   #endif
}

void cwDialog::onExecSetConstraint(cwWindow *child, int sides, TIE tie, int offset, cwWindow *base)
{
   #if defined __ECL_W32__
      ((WCDialog*)_wnd)->lm.SetConstraint((CWnd*)__getWnd(child),
         ConvLMS(sides), ConvLMT(tie), offset, (CWnd*)__getWnd(base));
   #elif defined __ECL_OS2__
   #endif
}

void cwDialog::onExecSetConstraint(int child_id, int sides, TIE tie, int offset, int base_id)
{
   #if defined __ECL_W32__
      ((WCDialog*)_wnd)->lm.SetConstraint(child_id, ConvLMS(sides), ConvLMT(tie), offset, base_id);
   #elif defined __ECL_OS2__
   #endif
}

cwDialog::DISMISS cwDialog::onAskStore()
{
   cBase::DbgTrcWin("cwDialog::onAskStore()");
   return dmStore;
}

cwDialog::DISMISS cwDialog::onAskDiscard()
{
   cBase::DbgTrcWin("cwDialog::onAskDiscard()");
   return dmDiscard;
}

void cwDialog::onOk()
{
   cBase::DbgTrcWin("cwDialog::onOk()");

   if ( !getFlags(wflInNotebook) ) {
      if ( allowStore() && store() ) {
         dismiss(dmStore);
      }
   } else {
      if ( allowStore() && store() ) {
         #if defined __ECL_W32__
            CWnd *mfc_wnd = ((WCDialog*)_wnd)->GetParent();
            if ( mfc_wnd != 0 )
               mfc_wnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDOK,1), NULL);
         #endif
      }
   }
}

void cwDialog::onCancel()
{
   cBase::DbgTrcWin("cwDialog::onCancel()");

   if ( !getFlags(wflInNotebook) ) {
      if ( allowDiscard() && discard() ) {
         dismiss(dmDiscard);
      }
   } else {
      if ( allowDiscard() && discard() ) {
         #if defined __ECL_W32__
            CWnd *mfc_wnd = ((WCDialog*)_wnd)->GetParent();
            if ( mfc_wnd != 0 )
               mfc_wnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDCANCEL,1), NULL);
         #endif
      }
   }
}


// Ueberschriebene Events
// ======================

bool cwDialog::onCreate()
{
   cBase::DbgTrcWin("cwDialog::onCreate");

   #if defined __ECL_W32__
      ((WCWnd*)_wnd)->ModifyStyle(DS_SETFONT | DS_FIXEDSYS,0);
   #else
   #endif

   return cwWindow::onCreate();
}

bool cwDialog::onRefresh()
{
   cBase::DbgTrcWin("cwDialog::onRefresh()");
#ifdef __How_To_Implement__
   if ( !getFlags(wflInNotebook) )
      SubstituteStrings();
#endif

   return cwWindow::onRefresh();
}

void cwDialog::onResumeClose()
{
   cBase::DbgTrcWin("cwDialog::onResumeClose");
#ifdef __How_To_Implement__
   // ??? PostMsg(WU_FORCECLOSE);
#endif
}

bool cwDialog::onCommand(const cwCmdEvt& cmd)
{
   // Kommando weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child != 0 && ccwWindow::onCommand(child, cmd) )
      return true;

   return cwWindow::onCommand(cmd);
}

bool cwDialog::onCommandUI(cwCmdUI& cmd)
{
   // UI-Aktualisierung weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child != 0 )
      return ccwWindow::onCommandUI(child, cmd);

   return cwWindow::onCommandUI(cmd);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwNotebookPage
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwDialog
//          +--cwNotebookPage
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwNotebookPage : public cwDialog {
   ELO_DECLARE(cwNotebookPage,cwDialog)
   friend class ccwNotebookPage;

public:

   // Allgemeines
   // ===========

   // Konstruktor
   inline cwNotebookPage() : cwDialog(0) { init(); }
   // Destruktor
   virtual ~cwNotebookPage();

   // Erzeugen der Notebook-Seite
   void create(cResource res, cResource title = cResource(0));

   // Modifiziert-Status aendern
   void setModified(bool modified = true);


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, wenn der Benutzer "OK" im Notebook-Dialog waehlt
   virtual void onOk();
   // Wird aufgerufen, wenn der Benutzer "CANCEL" im Notebook-Dialog waehlt
   virtual void onCancel();
   // Wird aufgerufen, wenn der Benutzer "APPLY" im Notebook-Dialog waehlt
   virtual bool onApply();
   // Wird aufgerufen, wenn der Benutzer "EDIT" im Notebook-Dialog waehlt
   virtual void onEdit();

   // Wird aufgerufen, wenn die Notebook-Seite angewaehlt wird (rc: false -> Anwahl nicht moeglich)
   virtual bool onEnter();
   // Wird aufgerufen, wenn die Notebook-Seite verlassen wird (rc: false -> Verlassen nicht moeglich)
   virtual bool onLeave();


   // Ueberschriebene Events
   // ======================

   // Wird beim Initialisieren des Dialogs aufgerufen
   bool onInit();

   // Wird aufgerufen, um ein Child-Window an eine Seite des Dialogs zu "binden"
   void onExecTieChild(cwWindow *child, int sides, TIE tie, cwWindow *base);
   // Wird aufgerufen, um ein Child-Window (ueber ID) an eine Seite des Dialogs zu "binden"
   void onExecTieChild(int child_id, int sides, TIE tie, int base_id);
   // Wird aufgerufen, um ein Constraint fuer ein Child-Window zu setzen
   void onExecSetConstraint(cwWindow *child, int sides, TIE tie, int offset0, cwWindow *base);
   // Wird aufgerufen, um ein Constraint fuer ein Child-Window (ueber ID) zu setzen
   void onExecSetConstraint(int child_id, int sides, TIE tie, int offset, int base_id);


protected:

   // Interner Konstruktor
   cwNotebookPage(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwNotebookPage
// ===========================================================================

cwNotebookPage::cwNotebookPage(void *wnd) :
   cwDialog(wnd)
{
   #ifdef __AutoDelete_Setzen_Oder_Nicht__
      // ... das ist hier die Frage ...
      setFlags(wflAutoDelete);
   #endif
}

cwNotebookPage::~cwNotebookPage()
{
}

void cwNotebookPage::init()
{
   #if defined __ECL_W32__
      _wnd = new WCPropertyPage(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwNotebookPage::create(cResource res, cResource title)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->Construct(res.getID(), title.getID());
   #elif defined __ECL_OS2__
   #endif

   // Wird zwar schon waehrend onInit() gemacht... Falls die Meldung
   // nicht durchkommt, sicherheitshalber aber nochmal:
   __attachDelayed();
}

void cwNotebookPage::setModified(bool modified)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->SetModified(modified);
   #elif defined __ECL_OS2__
   #endif
}


// Zusaetzliche Events
// ===================

void cwNotebookPage::onOk()
{
}

void cwNotebookPage::onCancel()
{
}

bool cwNotebookPage::onApply()
{
   return true;
}

void cwNotebookPage::onEdit()
{
}

bool cwNotebookPage::onEnter()
{
   // Liefert 'true', wenn die Seite betreten werden darf
   return refresh();
}

bool cwNotebookPage::onLeave()
{
   // Liefert 'true', wenn die Seite verlassen werden darf
   return allowTurn();
}


// Ueberschriebene Events
// ======================

bool cwNotebookPage::onInit()
{
   cBase::DbgTrcWin("cwNotebookPage::onInit()");

   #if defined __ECL_W32__
      WCPropertyPage *pp = ((WCPropertyPage*)_wnd);
      pp->lm.Attach((CWnd*)_wnd);
      pp->lm.AddAllChildren();
      if ( onSetConstraint() )
         pp->lm.RedrawLayout();
   #elif defined __ECL_OS2__
   #endif

   return true;
}

void cwNotebookPage::onExecTieChild(cwWindow *child, int sides, TIE tie, cwWindow *base)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->lm.TieChild((CWnd*)__getWnd(child),
         ConvLMS(sides), ConvLMT(tie), (CWnd*)__getWnd(base));
   #elif defined __ECL_OS2__
   #endif
}

void cwNotebookPage::onExecTieChild(int child_id, int sides, TIE tie, int base_id)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->lm.TieChild(child_id, ConvLMS(sides), ConvLMT(tie), base_id);
   #elif defined __ECL_OS2__
   #endif
}

void cwNotebookPage::onExecSetConstraint(cwWindow *child, int sides, TIE tie, int offset, cwWindow *base)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->lm.SetConstraint((CWnd*)__getWnd(child),
         ConvLMS(sides), ConvLMT(tie), offset, (CWnd*)__getWnd(base));
   #elif defined __ECL_OS2__
   #endif
}

void cwNotebookPage::onExecSetConstraint(int child_id, int sides, TIE tie, int offset, int base_id)
{
   #if defined __ECL_W32__
      ((WCPropertyPage*)_wnd)->lm.SetConstraint(child_id, ConvLMS(sides), ConvLMT(tie), offset, base_id);
   #elif defined __ECL_OS2__
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwNotebookDlg
// ---------------------------------------------------------------------------
//
// Ueber diese Klasse werden Notizbuech-Dialoge verwaltet. Notizbuch-Dialoge
// koennen beliebige andere Dialoge als Seiten aufnehmen, wenn diese mit Hilfe
// von cwNotebookPage angelegt wurden. Mit Hilfe der Methode addPage() muss
// mindestens eine Seite eingefuegt werden, bevor der Dialog angezeigt werden
// kann. Der Notizbuchdialog ist vom Benutzer in seiner Groesse aenderbar.
//
//    Life-Cycle modal:          Life-Cycle modeless:
//
//    cwDialog dlg;              dlg = new cwNotebookDlg();
//    dlg.create(...);           dlg->create(...);
//    ...                        ...
//    dlg->addPage(...);         dlg->addPage(...);
//    ...                        ...
//    dlg.process(...);          dlg->show();
//    ...                        ...
//    dlg deleted by C++         dlg->hide();
//                               delete dlg;
//
// cBase
//  +--cwWindow
//      +--cwNotebookDlg
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwNotebookDlg : public cwWindow {
   ELO_DECLARE(cwNotebookDlg,cwWindow)
   friend class ccwNotebookDlg;

public:

   // Konstruktor
   inline cwNotebookDlg() : cwWindow(0) { init(); }
   // Destruktor
   virtual ~cwNotebookDlg();


   // window-Flags
   // ============

   // Flags
   enum FLAGS { wflFirst = cwWindow::wflUser,
      wflAutoDeletePages   = wflFirst << 0,  // Eingefuegte Seiten loeschen
      wflUser              = wflFirst << 1   // Offset fuer benutzerdef. Flags
   };


   // Notebook-Style
   // ==============

   // Styles
   enum NOTEBOOK_STYLE { nbsFirst = 1,
      nbsOkBtn             = nbsFirst << 0,  // Ein OK-Button wird angezeigt
      nbsCancelBtn         = nbsFirst << 1,  // Ein CANCEL-Button wird angezeigt
      nbsApplyBtn          = nbsFirst << 2,  // Ein APPLY-Button wird angezeigt
      nbsHelpBtn           = nbsFirst << 3,  // Ein HELP-Button wird angezeigt
      nbsEditBtn           = nbsFirst << 4,  // Ein EDIT-Button wird angezeigt
      //
      nbsStdBtns           = nbsOkBtn|nbsCancelBtn|nbsApplyBtn,
      nbsAllBtns           = nbsStdBtns|nbsHelpBtn|nbsEditBtn
   };

   // Alle aktuellen Notebook-Styles ermitteln
   inline int getStyle() const
      { return style; }
   // Bestimmte aktuelle Notebook-Styles ermitteln
   inline int getStyle(int mask) const
      { return style & mask; }


   // Allgemeines
   // ===========

   // Verhalten beim Schliessen des Dialogs
   enum DISMISS {
      dmAbort,       // Dismiss abbrechen, zurueck zum Dialog
      dmStore,       // Aenderungen uebernehmen
      dmDiscard      // Aenderungen verwerfen
   };

   // Erzeugen des Notebook-Dialogs
   void create(cwWindow *parent, cString text, int style = nbsStdBtns, int flags = 0);

   // Seite einfuegen
   void addPage(cwNotebookPage *page);
   // Seite entfernen
   void removePage(cwNotebookPage *page);

   // Ausfuehren des modalen Dialogs
   DISMISS process(bool center = false);
   // Notebook-Dialog anzeigen
   void show();


protected:

   // Beenden des Dialogs
   // ===================

   // Beenden des Dialogs
   DISMISS dismiss(DISMISS dm);
   // Standard-Rueckfrage bei "Speichern"
   DISMISS defAskStore(); // war: DefAskStore
   // Standard-Rueckfrage bei "Abbrechen"
   DISMISS defAskDiscard(); // war: DefAskDiscard


   // Zusaetzliche Events
   // ===================

   // Wird beim Initialisieren des Dialogs aufgerufen
   virtual bool onInit();

   // Wird aufgerufen, nachdem eine Seite eingefuegt wurde
   virtual void onPageAdded(cwNotebookPage *page);
   // Wird aufgerufen, befor eine Seite entfernt wird
   virtual void onPageRemoved(cwNotebookPage *page);

   // Rueckfrage bei "Speichern"
   virtual DISMISS onAskStore(); // war: AskStoreEvt
   // Rueckfrage bei "Abbrechen"
   virtual DISMISS onAskDiscard(); // war: AskDiscardEvt

   // Benutzer waehlt "OK"; Default-Aktion: dismiss(dmStore)
   virtual void onOk();
   // Benutzer waehlt "CANCEL"; Default-Aktion: dismiss(dmDiscard)
   virtual void onCancel();
   // Benutzer waehlt "APPLY"
   virtual void onApply();
   // Benutzer waehlt "EDIT"
   virtual void onEdit();


   // Ueberschriebene Events
   // ======================

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onCreate();
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Refresh durchfuehren (gibt false zurueck, wenn Abbruch)
   bool onRefresh();
   // Beenden eines unterbrochenen "Schliessen"-Vorgangs
   void onResumeClose();


protected:

   // Interner Konstruktor
   cwNotebookDlg(void *wnd);


private:

   // Aktueller Notebook-Style
   int style;

   // Zusaetzliche Informationen
   struct ADD_INFO;
   ADD_INFO *info;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwNotebookDlg
// ===========================================================================

typedef cList<cwNotebookPage*,cwNotebookPage*> PAGE_LIST;

struct cwNotebookDlg::ADD_INFO {
   DISMISS dm_code;        // Code beim Aufruf von dismiss
   PAGE_LIST page_list;    // Liste eingefuegter Seiten
};

cwNotebookDlg::cwNotebookDlg(void *wnd) :
   cwWindow(wnd)
{
   info = new ADD_INFO;
   style = 0;
}

cwNotebookDlg::~cwNotebookDlg()
{
   if ( getFlags(wflAutoDeletePages) ) {
      for ( IPOSITION pos = info->page_list.getHeadPosition() ; pos != 0 ; ) {
         cwNotebookPage *page = info->page_list.getNext(pos);
         delete page;
      }
   }

   delete info;
}

void cwNotebookDlg::init()
{
   info = new ADD_INFO;
   style = 0;

   #if defined __ECL_W32__
      _wnd = new WCPropertySheet(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwNotebookDlg::create(cwWindow *parent, cString text, int style, int flags)
{
   cwNotebookDlg::style = style;
   setFlags(flags);
   setParent(parent);

   #if defined __ECL_W32__
      ((WCPropertySheet*)_wnd)->Construct(text, (CWnd*)__getWnd(parent));
   #elif defined __ECL_OS2__
   #endif
}

cwNotebookDlg::DISMISS cwNotebookDlg::process(bool /*center*/)
{
   int rc = dmAbort;

   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      rc = ((WCPropertySheet*)_wnd)->DoModal();
   #elif defined __ECL_OS2__
   #endif

   return DISMISS(rc);
}

void cwNotebookDlg::show()
{
   // Da modeless cwNotebookDlg nur dynamisch allokiert sinnvoll ist,
   // hier das wflAutoDelete-Flag setzen. Explizites loeschen nur mit "destroy"!
   setFlags(wflAutoDelete);

   #if defined __ECL_W32__
      WCWnd *parent_wnd = (WCWnd*)__getWnd(getParent());
      WCPropertySheet& ps = *((WCPropertySheet*)_wnd);
      __ECL_ASSERT2__(ps.Create(parent_wnd), ("Unable to create modeless notebook dialog"));
   #elif defined __ECL_OS2__
   #endif

   cwWindow::show();
}

void cwNotebookDlg::addPage(cwNotebookPage *page)
{
   #if defined __ECL_W32__
      ((WCPropertySheet*)_wnd)->AddPage((WCPropertyPage*)__getWnd(page));
   #elif defined __ECL_OS2__
   #endif

   info->page_list.addTail(page);
   onPageAdded(page);
}

void cwNotebookDlg::removePage(cwNotebookPage *page)
{
   IPOSITION pos = info->page_list.find(page);
   if ( __ECL_ASSERT1__(pos != 0) )
      info->page_list.removeAt(pos);

   onPageRemoved(page);

   #if defined __ECL_W32__
      ((WCPropertySheet*)_wnd)->RemovePage((WCPropertyPage*)__getWnd(page));
   #elif defined __ECL_OS2__
   #endif
}


// Beenden des Dialogs
// ===================

cwNotebookDlg::DISMISS cwNotebookDlg::dismiss(DISMISS dm)
{
   cBase::DbgTrcWin("cwNotebookDlg::dismiss(%d)", dm);
   __ECL_ASSERT1__(_wnd != 0);

   info->dm_code = dm;

   switch ( dm ) {

   case dmStore:
      if ( allowStore() && (dm = info->dm_code = onAskStore()) != dmAbort ) {
         if ( dm == dmStore && !store() || dm == dmDiscard && !discard() )
            return dmAbort;
         if ( allowClose(this) ) {
            #if defined __ECL_W32__
               ((WCPropertySheet*)_wnd)->EndDialog(dm);
            #elif defined __ECL_OS2__
               WinDismissDlg(GetHandle(), dm);
            #endif
         }
      } else {
         dm = info->dm_code = dmAbort;
      }
      break;

   case dmDiscard:
      if ( allowDiscard() && (dm = info->dm_code = onAskDiscard()) != dmAbort ) {
         if ( dm == dmStore && !store() || dm == dmDiscard && !discard() )
            return dmAbort;
         if ( allowClose(this) ) {
            #if defined __ECL_W32__
               ((WCPropertySheet*)_wnd)->EndDialog(dm);
            #elif defined __ECL_OS2__
               WinDismissDlg(GetHandle(), dm);
            #endif
         }
      } else {
         dm = info->dm_code = dmAbort;
      }
      break;

   }

   return dm;
}

cwNotebookDlg::DISMISS cwNotebookDlg::defAskStore()
{
   __ECL_ASSERT1__(_wnd != 0);

// switch ( MsgBox(this, WDB_MBOX_STORE, MyModule) ) {
// case cwMsgDlg::Store:   return dmStore;
// case cwMsgDlg::Discard: return dmDiscard;
// }

   return dmAbort;
}

cwNotebookDlg::DISMISS cwNotebookDlg::defAskDiscard()
{
   __ECL_ASSERT1__(_wnd != 0);

// switch ( MsgBox(this, WDB_MBOX_DISCARD, MyModule) ) {
// case cwMsgDlg::Store:   return dmStore;
// case cwMsgDlg::Discard: return dmDiscard;
// }

   return dmAbort;
}


// Zusaetzliche Events
// ===================

bool cwNotebookDlg::onInit()
{
   cBase::DbgTrcWin("cwNotebookDlg::onInit()");
   return true;
}

void cwNotebookDlg::onPageAdded(cwNotebookPage * /*page*/)
{
   cBase::DbgTrcWin("cwNotebookDlg::onPageAdded()");
}

void cwNotebookDlg::onPageRemoved(cwNotebookPage * /*page*/)
{
   cBase::DbgTrcWin("cwNotebookDlg::onPageRemoved()");
}

cwNotebookDlg::DISMISS cwNotebookDlg::onAskStore()
{
   cBase::DbgTrcWin("cwNotebookDlg::onAskStore()");
   return dmStore;
}

cwNotebookDlg::DISMISS cwNotebookDlg::onAskDiscard()
{
   cBase::DbgTrcWin("cwNotebookDlg::onAskDiscard()");
   return dmDiscard;
}

void cwNotebookDlg::onOk()
{
   cBase::DbgTrcWin("cwNotebookDlg::onOk()");
   if ( !getFlags(wflInNotebook) )
      dismiss(dmStore);
}

void cwNotebookDlg::onCancel()
{
   cBase::DbgTrcWin("cwNotebookDlg::onCancel()");
   if ( !getFlags(wflInNotebook) )
      dismiss(dmDiscard);
}

void cwNotebookDlg::onApply()
{
   cBase::DbgTrcWin("cwNotebookDlg::onApply()");
}

void cwNotebookDlg::onEdit()
{
   cBase::DbgTrcWin("cwNotebookDlg::onEdit()");
}


// Ueberschriebene Events
// ======================

bool cwNotebookDlg::onCreate()
{
   cBase::DbgTrcWin("cwNotebookDlg::onCreate");

   #if defined __ECL_W32__
      ((WCPropertySheet*)_wnd)->ModifyStyle(DS_SETFONT | DS_FIXEDSYS,0);
   #else
   #endif

   return cwWindow::onCreate();
}

bool cwNotebookDlg::onCommand(const cwCmdEvt& cmd)
{
   cBase::DbgTrcWin("cwNotebookDlg::onCommand");

   #if defined __ECL_W32__
      switch ( cmd.getId() ) {
      case IDOK:           onOk(); return true;
      case IDCANCEL:       onCancel(); return true;
      case ID_APPLY_NOW:   onApply(); return true;
    //case ID_EDIT:        onEdit(); return true;
      }
   #else
   #endif

   return false;
}

bool cwNotebookDlg::onRefresh()
{
   cBase::DbgTrcWin("cwNotebookDlg::onRefresh()");
#ifdef __How_To_Implement__
   if ( !getFlags(wflInNotebook) )
      SubstituteStrings();
#endif

   return cwWindow::onRefresh();
}

void cwNotebookDlg::onResumeClose()
{
   cBase::DbgTrcWin("cwNotebookDlg::onResumeClose");
#ifdef __How_To_Implement__
   // ??? PostMsg(WU_FORCECLOSE);
#endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwMsgDlg
// ---------------------------------------------------------------------------
//
// Diese Klasse stellt eine Art "bessere" MessageBox zur Verfuegung. Ueber
// eine vom Benutzer der Klasse zur Verfuegung gestellte Dialog-Resource
// koennen beliebig gestaltete Dialoge als Message-Box benutzt werden. Dabei
// sind die folgenden Dialogfelder vorgegeben:
//
//    Class      | ID                | Bedeutung
//   ------------+-------------------+---------------------------
//    Static     | ECLID_TXT_MESSAGE | Primaere Meldung
//    Static     | ECLID_TXT_EXPLAIN | Erlaeuterung der Meldung
//    PushButton | ECLID_PB_STORE    | Auswahl "Speichern"
//    PushButton | ECLID_PB_DISCARD  | Auswahl "Verwerfen"
//    PushButton | ECLID_PB_RETRY    | Auswahl "Wiederholen"
//    PushButton | ECLID_PB_READONLY | Auswahl "Nur lesen"
//    PushButton | ECLID_PB_YES      | Auswahl "Ja"
//    PushButton | ECLID_PB_NO       | Auswahl "Nein"
//
// cBase
//  +--cwWindow
//      +--cwDialog
//          +--cwMsgDlg
//
// ===========================================================================

#define ECLID_BASE            10000
#define ECLID_PB_CANCEL       (ECLID_BASE+100)
#define ECLID_PB_STORE        (ECLID_BASE+101)
#define ECLID_PB_DISCARD      (ECLID_BASE+102)
#define ECLID_PB_RETRY        (ECLID_BASE+103)
#define ECLID_PB_READONLY     (ECLID_BASE+104)
#define ECLID_PB_YES          (ECLID_BASE+105)
#define ECLID_PB_NO           (ECLID_BASE+106)

class __ECL_DLLEXPORT__ cwMsgDlg : public cwDialog {
   ELO_DECLARE(cwMsgDlg,cwDialog)

public:
   void create(cResource res, cwWindow *parent = 0,
      cString title = "", cString msg = "", cString explain = "");

   enum RESULT { None, Abort, Store, Discard, Retry, ReadOnly, Yes, No };

   RESULT process();


protected:

   // Ueberschriebene Events
   // ======================

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Benutzer waehlt "OK"; Default-Aktion: dismiss(dmStore)
   void onOk();
   // Benutzer waehlt "CANCEL"; Default-Aktion: dismiss(dmDiscard)
   void onCancel();


private:
   RESULT res;

};

#endif /*__INTERFACE__*/


// Implementierung cwMsgDlg
// ===========================================================================

void cwMsgDlg::create(cResource res, cwWindow *parent,
                      cString title, cString msg, cString explain)
{
   cwDialog::create(res, parent);

// cWindow *msg = new0 cWindow(WC_STATIC, this, ECLID_TXT_MESSAGE, 0, NULL, NULL, NULL);
// cWindow *expl = new0 cWindow(WC_STATIC, this, ECLID_TXT_EXPLAIN, 0, NULL, NULL, NULL);

   if ( !title.isEmpty() )
      setText(title);
// if ( !msg.IsEmpty() )
//    msg->setText(_msg);
// if ( !explain.IsEmpty() )
//    expl->setText(_explain);
}

cwMsgDlg::RESULT cwMsgDlg::process()
{
   res = None;
   cwDialog::process(TRUE);
   return res;
}


// Ueberschriebene Events
// ======================

bool cwMsgDlg::onCommand(const cwCmdEvt& cmd)
{
   switch ( cmd.getId() ) {
   case ECLID_PB_CANCEL:   res = Abort;    break;
   case ECLID_PB_STORE:    res = Store;    break;
   case ECLID_PB_DISCARD:  res = Discard;  break;
   case ECLID_PB_RETRY:    res = Retry;    break;
   case ECLID_PB_READONLY: res = ReadOnly; break;
   case ECLID_PB_YES:      res = Yes;      break;
   case ECLID_PB_NO:       res = No;       break;
   default:
      return cwDialog::onCommand(cmd);
   }

   dismiss(dmStore);
   return true;
}

void cwMsgDlg::onOk()
{
   res = Store;
   cwDialog::onOk();
}

void cwMsgDlg::onCancel()
{
   res = Abort;
   cwDialog::onCancel();
}




#ifdef __INTERFACE__

// ===========================================================================
// res = MsgBox(res, parent, [,title, msg, explain])
// ---------------------------------------------------------------------------
// Anzeige einer benutzerdefinierten "MessageBox" ueber die cwMsgDlg-Klasse. Als
// Funktionswert wird die vom Benutzer ausgewaehlte Alternative zurueckgegeben.
// ===========================================================================

cwMsgDlg::RESULT __ECL_DLLEXPORT__ MsgBox(cResource res, cwWindow *parent = 0,
   cString title = "", cString msg = "", cString explain = "");

#endif /*__INTERFACE__*/


// Implementierung MsgBox()
// ===========================================================================

cwMsgDlg::RESULT MsgBox(cResource res, cwWindow *parent,
                       cString title, cString msg, cString explain)
{
   cwMsgDlg askdlg;
   askdlg.create(res, parent, title, msg, explain);
   return askdlg.process();
}

