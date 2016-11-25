
#include "qt4port.h"
#include <QProxyStyle>
#include <QApplication>


#ifdef QT4

class cQtTouchStyle : public QProxyStyle {
	Q_OBJECT
public:
   cQtTouchStyle(float _multiplier, float xDisplayScale = 1.0f, float yDisplayScale = 1.0f);
   ~cQtTouchStyle();

   QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const;
   int pixelMetric (PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0) const;
   void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
   QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const;
   void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const;

private:
   cQtTouchStyle( const cQtTouchStyle & );
   cQtTouchStyle& operator=( const cQtTouchStyle & );
   float _multiplier;
   float _xDisplayScale;
   float _yDisplayScale;
};

class cWizardStyle : public QProxyStyle
{

public:
    cWizardStyle(float xDisplayScale = 1.0f, float yDisplayScale = 1.0f)
        : QProxyStyle(), _LayoutHorizontalSpacing(15),
        _xDisplayScale(xDisplayScale), _yDisplayScale(yDisplayScale)
    {
        if (_xDisplayScale != 1.0f) {
            qreal qScaledLayoutValue = qreal(_LayoutHorizontalSpacing) * _xDisplayScale;
            _LayoutHorizontalSpacing = qRound(qScaledLayoutValue);
        }

        setBaseStyle(qApp->style());
    }

    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const
    {
        if (metric == QStyle::PM_LayoutHorizontalSpacing) {
            return _LayoutHorizontalSpacing;
        }
        return QProxyStyle::pixelMetric(metric, option, widget);
    }

private:
    float _xDisplayScale;
    float _yDisplayScale;
    int _LayoutHorizontalSpacing;
};

#else

#include <qwindowsstyle.h>

class cQtTouchStyle : public QWindowsStyle {
   Q_OBJECT
public:
   cQtTouchStyle(float _multiplier, bool antialias_arrows = false, bool change_listview_branch_control = false);
   ~cQtTouchStyle();
   
   void drawPrimitive(PrimitiveElement pe,
      QPainter *p,
      const QRect & r,
      const QColorGroup & cg,
      SFlags flags = Style_Default,
      const QStyleOption & opt = QStyleOption::Default) const;
   
   void drawComplexControl( ComplexControl control,
      QPainter* p,
      const QWidget* widget,
      const QRect& r,
      const QColorGroup& cg,
      SFlags flags = Style_Default,
#ifdef Q_QDOC
      SCFlags sub = SC_All,
#else
      SCFlags sub = (uint)SC_All,
#endif
      SCFlags subActive = SC_None,
      const QStyleOption& = QStyleOption::Default ) const;

   int pixelMetric (PixelMetric metric, const QWidget * widget = 0) const;

   QRect querySubControlMetrics (ComplexControl control, 
      const QWidget * widget, 
      SubControl subcontrol, 
      const QStyleOption & opt = QStyleOption::Default ) const;

   QRect subRect ( SubRect subrect, const QWidget * widget ) const;

private:
   cQtTouchStyle( const cQtTouchStyle & );
   cQtTouchStyle& operator=( const cQtTouchStyle & );
   float _multiplier;
   bool _AntiAliasArrows;
   bool _ChangeListViewBranchControl;
};

#endif
