
#include "popupmenu.h"
#include <qtextedit.h>

PopupMenu::PopupMenu(QWidget * parent)
   : QMenu(parent), _currentId(0), _currentIndex(0)
{
}

int PopupMenu::insertItem(const QString & text, int id, int index)
{
   int newId = itemId(id);
   QAction * action = addAction(text);
   _actionMap[newId] = action;
   return newId;
}

int PopupMenu::insertItem(const QString & text, const QObject * receiver, const char * member, const QKeySequence & accel, int id, int index)
{
   int newId = itemId(id);
   QAction * action = addAction(text);
   _actionMap[newId] = action;
   connectItem(newId, receiver, member);
   return newId;
}

int PopupMenu::insertItem(const QPixmap & pixmap, const QString & text, int id, int index)
{
   int newId = itemId(id);
   QAction * action = addAction(pixmap, text);
   _actionMap[newId] = action;
   return newId;
}

int PopupMenu::insertItem(const QPixmap & pixmap, const QString & text, const QObject * receiver, const char * member, const QKeySequence & accel, int id, int index)
{
   int newId = itemId(id);
   QAction * action = addAction(pixmap, text);
   _actionMap[newId] = action;
   connectItem(newId, receiver, member);
   return newId;
}

int PopupMenu::insertItem(const QPixmap & pixmap, const QObject * receiver, const char * member, const QKeySequence & accel, int id, int index)
{
   int newId = itemId(id);
   QAction * action = addAction(pixmap, QString());
   _actionMap[newId] = action;
   connectItem(newId, receiver, member);
   return newId;
}

int PopupMenu::insertItem(QWidget * widget, int id, int index)
{
   widget->setParent(NULL);
   int newId = itemId(id);
   QWidget * widgetContainer = new QWidget(NULL);
   QHBoxLayout * layout = new QHBoxLayout();
   layout->addWidget(widget);
   widgetContainer->setLayout(layout);
   QWidgetAction * action = new QWidgetAction(NULL);
   action->setDefaultWidget(widgetContainer);
   addAction(action);
   _actionMap[newId] = action;
   return newId;
}

bool PopupMenu::connectItem(int id, const QObject * receiver, const char * member)
{
   QAction * action = this->action(id);
   return connect(action, SIGNAL(triggered()), receiver, member);
}

int PopupMenu::insertSeparator(int index)
{
   addSeparator();
QAction * action = this->action(index);
QMenu::insertSeparator(action);
return 0;
}

void PopupMenu::changeItem(int id, const QString & text)
{
   QAction * action = this->action(id);
   if (action != NULL) {
      action->setText(text);
   }
}

void PopupMenu::changeItem(int id, const QPixmap & pixmap, const QString & text)
{
   QAction * action = this->action(id);
   if (action != NULL) {
      action->setIcon(pixmap);
      action->setText(text);
   }
}

void PopupMenu::changeItem(int id, const QIcon & icon, const QString & text)
{
   QAction * action = this->action(id);
   if (action != NULL) {
      action->setIcon(icon);
      action->setText(text);
   }
}

void PopupMenu::setItemEnabled(int id, bool state)
{
   QAction * action = this->action(id);
   if (action != NULL) {
      action->setEnabled(state);
   }
}

void PopupMenu::setItemVisible(int id, bool state)
{
   QAction * action = this->action(id);
   if (action != NULL) {
      action->setVisible(state);
   }
}

int PopupMenu::exec(const QPoint & pos, int indexAtPoint)
{
   QMenu::exec(pos);
   return 0;
}

QAction * PopupMenu::action(int id)
{
   QAction * action = NULL;
   QMap<int,QAction*>::const_iterator i = _actionMap.find(id);
   if (i == _actionMap.end()) {
      int dummy = 0;
   } else {
      action = i.value();
   }
   return action;
}


#include <qfiledialog.h>

namespace FileDialogs {
   
QString getOpenFileName(const QString & startWith, const QString & filter, QWidget * parent, const char * name, const QString & caption, QString * selectedFilter, bool resolveSymlinks)
{
   QFileDialog::Options options = 0;
   return QFileDialog::getOpenFileName(parent, caption, startWith, filter, selectedFilter, options);
}

QString getSaveFileName(const QString & startWith, const QString & filter, QWidget * parent, const char * name, const QString & caption, QString * selectedFilter, bool resolveSymlinks)
{
   QFileDialog::Options options = 0;
   return QFileDialog::getSaveFileName(parent, caption, startWith, filter, selectedFilter, options);
};

};

#include <qinputdialog.h>

namespace InputDialogs {

QString getText(const QString & caption, const QString & label, QLineEdit::EchoMode mode, const QString & text, bool * ok, QWidget * parent, const char * name)
{
   Qt::InputMethodHints hints = Qt::ImhNone;
   Qt::WindowFlags flags = 0;
   QInputDialog dialog;
   return dialog.getText(parent, caption, label, mode, text, ok, flags, hints);
}

};

