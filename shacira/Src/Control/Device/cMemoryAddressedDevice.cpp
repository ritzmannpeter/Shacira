//## begin module%401E8259037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%401E8259037A.cm

//## begin module%401E8259037A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%401E8259037A.cp

//## Module: cMemoryAddressedDevice%401E8259037A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cMemoryAddressedDevice.cpp

//## begin module%401E8259037A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%401E8259037A.additionalIncludes

//## begin module%401E8259037A.includes preserve=yes

/// PR 29.04.09 - added checking of memory ranges

//## end module%401E8259037A.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cBlockCache
#include "Control/Device/cBlockCache.h"
// cCache
#include "Control/Device/cCache.h"
// cMemoryAddressedDevice
#include "Control/Device/cMemoryAddressedDevice.h"
//## begin module%401E8259037A.additionalDeclarations preserve=yes

#define SEGMENT_SIZE 0x20000

//## end module%401E8259037A.additionalDeclarations


// Class cMemoryAddressedDevice 








cMemoryAddressedDevice::cMemoryAddressedDevice()
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%.hasinit preserve=no
      : _Node(2), _SegmentSize(SEGMENT_SIZE), _ElementSize(1)
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%.hasinit
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%.initialization preserve=yes
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%.initialization
{
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%.body
}

cMemoryAddressedDevice::cMemoryAddressedDevice(const cMemoryAddressedDevice &right)
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%copy.hasinit preserve=no
      : _Node(2), _SegmentSize(SEGMENT_SIZE), _ElementSize(1)
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%copy.hasinit
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%copy.initialization preserve=yes
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%copy.initialization
{
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%copy.body
}

cMemoryAddressedDevice::cMemoryAddressedDevice (cConfigurationObject *config_obj, cCell *cell, ULONG_T element_size)
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.hasinit preserve=no
      : _Node(2), _SegmentSize(SEGMENT_SIZE), _ElementSize(1)
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.hasinit
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.initialization
{
  //## begin cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.body preserve=yes
   _ElementSize = element_size;
   _Node = config_obj->PropertyValue("Node", _Node);
  //## end cMemoryAddressedDevice::cMemoryAddressedDevice%1075741650.body
}


cMemoryAddressedDevice::~cMemoryAddressedDevice()
{
  //## begin cMemoryAddressedDevice::~cMemoryAddressedDevice%.body preserve=yes
  //## end cMemoryAddressedDevice::~cMemoryAddressedDevice%.body
}



//## Other Operations (implementation)
void cMemoryAddressedDevice::Start ()
{
  //## begin cMemoryAddressedDevice::Start%1075741651.body preserve=yes
  //## end cMemoryAddressedDevice::Start%1075741651.body
}

void cMemoryAddressedDevice::Stop ()
{
  //## begin cMemoryAddressedDevice::Stop%1075741652.body preserve=yes
  //## end cMemoryAddressedDevice::Stop%1075741652.body
}

void cMemoryAddressedDevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size)
{
  //## begin cMemoryAddressedDevice::Cache%1075741653.body preserve=yes
  //## end cMemoryAddressedDevice::Cache%1075741653.body
}

void cMemoryAddressedDevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
  //## begin cMemoryAddressedDevice::Buffer%1075741654.body preserve=yes
  //## end cMemoryAddressedDevice::Buffer%1075741654.body
}

void cMemoryAddressedDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cMemoryAddressedDevice::Read%1075741655.body preserve=yes
   cSharedMem * segment = Segment(_Node, buf_spec);
   void * data_address = (UCHAR_T*)segment->getAdr();
   void * source_buf = (UCHAR_T*)segment->getAdr() + (address * _ElementSize);
   if (address + len > _SegmentSize) {
      ErrorPrintf("invalid shared memory access on segment %s address %08.08x len %d\n",
                  buf_spec, address, len);
      return;
   }
   if (source_buf < data_address) {
      ErrorPrintf("invalid shared memory access on segment %s address %08.08x len %d\n",
                  buf_spec, address, len);
      return;
   }
   memcpy(buf, source_buf, _MIN_(len,buf_size));
  //## end cMemoryAddressedDevice::Read%1075741655.body
}

void cMemoryAddressedDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cMemoryAddressedDevice::Write%1075741656.body preserve=yes
   cSharedMem * segment = Segment(_Node, buf_spec);
   void * data_address = (UCHAR_T*)segment->getAdr();
   void * target_buf = (UCHAR_T*)segment->getAdr() + (address * _ElementSize);
   if (address + len > _SegmentSize) {
      ErrorPrintf("invalid shared memory access on segment %s address %08.08x len %d\n",
                  buf_spec, address, len);
      return;
   }
   if (target_buf < data_address) {
      ErrorPrintf("invalid shared memory access on segment %s address %08.08x len %d\n",
                  buf_spec, address, len);
      return;
   }
   memcpy(target_buf, buf, len);
  //## end cMemoryAddressedDevice::Write%1075741656.body
}

cSharedMem * cMemoryAddressedDevice::Segment (ULONG_T address, CONST_STRING_T name)
{
  //## begin cMemoryAddressedDevice::Segment%1076580851.body preserve=yes
   STRING_T segment_name = SegmentName(address, name);
   SEGMENT_MAP_T::const_iterator i = _Segments.find(segment_name.c_str());
   if (i == _Segments.end()) {
      cSharedMem * segment = CreateSegment(segment_name.c_str());
      return segment;
   } else {
      return (*i).second;
   }
  //## end cMemoryAddressedDevice::Segment%1076580851.body
}

STRING_T cMemoryAddressedDevice::SegmentName (ULONG_T address, CONST_STRING_T name)
{
  //## begin cMemoryAddressedDevice::SegmentName%1076580853.body preserve=yes
   char segment_name[128] = {0};
   SafePrintf(segment_name, sizeof(segment_name), "dev%d_%s", address, name);
   return segment_name;
  //## end cMemoryAddressedDevice::SegmentName%1076580853.body
}

cSharedMem * cMemoryAddressedDevice::CreateSegment (CONST_STRING_T segment_name)
{
  //## begin cMemoryAddressedDevice::CreateSegment%1076580852.body preserve=yes
   cSharedMem * segment = new cSharedMem(segment_name, cSharedMem::memOpenOrCreate, _SegmentSize);
   if (segment != NULL) {
      _Segments[segment_name] = segment;
      return segment;
   }
   throw cError(-22, 0, segment_name);
  //## end cMemoryAddressedDevice::CreateSegment%1076580852.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cMemoryAddressedDevice::get_Node () const
{
  //## begin cMemoryAddressedDevice::get_Node%401E82F200EA.get preserve=no
  return _Node;
  //## end cMemoryAddressedDevice::get_Node%401E82F200EA.get
}

void cMemoryAddressedDevice::set_Node (ULONG_T value)
{
  //## begin cMemoryAddressedDevice::set_Node%401E82F200EA.set preserve=no
  _Node = value;
  //## end cMemoryAddressedDevice::set_Node%401E82F200EA.set
}

ULONG_T cMemoryAddressedDevice::get_SegmentSize () const
{
  //## begin cMemoryAddressedDevice::get_SegmentSize%402B5AD10213.get preserve=no
  return _SegmentSize;
  //## end cMemoryAddressedDevice::get_SegmentSize%402B5AD10213.get
}

void cMemoryAddressedDevice::set_SegmentSize (ULONG_T value)
{
  //## begin cMemoryAddressedDevice::set_SegmentSize%402B5AD10213.set preserve=no
  _SegmentSize = value;
  //## end cMemoryAddressedDevice::set_SegmentSize%402B5AD10213.set
}

ULONG_T cMemoryAddressedDevice::get_ElementSize () const
{
  //## begin cMemoryAddressedDevice::get_ElementSize%4061309C032C.get preserve=no
  return _ElementSize;
  //## end cMemoryAddressedDevice::get_ElementSize%4061309C032C.get
}

void cMemoryAddressedDevice::set_ElementSize (ULONG_T value)
{
  //## begin cMemoryAddressedDevice::set_ElementSize%4061309C032C.set preserve=no
  _ElementSize = value;
  //## end cMemoryAddressedDevice::set_ElementSize%4061309C032C.set
}

// Additional Declarations
  //## begin cMemoryAddressedDevice%401E8259037A.declarations preserve=yes
  //## end cMemoryAddressedDevice%401E8259037A.declarations

//## begin module%401E8259037A.epilog preserve=yes
//## end module%401E8259037A.epilog
