//## begin module%411DF3E3036B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411DF3E3036B.cm

//## begin module%411DF3E3036B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%411DF3E3036B.cp

//## Module: cDataset%411DF3E3036B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cDataset.cpp

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
// cDatasetDirectory
#include "System/Structs/cDatasetDirectory.h"
// cDataset
#include "System/Structs/cDataset.h"
// cStyxParser
#include "Language/cStyxParser.h"
//## begin module%411DF3E3036B.additionalDeclarations preserve=yes
//## end module%411DF3E3036B.additionalDeclarations


// Class cDataset 




cDataset::cDataset()
  //## begin cDataset::cDataset%.hasinit preserve=no
      : _Directory(NULL), _Context(NULL)
  //## end cDataset::cDataset%.hasinit
  //## begin cDataset::cDataset%.initialization preserve=yes
  //## end cDataset::cDataset%.initialization
{
  //## begin cDataset::cDataset%.body preserve=yes
_ASSERT_UNCOND
  //## end cDataset::cDataset%.body
}

cDataset::cDataset(const cDataset &right)
  //## begin cDataset::cDataset%copy.hasinit preserve=no
      : _Directory(NULL), _Context(NULL)
  //## end cDataset::cDataset%copy.hasinit
  //## begin cDataset::cDataset%copy.initialization preserve=yes
  //## end cDataset::cDataset%copy.initialization
{
  //## begin cDataset::cDataset%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDataset::cDataset%copy.body
}

cDataset::cDataset (CONST_STRING_T source, BOOL_T file_name)
  //## begin cDataset::cDataset%1092480803.hasinit preserve=no
      : _Directory(NULL), _Context(NULL)
  //## end cDataset::cDataset%1092480803.hasinit
  //## begin cDataset::cDataset%1092480803.initialization preserve=yes
  //## end cDataset::cDataset%1092480803.initialization
{
  //## begin cDataset::cDataset%1092480803.body preserve=yes
   if (file_name) {
      cSHFile file(source);
      if (file.Exists()) {
         _Buf = file.ToString();
      }
   } else {
      _Buf = source;
   }
  //## end cDataset::cDataset%1092480803.body
}


cDataset::~cDataset()
{
  //## begin cDataset::~cDataset%.body preserve=yes
   DELETE_OBJECT(cContext, _Context)
  //## end cDataset::~cDataset%.body
}



//## Other Operations (implementation)
BOOL_T cDataset::Load ()
{
  //## begin cDataset::Load%1092480804.body preserve=yes
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
  //## end cDataset::Load%1092480804.body
}

BOOL_T cDataset::IsValid ()
{
  //## begin cDataset::IsValid%1092480805.body preserve=yes
   return (_Context != NULL);
  //## end cDataset::IsValid%1092480805.body
}

cContext * cDataset::GetContext ()
{
  //## begin cDataset::GetContext%1092480806.body preserve=yes
   return _Context;
  //## end cDataset::GetContext%1092480806.body
}

// Additional Declarations
  //## begin cDataset%411DF3E3036B.declarations preserve=yes
  //## end cDataset%411DF3E3036B.declarations

//## begin module%411DF3E3036B.epilog preserve=yes
//## end module%411DF3E3036B.epilog
