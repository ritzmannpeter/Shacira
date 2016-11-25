//---------------------------------------------------------------------------
#ifndef cWinRegistryH
#define cWinRegistryH
//---------------------------------------------------------------------------

#include <windows.h>

class cWinRegistry{
private:
   bool SetPrivilege(const char * privilege_name, bool value);
   bool SetPrivileges();
public:
   cWinRegistry();
   virtual ~cWinRegistry();
   HKEY SetKey(const char * key);
   HKEY OpenKey(HKEY parent, const char * subkey_name);
   void CloseKey(HKEY key);
   bool GetValue(HKEY key, const char * value_name, const char * buffer);
   bool GetValue(HKEY key, const char * value_name, long * value);
   bool SetValue(HKEY key, const char * value_name, const char * value);
   bool SetValue(HKEY key, const char * value_name, long value);
};



#endif
