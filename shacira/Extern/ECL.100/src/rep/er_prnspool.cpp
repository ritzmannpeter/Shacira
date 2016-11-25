// ===========================================================================
// er_prnspool.cpp                               ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--crPrnDriver           - Repraesentation treiberspezifischer Daten
//     |
//     +--crPrnQueue            - Repraesentation einer Drucker-Queue
//     |
//     +--crPrnSpooler          - Verwaltungsinstanz fuer Objekte der
//                                Klasse crPrnQueue
//
// ===========================================================================

#include "rep/er_prnspool.hpp"

#if defined(__ECL_OS2__)
   #define INCL_PM
   #define INCL_NLS
   #define INCL_SPL
   #define INCL_SPLDOSPRINT
   #define INCL_SPLERRORS
   #define INCL_BASE
   #include <os2.h>
#else
   #include "win/system/mfc/mfc_c.hpp"
   #include "win/system/mfc/stdafx.h"
   #include "rep/system/w32/w32_defprn.hpp"
   #include <winspool.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"

class cwWindow;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnDriver
// ---------------------------------------------------------------------------
//
// Repraesentation treiberspezifischer Daten. Achtung: Objekte dieser Klasse
// versuchen, unnoetige Allokation und kopieren der Treiberdaten durch einen
// Referenzzaehler zu vermeiden.
//
//  cBase
//   +--crPrnDriver
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnDriver : public cBase {

public:
   crPrnDriver();
   crPrnDriver(const char *name, void *data, int len);
   crPrnDriver(const crPrnDriver& other);
   ~crPrnDriver();

   // Zuweisungsoperator
   crPrnDriver& operator=(const crPrnDriver& other);

   // Treiber-Name und Version
   const cString& getName() const
      { return name; }
   long getVersion() const;

   // Erfragen der Treiber-Daten
   void *getData() const
      { return data->d; }
   long getDataLen() const
      { return data->size; }

private:
   cString name;
   struct DATA {
      int size;   // Allokierte Groesse
      int refc;   // Referenzzaehler
      char d[1];  // Groesse dynamisch
   } *data;

   DATA *alloc(int len);
   void dealloc(DATA *& data);

};

#endif /*__INTERFACE__*/


// Implementierung crPrnDriver
// ===========================================================================

crPrnDriver::crPrnDriver()
{
   alloc(0);
}

crPrnDriver::crPrnDriver(const char *name, void *data, int len)
{
   crPrnDriver::name = name;
   if ( alloc(len) != NULL && len > 0 )
      memcpy(crPrnDriver::data->d, data, len);
}

crPrnDriver::crPrnDriver(const crPrnDriver& other)
{
   name = other.name;
   data = other.data;
   if ( data )
      data->refc++;
}

crPrnDriver::~crPrnDriver()
{
   dealloc(data);
}

crPrnDriver& crPrnDriver::operator=(const crPrnDriver& other)
{
   if ( &other != this ) {
      dealloc(data);
      name = other.name;
      data = other.data;
      if ( data )
         data->refc++;
   }
   return *this;
}

crPrnDriver::DATA * crPrnDriver::alloc(int len)
{
   data = (DATA *)malloc(sizeof *data + len - 1);
   data->size = len;
   data->refc = 0;
   return data;
}

void crPrnDriver::dealloc(DATA *& data)
{
   if ( data ) {
      if ( data->refc-- == 0 )
         free(data);
      data = NULL;
   }
}

long crPrnDriver::getVersion() const
{
   if ( data ) {
      #if defined(__ECL_OS2__)
         const DRIVDATA *dd = (const DRIVDATA *)data->d;
         return dd->lVersion;
      #else
         const DEVMODE *dm = (const DEVMODE*)data->d;
         return dm->dmSpecVersion;
      #endif
   }

   return -1;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnQueue
// ---------------------------------------------------------------------------
//
// Repraesentation einer Drucker-Queue. Kann nur durch Befragen des Betriebs-
// systems ueber ein crPrnSpooler-Objekt entstehen. Ein crPrnQueue-Objekt ist
// ohne das zugehoerige crPrnSpooler-Objekt nicht lebensfaehig!
//
//  cBase
//   +--crPrnQueue
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnQueue : public cBase {
   friend class crPrnSpooler;

private:
   crPrnQueue(void *queue_info)
      { crPrnQueue::queue_info = queue_info; }

public:
   crPrnQueue()
      { queue_info = NULL; }

   // Zugeordneter Druckertreiber
   crPrnDriver getDriver() const;

   // Default-Daten fuer Druckertreiber ueberschreiben
   bool setDefaultDriverData(crPrnDriver other_driver);

   // Einstellungen vom Benutzer anfordern
   bool queryJobProperties(bool show_dialog = true, cwWindow *parent = 0);

   // Informationen ueber die Queue
   cString getName() const;
   cString getFormName() const;
   cString getComment() const;
   cString getLocation() const;
   cString getPortName() const;
   cString getProcessor() const;
   cString getParams() const;

   // Pruefen auf initialisierte Queue
   bool isInitialized() const
      { return queue_info != 0; }

   // Ist dies die Default-Queue?
   bool isDefault() const;

private:
   void *queue_info;

};

#endif /*__INTERFACE__*/


// Implementierung crPrnQueue
// ===========================================================================

crPrnDriver crPrnQueue::getDriver() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         const PRQINFO3 *qi = (const PRQINFO3 *)queue_info;
         return crPrnDriver(qi->pszDriverName, qi->pDriverData, qi->pDriverData->cb);
      #else
         PRINTER_INFO_2 *pi = (PRINTER_INFO_2 *)queue_info;
         DEVMODE *dm = pi->pDevMode;
         return dm != 0 ?
            crPrnDriver(pi->pDriverName, dm, dm->dmSize + dm->dmDriverExtra)
          : crPrnDriver(pi->pDriverName, 0, 0);
      #endif
   }

   return crPrnDriver(0, 0, 0);
}

bool crPrnQueue::setDefaultDriverData(crPrnDriver other_driver)
{
   if ( queue_info && other_driver.getDataLen() > 0 ) {
      #if defined(__ECL_OS2__)
         // Datenlaenge, Treibername und Treiberversion muss identisch sein!
         // Unter OS/2 werden die Default-Daten aus 'other_driver' einfach in
         // den Original-Datenbereich kopiert. Das ist aus einem IBM-Beispiel-
         // programm uebernommen!
         PRQINFO3 *qi = (PRQINFO3 *)queue_info;
         if ( qi->pDriverData->cb == other_driver.getDataLen()
           && qi->pDriverData->lVersion == other_driver.getVersion()
           && strcmp(qi->pszDriverName, other_driver.getName()) == 0 )
         {
            memcpy(qi->pDriverData, other_driver.getData(), other_driver.getDataLen());
            return true;
         }
         return false;
      #else
         // Datenlaenge, Treibername und Treiberversion muss identisch sein!
         // Unter Win32 werden die Default-Daten aus 'other_driver' einfach in
         // den Original-Datenbereich kopiert. Das geht hier hoffentlich genauso
         // wie unter OS/2.
         PRINTER_INFO_2 *pi = (PRINTER_INFO_2 *)queue_info;
         DEVMODE *dm = pi->pDevMode;
         if ( dm != 0
           && dm->dmSize + dm->dmDriverExtra == other_driver.getDataLen()
           && dm->dmSpecVersion == other_driver.getVersion()
           && strcmp(pi->pDriverName, other_driver.getName()) == 0 )
         {
            memcpy(pi->pDevMode, other_driver.getData(), other_driver.getDataLen());
            return true;
         }
         return false;
      #endif
   }

   return true;
}

bool crPrnQueue::queryJobProperties(bool show_dialog, cwWindow *parent)
{
   #if defined(__ECL_OS2__)

      char driver_name[128], device_name[128];
      PRQINFO3 *qi = (PRQINFO3 *)queue_info;

      // The pszDriverName is of the form DRIVER.DEVICE (e.g.,
      // LASERJET.HP LaserJet IID) so we need to separate it
      // at the dot
      int i = strcspn(qi->pszDriverName, ".");
      if ( i ) {
         strncpy(driver_name, qi->pszDriverName, i);
         driver_name[i] = '\0';
         strcpy(device_name, &qi->pszDriverName[i + 1]);
      } else {
         strcpy(driver_name, qi->pszDriverName);
         *device_name = '\0';
      }

      // Zweiten und weitere zugeordnete Drucker ignorieren
      char *comma = strchr(qi->pszPrinters, ',');
      if ( comma )
         *comma = '\0';

      long size = DevPostDeviceModes(cwWindow::GetGlobalHAB(),
            NULL, driver_name, device_name,
            qi->pszPrinters, DPDM_QUERYJOBPROP);

      if ( size != qi->pDriverData->cb ) {
         DbgError("Size of printer data different (was %d, should be %d)", qi->pDriverData->cb, size);
         DosAllocMem((PPVOID)&qi->pDriverData, size, fALLOC);
      }

      // Job properties anfordern
      return DEV_OK ==
         DevPostDeviceModes(cwWindow::GetGlobalHAB(),
            qi->pDriverData, driver_name, device_name,
            qi->pszPrinters, show_dialog ? DPDM_POSTJOBPROP : DPDM_QUERYJOBPROP);

   #else

      void *dm_ptr = 0;
      crPrnDriver driver = getDriver();
      void *drv_data = driver.getData();
      int drv_data_len = driver.getDataLen();

      PRINTDLG pd;
      ZeroMemory(&pd, sizeof(PRINTDLG));
      pd.lStructSize = sizeof(PRINTDLG);
      pd.hwndOwner   = (HWND)ccwWindow::__getHandle(parent);
      pd.hDevMode    = GlobalAlloc(GMEM_MOVEABLE, drv_data_len);
      pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames
      pd.Flags       = show_dialog ? PD_PRINTSETUP : PD_RETURNDEFAULT;
      pd.nCopies     = 1;
      pd.nFromPage   = 0xFFFF;
      pd.nToPage     = 0xFFFF;
      pd.nMinPage    = 1;
      pd.nMaxPage    = 0xFFFF;

      if ( drv_data_len > 0 && (dm_ptr = GlobalLock(pd.hDevMode)) != 0 ) {
         memcpy(dm_ptr, drv_data, drv_data_len);
         GlobalUnlock(pd.hDevMode);
      }

      bool ok = !!PrintDlg(&pd);

      if ( ok && drv_data_len > 0 && (dm_ptr = GlobalLock(pd.hDevMode)) != 0 ) {
         memcpy(drv_data, dm_ptr, drv_data_len);
         GlobalUnlock(pd.hDevMode);
      }

      if ( pd.hDevMode != 0 )
         GlobalFree(pd.hDevMode);
      if ( pd.hDevNames != 0 )
         GlobalFree(pd.hDevNames);

      return ok;

   #endif
}

cString crPrnQueue::getName() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         return ((PPRQINFO3)queue_info)->pszName;
      #else
         return ((PRINTER_INFO_2*)queue_info)->pPrinterName;
      #endif
   }

   return 0;
}

cString crPrnQueue::getFormName() const
{
   if ( queue_info ) {
      #if defined __ECL_W32__
         PRINTER_INFO_2 *pi = (PRINTER_INFO_2 *)queue_info;
         DEVMODE *dm = pi->pDevMode;
         if ( dm && (dm->dmFields & DM_FORMNAME) )
            return (const char *)dm->dmFormName;
      #endif
   }

   return 0;
}

cString crPrnQueue::getComment() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         return ((PPRQINFO3)queue_info)->pszComment;
      #else
         return ((PRINTER_INFO_2*)queue_info)->pComment;
      #endif
   }

   return 0;
}

cString crPrnQueue::getLocation() const
{
   if ( queue_info ) {
      #if defined __ECL_W32__
         cString location = ((PRINTER_INFO_2*)queue_info)->pLocation;
         return location.isEmpty() ?
            cString(((PRINTER_INFO_2*)queue_info)->pPortName)
          : location;
      #endif
   }

   return 0;
}

cString crPrnQueue::getPortName() const
{
   if ( queue_info ) {
      #if defined __ECL_W32__
         return ((PRINTER_INFO_2*)queue_info)->pPortName;
      #endif
   }

   return 0;
}

cString crPrnQueue::getProcessor() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         return ((PPRQINFO3)queue_info)->pszPrProc;
      #else
         return ((PRINTER_INFO_2*)queue_info)->pPrintProcessor;
      #endif
   }

   return 0;
}

cString crPrnQueue::getParams() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         return ((PPRQINFO3)queue_info)->pszParms;
      #else
         return ((PRINTER_INFO_2*)queue_info)->pParameters;
      #endif
   }

   return 0;
}

bool crPrnQueue::isDefault() const
{
   if ( queue_info ) {
      #if defined(__ECL_OS2__)
         return ((PPRQINFO3)queue_info)->fsType & PRQ3_TYPE_APPDEFAULT;
      #else
         PRINTER_INFO_2 *pi = (PRINTER_INFO_2 *)queue_info;
         if ( pi->Attributes & PRINTER_ATTRIBUTE_DEFAULT ) {
            return true; // Default printer for Win95
         } else {
            char def_printer[128];
            DWORD size = sizeof def_printer;
            return
               ::DPGetDefaultPrinter(def_printer, &size)
            && strcmp(def_printer, pi->pPrinterName) == 0;
         }
      #endif
   }

   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnSpooler
// ---------------------------------------------------------------------------
//
// Verwaltungsinstanz fuer Objekte der Klasse crPrnQueue.
//
//  cBase
//   +--crPrnSpooler
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnSpooler : public cBase {

public:
   crPrnSpooler();
   ~crPrnSpooler();

   // Erfragen der Anzahl vorhandener Queues
   int getQueueCount() const
      { return queue_count; }

   // Queue mit bestimmtem Namen suchen
   int findQueue(const char *queue_name) const;
   // Queue ueber Index erfragen
   crPrnQueue getQueue(int queue_no) const;
   // Standard-Queue ermitteln
   crPrnQueue getDefaultQueue() const;

private:
   int queue_count;
   void *queue_info;

};

#endif /*__INTERFACE__*/


// Implementierung crPrnSpooler
// ===========================================================================

crPrnSpooler::crPrnSpooler()
{
   queue_info = NULL;
   queue_count = 0;

   #if defined(__ECL_OS2__)

      ULONG queues_returned, total_queues, bytes_needed;

      // Anzahl der Queues im System erfragen
      SplEnumQueue(NULL, 3, NULL, 0L, &queues_returned,
         &total_queues, &bytes_needed, NULL);
      if ( total_queues != 0 && bytes_needed != 0 ) {
         // Einlesen aller Queuedefinitionen
         if ( (queue_info = malloc(bytes_needed)) == NULL )
            DbgError("could not allocate %d bytes for queue_info", bytes_needed);
         SplEnumQueue(NULL, 3, queue_info, bytes_needed, &queues_returned,
            &total_queues, &bytes_needed, NULL);
      }

      queue_count = queues_returned;

   #else

      DWORD total_queues, bytes_needed;
      DWORD flags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS;

      // Anzahl der Drucker(-queues) im System erfragen
      ::EnumPrinters(flags, NULL, 2, NULL, 0,
         &bytes_needed, &total_queues);
      if ( bytes_needed != 0 ) {
         // Einlesen aller Drucker(-queue)definitionen
         if ( (queue_info = malloc(bytes_needed)) == 0 )
            DbgError("could not allocate %d bytes for queue_info", bytes_needed);
         ::EnumPrinters(flags, NULL, 2, (BYTE*)queue_info,
            bytes_needed, &bytes_needed, &total_queues);
      }

      queue_count = total_queues;

      #define __Debug_Spooler_Init__
      #ifdef __Debug_Spooler_Init__
         for ( int i = 0 ; i < queue_count ; i++ ) {
            crPrnQueue queue = getQueue(i);
            DbgOut(0, "Spooler: [%c] Queue %d: name='%s', form='%s'",
               queue.isDefault() ? 'X' : ' ', i,
               (const char *)queue.getName(), (const char *)queue.getFormName());
         }
      #endif

   #endif
}

crPrnSpooler::~crPrnSpooler()
{
   if ( queue_info )
      free(queue_info);
}

int crPrnSpooler::findQueue(const char *queue_name) const
{
   if ( !queue_name )
      return -1;

   #if defined(__ECL_OS2__)
      const PRQINFO3 *qi = (const PRQINFO3 *)queue_info;
      for ( int i = 0 ; i < queue_count ; i++ ) {
         if ( qi[i].pszName && !strcmp(queue_name, qi[i].pszName) )
            return i;
      }
   #else
      PRINTER_INFO_2 *pi = (PRINTER_INFO_2*)queue_info;
      for ( int i=0 ; i<queue_count ; i++ ) {
         if ( pi[i].pPrinterName && !strcmp(queue_name, pi[i].pPrinterName) )
            return i;
      }
   #endif

   return -1;
}

crPrnQueue crPrnSpooler::getQueue(int queue_no) const
{
   if ( queue_no >= 0 && queue_no < queue_count ) {
      #if defined(__ECL_OS2__)
         const PRQINFO3 *qi = (const PRQINFO3 *)queue_info;
         return crPrnQueue((void *)&qi[queue_no]);
      #else
         PRINTER_INFO_2 *pi = (PRINTER_INFO_2 *)queue_info;
         return crPrnQueue((void *)&pi[queue_no]);
      #endif
   }

   // Bei fehlerhaftem Wert fuer 'queue_no': Erste Queue zurueckliefern
   return crPrnQueue(queue_info);
}

crPrnQueue crPrnSpooler::getDefaultQueue() const
{
   for ( int i = 0 ; i < queue_count ; i++ ) {
      if ( getQueue(i).isDefault() )
         return getQueue(i);
   }

   // Falls keine Default-Queue definiert: Erste Queue zurueckliefern
   return getQueue(0);
}


