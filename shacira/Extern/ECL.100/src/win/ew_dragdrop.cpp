// ===========================================================================
// eb_dragdrop.cpp                               ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwDragDrop       - Basisklasse fuer alle DragDrop-Klassen
//        |
//        +-cwDragSource  - Basisklasse zur Realisierung einer Drag-Quelle
//        |
//        +-cwDragTarget  - Basisklasse zur Realisierung eines Drop-Ziels
//
// ===========================================================================

#include "win/ew_dragdrop.hpp"

#if defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_clip.hpp"
#include "win/ew_windows.hpp"

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
// Definition cwDragDrop
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwDragDrop
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDragDrop : public cBase {
   friend class ccwDragDrop;

public:

   // Destruktor
   virtual ~cwDragDrop();


protected:

   void *_dd;       // Zeiger auf Wrapper-Objekt


   // ECL/win Internas
   // ================

   // Interner Konstruktor
   cwDragDrop(void *dd);

   // Trennen vom Wrapper
   void __disconnect();
   // Eigenen Zeiger auf Wrapper-Objekt ermitteln (non-const)
   void *__getDD();
   // Eigenen Zeiger auf Wrapper-Objekt ermitteln (const)
   const void *__getDD() const;
   // Zeiger auf Wrapper-Objekt ermitteln (statisch, non-const Variante)
   static void *__getDD(cwDragDrop *other);
   // Zeiger auf Wrapper-Objekt ermitteln (statisch, const Variante)
   static const void *__getDD(const cwDragDrop *other);

};

#endif /*__INTERFACE__*/


// Implementierung cwDragDrop
// ===========================================================================

cwDragDrop::cwDragDrop(void *dd)
{
   _dd = dd;
}

cwDragDrop::~cwDragDrop()
{
   #if defined __ECL_W32__
      delete (CCmdTarget*)_dd;
   #endif
}


// ECL/win Internas
// ================

void cwDragDrop::__disconnect()
   { _dd = 0; }
void * cwDragDrop::__getDD()
   { return _dd; }
const void * cwDragDrop::__getDD() const
   { return _dd; }
void * cwDragDrop::__getDD(cwDragDrop *other)
   { return other ? other->_dd : 0; }
const void * cwDragDrop::__getDD(const cwDragDrop *other)
   { return other ? other->_dd : 0; }




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDragSource
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwDragDrop
//      +--cwDragSource
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDragSource : public cwDragDrop {
   friend class ccwDragSource;

public:

   // Konstruktor
   inline cwDragSource() : cwDragDrop(0) { init(); }
   // Destruktor
   ~cwDragSource();

   // Inhalt der DragSource loeschen
   void empty();
   // Daten in DragSource schreiben (empty_ds = true, DS wird vorher geleert)
   bool setData(const cClipboardData& data, bool empty_ds = true);

   // Drag-Operation starten; kehrt erst nach Beendigung oder Abbruch wieder zurueck.
   // Liefert die tatsaechlich ausgefuehrte Operation zurueck (oder opNone)
   cwCmdDrop::DROP_OP doDrag(int source_ops = cwCmdDrop::mayBeAny);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDragSource
// ===========================================================================

cwDragSource::~cwDragSource()
{
}

void cwDragSource::init()
{
   #if defined __ECL_W32__
      _dd = new WCOleDataSource(this);
   #endif
}

void cwDragSource::empty()
{
   #if defined __ECL_W32__
      ((WCOleDataSource*)_dd)->Empty();
   #endif
}

bool cwDragSource::setData(const cClipboardData& data, bool empty_ds)
{
   if ( empty_ds )
      empty();

   cClipboardFormat format = data.getFormat();

   #if defined __ECL_W32__

      if ( format == cClipboardFormat::getFmtText() ) {

         int size = data.getStreamedTextSize();
         if ( size > 0 ) {
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, size);
            if ( __ECL_ASSERT1__(hg != NULL) ) {
               data.getStreamedText(cGlobalMem(hg));
               ((WCOleDataSource*)_dd)->CacheGlobalData(CF_TEXT, hg);
               // GlobalFree durch WCOleDataSource!!!
               return true;
            }
         }

      } else if ( format == cClipboardFormat::getFmtBitmap() ) {

         // ...

      } else if ( !format.getFormat().isEmpty() ) {

         int size = data.getStreamedDataSize();
         if ( size > 0 ) {
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, size);
            if ( __ECL_ASSERT1__(hg != NULL) ) {
               data.getStreamedData(cGlobalMem(hg));
               ((WCOleDataSource*)_dd)->CacheGlobalData(CLIPFORMAT(EclClipboardFormat()), hg);
               // GlobalFree durch WCOleDataSource!!!
               return true;
            }
         }

      }

   #endif

   return false;
}

cwCmdDrop::DROP_OP cwDragSource::doDrag(int source_ops)
{
   #if defined __ECL_W32__
      DROPEFFECT eff = ((WCOleDataSource*)_dd)->DoDragDrop(cwCmdDrop::convSourceOpsToSys(source_ops));
      return cwCmdDrop::convSysToDropOp(eff);
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDropTarget
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwDragDrop
//      +--cwDropTarget
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDropTarget : public cwDragDrop {
   friend class ccwDropTarget;

public:

   // Konstruktor
   inline cwDropTarget() : cwDragDrop(0) { init(); }
   // Destruktor
   ~cwDropTarget();


   // Allgemeines
   // ===========

   // Window mit DropTarget registrieren
   bool registerWindow(cwWindow *win);
   // Window bei DropTarget deregistrieren
   bool deregisterWindow(cwWindow *win);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, wenn eine Drag-Operation ein registriertes Fenster erreicht
   virtual bool onDragEnter(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation ueber einem registrierten Fenster ablaeuft
   virtual bool onDragOver(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Scroll-Operation ueber einem registrierten Fenster ablaeuft
   virtual bool onDragScroll(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation ein registriertes Fenster verlaesst
   virtual bool onDragLeave();
   // Wird aufgerufen, wenn ein Drop ueber einem registrierten Fenster veranlasst wurde
   virtual bool onDrop(cwCmdDrop& cmd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDropTarget
// ===========================================================================

cwDropTarget::~cwDropTarget()
{
   #if defined __ECL_W32__
      ((WCOleDropTarget*)_dd)->Revoke();
   #endif
}

void cwDropTarget::init()
{
   #if defined __ECL_W32__
      _dd = new WCOleDropTarget(this);
   #endif
}


// Allgemeines
// ===========

bool cwDropTarget::registerWindow(cwWindow *win)
{
   if ( __ECL_ASSERT1__(win != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_win = (CWnd*)ccwWindow::__getWnd(win);
         return
            __ECL_ASSERT1__(mfc_win != 0)
         && __ECL_ASSERT1__(((WCOleDropTarget*)_dd)->Register(mfc_win));
      #endif
   }

   return false;
}

bool cwDropTarget::deregisterWindow(cwWindow *win)
{
   if ( __ECL_ASSERT1__(win != 0) ) {
      #if defined __ECL_W32__
         // TBD: Richtig so? Oder Revoke besser nicht hier aufrufen?!
         CWnd *mfc_win = (CWnd*)ccwWindow::__getWnd(win);
         if ( __ECL_ASSERT1__(mfc_win != 0) )
            ((WCOleDropTarget*)_dd)->Revoke();
      #endif
   }

   return win != 0;
}


// Hinzugefuegte Events
// ====================

bool cwDropTarget::onDragEnter(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwDropTarget::onDragOver(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwDropTarget::onDragScroll(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwDropTarget::onDragLeave()
{
   return false;
}

bool cwDropTarget::onDrop(cwCmdDrop& /*cmd*/)
{
   return false;
}


