/*.SH.*/

/*
 *  Headerfile for module ed_font
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ed_font.cpp on Thursday March 21 2002  15:50:48
 */

#ifndef __ed_font__
#define __ed_font__


// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"

class cProfile;
class cwWindow;


// ===========================================================================
// Definition cdFont
// ---------------------------------------------------------------------------
//
// 'font_name' besteht aus einem Namen (nnnn) und einem optionalen Beschrei-
// bungsteil. Name und Beschreibungsteil sind durch ein "|"-Zeichen vonein-
// ander abgetrennt. Der Beschreibungsteil ist nicht interoperabel, zu seiner
// Kennzeichnung beginnt er jedoch mit der Kennung des Ursprungssystems (sss).
//
//    Schreibweise 1: "nnnn"
//    Schreibweise 2: "nnnn|sss:a,b,c,d,e"
//
//  cBase
//   +--cdDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdFont : public cBase {
   friend class ccdFont;

public:

   // Konstruktor
   inline cdFont() { init(); }
   // Destruktor
   ~cdFont();

   // Schriftart ueber Namen (inkl. evtl. Beschreibungsteil) erzeugen
   bool create(cString font_name, int point_size = -1, double factor = 0.0);
   // Freigeben der Schriftart
   void destroy();

   // Name (inkl. evtl. Beschreibungsteil) der Schriftart erfragen
   cString getFontName() const;
   // Beschreibung der Schriftart (Name + Stil) erfragen
   cString getFontDescr() const;
   // Punktgroesse erfragen
   int getPointSize() const;

   // Auswahldialog anzeigen
   bool showDialog(cwWindow *parent = 0);

   // Schriftart aus Profile laden bzw. ueber Auswahldialog
   bool load(cProfile *prf, cString app, cString key, cwWindow *parent = 0, bool show_dlg = false);
   // Sichern der Schriftart im Profile
   void save(cProfile *prf, cString app, cString key) const;


private:

   // Zeiger auf Font-Objekt
   void *font;

   // Initialisierung
   void init();

};


#endif

/*.EH.*/
