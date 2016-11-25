// ===========================================================================
// ew_base.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cwIconList
//
// ===========================================================================

#include "win/ew_base.hpp"

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

#include "base/eb_base.hpp"
#include "base/eb_res.hpp"
#include "draw/ed_base.hpp"

#endif /*__INTERFACE__*/




// Protokolldateien
// ===========================================================================

#if defined __ECL_W32__

   class cLogFile {
      static FILE *fp;
   public:
      cLogFile()
      {
         fp = fopen("\\\\.\\pipe\\pips", "w");
         if ( fp == 0 )
            fp = stderr;
         setbuf(fp, 0);
         cBase::setPrintFunc(printf);
      }
      ~cLogFile()
      {
         fclose(fp);
      }
      static int printf(const char *fmt, ...)
      {
         int num;
         va_list ap;

         va_start(ap, fmt);
         num = vfprintf(fp, fmt, ap);
         va_end(ap);

         return num;
      }
   } ECLLogFile;

   FILE * cLogFile::fp = 0;

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwIconList
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwIconList
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwIconList : public cBase {
   friend class ccwIconList;

public:

   // Konstruktor
   inline cwIconList() { init(); }
   // Destruktor
   ~cwIconList();


   // Allgemeines
   // ===========

   // Erzeugen einer Icon-Liste aus einer Resource
   bool create(const cResource& res, int pix_width, int grow, const cdColor& mask_color);
   // Loeschen der Icon-Liste (Freigeben der Resourcen)
   void destroy();

   // Groesse der Icon-Liste einstellen
   bool setCount(int count);
   // Anzahl Icons in der Liste erfragen
   int getCount() const;

   // Hintergrundfarbe setzen
   void setBkgndColor(const cdColor& bkgnd_color);
   // Hintergrundfarbe erfragen
   cdColor getBkgndColor() const;


   // Icons hinzufuegen/loeschen
   // ==========================

   // Icon an Position 'idx' durch 'icon' ersetzen
   bool setIcon(int idx, const cIcon& icon);
   // Icons ab Position 'idx' durch 'bmp' ersetzen
   bool setIcons(int idx, const cBitmap& bmp, const cdColor& mask_color);
   // Icon an Position 'idx' extrahieren
   cIcon getIcon(int idx) const;

   // Icon hinzufuegen (rc = Iconposition oder -1 bei Fehler)
   int addIcon(const cIcon& icon);
   // Icons ueber Bitmap hinzufuegen (rc = Position erstes Icon oder -1)
   int addIcons(const cBitmap& bmp, const cdColor& mask_color);
   // Icon an Position 'idx' loeschen
   bool removeIcon(int idx);


protected:

   void *_ilist;     // Zeiger auf Wrapper-Objekt


   // ECL/win Internas
   // ================

   // Interner Konstruktor
   cwIconList(void *ilist);
   // Initialisierung
   void init();

   // Trennen vom Wrapper
   void __disconnect();
   // Zeiger auf Wrapper-Objekt ermitteln
   inline void *__getIList() const
      { return _ilist; }

};

#endif /*__INTERFACE__*/


// Implementierung cwIconList
// ===========================================================================

cwIconList::cwIconList(void *ilist)
{
   _ilist = ilist;
}

cwIconList::~cwIconList()
{
   #if defined __ECL_W32__
      delete (WCImageList*)_ilist;
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwIconList::init()
{
   #if defined __ECL_W32__
      _ilist = new WCImageList(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

bool cwIconList::create(const cResource& res, int pix_width, int grow, const cdColor& mask_color)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      destroy();
      #if defined __ECL_W32__
         UINT mfc_id = res.getID();
         COLORREF w32_color = mask_color.getOsVal();
         WCImageList& mfc_ilist = *((WCImageList*)_ilist);
         if ( __ECL_ASSERT1__(mfc_ilist.Create(mfc_id, pix_width, grow, w32_color)) )
            return true;
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

void cwIconList::destroy()
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            ((WCImageList*)_ilist)->DeleteImageList();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

bool cwIconList::setCount(int count)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            return !!((WCImageList*)_ilist)->SetImageCount(count);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

int cwIconList::getCount() const
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            return ((WCImageList*)_ilist)->GetImageCount();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return -1;
}

void cwIconList::setBkgndColor(const cdColor& bkgnd_color)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         COLORREF w32_clr = bkgnd_color.getOsVal();
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            ((WCImageList*)_ilist)->SetBkColor(w32_clr);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

cdColor cwIconList::getBkgndColor() const
{
   cdColor color;

   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         COLORREF w32_clr = ((WCImageList*)_ilist)->m_hImageList != 0 ?
            ((CImageList*)_ilist)->GetBkColor()
          : CLR_NONE;
         if ( w32_clr != CLR_NONE )
            color = cdColor(GetRValue(w32_clr), GetGValue(w32_clr), GetBValue(w32_clr));
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return color;
}


// Icons hinzufuegen/loeschen
// ==========================

bool cwIconList::setIcon(int idx, const cIcon& icon)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            ((WCImageList*)_ilist)->Replace(idx, (HICON)ccwHandle::getHandle(icon));
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

bool cwIconList::setIcons(int /*idx*/, const cBitmap& /*bmp*/, const cdColor& /*mask_color*/)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         __ECL_ASSERT2__(0, ("cwIconList::setIcons() not yet implemented!!!"));
         // if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
         //    ((CImageList*)_ilist)->Replace(idx, ccwHandle::getHandle(bmp), mask_color);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

cIcon cwIconList::getIcon(int idx) const
{
   cIcon icon;

   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 ) {
            HICON hIcon = ((WCImageList*)_ilist)->ExtractIcon(idx);
            ccwHandle::setHandle(icon, hIcon);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return icon;
}

int cwIconList::addIcon(const cIcon& icon)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            return ((WCImageList*)_ilist)->Add((HICON)ccwHandle::getHandle(icon));
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return -1;
}

int cwIconList::addIcons(const cBitmap& bmp, const cdColor& mask_color)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         CBitmap *mfc_bmp = CBitmap::FromHandle((HBITMAP)ccwHandle::getHandle(bmp));
         COLORREF w32_clr = mask_color.getOsVal();
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            return ((WCImageList*)_ilist)->Add(mfc_bmp, w32_clr);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return -1;
}

bool cwIconList::removeIcon(int idx)
{
   if ( __ECL_ASSERT1__(_ilist != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCImageList*)_ilist)->m_hImageList != 0 )
            return !!((WCImageList*)_ilist)->Remove(idx);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}


// ECL/win Internas
// ================

void cwIconList::__disconnect()
{
   _ilist = 0;
}

