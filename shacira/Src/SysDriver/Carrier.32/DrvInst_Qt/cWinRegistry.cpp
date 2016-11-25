
#include "cWinRegistry.h"
#include <stdio.h>

void Error(const char * func, long error_code)
{
   char message[256] = {0};
   FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL,
                 error_code,
                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                 (LPTSTR)message,
                 sizeof(message), NULL);
   MessageBox( NULL, (LPCTSTR)message, func, MB_OK | MB_ICONINFORMATION );
}

HKEY _OpenKey(HKEY parent, const char * subkey_name)
{
   HKEY key = 0;
   long rc = RegOpenKeyEx(parent, subkey_name, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &key);
   if (rc != ERROR_SUCCESS) {
      Error("OpenKey", rc);
      return NULL;
   }
   return key;
}

HKEY _CreateKey(HKEY parent, const char * subkey_name)
{
   HKEY key = 0;
   long rc = RegCreateKey(parent, subkey_name, &key);
   if (rc != ERROR_SUCCESS) {
      Error("CreateKey", rc);
      return NULL;
   }
   return key;
}


cWinRegistry::cWinRegistry()
{
   SetPrivileges();
}

bool cWinRegistry::SetPrivilege(const char * privilege_name, bool value)
{
   HANDLE token_hnd = NULL;
   TOKEN_PRIVILEGES tp;
   LUID luid;
   if (!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                         &token_hnd)) return false;
   if (!LookupPrivilegeValue(NULL,             // lookup privilege on local system
                             privilege_name,   // privilege to lookup
                             &luid )) {        // receives LUID of privilege
      return false;
   }
   tp.PrivilegeCount = 1;
   tp.Privileges[0].Luid = luid;
   if (value) {
      tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   } else {
      tp.Privileges[0].Attributes = 0;
   }
   // Enable the privilege or disable all privileges.
   AdjustTokenPrivileges(token_hnd,
                         FALSE, &tp,
                         sizeof(TOKEN_PRIVILEGES),
                        (PTOKEN_PRIVILEGES) NULL,
                        (PDWORD) NULL);
   // Call GetLastError to determine whether the function succeeded.
   if (GetLastError() != ERROR_SUCCESS) {
      return false;
   }
   return true;
}

bool cWinRegistry::SetPrivileges()
{
   if (!SetPrivilege(SE_RESTORE_NAME, TRUE)) return false;
   if (!SetPrivilege(SE_BACKUP_NAME, TRUE)) return false;
   return true;
}

cWinRegistry::~cWinRegistry()
{
}

HKEY cWinRegistry::SetKey(const char * key)
{
   return NULL;
}

HKEY cWinRegistry::OpenKey(HKEY parent, const char * subkey_name)
{
   HKEY key = _OpenKey(parent, subkey_name);
   if (key == NULL) {
      key = _CreateKey(parent, subkey_name);
   }
   return key;
}

void cWinRegistry::CloseKey(HKEY key)
{
   RegCloseKey(key);
}

bool cWinRegistry::GetValue(HKEY key, const char * value_name, const char * buffer)
{
   return false;
}

bool cWinRegistry::GetValue(HKEY key, const char * value_name, long * value)
{
   return false;
}

bool cWinRegistry::SetValue(HKEY key, const char * value_name, const char * value)
{
   long rc = RegSetValueEx(key, value_name, 0, REG_SZ, (const unsigned char *)value, strlen(value));
   if (rc != ERROR_SUCCESS) {
      Error("Set string value", rc);
      return false;
   }
   return true;
}

bool cWinRegistry::SetValue(HKEY key, const char * value_name, long value)
{
   long rc = RegSetValueEx(key, value_name, 0, REG_DWORD, (const unsigned char*)&value, sizeof(value));
   if (rc != ERROR_SUCCESS) {
      Error("Set long value", rc);
      return false;
   }
   return true;
}





