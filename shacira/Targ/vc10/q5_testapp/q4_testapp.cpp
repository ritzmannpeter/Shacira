
#include "q4_testapp.h"
#include "widget.h"

q4_testapp::q4_testapp(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui.setupUi(this);
   QVBoxLayout * l = new QVBoxLayout(ui.frame);
//   Widget * w = new Widget(NULL);
//   l->addWidget(w);
   _listView = new ListView(NULL);
   _listView->setSortingEnabled(true);
   l->addWidget(_listView);
}

q4_testapp::~q4_testapp()
{
}

void q4_testapp::timerExpired()
{
   int row = rand() % 100;
   int column = rand() % 5;
   int red = rand() % 255;
   int blue = rand() % 255;
   int green = rand() % 255;
   QColor fgColor = QColor(red, blue, green);
   QColor bgColor = QColor(blue, green, red);
//   listView()->setColor(row, column, ListView::WindowText, fgColor);
//   listView()->setColor(row, column, ListView::Window, bgColor);
}
