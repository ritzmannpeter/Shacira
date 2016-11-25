//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DrvInstFormImpl.h"
#include "CarItf.h"
#include "cWinRegistry.h"
#include <stdio.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDrvInst *DrvInst;
//---------------------------------------------------------------------------
__fastcall TDrvInst::TDrvInst(TComponent* Owner)
        : TForm(Owner), _WinSystem(NULL), _SystemType(UNDEFINED_SYSTEM)
{

   _WinSystem = new cWinSystem;
   _SystemType = _WinSystem->SystemType();
   switch (_SystemType) {
   case WIN_95: System->Text = "Windows 95"; break;
   case WIN_98: System->Text = "Windows 98"; break;
   case WIN_ME: System->Text = "Windows ME"; break;
   case WIN_NT: System->Text = "Windows NT"; break;
   case WIN_2K: System->Text = "Windows 2000"; break;
   case WIN_XP: System->Text = "Windows XP"; break;
   default: System->Text = "Nicht definiert"; break;
   }
   MajorVersion->Text = _WinSystem->VersionInfo()->dwMajorVersion;
   MinorVersion->Text = _WinSystem->VersionInfo()->dwMinorVersion;
   PlatformId->Text = _WinSystem->VersionInfo()->dwPlatformId;
   BuildNumber->Text = _WinSystem->VersionInfo()->dwBuildNumber;
   VersionString->Text = _WinSystem->VersionInfo()->szCSDVersion;
   SystemDirectory->Text = _WinSystem->SystemDirectory();
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::FormCreate(TObject *Sender)
{
   LPTSTR command_line = GetCommandLine();
   char program[1024] = {0};
   char param[64] = {0};
   int params = sscanf(command_line, "%s %s", &program, &param);
   if (params == 2) {
      if (stricmp(param, "-t") == 0) {
         HANDLE hnd = CARITF_Open();
         if (hnd != INVALID_HANDLE_VALUE) {
            CARITF_Close(hnd);
            _exit(0);
         }
      }
   }
   HANDLE hnd = CARITF_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
      ReadPorts(hnd);
      ShowPorts();
      ReadParams(hnd);
      ShowParams();
      CARITF_Close(hnd);
      DriverInfo(true);
   } else {
      DriverInfo(false);
   }
   PortBase->ItemIndex = 3;
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ReadPorts(HANDLE hnd)
{
   ReadPort(hnd, "ADDR_LOW_PORT", "VALUE_LOW_PORT", &_AdrLowPort, &_AdrLowValue);
   ReadPort(hnd, "ADDR_HIGH_PORT", "VALUE_HIGH_PORT", &_AdrHighPort, &_AdrHighValue);
   ReadPort(hnd, "CMD_PORT", "VALUE_CMD_PORT", &_CmdPort, &_CmdValue);
   ReadPort(hnd, "READ_PORT", "VALUE_READ_PORT", &_ReadPort, &_ReadValue);
   ReadPort(hnd, "WRITE_PORT", "VALUE_WRITE_PORT", &_WritePort, &_WriteValue);
   ReadPort(hnd, "STATUS_PORT", "VALUE_STATUS_PORT", &_StatusPort, &_StatusValue);
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ReadPort(HANDLE hnd, const char * port_name, const char * port_value,
                                   unsigned long * port, unsigned long * value)
{
   *port = 0;
   *value = 0;
   long rc = CARITF_GetParam(hnd, port_name, (long*)port);
   if (rc >= 0) {
      rc = CARITF_GetParam(hnd, port_value, (long*)value);
   }
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ShowPorts()
{
   AdrLow->Text = HexValue(_AdrLowPort);
   AdrLowV->Text = HexValue(_AdrLowValue);
   AdrHigh->Text = HexValue(_AdrHighPort);
   AdrHighV->Text = HexValue(_AdrHighValue);
   Cmd->Text = HexValue(_CmdPort);
   CmdV->Text = HexValue(_CmdValue);
   Read->Text = HexValue(_ReadPort);
   ReadV->Text = HexValue(_ReadValue);
   Write->Text = HexValue(_WritePort);
   WriteV->Text = HexValue(_WriteValue);
   Status->Text = HexValue(_StatusPort);
   StatusV->Text = HexValue(_StatusValue);
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ReadParams(HANDLE hnd)
{
   ReadParam(hnd, "VERSION", &_Version);
   ReadParam(hnd, "CHECK_MODE", &_CheckMode);
   ReadParam(hnd, "STABILITY", &_Stability);
   ReadParam(hnd, "RETRIES", &_Retries);
   ReadParam(hnd, "DELAY_TIME", &_DelayTime);
   ReadParam(hnd, "SIMULATE_HARDWARE", &_SimulateHardware);
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ReadParam(HANDLE hnd, const char * param_name, unsigned long * value)
{
   *value = 0;
   long rc = CARITF_GetParam(hnd, param_name, (long*)value);
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::ShowParams()
{
   Version->Text = DecValue(_Version);
   CheckMode->Text = DecValue(_CheckMode);
   Stability->Text = DecValue(_Stability);
   Retries->Text = DecValue(_Retries);
   DelayTime->Text = DecValue(_DelayTime);
   SimulateHardware->Text = DecValue(_SimulateHardware);
}

//---------------------------------------------------------------------------

AnsiString __fastcall TDrvInst::HexValue(long value)
{
   char buf[64] = {0};
   sprintf(buf, "%X", value);
   return AnsiString(buf);
}

//---------------------------------------------------------------------------

AnsiString __fastcall TDrvInst::DecValue(long value)
{
   char buf[64] = {0};
   sprintf(buf, "%d", value);
   return AnsiString(buf);
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::DriverInfo(bool installed)
{
   AnsiString message;
   if (installed) {
      message = "Der Treiber zum Zugriff auf EEPROMS ist installiert.";
      Test->Enabled = true;
   } else {
      message = "Der Treiber zum Zugriff auf EEPROMS ist nicht installiert oder nicht aktiviert.";
      if (_SystemType == WIN_NT) {
         message += "Durch betätigen der Schaltfläche 'Installieren' können Sie den Treiber installieren.";
         Installation->Visible = true;
      } else if (_SystemType == WIN_2K || _SystemType == WIN_XP) {
         message += "Sie können den Treiber mit der Hardware-Unterstützung von Windows installieren.";
         message += "Die benötigten Dateien finden Sie im DNC-Unterverzeichnis Driver\Win2000.";
      }
   }
   Info->Text = message;
}

//---------------------------------------------------------------------------

bool __fastcall TDrvInst::FileCopy(const char * src, const char * dst)
{
   STARTUPINFO suinfo = {0};
   PROCESS_INFORMATION pinfo = {0};
   const char * name = "c:\\winnt\\system32\\xcopy.exe";
   char command[512] = {0};
   sprintf(command, "%s %s %s /v", name, src, dst);
   suinfo.cb = sizeof(suinfo);
   int err = 0;
   long pid = 0;
   HANDLE hnd = 0;
   bool success = (bool)CreateProcess(name, command,
                                      NULL, NULL, false,
                                      CREATE_NO_WINDOW, NULL, NULL,
                                      &suinfo, &pinfo);
   if (success) {
      pid = pinfo.dwProcessId;
      hnd = pinfo.hProcess;
      DWORD exit_code = STILL_ACTIVE;
      while (exit_code == STILL_ACTIVE) {
         GetExitCodeProcess(hnd, &exit_code);
         Sleep(500);
      }
      if (exit_code == 0) {
         return true;
      } else {
         return false;
      }
   } else {
      err = GetLastError();
      return false;
   }
   return false;
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::TestClick(TObject *Sender)
{
   Info->Text = "";
   HANDLE hnd = CARITF_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
      ReadPorts(hnd);
      ShowPorts();
      long value = 1 << 7;
      if (_StatusValue & value) {
         Info->Text = "Zugriff auf EEPROM-Hardware nicht möglich. \
Möglicherweise ist auf diesem Rechner keine Hardware installiert \
oder die Basis I/O-Adresse ist falsch gewählt.";
      } else {
         Info->Text = "Zugriff auf EEPROM-Hardware möglich.";
      }
      CARITF_Close(hnd);
   } else {
      Info->Text = "Auf den Treiber kann nicht zugegriffen werden.";
   }
}

//---------------------------------------------------------------------------

void __fastcall TDrvInst::InstallClick(TObject *Sender)
{
   AnsiString message;
   const char * src = "Driver\\WinNT\\carrier.sys";
   char dest_dir[512] = {0};
   sprintf(dest_dir, "%s\\%s", _WinSystem->SystemDirectory(), "drivers");
   if (FileCopy(src, dest_dir)) {
      cWinRegistry registry;
      HKEY system = NULL;
      HKEY current_cs = NULL;
      HKEY services = NULL;
      HKEY carrier = NULL;
      system = registry.OpenKey(HKEY_LOCAL_MACHINE, "System");
      if (system != NULL) {
         current_cs = registry.OpenKey(system, "CurrentControlSet");
         if (current_cs != NULL) {
            services = registry.OpenKey(current_cs, "Services");
            if (services != NULL) {
               carrier = registry.OpenKey(services, "Carrier");
               if (carrier != NULL) {
                  long port_base = 0x360;
                  int params = sscanf(PortBase->Text.c_str(), "%x", &port_base);
                  bool success = true;
                  if (success) registry.SetValue(carrier, "Type", 0x1);
                  if (success) success = registry.SetValue(carrier, "Start", 0x2);
                  if (success) success = registry.SetValue(carrier, "ErrorControl", 0x1);
                  if (success) success = registry.SetValue(carrier, "PortBase", port_base);
                  if (!success) {
                     message = "Fehler beim Setzen der Treiber-Parameter in der Registrierungsdatenbank.";
                  }
               }
            }
         }
      }
      if (carrier == NULL) {
         message = "Fehler beim Zugriff auf die Registrierungsdatenbank.";
      }
      if (carrier != NULL) registry.CloseKey(carrier);
      if (services != NULL) registry.CloseKey(services);
      if (current_cs != NULL) registry.CloseKey(current_cs);
      if (system != NULL) registry.CloseKey(system);
   } else {
      message = "Datei ";
      message += src;
      message += " kann nicht nach ";
      message += dest_dir;
      message += " kopiert werden.";
   }
   if (message.Length() > 0) {
      message += " Der Treiber konnte nicht installiert werden.";
   } else {
      message = "Der Treiber wurde erfolgreich installiert. Zum Starten des Treibers muss Windows neu gestartet werden.";
      Installation->Visible = false;
   }
   Info->Text = message;
   Beep(1000, 100);
}

//---------------------------------------------------------------------------

