/*.SH.*/

/*
 *  Headerfile for module er_prnform
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  er_prnform.cpp on Tuesday August 21 2001  18:01:19
 */

#ifndef __er_prnform__
#define __er_prnform__


// Headerfiles
// ===========================================================================

#include "base/eb_geo2d.hpp"
#include "rep/er_prnspool.hpp"


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


#endif

/*.EH.*/
