//## begin module%412B31000119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412B31000119.cm

//## begin module%412B31000119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412B31000119.cp

//## Module: cTextTable%412B31000119; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Text\cTextTable.cpp

//## begin module%412B31000119.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%412B31000119.additionalIncludes

//## begin module%412B31000119.includes preserve=yes
//## end module%412B31000119.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cTextTable
#include "System/Text/cTextTable.h"
//## begin module%412B31000119.additionalDeclarations preserve=yes
//## end module%412B31000119.additionalDeclarations


// Class cTextTable 






cTextTable::cTextTable()
  //## begin cTextTable::cTextTable%.hasinit preserve=no
      : _Min(0xffffffff), _Max(0), _Size(0), _StringTable(NULL)
  //## end cTextTable::cTextTable%.hasinit
  //## begin cTextTable::cTextTable%.initialization preserve=yes
  //## end cTextTable::cTextTable%.initialization
{
  //## begin cTextTable::cTextTable%.body preserve=yes
_ASSERT_UNCOND
  //## end cTextTable::cTextTable%.body
}

cTextTable::cTextTable(const cTextTable &right)
  //## begin cTextTable::cTextTable%copy.hasinit preserve=no
      : _Min(0xffffffff), _Max(0), _Size(0), _StringTable(NULL)
  //## end cTextTable::cTextTable%copy.hasinit
  //## begin cTextTable::cTextTable%copy.initialization preserve=yes
  //## end cTextTable::cTextTable%copy.initialization
{
  //## begin cTextTable::cTextTable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTextTable::cTextTable%copy.body
}

cTextTable::cTextTable (TEXT_ENTRY_T *table)
  //## begin cTextTable::cTextTable%1093344846.hasinit preserve=no
      : _Min(0xffffffff), _Max(0), _Size(0), _StringTable(NULL)
  //## end cTextTable::cTextTable%1093344846.hasinit
  //## begin cTextTable::cTextTable%1093344846.initialization preserve=yes
  //## end cTextTable::cTextTable%1093344846.initialization
{
  //## begin cTextTable::cTextTable%1093344846.body preserve=yes
   LoadTable(table);
  //## end cTextTable::cTextTable%1093344846.body
}


cTextTable::~cTextTable()
{
  //## begin cTextTable::~cTextTable%.body preserve=yes
   if (_StringTable != NULL) {
      cSystemUtils::Free(_StringTable);
   }
  //## end cTextTable::~cTextTable%.body
}



//## Other Operations (implementation)
CONST_STRING_T cTextTable::GetText (ULONG_T text_id)
{
  //## begin cTextTable::GetText%1093344844.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   int index = (text_id - _Min);
   if (index >= 0 && index < (int)_Size) {
      if (_StringTable[index] != NULL) {
         return _StringTable[index];
      }
   } 
   static char msg[0x100] = {0};
   SafePrintf(msg, sizeof(msg), "cannot find appropriate text, id is %d", text_id);
   return msg;
  //## end cTextTable::GetText%1093344844.body
}

void cTextTable::LoadTable (TEXT_ENTRY_T *table)
{
  //## begin cTextTable::LoadTable%1093344847.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   TEXT_ENTRY_T * text_ptr = table;
   _Min = 0xffffffff;
   _Max = 0;
   ULONG_T tab_size = 0;
   ULONG_T id = text_ptr->text_id;
   while (text_ptr->text_id != 0 &&
          text_ptr->text != NULL) {
      if (id < _Min) _Min = id;
      if (id > _Max) _Max = id;
      text_ptr++;
      id = text_ptr->text_id;
      tab_size++;
   }
   _Size = (_Max - _Min) + 1;
   if (_Size > 0) {
      _StringTable = (CONST_STRING_T *)cSystemUtils::Alloc(_Size * sizeof(CONST_STRING_T));
      ULONG_T i = 0;
      for (i=0; i<tab_size; i++) {
         LONG_T index = table[i].text_id - _Min;
         if (index >= 0 && index < (LONG_T)_Size) {
            _StringTable[index] = table[i].text;
         } else {
            int dummy = 0;
         }
      }
   }
  //## end cTextTable::LoadTable%1093344847.body
}

// Additional Declarations
  //## begin cTextTable%412B31000119.declarations preserve=yes
  //## end cTextTable%412B31000119.declarations

//## begin module%412B31000119.epilog preserve=yes
//## end module%412B31000119.epilog
