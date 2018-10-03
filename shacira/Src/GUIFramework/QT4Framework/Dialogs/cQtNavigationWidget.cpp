
// ==========================================================================
// cQtNavigationWidget.cpp
// 08.06.05 -SW- implemented
// 26.06.05 -PR- added support for naming and icons
// ==========================================================================

#include "cQtNavigationWidget.h"
#include "CPage.h"
#include <qtabwidget.h>

#define X_OFFSET 5

cPageDescription::cPageDescription(cQtNavigationWidget * widget, CAppFrame * app_frame,
                                   CPage * page)
{
   _Widget = widget;
   _AppFrame = app_frame;
   _Page = page;
   _RelPos = -1;
}

cPageDescription::~cPageDescription()
{
}

void cPageDescription::SetVisibleRect(QRect & rectangle)
{
   _VisibleRect = rectangle;
}

QRect cPageDescription::VisibleRect()
{
   return _VisibleRect;
}

QString cPageDescription::PageName()
{
   return _Page->getPageName();
}

QString cPageDescription::GroupName()
{
   return _Page->getPageGroup();
}

QString cPageDescription::PageHeadline()
{
   return _Page->getPageHeadline();
}

QString cPageDescription::LongPageHeadline()
{
   return _Page->getLongPageHeadline();
}

BOOL_T cPageDescription::IsVisible()
{
   ULONG_T appearance_state = _Page->GetAppearanceState();
   if (appearance_state != elementInvisible) {
      return true;
   } else {
      return false;
   }
}

BOOL_T cPageDescription::IsSelected(QPoint pos)
{
   if (pos.x() > _VisibleRect.right()) {
      return false;
   }
   if (pos.x() < _VisibleRect.left()) {
      return false;
   }
   if (pos.y() > _VisibleRect.bottom()) {
      return false;
   }
   if (pos.y() < _VisibleRect.top()) {
      return false;
   }
   return true;
}

void cPageDescription::Draw(QPainter & painter)
{
#ifdef QT4
   // under Qt 4 bottom line and right line are clipped when using _VisibleRect as clipping rectangle
   QRect clip_rectangle = _VisibleRect;
   clip_rectangle.setWidth(clip_rectangle.width() + 1);
   clip_rectangle.setHeight(clip_rectangle.height() + 1);
   painter.setClipRect(clip_rectangle);
   painter.setClipping(TRUE);
#else
   painter.setClipRect(_VisibleRect);
   painter.setClipping(TRUE);
#endif
   QColor specific_color = _Page->getSpecificColor();
   QBrush brush(specific_color);
   painter.setBrush(brush);
   if (_Widget->_BorderWidth > 0) {
      QPen pen(_Widget->_BorderColor, _Widget->_BorderWidth);
      painter.setPen(pen);
      painter.drawRect(_VisibleRect);
   } else {
      QPen pen(specific_color, _Widget->_BorderWidth);
      painter.setPen(pen);
      painter.drawRect(_VisibleRect);
   }
   QFontMetrics m(_Widget->font());
   int char_height = m.height();
   int y_pos = 15;
   int y_dist = 5;
   painter.setPen(Qt::black);
   if (_Widget->_NavigationFlags & SIZE_CALCULATED_REPRESENTATION) {
      char text[100] = {0};
      SafePrintf(text, sizeof(text), "%d", _RelPos);
      painter.drawText(_VisibleRect.x() + X_OFFSET,
                       _VisibleRect.y() + y_pos, text);
   }
   y_pos += y_dist + char_height;
   QString specific_name = _Page->getSpecificName();
   if (!specific_name.isNull() &&
       !specific_name.isEmpty()) {
      painter.drawText(_VisibleRect.x() + 10,
                       _VisibleRect.y(),// + y_pos,
                       _VisibleRect.width() - X_OFFSET*2,
                       _VisibleRect.height(),
#ifdef QT4
                       Qt::AlignCenter | Qt::TextWordWrap, specific_name);
#else
                       Qt::AlignCenter | Qt::WordBreak, specific_name);
#endif
   }
   else {
      QString PageText = PageHeadline();
#ifdef QT4
      if ((m.width(PageText) > (_VisibleRect.width() - X_OFFSET*2)) &&
          (PageText.indexOf(" ") == -1)) {
#else
      if ((m.width(PageText) > (_VisibleRect.width() - X_OFFSET*2)) &&
          (PageText.find(" ") == -1)) {
#endif
         painter.drawText(_VisibleRect.x() + X_OFFSET,
                          _VisibleRect.y(),// + y_pos,
                          _VisibleRect.width() - X_OFFSET*2,
                          _VisibleRect.height(),
                          Qt::AlignVCenter, PageText);
      }
      else {
         painter.drawText(_VisibleRect.x() + X_OFFSET,
                          _VisibleRect.y(),// + y_pos,
                          _VisibleRect.width() - X_OFFSET*2,
                          _VisibleRect.height(),
#ifdef QT4
                          Qt::AlignCenter | Qt::TextWordWrap, PageText);
#else
                          Qt::AlignCenter | Qt::WordBreak, PageText);
#endif
      }
   }
   painter.setClipping(false);
}

int cPageDescription::AbsPos()
{
   return _Page->GetAbsPos();
}

void cPageDescription::SetRelPos(int pos)
{
   _RelPos = pos;
}

int cPageDescription::GetRelPos()
{
   return _RelPos;
}

cGroupDescription::cGroupDescription(cQtNavigationWidget * widget, CAppFrame * app_frame, CGroupSelectButton * select_button)
{
   _Widget = widget;
   _AppFrame = app_frame;
   _SelectButton = select_button;
   if (widget->_NavigationFlags & GROUP_PIXMAP_GENERAL_PRESENTATION) {
      _GroupIcon = _SelectButton->getGeneralPixmap();
   }
   else {
      _GroupIcon = _SelectButton->getInactivePixmap();
   }
   _Right = false;
}

cGroupDescription::~cGroupDescription()
{
   int size = _Pages.size();
   for (int i=0; i<size; i++) {
      cPageDescription * page_desc = _Pages.at(i);
      if (page_desc != NULL) {
         delete page_desc;
      }
   }
}

void cGroupDescription::SetVisibleRect(QRect & rectangle, int group_index)
{
   int offset = group_index * 10;
   int size = _Pages.size();
   int pages = Pages();
   if(pages == 0)
   {
      _VisibleRect = rectangle;
      return;
   }
   int group_y_pos = rectangle.y();
   int group_height = rectangle.height();
   int group_width = rectangle.width();
   int width = _AppFrame->width() - group_width;
   int page_width = width / pages;
   if (_Widget->_NavigationFlags & SIZE_CALCULATED_REPRESENTATION) {
      page_width = width / pages;
   } else {
      page_width = _Widget->_GlobalPageWidth;
   }
   int start = 0;
   if (!_Right) {
      start = group_width;
   }
   for (int i=0; i<size; i++) {
      cPageDescription * page_desc = _Pages.at(i);
      if (page_desc != NULL) {
         if (_Widget->_NavigationFlags & FONT_CALCULATED_REPRESENTATION) {
            QString text = page_desc->PageHeadline();
            page_width = width / pages;
         }
         QRect page_rect;
         page_rect.setX(start);
         page_rect.setY(group_y_pos);
         page_rect.setWidth(page_width);
         page_rect.setHeight(group_height);
         page_desc->SetVisibleRect(page_rect);
         page_desc->SetRelPos(page_desc->GetRelPos() + offset);
         start += page_width;
      }
   }
   _VisibleRect = rectangle;
}

QString cGroupDescription::GroupName()
{
   return _SelectButton->getPageGroup();
}

QString cGroupDescription::GroupText()
{
   return _SelectButton->getPageGroup();
}

QPixmap cGroupDescription::GroupIcon()
{
   return _GroupIcon;
}

QRect cGroupDescription::VisibleRect()
{
   return _VisibleRect;
}

void cGroupDescription::SetPageDescription(cPageDescription * page_desc, int pos)
{
   InsertPage(pos, page_desc);
}

QString cGroupDescription::SelectedPage(QPoint pos)
{
   int size = _Pages.size();
   for (int i=0; i<size; i++) {
      cPageDescription * page_desc = _Pages.at(i);
      if (page_desc != NULL) {
         if (page_desc->IsSelected(pos)) {
            return page_desc->PageName();
         }
      }
   }
   return "";
}

int cGroupDescription::Pages()
{
   int pages = 0;
   int size = _Pages.size();
   for (int i=0; i<size; i++) {
      cPageDescription * page_desc = _Pages.at(i);
      if (page_desc != NULL) {
         pages++;
      }
   }
   return pages;
}

void cGroupDescription::Draw(QPainter & painter)
{
   painter.setClipRect(_VisibleRect);
   painter.setClipping(TRUE);
   if (_Widget->_BorderWidth > 0) {
      if (_GroupIcon.isNull()) {
         QPen pen(_Widget->_BorderColor, _Widget->_BorderWidth);
         painter.setPen(pen);
         painter.drawRect(_VisibleRect);
      } else {
#ifdef QT4
         QImage image = _GroupIcon.toImage();
#else
         QImage image = _GroupIcon.convertToImage();
#endif
         if ((_Widget->_NavigationFlags & GROUP_IMAGE_NOT_SCALED) == 0) {
#ifdef QT4
            image = image.scaled(_VisibleRect.width(), _VisibleRect.height());
#else
            image = image.scale(_VisibleRect.width(), _VisibleRect.height());
#endif
         }
         painter.drawImage(_VisibleRect.left(), _VisibleRect.top(), image);
      }
   }
   int size = _Pages.size();
   for (int i=0; i<size; i++) {
      cPageDescription * page_desc = _Pages.at(i);
      if (page_desc != NULL) {
         page_desc->Draw(painter);
      }
   }
   painter.setClipping(FALSE);
}

void cGroupDescription::InsertPage(int pos, cPageDescription * page_desc)
{
   int size = _Pages.size();
   if (pos >= size) {
      _Pages.resize(pos+1);
   }
#ifdef QT4
   _Pages[pos] = page_desc;
#else
   _Pages.insert(pos, page_desc);
#endif
}

void cGroupDescription::SetRight(BOOL_T state)
{
   if (_Widget->_NavigationFlags & PLACE_RIGHT_SIDE_GROUPS_RIGHT) {
      _Right = state;
   }
}

BOOL_T cGroupDescription::GetRight()
{
   return _Right;
}

BOOL_T cGroupDescription::IsVisible()
{
   ULONG_T appearance_state = _SelectButton->GetAppearanceState();
   if (appearance_state != elementInvisible) {
      return true;
   } else {
      return false;
   }
}


cQtNavigationWidget::cQtNavigationWidget(CAppFrame * parent,  
                                         const char * name,
                                         WIDGET_FLAGS_TYPE f,
                                         ULONG_T flags,
                                         QFont qfont)
#ifdef QT4
   : QWidget(parent, f),
#else
   : QWidget(parent, name, f),
#endif
     _FontPointSizeOffset(0),
     _FontPixelSizeOffset(0)
{
#ifdef QT4
   setObjectName(name);
   setAutoFillBackground(true);
#endif
   _FontPointSize = qfont.pointSize() + _FontPointSizeOffset;
   _FontPixelSize = qfont.pixelSize() + _FontPixelSizeOffset;
   _FontSizeType = (_FontPixelSize == -1) ? FONT_POINT_SIZE : FONT_PIXEL_SIZE;
   
   QWidget::setFont(qfont);
   _BorderWidth = 0;
   _BorderColor = Qt::white;
   _AppFrame = (CAppFrame*)parent;
   _GlobalPageWidth = 0;
   _GroupWidth = 50;
   _NavigationFlags = flags;
   Setup();
   resize(parent->getPageAreaSize());
}

cQtNavigationWidget::~cQtNavigationWidget()
{
}

cGroupDescription * cQtNavigationWidget::GroupDescription(const QString group_name)
{
   int size = _Groups.size();
   for (int i=0; i<size; i++) {
      cGroupDescription * group_desc = _Groups.at(i);
      if (group_desc != NULL) {
         if (group_desc->GroupName() == group_name) {
            return group_desc;
         }
      } else {
         break;
      }
   }
   return NULL;
}

void cQtNavigationWidget::Show()
{
   // Refresh data and check appearance to actualize all pages
   _AppFrame->Refresh(FAST_REFRESH, false, true);

   show();
}

void cQtNavigationWidget::SetBorderWidth(int width)
{
   _BorderWidth = width;
}

void cQtNavigationWidget::SetBorderColor(QColor & color)
{
   _BorderColor = color;
}

QString cQtNavigationWidget::SelectedPage(QPoint pos)
{
   int size = _Groups.size();
   for (int i=0; i<size; i++) {
      cGroupDescription * group_desc = _Groups.at(i);
      if (group_desc != NULL) {
         QString page_name = group_desc->SelectedPage(pos);
         if (page_name != "") {
            return page_name;
         }
      }
   }
   return "";
}

void cQtNavigationWidget::paintEvent(QPaintEvent * e)
{
   QPainter painter;                       
   painter.begin(this);                 
   drawGrid(painter);
   painter.end();       
}

void  cQtNavigationWidget::drawGrid(QPainter & painter)
{
   int size = _Groups.size();
   for (int i=0; i<size; i++) {
      cGroupDescription * group_desc = _Groups.at(i);
      if (group_desc != NULL) {
         group_desc->Draw(painter);
      }
   }
}

void cQtNavigationWidget::mouseReleaseEvent(QMouseEvent * e)
{ 
   QString page = SelectedPage(e->pos());
   if (page != "") {
      _AppFrame->ShowPage(page);
      hide();
      int size = _Groups.size();
      if (size) {
         for (int i=0; i<size; i++) {
            cGroupDescription * group_desc = _Groups.at(i);
            if (group_desc != NULL) {
               delete group_desc;
            }
         }

         _LeftGroups.clear();
         _RightGroups.clear();
         _Groups.clear();
      }
   }
}

void cQtNavigationWidget::InsertGroup(int pos, cGroupDescription * group_desc)
{
   if (pos == -1) {
      pos = _Groups.size();
   }
   int size = _Groups.size();
   if (pos >= size) {
      _Groups.resize(pos+1);
   }
   _Groups.insert(pos, group_desc);
}

void cQtNavigationWidget::Setup()
{
   // Refresh data and check appearance to actualize all pages
   _AppFrame->Refresh(FAST_REFRESH, false, true);

   int size = _Groups.size();
   if (size) {
      for (int i=0; i<size; i++) {
         cGroupDescription * group_desc = _Groups.at(i);
         if (group_desc != NULL) {
            delete group_desc;
         }
      }

      _LeftGroups.clear();
      _RightGroups.clear();
      _Groups.clear();
   }

   SELECT_BUTTON_MAP_T select_buttons;
   _AppFrame->GetSelectButtons(select_buttons);
   SELECT_BUTTON_MAP_T::const_iterator b = select_buttons.cbegin();
   while (b != select_buttons.cend()) {
      CGroupSelectButton * select_button = (*b).second;
      QPoint pos = select_button->mapToGlobal(select_button->pos());
      int xpos = pos.x();
      int ypos = pos.y();
      cGroupDescription * group_desc = new cGroupDescription(this, _AppFrame, select_button);

      if (xpos < _AppFrame->mapToGlobal(_AppFrame->pos()).x() + 500) {
         _LeftGroups[ypos] = group_desc;
      } else {
         group_desc->SetRight(true);
         _RightGroups[ypos] =  group_desc;
      }
      b++;
   }
   int index = 0;
   GROUP_DESC_MAP_T::const_iterator lg =_LeftGroups.cbegin();
   while (lg != _LeftGroups.cend()) {
      cGroupDescription * group_desc = (*lg).second;
      if (group_desc->IsVisible()) {
         InsertGroup(index, group_desc);
         index++;
      }
      lg++;
   }
   GROUP_DESC_MAP_T::const_iterator rg =_RightGroups.cbegin();
   while (rg != _RightGroups.cend()) {
      cGroupDescription * group_desc = (*rg).second;
      if (group_desc->IsVisible()) {
         InsertGroup(index, group_desc);
         index++;
      }
      rg++;
   }
   
   PAGE_LIST_T page_list;
   _AppFrame->GetPages(page_list, 0);
   PAGE_LIST_T::const_iterator i = page_list.cbegin();
   while (i != page_list.cend()) {
      CPage * page = (*i);
      if (page != NULL) {
         cPageDescription * page_desc = new cPageDescription(this, _AppFrame, page);
         if (page_desc->IsVisible()) {
            int pos = page_desc->AbsPos();
            page_desc->SetRelPos(pos);
            QString group_name = page_desc->GroupName();
            cGroupDescription * group_desc = GroupDescription(group_name);
            if (group_desc != NULL) {
               group_desc->SetPageDescription(page_desc, pos);
            } else {
               delete page_desc;
            }
         } else {
            delete page_desc;
         }
      }
      i++;
   }
   Calculate();
}

void cQtNavigationWidget::Calculate()
{
   int maxPages = MaxPages();
   if (_NavigationFlags & FONT_SIZE_CALCULATED) {
      setCalculatedFont(maxPages);
   }
   int size = _Groups.size();
   int height = _AppFrame->getPageAreaSize().height();
   int group_height = height / size;
   int group_width = group_height;
   int start = 0;
   _GroupWidth = group_height;
   if (maxPages > 0) {
      _GlobalPageWidth = (_AppFrame->getPageAreaSize().width() - _GroupWidth) / maxPages;
   } else {
      // potential division by zero
      _GlobalPageWidth = 40;
   }
   for (int i=0; i<size; i++) {
      cGroupDescription * group_desc = _Groups.at(i);
      if (group_desc != NULL) {
         QRect group_rect;
         if (group_desc->GetRight()) {
            group_rect.setX(_AppFrame->getPageAreaSize().width() - group_width);
            group_rect.setY(start);
            group_rect.setWidth(group_width);
            group_rect.setHeight(group_height);
            group_desc->SetVisibleRect(group_rect, i);
         } else {
            group_rect.setX(0);
            group_rect.setY(start);
            group_rect.setWidth(group_width);
            group_rect.setHeight(group_height);
            group_desc->SetVisibleRect(group_rect, i);
         }
         start += group_height;
      }
   }
}

int cQtNavigationWidget::MaxPages()
{
   int max = 0;
   int size = _Groups.size();
   for (int i=0; i<size; i++) {
      cGroupDescription * group_desc = _Groups.at(i);
      if (group_desc != NULL) {
         int pages = group_desc->Pages();
         if (pages > max) {
            max = pages;
         }
      }
   }
   return max;
}

void cQtNavigationWidget::Init()
{
   Setup();
}

void cQtNavigationWidget::setFont(const QFont &font)
{
   _FontPointSize = font.pointSize();
   _FontPixelSize = font.pixelSize();
   _FontSizeType = (_FontPixelSize == -1) ? FONT_POINT_SIZE : FONT_PIXEL_SIZE;

   QWidget::setFont(font);
}

void cQtNavigationWidget::setCalculatedFont(int maxPages)
{
   if (maxPages < 5) {
      _FontPointSizeOffset = 1; //2;
      _FontPixelSizeOffset = 1; //3;
   }
   else if (maxPages == 5) {
      _FontPointSizeOffset = 0; //1;
      _FontPixelSizeOffset = 0; //1;
   }
   else if (maxPages == 6) {
      _FontPointSizeOffset = -1; //0;
      _FontPixelSizeOffset = -1; //0;
   }
   else if (maxPages == 7) {
      _FontPointSizeOffset = -2; //-1;
      _FontPixelSizeOffset = -2; //-1;
   }
   else if (maxPages > 7) {
      _FontPointSizeOffset = -3; //-2;
      _FontPixelSizeOffset = -3; //-3;
   }

   QFont qfont = font();
   if (_FontSizeType == FONT_POINT_SIZE) {
      qfont.setPointSize(_FontPointSize + _FontPointSizeOffset);
   }
   else {
      qfont.setPixelSize(_FontPixelSize + _FontPixelSizeOffset);
   }

   if (!qfont.exactMatch()) {
      InfoPrintf("Font does not match exactly !\n");
   }

   QWidget::setFont(qfont);
}
