/****************************************************************************
** Form interface generated from reading ui file '.\newprojectmainwindow.ui'
**
** Created: Do 10. Mrz 20:42:43 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NEWPROJECTMAINWINDOW_H
#define NEWPROJECTMAINWINDOW_H

#include <qvariant.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QComboBox;
class QLabel;

class NewProjectMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NewProjectMainWindow( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~NewProjectMainWindow();

    QComboBox* comboBox1;
    QLabel* textLabel1;

protected:

protected slots:
    virtual void languageChange();

};

#endif // NEWPROJECTMAINWINDOW_H
