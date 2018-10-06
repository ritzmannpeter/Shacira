
#ifdef QT4
#include <QHeaderView>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

#include "cQtTouchStyle.h"
#include <QStyleOption>

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <qdrawutil.h>
#endif


#define X_OFFSET_RADIOBUTTON 5
#define SCALE_CHECKBOX 2


cQtTouchStyle::cQtTouchStyle(float multiplier, float xDisplayScale, float yDisplayScale)
   : QProxyStyle(),
   _multiplier(multiplier), _xDisplayScale(xDisplayScale), _yDisplayScale(yDisplayScale)
{
}

cQtTouchStyle::~cQtTouchStyle()
{
}

QRect cQtTouchStyle::subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const
{
   if (sc == SC_ComboBoxEditField) {
      if (const QStyleOptionComboBox *cb = qstyleoption_cast<const QStyleOptionComboBox *>(opt)) {
         int x = cb->rect.x();
         int y = cb->rect.y();
         int wi = cb->rect.width();
         int he = cb->rect.height();
         int margin = cb->frame ? 3 : 0;
         return QRect(x + margin, y + margin, wi - 2 * margin, he - 2 * margin);
      }
   }
   return QProxyStyle::subControlRect(cc, opt, sc, widget);
}

#if QT_VERSION >= QT_VERSION_CHECK(5,7,0)
QRect cQtTouchStyle::subElementRect(SubElement sr, const QStyleOption *opt, const QWidget *widget) const
{
   if (sr == SE_TabBarScrollLeftButton) {
      QRect r;
      const bool vertical = opt->rect.width() < opt->rect.height();
      const Qt::LayoutDirection ld = widget->layoutDirection();
      const int buttonWidth = qMax(pixelMetric(QStyle::PM_TabBarScrollButtonWidth, 0, widget), QApplication::globalStrut().width());
      const int buttonOverlap = pixelMetric(QStyle::PM_TabBar_ScrollButtonOverlap, 0, widget); 

      r = vertical ? QRect(0, opt->rect.height() - (buttonWidth * 2) + buttonOverlap, opt->rect.width(), buttonWidth)
          : QStyle::visualRect(ld, opt->rect, QRect(opt->rect.width() - (buttonWidth * 2) + buttonOverlap, 0, buttonWidth, opt->rect.height()));
      return r;
   }

   return QProxyStyle::subElementRect(sr, opt, widget);
}
#endif

int cQtTouchStyle::pixelMetric (PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
   int base_return = QProxyStyle::pixelMetric(metric, option, widget);

   switch (metric) {
   case PM_ScrollBarExtent:
      if ((widget == NULL) || 
          (widget->inherits("QWebView")) || 
          (widget->inherits("QScrollBar"))) {
         base_return *= _multiplier;
      }
      break;
   case PM_IndicatorWidth: // checkbox:
   case PM_IndicatorHeight: 
   case PM_ExclusiveIndicatorWidth: // radiobutton:
   case PM_ExclusiveIndicatorHeight:
      base_return *= SCALE_CHECKBOX;
	  break;
#if QT_VERSION >= QT_VERSION_CHECK(5,7,0)
   case PM_TabBarScrollButtonWidth:
       base_return *= _multiplier;
	   break;
#endif
   }
   return base_return;	  
}

void cQtTouchStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
   switch (element) {
   case QStyle::CE_HeaderLabel:
      if (const QStyleOptionHeader *header = qstyleoption_cast<const QStyleOptionHeader *>(option)) {
         QRect rect = header->rect;
         if (!header->icon.isNull()) {
            QPixmap pixmap
                    = header->icon.pixmap(proxy()->pixelMetric(PM_LargeIconSize), (header->state & State_Enabled) ? QIcon::Normal : QIcon::Disabled);
            int pixw = pixmap.width();

            QRect aligned = alignedRect(header->direction, QFlag(header->iconAlignment), pixmap.size(), rect);
            QRect inter = aligned.intersected(rect);
            painter->drawPixmap(inter.x(), inter.y(), pixmap, inter.x() - aligned.x(), inter.y() - aligned.y(), inter.width(), inter.height());

            if (header->direction == Qt::LeftToRight)
                rect.setLeft(rect.left() + pixw + 2);
            else
                rect.setRight(rect.right() - pixw - 2);
         }
      
         if (header->state & QStyle::State_On) {
            QFont fnt = painter->font();
            fnt.setBold(true);
            painter->setFont(fnt);
         }
         proxy()->drawItemText(painter, rect, header->textAlignment, header->palette,
                               (header->state & State_Enabled), header->text, QPalette::ButtonText);
         return;
      }
      break;
   }

   return QProxyStyle::drawControl(element, option, painter, widget);
}

QSize cQtTouchStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    if (type == QStyle::CT_HeaderSection) {
        if (const QStyleOptionHeader *hdr = qstyleoption_cast<const QStyleOptionHeader *>(option)) {
            QSize correctOrgSize(size);
            if (const QStyleOptionHeader *hdr = qstyleoption_cast<const QStyleOptionHeader *>(option)) {
                bool nullIcon = hdr->icon.isNull();
                int margin = proxy()->pixelMetric(QStyle::PM_HeaderMargin, hdr, widget);
                int iconSize = nullIcon ? 0 : proxy()->pixelMetric(QStyle::PM_SmallIconSize, hdr, widget);
                QSize txt = hdr->fontMetrics.size(0, hdr->text);
                correctOrgSize.setHeight(margin + qMax(iconSize, txt.height()) + margin);
                correctOrgSize.setWidth((nullIcon ? 0 : margin) + iconSize
                                        + (hdr->text.isEmpty() ? 0 : margin) + txt.width() + margin);
            }

            QSize orgSize = QProxyStyle::sizeFromContents(type,option, size, widget);
            if (orgSize != correctOrgSize) {
                orgSize = correctOrgSize;
            }

            QPixmap largePixmap = hdr->icon.pixmap(proxy()->pixelMetric(PM_LargeIconSize), (hdr->state & State_Enabled) ? QIcon::Normal : QIcon::Disabled);
            QPixmap smallPixmap = hdr->icon.pixmap(proxy()->pixelMetric(PM_SmallIconSize), (hdr->state & State_Enabled) ? QIcon::Normal : QIcon::Disabled);
            QSize sizeDifference = largePixmap.size() - smallPixmap.size();

            return orgSize+sizeDifference;
        }
    }

   return QProxyStyle::sizeFromContents(type,option, size, widget);
}

void cQtTouchStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    // Used to restore across fallthrough cases. Currently only used in PE_IndicatorCheckBox
    bool doRestore = false;

    switch (pe) {
    case PE_IndicatorCheckBox: {
        QBrush fill;
        if (opt->state & State_NoChange)
            fill = QBrush(opt->palette.base().color(), Qt::Dense4Pattern);
        else if (opt->state & State_Sunken)
            fill = opt->palette.button();
        else if (opt->state & State_Enabled)
            fill = opt->palette.base();
        else
            fill = opt->palette.background();
        p->save();
        doRestore = true;
        qDrawWinPanel(p, opt->rect, opt->palette, true, &fill);
        if (opt->state & State_NoChange)
            p->setPen(opt->palette.dark().color());
        else
            p->setPen(opt->palette.text().color());
        } // Fall through!
    case PE_IndicatorViewItemCheck:
        if (!doRestore) {
            p->save();
            doRestore = true;
        }
        if (pe == PE_IndicatorViewItemCheck) {
            const QStyleOptionViewItem *itemViewOpt = qstyleoption_cast<const QStyleOptionViewItem *>(opt);
            p->setPen(itemViewOpt
                      && itemViewOpt->showDecorationSelected
                      && opt->state & State_Selected
                        ? opt->palette.highlightedText().color()
                        : opt->palette.text().color());
            if (opt->state & State_NoChange)
                p->setBrush(opt->palette.brush(QPalette::Button));
            p->drawRect(opt->rect.x() + 1, opt->rect.y() + 1, 11*SCALE_CHECKBOX, 11*SCALE_CHECKBOX);
        }
        if (!(opt->state & State_Off)) {
            QLineF lines[(7*SCALE_CHECKBOX) + 2];
            int i, xx, yy;
            xx = opt->rect.x() + 3*SCALE_CHECKBOX-2;
            yy = opt->rect.y() + 5*SCALE_CHECKBOX;
            for (i = 0; i < 3*SCALE_CHECKBOX; ++i) {
                lines[i] = QLineF(xx, yy, xx, yy + (2*SCALE_CHECKBOX));
                ++xx;
                ++yy;
            }
            yy -= 2;
            for (i = (3*SCALE_CHECKBOX); i < ((7*SCALE_CHECKBOX) + 2); ++i) {
                lines[i] = QLineF(xx, yy, xx, yy + (2*SCALE_CHECKBOX));
                ++xx;
                --yy;
            }
            p->drawLines(lines, ((7*SCALE_CHECKBOX) + 2));
        }
        if (doRestore)
            p->restore();
        break;
    case PE_IndicatorRadioButton:
        {
#define PTSARRLEN(x) sizeof(x)/(sizeof(QPoint))
            static const QPoint pts1[] = {              // dark lines
                QPoint(2, 18), QPoint(1, 16), QPoint(0, 14), QPoint(0, 8), QPoint(2, 4), QPoint(3, 3),
                QPoint(4, 2), QPoint(6, 1), QPoint(8, 0), QPoint(14, 0), QPoint(16, 1), QPoint(18, 2)
                //QPoint(1, 9), QPoint(1, 8), QPoint(0, 7), QPoint(0, 4), QPoint(1, 3), QPoint(1, 2),
                //QPoint(2, 1), QPoint(3, 1), QPoint(4, 0), QPoint(7, 0), QPoint(8, 1), QPoint(9, 1)
            };
            static const QPoint pts2[] = {              // black lines
                QPoint(3, 16), QPoint(2, 14), QPoint(2, 8), QPoint(3, 6), QPoint(4, 4), QPoint(6, 3),
                QPoint(8, 2), QPoint(14, 2), QPoint(16, 3), QPoint(18, 4)
                //QPoint(2, 8), QPoint(1, 7), QPoint(1, 4), QPoint(2, 3), QPoint(2, 2), QPoint(3, 2),
                //QPoint(4, 1), QPoint(7, 1), QPoint(8, 2), QPoint(9, 2)
            };
            static const QPoint pts3[] = {              // background lines
                QPoint(4, 17), QPoint(6, 19), QPoint(8, 20), QPoint(14, 20), QPoint(16, 19), QPoint(18, 18),
                QPoint(9, 8), QPoint(10, 7), QPoint(10, 4), QPoint(9, 3)
                //QPoint(2, 9), QPoint(3, 9), QPoint(4, 10), QPoint(7, 10), QPoint(8, 9), QPoint(9, 9),
                //QPoint(9, 8), QPoint(10, 7), QPoint(10, 4), QPoint(9, 3)
            };
            static const QPoint pts4[] = {              // white lines
                QPoint(4, 20), QPoint(6, 21), QPoint(8, 22), QPoint(14, 22), QPoint(16, 21),
                QPoint(18, 20), QPoint(20, 18), QPoint(21, 16), QPoint(22, 14), QPoint(22, 8),
                QPoint(21, 6), QPoint(20, 4)
                //QPoint(2, 10), QPoint(3, 10), QPoint(4, 11), QPoint(7, 11), QPoint(8, 10),
                //QPoint(9, 10), QPoint(10, 9), QPoint(10, 8), QPoint(11, 7), QPoint(11, 4),
                //QPoint(10, 3), QPoint(10, 2)
            };
            static const QPoint pts5[] = {              // inner fill
                QPoint(11, 3), QPoint(14, 4), QPoint(18, 7), QPoint(19, 11), QPoint(18, 15), QPoint(16, 17),
                QPoint(14, 18), QPoint(11, 19), QPoint(8, 18), QPoint(6, 17), QPoint(4, 15), QPoint(3, 11),
                QPoint(4, 7), QPoint(6, 5), QPoint(8, 4)
                //QPoint(4, 2), QPoint(7, 2), QPoint(9, 4), QPoint(9, 7), QPoint(7, 9), QPoint(4, 9),
                //QPoint(2, 7), QPoint(2, 4)
            };

            // make sure the indicator is square
            QRect ir = opt->rect;

            if (opt->rect.width() < opt->rect.height()) {
                ir.setTop(opt->rect.top() + (opt->rect.height() - opt->rect.width()) / 2);
                ir.setHeight(opt->rect.width());
            } else if (opt->rect.height() < opt->rect.width()) {
                ir.setLeft(opt->rect.left() + (opt->rect.width() - opt->rect.height()) / 2);
                ir.setWidth(opt->rect.height());
            }

            p->save();
            bool down = opt->state & State_Sunken;
            bool enabled = opt->state & State_Enabled;
            bool on = opt->state & State_On;
            QPolygon a;

            //center when rect is larger than indicator size
            int xOffset = 0;
            int yOffset = 0;
            int indicatorWidth = proxy()->pixelMetric(PM_ExclusiveIndicatorWidth);
            int indicatorHeight = proxy()->pixelMetric(PM_ExclusiveIndicatorWidth);
            if (ir.width() > indicatorWidth)
                xOffset += (ir.width() - indicatorWidth)/2;
            if (ir.height() > indicatorHeight)
                yOffset += (ir.height() - indicatorHeight)/2;
            p->translate(xOffset, yOffset);

            p->translate(ir.x(), ir.y());

            p->setPen(opt->palette.dark().color());
            p->drawPolyline(pts1, PTSARRLEN(pts1));

            p->setPen(opt->palette.shadow().color());
            p->drawPolyline(pts2, PTSARRLEN(pts2));

            p->setPen(opt->palette.midlight().color());
            p->drawPolyline(pts3, PTSARRLEN(pts3));

            p->setPen(opt->palette.light().color());
            p->drawPolyline(pts4, PTSARRLEN(pts4));

            QColor fillColor = (down || !enabled)
                               ? opt->palette.button().color()
                               : opt->palette.base().color();
            p->setPen(fillColor);
            p->setBrush(fillColor) ;
            p->drawPolygon(pts5, PTSARRLEN(pts5));

            p->translate(-ir.x(), -ir.y()); // restore translate

            if (on) {
                p->setPen(Qt::NoPen);
                p->setBrush(opt->palette.text());
                p->drawRect( ir.x() + 9, ir.y() + 7,  4, 8 );
                p->drawRect( ir.x() + 7, ir.y() + 9,  8, 4 );
                p->drawRect( ir.x() + 8, ir.y() + 8,  6, 1 );
                p->drawRect( ir.x() + 8, ir.y() + 13, 6, 1 );
                //p->drawRect(ir.x() + 5, ir.y() + 4, 2, 4);
                //p->drawRect(ir.x() + 4, ir.y() + 5, 4, 2);
            }
            p->restore();
            break;
        }
    default:
        QProxyStyle::drawPrimitive(pe, opt, p, w);
    }
}

#else

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

cQtTouchStyle::cQtTouchStyle(float multiplier, bool antialias_arrows, bool change_listview_branch_control) :
   _multiplier(multiplier),
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
      return _multiplier * base_return;
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

#endif
