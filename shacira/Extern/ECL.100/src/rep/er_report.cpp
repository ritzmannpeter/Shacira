// ===========================================================================
// er_report.cpp                                 ECL (ET's tiny Class Library)
//                                                         Autor: Udo Pfrengle
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cRepElem                -
//         |
//         +--cRepGroup           -
//         |   |
//         |   +--cReport         -
//         |   |
//         |   +--cRepRecord      -
//         |   |
//         |   +--cRepTabCol      -
//         |   |
//         |   +--cReportTable    -
//         |
//         +--cRepText            -
//             |
//             +--cRepStatText    -
//             |
//             +--cRepVarText     -
//                 |
//                 +--cRepDBField -
//                 |
//                 +--cRepVarPgNo -
//
// ===========================================================================

#include "rep/er_report.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

// enum { ab, an, be, ent, er, her, hin, ver, vor, zu } richten;




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"
#include "rep/er_repelem.hpp"

// Default Font-IDs
#define REP_FID_NORM       1
#define REP_FID_TABHEAD    2
#define REP_FID_TABCONT    3
#define REP_FID_HEADLINE   4
#define REP_FID_FOOTLINE   5

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cReport
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cReport
//
// ===========================================================================

class __ECL_DLLEXPORT__ cReport : public cRepGroup {
   c2dBox         page1_rect;    // Fuer Seite 1
   c2dBox         page2_rect;    // Fuer Seite 2 und folgende
   bool           output;
   int            first_page, last_page;

public:
   int            page_count;
   int            page_no;
   cRepElem*      headline;      /* Kopfzeile fuer alle Seiten ausser 1. wenn first_h.*/
   cRepElem*      footline;      /* Fusszeile fuer alle Seiten ausser 1. wenn first_foo.*/
   cRepElem*      first_headline;
   cRepElem*      first_footline;

   virtual ~cReport();
   inline cReport() :
      cRepGroup(NULL, false, 0, NONE, NONE, c2dSize(0,0))
   {
      headline = footline = first_headline = first_footline = NULL;
      page_count = -1; // unbekannt bis jetzt
   }

   void DrawPages(cdSpace *space, const c2dBox& page1, const c2dBox& page2, int page_start, int page_end);
   virtual bool /*done*/ PageBreak(bool& out, bool force, cdSpace *space, c2dPoint& pos);
   double FootlineHeight();
   void DrawFooter(cdSpace *space, c2dPoint& pos);
   void DrawHeader(cdSpace *space, c2dPoint& pos);
   void Repaginate(cdSpace *space, const c2dBox& page);
   virtual c2dSize& QuerySize(cdSpace *space);
   virtual void SetSize(const c2dSize& s);

   cRepElem *getHeadline(int page) const
      { return page == 0 && first_headline ? first_headline : headline; }
   cRepElem *getFootline(int page) const
      { return page == 0 && first_footline ? first_footline : footline; }

};

#endif /*__INTERFACE__*/


// Implementierung cReport
// ===========================================================================

cReport::~cReport()
{
   delete headline;
   delete footline;
   delete first_headline;
   delete first_footline;
}

c2dSize& cReport::QuerySize(cdSpace *space)
{
   cRepGroup::QuerySize(space);
   cRepElem *hfl;

   if ( (hfl = getHeadline(page_no)) != NULL ) {
      wanted_size.cy += hfl->QuerySize(space).cy;
      if ( wanted_size.cx < hfl->wanted_size.cx )
         wanted_size.cx = hfl->wanted_size.cx;
   }

   if ( (hfl = getFootline(page_no)) != NULL ) {
      wanted_size.cy += hfl->QuerySize(space).cy;
      if ( wanted_size.cx < hfl->wanted_size.cx )
         wanted_size.cx = hfl->wanted_size.cx;
   }

   return wanted_size;
}

void cReport::SetSize(const c2dSize& s)
{
   c2dSize news(s);
   cRepElem *hfl;

   if ( (hfl = getHeadline(page_no)) != NULL ) {
      news.cy = hfl->wanted_size.cy;
      hfl->SetSize(news);
   }

   if ( (hfl = getFootline(page_no)) != NULL ) {
      news.cy = hfl->wanted_size.cy;
      hfl->SetSize(news);
   }

   news.cy = -1;         // Hoehe unangetastet lassen
   cRepGroup::SetSize(news);
}

void cReport::DrawHeader(cdSpace *space, c2dPoint& pos)
{
   cRepElem *hl = getHeadline(page_no);
   output = first_page <= page_no && page_no <= last_page;

   if ( hl ) {
      double x = pos.x;
      hl->Draw( output, space, pos );
      // pos.y -= hl->act_size.cy;
      // act_size.cy += hl->act_size.cy;
      pos.x = x;
   }
}

void cReport::DrawFooter(cdSpace *space, c2dPoint& pos)
{
   cRepElem *fl = getFootline(page_no);

   if ( fl ) {
      fl->Draw( output, space, pos);
      pos.y -= fl->act_size.cy;
   }
}

double cReport::FootlineHeight()
{
   cRepElem *fl = getFootline(page_no);
   return
      (page_no == 0 ? page1_rect.lb.y : page2_rect.lb.y)
    + (fl ? fl->act_size.cy : 0);
}

bool /*done*/ cReport::PageBreak(bool& out, bool force, cdSpace *space, c2dPoint& pos)
{
   c2dPoint fhpos((page_no == 0 ? page1_rect.lb.x : page2_rect.lb.x), FootlineHeight());

   if ( force || pos.y < fhpos.y ) {
      // passt nimmer ==> Seitenumbruch
      if ( page_no >= first_page ) {
         DrawFooter(space, fhpos );
         space->newFrame();
         SetSize(page2_rect.getSize());
      }
      ++page_no;
      pos.y = page2_rect.rt.y;
      DrawHeader(space, pos);
      out=output;
      return true;
   } else {
      return false;
   }
}

void cReport::DrawPages(cdSpace *space, const c2dBox& page1, const c2dBox& page2,
   int page_start, int page_end)
{
   const c2dBox& page = page_start == 0 ? page1 : page2;
   c2dPoint pos = page.getTopLeft();
   c2dSize page_size = page.getSize();
   SetSize(page_size);

   page1_rect = page1;
   page2_rect = page2;
   first_page = page_start;
   last_page = page_end;
   page_no = 0;

   DrawHeader(space, pos);
   c2dPoint cur_pos = pos;

   cRepElem *elem;

   for ( elem = GetFirst() ; elem && page_no <= page_end; elem = GetNext(elem) ) {
      if ( elem ) {
         c2dPoint p = cur_pos;
         if ( elem->handle_break ) {
            // Element kann selber gucken, ob es noch Platz findet
            elem->Draw(output, space, p);
            cur_pos.y = p.y;
         } else {
            cur_pos.y -= elem->act_size.cy;
            // Element behandelt Umbruch nicht selbst
            if ( PageBreak(output, false, space, cur_pos) ) {
               p = cur_pos;
               cur_pos.y -= elem->act_size.cy;
            }
            elem->Draw(output, space, p);
         }
      }
   }

   if ( !elem ) // Nicht auf letzter Seite?
      page_count = page_no+1;

   pos.y = FootlineHeight();
   DrawFooter(space, pos);
}

void cReport::Repaginate(cdSpace * /*space*/, const c2dBox& /*page*/)
{
   page_count = -1;
   // Tatsaechliche Seitenzahl wird beim naechsten Draw ermittelt
}




#ifdef __VIELLEICHT_MAL_ZU_RECYCLEN___
#ifdef __INTERFACE_

// ===========================================================================
// Definition cRepDBField
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//          +--cRepVarText
//             +--cRepDBField
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepDBField : public cRepVarText {
protected:
   cTable::cField *field;  // Assoziierte Spalte im Query
   cString  last_val;      // Wert in der Zeile obendran
   cString  cur_val;       // Aktueller Wert
   cString  out_val;       // Angezeigter Wert
public:
   bool     sum_rows;      // Spalte ueber alle Zeilen aufsummieren
   double   sum;           // Nur bei num. Spalten
   bool     supress_rows;  // Folgezeilen mit gleichem Inhalt unterdruecken
   cRepDBField(
            cRepGroup *owner,
            cTable::cField *f,
            long font_id=0,
            double _size=0,
            WHERE _align=NONE,
            WHERE _frame=NONE,
            const c2dSize& _dist=c2dSize(0,0)
          )
   : cur_val(), last_val(), cRepVarText( owner, &this->cur_val, font_id, _size, _align, _frame, _dist )
   {
      sum_rows = true;
      supress_rows = false;
      sum = 0.0;
      Assoc( f );
   }
   void Assoc( cTable::cField *f ) { field = f; }
   virtual bool /*changed*/ GetValue( void );
   virtual c2dSize& QuerySize(cdSpace *space);
   virtual c2dSize& QueryActSize(cdSpace *space);
   virtual void Draw( bool& out, cdSpace *space, c2dPoint& pos);
   virtual void Restart( bool full );
};

#endif /* __INTERFACE__ */


// Implementierung cRepDBField
// ===========================================================================

// Geschaetzte Groesse entsprechend Spaltenbreite
c2dSize& cRepDBField::QuerySize(cdSpace *space)
{
   PrepDraw(space);
   cRepElem::QuerySize(space);
// last_val.Clear();
   if (field) {
      c2dSize ch_size = QueryAvgCharSize(space);
      double textwidth = ch_size.cx * 1.4 * max( field->Width(), field->Size() + prec - field->Prec() );
      estim_line_count = multiline && size ? 1+textwidth / size : 1;
      if (size) {
         wanted_size.cx += size;
         wanted_size.cy += estim_line_count * ch_size.cy * 1.5;
      } else {
         wanted_size.cx += textwidth;
         wanted_size.cy += ch_size.cy * Rep_RowSpc;
      }
      sum = 0.0;
   }
   return wanted_size;
}

bool /*changed*/ cRepDBField::GetValue( void )
{
   text = &out_val;
   act_textsize.cx = -1;
   if (field) {
      if ( prec && E_NUMERIC == field->Type() ) {
         double value;
         char buffer[30];
         if (field->Get( value )) {
            if (2 == sum_rows) value += sum;
            Fmt_DblToStr( buffer, value, prec,
               cTable::cField::decimal_sep,
               cTable::cField::thousand_sep );
            cur_val = buffer;
         } else {
            cur_val = (char *)NULL;
         }
      } else {
         cur_val = field->Get();
      }
      if (supress_rows && cur_val == last_val && cur_val.Length() ) {
         out_val = "-\"-";
         return false;
      } else {
         out_val = cur_val;
         return true;
      }
   } else {
      out_val = cur_val = (char *)NULL;
      return false;
   }
}

// Groesse entsprechend akt. Feldinhalt
c2dSize& cRepDBField::QueryActSize(cdSpace *space)
{
   GetValue();
   return cRepText::QuerySize(space);
}

// Draw-Methode: stellt Feldinhalt dar
void cRepDBField::Draw( bool& out, cdSpace *space, c2dPoint& pos )
{
// If (GetValue() && supress_rows) Then
//    last_val = cur_val;
// Endif
   cRepVarText::Draw( out, space, pos );
   last_val = cur_val;
   double val;
   if (sum_rows && field->Get(val)) {
      sum += val;
   }
}

void cRepDBField::Restart( bool full )
{
   last_val.Clear();
   if (full) sum = 0.0;
}




#ifdef __INTERFACE_

// ===========================================================================
// Definition cRepRecord
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cRepRecord
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepRecord : public cRepGroup {
protected:
   cTable*        tab;
public:
   cRepRecord(  cReport* rep,
                  cTable* _tab,
                  double line_spacing=0,
                  WHERE _align=cRepElem::NONE,
                  WHERE _frame=cRepElem::NONE )
     : cRepGroup(rep, false, 0, _align, _frame,  c2dSize(0,line_spacing))
     { tab=_tab; }
   virtual ~cRepRecord() { if (tab) delete tab; }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE_

// ===========================================================================
// Definition cRepTabCol
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cRepTabCol
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepTabCol : public cRepGroup {
protected:
   double title_row_height;
   double data_row_height;
   double col_width;
public:
   cRepTabCol( cRepGroup* owner, cRepText* _title, cRepText* _field,
                  double col_spacing=0,
                  WHERE _align=cRepElem::NONE,
                  WHERE _frame=cRepElem::NONE );
// virtual c2dSize& QuerySize(cdSpace *space);
   c2dSize& QueryTitleSize(cdSpace *space);
   c2dSize& QueryDataSize(cdSpace *space);
   double QueryColWidth(cdSpace *space) { return col_width; }
   c2dSize& QueryActDataSize(cdSpace *space)
      { return elem && s[1] ? elems[1]->QueryActSize(space) : dist; }
   virtual void SetSize( const c2dSize& s );
   void SetSize( double width, double title_height, double data_height );
   void NewDataRowHeight( double data_height );
   double /*height*/ DrawData( bool out, cdSpace *space, c2dPoint &pos );
   double /*height*/ DrawTitle( bool out, cdSpace *space, c2dPoint &pos );
   cRepText* Title() { return (cRepText*)elems[0]; }
   cRepElem* Field() { return (cRepDBField*)elems[1]; }
};

#endif /*__INTERFACE__*/


// Implementierung cRepTabCol
// ===========================================================================

cRepTabCol::cRepTabCol( cRepGroup* owner, cRepText* _title, cRepText* _field,
               double col_spacing, cRepElem::WHERE _align, cRepElem::WHERE _frame )
   : cRepGroup( owner, false, 0, _align, _frame, c2dSize(col_spacing,0) )
{
   elems[0] = _title;
   elems[1] = _field;
   num_elems = 2;
   zoomable = _title ? _title->zoomable : false
           || _field ? _field->zoomable : false;
   if (_title && !_title->lcid) _title->lcid = REP_FID_TABHEAD;
   if (_field && !_field->lcid) _field->lcid = REP_FID_TABCONT;
}

void cRepTabCol::SetSize( const c2dSize& s )
{
   SetSize( s.cx, title_row_height, data_row_height );
}

void cRepTabCol::SetSize( double width, double title_height, double data_height )
{
   if (Title() && title_height>0) Title()->SetSize( c2dSize( width, title_row_height=title_height ) );
   if (Field() && data_height >0) Field()->SetSize( c2dSize( width, data_row_height=data_height   ) );
}

void cRepTabCol::NewDataRowHeight( double data_height )
{
   if (Field()) Field()->SetSize( c2dSize(Field()->act_size.cx, data_height) );
}

double /*height*/ cRepTabCol::DrawTitle( bool out, cdSpace *space, c2dPoint& pos )
{
   if (Title()) {
      Title()->Draw( out, space, pos );
      return Title()->act_size.cy;
   } else {
      return 0;
   }
}

double /*height*/ cRepTabCol::DrawData( bool out, cdSpace *space, c2dPoint &pos )
{
   if (Field()) {
      Field()->Draw( out, space, pos );
      return Field()->act_size.cy;
   } else {
      return 0;
   }
}

c2dSize& cRepTabCol::QueryTitleSize(cdSpace *space)
{
   if ( Title() ) {
      col_width = Title()->QuerySize(space).cx;
      return Title()->wanted_size;
   } else {
      return dist;
   }
}

c2dSize& cRepTabCol::QueryDataSize(cdSpace *space)
{
   if ( Field() ) {
      Field()->QuerySize(space);
      if (Field()) {
         if ( Field()->zoomable && Title() && !Title()->zoomable) {
            Field()->wanted_size.cx = col_width;
         } else {
            if (col_width < Field()->wanted_size.cx)
                col_width = Field()->wanted_size.cx;
         }
      } else {
         col_width = Field()->wanted_size.cx;
      }
      return Field()->wanted_size;
   } else {
      return dist;
   }
}




#ifdef __INTERFACE_

// ===========================================================================
// Definition cReportTable
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepGroup
//          +--cReportTable
//
// ===========================================================================

class __ECL_DLLEXPORT__ cReportTable : public cRepGroup {
protected:
   double data_row_height;
   double title_row_height;
   cTable*        tab;
public:
   cRepDBField    *row_descr;    // Superspezialo fuer Artikelbeschreibung
   int            descr_align_at;

   cReportTable(  cRepGroup* _owner,
                  cTable* _tab,
                  double line_spacing=0,
                  WHERE _align=cRepElem::NONE,
                  WHERE _frame=cRepElem::NONE );
   virtual ~cReportTable() { if (tab) delete tab; }
   virtual c2dSize& QuerySize(cdSpace *space);

   virtual void Draw( bool& out, cdSpace *space, c2dPoint &pos );
   virtual void DrawTitle( bool out, cdSpace *space, c2dPoint &pos );
   double DataRowHeight( void ) { return data_row_height; }
   double TitleRowHeight( void ) { return title_row_height; }
   virtual bool /*ok*/ FetchRow( void );
   double /*height*/ QueryActRowHeight(cdSpace *space);
   void Restart( bool full );
   virtual bool /*ok*/ DrawRow( bool out, cdSpace *space, c2dPoint& pos, double height );
};

#endif /*__INTERFACE__*/


// Implementierung cReportTable
// ===========================================================================

cReportTable::cReportTable(  cRepGroup* _owner,
               cTable* _tab,
               double line_spacing,
               WHERE _align, WHERE _frame )
  : cRepGroup(_owner, true, 0, _align, _frame, c2dSize(0,line_spacing))
{
   tab=_tab;
   row_descr = NULL;
   descr_align_at = 0;
   handle_break = true;
}

c2dSize& cReportTable::QuerySize(cdSpace *space)
{
   data_row_height  = 0;
   title_row_height = 0;

   zoom_ext.cx = zoom_ext.cy =
   wanted_size.cx = wanted_size.cy = 0;
   zoomable = false;
   for (int i = 0; i < num_elems; ++i) {
      cRepTabCol *el = (cRepTabCol*)elems[i];
      if (el->Field()) el->Field()->Restart( true );
      c2dSize title_size = el->QueryTitleSize(space);
      c2dSize data_size  = el->QueryDataSize(space);
      el->wanted_size.cx = el->QueryColWidth(space);
      wanted_size.cx += el->wanted_size.cx;
      if (el->zoomable) {
         zoomable = true;
         zoom_ext.cx += el->wanted_size.cx;
      }
      if (title_row_height < title_size.cy)
          title_row_height = title_size.cy;
      if (data_row_height < data_size.cy)
          data_row_height = data_size.cy;
   }
   if (row_descr) {
      c2dSize spec_size = row_descr->QuerySize(space);
      if (wanted_size.cx < spec_size.cx)
          wanted_size.cx = spec_size.cx;

      data_row_height += spec_size.cy;
      row_descr->SetSize( spec_size );
   }

   /* Zeilenhoehe anpassen */
   for (int i = 0; i < num_elems; ++i) {
      ((cRepTabCol*)elems[i])->SetSize( elems[i]->wanted_size.cx, title_row_height, data_row_height );
   }

   data_row_height += dist.cy;   // Zeilenabstand beruecksichtigen

   /* Datenzeilen zaehlen */
   int num_rows = 0;
   if (tab) {
      tab->Rewind();
      while( tab->Fetch() ) ++num_rows;
      wanted_size.cy = title_row_height + num_rows * data_row_height;
   } else {
      wanted_size.cy = title_row_height;
   }
   zoom_ext.cy = wanted_size.cy;
   return wanted_size += dist;
}

// Veraendert pos.x nicht
void cReportTable::DrawTitle( bool out, cdSpace *space, c2dPoint &pos )
{
   c2dPoint col_pos = pos;
// double height = 0;
   Align( col_pos );

   for (int i = 0; i < num_elems; ++i) {
      cRepTabCol *el = (cRepTabCol*)elems[i];
      col_pos.y = pos.y; // y-Position restaurieren
      el->DrawTitle( out, space, col_pos );
   }
   pos.y = col_pos.y;
}

bool /*ok*/ cReportTable::FetchRow( void )
{
   return tab && tab->Fetch();
}

void cReportTable::Restart( bool full )
{
   for (int i = 0; i < num_elems; ++i) {
      if (((cRepTabCol*)elems[i])->Field())
         ((cRepTabCol*)elems[i])->Field()->Restart( full );
   }
   if (row_descr) row_descr->Restart( full );
}

double /*height*/ cReportTable::QueryActRowHeight(cdSpace *space)
{
   double max_h=0;
   if (tab) {
      cRepTabCol **rtc = (cRepTabCol**)elems;
      for (int i = 0; i < num_elems; ++i) {
         double height = (*rtc++)->QueryActDataSize(space).cy;
         if (max_h < height) max_h = height;
      }
      if (row_descr) max_h += row_descr->QueryActSize(space).cy;
      max_h += dist.cy;   // Zeilenabstand beruecksichtigen
      //cString::Diagnostic();
   }
   return max_h;
}

// Veraendert pos.x nicht
bool /*ok*/ cReportTable::DrawRow( bool out, cdSpace *space, c2dPoint& pos, double height )
{
   if (tab) {
      cRepTabCol **rtc = (cRepTabCol**)elems;
      c2dPoint col_pos = pos;
      double data_height = (row_descr ? height - row_descr->wanted_size.cy : height)
                        - dist.cy;
      c2dPoint row_descr_pos = c2dPoint( pos.x, pos.y-data_height );

      Align( col_pos );
      rtc = (cRepTabCol**)elems;
      for (int i = 0; i < num_elems; ++i) {
         if (i==descr_align_at) row_descr_pos.x = col_pos.x;
         (*rtc)->NewDataRowHeight( data_height );
         if (descr_align_at == i) {
            row_descr_pos = col_pos;
            (*rtc)->DrawData( out, space, col_pos );
            if ((*rtc)->Field() )
               row_descr_pos.y -= (*rtc)->Field()->wanted_size.cy;
            col_pos.y = pos.y; // Y-Position restaurieren
         } else {
            (*rtc)->DrawData( out, space, col_pos );
         }
         col_pos.y = pos.y; // Y-Position restaurieren
         ++rtc;
      }
      cString::Diagnostic();
      if (row_descr) row_descr->Draw( out, space, row_descr_pos );
      pos.y -= height;
      act_size.cy += height;
      return true;
   } else {
      return false;
   }
}

void cReportTable::Draw( bool& out, cdSpace *space, c2dPoint& pos )
{
   bool title_needed = true;
   double y_start = pos.y;
   if (tab) {
      tab->Rewind();
      Restart( true );
      while( FetchRow() ) {
         double row_height = QueryActRowHeight(space);
         double title_height = title_needed ? TitleRowHeight() : 0;
         pos.y -= row_height + title_height;
         if ( PageBreak( out, false, space, pos ) ) {
            Restart( false );
            row_height = QueryActRowHeight(space);
            title_needed = true;
         } else {
            pos.y += row_height + title_height;
         }
         if (title_needed) {
            DrawTitle( out, space, pos );
            title_needed = false;
         }
         DrawRow( out, space, pos, row_height );
      }
   }
   pos.x += act_size.cx;
   pos.y -= dist.cy;
   act_size.cy = y_start - pos.y;
}
#endif /*__VIELLEICHT_MAL_ZU_RECYCLEN___*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRepVarPgNo
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRepElem
//      +--cRepText
//          +--cRepVarText
//              +--cRepVarPgNo
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRepVarPgNo : public cRepVarText {
public:
   inline cRepVarPgNo(cRepGroup* owner, cReport *_report, long font_id=0,
            double _size=0,
            WHERE _align=NONE,
            WHERE _frame=NONE,
            const c2dSize& _dist=c2dSize(0,0)
          ) : report( _report ),
              cRepVarText( owner, &value, font_id, _size, _align, _frame, _dist )
      { }
   virtual bool /*changed*/ GetValue( void );
protected:
   cReport *report;
   cString value;
};

#endif /* __INTERFACE__*/


// Implementierung cRepVarPgNo
// ===========================================================================

bool /*changed*/ cRepVarPgNo::GetValue( void )
{
   value = cStringf(" %d  ", report->page_no+1);
   return cRepVarText::GetValue();
}

