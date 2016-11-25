// ===========================================================================
// er_printer.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-crPrinter         -
//
// ===========================================================================

#include "rep/er_printer.hpp"
#include "win/ew_windows.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include "win/ew_lboxctls.hpp"
   #include "win/ew_dialogs.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc_c.hpp"
   #include "win/system/mfc/stdafx.h"
   #include "rep/system/w32/w32_prndev.hpp"
   #include <winspool.h>
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_prof.hpp"
#include "rep/er_prnform.hpp"

class cwWindow;

#endif /*__INTERFACE__*/




#if defined __ECL_OS2__

   // ===========================================================================
   // Klasse cPrQuery
   // ---------------------------------------------------------------------------
   //
   // Abfrage zum Fuellen der Queue-Auswahl-Listbox mit den Queue-Namen aus
   // der crPrnSpooler-Klasse.
   //
   // cBase
   //  +--csBaseStorage
   //      +--csQuery
   //          +--cSmallQuery
   //              +--cPrQuery
   //
   // ===========================================================================

   class cPrQuery : public csQuery {

   public:

      cPrQuery(crPrnSpooler *_qmgr)
         { qmgr = _qmgr; }

   protected:

      bool onRewind()
         { act = -1; return true; }

      bool onFetch()
         { return ++act < qmgr->getQueueCount(); }

      bool onGetString(int fld, cString &buf) const
      {
         if ( fld == fldKey ) {
            buf = Str(act);
         } else {
            crPrnQueue queue = qmgr->getQueue(act);
            const char *comment = queue.getComment();
            const char *name = (comment && *comment) ? comment : queue.getName();
            buf = name;
         }

         return true;
      }

   private:

      int act;
      crPrnSpooler *qmgr;

   };


   // ===========================================================================
   // Klasse cRequestPrinter
   // ---------------------------------------------------------------------------
   //
   // cBase
   //  +--cwWindow
   //      +--cwDialog
   //          +--cRequestPrinter
   //
   // ===========================================================================

   class cRequestPrinter : public cwDialog {

   public:

      cRequestPrinter(cwWindow *_owner, crPrinter *_prn, crPrnSpooler *_qmgr)
       : cwDialog(_owner, IDD_QUERYPRINT, MyModule)
      {
         lbxPrinter = new cwListBox(this, IDD_QPLISTBOX, new cVar(pridx), new cPrQuery(_qmgr));
         lbxPrinter->SetEventFunc((EVENT)LbxClicked);

         pbProperties = new cwPushButton(this, IDD_QPJOBPROP);
         pbProperties->SetEventFunc((EVENT)PbClicked);

         pbOk = new cwPushButton(this, DID_OK);
         pbCancel = new cwPushButton(this, DID_CANCEL);
         pbHelp = new cwPushButton(this, IDD_HELP);

         prn = _prn;
         qmgr = _qmgr;
         pridx = -1;
      }

      bool RefreshEvt()
      {
         crPrnQueue queue = prn->GetAssociatedQueue();

         for ( int i = 0; i < qmgr->getQueueCount(); i++ )
            if ( 0 == strcmp(qmgr->getQueue(i).getName(), queue.getName()) )
               pridx = i;

         return cwDialog::RefreshEvt();
      }

      bool StoreEvt()
      {
         if ( !cwDialog::StoreEvt() )
            return false;
         prn->SetAssociatedQueue(qmgr->getQueue(pridx));
         return true;
      }

      int LbxClicked(cBase *obj, void *)
      {
         Dismiss(dmStore);
         return 0;
      }

      int PbClicked(cBase *obj, void *)
      {
         qmgr->getQueue(pridx).queryJobProperties(true);
         return 0;
      }

   private:

      cwListBox *lbxPrinter;
      cwPushButton *pbProperties;
      cwPushButton *pbOk, *pbCancel, *pbHelp;

      crPrinter *prn;
      crPrnSpooler *qmgr;
      int pridx;

   };

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrinter
// ---------------------------------------------------------------------------
//
// cBase
//  +--crPrinter
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrinter : public cBase {
   friend class cPrintDoc;

public:

   // Konstruktor
   crPrinter();
   // Destruktor
   ~crPrinter();


   // Formulardaten erfragen
   // ======================

   // Ausgewaehltes Formular erfragen
   crPrnForm getCurrentForm() const;

   // Ermittelt die Papiergroesse in mm
   void getPaperSize(double& width, double& height);
   // Ermittelt die Groesse des bedruckbaren Bereichs in mm
   void getPrintableSize(double& width, double& height);
   // Ermittelt die druckerspezifischen Randeinstellungen
   void getMargins(double& left, double& right, double& top, double& bottom);


   // Zuordnungen
   // ===========

   // Queue zuordnen
   void setAssociatedQueue(crPrnQueue queue);
   // Zugeordnete Queue erfragen
   crPrnQueue getAssociatedQueue() const;


   // Einstellungen verwalten
   // =======================

   enum SHOW {
      showNever,           // Dialog nicht anzeigen, evtl. Defaultwerte waehlen
      showNeverAndFail,    // Dialog nicht anzeigen, evtl. mit false zurueck
      showIfNecessary,     // Dialog anzeigen, wenn noch keine Auswahl
      showAlways           // Dialog immer anzeigen
   };

   // Aktuelle Druckereinstellungen aus Profile laden bzw. ueber Auswahldialog
   bool load(cProfile *prf, cString app, cString key, cwWindow *parent = 0, SHOW show_dlg = showNever);
   // Sichern der aktuellen Druckereinstellungen im Profile
   void save(cProfile *prf, cString app, cString key);


private:

   crPrnSpooler spooler;   // Verwaltungsinstanz fuer Queue-Objekte
   crPrnQueue cur_queue;   // Aktueller Drucker(-warteschlange)
   crPrnForm cur_form;     // Aktuelles Formular

   // Intern: Liest Einstelldaten aus Profile
   crPrnDriver readFromProfile(cProfile *prf, cString app, cString key, cString& queue_name) const;
   // Intern: Schreibt Einstelldaten in Profile
   void writeToProfile(cProfile *prf, cString app, cString key) const;
   // Intern: Druckerauswahl
   bool requestPrinter(cwWindow *parent);

};

#endif /*__INTERFACE__*/


// Implementierung crPrinter
// ===========================================================================

crPrinter::crPrinter()
{
}

crPrinter::~crPrinter()
{
}


// Formulardaten erfragen
// ======================

crPrnForm crPrinter::getCurrentForm() const
{
   return cur_form;
}

void crPrinter::getPaperSize(double& width, double& height)
{
   width  = cur_form.getWidth();
   height = cur_form.getHeight();
}

void crPrinter::getPrintableSize(double& width, double& height)
{
   width  = cur_form.getClipWidth();
   height = cur_form.getClipHeight();
}

void crPrinter::getMargins(double& left, double& right, double& top, double& bottom)
{
   c2dBox box = cur_form.getRect();
   left   = box.getXLeft();
   right  = box.getXRight();
   top    = box.getYTop();
   bottom = box.getYBottom();
}


// Zuordnungen
// ===========

void crPrinter::setAssociatedQueue(crPrnQueue new_queue)
{
   cur_queue = new_queue;

   #if defined __ECL_W32__

      crPrnDriver driver = new_queue.getDriver();
      DEVMODE *dm = (DEVMODE*)driver.getData();

      HDC hdc = CreateIC(NULL, new_queue.getName(), NULL, dm);

      if ( hdc != NULL ) {

         int horzsize = GetDeviceCaps(hdc, HORZSIZE);
         int vertsize = GetDeviceCaps(hdc, VERTSIZE);
         int logpixelsx = GetDeviceCaps(hdc, LOGPIXELSX);
         int logpixelsy = GetDeviceCaps(hdc, LOGPIXELSY);
         double physical_width = GetDeviceCaps(hdc, PHYSICALWIDTH) * 25.4 / logpixelsx;
         double physical_height = GetDeviceCaps(hdc, PHYSICALHEIGHT) * 25.4 / logpixelsy;
         double physical_offsetx = GetDeviceCaps(hdc, PHYSICALOFFSETX) * 25.4 / logpixelsx;
         double physical_offsety = GetDeviceCaps(hdc, PHYSICALOFFSETY) * 25.4 / logpixelsy;

         double dx = round(physical_width, 1);
         double dy = round(physical_height, 1);
         double xs = round(physical_offsetx, 1);
         double ys = round(physical_height - physical_offsety - vertsize, 1);
         double xe = round(physical_offsetx + horzsize, 1);
         double ye = round(physical_height - physical_offsety, 1);

         cString form_name = "-?-";

         if ( /*(dm->dmFields & DM_FORMNAME) &&*/ dm->dmFormName[0] ) {
            form_name = (const char *)dm->dmFormName;
         } else {
            crPrnFormMgr form_mgr(cur_queue);
            double err = 1e42;
            for ( int i = 0 ; i < form_mgr.getFormCount() ; i++ ) {
               crPrnForm form = form_mgr.getForm(i);
               double err1 = fabs(form.getWidth() - dx) + fabs(form.getHeight() - dy);
               double err2 = fabs(form.getWidth() - dy) + fabs(form.getHeight() - dx);
               double min_err = min(err1, err2);
               if ( min_err < err ) {
                  form_name = form.getName();
                  err = min_err;
               }
            }
         }

         cur_form = crPrnForm(form_name, c2dBox(0,0,dx,dy), c2dBox(xs,ys,xe,ye), true);
         DeleteDC(hdc);
      }

   #else

      crPrnFormMgr form_mgr(cur_queue);
      cur_form = form_mgr.getCurrentForm();

   #endif
}

crPrnQueue crPrinter::getAssociatedQueue() const
{
   return cur_queue;
}


// Einstellungen verwalten
// =======================

bool crPrinter::load(cProfile *prf, cString app, cString key, cwWindow *parent, SHOW show_dlg)
{
   cString queue_name;
   crPrnDriver default_driver;

   // Sind ueberhaupt Queues definiert?
   if ( spooler.getQueueCount() < 1 ) {
      cwWindow::showInfo(parent,
         "Kein Drucker gefunden! Bitte richten Sie einen Drucker ein.");
      cur_form = crPrnForm();
      return false;
   }

   // Lesen von Vorgabewerten (Queuename, Treiberdaten)
   if ( prf != 0 && !app.isEmpty() && !key.isEmpty() )
      default_driver = readFromProfile(prf, app, key, queue_name);

   // Ist die bevorzugte Queue (noch) vorhanden? Ueber Spooler suchen.
   if ( !queue_name.isEmpty() ) {
      if ( spooler.findQueue(queue_name) < 0 ) {
         queue_name.clear();
         if ( show_dlg == showIfNecessary )
            show_dlg = showAlways;
      }
   }

   // Immer noch keine Queue? Default-Queue verwenden.
   if ( !queue_name.isEmpty() == 0 ) {
      if ( show_dlg == showNeverAndFail ) {
         cur_form = crPrnForm();
         return false;
      }
      queue_name = spooler.getDefaultQueue().getName();
      if ( show_dlg == showIfNecessary )
         show_dlg = showAlways;
   }

   // Zugeordnete Queue ermitteln, Default-Job-Properties holen
   crPrnQueue queue = spooler.getQueue(spooler.findQueue(queue_name));
   queue.queryJobProperties(false);

   // Default-Treiberdaten in Queue speichern
   if ( default_driver.getDataLen() > 0 ) {
      if ( !queue.setDefaultDriverData(default_driver) ) {
         cwWindow::showInfo(parent,
            "Die Version oder der Name des Druckertreibers hat sich geändert! "
            "Es wird die Voreinstellung des Druckerobjekts übernommen.");
         if ( show_dlg == showIfNecessary )
            show_dlg = showAlways;
      }
   }

   queue = spooler.getQueue(spooler.findQueue(queue_name));
   setAssociatedQueue(queue);

   // Display dialog box to select a printer
   return show_dlg == showAlways ?
      requestPrinter(parent)
    : true;
}

void crPrinter::save(cProfile *prf, cString app, cString key)
{
   if ( __ECL_ASSERT1__(prf != 0 && !app.isEmpty() && !key.isEmpty()) )
      writeToProfile(prf, app, key);
}


// Internes
// ========

crPrnDriver crPrinter::readFromProfile(cProfile *prf, cString app, cString key, cString& queue_name) const
{
   // Liest das Profile 'prf', belegt die Komponente 'queue_name'
   // und liefert ein fertig konstruiertes crPrnDriver-Objekt zurueck

   crPrnDriver new_driver;
   void *ddata; long ddlen;

   queue_name = prf->read(app, key + "Queue", queue_name);
   cString driver_name = prf->read(app, key + "Driver");

   if ( (ddlen = prf->read(app, key + "DriverSize", 0)) > 0 ) {
      if ( (ddata = malloc(ddlen)) != NULL ) {
         if ( prf->read(app, key + "DriverData", ddata, ddlen) > 0 )
            new_driver = crPrnDriver(driver_name, ddata, ddlen);
         free(ddata);
      } else {
         DbgError("could not allocate %d bytes for driver_data", ddlen);
      }
   }

   return new_driver;
}

void crPrinter::writeToProfile(cProfile *prf, cString app, cString key) const
{
   crPrnDriver driver = cur_queue.getDriver();

   if ( cur_queue.isInitialized() && cur_queue.getName() )
      prf->write(app, key + "Queue", cur_queue.getName());

   if ( !driver.getName().isEmpty() )
      prf->write(app, key + "Driver", driver.getName());

   if ( driver.getDataLen() > 0 ) {
      long ddlen = driver.getDataLen();
      prf->write(app, key + "DriverSize", ddlen);
      prf->write(app, key + "DriverData", driver.getData(), ddlen);
   }
}

bool crPrinter::requestPrinter(cwWindow *parent)
{
   #if defined __ECL_OS2__

      cRequestPrinter *qp = new cRequestPrinter(parent, this, &spooler);
      cwDialog::DISMISS dm = qp->process(true);
      delete qp;
      return dm != cwDialog::dmDiscard;

   #elif defined __ECL_W32__

      crPrnQueue queue = getAssociatedQueue();
      crPrnDriver driver = queue.getDriver();
      DEVMODE *dm_ptr = 0;
      DEVMODE *drv_data = (DEVMODE*)driver.getData();
      int drv_data_len = driver.getDataLen();

      PRINTDLG pd;
      ZeroMemory(&pd, sizeof(PRINTDLG));
      pd.lStructSize = sizeof(PRINTDLG);
      pd.hwndOwner   = (HWND)ccwWindow::__getHandle(parent);
      pd.hDevMode    = GlobalAlloc(GMEM_MOVEABLE, drv_data_len);
      pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames
      pd.Flags       = PD_NOPAGENUMS | PD_NOSELECTION;
      pd.nCopies     = 1;
      pd.nFromPage   = 0xFFFF;
      pd.nToPage     = 0xFFFF;
      pd.nMinPage    = 1;
      pd.nMaxPage    = 0xFFFF;

      if ( (dm_ptr = (DEVMODE*)GlobalLock(pd.hDevMode)) != 0 ) {
         memcpy(dm_ptr, drv_data, drv_data_len);
         GlobalUnlock(pd.hDevMode);
      }

      bool ok = false;

      if ( GetPrinterDevice(queue.getName(), &pd.hDevNames, 0) ) {

         ok = !!PrintDlg(&pd);

         if ( ok && (dm_ptr = (DEVMODE*)GlobalLock(pd.hDevMode)) != 0 ) {
            int new_drv_data_len = dm_ptr->dmSize + dm_ptr->dmDriverExtra;
            int idx = spooler.findQueue((const char *)dm_ptr->dmDeviceName);
            cBase::DbgInfo("Printer choosen = '%s', found int spooler at %d", dm_ptr->dmDeviceName, idx);
            if ( idx >= 0 ) {
               crPrnQueue new_queue = spooler.getQueue(idx);
               crPrnDriver new_driver(new_queue.getDriver().getName(), dm_ptr, new_drv_data_len);
               new_queue.setDefaultDriverData(new_driver);
               setAssociatedQueue(new_queue);
            } else {
               cwWindow::showError(parent, "Ausgewählter Drucker nicht in interner Druckerliste gefunden");
            }
            GlobalUnlock(pd.hDevMode);
         }

      }

      if ( pd.hDevMode != 0 )
         GlobalFree(pd.hDevMode);
      if ( pd.hDevNames != 0 )
         GlobalFree(pd.hDevNames);

      return ok;

   #endif
}
