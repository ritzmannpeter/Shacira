//## begin module%412B30D300FA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412B30D300FA.cm

//## begin module%412B30D300FA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412B30D300FA.cp

//## Module: cText%412B30D300FA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Text\cText.cpp

//## begin module%412B30D300FA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%412B30D300FA.additionalIncludes

//## begin module%412B30D300FA.includes preserve=yes
//## end module%412B30D300FA.includes

// cStringUtils
#include "System/cStringUtils.h"
// cError
#include "System/cError.h"
// cSharedLibrary
#include "System/Sys/cSharedLibrary.h"
// cText
#include "System/Text/cText.h"
// cTextTable
#include "System/Text/cTextTable.h"
//## begin module%412B30D300FA.additionalDeclarations preserve=yes

/// PR 30.03.05 made text table position indifferent
/// PR 15.06.05 introduced english system texts

//## end module%412B30D300FA.additionalDeclarations


// Class cText 

//## begin cText::SystemLanguage%42B025010399.attr preserve=no  public: static STRING_T {U} "de"
STRING_T cText::_SystemLanguage = "de";
//## end cText::SystemLanguage%42B025010399.attr

//## begin cText::TextTable%412B316002BF.attr preserve=no  private: static cTextTable * {U} NULL
cTextTable *cText::_TextTable = NULL;
//## end cText::TextTable%412B316002BF.attr

//## begin cText::GetCustomTextFuncAddress%412B39C6037A.attr preserve=no  private: static GET_CUSTOM_TEXT_FUNC_T {U} NULL
GET_CUSTOM_TEXT_FUNC_T cText::_GetCustomTextFuncAddress = NULL;
//## end cText::GetCustomTextFuncAddress%412B39C6037A.attr

cText::cText()
  //## begin cText::cText%.hasinit preserve=no
  //## end cText::cText%.hasinit
  //## begin cText::cText%.initialization preserve=yes
  //## end cText::cText%.initialization
{
  //## begin cText::cText%.body preserve=yes
  //## end cText::cText%.body
}

cText::cText(const cText &right)
  //## begin cText::cText%copy.hasinit preserve=no
  //## end cText::cText%copy.hasinit
  //## begin cText::cText%copy.initialization preserve=yes
  //## end cText::cText%copy.initialization
{
  //## begin cText::cText%copy.body preserve=yes
  //## end cText::cText%copy.body
}


cText::~cText()
{
  //## begin cText::~cText%.body preserve=yes
  //## end cText::~cText%.body
}



//## Other Operations (implementation)
CONST_STRING_T cText::GetText (ULONG_T text_id)
{
  //## begin cText::GetText%1093344845.body preserve=yes
   if (text_id >= START_CUSTOM_TEXT) {
      if (_GetCustomTextFuncAddress == NULL) {
         _GetCustomTextFuncAddress = cCustomFunctions::GetCustomTextFuncAddress();
      }
      if (_GetCustomTextFuncAddress != NULL) {
         return _GetCustomTextFuncAddress(text_id);
      } else {
         return "?";
      }
   } else {
      if (_TextTable == NULL) {
         if (_SystemLanguage == "en") {
            _TextTable = new cTextTable((TEXT_ENTRY_T*)_SystemTextEn);
         } else {
            _TextTable = new cTextTable((TEXT_ENTRY_T*)_SystemText);
         }
      }
      return _TextTable->GetText(text_id);
   }
  //## end cText::GetText%1093344845.body
}

STRING_T cText::GetText (ULONG_T text_id, CONST_STRING_T text)
{
  //## begin cText::GetText%1096541411.body preserve=yes
   if (text_id == 0) {
      if (text == NULL || strlen(text) == 0) {
         return "";
      } else {
         return text;
      }
   }
   return GetText(text_id);
  //## end cText::GetText%1096541411.body
}

STRING_T cText::GetText (cError &error)
{
  //## begin cText::GetText%1111566665.body preserve=yes
   STRING_T msg;
   if (error.get_ErrCode() == 0) {
      msg = error.get_Text();
   } else {
      msg = cText::GetText(-(error.get_ErrCode()));
   }
   return msg;
  //## end cText::GetText%1111566665.body
}

CONST_STRING_T cText::Context (ULONG_T text_id)
{
  //## begin cText::Context%1093424351.body preserve=yes
   if (text_id == 0 || text_id >= START_CUSTOM_TEXT) {
      return "custom";
   } else {
      return "system";
   }
  //## end cText::Context%1093424351.body
}

// Additional Declarations
  //## begin cText%412B30D300FA.declarations preserve=yes
  //## end cText%412B30D300FA.declarations

//## begin module%412B30D300FA.epilog preserve=yes
//## end module%412B30D300FA.epilog
