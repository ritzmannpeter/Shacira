//## begin module%401E8259037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%401E8259037A.cm

//## begin module%401E8259037A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%401E8259037A.cp

//## Module: cMemoryAddressedDevice%401E8259037A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cMemoryAddressedDevice.h

#ifndef cMemoryAddressedDevice_h
#define cMemoryAddressedDevice_h 1

//## begin module%401E8259037A.includes preserve=yes
//## end module%401E8259037A.includes

// eb_shmem
#include "base/eb_shmem.hpp"
// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cBlockCache;
class __DLL_EXPORT__ cCache;

//## begin module%401E8259037A.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cSharedMem*> SEGMENT_MAP_T;

//## end module%401E8259037A.additionalDeclarations


//## begin cMemoryAddressedDevice%401E8259037A.preface preserve=yes
//## end cMemoryAddressedDevice%401E8259037A.preface

//## Class: cMemoryAddressedDevice%401E8259037A
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%401E863C01B5;cFileSystemUtils { -> F}
//## Uses: <unnamed>%401E8844031C;cCacheControl { -> F}
//## Uses: <unnamed>%401E88650242;cCache { -> F}
//## Uses: <unnamed>%401E88AE000F;cBlockCache { -> F}
//## Uses: <unnamed>%402B51DD0119;cSharedMem { -> }

class __DLL_EXPORT__ cMemoryAddressedDevice : public cDevice  //## Inherits: <unnamed>%401E829703B9
{
  //## begin cMemoryAddressedDevice%401E8259037A.initialDeclarations preserve=yes
public:
  //## end cMemoryAddressedDevice%401E8259037A.initialDeclarations

    //## Constructors (generated)
      cMemoryAddressedDevice();

      cMemoryAddressedDevice(const cMemoryAddressedDevice &right);

    //## Constructors (specified)
      //## Operation: cMemoryAddressedDevice%1075741650
      cMemoryAddressedDevice (cConfigurationObject *config_obj, cCell *cell, ULONG_T element_size = 1);

    //## Destructor (generated)
      virtual ~cMemoryAddressedDevice();


    //## Other Operations (specified)
      //## Operation: Start%1075741651
      virtual void Start ();

      //## Operation: Stop%1075741652
      virtual void Stop ();

      //## Operation: Cache%1075741653
      virtual void Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size);

      //## Operation: Buffer%1075741654
      virtual void Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements = 1);

      //## Operation: Read%1075741655
      virtual void Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Write%1075741656
      virtual void Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Node%401E82F200EA
      ULONG_T get_Node () const;
      void set_Node (ULONG_T value);

      //## Attribute: SegmentSize%402B5AD10213
      ULONG_T get_SegmentSize () const;
      void set_SegmentSize (ULONG_T value);

      //## Attribute: ElementSize%4061309C032C
      ULONG_T get_ElementSize () const;
      void set_ElementSize (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cMemoryAddressedDevice%401E8259037A.public preserve=yes
      //## end cMemoryAddressedDevice%401E8259037A.public

  protected:
    // Data Members for Class Attributes

      //## begin cMemoryAddressedDevice::Node%401E82F200EA.attr preserve=no  public: ULONG_T {U} 2
      ULONG_T _Node;
      //## end cMemoryAddressedDevice::Node%401E82F200EA.attr

      //## begin cMemoryAddressedDevice::SegmentSize%402B5AD10213.attr preserve=no  public: ULONG_T {U} 0x2000
      ULONG_T _SegmentSize;
      //## end cMemoryAddressedDevice::SegmentSize%402B5AD10213.attr

      //## begin cMemoryAddressedDevice::ElementSize%4061309C032C.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _ElementSize;
      //## end cMemoryAddressedDevice::ElementSize%4061309C032C.attr

    // Additional Protected Declarations
      //## begin cMemoryAddressedDevice%401E8259037A.protected preserve=yes
      //## end cMemoryAddressedDevice%401E8259037A.protected

  private:
    // Additional Private Declarations
      //## begin cMemoryAddressedDevice%401E8259037A.private preserve=yes
      //## end cMemoryAddressedDevice%401E8259037A.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Segment%1076580851
      cSharedMem * Segment (ULONG_T address, CONST_STRING_T name);

      //## Operation: SegmentName%1076580853
      STRING_T SegmentName (ULONG_T address, CONST_STRING_T name);

      //## Operation: CreateSegment%1076580852
      cSharedMem * CreateSegment (CONST_STRING_T segment_name);

    // Data Members for Class Attributes

      //## Attribute: Segments%402B55550232
      //## begin cMemoryAddressedDevice::Segments%402B55550232.attr preserve=no  implementation: SEGMENT_MAP_T {U} 
      SEGMENT_MAP_T _Segments;
      //## end cMemoryAddressedDevice::Segments%402B55550232.attr

    // Additional Implementation Declarations
      //## begin cMemoryAddressedDevice%401E8259037A.implementation preserve=yes
      //## end cMemoryAddressedDevice%401E8259037A.implementation

};

//## begin cMemoryAddressedDevice%401E8259037A.postscript preserve=yes
//## end cMemoryAddressedDevice%401E8259037A.postscript

// Class cMemoryAddressedDevice 

//## begin module%401E8259037A.epilog preserve=yes
//## end module%401E8259037A.epilog


#endif
