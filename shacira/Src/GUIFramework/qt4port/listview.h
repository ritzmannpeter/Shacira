
#ifndef _listview_h_
#define _listview_h_

#define USE_DELEGATES

#include <qwidget.h>
#include <qstring.h>
#include <qtreewidget.h>
#include <qabstractitemmodel.h>
#include <qtimer.h>

#ifdef QT4
#include "qt4port.h"
#include "pluginfactory.h"
#else
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#define NOT_PORTED(msg)
#define _CWIDGET_EXPORT_
#endif

class ListView;
class ListViewItem;
class HeaderView;

#define RESIZE_COLUMNS_TO_CONTENTS  0x00000001
#define STRETCH_LAST_SECTION        0x00000002

class _CWIDGET_EXPORT_ ListView : public QTreeWidget
{
   Q_OBJECT

public:
   Q_PROPERTY(bool autoAdjustColumnSize READ getAutoAdjustColumnSize WRITE setAutoAdjustColumnSize)
   Q_PROPERTY(bool optimizeAppearanceAfterEventShow READ getOptimizeAppearanceAfterEventShow WRITE setOptimizeAppearanceAfterEventShow)

   friend class ListViewItem;
   enum ColorRole {
        Window = QPalette::Window,
        WindowText = QPalette::WindowText,
        Base = QPalette::Base,
        AlternateBase = QPalette::AlternateBase,
        ToolTipBase = QPalette::ToolTipBase,
        ToolTipText = QPalette::ToolTipText,
        Text = QPalette::Text,
        Button = QPalette::Button,
        ButtonText = QPalette::ButtonText,
        BrightText = QPalette::BrightText
   };
#ifdef qt3_doku
QListView::Manual - the column width does not change automatically. 
QListView::Maximum - the column is automatically sized according to the widths of all items in the column. (Note: The column never shrinks in this case.) This means that the column is always resized to the width of the item with the largest width in the column.
#endif
   enum ColumnWidthMode {
      Manual,
      Maximum
   };
#ifdef qt3_doku
QListView::NoColumn - The columns do not get resized in resize events. 
QListView::AllColumns - All columns are resized equally to fit the width of the list view. 
QListView::LastColumn - The last column is resized to fit the width of the list view. 
#endif
   enum ResizeMode {
      NoColumn,
      AllColumns,
      LastColumn
   };

   static inline QPalette::ColorRole role(ColorRole role)
   {
      switch (role) {
      case Window: return QPalette::Window;
      case WindowText: return QPalette::WindowText;
      case Base: return QPalette::Base;
      case AlternateBase: return QPalette::AlternateBase;
      case ToolTipBase: return QPalette::ToolTipBase;
      case ToolTipText: return QPalette::ToolTipText;
      case Text: return QPalette::Text;
      case Button: return QPalette::Button;
      case ButtonText: return QPalette::ButtonText;
      case BrightText: return QPalette::BrightText;
      }
      return QPalette::Window;
   };

public:
   ListView(QWidget * parent = NULL, const char * name = NULL, Qt::WindowFlags flags = 0);
   virtual ~ListView();

   bool hasCustomDelegate() const;
   HeaderView * header() const;
   ListViewItem * item(int row) const;
   ListViewItem * currentItem() const;
   ListViewItem * firstChild() const;
   ListViewItem * selectedItem() const;
   void setSelected(ListViewItem * item, bool state);
   void sort();
   int childCount() const;
   void setSelectionAnchor(ListViewItem * item);
   void setContentsPos(int x, int y);
   virtual int addColumn(const QString & label, int width = -1);
   virtual int addColumn(const QIcon & icon, const QString & label = QString(), int width = -1);
   virtual int addColumn(const QPixmap & pixmap, const QString & label, int width = -1);
   virtual int addColumn(const QImage & image, const QString & label, int width = -1);
   virtual int addColumn(const QPixmap & pixmap, int width = -1);
   virtual int addColumn(const QImage & image, int width = -1);
   int columns() const;
   void setHeaderLabel(int column, const QString & text);
   void setHeaderLabel(int column, const QIcon & icon, const QString & text);
   void setHorizontalHeaderLabel(int column, const QString & label);
   QString headerLabel(int column) const;
   ListViewItem * lastItem() const;
   void triggerUpdate();
   QPoint contentsToViewport(const QPoint & point) const;
   ListViewItem * itemAt(const QPoint & point) const;
   int treeStepSize() const;
   void setTreeStepSize(int stepSize);
   bool isOpen(ListViewItem * item);
   virtual void setOpen(ListViewItem * item, bool state);
   QRect itemRect(ListViewItem * item) const;
   int itemMargin() const;
   void ensureItemVisible(ListViewItem * item);
   int visibleWidth() const;
   int contentsWidth() const;
   virtual void setColumnWidthMode(int column, ColumnWidthMode mode);
   bool isSelected(ListViewItem * item) const;
   virtual void setResizeMode(ResizeMode mode);
   ResizeMode resizeMode() const;
   void setItemHeight(int height);
   void setAutoAdjustColumnSize(bool state)
   {
      _autoAdjustColumnSizeValue = state;
   };
   bool getAutoAdjustColumnSize() const 
   { 
      return _autoAdjustColumnSizeValue; 
   };
   void setOptimizeAppearanceAfterEventShow(bool state)
   {
      _optimizeAppearanceAfterEventShowValue = state;
   };
   bool getOptimizeAppearanceAfterEventShow() const 
   { 
      return _optimizeAppearanceAfterEventShowValue; 
   };
// QT3 compatibility methods
   virtual void setColumnText(int column, const QString & label);
   virtual void setColumnText(int column, const QIcon & icon, const QString & label);
   QString columnText(int column) const;
   virtual void setColumnWidth(int column, int width);
   int columnWidth(int column) const;
   virtual void setColumnAlignment(int column, int align);
   int columnAlignment(int column) const;
   virtual void setSorting(int column, bool ascending = true);
   void adjustColumn(int column, int width = -1);
   unsigned int appearanceStyle() const;
   void setAppearanceStyle(unsigned int style);
   void optimizeAppearance(unsigned int style);
   bool isShown() const
   {
      return _shown;
   };
// reimplemented virtual protected methods

protected:
   virtual bool event(QEvent * e);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   virtual void	languageChange () {};
   inline virtual void changeEvent(QEvent * event )
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      QTreeWidget::changeEvent(event);
   };
#endif
   virtual bool viewportEvent(QEvent *event);
   virtual void mousePressEvent(QMouseEvent * mouseEvent);
   virtual void mouseReleaseEvent(QMouseEvent * mouseEvent);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   virtual void mouseMoveEvent(QMouseEvent * mouseEvent);
#endif
   virtual void contentsMousePressEvent(QMouseEvent * mouseEvent);
   virtual void contentsMouseReleaseEvent(QMouseEvent * mouseEvent);
   virtual void drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index) const;
   virtual void drawRow(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
   virtual void drawChildren(ListViewItem * listViewItem, QPainter * painter, const QStyleOptionViewItem & option) const;
   virtual void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
   virtual int sizeHintForColumn(int column) const;
   virtual void adjustColumnWidths();
   int maxColumnWidth(QTreeWidgetItem * item, int column, int itemIndentation, int &recursivLevel);
// mapping of QTreeWidget signals to (Q)ListView signals
// using specific private slots
// this emulates Qt3 QListView signals

   QTimer * _columnWidthTimer;

protected slots:
   void slotCurrentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
   void slotItemActivated(QTreeWidgetItem * item, int column);
   virtual void slotItemClicked(QTreeWidgetItem * item, int column);
   void slotItemCollapsed(QTreeWidgetItem * item);
   void slotItemDoubleClicked(QTreeWidgetItem * item, int column);
   void slotItemExpanded(QTreeWidgetItem * item);
   void slotItemSelectionChanged();
   void slotSectionCountChanged(int oldCount, int newCount);

signals:
   void clicked(ListViewItem * item);
   void doubleClicked(ListViewItem * item, const QPoint & point, int column =-1);
   void doubleClicked(ListViewItem * item);
   void rightButtonClicked(ListViewItem * item, const QPoint & point, int column =-1);
   void returnPressed(ListViewItem * item);
   void selectionChanged();
   void selectionChanged(ListViewItem * item);
   void collapsed(ListViewItem * item);
   void expanded(ListViewItem * item);
   void contextMenuRequested(ListViewItem * item, const QPoint & pos, int column = -1);

private:
   int _treeStepSize;
   ResizeMode _resizeMode;
   QMap<int,ColumnWidthMode> _columnWidthMode;
   QMap<int,Qt::Alignment> _columnAlignment;
   QMap<int,int> _columnWidth;
   int _appearanceStyle;
   bool _shown;
   bool _autoAdjustColumnSizeValue;
   bool _optimizeAppearanceAfterEventShowValue;

private:
   int addColumn();
   ColumnWidthMode columnWidthMode(int column) const;
   QTreeWidgetItem * getLastLevelItem(QTreeWidgetItem* lastLevelItem) const;

protected slots:
   void slotAdjustColumnWidths();
   virtual void expandCollapseItem(const QModelIndex & index);
};

#include "listviewitem.h"
#include "listviewitemiterator.h"
#include "headerview.h"

#ifdef doku
//  signals emitted by qt3 QListView
void selectionChanged () 
void selectionChanged ( QListViewItem * ) 
void currentChanged ( QListViewItem * ) 
void clicked ( QListViewItem * item ) 
void clicked ( QListViewItem * item, const QPoint & pnt, int c ) 
void pressed ( QListViewItem * item ) 
void pressed ( QListViewItem * item, const QPoint & pnt, int c ) 
void doubleClicked ( QListViewItem * item )  (obsolete) 
void doubleClicked ( QListViewItem *, const QPoint &, int ) 
void returnPressed ( QListViewItem * ) 
void spacePressed ( QListViewItem * ) 
void rightButtonClicked ( QListViewItem *, const QPoint &, int ) 
void rightButtonPressed ( QListViewItem *, const QPoint &, int ) 
void mouseButtonPressed ( int button, QListViewItem * item, const QPoint & pos, int c ) 
void mouseButtonClicked ( int button, QListViewItem * item, const QPoint & pos, int c ) 
void contextMenuRequested ( QListViewItem * item, const QPoint & pos, int col ) 
void onItem ( QListViewItem * i ) 
void onViewport () 
void expanded ( QListViewItem * item ) 
void collapsed ( QListViewItem * item ) 
void dropped ( QDropEvent * e ) 
void itemRenamed ( QListViewItem * item, int col, const QString & text ) 
void itemRenamed ( QListViewItem * item, int col )
#endif

#ifdef documentation_of_palette_color_role
QPalette::Window	10	A general background color.
QPalette::Background	Window	This value is obsolete. Use Window instead.
QPalette::WindowText	0	A general foreground color.
QPalette::Foreground	WindowText	This value is obsolete. Use WindowText instead.
QPalette::Base	9	Used mostly as the background color for text entry widgets, but can also be used for other painting - such as the background of combobox drop down lists and toolbar handles. It is usually white or another light color.
QPalette::AlternateBase	16	Used as the alternate background color in views with alternating row colors (see QAbstractItemView::setAlternatingRowColors()).
QPalette::ToolTipBase	18	Used as the background color for QToolTip and QWhatsThis. Tool tips use the Inactive color group of QPalette, because tool tips are not active windows.
QPalette::ToolTipText	19	Used as the foreground color for QToolTip and QWhatsThis. Tool tips use the Inactive color group of QPalette, because tool tips are not active windows.
QPalette::Text	6	The foreground color used with Base. This is usually the same as the WindowText, in which case it must provide good contrast with Window and Base.
QPalette::Button	1	The general button background color. This background can be different from Window as some styles require a different background color for buttons.
QPalette::ButtonText	8	A foreground color used with the Button color.
QPalette::BrightText	7	A text color that is very different from WindowText,
                        and contrasts well with e.g. Dark.
                        Typically used for text that needs to be drawn where Text or WindowText
                        would give poor contrast, such as on pressed push buttons.
                        Note that text colors can be used for things other than just words;
                        text colors are usually used for text,
                        but it's quite common to use the text color roles for lines, icons, etc.
#endif

#endif // _listview_h_


