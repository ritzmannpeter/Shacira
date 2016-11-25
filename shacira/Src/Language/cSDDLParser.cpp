//## begin module%3E072E3F00DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E072E3F00DA.cm

//## begin module%3E072E3F00DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E072E3F00DA.cp

//## Module: cSDDLParser%3E072E3F00DA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Language\cSDDLParser.cpp

//## begin module%3E072E3F00DA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E072E3F00DA.additionalIncludes

//## begin module%3E072E3F00DA.includes preserve=yes
//## end module%3E072E3F00DA.includes

// cConvUtils
#include "System/Sys/cConvUtils.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cSDDLParser
#include "Language/cSDDLParser.h"
//## begin module%3E072E3F00DA.additionalDeclarations preserve=yes
//## end module%3E072E3F00DA.additionalDeclarations


// Class cSDDLParser 








//## begin cSDDLParser::Optimized%4134BC0F0251.attr preserve=no  protected: static BOOL_T {U} true
BOOL_T cSDDLParser::_Optimized = true;
//## end cSDDLParser::Optimized%4134BC0F0251.attr






cSDDLParser::cSDDLParser()
  //## begin cSDDLParser::cSDDLParser%.hasinit preserve=no
      : _IgnoreMapping(false), _IgnoreDataDefinitions(false), _IDEActive(false), _Steps(0), _Dynamic(false), _Step(0), _Line(-1), _Column(-1)
  //## end cSDDLParser::cSDDLParser%.hasinit
  //## begin cSDDLParser::cSDDLParser%.initialization preserve=yes
  //## end cSDDLParser::cSDDLParser%.initialization
{
  //## begin cSDDLParser::cSDDLParser%.body preserve=yes
  //## end cSDDLParser::cSDDLParser%.body
}

cSDDLParser::cSDDLParser(const cSDDLParser &right)
  //## begin cSDDLParser::cSDDLParser%copy.hasinit preserve=no
      : _IgnoreMapping(false), _IgnoreDataDefinitions(false), _IDEActive(false), _Steps(0), _Dynamic(false), _Step(0), _Line(-1), _Column(-1)
  //## end cSDDLParser::cSDDLParser%copy.hasinit
  //## begin cSDDLParser::cSDDLParser%copy.initialization preserve=yes
  //## end cSDDLParser::cSDDLParser%copy.initialization
{
  //## begin cSDDLParser::cSDDLParser%copy.body preserve=yes
  //## end cSDDLParser::cSDDLParser%copy.body
}


cSDDLParser::~cSDDLParser()
{
  //## begin cSDDLParser::~cSDDLParser%.body preserve=yes
  //## end cSDDLParser::~cSDDLParser%.body
}



//## Other Operations (implementation)
MAP_ITEM_T * cSDDLParser::NewMapItem (MAP_ITEM_T *base_item)
{
  //## begin cSDDLParser::NewMapItem%1072085856.body preserve=yes
   MAP_ITEM_T * item = (MAP_ITEM_T*)cSystemUtils::Alloc(sizeof(*item));
   if (base_item != NULL) {
      memcpy(item, base_item, sizeof(*item));
   } else {
      item->address = UNUSED_ADDRESS;
      item->bit_pos_b = UNUSED_BITPOS;
      item->bit_pos_e = UNUSED_BITPOS;
      item->enabled = true;
   }
   return item;
  //## end cSDDLParser::NewMapItem%1072085856.body
}

CONST_STRING_T cSDDLParser::CopyName (STRING_T name)
{
  //## begin cSDDLParser::CopyName%1075748781.body preserve=yes
   ULONG_T size = name.size();
   CONST_STRING_T new_name = (CONST_STRING_T)cSystemUtils::Alloc(size+1);
   memcpy((void*)new_name, (void*)name.c_str(), size);
   return new_name;
  //## end cSDDLParser::CopyName%1075748781.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cSDDLParser::get_IgnoreMapping () const
{
  //## begin cSDDLParser::get_IgnoreMapping%3E0C59F701DB.get preserve=no
  return _IgnoreMapping;
  //## end cSDDLParser::get_IgnoreMapping%3E0C59F701DB.get
}

void cSDDLParser::set_IgnoreMapping (BOOL_T value)
{
  //## begin cSDDLParser::set_IgnoreMapping%3E0C59F701DB.set preserve=no
  _IgnoreMapping = value;
  //## end cSDDLParser::set_IgnoreMapping%3E0C59F701DB.set
}

BOOL_T cSDDLParser::get_IgnoreDataDefinitions () const
{
  //## begin cSDDLParser::get_IgnoreDataDefinitions%40EE4F390213.get preserve=no
  return _IgnoreDataDefinitions;
  //## end cSDDLParser::get_IgnoreDataDefinitions%40EE4F390213.get
}

void cSDDLParser::set_IgnoreDataDefinitions (BOOL_T value)
{
  //## begin cSDDLParser::set_IgnoreDataDefinitions%40EE4F390213.set preserve=no
  _IgnoreDataDefinitions = value;
  //## end cSDDLParser::set_IgnoreDataDefinitions%40EE4F390213.set
}

BOOL_T cSDDLParser::get_IDEActive () const
{
  //## begin cSDDLParser::get_IDEActive%420CD01503B9.get preserve=no
  return _IDEActive;
  //## end cSDDLParser::get_IDEActive%420CD01503B9.get
}

void cSDDLParser::set_IDEActive (BOOL_T value)
{
  //## begin cSDDLParser::set_IDEActive%420CD01503B9.set preserve=no
  _IDEActive = value;
  //## end cSDDLParser::set_IDEActive%420CD01503B9.set
}

int cSDDLParser::get_Steps () const
{
  //## begin cSDDLParser::get_Steps%434D2D220027.get preserve=no
  return _Steps;
  //## end cSDDLParser::get_Steps%434D2D220027.get
}

void cSDDLParser::set_Steps (int value)
{
  //## begin cSDDLParser::set_Steps%434D2D220027.set preserve=no
  _Steps = value;
  //## end cSDDLParser::set_Steps%434D2D220027.set
}

STRING_T cSDDLParser::get_File () const
{
  //## begin cSDDLParser::get_File%43A7EF0D02E0.get preserve=no
  return _File;
  //## end cSDDLParser::get_File%43A7EF0D02E0.get
}

int cSDDLParser::get_Line () const
{
  //## begin cSDDLParser::get_Line%43A7EF0D02E1.get preserve=no
  return _Line;
  //## end cSDDLParser::get_Line%43A7EF0D02E1.get
}

int cSDDLParser::get_Column () const
{
  //## begin cSDDLParser::get_Column%43A7EF0D02EF.get preserve=no
  return _Column;
  //## end cSDDLParser::get_Column%43A7EF0D02EF.get
}

STRING_T cSDDLParser::get_ErrorText () const
{
  //## begin cSDDLParser::get_ErrorText%43A7EF0D02F0.get preserve=no
  return _ErrorText;
  //## end cSDDLParser::get_ErrorText%43A7EF0D02F0.get
}

// Additional Declarations
  //## begin cSDDLParser%3E072E3F00DA.declarations preserve=yes
  //## end cSDDLParser%3E072E3F00DA.declarations

//## begin module%3E072E3F00DA.epilog preserve=yes
//## end module%3E072E3F00DA.epilog
