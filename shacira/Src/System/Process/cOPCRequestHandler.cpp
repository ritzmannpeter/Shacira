//## begin module%43141F4F033D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43141F4F033D.cm

//## begin module%43141F4F033D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43141F4F033D.cp

//## Module: cOPCRequestHandler%43141F4F033D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOPCRequestHandler.cpp

//## begin module%43141F4F033D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43141F4F033D.additionalIncludes

//## begin module%43141F4F033D.includes preserve=yes

/// PR 19.08.06 - skipping proxies with ip address 127.0.0.1nt

//## end module%43141F4F033D.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cOPCRequestHandler
#include "System/Process/cOPCRequestHandler.h"
// cOPCClientProcess
#include "System/Process/cOPCClientProcess.h"
// cProxy
#include "System/Objects/cProxy.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cRemoteContext
#include "Client/RemoteDatabase/cRemoteContext.h"
//## begin module%43141F4F033D.additionalDeclarations preserve=yes

#define OPC_READABLE    0x1
#define OPC_WRITEABLE   0x2

static int _Count = 0;

class cConnectionControl: public cControlThread
{
public:
   cConnectionControl(cOPCRequestHandler * handler) {_Handler = handler;};
   virtual ~cConnectionControl() {};
   INT_T MainFunc (void *extra)
   {
MAINFUNC_PROLOG(_Name.c_str())
      while (!(_Terminated || _Terminating)) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
         if (_Handler != NULL) {
            if (_Handler->RefreshItems()) {
Beep(100,100);
            }
         }
MAINFUNC_LOOP_EPILOG
   		if (!_Terminated) cSystemUtils::Suspend(500);
         _Count++;
      }
      return 0;
MAINFUNC_EPILOG
   };
private:
   cOPCRequestHandler * _Handler;
};
static cConnectionControl * _ConnectionControl = NULL;

//## end module%43141F4F033D.additionalDeclarations


// Class cOPCRequestHandler 






cOPCRequestHandler::cOPCRequestHandler()
  //## begin cOPCRequestHandler::cOPCRequestHandler%.hasinit preserve=no
      : _LocalServer(false), _OnlyDedicated(false)
  //## end cOPCRequestHandler::cOPCRequestHandler%.hasinit
  //## begin cOPCRequestHandler::cOPCRequestHandler%.initialization preserve=yes
  //## end cOPCRequestHandler::cOPCRequestHandler%.initialization
{
  //## begin cOPCRequestHandler::cOPCRequestHandler%.body preserve=yes
_ASSERT_UNCOND
  //## end cOPCRequestHandler::cOPCRequestHandler%.body
}

cOPCRequestHandler::cOPCRequestHandler(const cOPCRequestHandler &right)
  //## begin cOPCRequestHandler::cOPCRequestHandler%copy.hasinit preserve=no
      : _LocalServer(false), _OnlyDedicated(false)
  //## end cOPCRequestHandler::cOPCRequestHandler%copy.hasinit
  //## begin cOPCRequestHandler::cOPCRequestHandler%copy.initialization preserve=yes
  //## end cOPCRequestHandler::cOPCRequestHandler%copy.initialization
{
  //## begin cOPCRequestHandler::cOPCRequestHandler%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cOPCRequestHandler::cOPCRequestHandler%copy.body
}

cOPCRequestHandler::cOPCRequestHandler (cSHProcess *process, CONST_STRING_T handler_name)
  //## begin cOPCRequestHandler::cOPCRequestHandler%1125391951.hasinit preserve=no
      : _LocalServer(false), _OnlyDedicated(false)
  //## end cOPCRequestHandler::cOPCRequestHandler%1125391951.hasinit
  //## begin cOPCRequestHandler::cOPCRequestHandler%1125391951.initialization preserve=yes
  , cRequestHandler(process, handler_name)
  //## end cOPCRequestHandler::cOPCRequestHandler%1125391951.initialization
{
  //## begin cOPCRequestHandler::cOPCRequestHandler%1125391951.body preserve=yes
   _Type = OPC_HANDLER;
   _ConnectionControl = new cConnectionControl(this);
   _ConnectionControl->Start();
  //## end cOPCRequestHandler::cOPCRequestHandler%1125391951.body
}


cOPCRequestHandler::~cOPCRequestHandler()
{
  //## begin cOPCRequestHandler::~cOPCRequestHandler%.body preserve=yes
  //## end cOPCRequestHandler::~cOPCRequestHandler%.body
}



//## Other Operations (implementation)
void cOPCRequestHandler::SetConnectionInfoFile (CONST_STRING_T file)
{
  //## begin cOPCRequestHandler::SetConnectionInfoFile%1134632034.body preserve=yes
   _ConnectionInfoFile = cFileSystemUtils::FullPath(file);
  //## end cOPCRequestHandler::SetConnectionInfoFile%1134632034.body
}

BOOL_T cOPCRequestHandler::RefreshItems ()
{
  //## begin cOPCRequestHandler::RefreshItems%1125391952.body preserve=yes
   BOOL_T new_items = false;
   if (_Process != NULL) {
      cOPCClientProcess * opc_client_process = (cOPCClientProcess*)_Process;
      STRING_LIST_T context_names;
      opc_client_process->NewContextNames(context_names);
      STRING_LIST_T::const_iterator i = context_names.cbegin();
      while (i != context_names.cend()) {
         STRING_T context_name = (*i);
         cContext * context = opc_client_process->NewContext(context_name.c_str());
         if (AddContext(context_name.c_str(), context)) {
            new_items = true;
            WORD quality = 0;
            DWORD access_rights = 0;
            VARTYPE opc_datatype = 0;
            STRING_LIST_T var_names;
            context->VariableNames(var_names);
            STRING_LIST_T::const_iterator j = var_names.cbegin();
            STRING_T var_name;
            while (j != var_names.cend()) {
               var_name = (*j);
               cVarDef * var_def = context->VarDef(var_name.c_str());
               if (var_def != NULL) {
                  if (VarSpec(var_def, quality, access_rights, opc_datatype)) {
                     char item_name[0x200] = {0};
                     ULONG_T elements = var_def->Elements();
                     for (ULONG_T pos=0; pos<elements; pos++) {
                        long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
                        var_def->GetIndices(pos, i1, i2, i3, i4);
                        if (i4 != -1) {
                           SafePrintf(item_name, sizeof(item_name), "%s[%d][%d][%d][%d]",
                                      var_name.c_str(),
                                      i1, i2, i3, i4);
                        } else if (i3 != -1) {
                           SafePrintf(item_name, sizeof(item_name), "%s[%d][%d][%d]",
                                      var_name.c_str(),
                                      i1, i2, i3);
                        } else if (i2 != -1) {
                           SafePrintf(item_name, sizeof(item_name), "%s[%d][%d]",
                                      var_name.c_str(),
                                      i1, i2);
                        } else if (i1 != -1) {
                           SafePrintf(item_name, sizeof(item_name), "%s[%d]",
                                      var_name.c_str(),
                                      i1);
                        } else {
                           SafePrintf(item_name, sizeof(item_name), "%s", var_name.c_str());
                        }
                        cVarRef * var_ref = NULL;
                        try {
                           var_ref = context->VarRef(item_name);
                        } catch (cError & e) {
                           ErrorPrintf("%s while resolving %s\n", (const char *)e, item_name);
                           return false;
                        } catch (...) {
                           ErrorPrintf("unknown exception while resolving %s\n", item_name);
                           return false;
                        }
                        SetItemDefinition(var_ref, context_name.c_str(), (cRemoteContext*)context,
                                          item_name, quality, access_rights, opc_datatype);
                     }
                  }
               }
               j++;
            }
         }
         i++;
      }
   }
   if (new_items) {
      UpdateContextInfo();
   }
   return new_items;
  //## end cOPCRequestHandler::RefreshItems%1125391952.body
}

void cOPCRequestHandler::SetItemDefinition (cVarRef *var_ref, CONST_STRING_T context_name, cRemoteContext *context, CONST_STRING_T var_name, WORD quality, DWORD access_rights, VARTYPE opc_datatype)
{
  //## begin cOPCRequestHandler::SetItemDefinition%1125393495.body preserve=yes
  //## end cOPCRequestHandler::SetItemDefinition%1125393495.body
}

BOOL_T cOPCRequestHandler::AddContext (CONST_STRING_T context_name, cContext *context)
{
  //## begin cOPCRequestHandler::AddContext%1125393499.body preserve=yes
   try {
      if (IsSupported(context_name, context)) {
         CONTEXT_MAP_T::const_iterator i = _ContextMap.find(context_name);
         if (i == _ContextMap.cend()) {
//            context->Connect();
//            context->Create();
            _ContextMap[context_name] = context;
            return true;
         } else {
            return false;
         }
      } else {
         return false;
      }
   } catch (cError & e) {
      ErrorPrintf("%s while adding context to request handler\n", (const char *)e);
      return false;
   } catch (...) {
      ErrorPrintf("unknown execption while adding context to request handler\n");
      return false;
   }
  //## end cOPCRequestHandler::AddContext%1125393499.body
}

void cOPCRequestHandler::AddServer (CONST_STRING_T server_name)
{
  //## begin cOPCRequestHandler::AddServer%1141820977.body preserve=yes
   _ServerMap[server_name] = server_name;
   InfoPrintf("dedicated context %s\n", server_name);
  //## end cOPCRequestHandler::AddServer%1141820977.body
}

void cOPCRequestHandler::RemoveServer (CONST_STRING_T server_name)
{
  //## begin cOPCRequestHandler::RemoveServer%1141820978.body preserve=yes
   _ServerMap.erase(server_name);
  //## end cOPCRequestHandler::RemoveServer%1141820978.body
}

cContext * cOPCRequestHandler::Context (CONST_STRING_T context_name)
{
  //## begin cOPCRequestHandler::Context%1125393500.body preserve=yes
   CONTEXT_MAP_T::const_iterator i = _ContextMap.find(context_name);
   if (i == _ContextMap.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cOPCRequestHandler::Context%1125393500.body
}

BOOL_T cOPCRequestHandler::VarSpec (cVarDef *var_def, WORD &quality, DWORD &access_rights, VARTYPE &opc_datatype)
{
  //## begin cOPCRequestHandler::VarSpec%1125393504.body preserve=yes
   ULONG_T system_flags = var_def->_SystemFlags;
   if (!(system_flags & HOST_READ ||
         system_flags & HOST_WRITE)) {
      return false;
   }
   UCHAR_T vartype = var_def->_VarType;
   if (vartype == SH_VAR_ACT) {
      access_rights = OPC_READABLE;
   } else {
      if (system_flags & HOST_WRITE) {
         access_rights = OPC_READABLE|OPC_WRITEABLE;
      } else {
         access_rights = OPC_READABLE;
      }
   }
   opc_datatype = VT_EMPTY;
   UCHAR_T data_type = var_def->DataType();
   UCHAR_T precision = var_def->_Precision;
   switch (data_type) {
   case SH_CHAR:
      opc_datatype = VT_I1;
      break;
   case SH_UCHAR:
      opc_datatype = VT_UI1;
      break;
   case SH_SHORT:
      if (precision > 0) {
         opc_datatype = VT_R8;
      } else {
         opc_datatype = VT_I2;
      }
      break;
   case SH_USHORT:
      if (precision > 0) {
         opc_datatype = VT_R8;
      } else {
         opc_datatype = VT_UI2;
      }
      break;
   case SH_LONG:
      if (precision > 0) {
         opc_datatype = VT_R8;
      } else {
         opc_datatype = VT_I4;
      }
      break;
   case SH_ULONG:
      if (precision > 0) {
         opc_datatype = VT_R8;
      } else {
         opc_datatype = VT_UI4;
      }
      break;
   case SH_BIT_8:
      opc_datatype = VT_UI1;
      break;
   case SH_BIT_16:
      opc_datatype = VT_UI2;
      break;
   case SH_BIT_32:
      opc_datatype = VT_UI4;
      break;
   case SH_FLOAT:
      opc_datatype = VT_R8;
      break;
   case SH_DOUBLE:
      opc_datatype = VT_R8;
      break;
   case SH_STRING:
   case SH_WSTRING:
      opc_datatype = VT_BSTR;
      break;
   default:
      opc_datatype = VT_EMPTY;
      break;
   }
   return true;
  //## end cOPCRequestHandler::VarSpec%1125393504.body
}

void cOPCRequestHandler::UpdateContextInfo ()
{
  //## begin cOPCRequestHandler::UpdateContextInfo%1134592366.body preserve=yes
   if (_ContextMap.size() > 0) {
      if (_ConnectionInfoFile.size() > 0) {
         cSHFile file(_ConnectionInfoFile.c_str());
         if (file.Open(FILE_MODE_CREATE)) {
            CONTEXT_MAP_T::const_iterator i = _ContextMap.cbegin();
            while (i != _ContextMap.cend()) {
               cContext * context = (*i).second;
               STRING_T context_name = context->get_Name();
               STRING_T ip_addr = "?";
               STRING_T computer_name = "?";
               int port = 0;
               int sec = 0;
               int minute = 0;
               int hour = 0;
               int day = 0;
               int month = 0;
               int year = 0;
               cProxy * proxy = _Process->Proxy(context_name.c_str());
               if (proxy != NULL) {
                  try {
                     if (proxy != NULL) {
                        cTimeObject time_stamp = proxy->get_TimeStamp();
                        ULONG_T secs = time_stamp;
                        sec = time_stamp.Get(cTimeObject::SECOND);
                        minute = time_stamp.Get(cTimeObject::MINUTE);
                        hour = time_stamp.Get(cTimeObject::HOUR);
                        day = time_stamp.Get(cTimeObject::DAY);
                        month = time_stamp.Get(cTimeObject::MONTH);
                        year = time_stamp.Get(cTimeObject::YEAR);
                        ip_addr = proxy->get_IPAddress();
                        computer_name = proxy->get_Computer();
                        port = proxy->get_Port();
                        file.Printf("%s;%s;%s;%d;%02.02d.%02.02d.%04.04d %02.02d:%02.02d:%02.02d;\n",
                                    context_name.c_str(),
                                    computer_name.c_str(),
                                    ip_addr.c_str(),
                                    port,
                                    day, month, year, hour, minute, sec);
                     }
                  } catch (cError & e) {
                     ErrorPrintf("%s while retrieving proxy info of %s\n", (const char *)e, context_name.c_str());
                  } catch (...) {
                     ErrorPrintf("unknown exception while retrieving proxy info of %s\n", context_name.c_str());
                  }
               }
               i++;
            }
            file.Close();
         }
      }
   }
  //## end cOPCRequestHandler::UpdateContextInfo%1134592366.body
}

BOOL_T cOPCRequestHandler::IsSupported (CONST_STRING_T server_name, cContext *context)
{
  //## begin cOPCRequestHandler::IsSupported%1141821098.body preserve=yes
   cProxy * proxy = _Process->Proxy(server_name);
   if (proxy == NULL) {
      InfoPrintf("skipped context %s: proxy is NULL\n", server_name);
      return false;
   } else {
      STRING_T ip_addr = proxy->get_IPAddress();
      if (_stricmp(ip_addr.c_str(), "127.0.0.1") == 0) {
         InfoPrintf("skipped context %s: unsupported ip address %s\n", server_name, ip_addr.c_str());
         return false;
      }
   }
   if (!_LocalServer &&
       !_OnlyDedicated) {
      return true;
   } else {
      if (_LocalServer) {
         if (context->IsRemote()) {
            cRemoteContext * remote_context = (cRemoteContext*)context;
            if (remote_context->IsLocal()) {
               return true;
            } else {
               InfoPrintf("skipped context %s: not remote 1\n", server_name);
               return false;
            }
         } else {
            InfoPrintf("skipped context %s: not remote 2\n", server_name);
            return false;
         }
      } else {
         SERVER_MAP_T::const_iterator i = _ServerMap.find(server_name);
         if (i == _ServerMap.cend()) {
            InfoPrintf("skipped context %s: filtered\n", server_name);
            return false;
         } else {
            return true;
         }
      }
   }
  //## end cOPCRequestHandler::IsSupported%1141821098.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cOPCRequestHandler::get_LocalServer () const
{
  //## begin cOPCRequestHandler::get_LocalServer%440ECD640128.get preserve=no
  return _LocalServer;
  //## end cOPCRequestHandler::get_LocalServer%440ECD640128.get
}

void cOPCRequestHandler::set_LocalServer (BOOL_T value)
{
  //## begin cOPCRequestHandler::set_LocalServer%440ECD640128.set preserve=no
  _LocalServer = value;
  //## end cOPCRequestHandler::set_LocalServer%440ECD640128.set
}

BOOL_T cOPCRequestHandler::get_OnlyDedicated () const
{
  //## begin cOPCRequestHandler::get_OnlyDedicated%440ECE0B035B.get preserve=no
  return _OnlyDedicated;
  //## end cOPCRequestHandler::get_OnlyDedicated%440ECE0B035B.get
}

void cOPCRequestHandler::set_OnlyDedicated (BOOL_T value)
{
  //## begin cOPCRequestHandler::set_OnlyDedicated%440ECE0B035B.set preserve=no
  _OnlyDedicated = value;
  //## end cOPCRequestHandler::set_OnlyDedicated%440ECE0B035B.set
}

SERVER_MAP_T cOPCRequestHandler::get_ServerMap () const
{
  //## begin cOPCRequestHandler::get_ServerMap%440ECD8B03E7.get preserve=no
  return _ServerMap;
  //## end cOPCRequestHandler::get_ServerMap%440ECD8B03E7.get
}

void cOPCRequestHandler::set_ServerMap (SERVER_MAP_T value)
{
  //## begin cOPCRequestHandler::set_ServerMap%440ECD8B03E7.set preserve=no
  _ServerMap = value;
  //## end cOPCRequestHandler::set_ServerMap%440ECD8B03E7.set
}

// Additional Declarations
  //## begin cOPCRequestHandler%43141F4F033D.declarations preserve=yes
  //## end cOPCRequestHandler%43141F4F033D.declarations

//## begin module%43141F4F033D.epilog preserve=yes
//## end module%43141F4F033D.epilog
