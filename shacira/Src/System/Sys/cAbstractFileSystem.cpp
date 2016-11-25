//## begin module%440800B203DD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440800B203DD.cm

//## begin module%440800B203DD.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440800B203DD.cp

//## Module: cAbstractFileSystem%440800B203DD; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cAbstractFileSystem.cpp

//## begin module%440800B203DD.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%440800B203DD.additionalIncludes

//## begin module%440800B203DD.includes preserve=yes
//## end module%440800B203DD.includes

// cStandardFileSystem
#include "System/Sys/cStandardFileSystem.h"
// cAbstractFileSystem
#include "System/Sys/cAbstractFileSystem.h"
//## begin module%440800B203DD.additionalDeclarations preserve=yes
//## end module%440800B203DD.additionalDeclarations


// Class cAbstractFileSystem 



cAbstractFileSystem::cAbstractFileSystem()
  //## begin cAbstractFileSystem::cAbstractFileSystem%.hasinit preserve=no
  //## end cAbstractFileSystem::cAbstractFileSystem%.hasinit
  //## begin cAbstractFileSystem::cAbstractFileSystem%.initialization preserve=yes
  //## end cAbstractFileSystem::cAbstractFileSystem%.initialization
{
  //## begin cAbstractFileSystem::cAbstractFileSystem%.body preserve=yes
  //## end cAbstractFileSystem::cAbstractFileSystem%.body
}

cAbstractFileSystem::cAbstractFileSystem(const cAbstractFileSystem &right)
  //## begin cAbstractFileSystem::cAbstractFileSystem%copy.hasinit preserve=no
  //## end cAbstractFileSystem::cAbstractFileSystem%copy.hasinit
  //## begin cAbstractFileSystem::cAbstractFileSystem%copy.initialization preserve=yes
  //## end cAbstractFileSystem::cAbstractFileSystem%copy.initialization
{
  //## begin cAbstractFileSystem::cAbstractFileSystem%copy.body preserve=yes
  //## end cAbstractFileSystem::cAbstractFileSystem%copy.body
}


cAbstractFileSystem::~cAbstractFileSystem()
{
  //## begin cAbstractFileSystem::~cAbstractFileSystem%.body preserve=yes
  //## end cAbstractFileSystem::~cAbstractFileSystem%.body
}



//## Other Operations (implementation)
cAbstractFileSystem * cAbstractFileSystem::Create (ULONG_T type)
{
  //## begin cAbstractFileSystem::Create%1141375548.body preserve=yes
   if (type == FS_STANDARD) {
      return new cStandardFileSystem;
   } else {
      return NULL;
   }
  //## end cAbstractFileSystem::Create%1141375548.body
}

CONST_STRING_T cAbstractFileSystem::ErrorText (int error_code)
{
  //## begin cAbstractFileSystem::ErrorText%1166170818.body preserve=yes
   switch (error_code) {
   case FAILED_TO_CREATE_DIRECTORY: return "cannot create directory";
   case FILE_DOES_NOT_EXIST: return "file does not exist";
   case FAILED_TO_WRITE_FILE: return "cannot write to file";
   case FAILED_TO_RENAME_FILE: return "cannot rename file";
   case FAILED_TO_CREATE_FILE: return "cannot create file";
   case FAILED_TO_REMOVE_FILE: return "cannot remove file";
   }
   return "unknown file error";
  //## end cAbstractFileSystem::ErrorText%1166170818.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cAbstractFileSystem::get_BasePath () const
{
  //## begin cAbstractFileSystem::get_BasePath%440802080302.get preserve=no
  return _BasePath;
  //## end cAbstractFileSystem::get_BasePath%440802080302.get
}

void cAbstractFileSystem::set_BasePath (STRING_T value)
{
  //## begin cAbstractFileSystem::set_BasePath%440802080302.set preserve=no
  _BasePath = value;
  //## end cAbstractFileSystem::set_BasePath%440802080302.set
}

// Additional Declarations
  //## begin cAbstractFileSystem%440800B203DD.declarations preserve=yes
  //## end cAbstractFileSystem%440800B203DD.declarations

//## begin module%440800B203DD.epilog preserve=yes
//## end module%440800B203DD.epilog
