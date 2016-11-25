// ===========================================================================
// ew_commands.cpp                               ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cwCmd
//     |
//     +--cwCmdPosition
//     |   |
//     |   +--cwCmdMouse
//     |
//     +--cwCmdChar
//     |
//     +--cwCmdCmds
//         |
//         +--cwCmdEvt
//         |
//         +--cwCmdUI
//
// ===========================================================================

#include "win/ew_commands.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #if !defined GET_X_LPARAM
      #define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
      #define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
   #endif
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
#include "base/eb_str.hpp"
#include "base/eb_clip.hpp"
#include "win/ew_base.hpp"

#endif /*__INTERFACE__*/




// Lokale Klassen
// ===========================================================================

#if defined __ECL_W32__

   // Kennung des registrierten Formates "CBF_ECL"
   __declspec(dllimport) unsigned int EclClipboardFormat();

   // Wrapper-Klasse fuer Windows Global Memory Objekte
   class cGlobalMem {
      void *p; HGLOBAL hg;
   public:
      cGlobalMem(HGLOBAL handle)
         { p = GlobalLock(hg = handle); }
      ~cGlobalMem()
         { GlobalUnlock(hg); }
      operator void *()
         { return p; }
   };

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmd
// ---------------------------------------------------------------------------
//
//    cwCmd
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmd {
   friend class ccwCmd;

public:
   inline cwCmd(const cwCmd& cmd)
      { *this = cmd; }

protected:
   #if defined __ECL_W32__

      inline cwCmd()
         { l1 = l2 = msg = 0; }

      struct SHORTS {
         union { short s1; unsigned short us1; };
         union { short s2; unsigned short us2; };
      };

      unsigned int msg;       // Meldungscode
      union {
         unsigned long  ul1;  //  - ULONG (allgemein)
         long           l1;   //  - LONG (allgemein)
         SHORTS         v1;   //  - 2xSHORT (allgemein)
      };
      union {
         unsigned long  ul2;  //  - ULONG (allgemein)
         long           l2;   //  - LONG (allgemein)
         SHORTS         v2;   //  - 2xSHORT (allgemein)
      };

   #elif defined __ECL_OS2__

      cwCmd()
         { hwnd = msg = ul1 = ul2 = 0; }

      struct SHORTS {
         union { short s1; unsigned short us1; };
         union { short s2; unsigned short us2; };
      };

      unsigned long hwnd;     // Window-Handle
      unsigned long msg;      // Meldungscode
      union {
         unsigned long  ul1;  //  - ULONG (allgemein)
         long           l1;   //  - LONG (allgemein)
         SHORTS         v1;   //  - 2xSHORT (allgemein)
      };
      union {
         unsigned long  ul2;  //  - ULONG (allgemein)
         long           l2;   //  - LONG (allgemein)
         SHORTS         v2;   //  - 2xSHORT (allgemein)
      };

   #endif

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdPosition
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdPosition : public cwCmd {

public:
   cwCmdPosition(const cwCmd& cmd) :
      cwCmd(cmd) { }

   // Position des Events (in Window-Koordinaten)
   cdPoint getPos() const;

   int getPosX() const;
   int getPosY() const;

   // Screen- oder Window-Koordinaten?
   bool isRelativeToScreen() const;
   bool isRelativeToWindow() const;

   // Anforderung via Tastatur oder Maus?
   bool fromMouse() const;
   bool fromKeyboard() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdPosition
// ===========================================================================

cdPoint cwCmdPosition::getPos() const
{
   return cdPoint(getPosX(), getPosY());
}

int cwCmdPosition::getPosX() const
{
   #if defined __ECL_OS2__
      return v1.s1;
   #else
      return GET_X_LPARAM(ul2);
   #endif
}

int cwCmdPosition::getPosY() const
{
   #if defined __ECL_OS2__
      return v1.s2;
   #else
      return GET_Y_LPARAM(ul2);
   #endif
}

bool cwCmdPosition::isRelativeToScreen() const
{
   #if defined __ECL_W32__
      return msg == WM_CONTEXTMENU;
   #else
      // ...
   #endif
}

bool cwCmdPosition::isRelativeToWindow() const
{
   #if defined __ECL_W32__
      return msg != WM_CONTEXTMENU;
   #else
      // ...
   #endif
}

bool cwCmdPosition::fromMouse() const
{
   return getPosX() >= 0 && getPosY() >= 0;
}

bool cwCmdPosition::fromKeyboard() const
{
   return getPosX() < 0 || getPosY() < 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdMouse
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdMouse
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdMouse : public cwCmdPosition {

public:
   cwCmdMouse(const cwCmd& cmd) :
      cwCmdPosition(cmd) { }

   // SHIFT, CTRL oder ALT momentan gedrueckt?
   bool holdsShift() const;
   bool holdsCtrl() const;
   bool holdsAlt() const;

   // Welche Mausknoepfe sind momentan gedrueckt?
   bool holdsLeftButton() const;
   bool holdsRightButton() const;
   bool holdsMiddleButton() const;

   // Event von Mausknopf (0=None, 1=Left, 2=Right, 3=Middle)
   int getButtonNo() const;

   bool wasClickLeftButton() const;
   bool wasClickRightButton() const;
   bool wasClickMiddleButton() const;

   // Art des Mausklicks (0=None, 1=Down, 2=Up, 3=DblClick)
   int getClickStyle() const;

   bool wasClickDown() const;
   bool wasClickUp() const;
   bool wasClickDbl() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdMouse
// ===========================================================================

bool cwCmdMouse::holdsShift() const
{
   #if defined __ECL_OS2__
      return v2.us2 & KC_SHIFT;
   #else
      return !!(ul1 & MK_SHIFT);
   #endif
}

bool cwCmdMouse::holdsCtrl() const
{
   #if defined __ECL_OS2__
      return v2.us2 & KC_CTRL;
   #else
      return !!(ul1 & MK_CONTROL);
   #endif
}

bool cwCmdMouse::holdsAlt() const
{
   #if defined __ECL_OS2__
      return v2.us2 & KC_ALT;
   #else
      // Kann unter Win32 nicht ermittelt werden!
      return false;
   #endif
}

bool cwCmdMouse::holdsLeftButton() const
{
   #if defined __ECL_OS2__
      // ...
   #else
      return !!(ul1 & MK_LBUTTON);
   #endif
}

bool cwCmdMouse::holdsRightButton() const
{
   #if defined __ECL_OS2__
      // ...
   #else
      return !!(ul1 & MK_RBUTTON);
   #endif
}

bool cwCmdMouse::holdsMiddleButton() const
{
   #if defined __ECL_OS2__
      // ...
   #else
      return !!(ul1 & MK_MBUTTON);
   #endif
}

bool cwCmdMouse::wasClickLeftButton() const
{
   #if defined __ECL_W32__
      return
         msg == WM_LBUTTONDOWN
      || msg == WM_LBUTTONUP
      || msg == WM_LBUTTONDBLCLK;
   #else
      // ...
   #endif
}

bool cwCmdMouse::wasClickRightButton() const
{
   #if defined __ECL_W32__
      return
         msg == WM_RBUTTONDOWN
      || msg == WM_RBUTTONUP
      || msg == WM_RBUTTONDBLCLK;
   #else
      // ...
   #endif
}

bool cwCmdMouse::wasClickMiddleButton() const
{
   #if defined __ECL_W32__
      return
         msg == WM_MBUTTONDOWN
      || msg == WM_MBUTTONUP
      || msg == WM_MBUTTONDBLCLK;
   #else
      // ...
   #endif
}

bool cwCmdMouse::wasClickDown() const
{
   #if defined __ECL_W32__
      return
         msg == WM_LBUTTONDOWN
      || msg == WM_RBUTTONDOWN
      || msg == WM_MBUTTONDOWN;
   #else
      // ...
   #endif
}

bool cwCmdMouse::wasClickUp() const
{
   #if defined __ECL_W32__
      return
         msg == WM_LBUTTONUP
      || msg == WM_RBUTTONUP
      || msg == WM_MBUTTONUP;
   #else
      // ...
   #endif
}

bool cwCmdMouse::wasClickDbl() const
{
   #if defined __ECL_W32__
      return
         msg == WM_LBUTTONDBLCLK
      || msg == WM_RBUTTONDBLCLK
      || msg == WM_MBUTTONDBLCLK;
   #else
      // ...
   #endif
}

int cwCmdMouse::getButtonNo() const
{
   if ( wasClickLeftButton() ) {
      return 1;
   } else if ( wasClickRightButton() ) {
      return 2;
   } else if ( wasClickMiddleButton() ) {
      return 3;
   } else {
      return 0;
   }
}

int cwCmdMouse::getClickStyle() const
{
   if ( wasClickDown() ) {
      return 1;
   } else if ( wasClickUp() ) {
      return 2;
   } else if ( wasClickDbl() ) {
      return 3;
   } else {
      return 0;
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdDragDrop
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDragDrop : public cwCmdPosition {

public:
   cwCmdDragDrop(const cwCmd& cmd) :
      cwCmdPosition(cmd) { }

   // SHIFT, CTRL oder ALT momentan gedrueckt?
   bool holdsShift() const;
   bool holdsCtrl() const;
   bool holdsAlt() const;

   // Welche Mausknoepfe sind momentan gedrueckt?
   bool holdsLeftButton() const;
   bool holdsRightButton() const;
   bool holdsMiddleButton() const;

   // Ist ein bestimmtes Format vorhanden?
   bool isAvailable(const cClipboardFormat& format) const;
   // Daten im ECL-Format erfragen
   bool getData(cClipboardData& data) const;
   // Daten in bestimmtem Format 'format' erfragen
   bool getData(cClipboardData& data, const cClipboardFormat& format) const;

protected:
   // Menge der erlaubten Operationen setzen
   void setAllowedOps(int allowed_ops);
   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setSourceOps(int source_ops);
   // Ausgewaehlte Operation setzen
   void setDropOp(int drop_op);

   // Menge der erlaubten Operationen erfragen
   int getAllowedOps() const;
   // Menge der von der DragSource unterstuetzten Operationen erfragen
   int getSourceOps() const;
   // Ausgewaehlte Operation erfragen
   int getDropOp() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdDragDrop
// ===========================================================================

#if defined __ECL_W32__
   //
   //      | HIWORD | LOWORD     <ops> = 0xfXyz0000
   // -----+--------+---------          (0x76543210)
   // msg: | <ops>  | KeyState       x = cwDragSource::SOURCE_OPS (Shift=24)
   // ul1: | <COleDataObject*>       y = cwDropTarget::ALLOWED_OPS (Shift=20)
   // ul2: | yPos   | xPos           z = cwDropTarget::DROP_OP (Shift=16)
   //
   #define DDS_SOURCE_OPS  24
   #define DDS_ALLOWED_OPS 20
   #define DDS_DROP_OP     16
#endif

bool cwCmdDragDrop::holdsShift() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return !!(::GetKeyState(VK_SHIFT) & 0x8000);
      } else {
         return !!(msg & MK_SHIFT);
      }
   #endif
}

bool cwCmdDragDrop::holdsCtrl() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return !!(::GetKeyState(VK_CONTROL) & 0x8000);
      } else {
         return !!(msg & MK_CONTROL);
      }
   #endif
}

bool cwCmdDragDrop::holdsAlt() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return false; // TBD: Kann nicht erfragt werden?!
      } else {
         return !!(msg & MK_ALT);
      }
   #endif
}

bool cwCmdDragDrop::holdsLeftButton() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return !!(::GetKeyState(VK_LBUTTON) & 0x8000);
      } else {
         return !!(msg & MK_LBUTTON);
      }
   #endif
}

bool cwCmdDragDrop::holdsRightButton() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return !!(::GetKeyState(VK_RBUTTON) & 0x8000);
      } else {
         return !!(msg & MK_RBUTTON);
      }
   #endif
}

bool cwCmdDragDrop::holdsMiddleButton() const
{
   #if defined __ECL_W32__
      if ( (msg & 0xffff) == 0xffff ) {
         return !!(::GetKeyState(VK_MBUTTON) & 0x8000);
      } else {
         return !!(msg & MK_MBUTTON);
      }
   #endif
}

bool cwCmdDragDrop::isAvailable(const cClipboardFormat& format) const
{
   #if defined __ECL_W32__

      COleDataObject *mfc_data = (COleDataObject*)ul1;

      if ( mfc_data != 0 ) {
         if ( format == cClipboardFormat::getFmtText() ) {
            return !!mfc_data->IsDataAvailable(CF_TEXT);
         } else if ( format == cClipboardFormat::getFmtBitmap() ) {
            return !!mfc_data->IsDataAvailable(CF_BITMAP);
         } else if ( mfc_data->IsDataAvailable(CLIPFORMAT(EclClipboardFormat())) ) {
            HGLOBAL hg = mfc_data->GetGlobalData(CLIPFORMAT(EclClipboardFormat()));
            if ( __ECL_ASSERT1__(hg != NULL) )
               return format == cClipboardData::getFormatFromStreamed(cGlobalMem(hg));
         }
      }

   #else
   #endif

   return false;
}

bool cwCmdDragDrop::getData(cClipboardData& data) const
{
   #if defined __ECL_W32__

      COleDataObject *mfc_data = (COleDataObject*)ul1;

      if ( mfc_data != 0 ) {
         if ( mfc_data->IsDataAvailable(CLIPFORMAT(EclClipboardFormat())) ) {
            HGLOBAL hg = mfc_data->GetGlobalData(CLIPFORMAT(EclClipboardFormat()));
            if ( __ECL_ASSERT1__(hg != NULL) )
               return data.initFromStreamedData(cGlobalMem(hg));
         }
      }

   #else
   #endif

   return false;
}

bool cwCmdDragDrop::getData(cClipboardData& data, const cClipboardFormat& format) const
{
   #if defined __ECL_W32__

      COleDataObject *mfc_data = (COleDataObject*)ul1;

      if ( mfc_data != 0 ) {

         if ( format == cClipboardFormat::getFmtText()
           || format == cClipboardFormat::getFmtUndef() )
         {
            if ( mfc_data->IsDataAvailable(CF_TEXT) ) {
               HGLOBAL hg = mfc_data->GetGlobalData(CF_TEXT);
               if ( __ECL_ASSERT1__(hg != NULL) )
                  return data.initFromStreamedText(cGlobalMem(hg));
            }
         }

         if ( format == cClipboardFormat::getFmtBitmap()
           || format == cClipboardFormat::getFmtUndef() )
         {
            if ( mfc_data->IsDataAvailable(CF_BITMAP) ) {
               // ...
            }
         }

      }

   #else
   #endif

   return getData(data);
}

void cwCmdDragDrop::setAllowedOps(int allowed_ops)
{
   #if defined __ECL_W32__
      msg = (msg & ~(0xf << DDS_ALLOWED_OPS)) | ((allowed_ops & 0xf) << DDS_ALLOWED_OPS);
   #endif
}

void cwCmdDragDrop::setSourceOps(int source_ops)
{
   #if defined __ECL_W32__
      msg = (msg & ~(0xf << DDS_SOURCE_OPS)) | ((source_ops & 0xf) << DDS_SOURCE_OPS);
   #endif
}

void cwCmdDragDrop::setDropOp(int drop_op)
{
   #if defined __ECL_W32__
      msg = (msg & ~(0xf << DDS_DROP_OP)) | ((drop_op & 0xf) << DDS_DROP_OP);
   #endif
}

int cwCmdDragDrop::getAllowedOps() const
{
   #if defined __ECL_W32__
      return (msg >> DDS_ALLOWED_OPS) & 0xf;
   #endif
}

int cwCmdDragDrop::getSourceOps() const
{
   #if defined __ECL_W32__
      return (msg >> DDS_SOURCE_OPS) & 0xf;
   #endif
}

int cwCmdDragDrop::getDropOp() const
{
   #if defined __ECL_W32__
      return (msg >> DDS_DROP_OP) & 0xf;
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdDrag
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//             +--cwCmdDrag
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDrag : public cwCmdDragDrop {

public:
   cwCmdDrag(const cwCmd& cmd) :
      cwCmdDragDrop(cmd) { }

   // Erlaubte Operationen
   enum ALLOWED_OPS {
      allowNone   = 0x00,  // DropTarget erlaubt keine Operation
      allowCopy   = 0x01,  // DropTarget erlaubt "Objekt kopieren"
      allowMove   = 0x02,  // DropTarget erlaubt "Objekt bewegen"
      allowLink   = 0x04   // DropTarget erlaubt "Verknuefpung erstellen"
   };

   // Menge der erlaubten Operationen setzen
   void setAllowedOps(int allowed_ops);
   // Menge der erlaubten Operationen erfragen
   int getAllowedOps() const;

   // Umwandlung vom systemspezifischen Format: Erlaubte Operationen
   static int convSysToAllowedOps(int sys);
   // Umwandlung ins systemspezifische Format: Erlaubte Operationen
   static int convAllowedOpsToSys(int allowed_ops);

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdDrag
// ===========================================================================

void cwCmdDrag::setAllowedOps(int allowed_ops)
{
   cwCmdDragDrop::setAllowedOps(allowed_ops);
}

int cwCmdDrag::getAllowedOps() const
{
   return cwCmdDragDrop::getAllowedOps();
}

int cwCmdDrag::convSysToAllowedOps(int sys)
{
   int allowed_ops = allowNone;

   #if defined __ECL_W32__
      if ( sys & DROPEFFECT_COPY )
         allowed_ops |= allowCopy;
      if ( sys & DROPEFFECT_MOVE )
         allowed_ops |= allowMove;
      if ( sys & DROPEFFECT_LINK )
         allowed_ops |= allowLink;
   #endif

   return allowed_ops;
}

int cwCmdDrag::convAllowedOpsToSys(int allowed_ops)
{
   int sys = 0;

   #if defined __ECL_W32__
      if ( allowed_ops & allowCopy )
         sys |= DROPEFFECT_COPY;
      if ( allowed_ops & allowMove )
         sys |= DROPEFFECT_MOVE;
      if ( allowed_ops & allowLink )
         sys |= DROPEFFECT_LINK;
   #endif

   return sys;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdDrop
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//             +--cwCmdDrop
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDrop : public cwCmdDragDrop {

public:
   cwCmdDrop(const cwCmd& cmd) :
      cwCmdDragDrop(cmd) { }

   // Von der DragSource unterstuetzte Operationen
   enum SOURCE_OPS {
      mayCopy     = 0x01,  // DragSource unterstuetzt "Objekt kopieren"
      mayMove     = 0x02,  // DragSource unterstuetzt "Objekt bewegen"
      mayLink     = 0x04,  // DragSource unterstuetzt "Verknuefpung erstellen"
      mayBeAny    = 0x07   // DragSource unterstuetzt alle Operationen
   };

   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setSourceOps(int source_ops);
   // Menge der erlaubten Operationen erfragen
   int getSourceOps() const;

   // Umwandlung vom systemspezifischen Format: Von DragSource unterstuetzte Operationen
   static int convSysToSourceOps(int sys);
   // Umwandlung ins systemspezifische Format: Von DragSource unterstuetzte Operationen
   static int convSourceOpsToSys(int source_ops);


   // Auszufuehrende Operation
   enum DROP_OP {
      opNone      = 0x00,  // Keine Drop-Operation ausfuehren (Dummy)
      opCopy      = 0x01,  // Drop-Operation "Objekt kopieren"
      opMove      = 0x02,  // Drop-Operation "Objekt bewegen"
      opLink      = 0x04   // Drop-Operation "Verknuefpung erstellen"
   };

   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setDropOp(DROP_OP drop_op);
   // Menge der erlaubten Operationen erfragen
   DROP_OP getDropOp() const;

   // Umwandlung vom systemspezifischen Format: Ausgewaehlte Operation
   static DROP_OP convSysToDropOp(int sys);
   // Umwandlung ins systemspezifischen Format: Ausgewaehlte Operation
   static int convDropOpToSys(DROP_OP drop_op);

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdDrop
// ===========================================================================

void cwCmdDrop::setSourceOps(int source_ops)
{
   cwCmdDragDrop::setSourceOps(source_ops);
}

int cwCmdDrop::getSourceOps() const
{
   return cwCmdDragDrop::getSourceOps();
}

int cwCmdDrop::convSysToSourceOps(int sys)
{
   int source_ops = 0;

   #if defined __ECL_W32__
      if ( sys & DROPEFFECT_COPY )
         source_ops |= mayCopy;
      if ( sys & DROPEFFECT_MOVE )
         source_ops |= mayMove;
      if ( sys & DROPEFFECT_LINK )
         source_ops |= mayLink;
   #endif

   return source_ops;
}

int cwCmdDrop::convSourceOpsToSys(int source_ops)
{
   int sys = 0;

   #if defined __ECL_W32__
      if ( source_ops & mayCopy )
         sys |= DROPEFFECT_COPY;
      if ( source_ops & mayMove )
         sys |= DROPEFFECT_MOVE;
      if ( source_ops & mayLink )
         sys |= DROPEFFECT_LINK;
   #endif

   return sys;
}

void cwCmdDrop::setDropOp(DROP_OP drop_op)
{
   cwCmdDragDrop::setDropOp(drop_op);
}

cwCmdDrop::DROP_OP cwCmdDrop::getDropOp() const
{
   return DROP_OP(cwCmdDragDrop::getDropOp());
}

cwCmdDrop::DROP_OP cwCmdDrop::convSysToDropOp(int sys)
{
   DROP_OP drop_op = opNone;

   #if defined __ECL_W32__
      if ( sys & DROPEFFECT_COPY ) {
         drop_op = opCopy;
      } else if ( sys & DROPEFFECT_MOVE ) {
         drop_op = opMove;
      } else if ( sys & DROPEFFECT_LINK ) {
         drop_op = opLink;
      }
   #endif

   return drop_op;
}

int cwCmdDrop::convDropOpToSys(DROP_OP drop_op)
{
   int sys = 0;

   #if defined __ECL_W32__
      if ( drop_op & opCopy )
         sys |= DROPEFFECT_COPY;
      if ( drop_op & opMove )
         sys |= DROPEFFECT_MOVE;
      if ( drop_op & opLink )
         sys |= DROPEFFECT_LINK;
   #endif

   return sys;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdChar
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdChar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdChar : public cwCmd {

public:
   cwCmdChar(const cwCmd& cmd) :
      cwCmd(cmd) { }

   enum VIRTUALKEYS {
      vkUndef,                // Nicht definiert, normale Taste

      vkF1, vkF2, vkF3,       // Funktionstasten F1..F3
      vkF4, vkF5, vkF6,       // Funktionstasten F4..F6
      vkF7, vkF8, vkF9,       // Funktionstasten F7..F9
      vkF10, vkF11, vkF12,    // Funktionstasten F10..F12

      vkBreak,                // Break
      vkShift,                // Shift (links oder rechts)
      vkControl,              // Strg (links oder rechts)
      vkAlt,                  // Alt (links)
      vkAltGraf,              // AltGr (rechts)
      vkEsc,                  // ESC
      vkBackspace,            // BACKSPACE
      vkReturn,               // RETURN (Alpha-Block)
      vkTab,                  // TAB
      vkBackTab,              // BACKTAB
      vkPause,                // PAUSE
      vkSpace,                // Leertaste

      vkPgUp,                 // Cursor "Bild Auf"
      vkPgDown,               // Cursor "Bild Ab"
      vkEnd,                  // Cursor "Ende"
      vkHome,                 // Cursor "Pos1"
      vkLeft,                 // Cursor "Links"
      vkRight,                // Cursor "Rechts"
      vkUp,                   // Cursor "Auf"
      vkDown,                 // Cursor "Ab"

      vkPrintScrn,            // Druck
      vkInsert,               // Einfg
      vkDelete,               // Entf
      vkScrlLock,             // Rollen
      vkCapsLock,             // Caps

      vkNumLock,              // NumPad "Num" (Num-Lock)
      vkNumDiv,               // NumPad "/" (Divide)
      vkNumMul,               // NumPad "x" (Multiply)
      vkNumSub,               // NumPad "-" (Subtract)
      vkNumAdd,               // NumPad "+" (Add)
      vkNumEnter,             // NumPad "Enter"
      vkNumDec,               // NumPad "," (Decimal-Point)
      vkNum0,                 // NumPad "0"
      vkNum1,                 // NumPad "1"
      vkNum2,                 // NumPad "2"
      vkNum3,                 // NumPad "3"
      vkNum4,                 // NumPad "4"
      vkNum5,                 // NumPad "5"
      vkNum6,                 // NumPad "6"
      vkNum7,                 // NumPad "7"
      vkNum8,                 // NumPad "8"
      vkNum9,                 // NumPad "9"

      // Alte Bezeichner, nicht mehr benutzen:
      //
      vkEnter = vkNumEnter,   // ENTER (Ziffern-Block)
      vkPageUp = vkPgUp,      // Bild Auf
      vkPageDown = vkPgDown,  // Bild Ab
   };

   // Taste gedrueckt?
   bool isKeyDown() const;
   // Taste losgelassen?
   bool isKeyUp() const;

   // Code fuer Sondertaste verfuegbar?
   bool isVirt() const;
   // Code fuer normale Taste verfuegbar?
   bool isChar() const;

   // Abfrage der Codes fuer Sondertaste
   VIRTUALKEYS getVirt() const;
   // Abfrage der Codes fuer normale Taste
   int getChar() const;

   // Meldung nicht weiterleiten
   void killMsg();

   // Tastencode modifizieren (nur bei normaler Taste)
   void setChar(int ch_code);
   // Tastencode aus Puffer entfernen (nur bei normaler Taste)
   void killChar();

   // SHIFT gedrueckt?
   bool holdsShift() const;
   // CTRL gedrueckt?
   bool holdsCtrl() const;
   // ALT gedrueckt?
   bool holdsAlt() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdChar
// ===========================================================================

bool cwCmdChar::isKeyUp() const
{
   #if defined __ECL_OS2__
      return !!(v1.us1 & KC_KEYUP);
   #elif defined __ECL_W32__
      return !!(v2.us2 & KF_UP);
   #else
      return false;
   #endif
}

bool cwCmdChar::isKeyDown() const
{
   #if defined __ECL_OS2__
      return !(v1.us1 & KC_KEYUP);
   #elif defined __ECL_W32__
      return !(v2.us2 & KF_UP);
   #else
      return false;
   #endif
}

bool cwCmdChar::isVirt() const
{
   #if defined __ECL_OS2__
      return !!(v1.us1 & KC_VIRTUALKEY);
   #elif defined __ECL_W32__
      return msg == WM_KEYDOWN || msg == WM_KEYUP;
   #else
      return false;
   #endif
}

bool cwCmdChar::isChar() const
{
   #if defined __ECL_OS2__
      return !!(v1.us1 & KC_CHAR);
   #elif defined __ECL_W32__
      return msg == WM_CHAR || msg == 0;
   #else
      return false;
   #endif
}

cwCmdChar::VIRTUALKEYS cwCmdChar::getVirt() const
{
   #if defined __ECL_OS2__
      switch ( v2.us2 ) {
         case VK_BREAK:       return vkBreak;
         case VK_BACKSPACE:   return vkBackspace
         case VK_TAB:         return vkTab;
         case VK_BACKTAB:     return vkBackTab;
         case VK_NEWLINE:     return vkReturn;
         case VK_SHIFT:       return vkShift;
         case VK_CTRL:        return vkControl;
         case VK_ALT:         return vkAlt;
         case VK_ALTGRAF:     return vkAltGraf;
         case VK_PAUSE:       return vkPause;
         case VK_CAPSLOCK:    return vkCapsLock;
         case VK_ESC:         return vkEsc;
         case VK_SPACE:       return vkSpace;
         case VK_PAGEUP:      return vkPageUp;
         case VK_PAGEDOWN:    return vkPageDown;
         case VK_END:         return vkEnd;
         case VK_HOME:        return vkHome;
         case VK_LEFT:        return vkLeft;
         case VK_UP:          return vkUp;
         case VK_RIGHT:       return vkRight;
         case VK_DOWN:        return vkDown;
         case VK_PRINTSCRN:   return vkPrintScrn;
         case VK_INSERT:      return vkInsert;
         case VK_DELETE:      return vkDelete;
         case VK_SCRLLOCK:    return vkScrlLock;
         case VK_NUMLOCK:     return vkNumLock;
         case VK_ENTER:       return vkCapsLock;
         case VK_F1:          return vkF1;
         case VK_F2:          return vkF2;
         case VK_F3:          return vkF3;
         case VK_F4:          return vkF4;
         case VK_F5:          return vkF5;
         case VK_F6:          return vkF6;
         case VK_F7:          return vkF7;
         case VK_F8:          return vkF8;
         case VK_F9:          return vkF9;
         case VK_F10:         return vkF10;
         case VK_F11:         return vkF11;
         case VK_F12:         return vkF12;
         default:             return vkUndef;
      }
   #elif defined __ECL_W32__
      if ( msg == WM_KEYDOWN || msg == WM_KEYUP ) {
         switch ( ul1 ) {
            case VK_BACK:        return vkBackspace;
            case VK_TAB:         return holdsShift() ? vkBackTab : vkTab;
            case VK_RETURN:      return vkReturn;
            case VK_SHIFT:       return vkShift;
            case VK_CONTROL:     return vkControl;
            case VK_MENU:        return (GetKeyState(VK_RMENU) & 0xff00) ? vkAltGraf : vkAlt;
            case VK_PAUSE:       return holdsCtrl() ? vkBreak : vkPause;
            case VK_ESCAPE:      return vkEsc;
            case VK_SPACE:       return vkSpace;

            case VK_PRIOR:       return vkPgUp;
            case VK_NEXT:        return vkPgDown;
            case VK_END:         return vkEnd;
            case VK_HOME:        return vkHome;
            case VK_LEFT:        return vkLeft;
            case VK_UP:          return vkUp;
            case VK_RIGHT:       return vkRight;
            case VK_DOWN:        return vkDown;

            case VK_INSERT:      return vkInsert;
            case VK_DELETE:      return vkDelete;
            case VK_SCROLL:      return vkScrlLock;
            case VK_CAPITAL:     return vkCapsLock;

            case VK_NUMLOCK:     return vkNumLock;
            case VK_NUMPAD0:     return vkNum0;
            case VK_NUMPAD1:     return vkNum1;
            case VK_NUMPAD2:     return vkNum2;
            case VK_NUMPAD3:     return vkNum3;
            case VK_NUMPAD4:     return vkNum4;
            case VK_NUMPAD5:     return vkNum5;
            case VK_NUMPAD6:     return vkNum6;
            case VK_NUMPAD7:     return vkNum7;
            case VK_NUMPAD8:     return vkNum8;
            case VK_NUMPAD9:     return vkNum9;
            case VK_MULTIPLY:    return vkNumMul;
            case VK_ADD:         return vkNumAdd;
            case VK_SUBTRACT:    return vkNumSub;
            case VK_DECIMAL:     return vkNumDec;
            case VK_DIVIDE:      return vkNumDiv;

            case VK_F1:          return vkF1;
            case VK_F2:          return vkF2;
            case VK_F3:          return vkF3;
            case VK_F4:          return vkF4;
            case VK_F5:          return vkF5;
            case VK_F6:          return vkF6;
            case VK_F7:          return vkF7;
            case VK_F8:          return vkF8;
            case VK_F9:          return vkF9;
            case VK_F10:         return vkF10;
            case VK_F11:         return vkF11;
            case VK_F12:         return vkF12;

            default:             return vkUndef;
         }
      }
      return vkUndef;
   #else
      return vkUndef;
   #endif
}

int cwCmdChar::getChar() const
{
   #if defined __ECL_OS2__
      return v2.us1;
   #elif defined __ECL_W32__
      return (msg == WM_CHAR || msg == 0) ? int(l1) : -1;
   #else
      return 0;
   #endif
}

void cwCmdChar::setChar(int ch_code)
{
   #if defined __ECL_OS2__
      v2.us1 = (unsigned short)ch_code;
   #elif defined __ECL_W32__
      if ( isChar() ) {
         msg = 0; // Meldung als "veraendert" markieren
         l1 = ch_code;
      }
   #endif
}

void cwCmdChar::killMsg()
{
   #if defined __ECL_OS2__
      v2.us1 = 0;
   #elif defined __ECL_W32__
      msg = 0; // Meldung als "veraendert" markieren
      l1 = 0;
   #endif
}

void cwCmdChar::killChar()
{
   if ( isChar() )
      killMsg();
}

bool cwCmdChar::holdsShift() const
{
   #if defined __ECL_OS2__
      return v1.us1 & KC_SHIFT;
   #elif defined __ECL_W32__
      return !!(GetKeyState(VK_SHIFT) & 0xff00);
   #else
      return false;
   #endif
}

bool cwCmdChar::holdsCtrl() const
{
   #if defined __ECL_OS2__
      return v1.us1 & KC_CTRL;
   #elif defined __ECL_W32__
      return !!(GetKeyState(VK_CONTROL) & 0xff00);
   #else
      return false;
   #endif
}

bool cwCmdChar::holdsAlt() const
{
   #if defined __ECL_OS2__
      return v1.us1 & KC_ALT;
   #elif defined __ECL_W32__
      return !!(GetKeyState(VK_MENU) & 0xff00);
   #else
      return false;
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdCmds
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdCmds : public cwCmd {

public:
   // Konstruktor
   cwCmdCmds(const cwCmd& cmd) :
      cwCmd(cmd) { }

   enum CMDSRC {
      csSystem,               // Systemereignis
      csProgram,              // Programmiertes Ereignis
      csControl,              // Quelle: Dialog-Control
      csMenu,                 // Quelle: Menueauswahl
      csAccel                 // Quelle: Accelerator
   };

   enum STDCMDS {
      cmdStandardFirst = -1000,

      cmdSysClose,
      cmdSysHotkey,
      cmdSysHScroll,
      cmdSysKeyMenu,
      cmdSysMaximize,
      cmdSysMinimize,
      cmdSysMouseMenu,
      cmdSysMove,
      cmdSysNextWindow,
      cmdSysPrevWindow,
      cmdSysRestore,
      cmdSysScreenSave,
      cmdSysSize,
      cmdSysTaskList,
      cmdSysVScroll,

      cmdFileNew,                         // Datei->Neu...
      cmdFileOpen,                        // Datei->Öffnen...
      cmdFileClose,                       // Datei->Schliessen
      cmdFileSave,                        // Datei->Speichern
      cmdFileSaveAs,                      // Datei->Speichern unter...
      cmdFilePageSetup,                   // Datei->Seite einrichten...
      cmdFilePrintSetup,                  // Datei->Druckereinrichtung...
      cmdFilePrint,                       // Datei->Drucken...
      cmdFilePrintDirect,                 // ?
      cmdFilePrintPreview,                // Datei->Druckvorschau...
      cmdFileUpdate,                      // ?
      cmdFileSaveCopyAs,                  // Datei->Speichern als Kopie...
      cmdFileSendMail,                    // Datei->Senden...

      cmdFileMruFirst,                    // (erster Eintrag der Liste)
      cmdFileMru01 = cmdFileMruFirst,     // (Datei 01 oeffnen)
      cmdFileMru02,                       // (Datei 02 oeffnen)
      cmdFileMru03,                       // (Datei 03 oeffnen)
      cmdFileMru04,                       // (Datei 04 oeffnen)
      cmdFileMru05,                       // (Datei 05 oeffnen)
      cmdFileMru06,                       // (Datei 06 oeffnen)
      cmdFileMru07,                       // (Datei 07 oeffnen)
      cmdFileMru08,                       // (Datei 08 oeffnen)
      cmdFileMru09,                       // (Datei 09 oeffnen)
      cmdFileMru10,                       // (Datei 10 oeffnen)
      cmdFileMru11,                       // (Datei 11 oeffnen)
      cmdFileMru12,                       // (Datei 12 oeffnen)
      cmdFileMru13,                       // (Datei 13 oeffnen)
      cmdFileMru14,                       // (Datei 14 oeffnen)
      cmdFileMru15,                       // (Datei 15 oeffnen)
      cmdFileMru16,                       // (Datei 16 oeffnen)
      cmdFileMruLast = cmdFileMru16,      // (letzter Eintrag der Liste)

      cmdEditClear,
      cmdEditClearAll,
      cmdEditCopy,
      cmdEditCut,
      cmdEditFind,
      cmdEditPaste,
      cmdEditPasteLink,
      cmdEditPasteSpecial,
      cmdEditRepeat,
      cmdEditReplace,
      cmdEditSelectAll,
      cmdEditUndo,
      cmdEditRedo,

      cmdWindowNew,
      cmdWindowArrange,
      cmdWindowCascade,
      cmdWindowTileHorz,
      cmdWindowTileVert,
      cmdWindowSplit,

      cmdWindowFirst,
      cmdWindow01 = cmdWindowFirst,
      cmdWindow02,
      cmdWindow03,
      cmdWindow04,
      cmdWindow05,
      cmdWindow06,
      cmdWindow07,
      cmdWindow08,
      cmdWindow09,
      cmdWindow10,
      cmdWindow11,
      cmdWindow12,
      cmdWindow13,
      cmdWindow14,
      cmdWindow15,
      cmdWindow16,
      cmdWindowLast = cmdWindow16,

      cmdAppAbout,
      cmdAppExit,

      cmdHelpIndex,
      cmdHelpFinder,
      cmdHelpUsing,
      cmdHelpContext,
      cmdHelp,
      cmdDefaultHelp,

      cmdPaneNext,
      cmdPanePrev,

      cmdFormatFont,

      cmdPreviewClose,
      cmdPreviewNumpage,
      cmdPreviewNext,
      cmdPreviewPrev,
      cmdPreviewPrint,
      cmdPreviewZoomin,
      cmdPreviewZoomout,

      cmdViewToolbar,
      cmdViewStatusbar,
      cmdViewRebar,
      cmdViewAutoarrange,
      cmdViewSmallIcon,
      cmdViewLargeIcon,
      cmdViewList,
      cmdViewDetails,
      cmdViewLineup,
      cmdViewByname,

      cmdRecordFirst,
      cmdRecordLast,
      cmdRecordNext,
      cmdRecordPrev,

      cmdStandardLast
   };


   // Ermitteln der System-ID zu einer ECL-Ereignis-ID
   static int convID(STDCMDS ecl_id);
   // Ermitteln der ECL-Ereignis-ID zu einer System-ID
   static int convID(int sys_id, bool from_sysmenu);

protected:
   cwCmdCmds()
      { }

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdCmds
// ===========================================================================

int cwCmdCmds::convID(STDCMDS ecl_id)
{
   #if defined __ECL_W32__

      switch ( ecl_id ) {

      // System Commands
      case cmdSysClose:                       return SC_CLOSE;
      case cmdSysHotkey:                      return SC_HOTKEY;
      case cmdSysHScroll:                     return SC_HSCROLL;
      case cmdSysKeyMenu:                     return SC_KEYMENU;
      case cmdSysMaximize:                    return SC_MAXIMIZE;
      case cmdSysMinimize:                    return SC_MINIMIZE;
      case cmdSysMouseMenu:                   return SC_MOUSEMENU;
      case cmdSysMove:                        return SC_MOVE;
      case cmdSysNextWindow:                  return SC_NEXTWINDOW;
      case cmdSysPrevWindow:                  return SC_PREVWINDOW;
      case cmdSysRestore:                     return SC_RESTORE;
      case cmdSysScreenSave:                  return SC_SCREENSAVE;
      case cmdSysSize:                        return SC_SIZE;
      case cmdSysTaskList:                    return SC_TASKLIST;
      case cmdSysVScroll:                     return SC_VSCROLL;

      // File commands
      case cmdFileNew:                        return ID_FILE_NEW;
      case cmdFileOpen:                       return ID_FILE_OPEN;
      case cmdFileClose:                      return ID_FILE_CLOSE;
      case cmdFileSave:                       return ID_FILE_SAVE;
      case cmdFileSaveAs:                     return ID_FILE_SAVE_AS;
      case cmdFilePageSetup:                  return ID_FILE_PAGE_SETUP;
      case cmdFilePrintSetup:                 return ID_FILE_PRINT_SETUP;
      case cmdFilePrint:                      return ID_FILE_PRINT;
      case cmdFilePrintDirect:                return ID_FILE_PRINT_DIRECT;
      case cmdFilePrintPreview:               return ID_FILE_PRINT_PREVIEW;
      case cmdFileUpdate:                     return ID_FILE_UPDATE;
      case cmdFileSaveCopyAs:                 return ID_FILE_SAVE_COPY_AS;
      case cmdFileSendMail:                   return ID_FILE_SEND_MAIL;

      case cmdFileMru01:                      return ID_FILE_MRU_FILE1;
      case cmdFileMru02:                      return ID_FILE_MRU_FILE2;
      case cmdFileMru03:                      return ID_FILE_MRU_FILE3;
      case cmdFileMru04:                      return ID_FILE_MRU_FILE4;
      case cmdFileMru05:                      return ID_FILE_MRU_FILE5;
      case cmdFileMru06:                      return ID_FILE_MRU_FILE6;
      case cmdFileMru07:                      return ID_FILE_MRU_FILE7;
      case cmdFileMru08:                      return ID_FILE_MRU_FILE8;
      case cmdFileMru09:                      return ID_FILE_MRU_FILE9;
      case cmdFileMru10:                      return ID_FILE_MRU_FILE10;
      case cmdFileMru11:                      return ID_FILE_MRU_FILE11;
      case cmdFileMru12:                      return ID_FILE_MRU_FILE12;
      case cmdFileMru13:                      return ID_FILE_MRU_FILE13;
      case cmdFileMru14:                      return ID_FILE_MRU_FILE14;
      case cmdFileMru15:                      return ID_FILE_MRU_FILE15;
      case cmdFileMru16:                      return ID_FILE_MRU_FILE16;

      // Edit commands
      case cmdEditClear:                      return ID_EDIT_CLEAR;
      case cmdEditClearAll:                   return ID_EDIT_CLEAR_ALL;
      case cmdEditCopy:                       return ID_EDIT_COPY;
      case cmdEditCut:                        return ID_EDIT_CUT;
      case cmdEditFind:                       return ID_EDIT_FIND;
      case cmdEditPaste:                      return ID_EDIT_PASTE;
      case cmdEditPasteLink:                  return ID_EDIT_PASTE_LINK;
      case cmdEditPasteSpecial:               return ID_EDIT_PASTE_SPECIAL;
      case cmdEditRepeat:                     return ID_EDIT_REPEAT;
      case cmdEditReplace:                    return ID_EDIT_REPLACE;
      case cmdEditSelectAll:                  return ID_EDIT_SELECT_ALL;
      case cmdEditUndo:                       return ID_EDIT_UNDO;
      case cmdEditRedo:                       return ID_EDIT_REDO;

      // Window commands
      case cmdWindowNew:                      return ID_WINDOW_NEW;
      case cmdWindowArrange:                  return ID_WINDOW_ARRANGE;
      case cmdWindowCascade:                  return ID_WINDOW_CASCADE;
      case cmdWindowTileHorz:                 return ID_WINDOW_TILE_HORZ;
      case cmdWindowTileVert:                 return ID_WINDOW_TILE_VERT;
      case cmdWindowSplit:                    return ID_WINDOW_SPLIT;
      #ifndef RC_INVOKED      // code only
      case cmdWindow01:                       return AFX_IDM_FIRST_MDICHILD+0;
      case cmdWindow02:                       return AFX_IDM_FIRST_MDICHILD+1;
      case cmdWindow03:                       return AFX_IDM_FIRST_MDICHILD+2;
      case cmdWindow04:                       return AFX_IDM_FIRST_MDICHILD+3;
      case cmdWindow05:                       return AFX_IDM_FIRST_MDICHILD+4;
      case cmdWindow06:                       return AFX_IDM_FIRST_MDICHILD+5;
      case cmdWindow07:                       return AFX_IDM_FIRST_MDICHILD+6;
      case cmdWindow08:                       return AFX_IDM_FIRST_MDICHILD+7;
      case cmdWindow09:                       return AFX_IDM_FIRST_MDICHILD+8;
      case cmdWindow10:                       return AFX_IDM_FIRST_MDICHILD+9;
      case cmdWindow11:                       return AFX_IDM_FIRST_MDICHILD+10;
      case cmdWindow12:                       return AFX_IDM_FIRST_MDICHILD+11;
      case cmdWindow13:                       return AFX_IDM_FIRST_MDICHILD+12;
      case cmdWindow14:                       return AFX_IDM_FIRST_MDICHILD+13;
      case cmdWindow15:                       return AFX_IDM_FIRST_MDICHILD+14;
      case cmdWindow16:                       return AFX_IDM_FIRST_MDICHILD+15;
      #endif //!RC_INVOKED

      // Help and App commands
      case cmdAppAbout:                       return ID_APP_ABOUT;
      case cmdAppExit:                        return ID_APP_EXIT;
      case cmdHelpIndex:                      return ID_HELP_INDEX;
      case cmdHelpFinder:                     return ID_HELP_FINDER;
      case cmdHelpUsing:                      return ID_HELP_USING;
      case cmdHelpContext:                    return ID_CONTEXT_HELP;
      case cmdHelp:                           return ID_HELP;
      case cmdDefaultHelp:                    return ID_DEFAULT_HELP;

      // Misc
      case cmdPaneNext:                       return ID_NEXT_PANE;
      case cmdPanePrev:                       return ID_PREV_PANE;

      // Format
      case cmdFormatFont:                     return ID_FORMAT_FONT;

      // for print preview dialog bar
      case cmdPreviewClose:                   return AFX_ID_PREVIEW_CLOSE;
      case cmdPreviewNumpage:                 return AFX_ID_PREVIEW_NUMPAGE;
      case cmdPreviewNext:                    return AFX_ID_PREVIEW_NEXT;
      case cmdPreviewPrev:                    return AFX_ID_PREVIEW_PREV;
      case cmdPreviewPrint:                   return AFX_ID_PREVIEW_PRINT;
      case cmdPreviewZoomin:                  return AFX_ID_PREVIEW_ZOOMIN;
      case cmdPreviewZoomout:                 return AFX_ID_PREVIEW_ZOOMOUT;

      // View commands (same number used as IDW used for control bar)
      case cmdViewToolbar:                    return ID_VIEW_TOOLBAR;
      case cmdViewStatusbar:                  return ID_VIEW_STATUS_BAR;
      case cmdViewRebar:                      return ID_VIEW_REBAR;
      case cmdViewAutoarrange:                return ID_VIEW_AUTOARRANGE;
      case cmdViewSmallIcon:                  return ID_VIEW_SMALLICON;
      case cmdViewLargeIcon:                  return ID_VIEW_LARGEICON;
      case cmdViewList:                       return ID_VIEW_LIST;
      case cmdViewDetails:                    return ID_VIEW_DETAILS;
      case cmdViewLineup:                     return ID_VIEW_LINEUP;
      case cmdViewByname:                     return ID_VIEW_BYNAME;

      // RecordForm commands
      case cmdRecordFirst:                    return ID_RECORD_FIRST;
      case cmdRecordLast:                     return ID_RECORD_LAST;
      case cmdRecordNext:                     return ID_RECORD_NEXT;
      case cmdRecordPrev:                     return ID_RECORD_PREV;

      }

      return 0;

   #elif defined __ECL_OS2__
      // ???
   #endif
}

int cwCmdCmds::convID(int sys_id, bool from_sysmenu)
{
   #if defined __ECL_W32__

      if ( from_sysmenu ) {

         switch ( sys_id ) {
         case SC_CLOSE:                            return cmdSysClose;
         case SC_HOTKEY:                           return cmdSysHotkey;
         case SC_HSCROLL:                          return cmdSysHScroll;
         case SC_KEYMENU:                          return cmdSysKeyMenu;
         case SC_MAXIMIZE:                         return cmdSysMaximize;
         case SC_MINIMIZE:                         return cmdSysMinimize;
         case SC_MOUSEMENU:                        return cmdSysMouseMenu;
         case SC_MOVE:                             return cmdSysMove;
         case SC_NEXTWINDOW:                       return cmdSysNextWindow;
         case SC_PREVWINDOW:                       return cmdSysPrevWindow;
         case SC_RESTORE:                          return cmdSysRestore;
         case SC_SCREENSAVE:                       return cmdSysScreenSave;
         case SC_SIZE:                             return cmdSysSize;
         case SC_TASKLIST:                         return cmdSysTaskList;
         case SC_VSCROLL:                          return cmdSysVScroll;
         }

      } else if ( sys_id >= 0xe100 ) {

         switch ( sys_id ) {

         // File commands
         case ID_FILE_NEW:                         return cmdFileNew;
         case ID_FILE_OPEN:                        return cmdFileOpen;
         case ID_FILE_CLOSE:                       return cmdFileClose;
         case ID_FILE_SAVE:                        return cmdFileSave;
         case ID_FILE_SAVE_AS:                     return cmdFileSaveAs;
         case ID_FILE_PAGE_SETUP:                  return cmdFilePageSetup;
         case ID_FILE_PRINT_SETUP:                 return cmdFilePrintSetup;
         case ID_FILE_PRINT:                       return cmdFilePrint;
         case ID_FILE_PRINT_DIRECT:                return cmdFilePrintDirect;
         case ID_FILE_PRINT_PREVIEW:               return cmdFilePrintPreview;
         case ID_FILE_UPDATE:                      return cmdFileUpdate;
         case ID_FILE_SAVE_COPY_AS:                return cmdFileSaveCopyAs;
         case ID_FILE_SEND_MAIL:                   return cmdFileSendMail;

         case ID_FILE_MRU_FILE1:                   return cmdFileMru01;
         case ID_FILE_MRU_FILE2:                   return cmdFileMru02;
         case ID_FILE_MRU_FILE3:                   return cmdFileMru03;
         case ID_FILE_MRU_FILE4:                   return cmdFileMru04;
         case ID_FILE_MRU_FILE5:                   return cmdFileMru05;
         case ID_FILE_MRU_FILE6:                   return cmdFileMru06;
         case ID_FILE_MRU_FILE7:                   return cmdFileMru07;
         case ID_FILE_MRU_FILE8:                   return cmdFileMru08;
         case ID_FILE_MRU_FILE9:                   return cmdFileMru09;
         case ID_FILE_MRU_FILE10:                  return cmdFileMru10;
         case ID_FILE_MRU_FILE11:                  return cmdFileMru11;
         case ID_FILE_MRU_FILE12:                  return cmdFileMru12;
         case ID_FILE_MRU_FILE13:                  return cmdFileMru13;
         case ID_FILE_MRU_FILE14:                  return cmdFileMru14;
         case ID_FILE_MRU_FILE15:                  return cmdFileMru15;
         case ID_FILE_MRU_FILE16:                  return cmdFileMru16;

         // Edit commands
         case ID_EDIT_CLEAR:                       return cmdEditClear;
         case ID_EDIT_CLEAR_ALL:                   return cmdEditClearAll;
         case ID_EDIT_COPY:                        return cmdEditCopy;
         case ID_EDIT_CUT:                         return cmdEditCut;
         case ID_EDIT_FIND:                        return cmdEditFind;
         case ID_EDIT_PASTE:                       return cmdEditPaste;
         case ID_EDIT_PASTE_LINK:                  return cmdEditPasteLink;
         case ID_EDIT_PASTE_SPECIAL:               return cmdEditPasteSpecial;
         case ID_EDIT_REPEAT:                      return cmdEditRepeat;
         case ID_EDIT_REPLACE:                     return cmdEditReplace;
         case ID_EDIT_SELECT_ALL:                  return cmdEditSelectAll;
         case ID_EDIT_UNDO:                        return cmdEditUndo;
         case ID_EDIT_REDO:                        return cmdEditRedo;

         // Window commands
         case ID_WINDOW_NEW:                       return cmdWindowNew;
         case ID_WINDOW_ARRANGE:                   return cmdWindowArrange;
         case ID_WINDOW_CASCADE:                   return cmdWindowCascade;
         case ID_WINDOW_TILE_HORZ:                 return cmdWindowTileHorz;
         case ID_WINDOW_TILE_VERT:                 return cmdWindowTileVert;
         case ID_WINDOW_SPLIT:                     return cmdWindowSplit;
         #ifndef RC_INVOKED      // code only
         case AFX_IDM_FIRST_MDICHILD+0:            return cmdWindow01;
         case AFX_IDM_FIRST_MDICHILD+1:            return cmdWindow02;
         case AFX_IDM_FIRST_MDICHILD+2:            return cmdWindow03;
         case AFX_IDM_FIRST_MDICHILD+3:            return cmdWindow04;
         case AFX_IDM_FIRST_MDICHILD+4:            return cmdWindow05;
         case AFX_IDM_FIRST_MDICHILD+5:            return cmdWindow06;
         case AFX_IDM_FIRST_MDICHILD+6:            return cmdWindow07;
         case AFX_IDM_FIRST_MDICHILD+7:            return cmdWindow08;
         case AFX_IDM_FIRST_MDICHILD+8:            return cmdWindow09;
         case AFX_IDM_FIRST_MDICHILD+9:            return cmdWindow10;
         case AFX_IDM_FIRST_MDICHILD+10:           return cmdWindow11;
         case AFX_IDM_FIRST_MDICHILD+11:           return cmdWindow12;
         case AFX_IDM_FIRST_MDICHILD+12:           return cmdWindow13;
         case AFX_IDM_FIRST_MDICHILD+13:           return cmdWindow14;
         case AFX_IDM_FIRST_MDICHILD+14:           return cmdWindow15;
         case AFX_IDM_FIRST_MDICHILD+15:           return cmdWindow16;
         #endif //!RC_INVOKED

         // Help and App commands
         case ID_APP_ABOUT:                        return cmdAppAbout;
         case ID_APP_EXIT:                         return cmdAppExit;
         case ID_HELP_INDEX:                       return cmdHelpIndex;
         case ID_HELP_FINDER:                      return cmdHelpFinder;
         case ID_HELP_USING:                       return cmdHelpUsing;
         case ID_CONTEXT_HELP:                     return cmdHelpContext;
         case ID_HELP:                             return cmdHelp;
         case ID_DEFAULT_HELP:                     return cmdDefaultHelp;

         // Misc
         case ID_NEXT_PANE:                        return cmdPaneNext;
         case ID_PREV_PANE:                        return cmdPanePrev;

         // Format
         case ID_FORMAT_FONT:                      return cmdFormatFont;

         // for print preview dialog bar
         case AFX_ID_PREVIEW_CLOSE:                return cmdPreviewClose;
         case AFX_ID_PREVIEW_NUMPAGE:              return cmdPreviewNumpage;
         case AFX_ID_PREVIEW_NEXT:                 return cmdPreviewNext;
         case AFX_ID_PREVIEW_PREV:                 return cmdPreviewPrev;
         case AFX_ID_PREVIEW_PRINT:                return cmdPreviewPrint;
         case AFX_ID_PREVIEW_ZOOMIN:               return cmdPreviewZoomin;
         case AFX_ID_PREVIEW_ZOOMOUT:              return cmdPreviewZoomout;

         // View commands (same number used as IDW used for control bar)
         case ID_VIEW_TOOLBAR:                     return cmdViewToolbar;
         case ID_VIEW_STATUS_BAR:                  return cmdViewStatusbar;
         case ID_VIEW_REBAR:                       return cmdViewRebar;
         case ID_VIEW_AUTOARRANGE:                 return cmdViewAutoarrange;
         case ID_VIEW_SMALLICON:                   return cmdViewSmallIcon;
         case ID_VIEW_LARGEICON:                   return cmdViewLargeIcon;
         case ID_VIEW_LIST:                        return cmdViewList;
         case ID_VIEW_DETAILS:                     return cmdViewDetails;
         case ID_VIEW_LINEUP:                      return cmdViewLineup;
         case ID_VIEW_BYNAME:                      return cmdViewByname;

         // RecordForm commands
         case ID_RECORD_FIRST:                     return cmdRecordFirst;
         case ID_RECORD_LAST:                      return cmdRecordLast;
         case ID_RECORD_NEXT:                      return cmdRecordNext;
         case ID_RECORD_PREV:                      return cmdRecordPrev;

         }

      }

      return sys_id;

   #elif defined __ECL_OS2__
      // ???
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdEvt
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//         +--cwCmdEvt
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdEvt : public cwCmdCmds {

public:
   // Konstruktor
   cwCmdEvt(const cwCmd& cmd) :
      cwCmdCmds(cmd) { }
   // Konstruktor ueber ID
   cwCmdEvt(int id);
   // Konstruktor ueber ECL-Ereignis-ID
   cwCmdEvt(STDCMDS id);

   // Ereignis ausgeloest ueber Tastatur?
   bool fromKeyboard() const;
   // Ereignis ausgeloest ueber Maus?
   bool fromMouse() const;
   // Ermitteln der Quelle des Ereignisses
   CMDSRC getSource() const;
   // Ermitteln der ID des Ereignisses
   int getId() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdEvt
// ===========================================================================

cwCmdEvt::cwCmdEvt(STDCMDS id)
{
   #if defined __ECL_W32__
      if ( id >= cmdSysClose && id <= cmdSysVScroll ) {
         msg = WM_SYSCOMMAND;
         ul1 = convID(id);
      } else {
         msg = WM_COMMAND;
         v1.us1 = (unsigned short)convID(id);
         v1.us2 = (unsigned short)0;
      }
   #elif defined __ECL_OS2__
      // ???
   #endif
}

cwCmdEvt::cwCmdEvt(int id)
{
   #if defined __ECL_W32__
      msg = WM_COMMAND;
      v1.us1 = (unsigned short)id;
      v1.us2 = (unsigned short)0;
   #elif defined __ECL_OS2__
      // ???
   #endif
}

bool cwCmdEvt::fromKeyboard() const
{
   #if defined __ECL_W32__
      return true; // nicht ermittelbar mit MFC
   #elif defined __ECL_OS2__
      // ???
   #endif
}

bool cwCmdEvt::fromMouse() const
{
   #if defined __ECL_W32__
      return true; // nicht ermittelbar mit MFC
   #elif defined __ECL_OS2__
      // ???
   #endif
}

cwCmdEvt::CMDSRC cwCmdEvt::getSource() const
{
   #if defined __ECL_W32__
      if ( msg == WM_SYSCOMMAND ) {
         return csSystem;
      } else {
         switch ( v1.us2 ) {
         case 0: return csMenu;
         case 1: return csAccel;
         default: return csControl;
         }
      }
   #elif defined __ECL_OS2__
      // ???
   #endif
}

int cwCmdEvt::getId() const
{
   #if defined __ECL_W32__

      if ( msg == WM_SYSCOMMAND ) {
         return convID(ul1 & 0xfff0, true);
      } else {
         return convID(v1.us1, false);
      }

      return v1.us1;

   #elif defined __ECL_OS2__
      // ???
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdUI
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//         +--cwCmdUI
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdUI : public cwCmdCmds {

public:
   cwCmdUI(const cwCmd& cmd) :
      cwCmdCmds(cmd) { }

   // ID des betroffenen Menu-Items, Toolbar-Buttons, o.a. erfragen
   int getId() const;
   // Index des betroffenen Menu-Items, Toolbar-Buttons, o.a. erfragen
   int getIndex() const;

   // Enable-Flag manipulieren (true = freigeben; false = sperren)
   void setEnable(bool enable = true);
   // Enable-Status manipulieren (0 = chkUnchecked, 1 = chkChecked, 2 = chkIndeter)
   void setCheck(int check);
   // Text setzen
   void setText(const cString& text);

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdUI
// ===========================================================================

int cwCmdUI::getId() const
{
   #if defined __ECL_W32__
      // For MFC, l2 points to a CCmdUI object
      return convID(((CCmdUI*)l2)->m_nID, false);
   #else
      // ...
   #endif
}

int cwCmdUI::getIndex() const
{
   #if defined __ECL_W32__
      // For MFC, l2 points to a CCmdUI object
      return ((CCmdUI*)l2)->m_nIndex;
   #else
      // ...
   #endif
}

void cwCmdUI::setEnable(bool enable)
{
   #if defined __ECL_W32__
      // For MFC, l2 points to a CCmdUI object
      ((CCmdUI*)l2)->Enable(enable);
   #else
      // ...
   #endif
}

void cwCmdUI::setCheck(int check)
{
   #if defined __ECL_W32__
      // For MFC, l2 points to a CCmdUI object
      ((CCmdUI*)l2)->SetCheck(check);
   #else
      // ...
   #endif
}

void cwCmdUI::setText(const cString& text)
{
   #if defined __ECL_W32__
      // For MFC, l2 points to a CCmdUI object
      ((CCmdUI*)l2)->SetText(text);
   #else
      // ...
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwCmdScroll
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdScroll
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdScroll : public cwCmd {

public:

   enum BAR {
      barHorz  = 0x0001,   // Kennzeichnet den horizontalen Standard-Scrollbalken
      barVert  = 0x0002    // Kennzeichnet den vertikalen Standard-Scrollbalken
   };

   enum ACTION {
      scrlLeft,            // An den linken Rand scrollen
      scrlLeftLine,        // Um eine "Zeile" nach links scrollen
      scrlLeftPage,        // Um eine "Seite" nach links scrollen
      scrlRight,           // An der rechten Rand scrollen
      scrlRightLine,       // Um eine "Zeile" nach rechts scrollen
      scrlRightPage,       // Um eine "Seite" nach rechts scrollen
      // ---
      scrlTop,             // An den oberen Rand scrollen
      scrlUpLine,          // Um eine "Zeile" nach oben scrollen
      scrlupPage,          // Um eine "Seite" nach oben scrollen
      scrlBottom,          // An den unteren Rand scrollen
      scrlDownLine,        // Um eine "Zeile" nach unten scrollen
      scrlDownPage,        // Um eine "Seite" nach unten scrollen
      // ---
      scrlEnd,             // MouseUp nach wiederholter Scrollbewegung
      // ---
      scrlBoxTracking,     // Scrollbox wird bewegt (Position vgl. getScrollTrackPos)
      scrlBoxReleased,     // Scrollbox wieder losgelassen (Position vgl. getScrollTrackPos)
   };

   // Konstruktor ueber cwCmd-Objekt
   cwCmdScroll(const cwCmd& cmd) :
      cwCmd(cmd) { }
   // Konstruktor ueber spezifische Parameter
   cwCmdScroll(BAR bar, ACTION action);

   // Scroll-Aktion von horizontalem Standard-Scrollbar?
   bool fromHorzScrollBar() const;
   // Scroll-Aktion von vertikalem Standard-Scrollbar?
   bool fromVertScrollBar() const;

   // Scroll-Aktion ermitteln
   ACTION getAction() const;

};

#endif /*__INTERFACE__*/


// Implementierung cwCmdScroll
// ===========================================================================

cwCmdScroll::cwCmdScroll(BAR bar, ACTION action)
{
   #if defined __ECL_W32__
      switch ( bar ) {
      case barHorz:  msg = WM_HSCROLL; break;
      case barVert:  msg = WM_VSCROLL; break;
      }
      switch ( action ) {
      case scrlLeft:          v1.s1 = SB_LEFT; break;
      case scrlLeftLine:      v1.s1 = SB_LINELEFT; break;
      case scrlLeftPage:      v1.s1 = SB_PAGELEFT; break;
      case scrlRight:         v1.s1 = SB_RIGHT; break;
      case scrlRightLine:     v1.s1 = SB_LINERIGHT; break;
      case scrlRightPage:     v1.s1 = SB_PAGERIGHT; break;
      case scrlTop:           v1.s1 = SB_TOP; break;
      case scrlUpLine:        v1.s1 = SB_LINEUP; break;
      case scrlupPage:        v1.s1 = SB_PAGEUP; break;
      case scrlBottom:        v1.s1 = SB_BOTTOM; break;
      case scrlDownLine:      v1.s1 = SB_LINEDOWN; break;
      case scrlDownPage:      v1.s1 = SB_PAGEDOWN; break;
      case scrlBoxTracking:   v1.s1 = SB_THUMBTRACK; break;
      case scrlBoxReleased:   v1.s1 = SB_THUMBPOSITION; break;
      default:                v1.s1 = SB_ENDSCROLL; break;
      }
   #endif
}

bool cwCmdScroll::fromHorzScrollBar() const
{
   #if defined __ECL_OS2__
      return msg == WM_HSCROLL;
   #elif defined __ECL_W32__
      return msg == WM_HSCROLL;
   #else
      return false;
   #endif
}

bool cwCmdScroll::fromVertScrollBar() const
{
   #if defined __ECL_OS2__
      return msg == WM_VSCROLL;
   #elif defined __ECL_W32__
      return msg == WM_VSCROLL;
   #else
      return false;
   #endif
}

cwCmdScroll::ACTION cwCmdScroll::getAction() const
{
   #if defined __ECL_W32__
      if ( msg == WM_VSCROLL ) {
         switch ( v1.s1 ) {
         case SB_TOP:            return scrlTop;
         case SB_LINEUP:         return scrlUpLine;
         case SB_PAGEUP:         return scrlupPage;
         case SB_BOTTOM:         return scrlBottom;
         case SB_LINEDOWN:       return scrlDownLine;
         case SB_PAGEDOWN:       return scrlDownPage;
         case SB_THUMBTRACK:     return scrlBoxTracking;
         case SB_THUMBPOSITION:  return scrlBoxReleased;
         default:                return scrlEnd;
         }
      } else {
         switch ( v1.s1 ) {
         case SB_LEFT:           return scrlLeft;
         case SB_LINELEFT:       return scrlLeftLine;
         case SB_PAGELEFT:       return scrlLeftPage;
         case SB_RIGHT:          return scrlRight;
         case SB_LINERIGHT:      return scrlRightLine;
         case SB_PAGERIGHT:      return scrlRightPage;
         case SB_THUMBTRACK:     return scrlBoxTracking;
         case SB_THUMBPOSITION:  return scrlBoxReleased;
         default:                return scrlEnd;
         }
      }
   #endif

   return scrlEnd;
}


