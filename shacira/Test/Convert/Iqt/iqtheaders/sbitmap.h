/***************************************************************************
*
*  SBITMAP.H
*
*  Enthaelt die Strukturen, die notwendig sind, um ein Windows Bitmap zu
*  erstellen und zu verwalten. Unter Windows selbst ist dieses Includefile
*  leer, da alle Strukturen von Windows zur Verfuegung gestellt werden.
*  Fuer die anderen Betriebssysteme werden die Windowsstrukturen hierher
*  kopiert.
*
*  HISTORY:
*     14.08.2002  -TSchw-  Strukturen gepackt, sonst stimmt das Fileformat nicht.
*
***************************************************************************/


#ifndef __sbitmap__
#define __sbitmap__

#include <target.h>

#ifdef __WIN32__

#include <windows.h>
#include <winbase.h>

#else // Not __WIND32__

typedef ULONG DWORD;
typedef ULONG COLORREF;

#define RGB(r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

#define GetRValue(rgb)  ((BYTE)(rgb))
#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)  ((BYTE)((rgb) >> 16))

#include <packstart.h>
typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
} STRUCT_PACKED RGBQUAD;
#include <packstop.h>

#include <packstart.h>
typedef struct tagBITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
} STRUCT_PACKED BITMAPFILEHEADER;
#include <packstop.h>

#include <packstart.h>
typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} STRUCT_PACKED BITMAPINFOHEADER;
#include <packstop.h>

#include <packstart.h>
typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} STRUCT_PACKED BITMAPINFO;
#include <packstop.h>

/* constants for the biCompression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

#endif // Not __WIN32__


// Im ersten Wort eines Bitmapfiles (Member bfType vom BITMAPFILEHEADERS)
// steht die folgende ID, die ein File als Bitmap identifiziert.
// 0x42 = 'B', 0x4d = 'M'
#define BITMAP_FILETYPE_ID 0x4d42

GLOBAL COLORREF GetColorRef (int col); // Defined in win32s.c


#endif /* __sbitmap__ */

