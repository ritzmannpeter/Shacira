
#ifndef CWIDGETMAP_H
#define CWIDGETMAP_H

#include <qwidget.h>
class CWidgetBase;

class CUserData : public QObjectUserData
{
public:
   CUserData(CWidgetBase * base_widget) {_BaseWidget = base_widget;};
   CWidgetBase * _BaseWidget;
};

#ifdef QT_NO_USERDATA

typedef std::map<QWidget*,CUserData*> WIDGET_MAP_T;
static WIDGET_MAP_T _WidgetMap;

class CWidgetMap
{
public:
   static inline void SetBaseWidget(QWidget * widget, CWidgetBase * base_widget)
   {
      CUserData * user_data = new CUserData(base_widget);
      _WidgetMap[widget] = user_data;
   };
   static inline CWidgetBase * BaseWidget(QWidget * widget)
   {
      WIDGET_MAP_T::const_iterator i = _WidgetMap.find(widget);
      if (i == _WidgetMap.end()) {
         return NULL;
      } else {
         CUserData * user_data = (*i).second;
         return user_data->_BaseWidget;
      }
   };
};

#else

#define BASE_ID      0

class CWidgetMap
{
public:
   static inline void SetBaseWidget(QWidget * widget, CWidgetBase * base_widget)
   {
      CUserData * user_data = new CUserData(base_widget);
      widget->setUserData(BASE_ID, user_data);
   };
   static inline CWidgetBase * BaseWidget(QWidget * widget)
   {
      CUserData * user_data = (CUserData*)widget->userData(BASE_ID);
      if (user_data == NULL) {
         return NULL;
      } else {
         return user_data->_BaseWidget;
      }
   };
};

#endif

#endif


