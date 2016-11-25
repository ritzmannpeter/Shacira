

/// PR 09.12.08 - added antialiasing of arrows

#include "cQtTouchStyle.h"
#include <qpointarray.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qradiobutton.h>
#include <qwidget.h>
#include "qdrawutil.h"
#include "qpixmap.h"
#include "qimage.h"
#include "qapplication.h"
#include "qlistview.h"
#include "qbitmap.h"
#include <qcleanuphandler.h>

#define X_OFFSET_RADIOBUTTON 5
#define SCALE_CHECKBOX 2

cQtTouchStyle::cQtTouchStyle(double scroll_bar_width_multiplier, bool antialias_arrows, bool change_listview_branch_control) :
   _scroll_bar_width_multiplier(scroll_bar_width_multiplier),
   _AntiAliasArrows(antialias_arrows), _ChangeListViewBranchControl(change_listview_branch_control)
{
}

cQtTouchStyle::~cQtTouchStyle()
{
}

void cQtTouchStyle::drawPrimitive(PrimitiveElement pe,
                                     QPainter * p,
                                     const QRect & r,
                                     const QColorGroup & cg,
                                     SFlags flags,
                                     const QStyleOption & opt) const
{
   switch ( pe ) {
   case PE_ArrowUp:
   case PE_ArrowDown:
   case PE_ArrowRight:
   case PE_ArrowLeft:
      {
         QPointArray pa( 3 );
         int x = r.x();
         int y = r.y();
         int w = r.width() / 2;
         int h = r.height() / 2;
         x += (r.width() - w) / 2;
         y += (r.height() - h) /2;
         switch( pe ) {
         case PE_ArrowDown:
            pa.setPoint( 0, x, y );
            pa.setPoint( 1, x + w, y );
            pa.setPoint( 2, x + w / 2, y + h );
            break;
         case PE_ArrowUp:
            pa.setPoint( 0, x, y + h );
            pa.setPoint( 1, x + w, y + h );
            pa.setPoint( 2, x + w / 2, y );
            break;
         case PE_ArrowLeft:
            pa.setPoint( 0, x + w, y );
            pa.setPoint( 1, x + w, y + h );
            pa.setPoint( 2, x, y + h / 2 );
            break;
         case PE_ArrowRight:
            pa.setPoint( 0, x, y );
            pa.setPoint( 1, x, y + h );
            pa.setPoint( 2, x + w, y + h / 2 );
            break;
         default: break;
         }
         if ( flags & Style_Enabled ) {
            p->setPen( cg.mid() );
            p->setBrush( cg.brush( QColorGroup::ButtonText ) );
         } else {
            p->setPen( cg.buttonText() );
            p->setBrush( cg.brush( QColorGroup::Mid ) );
         }
         if (!_AntiAliasArrows) {
            p->drawPolygon( pa );
         } else {
#define SCALE_SIZE   8
#define RECT_DIST    4
            int _w = r.width() - (RECT_DIST * 2);
            int _h = r.height() - (RECT_DIST * 2);
            if (_w > RECT_DIST &&
                _h > RECT_DIST) {
               QPixmap pm(_w * SCALE_SIZE, _h * SCALE_SIZE);
               pm.fill(cg.background());
               QPainter plocal(&pm);
               if ( flags & Style_Enabled ) {
                  plocal.setPen( cg.mid() );
                  plocal.setBrush( cg.brush( QColorGroup::ButtonText ) );
               } else {
                  plocal.setPen( cg.buttonText() );
                  plocal.setBrush( cg.brush( QColorGroup::Mid ) );
               }
               QPointArray pb( 3 );
               pb.setPoint(0, ((pa[0].x() - r.x()) * SCALE_SIZE) - RECT_DIST, ((pa[0].y() - r.y()) * SCALE_SIZE) - RECT_DIST);
               pb.setPoint(1, ((pa[1].x() - r.x()) * SCALE_SIZE) - RECT_DIST, ((pa[1].y() - r.y()) * SCALE_SIZE) - RECT_DIST);
               pb.setPoint(2, ((pa[2].x() - r.x()) * SCALE_SIZE) - RECT_DIST, ((pa[2].y() - r.y()) * SCALE_SIZE) - RECT_DIST);
               plocal.drawPolygon( pb );
               QImage image;
               image = pm;
               image = image.smoothScale(_w, _h);
               p->drawImage(r.x() + RECT_DIST/2, r.y() + RECT_DIST/2, image);
            } else {
               p->drawPolygon( pa );
            }
         }
      }
      break;
   case PE_Indicator:
   {
      QBrush fill;
	   if (flags & Style_NoChange) {
         QBrush b = p->brush();
         QColor c = p->backgroundColor();
         p->setBackgroundMode( TransparentMode );
         p->setBackgroundColor( green );
         fill = QBrush(cg.base(), Dense4Pattern);
         p->setBackgroundColor( c );
         p->setBrush( b );
      } 
      else if (flags & Style_Down)
         fill = cg.brush( QColorGroup::Button );
      else if (flags & Style_Enabled)
         fill = cg.brush( QColorGroup::Base );
      else
         fill = cg.brush( QColorGroup::Background );

      qDrawWinPanel( p, r, cg, TRUE, &fill );

      if (flags & Style_NoChange )
         p->setPen( cg.dark() );
      else
         p->setPen( cg.text() );
   } // FALLTHROUGH
   case PE_CheckListIndicator:
      if ( pe == PE_CheckListIndicator ) { //since we fall through from PE_Indicator
         if ( flags & Style_Enabled )
            p->setPen( QPen( cg.text(), 1 ) );
         else
            p->setPen( QPen( cg.dark(), 1 ) );
         if ( flags & Style_NoChange )
            p->setBrush( cg.brush( QColorGroup::Button ) );
         p->drawRect( r.x()+1, r.y()+1, 11*SCALE_CHECKBOX, 11*SCALE_CHECKBOX );
      }
      if (! (flags & Style_Off)) {
         QRect rr( r );
         QPointArray a( 16*2 ); // 7*2
         int i, xx, yy;
         xx = rr.x() + 3*SCALE_CHECKBOX-2;
         yy = rr.y() + 5*SCALE_CHECKBOX;

         for ( i=0; i<(3*SCALE_CHECKBOX); i++ ) {
            a.setPoint( 2*i,   xx, yy );
            a.setPoint( 2*i+1, xx, yy+2*SCALE_CHECKBOX );
            xx++; yy++;
         }

         yy -= 2;
         for ( i=(3*SCALE_CHECKBOX); i<16; i++ ) { // 7
            a.setPoint( 2*i,   xx, yy );
            a.setPoint( 2*i+1, xx, yy+2*SCALE_CHECKBOX );
            xx++; yy--;
         }
         p->drawLineSegments( a );
      }
   break;
   case PE_ExclusiveIndicator: 
   {
#define QCOORDARRLEN(x) sizeof(x)/(sizeof(QCOORD)*2)
      static const QCOORD pts1[] = {              // dark lines
         2,18, 1,16, 0,14, 0,8, 2,4, 3,3, 4,2, 6,1, 8,0, 14,0, 16,1, 18,2 };
      static const QCOORD pts2[] = {              // black lines
         3,16, 2,14, 2,8, 3,6, 4,4, 6,3, 8,2, 14,2, 16,3, 18,4 };
      static const QCOORD pts3[] = {              // background lines
         4,17, 6,19, 8,20, 14,20, 16,19, 18,18, 19,16, 20,14, 20,8, 19,6 };
      static const QCOORD pts4[] = {              // white lines
         4,20, 6,21, 8,22, 14,22, 16,21, 18,20, 20,18, 21,16, 22,14,
         22,8, 21,6, 20,4 };
      static const QCOORD pts5[] = {              // inner fill
         11,3, 14,4, 18,7, 19,11, 18,15, 16,17, 14,18, 11,19,
          8,18, 6,17, 4,15, 3,11, 4,7,   6,5,   8,4};

      // make sure the indicator is square
      QRect ir = r;

      if (r.width() < r.height()) {
         ir.setTop(r.top() + (r.height() - r.width()) / 2);
         ir.setHeight(r.width());
      } 
      else if (r.height() < r.width()) {
         ir.setLeft(r.left() + (r.width() - r.height()) / 2);
         ir.setWidth(r.height());
      }

      p->eraseRect(ir);
      bool down = flags & Style_Down;
      bool enabled = flags & Style_Enabled;
      bool on = flags & Style_On;
      QPointArray a;
      a.setPoints( QCOORDARRLEN(pts1), pts1 );
      a.translate( ir.x(), ir.y() );
      p->setPen( cg.dark() );
      p->drawPolyline( a );

      a.setPoints( QCOORDARRLEN(pts2), pts2 );
      a.translate( ir.x(), ir.y() );
      p->setPen( cg.shadow() );
      p->drawPolyline( a );

      a.setPoints( QCOORDARRLEN(pts3), pts3 );
      a.translate( ir.x(), ir.y() );
      p->setPen( cg.midlight() );
      p->drawPolyline( a );

      a.setPoints( QCOORDARRLEN(pts4), pts4 );
      a.translate( ir.x(), ir.y() );
      p->setPen( cg.light() );
      p->drawPolyline( a );

      a.setPoints( QCOORDARRLEN(pts5), pts5 );
      a.translate( ir.x(), ir.y() );
      QColor fillColor = ( down || !enabled ) ? cg.button() : cg.base();
      p->setPen( fillColor );
      p->setBrush( fillColor  ) ;
      p->drawPolygon( a );
      if ( on ) {
         p->setPen( NoPen );
         p->setBrush( cg.text() );
         p->drawRect( ir.x() + 9, ir.y() + 7,  4, 8 );
         p->drawRect( ir.x() + 7, ir.y() + 9,  8, 4 );
         p->drawRect( ir.x() + 8, ir.y() + 8,  6, 1 );
         p->drawRect( ir.x() + 8, ir.y() + 13, 6, 1 );
      }
      break;
   }
   default:
      QWindowsStyle::drawPrimitive( pe, p, r, cg, flags, opt );
      break;
   }
}


void cQtTouchStyle::drawComplexControl( ComplexControl ctrl, QPainter *p,
					const QWidget *widget,
					const QRect &r,
					const QColorGroup &cg,
					SFlags flags,
					SCFlags sub,
					SCFlags subActive,
					const QStyleOption& opt ) const
{
   switch( ctrl ) {
#ifndef QT_NO_LISTVIEW
   case CC_ListView:
   {
      if (_ChangeListViewBranchControl == false) {
         QWindowsStyle::drawComplexControl(ctrl, p, widget, r, cg, flags, sub, subActive, opt );
         return;
      }

      if ( sub & SC_ListView ) {
         QCommonStyle::drawComplexControl( ctrl, p, widget, r, cg, flags, sub, subActive, opt );
	  }
	  if ( sub & ( SC_ListViewBranch | SC_ListViewExpand ) ) {
         if (opt.isDefault())
            break;

		 QListViewItem *item = opt.listViewItem(),
		 *child = item->firstChild();

		 int y = r.y();
		 int c;
		 int dotoffset = 0;
		 QPointArray dotlines;
		 if ( subActive == (uint)SC_All && sub == SC_ListViewExpand ) {
		    c = 2;
		    dotlines.resize(2);
		    dotlines[0] = QPoint( r.right(), r.top() );
		    dotlines[1] = QPoint( r.right(), r.bottom() );
         } else {
		    int linetop = 0, linebot = 0;
		    // each branch needs at most two lines, ie. four end points
		    dotoffset = (item->itemPos() + item->height() - y) %2;
		    dotlines.resize( item->childCount() * 4 );
		    c = 0;

            // skip the stuff above the exposed rectangle
		    while ( child && y + child->height() <= 0 ) {
			   y += child->totalHeight();
			   child = child->nextSibling();
            }

		    int bx = r.width() / 2;

            // paint stuff in the magical area
		    QListView* v = item->listView();
		    while ( child && y < r.height() ) {
			   if (child->isVisible()) {
			      int lh;
			      if ( !item->multiLinesEnabled() )
			         lh = child->height();
			      else
			         lh = p->fontMetrics().height() + 2 * v->itemMargin();
			      lh = QMAX( lh, QApplication::globalStrut().height() );
			      if ( lh % 2 > 0 )
			         lh++;
			      linebot = y + lh/2;
		          bx = QMIN(bx, lh/2);
                  int bx_factor = bx * 6/10;
			      if ((child->isExpandable() || child->childCount()) &&
				      (child->height() > 0) ) {
				     // needs a box
				     p->setPen( cg.mid() );
				     p->drawRect( bx - bx_factor, linebot - bx_factor, bx + (bx/3), bx + (bx/3) );
				     // plus or minus
				     p->setPen( cg.text() );
				     p->drawLine( bx - (bx_factor-2), linebot, bx + (bx_factor-2), linebot );
				     if ( !child->isOpen() )
				        p->drawLine( bx, linebot - (bx_factor-2), bx, linebot + (bx_factor-2) );
				     // dotlinery
				     p->setPen( cg.mid() );
				     dotlines[c++] = QPoint( bx, linetop );
				     dotlines[c++] = QPoint( bx, linebot - bx_factor );
				     dotlines[c++] = QPoint( bx + bx_factor + 1, linebot );
				     dotlines[c++] = QPoint( r.width(), linebot );
				     linetop = linebot + bx_factor + 1;
                  } else {
				     // just dotlinery
				     dotlines[c++] = QPoint( bx+1, linebot -1);
				     dotlines[c++] = QPoint( r.width(), linebot -1);
                  }
			      y += child->totalHeight();
               }
			   child = child->nextSibling();
            }

		    // Expand line height to edge of rectangle if there's any
		    // visible child below
            int lh = bx*2;
		    while ( child && child->height() <= 0)
			   child = child->nextSibling();
            if ( child ) {
			   linebot = r.height();
               lh = child->height();
            }

            if ( linetop < linebot ) {
               bx = QMIN(bx, lh/2);
			   dotlines[c++] = QPoint( bx, linetop );
			   dotlines[c++] = QPoint( bx, linebot );
            }
         }
		 p->setPen( cg.text() );

		 static QBitmap *verticalLine = 0, *horizontalLine = 0;
		 static QCleanupHandler<QBitmap> qlv_cleanup_bitmap;
		 if ( !verticalLine ) {
		    // make 128*1 and 1*128 bitmaps that can be used for
		    // drawing the right sort of lines.
		    verticalLine = new QBitmap( 1, 129, TRUE );
		    horizontalLine = new QBitmap( 128, 1, TRUE );
		    QPointArray a( 64 );
		    QPainter p;
		    p.begin( verticalLine );
		    int i;
		    for( i=0; i<64; i++ )
		       a.setPoint( i, 0, i*2+1 );
		    p.setPen( color1 );
		    p.drawPoints( a );
		    p.end();
		    QApplication::flushX();
		    verticalLine->setMask( *verticalLine );
		    p.begin( horizontalLine );
		    for( i=0; i<64; i++ )
		       a.setPoint( i, i*2+1, 0 );
		    p.setPen( color1 );
		    p.drawPoints( a );
		    p.end();
		    QApplication::flushX();
		    horizontalLine->setMask( *horizontalLine );
		    qlv_cleanup_bitmap.add( &verticalLine );
		    qlv_cleanup_bitmap.add( &horizontalLine );
         }

		 int line; // index into dotlines
		 if ( sub & SC_ListViewBranch ) for( line = 0; line < c; line += 2 ) {
		    // assumptions here: lines are horizontal or vertical.
		    // lines always start with the numerically lowest
		    // coordinate.

            // point ... relevant coordinate of current point
		    // end ..... same coordinate of the end of the current line
		    // other ... the other coordinate of the current point/line
		    if ( dotlines[line].y() == dotlines[line+1].y() ) {
		       int end = dotlines[line+1].x();
			   int point = dotlines[line].x();
			   int other = dotlines[line].y();
			   while( point < end ) {
			      int i = 128;
			      if ( i+point > end )
			         i = end-point;
			      p->drawPixmap(point, other, *horizontalLine,
			  	                0, 0, i, 1 );
			      point += i;
               }
            } else {
			   int end = dotlines[line+1].y();
			   int point = dotlines[line].y();
			   int other = dotlines[line].x();
			   int pixmapoffset = ((point & 1) != dotoffset ) ? 1 : 0;
			   while( point < end ) {
			      int i = 128;
			      if ( i+point > end )
			         i = end-point;
			      p->drawPixmap(other, point, *verticalLine,
			    	            0, pixmapoffset, 1, i );
			      point += i;
               }
            }
         }
      }
   }
   break;
#endif //QT_NO_LISTVIEW
   default:
      QWindowsStyle::drawComplexControl(ctrl, p, widget, r, cg, flags,
	                  				    sub, subActive, opt );
   break;
   }
}


int cQtTouchStyle::pixelMetric (PixelMetric metric, const QWidget * widget) const
{
   int base_return = QWindowsStyle::pixelMetric( metric, widget );
   
   switch ( metric ) {
   case PM_TabBarScrollButtonWidth:
   case PM_ScrollBarExtent:
      return _scroll_bar_width_multiplier * base_return;
   default: break;
   }

   return base_return;
}


QRect cQtTouchStyle::querySubControlMetrics (ComplexControl control, 
   const QWidget * widget, 
   SubControl subcontrol, 
   const QStyleOption & opt ) const
{
   QRect base_return = QWindowsStyle::querySubControlMetrics( control, widget, subcontrol, opt );

   switch ( control ) {
   case CC_ComboBox:
      {
         switch ( subcontrol ) {
         case SC_ComboBoxArrow:         
            // Kein Pfeil-Button
            return QRect();
         case SC_ComboBoxEditField:
            // Breite bzw. rechter Rand wird vom linken Rand abgeleitet
            base_return.setWidth(widget->width() - 2*base_return.left());
            return base_return;
         default: break;
         }
      }
      break; 
   default: break;
   }

   return base_return;
}


QRect cQtTouchStyle::subRect ( SubRect subrect, const QWidget * widget ) const
{
   QRect base_return = QWindowsStyle::subRect ( subrect, widget );

   switch ( subrect ) {
   case SR_ComboBoxFocusRect:
      // Breite bzw. rechter Rand wird vom linken Rand abgeleitet
      base_return.setWidth(widget->width() - 2*base_return.left());
      return base_return;
   case SR_RadioButtonIndicator:
   {
      int scaled_base_height = base_return.height() * 2;
      int y1 = (widget->height() - scaled_base_height) / 2;
      base_return.setRect(X_OFFSET_RADIOBUTTON, y1, scaled_base_height, scaled_base_height);
      break;
   }
   case SR_CheckBoxIndicator:
   {
      int scaled_base_height = (base_return.height()-1) * 2;
      int y1 = (widget->height() - scaled_base_height) / 2;
      base_return.setRect(0, y1, scaled_base_height, scaled_base_height);
      break;
   }
   default: break;
   }

   return base_return;
}

