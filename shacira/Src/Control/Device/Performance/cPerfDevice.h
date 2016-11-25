//## begin module%428C87EE01F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%428C87EE01F4.cm

//## begin module%428C87EE01F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%428C87EE01F4.cp

//## Module: cPerfDevice%428C87EE01F4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\Performance\cPerfDevice.h

#ifndef cPerfDevice_h
#define cPerfDevice_h 1

//## begin module%428C87EE01F4.includes preserve=yes

#include "Control/Device/Performance/cPerformance.h"

//## end module%428C87EE01F4.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cChannel;

//## begin module%428C87EE01F4.additionalDeclarations preserve=yes

typedef struct _perf_data
{
   ULONG_T blocks_allocated;
   ULONG_T transient_objects;
   DOUBLE_T cpu_time;
   ULONG_T cpu_utilization;
   ULONG_T memory;
   ULONG_T virtual_memory;
   ULONG_T threads;
   ULONG_T user_objects;
   ULONG_T gdi_objects;
}  PERF_DATA_T;

#define CHANNEL_ARRAY_SIZE    100
typedef cChannel * CHANNEL_ARRAY_T[CHANNEL_ARRAY_SIZE];

//## end module%428C87EE01F4.additionalDeclarations


//## begin cPerfDevice%428C87EE01F4.preface preserve=yes
//## end cPerfDevice%428C87EE01F4.preface

//## Class: cPerfDevice%428C87EE01F4
//## Category: Control::Device::Performance%428C891100DA
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43022339006D;cChannel { -> F}

class __DLL_EXPORT__ cPerfDevice : public cDevice  //## Inherits: <unnamed>%428C881A01A5
{
  //## begin cPerfDevice%428C87EE01F4.initialDeclarations preserve=yes
public:
  //## end cPerfDevice%428C87EE01F4.initialDeclarations

    //## Constructors (generated)
      cPerfDevice();

      cPerfDevice(const cPerfDevice &right);

    //## Constructors (specified)
      //## Operation: cPerfDevice%1116506566
      cPerfDevice (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cPerfDevice();


    //## Other Operations (specified)
      //## Operation: Start%1116506567
      virtual void Start ();

      //## Operation: Stop%1116506568
      virtual void Stop ();

      //## Operation: Cache%1116506569
      virtual void Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size);

      //## Operation: Buffer%1116506570
      virtual void Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements = 1);

      //## Operation: Get%1116506572
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags = 0);

      //## Operation: Get%1116506573
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1116506574
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1116506575
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags = 0);

      //## Operation: Get%1116507645
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags = 0);

      //## Operation: Set%1116506576
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags = 0);

      //## Operation: Set%1116506577
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags = 0);

      //## Operation: Set%1116506578
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);

      //## Operation: Set%1116507646
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags = 0);

      //## Operation: Set%1116507647
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags = 0);

      //## Operation: Cast%1116506579
      virtual void Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value);

      //## Operation: Read%1116506580
      virtual void Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Get%1121073529
      virtual void Get (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T &value, ULONG_T flags = 0);

      //## Operation: Get%1121073530
      virtual void Get (CONST_STRING_T buf_spec, ULONG_T address, LONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1121073531
      virtual void Get (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1121073532
      virtual void Get (CONST_STRING_T buf_spec, ULONG_T address, STRING_T &value, ULONG_T flags = 0);

      //## Operation: Get%1121073533
      virtual void Get (CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T &value, ULONG_T flags = 0);

  public:
    // Additional Public Declarations
      //## begin cPerfDevice%428C87EE01F4.public preserve=yes
      //## end cPerfDevice%428C87EE01F4.public

  protected:
    // Additional Protected Declarations
      //## begin cPerfDevice%428C87EE01F4.protected preserve=yes
      //## end cPerfDevice%428C87EE01F4.protected

  private:
    // Additional Private Declarations
      //## begin cPerfDevice%428C87EE01F4.private preserve=yes
      //## end cPerfDevice%428C87EE01F4.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Refresh%1116507648
      void Refresh ();

    // Data Members for Class Attributes

      //## Attribute: PerfObject%428C884A0157
      //## begin cPerfDevice::PerfObject%428C884A0157.attr preserve=no  implementation: cPerformance * {U} NULL
      cPerformance *_PerfObject;
      //## end cPerfDevice::PerfObject%428C884A0157.attr

      //## Attribute: PerfData%428C8F40037A
      //## begin cPerfDevice::PerfData%428C8F40037A.attr preserve=no  implementation: PERF_DATA_T {U} 
      PERF_DATA_T _PerfData;
      //## end cPerfDevice::PerfData%428C8F40037A.attr

      //## Attribute: BackupPerfData%428C8F5D00FA
      //## begin cPerfDevice::BackupPerfData%428C8F5D00FA.attr preserve=no  implementation: PERF_DATA_T {U} 
      PERF_DATA_T _BackupPerfData;
      //## end cPerfDevice::BackupPerfData%428C8F5D00FA.attr

      //## Attribute: Start%428CC4A70000
      //## begin cPerfDevice::Start%428CC4A70000.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Start;
      //## end cPerfDevice::Start%428CC4A70000.attr

      //## Attribute: ProcessId%428CC4CE037A
      //## begin cPerfDevice::ProcessId%428CC4CE037A.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ProcessId;
      //## end cPerfDevice::ProcessId%428CC4CE037A.attr

      //## Attribute: Channels%430227B901C5
      //## begin cPerfDevice::Channels%430227B901C5.attr preserve=no  implementation: CHANNEL_ARRAY_T {U} 
      CHANNEL_ARRAY_T _Channels;
      //## end cPerfDevice::Channels%430227B901C5.attr

    // Additional Implementation Declarations
      //## begin cPerfDevice%428C87EE01F4.implementation preserve=yes
      //## end cPerfDevice%428C87EE01F4.implementation

};

//## begin cPerfDevice%428C87EE01F4.postscript preserve=yes
//## end cPerfDevice%428C87EE01F4.postscript

// Class cPerfDevice 

//## begin module%428C87EE01F4.epilog preserve=yes
//## end module%428C87EE01F4.epilog


#endif
