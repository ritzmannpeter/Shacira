// ===========================================================================
// er_repelem.cpp                                ECL (ET's tiny Class Library)
//                                                         Autor: Udo Pfrengle
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cRepElem              - Basisklasse fuer alle Report-Komponenten.
//         |
//         +--cRepNewPage       - Erzwingt einen Seitenvorschub.
//         |
//         +--cRepGroup         - Gruppe von cRepElem's.
//         |   |
//         |   +--cRepLine      - Gruppe horizontal angeordneter Elemente.
//         |   |
//         |   +--cRepColumn    - Gruppe vertikal angeordneter Elemente.
//         |   |
//         |   +--cRepTable     - Gruppe vertikal angeordneter Elemente, wo-
//         |                      bei das erste Element auf jeder neuen Seite
//         |                      wiederholt wird.
//         |
//         +--cRepText          - Basis-Element fuer Texte.
//         |   |
//         |   +--cRepStatText  - Einfache statische Texte.
//         |   |
//         |   +--cRepVarText   - Variable Texte.
//         |   |
//         |   +--cRepVariable  - Text-Variablen.
//         |
//         +--cRepGraphic       - Graphische Elemente.
//         |
//         +--cRepAbstract      - Basisklasse fuer Verwaltungselemente.
//             |
//             +--cRepChgText   - Synchrone Aenderung von cRepText-Elementen.
//
// ===========================================================================

#include "rep/er_repelem.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>
#include <ctype.h>




GLOBAL const double Rep_RowSpc = 1.2;




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"
#include "draw/ed_space.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

//  FBS_DEBUG_REP | Debug-Variante
// ---------------+-----------------------------------------------
//        0       | Keine speziellen Debug-Ausgaben
//  Bit 0 gesetzt | Rahmen um jedes cRepElem zeichnen
//  Bit 1 gesetzt | Zusaetzliche Ausgabe der Rahmengroesse

static int DebugReport = getenv("FBS_DEBUG_REP") ?
   atoi(getenv("FBS_DEBUG_REP")) : 0;




// Globale Funktionen
// ===========================================================================

GLOBAL c2dSize __ECL_DLLEXPORT__ QueryTextSize(cdSpace *space, const char *text, double width, double row_spc)
{
   c2dSize size(0,0);
   double font_height = space->queryAvgCharHeight();
   const char *tmo_cp1 = NULL, *tmo_cp2 = NULL;

   if ( is_zero(width) ) width = 1e42;
   if (text) {
      char buf[4096], *bufp=buf, *last_brk = NULL;
      do {                  // Schleife ueber alle Zeilen
         double last_width = 0;
         while ( true ) {      // Schleife ueber alle Zeichen einer Zeile
            // Kopiere Zeichen, behandle \r\n wie \n
            if ( '\r' == *text ) {
               if ( '\n' == text[1] ) ++text;
               *bufp = '\n';
            } else {
               *bufp = *text;
            }
            if (*text) ++text;
            // Gelegenheit zum Zeilenumbruch ?
            if ( !*bufp || isspace(*bufp) || '\n' == *bufp
              || bufp>buf && ( '-' == bufp[-1] || '~' == bufp[-1] ) )
            {
               double curr_width = space->queryTextWidth(buf, bufp-buf);
               // Test, ob noch Platz hat
               if (curr_width > width) {
                  /* TEST */
                  if ( bufp == tmo_cp1 && text == tmo_cp2 ) {
                     cBase::DbgError("Endless loop in QueryTextSize (width=%g, curr_width=%g)- aborted", width, curr_width);
                     size.cx = width;
                     size.cy += font_height * row_spc;
                     return size;
                  } else {
                     tmo_cp1 = bufp;
                     tmo_cp2 = text;
                  }
                  /* TEST */
                  // passt nicht mehr: Zeile ausgeben
                  if ('\n' == *bufp) --bufp, --text;
                  break;
               } else if (last_brk > buf && '~' == last_brk[-1]) {
                  // ungenutzes voriges Trennvorschlagszeichen loeschen
                  for ( ; last_brk <= bufp; last_brk++ )
                     last_brk[-1] = last_brk[0];
                  --bufp;
               }
               last_brk = bufp;
               last_width = curr_width;
               if ('\n' == *bufp || !*bufp) break; // Zeile ausgeben!
            }
            ++bufp;
         }
         if (!last_brk) last_brk = bufp;
         if (size.cx < last_width)
             size.cx = last_width;
         size.cy += font_height * row_spc;
         char *start = last_brk;
         bufp[1] = '\0';   // Verhindere, dass ueber das akt. Ende hinaus gelesesn wird
         if ('\n'==*last_brk) {
            ++start;   // Leerstellen nach '\n' erhalten
         } else if (*start) {
            while (' ' == *start || '\t' == *start) ++start;
         }
         // Kopiere den umgebrochenen Rest der Zeile
         bufp=buf;
         while ( (*bufp = *start) != NULL ) ++bufp, ++start;
         last_brk = (bufp-2 >= buf && '~' == bufp[-2]) ? bufp - 1 : bufp;
      } while( bufp!=buf || *text );
   }

   return size;
}


GLOBAL c2dSize __ECL_DLLEXPORT__ DrawTextAt(cdSpace *space, c2dPoint pos, const char *text, double width, double row_spc )
{
   c2dSize size(0,0);
   double font_height = space->queryAvgCharHeight();
   const char *tmo_cp1 = NULL, *tmo_cp2 = NULL;

   if ( is_zero(width) ) width = 1e42;
   if (text) {
      char buf[4096], *bufp=buf, *last_brk = NULL;
      do {                  // Schleife ueber alle Zeilen
         double last_width = 0;
         while (true) {      // Schleife ueber alle Zeichen einer Zeile
            // Kopiere Zeichen, behandle \r\n und \r wie \n
            if ( '\r' == *text ) {
               if ( '\n' == text[1] ) ++text;
               *bufp = '\n';
            } else {
               *bufp = *text;
            }
            if (*text) ++text;
            // Gelegenheit zum Zeilenumbruch ?
            if ( !*bufp || isspace(*bufp) || '\n' == *bufp
              || bufp>buf && ('-' == bufp[-1] || '~'==bufp[-1]))
            {
               double curr_width = space->queryTextWidth(buf, bufp-buf);
               // Test, ob noch Platz hat
               if (curr_width > width) {
                  /* TEST */
                  if ( bufp == tmo_cp1 && text == tmo_cp2 ) {
                     cBase::DbgError("Endless loop in DrawTextAt - aborted");
                     size.cx = width;
                     size.cy += font_height * row_spc;
                     return size;
                  } else {
                     tmo_cp1 = bufp;
                     tmo_cp2 = text;
                  }
                  /* TEST */
                  // passt nicht mehr: Zeile ausgeben
                  if ('\n' == *bufp) --bufp, --text;
                  break;
               } else if (last_brk > buf && '~' == last_brk[-1]) {
                  // ungenutzes voriges Trennvorschlagszeichen loeschen
                  for ( ; last_brk <= bufp; last_brk++ )
                     last_brk[-1] = last_brk[0];
                  --bufp;
               }
               last_brk = bufp;                    // aktuelle Trennchance
               last_width = curr_width;            // Breite bis hierher
               if ('\n' == *bufp || !*bufp) break; // Zeile ausgeben!
            }
            ++bufp;
         }
         if (!last_brk) {
            last_brk = bufp;
         } else if ( '~' == last_brk[-1]) {
            last_brk[-1] = '-';                    // Werïs lieber so mag
         }
         space->moveTo(pos);
         space->draw(buf, last_brk-buf);
         if (size.cx < last_width)
             size.cx = last_width;
         size.cy += font_height * row_spc;
         pos.y   -= font_height * row_spc;

         // loesche Leerstellen am Zeilenanfang
         bufp[1] = '\0';                           // sicher terminieren
         char *start = last_brk;
         if ('\n'==*last_brk) {
            ++start;                // Leerstellen nach '\n' erhalten
         } else if (*start) {
            while (' ' == *start || '\t' == *start) ++start;
         }

         // Kopiere den umgebrochenen Rest der Zeile
         bufp=buf;
         while ( (*bufp = *start) != NULL ) ++bufp, ++start;
         last_brk = (bufp-2 >= buf && '~' == bufp[-2]) ? bufp - 1 : bufp;
      } while ( bufp!=buf || *text );
   }

   return size;
}


GLOBAL c2dSize __ECL_DLLEXPORT__ QueryAvgCharSize(cdSpace *space)
{
   double cx, cy;
   space->queryAvgCharSize(cx, cy);
   return c2dSize(cx, cy);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepElem
// ---------------------------------------------------------------------------
//
// Basisklasse fuer alle Komponenten eines Reports
//
// Ein cRepElem ist ein rechteckiger Bereich innerhalb eines Reports mit den
// Attributen:
//    Ausrichtung des Inhaltes
//    Rahmenart und Abstand des Rahmens vom Inhalt
//    Groesse (fest vorgegeben, dynamisch (je nach Inhalt) oder zoombar
//    Abstand zum naechsten Element
//
// Methoden:
//    QuerySize : Erfragt den (vermutlich) benoetigten Platz
//    QueryActSize: Erfragt den tatsaechlich benoetigten Platz
//    SetSize: Weist dem Element eine feste Groesse zu
//    Restart: Nachricht fuer Elemente mit 'Gedaechtnis':
//                Neuanfang (true) / Neue Seite (false)
//    Draw:    Element soll sich zeigen. Diese Methode nennt die Position
//             der linken oberen Ecke an der das Element gezeichnet werden
//             soll. Das Element muss (!) diese Position zur rechten unteren
//             Ecke weiterruecken.
//    PageBreak: Methode, die ggf. einen Seitenumbruch durchfuehrt. Hier (im
//             cRepElem) nur als Durchreiche zum Besitzer realisert. D.h.,
//             das cRepElem laesst seinen Besitzer ggf. den Seitenumbruch durch-
//             fuehren.
//
// cBase
//  +--cRepElem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepElem : /*public cSaveDynStorage,*/ public cBase {
   friend class cRepGroup;

public:
   enum WHERE { NONE=0, LEFT=1, RIGHT=2,
                VERTICAL=LEFT|RIGHT, H_CENTER=VERTICAL,
                TOP=4, TOPLEFT, TOPRIGHT, TOPVERTICAL,
                BOTTOM=8, BOTTOMLEFT, BOTTOMRIGHT, BOTTOMVERTICAL, BOTTOMTOP,

                TOPCENTER=TOPVERTICAL, BOTTOMCENTER=BOTTOMVERTICAL,
                HORIZONTAL=TOP|BOTTOM, V_CENTER=HORIZONTAL,
                ALL=HORIZONTAL|VERTICAL,
                CENTER=H_CENTER|V_CENTER
              };
   enum FLOWCTRL { NOWRAP, WRAP };

   // Klassenparameter
   static double default_frame_dist;      // Voreinstellung: Abstand des Rahmens vom Feldinhalt
   static cdLineStyle default_line_type;  // Voreinstellung: Linienart
   static FLOWCTRL default_flow;          // Voreinstellung: Umbruch erlaubt
   cRepGroup*owner;                       // Besitzer des Feldes
   c2dSize wanted_size;                   // Durch Inhalt bestimmte Groesse
   c2dSize act_size;                      // tatsaechliche Groesse
   bool zoomable;                         // Feld darf vergroessert werden
   bool handle_break;                     // Element erkennt selbst, ob es noch auf
                                          // die aktuelle Seite passt
   WHERE align;
   WHERE frame;
   cdLineStyle line_type;                 // Linienart
   FLOWCTRL flow;
   double frame_dist;                     // Abstand des Rahmens zum Inhalt
   c2dSize  dist;                         // Abstand zum Vorgaenger in mm
   double size;                           // Groesse in mm (Breite bzw. Hoehe)

   static void setDefaultFrameDist(double dfd);
   static double getDefaultFrameDist();

   inline cRepElem(cRepGroup* owner = 0,
                   double size = 0,
                   WHERE align = NONE,
                   WHERE frame = NONE,
                   const c2dSize& dist = c2dSize(0,0))
   {
      init(owner, size, align, frame, dist);
   }

   virtual ~cRepElem();
   bool Align(c2dPoint& pos, double x_corr = 0, bool corr_pos = true);
   virtual bool /*out*/ PageBreak(bool& out, bool force, cdSpace *space, c2dPoint& pos);
   virtual void Draw(bool& out, cdSpace *space, c2dPoint& pos);
   virtual c2dSize& QuerySize(cdSpace *space);
   virtual c2dSize& QueryActSize(cdSpace *space);
   virtual void SetSize(const c2dSize& s);
   virtual void Restart(bool full);

   bool AdjacentToFrameBottom() const;
   bool AdjacentToFrameTop() const;
   bool AdjacentToFrameRight() const;
   bool AdjacentToFrameLeft() const;

private:
   cRepElem *prev, *next;
   void init(cRepGroup* owner, double size, WHERE align, WHERE frame, const c2dSize& dist);

};

#endif /*__INTERFACE__*/


// Implementierung cRepElem
// ===========================================================================

double cRepElem::default_frame_dist = 2.0;
cdLineStyle cRepElem::default_line_type = cdLineStyle::Solid; //Dot;
cRepElem::FLOWCTRL cRepElem::default_flow = cRepElem::WRAP;

void cRepElem::init(cRepGroup* _owner, double _size, WHERE _align, WHERE _frame, const c2dSize& _dist)
{
   align       =  _align;
   frame       =  _frame;
   frame_dist  =  default_frame_dist;
   line_type   =  default_line_type;
   flow        =  default_flow;
   dist        =  _dist;
   size        =  _size <= 0 ? 0 : _size;
   zoomable    =  !_size;
   handle_break = false;  // atomare Elemente sind unzerbrechlich

   // 08.09.96 -TE- Besser initialisieren, da wanted_size anscheinend auch
   //   benutzt wird, _bevor_ QuerySize aufgerufen wird (!?!)
   wanted_size.cx = dist.cx;
   wanted_size.cy = dist.cy;

   prev = next = NULL;
   owner = NULL;

   if ( _owner )
      _owner->AddField(this);
}

cRepElem::~cRepElem()
{
   if ( owner )
      owner->RemoveField(this);
}

void cRepElem::setDefaultFrameDist(double dfd)
{
   default_frame_dist = dfd;
}

double cRepElem::getDefaultFrameDist()
{
   return default_frame_dist;
}

c2dSize& cRepElem::QuerySize(cdSpace * /*space*/)
{
   wanted_size.cx = dist.cx;
   wanted_size.cy = dist.cy;

   if ( AdjacentToFrameTop() )
      wanted_size.cy += frame_dist;
   if ( AdjacentToFrameBottom() )
      wanted_size.cy += frame_dist;
   if ( AdjacentToFrameLeft() )
      wanted_size.cx += frame_dist;
   if ( AdjacentToFrameRight() )
      wanted_size.cx += frame_dist;

   return wanted_size;
}

c2dSize& cRepElem::QueryActSize(cdSpace * /*space*/)
{
   return act_size;
}

bool cRepElem::AdjacentToFrameLeft() const
{
   if ( LEFT & frame )  {
      return true;
   } else if ( owner ) {
      if ( owner->IsHorizontal() && prev ) {
         return !!(RIGHT & prev->frame);
      } else {
         return owner->AdjacentToFrameLeft();
      }
   }
   return false;
}

bool cRepElem::AdjacentToFrameRight() const
{
   if ( RIGHT & frame )  {
      return true;
   } else if ( owner ) {
      if ( owner->IsHorizontal() && next ) {
         return LEFT & next->frame;
      } else {
         return owner->AdjacentToFrameRight();
      }
   }
   return false;
}

bool cRepElem::AdjacentToFrameTop() const
{
   if ( TOP & frame )  {
      return true;
   } else if ( owner ) {
      if ( owner->IsVertical() && prev ) {
         return !!(BOTTOM & prev->frame);
      } else {
         return owner->AdjacentToFrameTop();
      }
   }
   return false;
}

bool cRepElem::AdjacentToFrameBottom() const
{
   if ( BOTTOM & frame )  {
      return true;
   } else if ( owner ) {
      if ( owner->IsVertical() && next ) {
         return !!(TOP & next->frame);
      } else {
         return owner->AdjacentToFrameBottom();
      }
   }
   return false;
}

void cRepElem::Draw( bool& out, cdSpace *space, c2dPoint& pos )
{
   if ( out ) {
      if ( DebugReport & 0x0001 ) {
         c2dPoint sp(pos.x, pos.y);
         c2dPoint ep(pos.x + (act_size.cx - dist.cx), pos.y - (act_size.cy - dist.cy));
         space->setColor(cdColor::Blue);
         space->draw(c2dBox(sp, ep));
         space->setColor(cdColor::Black);
      }
      if ( DebugReport & 0x0002 ) {
         fprintf(stderr, "cRepElem::Draw: %g,%g, %g,%g, %g,%g, %g,%g\n",
            pos.x, pos.y, act_size.cx, act_size.cy, dist.cx, dist.cy,
            (act_size.cx - dist.cx), (act_size.cy - dist.cy));
      }
   }

   if ( frame && out ) {
      c2dPoint sp(pos.x, pos.y);
      c2dPoint ep(pos.x + (act_size.cx - dist.cx), pos.y - (act_size.cy - dist.cy));

      space->setLineStyle(line_type);
      if ( LEFT & frame )   space->draw(c2dLineSeg(sp.x, sp.y, sp.x, ep.y));
      if ( TOP & frame )    space->draw(c2dLineSeg(sp.x, sp.y, ep.x, sp.y));
      if ( RIGHT & frame )  space->draw(c2dLineSeg(ep.x, ep.y, ep.x, sp.y));
      if ( BOTTOM & frame ) space->draw(c2dLineSeg(ep.x, ep.y, sp.x, ep.y));
   }

   pos.x += act_size.cx;
   pos.y -= act_size.cy;
}

bool /*ok*/ cRepElem::Align(c2dPoint &pos, double x_corr, bool corr_pos)
{
   // Rahmenkorrektur der Position auch bei 'zoomable'-Elementen
   // durchfuehren

   if ( corr_pos ) {
      if ( AdjacentToFrameLeft() )
         pos.x += frame_dist;
      if ( AdjacentToFrameRight() )
         pos.x += frame_dist;
      if ( AdjacentToFrameTop() )
         pos.y -= frame_dist;
   }

   // Die restlichen Berechnungen nur durchfuehren, wenn Element
   // nicht 'zoomable' oder x_corr angegeben

   if ( !zoomable || x_corr > 0 ) {

      // Berechne Nettogroesse abzgl. Platz fuer Rahmen und Abstand
      // zum Naechsten

      c2dSize wanted = wanted_size;   // retten
      c2dSize remain = act_size - wanted - cRepElem::QuerySize(NULL);
      wanted_size = wanted;         // restaurieren

      if ( remain.cx > 0 ) {
         switch ( align & H_CENTER ) {
          case RIGHT:      pos.x += remain.cx - x_corr; break;
          case H_CENTER:   pos.x += remain.cx / 2.0; break;
          case LEFT:       break;
         }
      }

      if ( remain.cy > 0 ) {
         switch ( align & V_CENTER ) {
          case NONE:       break;
          case TOP:        break;
          case V_CENTER:   pos.y -= remain.cy / 2.0; break;
          case BOTTOM:     pos.y -= remain.cy; break;
         }
      }

      return remain.cx >= 0.0 && remain.cy >= 0.0;

   }

   return true;
}

bool /*done*/ cRepElem::PageBreak(bool& out, bool /*force*/, cdSpace *space, c2dPoint& pos)
{
   return owner ? owner->PageBreak(out, false, space, pos) : false;
}

void cRepElem::SetSize(const c2dSize& s)
{
   act_size.cx = s.cx >= 0.0 ? s.cx : wanted_size.cx;
   act_size.cy = s.cy >= 0.0 ? s.cy : wanted_size.cy;

   //#define __Test_SetSize_Params__
   #ifdef __Test_SetSize_Params__
      if ( act_size.cx > 50000.0 || act_size.cx < -1.0
        || act_size.cy > 50000.0 || act_size.cy < -1.0 )
      {
         fprintf(stderr, ">>>> %g,%g = %g,%g || %g,%g\n",
            act_size.cx, act_size.cy, s.cx, s.cy, wanted_size.cx, wanted_size.cy);
      }
   #endif
}

void cRepElem::Restart(bool /*full*/)
{
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepNewPage
// ---------------------------------------------------------------------------
//
// Erzwingt einen Seitenvorschub.
//
// cBase
//  +--cRepElem
//      +--cRepNewPage
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepNewPage : public cRepElem {

public:
   inline cRepNewPage(cRepGroup* owner) :
      cRepElem(owner)
   {
      handle_break = true;
   }

   void Draw(bool& out, cdSpace *space, c2dPoint& pos);

};

#endif /*__INTERFACE__*/


// Implementierung cRepNewPage
// ===========================================================================

void cRepNewPage::Draw(bool& out, cdSpace *space, c2dPoint& pos)
{
   if ( owner )
      owner->PageBreak(out, true, space, pos);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepGroup
// ---------------------------------------------------------------------------
//
// cRepGroup ist eine geordnete Sammlung von RepElems. Eine cRepGroup
// beinhaltet eine Liste von Reportelementen und kann diese entweder
// negeneinander (horizontal == true) oder untereinander darstellen. Eine
// cRepGroup, deren Elemente untereinander dargestellt werden, unterstuetzt
// autom. den Seitenumbruch, d.h. vor der Anzeige jedes Elementes innerhalb
// der Gruppe wird geprueft, ob es auf der akt. Seite noch Platz findet.
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepGroup : public cRepElem {

public:
   long font_idx;

   inline cRepGroup(cRepGroup* owner = NULL,
                    bool horz = true,
                    double size = 0,
                    WHERE align = NONE,
                    WHERE frame = NONE,
                    const c2dSize& dist = c2dSize(0,0)) :
      cRepElem(owner, size, align, frame, dist)
   {
      init(owner, horz);
   }

  ~cRepGroup();

   virtual bool AddField(cRepElem *elem);
   virtual bool RemoveField(cRepElem *elem);
   virtual bool HasTitle() const { return false; }
   virtual void Draw(bool& out, cdSpace *space, c2dPoint& pos);
   virtual c2dSize& QuerySize(cdSpace *space);
   virtual void SetSize(const c2dSize& s);
   virtual void SetFont(int font_idx) { cRepGroup::font_idx = font_idx; }

   cRepElem *GetFirst() const { return first; }
   cRepElem *GetNext(cRepElem *elem) const { return elem ? elem->next : NULL; }

   bool IsHorizontal() const { return horizontal; }
   bool IsVertical() const { return !horizontal; }

protected:
   bool     horizontal;
   c2dSize    zoom_ext;

private:
   cRepElem *first, *last;
   void init(cRepGroup* owner, bool horz);

};

#endif /*__INTERFACE__*/


// Implementierung cRepGroup
// ===========================================================================

void cRepGroup::init(cRepGroup *owner, bool horz)
{
   horizontal = horz;
   handle_break = !horz; // nur zeilenweise organsierte Gruppe behandelt
   font_idx = owner ? owner->font_idx : 0;
   first = last = NULL;
}

cRepGroup::~cRepGroup()
{
   cRepElem *it = first;
   first = 0;

   while ( it ) {
      cRepElem *to_del = it;
      it = it->next;
      delete to_del;
   }
}


// Traegt ein RepElem bei seinen owner ein
// Falls das Element ein Textfeld ist und keinen Font gesetzt
// hat, wird der Font des owner uebernommen.

bool cRepGroup::AddField(cRepElem *elem)
{
   if ( elem ) {
      if ( elem->owner && (elem->prev || elem->next) )
         elem->owner->RemoveField(elem);
      if ( (elem->prev = last) != NULL )
         last->next = elem;
      elem->next = NULL;
      last = elem;
      if ( !first )
         first = elem;
      elem->owner = this;
   }

   return true;
}

bool cRepGroup::RemoveField(cRepElem *elem)
{
   if ( elem ) {
      if ( elem->prev ) {
         elem->prev->next = elem->next;
      } else {
         first = elem->next;
      }
      if ( elem->next ) {
         elem->next->prev = elem->prev;
      } else {
         last = elem->prev;
      }
      elem->prev = elem->next = NULL;
      elem->owner = NULL;
   }

   return true;
}

// Zeichne Element mit allen Teilelementen
// pos : beim Aufruf: linke, obere Ecke
//       danach: rechte, untere Ecke

void cRepGroup::Draw(bool& out, cdSpace *space, c2dPoint& pos)
{
   c2dPoint cur_pos = pos;
   c2dPoint p = cur_pos;
   double mx = 0;
   bool drawing = out; // Merken, um Zustandswechsel erkennen zu koennen
   cRepElem *last_backed = 0;

   Align(cur_pos, 0, false);

   for ( cRepElem *elem = first ; elem ; elem = elem->next ) {
      cRepElem *el = elem;
      if ( el ) {
         p = cur_pos;
         if ( horizontal ) {
            el->Draw(out, space, p);
            cur_pos.x += el->act_size.cx;
            if ( mx < el->act_size.cy )
                mx = el->act_size.cy;
         } else {
            if ( el->handle_break ) {
               // Element kann selber gucken, ob es noch Platz findet
               el->Draw(out, space, p);
               cur_pos.y = p.y;
            } else {
               cur_pos.y -= el->act_size.cy;
               // Element behandelt Umbruch nicht selbst
               if ( PageBreak(out, false, space, cur_pos) ) {
                  // Teste, ob letzte Seite beendet wurde
                  if ( drawing && !out ) break; // spar dir den Rest!
                  if ( HasTitle() && last_backed != elem->prev ) {
                     el = first; elem = elem->prev;
                     last_backed = elem;
                  }
                  p = cur_pos;
                  cur_pos.y -= el->act_size.cy;
               }
               el->Draw(out, space, p);
            }
            if ( mx < el->act_size.cx )
                mx = el->act_size.cx;
         }
      }
   }

   p = pos;
   cRepElem::Draw(out, space, p);   // Rahmen um Gruppe

   if ( horizontal ) {
      pos.x = cur_pos.x;
      pos.y -= mx + dist.cy;
   } else {
      pos.x += mx + dist.cx;
      pos.y = cur_pos.y;
   }
}

c2dSize& cRepGroup::QuerySize(cdSpace *space)
{
   // Die cRepGroup beachtet keine Rand-Groessen (ueber die QuerySize-Methode
   // der Basisklasse), damit keine ueberfluessigen Leerraeume entstehen.

   wanted_size.cx = dist.cx;
   wanted_size.cy = dist.cy;

   c2dSize elems_size(0,0);
   zoom_ext.cx = zoom_ext.cy = 0;
// bool might_zoom = false;

   for ( cRepElem *elem = first ; elem ; elem = elem->next ) {
      if ( elem ) {
         c2dSize e_s = elem->QuerySize(space);
         if (horizontal) {
            elems_size.cx += e_s.cx;
            if (elems_size.cy < e_s.cy) elems_size.cy = e_s.cy;
            if (elem->zoomable) {
               // might_zoom = zoomable;
               zoom_ext.cx += e_s.cx;
               if (zoom_ext.cy < e_s.cy) zoom_ext.cy = e_s.cy;
            }
         } else {
            elems_size.cy += e_s.cy;
            if (elems_size.cx < e_s.cx) elems_size.cx = e_s.cx;
            if (elem->zoomable) {
               // might_zoom = zoomable;
               // 08.09.99 -TE- Die folgende Anweisung darf
               // zoom_ext.cy AUF KEINEN FALL modifizieren!!!
               zoom_ext.cx += e_s.cy;
               if (zoom_ext.cx < e_s.cx) zoom_ext.cx = e_s.cx;
            }
         }
      }
   }

   if ( !is_zero(size) ) {
      if ( horizontal ) {
         elems_size.cy = size;
      } else {
         elems_size.cx = size;
      }
   }

   return wanted_size += elems_size;
}

void cRepGroup::SetSize( const c2dSize& s )
{
   c2dSize  wanted = wanted_size;  // Retten
   c2dSize  netto  = s - dist;
   wanted_size   = wanted;       // Restauration
   double zoom_x = zoom_ext.cx ? 1.0+(double)(netto.cx-wanted.cx) / zoom_ext.cx : 1.0;
   double zoom_y = zoom_ext.cy ? 1.0+(double)(netto.cy-wanted.cy) / zoom_ext.cy : 1.0;

   cRepElem::SetSize(s);
   if (zoom_x < 0) zoom_x=0;
   if (zoom_y < 0) zoom_y=0;

   for ( cRepElem *elem = first ; elem ; elem = elem->next ) {
      if ( elem ) {
         if (elem->zoomable) {
            if (horizontal) {
               elem->SetSize( c2dSize(elem->wanted_size.cx * zoom_x, netto.cy) );
            } else {
               elem->SetSize( c2dSize(netto.cx, elem->wanted_size.cy * zoom_y) );
            }
         } else {
            if (horizontal) {
               elem->SetSize( c2dSize(elem->wanted_size.cx, netto.cy) );
            } else {
               elem->SetSize( c2dSize(netto.cx, elem->wanted_size.cy) );
            }
         }
      }
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepLine
// ---------------------------------------------------------------------------
//
// cRepLine ist ein Synonym fuer eine cRepGroup mit horizontal (nebeneinander)
// angeordneten Report-Elementen.
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cRepLine
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepLine : public cRepGroup {

public:
   inline cRepLine(cRepGroup *owner,
                   long font_idx = 0,
                   double line_spacing = 0,
                   WHERE align = cRepElem::NONE,
                   WHERE frame = cRepElem::NONE) :
      cRepGroup(owner, true, 0, align, frame, c2dSize(0,line_spacing))
   {
      cRepLine::font_idx = font_idx;
   }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepColumn
// ---------------------------------------------------------------------------
//
// cRepColumn ist ein Synonym fuer eine cRepGroup mit vertikal (untereinander)
// angeordneten Report-Elementen.
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cRepColumn
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepColumn : public cRepGroup {

public:
   inline cRepColumn(cRepGroup *owner,
                     long font_idx = 0,
                     double col_spacing = 0,
                     WHERE align = cRepElem::NONE,
                     WHERE frame = cRepElem::NONE) :
      cRepGroup(owner, false, 0, align, frame, c2dSize(col_spacing,0))
   {
      cRepColumn::font_idx = font_idx;
   }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepTable
// ---------------------------------------------------------------------------
//
// cRepTable ist ein Synonym fuer eine cRepGroup mit vertikal (untereinander)
// angeordneten Report-Elementen, bei denen das erste Element der Gruppe auf
// jeder neuen Report-Seite wiederholt wird, solange die cRepGroup noch nicht
// vollstaendig ausgegeben ist.
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cRepTable
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepTable : public cRepGroup {

public:
   inline cRepTable(cRepGroup *owner,
                    cRepElem *title,
                    double size = 0,
                    WHERE align = NONE,
                    WHERE frame = NONE) :
      cRepGroup(owner, false, size, align, frame, c2dSize(0,0))
   {
      handle_break = true;
      AddField(title);
   }

   inline bool HasTitle() const
      { return true; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepText
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepText : public cRepElem {
   friend class cRepChgText;

public:
   static   long *font_ids;   // IDs aller registrierten Fonts
   static   long font_num;    // Anzahl registrierter Fonts
   long     font_idx;         // Index in FontIDs-Tabelle

   static void RegisterFontIDs(long *ids, int count);

protected:
   cString* text;             // Text
   c2dSize  avg_char_size;    // mittlere Zeichengroesse
   bool     multiline;        // Umbruch auf mehrere Zeilen durchfuehren ?
   int      estim_line_count; // Geschaetzte Anzahl Zeilen, falls Multiline
   c2dSize  act_textsize;     // vom Text beanspruchter Platz

public:
   int      prec;             // Nachkommastellen fuer dez. Tabulator

   cRepText(cRepGroup* owner, cString* text, long font_idx = 0, double size = 0,
            WHERE align = NONE, WHERE frame = NONE, const c2dSize& dist = c2dSize(0,0)) :
      cRepElem(owner, size, align, frame, dist),
      act_textsize(-1, -1)
   {
      init(owner, text, font_idx, size);
   }
   ~cRepText();

   void DrawText( bool out, cdSpace *space, c2dPoint& pos, double x_corr, cString text );
   virtual void PrepDraw(cdSpace *space);
   virtual bool /*changed*/ GetValue( void ) { return false;};
   virtual c2dSize& QuerySize(cdSpace *space);
   virtual void Draw( bool& out, cdSpace *space, c2dPoint& pos );

private:
   void init(cRepGroup *owner, cString *text, long font_idx, double size);

};

#endif /*__INTERFACE__*/


// Implementierung cRepText
// ===========================================================================

long * cRepText::font_ids = NULL;
long cRepText::font_num = 0;

cRepText::~cRepText()
{
}

void cRepText::init(cRepGroup *owner, cString *text, long font_idx, double size)
{
   // Fuer das automatische Loeschen von font_ids Sorge tragen...
   class cAutoCleanup { public: ~cAutoCleanup() { delete[] cRepText::font_ids; } };
   static cAutoCleanup auto_cleanup;

   cRepText::multiline         = !is_zero(size);
   cRepText::avg_char_size.cx  = 0;     // Noch nicht bekannt
   cRepText::text              = text;
   cRepText::font_idx          = font_idx;
   cRepText::prec              = 0;

   if ( owner ) {
      if ( !cRepText::font_idx ) cRepText::font_idx = owner->font_idx;
      else if ( !owner->font_idx ) owner->font_idx = cRepText::font_idx;
   }
}

void cRepText::RegisterFontIDs(long *ids, int count)
{
   if ( font_num > 0 )
      delete[] font_ids;

   font_num = count;
   font_ids = new0 long[count];
   memcpy(font_ids, ids, count * sizeof(long));
}

void cRepText::DrawText( bool out, cdSpace *space, c2dPoint& pos, double x_corr, cString text )
{
   // 24.08.95 -TE- Heute erblickt Windows'95 das Licht der Welt... Raebaeaeh
   // 24.08.95 -TE- Clipping ausgebaut, da es im Zusammenspiel mit HPLJs nur
   //               Probleme gab...

   #ifdef WAS_SOLLTE_DENN_DAS
      c2dSize remain = act_size - wanted_size; // act_textsize - cRepElem::QuerySize(space);
      pos.y -= avg_char_size.cy/3; // Empirisch/Optisch/Quadratisch/Schlecht ?
   #endif

   c2dBox clip_rect(pos, act_size);

   if ( !text.isEmpty() ) {
      double max_str_width = clip_rect.rt.x - pos.x;
      Align(pos, x_corr);
      if ( out )
         DrawTextAt(space, pos, (char *)(const char *)text, max_str_width, Rep_RowSpc);
   }
}

void cRepText::PrepDraw(cdSpace *space)
{
   if ( font_idx < 1 || font_idx > font_num )
      DbgError("cRepText::PrepDraw: Font index (%d) not in range 1..%d", font_idx, font_num);
   if ( font_ids && font_idx > 0 && font_idx <= font_num )
      space->selectFont(font_ids[font_idx - 1]);
   space->setTextAlign(cdAlign::Left, cdAlign::Top);
   if ( avg_char_size.cx < 1.0 )
      avg_char_size = QueryAvgCharSize(space);
}

c2dSize& cRepText::QuerySize(cdSpace *space)
{
   PrepDraw(space);   // Wird jetzt auf jeden Fall gemacht
   cRepElem::QuerySize(space);
   GetValue();                               // Beschaffe Text
   if ( act_textsize.cx < 1.0 ) {
      act_textsize = QueryTextSize(space, (char*)(const char*)*text, size, Rep_RowSpc );
   }
   estim_line_count = 1;
   if ( !is_zero(size) ) {
      wanted_size.cx += size;
///   If (act_textsize.cx > size) Then
///      double div = max(1, size-3*avg_char_size.cx ); // Verschnitt abschaetzen
///      estim_line_count = multiline ? 1+textsize.cx/div : 1;
///   Endif
      wanted_size.cy += act_textsize.cy * estim_line_count;
   } else {
      wanted_size += act_textsize;
   }
   return wanted_size;
}

void cRepText::Draw( bool& out, cdSpace *space, c2dPoint& pos )
{
   double forced_size = size;
   c2dSize orig_wanted = wanted_size;
   size = 0;               // Ermittle vom   T e x t  beanspruchten Platz
   cRepText::QuerySize(space);   // Fuehrt unbedingt PrepDraw aus!!!
   size  = forced_size;    // Restauration
   char *dot = NULL;
   if ( prec && !text->isEmpty() ) {
      dot = strrchr( (const char *)*text, ',' );
      if (!dot) dot = strrchr( (const char *)*text, '.' );
   }
   double x_corr = 0;
   if (dot) x_corr = QueryTextSize(space, dot, 0, Rep_RowSpc ).cx - avg_char_size.cx * prec;
#ifdef WAS_SOLL_DAS /* -TE- 21.01.95 */
   if (align&RIGHT) x_corr += avg_char_size.cx;
#endif
   c2dPoint at = pos;
   DrawText( out, space, at, x_corr, *text );
   cRepElem::Draw( out, space, pos );      // Rahmen
   wanted_size = orig_wanted;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepStatText
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//          +--cRepStatText
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepStatText : public cRepText {
public:
   inline cRepStatText(cRepGroup* owner,
                       const cString& text,
                       long font_idx = 0,
                       double size = 0,
                       WHERE align = NONE,
                       WHERE frame = NONE,
                       const c2dSize& dist = c2dSize(0,0)) :
      cRepText(owner, new0 cString(text), font_idx, size, align, frame, dist)
   { }

   virtual ~cRepStatText() { delete text; }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepVarText
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//          +--cRepVarText
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepVarText : public cRepText {
public:
   inline cRepVarText(cRepGroup *owner,
                      cString *text,
                      long font_idx = 0,
                      double size = 0,
                      WHERE align = NONE,
                      WHERE frame = NONE,
                      const c2dSize& dist = c2dSize(0,0)) :
      cRepText(owner, text, font_idx, size, align, frame, dist)
   { }

   virtual bool /*changed*/ GetValue( void );
   virtual void Draw( bool& out, cdSpace *space, c2dPoint& pos );
};

#endif /*__INTERFACE__*/


// Implementierung cRepVarText
// ===========================================================================

bool /*changed*/ cRepVarText::GetValue( void )
{
   act_textsize.cx = -1;
   return true;            // moeglicherweise geaendert
}

void cRepVarText::Draw( bool& out, cdSpace *space, c2dPoint& pos )
{
//   long forced_size = size;
//   c2dSize orig_wanted = wanted_size;
//   size = 0;               // Ermittle vom   T e x t  beanspruchten Platz
//   cRepVarText::QuerySize(space);
//   size  = forced_size;    // Restauration
   cRepText::Draw( out, space, pos );
//   wanted_size = orig_wanted;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepVariable
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//          +--cRepVariable
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepVariable : public cRepText {

public:
   typedef cString (*VAL_FUNC_PTR)();

   inline cRepVariable(cRepGroup *_owner,
                       VAL_FUNC_PTR _func_ptr,
                       long _font_id = 0,
                       double _size = 0,
                       WHERE _align = NONE,
                       WHERE _frame = NONE,
                       const c2dSize& _dist = c2dSize(0,0)) :
      cRepText(_owner, &value, _font_id, _size, _align, _frame, _dist)
   {
      func_ptr = _func_ptr;
   }

   inline cRepVariable(cRepGroup *_owner,
                       long _font_id = 0,
                       double _size = 0,
                       WHERE _align = NONE,
                       WHERE _frame = NONE,
                       const c2dSize& _dist = c2dSize(0,0)) :
      cRepText(_owner, &value, _font_id, _size, _align, _frame, _dist)
   {
      func_ptr = NULL;
   }

   bool /*changed*/ GetValue();

protected:
   VAL_FUNC_PTR func_ptr;
   cString value;

};

#endif /*__INTERFACE__*/


// Implementierung cRepVariable
// ===========================================================================

bool /*changed*/ cRepVariable::GetValue()
{
   if ( func_ptr != NULL )
      value = func_ptr();
   act_textsize.cx = -1;
   return true;            // moeglicherweise geaendert
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepAbstract
// ---------------------------------------------------------------------------
//
// Elemente dieser Klasse haben selbst keinen Platzbedarf im Report und dienen
// lediglich Verwaltungszwecken. Das cRepAbstract-Element wird an einer be-
// stimmten Stelle im Report eingebunden und aktiviert zum Zeitpunkt des
// Report-Aufbaus zeitsynchron an der Stelle der Definition seine Action()-
// Methode.
//
// cBase
//  +--cRepElem
//      +--cRepAbstract
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepAbstract : public cRepElem {

public:
   inline cRepAbstract(cRepGroup *_owner) :
      cRepElem(_owner, 0, NONE, NONE, c2dSize(0,0))
   { }

   void Draw(bool& out, cdSpace *space, c2dPoint& pos);

   virtual void Action() = 0;

};

#endif /*__INTERFACE__*/


// Implementierung cRepAbstract
// ===========================================================================

void cRepAbstract::Draw(bool& out, cdSpace *space, c2dPoint& pos)
{
   Action();
   cRepElem::Draw(out, space, pos);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepChgText
// ---------------------------------------------------------------------------
//
// Ueber dieses Element kann der Wert eines beliebigen cRepText-Elementes
// synchron zum Aufbau des gesamten Reports manipuliert werden.
//
// cBase
//  +--cRepElem
//      +--cRepAbstract
//          +--cRepChgText
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepChgText : public cRepAbstract {

public:
   inline cRepChgText(cRepGroup *_owner, cRepText *_text_elem, const cString& _value) :
      cRepAbstract(_owner)
   {
      text_elem = _text_elem;
      value = _value;
   }

   void Action();

protected:
   cRepText *text_elem;
   cString value;

};

#endif /*__INTERFACE__*/


// Implementierung cRepChgText
// ===========================================================================

void cRepChgText::Action()
{
   if ( text_elem && text_elem->text )
      *text_elem->text = value;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepGraphic
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepGraphic
//
// ===========================================================================

struct MYPOINTL {
   long x, y;
};

class __ECL_DLLEXPORT__ cRepGraphic : public cRepElem {

public:
   cRepGraphic(cRepGroup* _owner, WHERE _align = NONE, WHERE _frame = NONE,
      const c2dSize& _dist = c2dSize(0,0)) :
      cRepElem(_owner, 0, _align, _frame,  _dist)
   {
      width = height = 0;
   }

   bool /*changed*/ GetValue() { return false;};
   c2dSize& QuerySize(cdSpace *space);
   void Draw(bool& out, cdSpace *space, c2dPoint& pos);

   // Faellt weg:
   void Move(int, int) { }
   void Line(int, int) { }
   void Text(const char *) { }
   void PolyLine(int, MYPOINTL *) { }
   void Polygon(int, MYPOINTL *, bool) { }
   void SetTextAlign(int, int) { }
   void SetCharAngle(int, int) { }
   void SelectFont(cdSpace *, const char *, int) { }

protected:
   cdMemorySpace mem_space;
   double width, height;

};

#endif /*__INTERFACE__*/


// Implementierung cRepGraphic
// ===========================================================================

void cRepGraphic::Draw(bool& out, cdSpace *space, c2dPoint& pos)
{
   c2dPoint cur_pos = pos;
   Align(cur_pos);

   if ( out ) {
      if ( cRepText::font_ids && cRepText::font_num > 2 )
         space->selectFont(cRepText::font_ids[3]); // Skizzenbeschriftung
      space->moveTo(cur_pos - c2dVector(0, height));
      space->draw(&mem_space);
      space->setColor(cdColor::Black);
   }

   cRepElem::Draw(out, space, pos); // Rahmen
}

c2dSize& cRepGraphic::QuerySize(cdSpace *space)
{
   cRepElem::QuerySize(space); // Rand-Groesse
   c2dSize elems_size(width, height);
   return wanted_size += elems_size;
}

