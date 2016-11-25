// ===========================================================================
// er_prndraw.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdDevice
//     |   |
//     |   +--cdRetainedDevice
//     |       |
//     |       +--crPrnDevice          -
//     |
//     +--cdSpace
//         |
//         +--crPrnSpace               -
//
//    cEloBase
//     |
//     +--cEloElement
//         |
//         +--cEloDocument             -
//             |
//             +--crPrnDocument        -
//
// ===========================================================================

#include "rep/er_prndraw.hpp"
#include "base/eb_err.hpp"

#if defined(__ECL_OS2__)
   #define INCL_PM
   #define INCL_NLS
   #define INCL_SPL
   #define INCL_SPLDOSPRINT
   #define INCL_SPLERRORS
   #define INCL_BASE
   #include <os2.h>
#else
   #include "win/system/mfc/stdafx.h"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_docview.hpp"
#include "draw/ed_space.hpp"
#include "rep/er_printer.hpp"

#endif /*__INTERFACE__*/




// Lokale Funktionen
// ===========================================================================

#define METRIC cdDevice::mmLoMetric /*cdDevice::mmLoMetric*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnDevice
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdDevice
//       +--crPrnDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnDevice : public cdDevice {

public:

   // Konstruktor
   inline crPrnDevice() { }
   // Destruktor
   ~crPrnDevice();

   // Queuezuordnung durchfuehren
   void associateQueue(const crPrnQueue& new_queue);
   // Zugeordnete Queue erfragen
   crPrnQueue getAssociatedQueue() const
      { return queue; }

   // Drucker-Device oeffnen
   void openDevice(cString title, int copies);
   // Drucker-Device schliessen
   void closeDevice();

private:

   crPrnQueue queue;

};

#endif /*__INTERFACE__*/


// Implementierung crPrnDevice
// ===========================================================================

crPrnDevice::~crPrnDevice()
{
   closeDevice();
}

void crPrnDevice::associateQueue(const crPrnQueue& new_queue)
{
   queue = new_queue;
}

void crPrnDevice::openDevice(cString title, int copies)
{
   crPrnDriver driver = queue.getDriver();

   if ( driver.getDataLen() > 0 && queue.isInitialized() ) {

      closeDevice();

      #if defined(__ECL_OS2__)

         char driver_name[128];
         strxcpy(driver_name, driver.getName(), sizeof driver_name);
         char *dotp = strchr(driver_name, '.');
         if (dotp) *dotp = '\0';

         char queue_name[128];
         strxcpy(queue_name, queue.getName(), sizeof queue_name);

         char queue_proc_params[16];
         sprintf(queue_proc_params, "COP=%d", copies);

         char spooler_params[128];
         sprintf(spooler_params, "FORM=%s", (const char *)form.getName());

         // Build the device context data for DevOpenDC
         DEVOPENSTRUC dos;
         memset(&dos, 0, sizeof dos);

         dos.pszLogAddress = queue_name;
         dos.pszDriverName = driver_name;
         dos.pdriv = (PDRIVDATA)driver.getData();
         dos.pszDataType = "PM_Q_STD";
         dos.pszComment = (char*)title;
         dos.pszQueueProcParams = queue_proc_params;
         dos.pszSpoolerParams = spooler_params;

         // Setup HDC with 0.01 mm units
         SIZEL pagesize = { 0, 0 };
         ULONG psflags = GPIA_ASSOC | METRIC | GPIT_NORMAL;
         HAB hab = cwWindow::GetGlobalHAB();

         if ( (hdc = DevOpenDC(hab, OD_QUEUED, "*", 7L, (PDEVOPENDATA)&dos, NULL)) == NULLHANDLE )
            DbgError("WinOpenWindowDC failed");
         if ( (hps = GpiCreatePS(hab, hdc, &pagesize, psflags)) == NULLHANDLE )
            DbgError("GpiCreatePS failed");

         MATRIXLF tmat;
         tmat.fxM11 = MAKEFIXED(1,0); tmat.fxM12 = MAKEFIXED(0,0); tmat.lM13  = 0;
         tmat.fxM21 = MAKEFIXED(0,0); tmat.fxM22 = MAKEFIXED(1,0); tmat.lM23  = 0;
         tmat.lM31  = 0;              tmat.lM32  = 0;              tmat.lM33  = 1;

         GpiSetDefaultViewMatrix(hps, 9, &tmat, TRANSFORM_REPLACE);

      #elif defined(__ECL_W32__)

         CDC *dc = new CDC;
         dc->m_bPrinting = TRUE; // Muss man wohl tatsaechlich selbst machen, oder... ?!?
         dc->CreateDC(driver.getName(), queue.getName(), 0, driver.getData());
         __setDC(dc);
         setMapMode(METRIC);
         dc->SetViewportOrg(0, dc->GetDeviceCaps(VERTRES));

      #endif

   }
}

void crPrnDevice::closeDevice()
{
   #if defined(__ECL_OS2__)
      if ( hps && !GpiAssociate(hps, NULLHANDLE) )
         DbgError("GpiAssociate failed");
      if ( hps && !GpiDestroyPS(hps) )
         DbgError("GpiDestroyPS failed");
      if ( hdc && !DevCloseDC(hdc) )
         DbgError("DevCloseDC failed");
   #elif defined(__ECL_W32__)
      CDC *dc = __getDC();
      __setDC(0);
      delete dc;
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnSpace
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdSpace
//       +--crPrnSpace
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnSpace : public cdSpace {

public:

   inline crPrnSpace(crPrnDevice *dev) : cdSpace(dev) { prn_dev = dev; }
   ~crPrnSpace();

protected:

   // Konvertiere physikalische in logische Koordinaten
   long onConvPhys2Log(double phys) const;
   // Konvertiere logische in physikalische Koordinaten
   double onConvLog2Phys(long log) const;

private:

   crPrnDevice *prn_dev;   // Zugeordnetes Printer-Device

};

#endif /*__INTERFACE__*/


// Implementierung crPrnSpace
// ===========================================================================

crPrnSpace::~crPrnSpace()
{
}

long crPrnSpace::onConvPhys2Log(double /*mm*/) const
{
   throw cErrBase(cErrBase::errSorry);
   // return (long)(mm * METRIC_UNIT /*+0.5*/);
}

double crPrnSpace::onConvLog2Phys(long /*w*/) const
{
   throw cErrBase(cErrBase::errSorry);
   // return (double)w / METRIC_UNIT;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnDocument
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloElement
//      +--crPrnDocument
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnDocument : public cEloDocument {
   ELO_DECLARE(crPrnDocument,cEloDocument)

public:

   // Konstruktor ohne Elementbeschreibung
   inline crPrnDocument(crPrinter *prn) :
      cEloDocument(getDefaultElemDescr()) { init(prn); }
   // Konstruktor ueber Elementbeschreibung (direkt)
   inline crPrnDocument(crPrinter *prn, const cEloElementDescription *elem_descr) :
      cEloDocument(elem_descr) { init(prn); }
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   inline crPrnDocument(crPrinter *prn, const cEloDescriptionManager *descr_manager, cString descr_sig) :
      cEloDocument(descr_manager, descr_sig) { init(prn); }
   // Destruktor
   virtual ~crPrnDocument();


   // Allgemeines
   // ===========

   // Zeichenbereich in physikalischen Koordinaten (mm) ermitteln
   inline c2dBox getDrawArea() const
      { return onGetDrawArea(); }
   // Zugeordnetes Device erfragen
   inline crPrnDevice *getAssociatedDevice()
      { return &device; }

   // Default-Elementbeschreibung erfragen
   static cEloElementDescription *getDefaultElemDescr();


   // Dokumentaufbereitung
   // ====================

   // Startet die Aufbereitung eines Druckdokuments
   bool start(cString doc_name, cString title, int copies = 1);
   // Beendet die Aufbereitung, beginnt den Druckvorgang und liefert job_id
   int end();
   // Bricht die Aufbereitung des Druckdokuments ab
   void abort();
   // Fuegt einen Seitenvorschub ein
   void newFrame();


   // Seitenraender und Offsets
   // =========================

   enum SETMARG {
      Absolute,      // Raender auf Absolutwert setzen (in mm)
      Relative       // Raender relativ zum Papierrand setzen (in mm)
   };

   // Setzt die Raender relativ zum Papierrand oder Absolut (in mm)
   void setMargins(double left, double right, double top, double bottom, SETMARG sm = Absolute);
   // Setzt die Offsets fuer Seite 1 relativ zum Rand (in mm)
   void setOffsets(int page, double left, double right, double top, double bottom);
   // Ermittelt die absoluten Randeinstellungen fuer Seite 'page'
   void getMargins(int page, double& left, double& right, double& top, double& bottom);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um den Zeichenbereich zu ermitteln
   virtual c2dBox onGetDrawArea() const;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return __getClassName(); }

private:

   crPrinter *prn;          // Zugeordneter Drucker
   crPrnDevice device;     // Zugeordnetes Drucker-Geraet

   double marg_left;       // Abstand linker Blattrand zum Beginn Druckbereich [mm]
   double marg_right;      // Abstand linker Blattrand zum Ende Druckbereich [mm]
   double marg_bottom;     // Abstand unterer Blattrand zum Ende Druckbereich [mm]
   double marg_top;        // Abstand unterer Blattrand zum Beginn Druckbereich [mm]
   double off1_bottom;     // Seite 1: Offset zu marg_bottom [mm relativ]
   double off1_top;        // Seite 1: Offset zu marg_top [mm relativ]

   void init(crPrinter *prn);

};

#endif /*__INTERFACE__*/


// Implementierung crPrnDocument
// ===========================================================================

void crPrnDocument::init(crPrinter *prn)
{
   crPrnDocument::prn = prn;
   crPrnDocument::device.associateQueue(prn->getAssociatedQueue());
}

crPrnDocument::~crPrnDocument()
{
   device.closeDevice();
}


// Allgemeines
// ===========

cEloElementDescription * crPrnDocument::getDefaultElemDescr()
{
   static class crPrnDocumentDescription : public cEloElementDescription {
      void onInitialize() { }
      cString onGetSignature() const { return "crPrnDocumentDescription"; }
      cString onGetName() const { return onGetSignature(); }
   } PrnDocumentDescription;

   return &PrnDocumentDescription;
}


// Dokumentaufbereitung
// ====================

bool crPrnDocument::start(cString doc_name, cString title, int copies)
{
   device.openDevice(title, copies);
   device.startDoc(doc_name);
   return true;
}

int crPrnDocument::end()
{
   int job_id = device.endDoc();
   device.closeDevice();
   return job_id;
}

void crPrnDocument::abort()
{
   device.abortDoc();
   device.closeDevice();
}


// Besondere Verarbeitung
// ======================

void crPrnDocument::newFrame()
{
   device.newFrame();
}


// Seitenraender und Offsets
// =========================

void crPrnDocument::setMargins(double left, double right, double top, double bottom, SETMARG sm)
{
   double hw_left, hw_right, hw_top, hw_bottom;
   prn->getMargins(hw_left, hw_right, hw_top, hw_bottom);

   if ( sm == Relative ) {
      double width, height;
      prn->getPaperSize(width, height);
      right = width - right;
      top = height - top;
   }

   marg_left = max(left, hw_left);
   marg_top = min(top, hw_top);
   marg_right = min(right, hw_right);
   marg_bottom = max(bottom, hw_bottom);
}

void crPrnDocument::setOffsets(int page, double, double, double top, double bottom)
{
   // Einzig moegliche Seite ist page == 0 (erste Seite)
   // Offsets links und rechts werden nicht beruecksichtigt

   if ( page == 0 ) {
      off1_top = top;
      off1_bottom = bottom;
   }
}

void crPrnDocument::getMargins(int page, double& left, double& right, double& top, double& bottom)
{
   // page == 0: Erste Seite
   // page > 0:  Alle folgenden Seiten

   left = marg_left;
   right = marg_right;
   top = marg_top;
   bottom = marg_bottom;

   if ( page == 0 ) {
      double hw_left, hw_right, hw_top, hw_bottom;
      prn->getMargins(hw_left, hw_right, hw_top, hw_bottom);
      top = min(top - off1_top, hw_top);
      bottom = max(bottom + off1_bottom, hw_bottom);
   }
}


// Hinzugefuegte Events
// ====================

c2dBox crPrnDocument::onGetDrawArea() const
{
   return c2dBox();
}


