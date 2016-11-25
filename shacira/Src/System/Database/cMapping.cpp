//## begin module%3E00548802D6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00548802D6.cm

//## begin module%3E00548802D6.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00548802D6.cp

//## Module: cMapping%3E00548802D6; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cMapping.cpp

//## begin module%3E00548802D6.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E00548802D6.additionalIncludes

//## begin module%3E00548802D6.includes preserve=yes
//## end module%3E00548802D6.includes

// cMapping
#include "System/Database/cMapping.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cDevice
#include "Control/Device/cDevice.h"
//## begin module%3E00548802D6.additionalDeclarations preserve=yes
//## end module%3E00548802D6.additionalDeclarations


// Class cMapping 









cMapping::cMapping()
  //## begin cMapping::cMapping%.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _ItemCount(1), _MapItems(NULL), _ConvFunc(NULL)
  //## end cMapping::cMapping%.hasinit
  //## begin cMapping::cMapping%.initialization preserve=yes
  //## end cMapping::cMapping%.initialization
{
  //## begin cMapping::cMapping%.body preserve=yes
   _MapItems = (MAP_ITEM_T**)cSystemUtils::Alloc(_ItemCount * sizeof(MAP_ITEM_T*));
  //## end cMapping::cMapping%.body
}

cMapping::cMapping(const cMapping &right)
  //## begin cMapping::cMapping%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _ItemCount(1), _MapItems(NULL), _ConvFunc(NULL)
  //## end cMapping::cMapping%copy.hasinit
  //## begin cMapping::cMapping%copy.initialization preserve=yes
  //## end cMapping::cMapping%copy.initialization
{
  //## begin cMapping::cMapping%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cMapping::cMapping%copy.body
}

cMapping::cMapping (ULONG_T item_count)
  //## begin cMapping::cMapping%1071222102.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _ItemCount(1), _MapItems(NULL), _ConvFunc(NULL)
  //## end cMapping::cMapping%1071222102.hasinit
  //## begin cMapping::cMapping%1071222102.initialization preserve=yes
  //## end cMapping::cMapping%1071222102.initialization
{
  //## begin cMapping::cMapping%1071222102.body preserve=yes
   _ItemCount = item_count;
   _MapItems = (MAP_ITEM_T**)cSystemUtils::Alloc(_ItemCount * sizeof(MAP_ITEM_T*));
  //## end cMapping::cMapping%1071222102.body
}


cMapping::~cMapping()
{
  //## begin cMapping::~cMapping%.body preserve=yes
   unsigned long i = 0;
   for (i=0; i<_ItemCount; i++) {
      cSystemUtils::Free(_MapItems[i]);
   }
   cSystemUtils::Free(_MapItems);
   DELETE_OBJECT(cFuncRef, _ConvFunc)
  //## end cMapping::~cMapping%.body
}



//## Other Operations (implementation)
void cMapping::SetConvFunc (cFuncRef *conv_func)
{
  //## begin cMapping::SetConvFunc%1041236870.body preserve=yes
   _ConvFunc = conv_func;
  //## end cMapping::SetConvFunc%1041236870.body
}

void cMapping::SetItem (ULONG_T pos, MAP_ITEM_T *item)
{
  //## begin cMapping::SetItem%1071222103.body preserve=yes
   if (pos >= _ItemCount) throw cError(MAPPING_INVALID_MAPITEM_POS, 0,
                                       cConvUtils::StringValue(pos).c_str(),
                                       cConvUtils::StringValue(_ItemCount).c_str());
   item->pos = pos;
   _MapItems[pos] = item;
  //## end cMapping::SetItem%1071222103.body
}

MAP_ITEM_T * cMapping::MapItem (ULONG_T pos)
{
  //## begin cMapping::MapItem%1042459999.body preserve=yes
   if (pos >= _ItemCount) throw cError(MAPPING_INVALID_MAPITEM_POS, 0,
                                       cConvUtils::StringValue(pos).c_str(),
                                       cConvUtils::StringValue(_ItemCount).c_str());
   return _MapItems[pos];
  //## end cMapping::MapItem%1042459999.body
}

// Additional Declarations
  //## begin cMapping%3E00548802D6.declarations preserve=yes
  //## end cMapping%3E00548802D6.declarations

//## begin module%3E00548802D6.epilog preserve=yes
//## end module%3E00548802D6.epilog
