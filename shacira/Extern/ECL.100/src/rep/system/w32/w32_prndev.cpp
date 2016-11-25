/* refer to KB:Q166129 */

#include <windows.h>
#include <winspool.h>
#include "rep/system/w32/w32_prndev.hpp"
#include "base/eb_base.hpp"

#define GLOBAL /* for use with MAKEHEAD */

// returns a DEVMODE and DEVNAMES for the printer name specified
GLOBAL BOOL GetPrinterDevice(LPCTSTR pszPrinterName, HGLOBAL* phDevNames, HGLOBAL* phDevMode)
{
   // if NULL is passed, then assume we are setting app object's
   // devmode and devnames
   if (phDevMode == NULL && phDevNames == NULL)
      return TRUE;

   // Open printer
   HANDLE hPrinter;
   if (OpenPrinter((char*)pszPrinterName, &hPrinter, NULL) == FALSE)
      return FALSE;

   // obtain PRINTER_INFO_2 structure and close printer
   DWORD dwBytesReturned, dwBytesNeeded;
   GetPrinter(hPrinter, 2, NULL, 0, &dwBytesNeeded);
   PRINTER_INFO_2* p2 = (PRINTER_INFO_2*)GlobalAlloc(GPTR,
                                                     dwBytesNeeded);
   if (GetPrinter(hPrinter, 2, (LPBYTE)p2, dwBytesNeeded,
                  &dwBytesReturned) == 0) {
      GlobalFree(p2);
      ClosePrinter(hPrinter);
      return FALSE;
   }
   ClosePrinter(hPrinter);

   HGLOBAL hDevMode = NULL;
   if (phDevMode != NULL) {
      // Allocate a global handle for DEVMODE
      hDevMode = GlobalAlloc(GHND, sizeof(*p2->pDevMode) +
                                   p2->pDevMode->dmDriverExtra);
      __ECL_ASSERT1__(hDevMode);
      DEVMODE* pDevMode = (DEVMODE*)GlobalLock(hDevMode);
      __ECL_ASSERT1__(pDevMode);

      // copy DEVMODE data from PRINTER_INFO_2::pDevMode
      memcpy(pDevMode, p2->pDevMode, sizeof(*p2->pDevMode) +
             p2->pDevMode->dmDriverExtra);
      GlobalUnlock(hDevMode);
   }

   HGLOBAL hDevNames = NULL;
   if (phDevNames != NULL) {
      // Compute size of DEVNAMES structure from PRINTER_INFO_2's data
      DWORD drvNameLen = lstrlen(p2->pDriverName)+1;  // driver name
      DWORD ptrNameLen = lstrlen(p2->pPrinterName)+1; // printer name
      DWORD porNameLen = lstrlen(p2->pPortName)+1;    // port name

      // Allocate a global handle big enough to hold DEVNAMES.
      hDevNames = GlobalAlloc(GHND, sizeof(DEVNAMES) +
                                    (drvNameLen + ptrNameLen + porNameLen)*sizeof(TCHAR));
      __ECL_ASSERT1__(hDevNames);
      DEVNAMES* pDevNames = (DEVNAMES*)GlobalLock(hDevNames);
      __ECL_ASSERT1__(pDevNames);

      // Copy the DEVNAMES information from PRINTER_INFO_2
      // tcOffset = TCHAR Offset into structure
      int tcOffset = sizeof(DEVNAMES)/sizeof(TCHAR);
      __ECL_ASSERT1__(sizeof(DEVNAMES) == tcOffset*sizeof(TCHAR));

      pDevNames->wDriverOffset = (unsigned short)tcOffset;
      memcpy((LPTSTR)pDevNames + tcOffset, p2->pDriverName,
             drvNameLen*sizeof(TCHAR));
      tcOffset += drvNameLen;

      pDevNames->wDeviceOffset = (unsigned short)tcOffset;
      memcpy((LPTSTR)pDevNames + tcOffset, p2->pPrinterName,
             ptrNameLen*sizeof(TCHAR));
      tcOffset += ptrNameLen;

      pDevNames->wOutputOffset = (unsigned short)tcOffset;
      memcpy((LPTSTR)pDevNames + tcOffset, p2->pPortName,
             porNameLen*sizeof(TCHAR));
      pDevNames->wDefault = 0;

      GlobalUnlock(hDevNames);
   }

   GlobalFree(p2);   // free PRINTER_INFO_2

   // set the new hDevMode and hDevNames
   if (phDevMode != NULL)
      *phDevMode = hDevMode;
   if (phDevNames != NULL)
      *phDevNames = hDevNames;
   return TRUE;
}


