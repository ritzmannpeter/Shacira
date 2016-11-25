/****************************************************************************
** Form interface generated from reading ui file '.\DrvInstForm.ui'
**
** Created: Mo 10. Mrz 15:53:10 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef DRVINSTFORM_H
#define DRVINSTFORM_H

#include <qvariant.h>
#include <qmainwindow.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QComboBox;
class QFrame;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QTextEdit;
class QWidget;

class DrvInstForm : public QMainWindow
{ 
    Q_OBJECT

public:
    DrvInstForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~DrvInstForm();

    QTabWidget* TabWidget2;
    QWidget* tab;
    QGroupBox* GroupBox1;
    QTextEdit* Info;
    QFrame* Frame3;
    QLabel* TextLabel1_2;
    QLabel* TextLabel1_3_4;
    QLabel* TextLabel1_3;
    QLabel* TextLabel1_3_2;
    QPushButton* Test;
    QGroupBox* Installation;
    QLabel* TextLabel1_4;
    QPushButton* Install;
    QComboBox* PortBase;
    QLabel* TextLabel1_3_3;
    QLineEdit* AddrHigh;
    QLineEdit* AddrHighV;
    QLineEdit* Cmd;
    QLineEdit* CmdV;
    QLineEdit* Read;
    QLineEdit* ReadV;
    QLineEdit* Write;
    QLineEdit* WriteV;
    QLineEdit* Status;
    QLineEdit* StatusV;
    QLineEdit* AddrLow;
    QLineEdit* AddrLowV;
    QLabel* TextLabel1;
    QWidget* tab_2;
    QFrame* Frame4;
    QLabel* TextLabel2_2;
    QLabel* TextLabel2_3;
    QLabel* TextLabel2_3_2;
    QLabel* TextLabel2_3_3;
    QLabel* TextLabel2;
    QLineEdit* System;
    QLineEdit* MajorVersion;
    QLineEdit* MinorVersion;
    QLineEdit* BuildNumber;
    QLineEdit* VersionString;
    QLineEdit* PlatformId;
    QLabel* TextLabel2_3_4;
    QLabel* TextLabel2_3_4_2;
    QLineEdit* CurrentDirectory;
    QLineEdit* SystemDirectory;
    QWidget* tab_3;
    QFrame* Frame5;
    QLabel* TextLabel2_4;
    QLabel* TextLabel2_4_2;
    QLabel* TextLabel2_4_3;
    QLabel* TextLabel2_4_3_2;
    QLabel* TextLabel2_4_3_3;
    QLabel* TextLabel2_4_3_4;
    QLineEdit* Version;
    QLineEdit* CheckMode;
    QLineEdit* Retries;
    QLineEdit* Stability;
    QLineEdit* DelayTime;
    QLineEdit* SimulateHardware;


public slots:
    virtual void Test_clicked();
    virtual void Install_clicked();
    virtual void init();

protected:
    QGridLayout* DrvInstFormLayout;
    QGridLayout* tabLayout;
    QGridLayout* GroupBox1Layout;
    QGridLayout* Frame3Layout;
    QGridLayout* tabLayout_2;
    QGridLayout* tabLayout_3;
};

#endif // DRVINSTFORM_H
