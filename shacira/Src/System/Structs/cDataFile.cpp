//## begin module%411DF3E3036B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411DF3E3036B.cm

//## begin module%411DF3E3036B.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%411DF3E3036B.cp

//## Module: cDataFile%411DF3E3036B; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\System\Structs\cDataFile.cpp

//## begin module%411DF3E3036B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%411DF3E3036B.additionalIncludes

//## begin module%411DF3E3036B.includes preserve=yes
//## end module%411DF3E3036B.includes

// cContext
#include "System/Database/cContext.h"
// cFileContext
#include "System/Database/cFileContext.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cStyxParser
#include "Language/cStyxParser.h"
// cDataFile
#include "System/Structs/cDataFile.h"
//## begin module%411DF3E3036B.additionalDeclarations preserve=yes
//## end module%411DF3E3036B.additionalDeclarations


// Class cDataFile 



cDataFile::cDataFile()
  //## begin cDataFile::cDataFile%.hasinit preserve=no
      : _Context(NULL)
  //## end cDataFile::cDataFile%.hasinit
  //## begin cDataFile::cDataFile%.initialization preserve=yes
  //## end cDataFile::cDataFile%.initialization
{
  //## begin cDataFile::cDataFile%.body preserve=yes
_ASSERT_UNCOND
  //## end cDataFile::cDataFile%.body
}

cDataFile::cDataFile(const cDataFile &right)
  //## begin cDataFile::cDataFile%copy.hasinit preserve=no
      : _Context(NULL)
  //## end cDataFile::cDataFile%copy.hasinit
  //## begin cDataFile::cDataFile%copy.initialization preserve=yes
  //## end cDataFile::cDataFile%copy.initialization
{
  //## begin cDataFile::cDataFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDataFile::cDataFile%copy.body
}

cDataFile::cDataFile (CONST_STRING_T source, BOOL_T file_name)
  //## begin cDataFile::cDataFile%1092480803.hasinit preserve=no
      : _Context(NULL)
  //## end cDataFile::cDataFile%1092480803.hasinit
  //## begin cDataFile::cDataFile%1092480803.initialization preserve=yes
  //## end cDataFile::cDataFile%1092480803.initialization
{
  //## begin cDataFile::cDataFile%1092480803.body preserve=yes
   if (file_name) {
      cSHFile file(source);
      if (file.Exists()) {
         _Buf = file.ToString();
      }
   } else {
      _Buf = source;
   }
  //## end cDataFile::cDataFile%1092480803.body
}


cDataFile::~cDataFile()
{
  //## begin cDataFile::~cDataFile%.body preserve=yes
   DELETE_OBJECT(cContext, _Context)
  //## end cDataFile::~cDataFile%.body
}



//## Other Operations (implementation)
BOOL_T cDataFile::Load ()
{
  //## begin cDataFile::Load%1092480804.body preserve=yes
   if (_Context == NULL) {
      _Context = new cFileContext;
   }
//   try {
      cStyxParser parser;
      parser.ParseDatabaseFromString(_Context, _Buf.c_str());
      _Context->Create();
      return true;
#ifdef lassma
   } catch (cError & e) {
      return false;
   } catch (...) {
      return false;
   }
#endif
   //## end cDataFile::Load%1092480804.body
}

BOOL_T cDataFile::IsValid ()
{
  //## begin cDataFile::IsValid%1092480805.body preserve=yes
   return (_Context != NULL);
  //## end cDataFile::IsValid%1092480805.body
}

cContext * cDataFile::GetContext ()
{
  //## begin cDataFile::GetContext%1092480806.body preserve=yes
   return _Context;
  //## end cDataFile::GetContext%1092480806.body
}

// Additional Declarations
  //## begin cDataFile%411DF3E3036B.declarations preserve=yes
  //## end cDataFile%411DF3E3036B.declarations

//## begin module%411DF3E3036B.epilog preserve=yes
//## end module%411DF3E3036B.epilog
