//## begin module%412ADD260213.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412ADD260213.cm

//## begin module%412ADD260213.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412ADD260213.cp

//## Module: cSharedLibrary%412ADD260213; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSharedLibrary.cpp

//## begin module%412ADD260213.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%412ADD260213.additionalIncludes

//## begin module%412ADD260213.includes preserve=yes
//## end module%412ADD260213.includes

// cSharedLibrary
#include "System/Sys/cSharedLibrary.h"
//## begin module%412ADD260213.additionalDeclarations preserve=yes
//## end module%412ADD260213.additionalDeclarations


// Class cSharedLibrary 






//## begin cSharedLibrary::Libraries%412AECDA038A.attr preserve=no  implementation: static SHARED_LIBRARY_MAP_T {U} 
SHARED_LIBRARY_MAP_T cSharedLibrary::_Libraries;
//## end cSharedLibrary::Libraries%412AECDA038A.attr

cSharedLibrary::cSharedLibrary()
  //## begin cSharedLibrary::cSharedLibrary%.hasinit preserve=no
      : _Handle(INVALID_LIBRARY_HANDLE), _NativeError(0)
  //## end cSharedLibrary::cSharedLibrary%.hasinit
  //## begin cSharedLibrary::cSharedLibrary%.initialization preserve=yes
  //## end cSharedLibrary::cSharedLibrary%.initialization
{
  //## begin cSharedLibrary::cSharedLibrary%.body preserve=yes
_ASSERT_UNCOND
  //## end cSharedLibrary::cSharedLibrary%.body
}

cSharedLibrary::cSharedLibrary(const cSharedLibrary &right)
  //## begin cSharedLibrary::cSharedLibrary%copy.hasinit preserve=no
      : _Handle(INVALID_LIBRARY_HANDLE), _NativeError(0)
  //## end cSharedLibrary::cSharedLibrary%copy.hasinit
  //## begin cSharedLibrary::cSharedLibrary%copy.initialization preserve=yes
  //## end cSharedLibrary::cSharedLibrary%copy.initialization
{
  //## begin cSharedLibrary::cSharedLibrary%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSharedLibrary::cSharedLibrary%copy.body
}

cSharedLibrary::cSharedLibrary (CONST_STRING_T name)
  //## begin cSharedLibrary::cSharedLibrary%1093328409.hasinit preserve=no
      : _Handle(INVALID_LIBRARY_HANDLE), _NativeError(0)
  //## end cSharedLibrary::cSharedLibrary%1093328409.hasinit
  //## begin cSharedLibrary::cSharedLibrary%1093328409.initialization preserve=yes
  //## end cSharedLibrary::cSharedLibrary%1093328409.initialization
{
  //## begin cSharedLibrary::cSharedLibrary%1093328409.body preserve=yes
   _Name = name;
   _LibraryName = SharedLibraryName(name);
   _Libraries[_Name.c_str()] = this;
  //## end cSharedLibrary::cSharedLibrary%1093328409.body
}


cSharedLibrary::~cSharedLibrary()
{
  //## begin cSharedLibrary::~cSharedLibrary%.body preserve=yes
  //## end cSharedLibrary::~cSharedLibrary%.body
}



//## Other Operations (implementation)
LONG_T cSharedLibrary::Load ()
{
  //## begin cSharedLibrary::Load%1093328410.body preserve=yes
#if defined(_WIN32)
   if (_Handle != INVALID_LIBRARY_HANDLE) return 0;
   _Handle = LoadLibrary(_LibraryName.c_str());
   if (_Handle == INVALID_LIBRARY_HANDLE) {
      _NativeError = GetLastError();
      throw cError(SHARED_LIBRARY_LOAD, _NativeError, _LibraryName.c_str());
   } else {
      _NativeError = 0;
      return 0;
   }
#elif defined(__linux__)
PORT_LEVEL_3
   return -1;
#else
NO_PLATFORM
#endif
  //## end cSharedLibrary::Load%1093328410.body
}

SHARED_FUNCTION_ADDRESS_T cSharedLibrary::FunctionAddress (CONST_STRING_T func_name)
{
  //## begin cSharedLibrary::FunctionAddress%1093328411.body preserve=yes
   if (_Handle == INVALID_LIBRARY_HANDLE) {
      return NULL;
   }
#if defined(_WIN32)
   SHARED_FUNCTION_ADDRESS_T func_address =
      (SHARED_FUNCTION_ADDRESS_T)GetProcAddress(_Handle, func_name);
   return func_address;
#elif defined(__linux__)
PORT_LEVEL_3
   return NULL;
#else
NO_PLATFORM
#endif
  //## end cSharedLibrary::FunctionAddress%1093328411.body
}

LONG_T cSharedLibrary::Error ()
{
  //## begin cSharedLibrary::Error%1093328413.body preserve=yes
   return _NativeError;
  //## end cSharedLibrary::Error%1093328413.body
}

LIBRARY_HANDLE_T cSharedLibrary::Handle ()
{
  //## begin cSharedLibrary::Handle%1093328414.body preserve=yes
   return _Handle;
  //## end cSharedLibrary::Handle%1093328414.body
}

STRING_T cSharedLibrary::LibraryName ()
{
  //## begin cSharedLibrary::LibraryName%1093328415.body preserve=yes
   return _LibraryName;
  //## end cSharedLibrary::LibraryName%1093328415.body
}

cSharedLibrary * cSharedLibrary::Library (CONST_STRING_T name)
{
  //## begin cSharedLibrary::Library%1093328416.body preserve=yes
   SHARED_LIBRARY_MAP_T::const_iterator i = _Libraries.find(name);
   if (i == _Libraries.cend()) {
      cSharedLibrary * library = new cSharedLibrary(name);
      return library;
   } else {
      return (*i).second;
   }
  //## end cSharedLibrary::Library%1093328416.body
}

STRING_T cSharedLibrary::SharedLibraryName (CONST_STRING_T name)
{
  //## begin cSharedLibrary::SharedLibraryName%1093328412.body preserve=yes
   STRING_T library_name;
   library_name = name;
#if defined(_WIN32)
#ifdef _DEBUG
   library_name += "d.dll";
#else
   library_name += ".dll";
#endif
   return library_name;
#elif defined(__linux__)
   library_name = "lib";
   library_name += name;
   library_name += ".so";
#else
NO_PLATFORM
#endif
  //## end cSharedLibrary::SharedLibraryName%1093328412.body
}

// Additional Declarations
  //## begin cSharedLibrary%412ADD260213.declarations preserve=yes
  //## end cSharedLibrary%412ADD260213.declarations

//## begin module%412ADD260213.epilog preserve=yes
//## end module%412ADD260213.epilog
