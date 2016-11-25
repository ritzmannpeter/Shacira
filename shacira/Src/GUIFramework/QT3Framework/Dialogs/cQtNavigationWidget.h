

#ifndef _cqtnavigationwidget_h_
#define _cqtnavigationwidget_h_

#include <qwidget.h>
#include <qptrvector.h>
#include "CAppFrame.h"
#include "CGroupSelectButton.h"

#define FONT_POINT_SIZE 0
#define FONT_PIXEL_SIZE 1

class cQtNavigationWidget;

class cPageDescription {
public:
   cPageDescription(cQtNavigationWidget * widget, CAppFrame * app_frame,
                    CPage * page);
   virtual ~cPageDescription();
   void SetVisibleRect(QRect & rectangle);
   QRect VisibleRect();
   QString PageName();
   QString GroupName();
   QString PageHeadline();
   QString LongPageHeadline();
   BOOL_T IsVisible();
   BOOL_T IsSelected(QPoint pos);
   void Draw(QPainter & painter);
   int AbsPos();
   void SetRelPos(int pos);
   int GetRelPos();
private:
   QRect _VisibleRect;
   cQtNavigationWidget * _Widget;
   CAppFrame * _AppFrame;
   CPage * _Page;
   int _RelPos;
};

class cGroupDescription {
public:
   cGroupDescription(cQtNavigationWidget * widget, CAppFrame * app_frame,
                     CGroupSelectButton * select_button);
   virtual ~cGroupDescription();
   QString GroupName();
   QString GroupText();
   QPixmap GroupIcon();
   void SetVisibleRect(QRect & rectangle, int group_index = 0);
   QRect VisibleRect();
   void SetPageDescription(cPageDescription * page_desc, int pos);
   QString SelectedPage(QPoint pos);
   int Pages();
   void Draw(QPainter & painter);
   void SetRight(BOOL_T state);
   BOOL_T GetRight();
   BOOL_T IsVisible();
private:
   QRect _VisibleRect;
   cQtNavigationWidget * _Widget;
   CAppFrame * _AppFrame;
   CGroupSelectButton * _SelectButton;
   QPixmap _GroupIcon;
   QPtrVector<cPageDescription> _Pages;
   BOOL_T _Right;
private:
   void InsertPage(int pos, cPageDescription * page_desc);
   friend class cPageDescription;
};

/// these constants define the appearance of the navigation widget

#define STRICT_MATRIX_REPRESENTATION      0x00000001  // cells of the matrix are adjusted strictly
                                                      // this leads to identcal cell sizes and 
                                                      // therefore restricts place for page descriptions
#define FONT_CALCULATED_REPRESENTATION    0x00000002  // cell size is calculated by font and string size
                                                      // actually not supported !!!
#define SIZE_CALCULATED_REPRESENTATION    0x00000004  // cells are adjusted per group
                                                      // leaves more place in groups with
                                                      // few pages
#define PLACE_RIGHT_SIDE_GROUPS_RIGHT     0x00000008  // places right side group buttons on the right side

#define FONT_SIZE_CALCULATED              0x00000010  // font size calculated by max pages
#define GROUP_PIXMAP_GENERAL_PRESENTATION 0x00000020  // general pixmap group button presentation
#define GROUP_IMAGE_NOT_SCALED            0x00000040  // group button image not scaled


typedef std::map<int,cGroupDescription*> GROUP_DESC_MAP_T;

class cQtNavigationWidget : public QWidget
{
public:
   cQtNavigationWidget(CAppFrame * parent,
                       const char * name = NULL,
                       WFlags f = 0,
                       ULONG_T flags = 0,
                       QFont qfont = QFont("Arial", 11));
   virtual ~cQtNavigationWidget();
   cGroupDescription * GroupDescription(const QString group_name);
   void Show();
   QString SelectedPage(QPoint pos);
   void SetBorderWidth(int width);
   void SetBorderColor(QColor & color);
   void Init();
   virtual void setFont(const QFont &font);
protected:
   virtual void paintEvent( QPaintEvent * e );
   //shows the selected page
   virtual void mouseReleaseEvent ( QMouseEvent * e );
private:
   void Setup();
   void drawGrid(QPainter & painter);
   void InsertGroup(int pos, cGroupDescription * group_desc);
   void Calculate();
   int MaxPages();
   void setCalculatedFont(int maxPages);
private:
   CAppFrame * _AppFrame;
   PAGE_LIST_T _PageList;
   GROUP_DESC_MAP_T _LeftGroups;
   GROUP_DESC_MAP_T _RightGroups;
   QPtrVector<cGroupDescription> _Groups;
   int _GlobalPageWidth;
   int _GroupWidth;
   ULONG_T _NavigationFlags;
   int _BorderWidth;
   QColor _BorderColor;
   int _FontPointSize;
   int _FontPixelSize;
   int _FontPointSizeOffset;
   int _FontPixelSizeOffset;
   bool _FontSizeType;
   friend class cGroupDescription;
   friend class cPageDescription;
};

#endif 
