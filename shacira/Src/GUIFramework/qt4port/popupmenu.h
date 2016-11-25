
#ifndef _popupmenu_h_
#define _popupmenu_h_

#include <qwidget.h>
#include <qstring.h>
#include <qmenu.h>
#include <qpixmap.h>
#include <qicon.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qwidgetaction.h>
#include <qlayout.h>

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

class PopupMenu : public QMenu
{
public:
   PopupMenu(QWidget * parent = NULL);
   int insertItem(const QString & text, int id =-1, int index = -1);
   int insertItem(const QString & text, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1);
   int insertItem(const QPixmap & pixmap, const QString & text, int id = -1, int index = -1);
   int insertItem(const QPixmap & pixmap, const QString & text, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1);
   int insertItem(const QPixmap & pixmap, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1);
   int insertItem(QWidget * widget, int id = -1, int index = -1);
   bool connectItem(int id, const QObject * receiver, const char * member);
   int insertSeparator(int index = -1);
   void changeItem(int id, const QString & text);
   void changeItem(int id, const QPixmap & pixmap, const QString & text = QString());
   void changeItem(int id, const QIcon & icon, const QString & text = QString());
   void setItemEnabled(int id, bool state);
   void setItemVisible(int id, bool state);
   int exec(const QPoint & pos, int indexAtPoint = 0);
private:
   QMap<int,QAction*> _actionMap;
   int _currentId;
   int _currentIndex;
   QAction * action(int id);
   inline int itemId(int id)
   {
      if (id != -1) {
         return id;
      } else {
         return nextId();
      }
   };
   inline int nextId()
   {
      return _currentId++;
   };
};

namespace FileDialogs {
   QString getOpenFileName(const QString & startWith = QString::null, const QString & filter = QString::null, QWidget * parent = 0, const char * name = 0, const QString & caption = QString::null, QString * selectedFilter = 0, bool resolveSymlinks = true);
   QString getSaveFileName(const QString & startWith = QString::null, const QString & filter = QString::null, QWidget * parent = 0, const char * name = 0, const QString & caption = QString::null, QString * selectedFilter = 0, bool resolveSymlinks = true);
};

namespace InputDialogs {
   QString getText ( const QString & caption, const QString & label, QLineEdit::EchoMode mode = QLineEdit::Normal, const QString & text = QString::null, bool * ok = 0, QWidget * parent = 0, const char * name = 0);
};

#endif // _popupmenu_h_


