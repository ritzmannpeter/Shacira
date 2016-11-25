/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

#include <windows.h>
#include "cWinSystem.h"
#include "cWinRegistry.h"
#include "caritf.h"
#include "QtUtils.h"

void TestClick(QObject * object);
void InstallClick(QObject * object);

void DrvInstForm::Test_clicked()
{
	TestClick(this);
}

void DrvInstForm::Install_clicked()
{
	InstallClick(this);
}

typedef struct {
   cWinSystem * _WinSystem;
   int _SystemType;
   unsigned long _AddrLowPort;
   unsigned long _AddrLowValue;
   unsigned long _AddrHighPort;
   unsigned long _AddrHighValue;
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
	DrvInstForm * _Form;
}	FORM_DATA;

#define _OBJECT_DATA_ ((FORM_DATA*)(QtUtils::WidgetData(object)))

static QString HexValue(long value)
{
   char buf[64] = {0};
   sprintf(buf, "%X", value);
   return QString(buf);
}

static QString DecValue(long value)
{
   char buf[64] = {0};
   sprintf(buf, "%d", value);
   return QString(buf);
}

static void ReadPort(HANDLE hnd, const char * port_name, const char * port_value,
              unsigned long * port, unsigned long * value)
{
   *port = 0;
   *value = 0;
   long rc = CARITF_GetParam(hnd, port_name, (long*)port);
   if (rc >= 0) {
      rc = CARITF_GetParam(hnd, port_value, (long*)value);
   }
}

static void ReadPorts(QObject * object, HANDLE hnd)
{
   ReadPort(hnd, "ADDR_LOW_PORT", "VALUE_LOW_PORT", &_OBJECT_DATA_->_AddrLowPort, &_OBJECT_DATA_->_AddrLowValue);
   ReadPort(hnd, "ADDR_HIGH_PORT", "VALUE_HIGH_PORT", &_OBJECT_DATA_->_AddrHighPort, &_OBJECT_DATA_->_AddrHighValue);
   ReadPort(hnd, "CMD_PORT", "VALUE_CMD_PORT", &_OBJECT_DATA_->_CmdPort, &_OBJECT_DATA_->_CmdValue);
   ReadPort(hnd, "READ_PORT", "VALUE_READ_PORT", &_OBJECT_DATA_->_ReadPort, &_OBJECT_DATA_->_ReadValue);
   ReadPort(hnd, "WRITE_PORT", "VALUE_WRITE_PORT", &_OBJECT_DATA_->_WritePort, &_OBJECT_DATA_->_WriteValue);
   ReadPort(hnd, "STATUS_PORT", "VALUE_STATUS_PORT", &_OBJECT_DATA_->_StatusPort, &_OBJECT_DATA_->_StatusValue);
}

static void ShowPorts(QObject * object)
{
   _OBJECT_DATA_->_Form->AddrLow->setText(HexValue(_OBJECT_DATA_->_AddrLowPort));
   _OBJECT_DATA_->_Form->AddrLowV->setText(HexValue(_OBJECT_DATA_->_AddrLowValue));
   _OBJECT_DATA_->_Form->AddrHigh->setText(HexValue(_OBJECT_DATA_->_AddrHighPort));
   _OBJECT_DATA_->_Form->AddrHighV->setText(HexValue(_OBJECT_DATA_->_AddrHighValue));
   _OBJECT_DATA_->_Form->Cmd->setText(HexValue(_OBJECT_DATA_->_CmdPort));
   _OBJECT_DATA_->_Form->CmdV->setText(HexValue(_OBJECT_DATA_->_CmdValue));
   _OBJECT_DATA_->_Form->Read->setText(HexValue(_OBJECT_DATA_->_ReadPort));
   _OBJECT_DATA_->_Form->ReadV->setText(HexValue(_OBJECT_DATA_->_ReadValue));
   _OBJECT_DATA_->_Form->Write->setText(HexValue(_OBJECT_DATA_->_WritePort));
   _OBJECT_DATA_->_Form->WriteV->setText(HexValue(_OBJECT_DATA_->_WriteValue));
   _OBJECT_DATA_->_Form->Status->setText(HexValue(_OBJECT_DATA_->_StatusPort));
   _OBJECT_DATA_->_Form->StatusV->setText(HexValue(_OBJECT_DATA_->_StatusValue));
}

static void ReadParam(HANDLE hnd, const char * param_name, unsigned long * value)
{
   *value = 0;
   long rc = CARITF_GetParam(hnd, param_name, (long*)value);
}

static void ReadParams(QObject * object, HANDLE hnd)
{
   ReadParam(hnd, "VERSION", &_OBJECT_DATA_->_Version);
   ReadParam(hnd, "CHECK_MODE", &_OBJECT_DATA_->_CheckMode);
   ReadParam(hnd, "STABILITY", &_OBJECT_DATA_->_Stability);
   ReadParam(hnd, "RETRIES", &_OBJECT_DATA_->_Retries);
   ReadParam(hnd, "DELAY_TIME", &_OBJECT_DATA_->_DelayTime);
   ReadParam(hnd, "SIMULATE_HARDWARE", &_OBJECT_DATA_->_SimulateHardware);
}

static void ShowParams(QObject * object)
{
   _OBJECT_DATA_->_Form->Version->setText(DecValue(_OBJECT_DATA_->_Version));
   _OBJECT_DATA_->_Form->CheckMode->setText(DecValue(_OBJECT_DATA_->_CheckMode));
   _OBJECT_DATA_->_Form->Stability->setText(DecValue(_OBJECT_DATA_->_Stability));
   _OBJECT_DATA_->_Form->Retries->setText(DecValue(_OBJECT_DATA_->_Retries));
   _OBJECT_DATA_->_Form->DelayTime->setText(DecValue(_OBJECT_DATA_->_DelayTime));
   _OBJECT_DATA_->_Form->SimulateHardware->setText(DecValue(_OBJECT_DATA_->_SimulateHardware));
}

static void DriverInfo(QObject * object, bool installed)
{
   QString message;
   _OBJECT_DATA_->_Form->Test->setEnabled(false);
   _OBJECT_DATA_->_Form->Install->setEnabled(false);
   _OBJECT_DATA_->_Form->PortBase->setEnabled(false);
   if (installed) {
      message = "Der Treiber zum Zugriff auf EEPROMS ist installiert.";
      _OBJECT_DATA_->_Form->Test->setEnabled(true);
   } else {
      message = "Der Treiber zum Zugriff auf EEPROMS ist nicht installiert oder nicht aktiviert.";
      if (_OBJECT_DATA_->_SystemType == WIN_NT) {
         message += "Durch betätigen der Schaltfläche 'Installieren' können Sie den Treiber installieren.";
	      _OBJECT_DATA_->_Form->Install->setEnabled(true);
		   _OBJECT_DATA_->_Form->PortBase->setEnabled(true);
      } else if (_OBJECT_DATA_->_SystemType == WIN_2K || _OBJECT_DATA_->_SystemType == WIN_XP) {
         message += "Sie können den Treiber mit der Hardware-Unterstützung von Windows installieren.";
         message += "Die benötigten Dateien finden Sie im DNC-Unterverzeichnis Driver\\Win2000.";
      }
   }
   _OBJECT_DATA_->_Form->Info->setText(message);
}

static bool FileCopy(const char * src, const char * dst)
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

static void TestClick(QObject * object)
{
   _OBJECT_DATA_->_Form->Info->setText("");
   HANDLE hnd = CARITF_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
      ReadPorts(object, hnd);
      ShowPorts(object);
      long value = 1 << 7;
      if (_OBJECT_DATA_->_StatusValue & value) {
         _OBJECT_DATA_->_Form->Info->setText("Zugriff auf EEPROM-Hardware nicht möglich. \
Möglicherweise ist auf diesem Rechner keine Hardware installiert \
oder die Basis I/O-Addresse ist falsch gewählt.");
      } else {
         _OBJECT_DATA_->_Form->Info->setText("Zugriff auf EEPROM-Hardware möglich.");
      }
      CARITF_Close(hnd);
   } else {
      _OBJECT_DATA_->_Form->Info->setText("Auf den Treiber kann nicht zugegriffen werden.");
   }
}

static void InstallClick(QObject * object)
{
   QString message;
   const char * src = "Driver\\WinNT\\carrier.sys";
   char dest_dir[512] = {0};
   sprintf(dest_dir, "%s\\%s", _OBJECT_DATA_->_WinSystem->SystemDirectory(), "drivers");
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
                  int params = sscanf(_OBJECT_DATA_->_Form->PortBase->currentText(), "%x", &port_base);
                  bool success = true;
                  if (success) registry.SetValue(carrier, "Type", 0x1);
                  if (success) success = registry.SetValue(carrier, "Start", 0x2);
                  if (success) success = registry.SetValue(carrier, "ErrorControl", 0x1);
                  if (success) success = registry.SetValue(carrier, "PortBase", port_base);
                  if (!success) {
                     message = "Fehler beim Setzen der Treiber-Parameter in der Registrierungsdatenbank.";
                  } else {
#ifdef lassma
							if (!_OBJECT_DATA_->_WinSystem->StartDevice(CarrierName())) {
	                     message = "Der Treiber ";
								message += CarrierName();
								message += " konnte nicht gestartet werden. Für die Installation des Treibers werden Administratorrechte benötigt.";
							}
#endif
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
   if (message.length() > 0) {
      message += " Der Treiber konnte nicht installiert werden.";
   } else {
      message = "Der Treiber wurde erfolgreich installiert. Zum Starten des Treibers muss Windows neu gestartet werden.";
      _OBJECT_DATA_->_Form->Installation->setEnabled(false);
   }
   _OBJECT_DATA_->_Form->Info->setText(message);
   Beep(1000, 100);
}

void DrvInstForm::init()
{
	QObject * object = this;
	FORM_DATA * form_data = (FORM_DATA*)calloc(1, sizeof(*form_data));
	QtUtils::AddWidgetData(this, form_data);
	_OBJECT_DATA_->_Form = this;
   _OBJECT_DATA_->_WinSystem = new cWinSystem;
   _OBJECT_DATA_->_SystemType = _OBJECT_DATA_->_WinSystem->SystemType();
   switch (_OBJECT_DATA_->_SystemType) {
   case WIN_95: System->setText("Windows 95"); break;
   case WIN_98: System->setText("Windows 98"); break;
   case WIN_ME: System->setText("Windows ME"); break;
   case WIN_NT: System->setText("Windows NT"); break;
   case WIN_2K: System->setText("Windows 2000"); break;
   case WIN_XP: System->setText("Windows XP"); break;
   default: System->setText("Nicht definiert"); break;
   }
   QString number;
   number.setNum(_OBJECT_DATA_->_WinSystem->VersionInfo()->dwMajorVersion);
   MajorVersion->setText(number);
   number.setNum(_OBJECT_DATA_->_WinSystem->VersionInfo()->dwMinorVersion);
   MinorVersion->setText(number);
   number.setNum(_OBJECT_DATA_->_WinSystem->VersionInfo()->dwPlatformId);
   PlatformId->setText(number);
   number.setNum(_OBJECT_DATA_->_WinSystem->VersionInfo()->dwBuildNumber);
   BuildNumber->setText(number);
   VersionString->setText(_OBJECT_DATA_->_WinSystem->VersionInfo()->szCSDVersion);
   SystemDirectory->setText(_OBJECT_DATA_->_WinSystem->SystemDirectory());
   CurrentDirectory->setText(_OBJECT_DATA_->_WinSystem->CurrentDirectory());
   HANDLE hnd = CARITF_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
	   ReadPorts(this, hnd);
      ShowPorts(this);
      ReadParams(this, hnd);
      ShowParams(this);
      CARITF_Close(hnd);
      DriverInfo(this, true);
   } else {
      DriverInfo(this, false);
   }
	PortBase->insertItem("300", 0);
	PortBase->insertItem("320", 1);
	PortBase->insertItem("340", 2);
	PortBase->insertItem("360", 3);
	PortBase->insertItem("380", 4);
   PortBase->setCurrentItem(3);
}
