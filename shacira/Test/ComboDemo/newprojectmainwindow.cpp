/****************************************************************************
** Form implementation generated from reading ui file '.\newprojectmainwindow.ui'
**
** Created: Do 10. Mrz 20:42:43 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "newprojectmainwindow.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>

/*
 *  Constructs a NewProjectMainWindow as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
NewProjectMainWindow::NewProjectMainWindow( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "NewProjectMainWindow" );
    QFont f( font() );
    f.setPointSize( 10 );
    setFont( f ); 
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );

    comboBox1 = new QComboBox( FALSE, centralWidget(), "comboBox1" );
    comboBox1->setGeometry( QRect( 70, 299, 435, 21 ) );

    textLabel1 = new QLabel( centralWidget(), "textLabel1" );
    textLabel1->setGeometry( QRect( 60, 74, 446, 161 ) );
    textLabel1->setAlignment( int( QLabel::AlignTop | QLabel::AlignLeft ) );

    // toolbars

    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NewProjectMainWindow::~NewProjectMainWindow()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NewProjectMainWindow::languageChange()
{
    setCaption( tr( "NewProject" ) );
    comboBox1->clear();
    comboBox1->insertItem( tr( "item1" ) );
    comboBox1->insertItem( tr( "item2" ) );
    comboBox1->insertItem( tr( "item3" ) );
    comboBox1->insertItem( tr( "item4" ) );
    comboBox1->insertItem( tr( "item5" ) );
    textLabel1->setText( tr( "select an item\n"
"while you hear the beeps the combo box input is blocked\n"
"when you click on the combo box at least 2 times within the blocked period,\n"
"the combo box will block forever" ) );
}

