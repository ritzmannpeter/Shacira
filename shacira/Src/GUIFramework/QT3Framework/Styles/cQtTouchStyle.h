
#include <qwindowsstyle.h>

class cQtTouchStyle : public QWindowsStyle {
   Q_OBJECT
public:
   cQtTouchStyle(double scroll_bar_width_multiplier, bool antialias_arrows = false, bool change_listview_branch_control = false);
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
   double _scroll_bar_width_multiplier;
   bool _AntiAliasArrows;
   bool _ChangeListViewBranchControl;
};

