// ===========================================================================
// er_prnform.cpp                                ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--crPrnForm             - Beschreibung eines Druckformulars
//     |
//     +--crPrnFormMgr          - Verwaltung der Druckformulare einer Queue
//
// ===========================================================================

#include "rep/er_prnform.hpp"

#if defined __ECL_W32__
   #include "win/system/mfc/stdafx.h"
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

#include "base/eb_geo2d.hpp"
#include "rep/er_prnspool.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnForm
// ---------------------------------------------------------------------------
//
// Beschreibung eines Druckformulars. Alle Groessen in mm.
//
//  cBase
//   +--crPrnForm
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnForm : public cBase {

public:

   // Default-Konstruktor
   crPrnForm()
      { current = false; }
   // Normaler Konstruktor
   crPrnForm(cString name, const c2dBox& size_rect, const c2dBox& clip_rect, bool current)
      { crPrnForm::name = name;
        crPrnForm::size_rect = size_rect;
        crPrnForm::clip_rect = clip_rect;
        crPrnForm::current = current; }
   // Copy-Konstruktor
   crPrnForm(const crPrnForm& other)
      { crPrnForm::name = other.name;
        crPrnForm::size_rect = other.size_rect;
        crPrnForm::clip_rect = other.clip_rect;
        crPrnForm::current = other.current; }
   // Zuweisungsoperator
   crPrnForm& operator=(const crPrnForm& other)
      { crPrnForm::name = other.name;
        crPrnForm::size_rect = other.size_rect;
        crPrnForm::clip_rect = other.clip_rect;
        crPrnForm::current = other.current;
        return *this; }

   // Name des Formulars
   const cString& getName() const
      { return name; }

   // Papierbreite in mm
   double getWidth() const
      { return size_rect.rt.x - size_rect.lb.x; }
   // Papierhoehe in mm
   double getHeight() const
      { return size_rect.rt.y - size_rect.lb.y; }
   // Papiergroesse in mm
   const c2dBox& getRect() const
      { return size_rect; }

   // Breite des druckbaren Bereichs in mm
   double getClipWidth() const
      { return clip_rect.rt.x - clip_rect.lb.x; }
   // Hoehe des druckbaren Bereichs in mm
   double getClipHeight() const
      { return clip_rect.rt.y - clip_rect.lb.y; }
   // Druckbarer Bereich in mm
   const c2dBox& getClipRect() const
      { return clip_rect; }

   // Formular momentan ausgewaehlt?
   bool isCurrent() const
      { return current; }

private:
   cString name;
   c2dBox size_rect;
   c2dBox clip_rect;
   bool current;

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition crPrnFormMgr
// ---------------------------------------------------------------------------
//
// Verwalten von Formularen eines crPrnQueue-Objektes.
//
//  cBase
//   +--crPrnFormMgr
//
// ===========================================================================

class __ECL_DLLEXPORT__ crPrnFormMgr : public cBase {

public:

   // Konstruktor
   crPrnFormMgr(const crPrnQueue& queue);
   // Destruktor
   ~crPrnFormMgr();


   // Allgemeines
   // ===========

   // Assoziierte Queue erfragen
   crPrnQueue getAssociatedQueue() const
      { return queue; }


   // Formulare
   // =========

   // Erfragen der Anzahl registrierter Formulare
   inline int getFormCount() const
      { return form_count; }

   // Suchen eines Formulars ueber dessen Namen
   int findForm(cString form_name) const;
   // Erfragen eines Formulares
   crPrnForm getForm(int form_no) const;
   // Erfragen des aktuellen Formulares der assoziierten Queue
   crPrnForm getCurrentForm() const;


private:

   crPrnQueue queue;    // Assoziierte Queue
   int form_count;      // Anzahl Formulare
   crPrnForm *forms;    // Feld mit Formularobjekten

};

#endif /*__INTERFACE__*/


// Implementierung crPrnFormMgr
// ===========================================================================

#if defined __ECL_W32__

   static void * GetDevCap(const crPrnQueue& queue, const crPrnDriver& driver, int dev_cap, int& count, int size)
   {
      cString queue_name = queue.getName();
      cString port_name = queue.getPortName();
      DEVMODE *dm = (DEVMODE*)driver.getData();

      count = DeviceCapabilities(queue_name, port_name, WORD(dev_cap), 0, dm);

      if ( count <= 0 )
         return 0;

      char *buffer = (char*)malloc(count * size);
      count = DeviceCapabilities(queue_name, port_name, WORD(dev_cap), buffer, dm);

      if ( __ECL_ASSERT1__(count > 0) ) {
         return buffer;
      } else {
         if ( buffer) free(buffer);
         return 0;
      }
   }

#endif

crPrnFormMgr::crPrnFormMgr(const crPrnQueue& queue)
{
   crPrnFormMgr::queue = queue;
   crPrnFormMgr::form_count = 0;
   crPrnFormMgr::forms = 0;

   if ( __ECL_ASSERT1__(queue.isInitialized()) ) {

      #if defined __ECL_W32__

         int paper_names_count, papers_count, paper_size_count;
         crPrnDriver driver = queue.getDriver();

         char *paper_names = (char*)GetDevCap(queue, driver, DC_PAPERNAMES, paper_names_count, 64);
         WORD *papers = (WORD*)GetDevCap(queue, driver, DC_PAPERS, papers_count, sizeof(WORD));
         POINT *paper_sizes = (POINT*)GetDevCap(queue, driver, DC_PAPERSIZE, paper_size_count, sizeof(POINT));

         if ( __ECL_ASSERT1__(paper_names != 0 && papers != 0 && paper_sizes != 0)
           && __ECL_ASSERT1__(paper_names_count == papers_count && paper_size_count == papers_count) )
         {
            form_count = papers_count;
            forms = new crPrnForm[form_count];

            #define __Debug_FormMgr__
            #ifdef __Debug_FormMgr__
               DbgOut(0, "Forms defined for queue %s (default = %s):",
                  (const char *)queue.getName(), (const char *)queue.getFormName());
            #endif

            cString default_form_name = queue.getFormName();

            for ( int i = 0 ; i < form_count ; i++ ) {
               POINT& size = paper_sizes[i];
               c2dBox size_rect = c2dBox(0, 0, double(size.x)/10.0, double(size.y)/10.0);
               c2dBox clip_rect = c2dBox(0, 0, double(size.x)/10.0, double(size.y)/10.0);
               cString form_name = (const char *)&paper_names[i*64];
               bool is_current = form_name.compare(default_form_name, default_form_name.getLength()) == 0;
               forms[i] = crPrnForm(form_name, size_rect, clip_rect, is_current);

               #ifdef __Debug_FormMgr__
                  DbgOut(0, "   [%c] %02d: %s (%g x %g mm)",
                     is_current ? 'X' : ' ', i, (const char *)form_name,
                     size_rect.getWidth(), size_rect.getHeight());
               #endif
            }

         }

         if ( paper_names ) free(paper_names);
         if ( papers      ) free(papers);
         if ( paper_sizes ) free(paper_sizes);

      #elif defined __ECL_W32__x /* Win2000 only */

         HANDLE hPrinter;
         char prn_name[128]; strxcpy(prn_name, queue.getName(), sizeof prn_name);

         if ( ::OpenPrinter(prn_name, &hPrinter, 0) ) {

            DWORD bytes_needed = 0, forms_returned;
            ::EnumForms(hPrinter, 1, 0, 0, &bytes_needed, &forms_returned);

            if ( bytes_needed > 0 ) {
               FORM_INFO_1 *fi = (FORM_INFO_1*)new char[bytes_needed];
               ::EnumForms(hPrinter, 1, (BYTE*)fi, bytes_needed, &bytes_needed, &forms_returned);

               form_count = forms_returned;
               forms = new crPrnForm[form_count];

               #define __Debug_FormMgr__
               #ifdef __Debug_FormMgr__
                  DbgOut(0, "Forms defined for queue %s (default = %s):",
                     (const char *)queue.getName(), (const char *)queue.getFormName());
               #endif

               for ( unsigned int i = 0 ; i < forms_returned ; i++ ) {
                  SIZEL& size = fi[i].Size;
                  RECTL& clip = fi[i].ImageableArea;
                  c2dBox size_rect = c2dBox(0, 0,
                                            double(size.cx)/1000.0, double(size.cy)/1000.0);
                  c2dBox clip_rect = c2dBox(double(clip.left)/1000.0, double(clip.bottom)/1000.0,
                                            double(clip.right)/1000.0, double(clip.top)/1000.0);
                  cString form_name = fi[i].pName;
                  bool is_current = form_name == queue.getFormName();
                  forms[i] = crPrnForm(form_name, size_rect, clip_rect, is_current);

                  #ifdef __Debug_FormMgr__
                     DbgOut(0, "   [%c] %02d: %s", is_current ? 'X' : ' ', i, (const char *)form_name);
                  #endif
               }

               delete[] fi;

            }

            ::ClosePrinter(hPrinter);

         }

      #else
         // ...
      #endif

   }
}

crPrnFormMgr::~crPrnFormMgr()
{
   delete[] forms;
}

int crPrnFormMgr::findForm(cString form_name) const
{
   int form_count = getFormCount();

   for ( int i = 0 ; i < form_count ; i++ ) {
      crPrnForm form = getForm(i);
      if ( form_name == form.getName() )
         return i;
   }

   return -1;
}

crPrnForm crPrnFormMgr::getForm(int form_no) const
{
   if ( form_no >= 0 && form_no < form_count) {
      // Formulare erfragen
      return forms[form_no];
   } else {
      // Standard-Formulare erfragen
      if ( form_no == 1 ) {
         return crPrnForm("US Letter", c2dBox(0,0,216,279), c2dBox(10,10,206,269), false);
      } else {
         return crPrnForm("DIN A4", c2dBox(0,0,211,279), c2dBox(10,10,201,269), true);
      }
   }
}

crPrnForm crPrnFormMgr::getCurrentForm() const
{
   int form_count = getFormCount();

   for ( int i = 0 ; i < form_count ; i++ ) {
      crPrnForm form = getForm(i);
      if ( form.isCurrent() )
         return form;
   }

   // Falls kein aktuelles Formular definiert: Erstes Formular zurueckliefern
   return getForm(0);
}


