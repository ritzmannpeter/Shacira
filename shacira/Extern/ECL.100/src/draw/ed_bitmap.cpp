// ===========================================================================
// ed_bitmap.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur VerfÅgung:
//
//    cBase
//     |
//     +--cdDevice
//     |   |
//     |   +--cdRetainedDevice
//     |       |
//     |       +--cdBmpDevice    - Speichergeraet fuer Zeichenoperationen
//     |                           in Bitmaps
//     |
//     +--cdSpace
//     |   |
//     |   +--cdBmpSpace         - Anzeigebereich in Bitmaps
//     |
//     +--cdBitmap               - Basisklasse fuer Bitmaps
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>
#include <stdarg.h>
#include <math.h>

#include "base/eb_file.hpp"
#include "draw/ed_bitmap.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_GPI
   #include <os2.h> /* OS/2 include file      */
#else
   #error "Unsupported target for ECL module ed_device"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_geo2d.hpp"
#include "draw/ed_space.hpp"

#endif /*__INTERFACE__*/




// Lokale Funktionen
// ===========================================================================

#if defined(__OS2__)

   #define METRIC PU_LOMETRIC /*PU_HIMETRIC*/

   #if METRIC == PU_HIMETRIC
      #define METRIC_UNIT 100.0
   #elif METRIC == PU_LOMETRIC
      #define METRIC_UNIT 10.0
   #endif

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdBmpDevice
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdDevice
//       +--cdRetainedDevice
//           +--cdBmpDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdBmpDevice : public cdRetainedDevice {

public:
   cdBmpDevice(int width, int height, int bpp = 1);
   ~cdBmpDevice();

   void setView(long sx, long sy, double scale);
   void paintAt(cdStorage *elems, long sx, long sy);

   // Save the bitmap in Windows DIB format
   void saveAsDIB(cString filename) const;

   // Breite der Bitmap in Pels erfragen
   int getWidth() const
      { return width; }
   // Hoehe der Bitmap in Pels erfragen
   int getHeight() const
      { return height; }
   // Anzahl Bits pro Pel erfragen
   int getBpp() const
      { return bpp; }

   // Groesse einer Scanline in Bytes erfragen
   long getLineSize() const;
   // Groesse der Bitmap (Nutzdaten) in Bytes erfragen
   long getSize() const;

private:
   int width, height, bpp;
   long start_x, start_y;
   double scale;

   #if defined __OS2__
      unsigned long hbm;         // Momentan selektiertes Bitmap
      unsigned long hbm_prev;    // Vorher selektiertes Bitmap
   #endif

};

#endif /*__INTERFACE__*/


// Implementierung cdBmpDevice
// ===========================================================================

cdBmpDevice::cdBmpDevice(int width, int height, int bpp)
{
   cdBmpDevice::width = width;
   cdBmpDevice::height = height;
   cdBmpDevice::bpp = bpp;

   setView(0, 0, 1.0);

   #if defined(__OS2__)
      // Setup HDC with 0.01 mm units
      SIZEL pagesize = { 0, 0 };
      DEVOPENSTRUC dop = { NULL, "MEMORY", NULL, NULL, NULL };
      ULONG psflags = GPIA_ASSOC | METRIC | GPIT_NORMAL | GPIF_LONG;
      hdc = DevOpenDC(hab, OD_MEMORY, "*", 5L, (PDEVOPENDATA)&dop, NULLHANDLE);
      if ( hdc == NULLHANDLE )
         DbgError("WinOpenWindowDC failed");
      if ( (hps = GpiCreatePS(hab, hdc, &pagesize, psflags)) == NULLHANDLE )
         DbgError("GpiCreatePS failed");

      // Create bitmap and setup with HPS
      BITMAPINFOHEADER bmph = { sizeof(BITMAPINFOHEADER), width, height, 1, bpp };
      if ( (hbm = GpiCreateBitmap(hps, (PBITMAPINFOHEADER2)&bmph, 0, NULL, NULL)) == 0 )
         DbgError("GpiCreateBitmap failed");
      hbm_prev = GpiSetBitmap(hps, hbm);
   #else
      // ...
   #endif

   reset();
}

cdBmpDevice::~cdBmpDevice()
{
   #if defined(__OS2__)
      GpiSetBitmap(hps, hbm_prev);
      if ( !GpiDeleteBitmap(hbm) )
         DbgError("GpiDeleteBitmap failed");
      if ( !GpiAssociate(hps, NULLHANDLE) )
         DbgError("GpiAssociate failed");
      if ( !GpiDestroyPS(hps) )
         DbgError("GpiDestroyPS failed");
      if ( DevCloseDC(hdc) != DEV_OK )
         DbgError("DevCloseDC failed");
   #else
      // ...
   #endif
}

long cdBmpDevice::getLineSize() const
{
   // Funktion evtl. systemabhaengig!
   return 4 * (bpp * width + 31) / 32;
}

long cdBmpDevice::getSize() const
{
   // Funktion evtl. systemabhaengig!
   return getLineSize() * height;
}

void cdBmpDevice::setView(long sx, long sy, double scale)
{
   start_x = sx; start_y = sy;
   cdBmpDevice::scale = scale;
}

void cdBmpDevice::paintAt(cdStorage *elems, long sx, long sy)
{
   #if defined(__OS2__)
      MATRIXLF tmat;
      FIXED fscale = MAKEFIXED(int(scale), long((scale - floor(scale)) * 65536.0));

      tmat.fxM11 = fscale;         tmat.fxM12 = MAKEFIXED(0,0); tmat.lM13  = 0;
      tmat.fxM21 = MAKEFIXED(0,0); tmat.fxM22 = fscale;         tmat.lM23  = 0;
      tmat.lM31  = -start_x;       tmat.lM32  = -start_y;       tmat.lM33  = 1;

      GpiErase(hps);
      GpiSetDefaultViewMatrix(hps, 9, &tmat, TRANSFORM_REPLACE);
   #else
      // ...
   #endif

   cdRetainedDevice::paintAt(elems, sx, sy);
}

void cdBmpDevice::saveAsDIB(cString filename) const
{
   #ifdef __OS2__

      RGB bmcol[2] = { {0,0,0}, {255,255,255} };

      BITMAPFILEHEADER bmfh;
      bmfh.usType = 0x4d42; // "BM"
      bmfh.cbSize = sizeof(BITMAPFILEHEADER);
      bmfh.xHotspot = bmfh.yHotspot = 0;
      bmfh.offBits = sizeof(BITMAPFILEHEADER) + sizeof bmcol;
      bmfh.bmp.cbFix = sizeof(BITMAPINFOHEADER);

      BITMAPINFO2 bmi2;
      bmi2.cbFix = 16L;
      bmi2.cPlanes = 1;
      bmi2.cBitCount = bpp;
      char *pbuf = new char[getSize()];

      if ( GpiQueryBitmapBits(hps, 0, height, pbuf, &bmi2) != height ) {
         DbgError("GpiQueryBitmapBits failed");
         //return;
      }

      bmfh.bmp.cx = bmi2.cx;
      bmfh.bmp.cy = bmi2.cy;
      bmfh.bmp.cPlanes = bmi2.cPlanes;
      bmfh.bmp.cBitCount = bmi2.cBitCount;

      cFile file(filename, "w+b");
      file.Write(&bmfh, sizeof bmfh, 1);
      file.Write(bmcol, sizeof bmcol, 1);
      file.Write(pbuf, getSize(), 1);

      delete[] pbuf;

   #else

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdBmpSpace
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdSpace
//       +--cdBmpSpace
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdBmpSpace : public cdSpace {

public:
   cdBmpSpace(cdBmpDevice *dev);
   ~cdBmpSpace();

   void beginDrawing();
   void endDrawing();

   void paintAsync();

   void setViewport(const cdViewport& viewport);
   const cdViewport& getViewport() const
      { return viewport; }

   int convUnit2Pel(double unit) const;
   double convPel2Unit(int pel) const;

   // Konvertiere mm in Weltkoordinaten und zurueck
   long mm2w(double mm) const;
   double w2mm(long w) const;

private:
   cdViewport viewport;   // Aktueller Viewport
   cdBmpDevice *bmp_dev;   // Zugeordnetes Windows-Device
   cdStorage *elems;   // Zuletzt gemalte Elemente

};

#endif /*__INTERFACE__*/


// Implementierung cdBmpSpace
// ===========================================================================

cdBmpSpace::cdBmpSpace(cdBmpDevice *dev) :
   cdSpace(dev)
{
   cdBmpSpace::bmp_dev = dev;
   elems = NULL;
   setViewport(viewport);
}

cdBmpSpace::~cdBmpSpace()
{
   delete elems;
}

void cdBmpSpace::beginDrawing()
{
   cdSpace::beginDrawing();
   bmp_dev->beginDrawing();
   delete elems; elems = NULL;
}

void cdBmpSpace::endDrawing()
{
   elems = bmp_dev->endDrawing();
   cdSpace::endDrawing();
}

void cdBmpSpace::paintAsync()
{
   bmp_dev->paintAt(elems, 0, 0);
}

void cdBmpSpace::setViewport(const cdViewport& viewport)
{
   cdBmpSpace::viewport = viewport;

   double scale = viewport.scale;
   long start_x = mm2w(viewport.start.x * scale);
   long start_y = mm2w(viewport.start.y * scale);

   bmp_dev->setView(start_x, start_y, scale);
}

int cdBmpSpace::convUnit2Pel(double unit) const
{
   return bmp_dev->convWorld2Pel(mm2w(unit * viewport.scale));
}

double cdBmpSpace::convPel2Unit(int pel) const
{
   return w2mm(double(bmp_dev->convPel2World(pel)) / viewport.scale);
}

long cdBmpSpace::mm2w(double mm) const
{
   return (long)(mm * METRIC_UNIT /*+0.5*/);
}

double cdBmpSpace::w2mm(long w) const
{
   return (double)w / METRIC_UNIT;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdBitmap
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdBitmap
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdBitmap : public cBase {

public:
   cdBitmap(int width, int height);

   // Viewport so einrichten, dass 'box' vollstaendig dargestellt wird;
   // Zwangsrahmen mit 'pixborder' Pixeln beruecksichtigen
   void zoom(const c2dBox& box, int pixborder = 10);

   // Zeichenbereich in Weltkoordinaten (mm) ermitteln
   c2dBox getDrawingArea() const;
   // Groesse des Zeichenbereiches in Weltkoordinaten (mm) ermitteln
   c2dSize getDrawingAreaSize() const;

protected:
   cdBmpDevice device;
   cdBmpSpace space;
   cdViewport vport;

};

#endif /*__INTERFACE__*/


// Implementierung cdBitmap
// ===========================================================================

cdBitmap::cdBitmap(int width, int height) :
   device(width, height), space(&device)
{
}

static double CalcScale(const c2dSize& disp_size, const c2dSize& box_size)
{
   double scale_x = box_size.cx > 0.0 ? disp_size.cx / box_size.cx : 1.0;
   double scale_y = box_size.cy > 0.0 ? disp_size.cy / box_size.cy : 1.0;
   double scale = min(scale_x, scale_y);
   return is_zero(scale) ? 1.0 : scale;
}

void cdBitmap::zoom(const c2dBox& box, int pixborder)
{
   vport.scale = 1.0; // Erstmal klare Verhaeltnisse schaffen...
   space.setViewport(vport);

   // Staerke des Zwangsrahmens in 1:1.0-Skalierung berechnen
   double border_size = space.convPel2Unit(pixborder);
   // Groesse des Fensters in Weltkoordinaten
   c2dSize display = getDrawingAreaSize() - 2 * c2dSize(border_size, border_size);
   // Skalierung berechnen
   double scale = CalcScale(display, box.getSize());
   // Distanz vom Display-Startpunkt zum 'box'-Startpunkt in Weltkoordinaten
   c2dVector start_rel = (display / scale - box.getSize()) / 2.0;
   // Absoluter Display-Startpunkt in Weltkoordinaten
   c2dPoint start_abs = box.lb - start_rel;

   // Skalierung einschalten, damit Zwangsrahmen berechnet werden kann
   vport.scale = scale;
   space.setViewport(vport);

   // Staerke des Zwangsrahmens in neuer Skalierung berechnen
   border_size = space.convPel2Unit(pixborder);

   // Skalierung einschalten (Zwangsrahmen beruecksichtigen!)
   vport.start = start_abs - c2dVector(border_size, border_size);
   space.setViewport(vport);
}

c2dBox cdBitmap::getDrawingArea() const
{
   return c2dBox(c2dPoint(0,0), getDrawingAreaSize());
}

c2dSize cdBitmap::getDrawingAreaSize() const
{
   return c2dSize(space.convPel2Unit(device.getWidth()), space.convPel2Unit(device.getHeight()));
}



