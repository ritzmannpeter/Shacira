// ===========================================================================
// ed_context.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//     |
//     +--cdContext              - Kontext fuer Zeichenoperationen
//
// ===========================================================================

#include "draw/ed_context.hpp"

#if defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_object.hpp"
#include "draw/ed_base.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdContext
// ---------------------------------------------------------------------------
//
// Kontext fuer Zeichenoperationen.
//
//  cEclObject
//   +--cdContext
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdContext : public cEclObject {
   ECL_DECLARE(cdContext, cEclObject)
   friend class ccdContext;

public:

   // Destruktor
   ~cdContext();


   // Allgemeines
   // ===========

   // Ungueltigen Bereich ermitteln (in Geraetekoordinaten)
   const cdRect& getRedrawArea() const;
   // Muss der Hintergrund geloescht werden?
   bool mustEraseBkgnd() const;


protected:

   // Konstruktor (nur fuer Ableitungen)
   cdContext();

   // Kontext setzen (Systemabhaengig)
   void setContext(void *ctxt, bool must_free = false);
   // Kontext erfragen (Systemabhaengig)
   void *getContext() const;

   // Ungueltigen Bereich setzen
   void setRedrawArea(const cdRect& redraw_area);
   // Flag "Hintergrund loeschen" setzen
   void setEraseBkgnd(bool erase_bkgnd);


private:

   // Zeiger auf Font-Objekt
   struct CONTEXT_INFO;
   CONTEXT_INFO *info;

};

#endif /*__INTERFACE__*/


// Implementierung cdContext
// ===========================================================================

   struct cdContext::CONTEXT_INFO {
      CONTEXT_INFO();
      ~CONTEXT_INFO();

      cdRect redraw_area;     // Ungueltiger Bereich (in Geraetekoordinaten)
      bool erase_bkgnd;       // Muss der Hintergrund geloescht werden?

      #if defined __ECL_W32__
         CDC *dc;             // Zeiger auf Display-Context
         bool must_free_dc;   // Muss der DC freigegeben werden?
      #endif
   };

cdContext::cdContext()
{
   info = new0 CONTEXT_INFO;
}

cdContext::~cdContext()
{
   delete info;
}

cdContext::CONTEXT_INFO::CONTEXT_INFO()
{
   #if defined __ECL_W32__
      dc = 0;
      must_free_dc = false;
   #endif
   erase_bkgnd = false;
}

cdContext::CONTEXT_INFO::~CONTEXT_INFO()
{
   #if defined __ECL_W32__
      if ( must_free_dc ) {
         delete dc; dc = 0;
      }
   #endif
}


// Allgemeines
// ===========

void cdContext::setContext(void *ctxt, bool must_free)
{
   #if defined __ECL_W32__
      info->dc = (CDC*)ctxt;
      info->must_free_dc = must_free;
   #endif
}

void * cdContext::getContext() const
{
   #if defined __ECL_W32__
      return info->dc;
   #endif
}

void cdContext::setRedrawArea(const cdRect& redraw_area)
{
   info->redraw_area = redraw_area;
}

const cdRect& cdContext::getRedrawArea() const
{
   return info->redraw_area;
}

void cdContext::setEraseBkgnd(bool erase_bkgnd)
{
   info->erase_bkgnd = erase_bkgnd;
}

bool cdContext::mustEraseBkgnd() const
{
   return info->erase_bkgnd;
}

