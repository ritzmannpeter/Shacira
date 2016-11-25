//---------------------------------------------------------------------------
#ifndef DrvInstFormImplH
#define DrvInstFormImplH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "cWinSystem.h"
//---------------------------------------------------------------------------
class TDrvInst : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox1;
        TPanel *Panel1;
   TMemo *Info;
        TButton *Test;
        TLabel *Label3;
        TEdit *AdrLow;
        TEdit *AdrLowV;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *AdrHigh;
        TEdit *Cmd;
        TEdit *Read;
        TEdit *Write;
        TEdit *Status;
        TEdit *AdrHighV;
        TEdit *CmdV;
        TEdit *ReadV;
        TEdit *WriteV;
        TEdit *StatusV;
   TPanel *Panel2;
   TLabel *Label1;
   TEdit *System;
   TEdit *MajorVersion;
   TEdit *MinorVersion;
   TEdit *VersionString;
   TEdit *PlatformId;
   TEdit *BuildNumber;
   TLabel *Label11;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label15;
   TEdit *SystemDirectory;
   TLabel *Label2;
   TGroupBox *Installation;
   TButton *Install;
   TLabel *Label14;
   TComboBox *PortBase;
   TTabSheet *TabSheet3;
   TPanel *Panel3;
   TEdit *Version;
   TEdit *CheckMode;
   TEdit *Retries;
   TEdit *Stability;
   TEdit *DelayTime;
   TEdit *SimulateHardware;
   TLabel *Label16;
   TLabel *Label22;
   TLabel *Label18;
   TLabel *Label19;
   TLabel *Label20;
   TLabel *Label21;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall TestClick(TObject *Sender);
   void __fastcall InstallClick(TObject *Sender);
private:	// Anwenderdeklarationen
   cWinSystem * _WinSystem;
   int _SystemType;
   unsigned long _AdrLowPort;
   unsigned long _AdrLowValue;
   unsigned long _AdrHighPort;
   unsigned long _AdrHighValue;
   unsigned long _CmdPort;
   unsigned long _CmdValue;
   unsigned long _ReadPort;
   unsigned long _ReadValue;
   unsigned long _WritePort;
   unsigned long _WriteValue;
   unsigned long _StatusPort;
   unsigned long _StatusValue;
   unsigned long _Version;
   unsigned long _CheckMode;
   unsigned long _Stability;
   unsigned long _Retries;
   unsigned long _DelayTime;
   unsigned long _SimulateHardware;
public:		// Anwenderdeklarationen
   __fastcall TDrvInst(TComponent* Owner);
   void __fastcall ReadPorts(HANDLE hnd);
   void __fastcall ReadPort(HANDLE hnd, const char * port_name, const char * port_value,
                            unsigned long * port, unsigned long * value);
   void __fastcall ShowPorts();
   void __fastcall ReadParams(HANDLE hnd);
   void __fastcall ReadParam(HANDLE hnd, const char * param_name, unsigned long * value);
   void __fastcall ShowParams();
   AnsiString __fastcall HexValue(long value);
   AnsiString __fastcall DecValue(long value);
   void __fastcall DriverInfo(bool installed);
   bool __fastcall FileCopy(const char * src, const char * dst);
};
//---------------------------------------------------------------------------
extern PACKAGE TDrvInst *DrvInst;
//---------------------------------------------------------------------------
#endif
