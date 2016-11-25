/****************************************************************************
** Form implementation generated from reading ui file '.\DrvInstForm.ui'
**
** Created: Mo 10. Mrz 15:53:10 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "DrvInstForm.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>

#include "DrvInstForm.ui.h"
static const char* const image0_data[] = { 
"32 32 4 1",
"a c #000000",
"b c #0000ff",
". c #c6c3c6",
"# c #ff0000",
"................................",
"..............................#.",
"...aaaa...aa...................#",
"..aaaaaa..aa.####aa###aa###aa###",
".aa...aa.....#...aa...aa...aa..#",
".a....aa..aa..#...........#.#.#.",
"......aa..aa...#.........#..#...",
".....aa...aa....#.......#...#...",
"....aa....aa.....aa...aa...aa...",
"...aa.....aa.....aa...aa...aa...",
"..aa......aa.......#.#......#...",
".aa.......aa........#.......#...",
".aa.......aa.......#.#......#...",
".aaaaaaaaaaa.....aa...aa...aa...",
".aaaaaaaaaaa.....aa...aa...aa...",
"................#.......#...#...",
"...............#.........#..#...",
"..............#...........#.#...",
".............#.............##...",
"................................",
"................................",
"...bbbb......bbb...bb..bbbbbb...",
"...bbbbbb....bbb...bb..bb..bb...",
"...bb..bbb...bbb...bb..bb.......",
"...bb...bb...bb.b..bb..bb.......",
"...bb....b...bb.bb.bb..bb.......",
"...bb...bb...bb..b.bb..bb.......",
"...bb..bbb...bb...bbb..bb.......",
"...bbbbbb....bb...bbb..bb..bb...",
"...bbbb......bb...bbb..bbbbbb...",
"................................",
"................................"};


/* 
 *  Constructs a DrvInstForm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */
DrvInstForm::DrvInstForm( QWidget* parent,  const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    QPixmap image0( ( const char** ) image0_data );
    if ( !name )
	setName( "DrvInstForm" );
    resize( 380, 435 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 326, 435 ) );
    setMaximumSize( QSize( 600, 600 ) );
    QFont f( font() );
    f.setFamily( "Arial" );
    f.setPointSize( 10 );
    setFont( f ); 
    setCaption( trUtf8( "2i DNC EEPROM-Einschub Treiberinstallation" ) );
    setIcon( image0 );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
    DrvInstFormLayout = new QGridLayout( centralWidget(), 1, 1, 11, 6, "DrvInstFormLayout"); 

    TabWidget2 = new QTabWidget( centralWidget(), "TabWidget2" );
    TabWidget2->setMaximumSize( QSize( 600, 600 ) );
    TabWidget2->setBackgroundOrigin( QTabWidget::ParentOrigin );

    tab = new QWidget( TabWidget2, "tab" );
    tabLayout = new QGridLayout( tab, 1, 1, 11, 6, "tabLayout"); 

    GroupBox1 = new QGroupBox( tab, "GroupBox1" );
    GroupBox1->setTitle( trUtf8( "Informationen" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 6 );
    GroupBox1->layout()->setMargin( 11 );
    GroupBox1Layout = new QGridLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );

    Info = new QTextEdit( GroupBox1, "Info" );
    Info->setReadOnly( TRUE );

    GroupBox1Layout->addWidget( Info, 0, 0 );

    tabLayout->addWidget( GroupBox1, 1, 0 );

    Frame3 = new QFrame( tab, "Frame3" );
    Frame3->setFrameShape( QFrame::StyledPanel );
    Frame3->setFrameShadow( QFrame::Raised );
    Frame3Layout = new QGridLayout( Frame3, 1, 1, 11, 6, "Frame3Layout"); 

    TextLabel1_2 = new QLabel( Frame3, "TextLabel1_2" );
    TextLabel1_2->setText( trUtf8( "Adr. High" ) );

    Frame3Layout->addWidget( TextLabel1_2, 1, 0 );

    TextLabel1_3_4 = new QLabel( Frame3, "TextLabel1_3_4" );
    TextLabel1_3_4->setText( trUtf8( "Read" ) );

    Frame3Layout->addWidget( TextLabel1_3_4, 3, 0 );

    TextLabel1_3 = new QLabel( Frame3, "TextLabel1_3" );
    TextLabel1_3->setText( trUtf8( "Write" ) );

    Frame3Layout->addWidget( TextLabel1_3, 4, 0 );

    TextLabel1_3_2 = new QLabel( Frame3, "TextLabel1_3_2" );
    TextLabel1_3_2->setText( trUtf8( "Status" ) );

    Frame3Layout->addWidget( TextLabel1_3_2, 5, 0 );

    Test = new QPushButton( Frame3, "Test" );
    Test->setText( trUtf8( "Testen" ) );

    Frame3Layout->addWidget( Test, 5, 3 );

    Installation = new QGroupBox( Frame3, "Installation" );
    Installation->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Installation->sizePolicy().hasHeightForWidth() ) );
    Installation->setTitle( trUtf8( "Installation" ) );
    Installation->setAlignment( int( QGroupBox::AlignLeft ) );

    TextLabel1_4 = new QLabel( Installation, "TextLabel1_4" );
    TextLabel1_4->setGeometry( QRect( 10, 20, 67, 20 ) ); 
    TextLabel1_4->setText( trUtf8( "Basisadresse" ) );

    Install = new QPushButton( Installation, "Install" );
    Install->setGeometry( QRect( 10, 100, 80, 26 ) ); 
    Install->setText( trUtf8( "Installieren" ) );

    PortBase = new QComboBox( FALSE, Installation, "PortBase" );
    PortBase->setGeometry( QRect( 20, 50, 60, 22 ) ); 

    Frame3Layout->addMultiCellWidget( Installation, 0, 4, 3, 3 );

    TextLabel1_3_3 = new QLabel( Frame3, "TextLabel1_3_3" );
    TextLabel1_3_3->setText( trUtf8( "Cmd" ) );

    Frame3Layout->addWidget( TextLabel1_3_3, 2, 0 );

    AddrHigh = new QLineEdit( Frame3, "AddrHigh" );
    AddrHigh->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, AddrHigh->sizePolicy().hasHeightForWidth() ) );
    AddrHigh->setMinimumSize( QSize( 40, 20 ) );
    AddrHigh->setMaximumSize( QSize( 40, 20 ) );
    AddrHigh->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    AddrHigh->setFrameShape( QLineEdit::LineEditPanel );
    AddrHigh->setFrameShadow( QLineEdit::Sunken );
    AddrHigh->setReadOnly( TRUE );

    Frame3Layout->addWidget( AddrHigh, 1, 1 );

    AddrHighV = new QLineEdit( Frame3, "AddrHighV" );
    AddrHighV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, AddrHighV->sizePolicy().hasHeightForWidth() ) );
    AddrHighV->setMinimumSize( QSize( 40, 20 ) );
    AddrHighV->setMaximumSize( QSize( 40, 20 ) );
    AddrHighV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    AddrHighV->setFrameShape( QLineEdit::LineEditPanel );
    AddrHighV->setFrameShadow( QLineEdit::Sunken );
    AddrHighV->setReadOnly( TRUE );

    Frame3Layout->addWidget( AddrHighV, 1, 2 );

    Cmd = new QLineEdit( Frame3, "Cmd" );
    Cmd->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Cmd->sizePolicy().hasHeightForWidth() ) );
    Cmd->setMinimumSize( QSize( 40, 20 ) );
    Cmd->setMaximumSize( QSize( 40, 20 ) );
    Cmd->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Cmd->setFrameShape( QLineEdit::LineEditPanel );
    Cmd->setFrameShadow( QLineEdit::Sunken );
    Cmd->setReadOnly( TRUE );

    Frame3Layout->addWidget( Cmd, 2, 1 );

    CmdV = new QLineEdit( Frame3, "CmdV" );
    CmdV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, CmdV->sizePolicy().hasHeightForWidth() ) );
    CmdV->setMinimumSize( QSize( 40, 20 ) );
    CmdV->setMaximumSize( QSize( 40, 20 ) );
    CmdV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    CmdV->setFrameShape( QLineEdit::LineEditPanel );
    CmdV->setFrameShadow( QLineEdit::Sunken );
    CmdV->setReadOnly( TRUE );

    Frame3Layout->addWidget( CmdV, 2, 2 );

    Read = new QLineEdit( Frame3, "Read" );
    Read->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Read->sizePolicy().hasHeightForWidth() ) );
    Read->setMinimumSize( QSize( 40, 20 ) );
    Read->setMaximumSize( QSize( 40, 20 ) );
    Read->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Read->setFrameShape( QLineEdit::LineEditPanel );
    Read->setFrameShadow( QLineEdit::Sunken );
    Read->setReadOnly( TRUE );

    Frame3Layout->addWidget( Read, 3, 1 );

    ReadV = new QLineEdit( Frame3, "ReadV" );
    ReadV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, ReadV->sizePolicy().hasHeightForWidth() ) );
    ReadV->setMinimumSize( QSize( 40, 20 ) );
    ReadV->setMaximumSize( QSize( 40, 20 ) );
    ReadV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    ReadV->setFrameShape( QLineEdit::LineEditPanel );
    ReadV->setFrameShadow( QLineEdit::Sunken );
    ReadV->setReadOnly( TRUE );

    Frame3Layout->addWidget( ReadV, 3, 2 );

    Write = new QLineEdit( Frame3, "Write" );
    Write->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Write->sizePolicy().hasHeightForWidth() ) );
    Write->setMinimumSize( QSize( 40, 20 ) );
    Write->setMaximumSize( QSize( 40, 20 ) );
    Write->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Write->setFrameShape( QLineEdit::LineEditPanel );
    Write->setFrameShadow( QLineEdit::Sunken );
    Write->setReadOnly( TRUE );

    Frame3Layout->addWidget( Write, 4, 1 );

    WriteV = new QLineEdit( Frame3, "WriteV" );
    WriteV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, WriteV->sizePolicy().hasHeightForWidth() ) );
    WriteV->setMinimumSize( QSize( 40, 20 ) );
    WriteV->setMaximumSize( QSize( 40, 20 ) );
    WriteV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    WriteV->setFrameShape( QLineEdit::LineEditPanel );
    WriteV->setFrameShadow( QLineEdit::Sunken );
    WriteV->setReadOnly( TRUE );

    Frame3Layout->addWidget( WriteV, 4, 2 );

    Status = new QLineEdit( Frame3, "Status" );
    Status->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Status->sizePolicy().hasHeightForWidth() ) );
    Status->setMinimumSize( QSize( 40, 20 ) );
    Status->setMaximumSize( QSize( 40, 20 ) );
    Status->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Status->setFrameShape( QLineEdit::LineEditPanel );
    Status->setFrameShadow( QLineEdit::Sunken );
    Status->setReadOnly( TRUE );

    Frame3Layout->addWidget( Status, 5, 1 );

    StatusV = new QLineEdit( Frame3, "StatusV" );
    StatusV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, StatusV->sizePolicy().hasHeightForWidth() ) );
    StatusV->setMinimumSize( QSize( 40, 20 ) );
    StatusV->setMaximumSize( QSize( 40, 20 ) );
    StatusV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    StatusV->setFrameShape( QLineEdit::LineEditPanel );
    StatusV->setFrameShadow( QLineEdit::Sunken );
    StatusV->setReadOnly( TRUE );

    Frame3Layout->addWidget( StatusV, 5, 2 );

    AddrLow = new QLineEdit( Frame3, "AddrLow" );
    AddrLow->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, AddrLow->sizePolicy().hasHeightForWidth() ) );
    AddrLow->setMinimumSize( QSize( 40, 20 ) );
    AddrLow->setMaximumSize( QSize( 40, 20 ) );
    AddrLow->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    AddrLow->setFrameShape( QLineEdit::LineEditPanel );
    AddrLow->setFrameShadow( QLineEdit::Sunken );
    AddrLow->setReadOnly( TRUE );

    Frame3Layout->addWidget( AddrLow, 0, 1 );

    AddrLowV = new QLineEdit( Frame3, "AddrLowV" );
    AddrLowV->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, AddrLowV->sizePolicy().hasHeightForWidth() ) );
    AddrLowV->setMinimumSize( QSize( 40, 20 ) );
    AddrLowV->setMaximumSize( QSize( 40, 20 ) );
    AddrLowV->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    AddrLowV->setFrameShape( QLineEdit::LineEditPanel );
    AddrLowV->setFrameShadow( QLineEdit::Sunken );
    AddrLowV->setReadOnly( TRUE );

    Frame3Layout->addWidget( AddrLowV, 0, 2 );

    TextLabel1 = new QLabel( Frame3, "TextLabel1" );
    TextLabel1->setText( trUtf8( "Adr. Low" ) );

    Frame3Layout->addWidget( TextLabel1, 0, 0 );

    tabLayout->addWidget( Frame3, 0, 0 );
    TabWidget2->insertTab( tab, trUtf8( "Treiber" ) );

    tab_2 = new QWidget( TabWidget2, "tab_2" );
    tabLayout_2 = new QGridLayout( tab_2, 1, 1, 11, 6, "tabLayout_2"); 

    Frame4 = new QFrame( tab_2, "Frame4" );
    Frame4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, Frame4->sizePolicy().hasHeightForWidth() ) );
    Frame4->setFrameShape( QFrame::StyledPanel );
    Frame4->setFrameShadow( QFrame::Raised );

    TextLabel2_2 = new QLabel( Frame4, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 10, 30, 95, 20 ) ); 
    TextLabel2_2->setText( trUtf8( "Plattform" ) );

    TextLabel2_3 = new QLabel( Frame4, "TextLabel2_3" );
    TextLabel2_3->setGeometry( QRect( 10, 50, 95, 20 ) ); 
    TextLabel2_3->setText( trUtf8( "Hauptversion" ) );

    TextLabel2_3_2 = new QLabel( Frame4, "TextLabel2_3_2" );
    TextLabel2_3_2->setGeometry( QRect( 10, 70, 95, 20 ) ); 
    TextLabel2_3_2->setText( trUtf8( "Nebenversion" ) );

    TextLabel2_3_3 = new QLabel( Frame4, "TextLabel2_3_3" );
    TextLabel2_3_3->setGeometry( QRect( 10, 90, 95, 20 ) ); 
    TextLabel2_3_3->setText( trUtf8( "Build" ) );

    TextLabel2 = new QLabel( Frame4, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 10, 95, 20 ) ); 
    TextLabel2->setText( trUtf8( "Betriebssystem" ) );

    System = new QLineEdit( Frame4, "System" );
    System->setGeometry( QRect( 110, 10, 160, 20 ) ); 
    System->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, System->sizePolicy().hasHeightForWidth() ) );
    System->setMinimumSize( QSize( 160, 20 ) );
    System->setMaximumSize( QSize( 160, 20 ) );
    System->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    System->setFrameShape( QLineEdit::LineEditPanel );
    System->setFrameShadow( QLineEdit::Sunken );
    System->setReadOnly( TRUE );

    MajorVersion = new QLineEdit( Frame4, "MajorVersion" );
    MajorVersion->setGeometry( QRect( 110, 50, 160, 20 ) ); 
    MajorVersion->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, MajorVersion->sizePolicy().hasHeightForWidth() ) );
    MajorVersion->setMinimumSize( QSize( 160, 20 ) );
    MajorVersion->setMaximumSize( QSize( 160, 20 ) );
    MajorVersion->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    MajorVersion->setFrameShape( QLineEdit::LineEditPanel );
    MajorVersion->setFrameShadow( QLineEdit::Sunken );
    MajorVersion->setReadOnly( TRUE );

    MinorVersion = new QLineEdit( Frame4, "MinorVersion" );
    MinorVersion->setGeometry( QRect( 110, 70, 160, 20 ) ); 
    MinorVersion->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, MinorVersion->sizePolicy().hasHeightForWidth() ) );
    MinorVersion->setMinimumSize( QSize( 160, 20 ) );
    MinorVersion->setMaximumSize( QSize( 160, 20 ) );
    MinorVersion->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    MinorVersion->setFrameShape( QLineEdit::LineEditPanel );
    MinorVersion->setFrameShadow( QLineEdit::Sunken );
    MinorVersion->setReadOnly( TRUE );

    BuildNumber = new QLineEdit( Frame4, "BuildNumber" );
    BuildNumber->setGeometry( QRect( 110, 90, 160, 20 ) ); 
    BuildNumber->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, BuildNumber->sizePolicy().hasHeightForWidth() ) );
    BuildNumber->setMinimumSize( QSize( 160, 20 ) );
    BuildNumber->setMaximumSize( QSize( 160, 20 ) );
    BuildNumber->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    BuildNumber->setFrameShape( QLineEdit::LineEditPanel );
    BuildNumber->setFrameShadow( QLineEdit::Sunken );
    BuildNumber->setReadOnly( TRUE );

    VersionString = new QLineEdit( Frame4, "VersionString" );
    VersionString->setGeometry( QRect( 110, 110, 160, 20 ) ); 
    VersionString->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, VersionString->sizePolicy().hasHeightForWidth() ) );
    VersionString->setMinimumSize( QSize( 160, 20 ) );
    VersionString->setMaximumSize( QSize( 160, 20 ) );
    VersionString->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    VersionString->setFrameShape( QLineEdit::LineEditPanel );
    VersionString->setFrameShadow( QLineEdit::Sunken );
    VersionString->setReadOnly( TRUE );

    PlatformId = new QLineEdit( Frame4, "PlatformId" );
    PlatformId->setGeometry( QRect( 110, 30, 160, 20 ) ); 
    PlatformId->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, PlatformId->sizePolicy().hasHeightForWidth() ) );
    PlatformId->setMinimumSize( QSize( 160, 20 ) );
    PlatformId->setMaximumSize( QSize( 160, 20 ) );
    PlatformId->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    PlatformId->setFrameShape( QLineEdit::LineEditPanel );
    PlatformId->setFrameShadow( QLineEdit::Sunken );
    PlatformId->setReadOnly( TRUE );

    TextLabel2_3_4 = new QLabel( Frame4, "TextLabel2_3_4" );
    TextLabel2_3_4->setGeometry( QRect( 10, 130, 54, 20 ) ); 
    TextLabel2_3_4->setText( trUtf8( "Sysverz." ) );

    TextLabel2_3_4_2 = new QLabel( Frame4, "TextLabel2_3_4_2" );
    TextLabel2_3_4_2->setGeometry( QRect( 10, 150, 72, 20 ) ); 
    TextLabel2_3_4_2->setText( trUtf8( "Arbeitsverz." ) );

    CurrentDirectory = new QLineEdit( Frame4, "CurrentDirectory" );
    CurrentDirectory->setGeometry( QRect( 90, 150, 410, 20 ) ); 
    CurrentDirectory->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, CurrentDirectory->sizePolicy().hasHeightForWidth() ) );
    CurrentDirectory->setMinimumSize( QSize( 160, 20 ) );
    CurrentDirectory->setMaximumSize( QSize( 600, 20 ) );
    CurrentDirectory->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    CurrentDirectory->setFrameShape( QLineEdit::LineEditPanel );
    CurrentDirectory->setFrameShadow( QLineEdit::Sunken );
    CurrentDirectory->setReadOnly( TRUE );

    SystemDirectory = new QLineEdit( Frame4, "SystemDirectory" );
    SystemDirectory->setGeometry( QRect( 90, 130, 410, 20 ) ); 
    SystemDirectory->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, SystemDirectory->sizePolicy().hasHeightForWidth() ) );
    SystemDirectory->setMinimumSize( QSize( 160, 20 ) );
    SystemDirectory->setMaximumSize( QSize( 600, 20 ) );
    SystemDirectory->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    SystemDirectory->setFrameShape( QLineEdit::LineEditPanel );
    SystemDirectory->setFrameShadow( QLineEdit::Sunken );
    SystemDirectory->setReadOnly( TRUE );

    tabLayout_2->addWidget( Frame4, 0, 0 );
    TabWidget2->insertTab( tab_2, trUtf8( "System" ) );

    tab_3 = new QWidget( TabWidget2, "tab_3" );
    tabLayout_3 = new QGridLayout( tab_3, 1, 1, 11, 6, "tabLayout_3"); 

    Frame5 = new QFrame( tab_3, "Frame5" );
    Frame5->setFrameShape( QFrame::StyledPanel );
    Frame5->setFrameShadow( QFrame::Raised );

    TextLabel2_4 = new QLabel( Frame5, "TextLabel2_4" );
    TextLabel2_4->setGeometry( QRect( 20, 20, 120, 20 ) ); 
    TextLabel2_4->setText( trUtf8( "Hardware Version" ) );

    TextLabel2_4_2 = new QLabel( Frame5, "TextLabel2_4_2" );
    TextLabel2_4_2->setGeometry( QRect( 20, 40, 120, 20 ) ); 
    TextLabel2_4_2->setText( trUtf8( "Kapazitätsprüfung" ) );

    TextLabel2_4_3 = new QLabel( Frame5, "TextLabel2_4_3" );
    TextLabel2_4_3->setGeometry( QRect( 20, 60, 106, 20 ) ); 
    TextLabel2_4_3->setText( trUtf8( "Wiederholungen" ) );

    TextLabel2_4_3_2 = new QLabel( Frame5, "TextLabel2_4_3_2" );
    TextLabel2_4_3_2->setGeometry( QRect( 20, 80, 106, 20 ) ); 
    TextLabel2_4_3_2->setText( trUtf8( "Stabilität" ) );

    TextLabel2_4_3_3 = new QLabel( Frame5, "TextLabel2_4_3_3" );
    TextLabel2_4_3_3->setGeometry( QRect( 20, 100, 110, 20 ) ); 
    TextLabel2_4_3_3->setText( trUtf8( "Schreibverögerung" ) );

    TextLabel2_4_3_4 = new QLabel( Frame5, "TextLabel2_4_3_4" );
    TextLabel2_4_3_4->setGeometry( QRect( 20, 120, 106, 20 ) ); 
    TextLabel2_4_3_4->setText( trUtf8( "Simulation" ) );

    Version = new QLineEdit( Frame5, "Version" );
    Version->setGeometry( QRect( 140, 20, 40, 20 ) ); 
    Version->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Version->sizePolicy().hasHeightForWidth() ) );
    Version->setMinimumSize( QSize( 40, 20 ) );
    Version->setMaximumSize( QSize( 40, 20 ) );
    Version->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Version->setFrameShape( QLineEdit::LineEditPanel );
    Version->setFrameShadow( QLineEdit::Sunken );
    Version->setReadOnly( TRUE );

    CheckMode = new QLineEdit( Frame5, "CheckMode" );
    CheckMode->setGeometry( QRect( 140, 40, 40, 20 ) ); 
    CheckMode->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, CheckMode->sizePolicy().hasHeightForWidth() ) );
    CheckMode->setMinimumSize( QSize( 40, 20 ) );
    CheckMode->setMaximumSize( QSize( 40, 20 ) );
    CheckMode->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    CheckMode->setFrameShape( QLineEdit::LineEditPanel );
    CheckMode->setFrameShadow( QLineEdit::Sunken );
    CheckMode->setReadOnly( TRUE );

    Retries = new QLineEdit( Frame5, "Retries" );
    Retries->setGeometry( QRect( 140, 60, 40, 20 ) ); 
    Retries->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Retries->sizePolicy().hasHeightForWidth() ) );
    Retries->setMinimumSize( QSize( 40, 20 ) );
    Retries->setMaximumSize( QSize( 40, 20 ) );
    Retries->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Retries->setFrameShape( QLineEdit::LineEditPanel );
    Retries->setFrameShadow( QLineEdit::Sunken );
    Retries->setReadOnly( TRUE );

    Stability = new QLineEdit( Frame5, "Stability" );
    Stability->setGeometry( QRect( 140, 80, 40, 20 ) ); 
    Stability->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, Stability->sizePolicy().hasHeightForWidth() ) );
    Stability->setMinimumSize( QSize( 40, 20 ) );
    Stability->setMaximumSize( QSize( 40, 20 ) );
    Stability->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    Stability->setFrameShape( QLineEdit::LineEditPanel );
    Stability->setFrameShadow( QLineEdit::Sunken );
    Stability->setReadOnly( TRUE );

    DelayTime = new QLineEdit( Frame5, "DelayTime" );
    DelayTime->setGeometry( QRect( 140, 100, 40, 20 ) ); 
    DelayTime->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, DelayTime->sizePolicy().hasHeightForWidth() ) );
    DelayTime->setMinimumSize( QSize( 40, 20 ) );
    DelayTime->setMaximumSize( QSize( 40, 20 ) );
    DelayTime->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    DelayTime->setFrameShape( QLineEdit::LineEditPanel );
    DelayTime->setFrameShadow( QLineEdit::Sunken );
    DelayTime->setReadOnly( TRUE );

    SimulateHardware = new QLineEdit( Frame5, "SimulateHardware" );
    SimulateHardware->setGeometry( QRect( 140, 120, 40, 20 ) ); 
    SimulateHardware->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, SimulateHardware->sizePolicy().hasHeightForWidth() ) );
    SimulateHardware->setMinimumSize( QSize( 40, 20 ) );
    SimulateHardware->setMaximumSize( QSize( 40, 20 ) );
    SimulateHardware->setPaletteBackgroundColor( QColor( 192, 192, 192 ) );
    SimulateHardware->setFrameShape( QLineEdit::LineEditPanel );
    SimulateHardware->setFrameShadow( QLineEdit::Sunken );
    SimulateHardware->setReadOnly( TRUE );

    tabLayout_3->addWidget( Frame5, 0, 0 );
    TabWidget2->insertTab( tab_3, trUtf8( "Konfiguration" ) );

    DrvInstFormLayout->addWidget( TabWidget2, 0, 0 );

    // toolbars


    // signals and slots connections
    connect( Test, SIGNAL( clicked() ), this, SLOT( Test_clicked() ) );
    connect( Install, SIGNAL( clicked() ), this, SLOT( Install_clicked() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DrvInstForm::~DrvInstForm()
{
    // no need to delete child widgets, Qt does it all for us
}

