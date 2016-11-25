//## begin module%404713CF0138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404713CF0138.cm

//## begin module%404713CF0138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404713CF0138.cp

//## Module: cDigIODevice%404713CF0138; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cDigIODevice.h

#ifndef cDigIODevice_h
#define cDigIODevice_h 1

//## begin module%404713CF0138.includes preserve=yes
//## end module%404713CF0138.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cBlockCache;
class __DLL_EXPORT__ cCache;
class __DLL_EXPORT__ cMemoryAddressedDevice;
class __DLL_EXPORT__ cMemIO;
class __DLL_EXPORT__ cPA150;
class __DLL_EXPORT__ cAddiStandard;
class __DLL_EXPORT__ cDigIO;

//## begin module%404713CF0138.additionalDeclarations preserve=yes
//## end module%404713CF0138.additionalDeclarations


//## begin cDigIODevice%404713CF0138.preface preserve=yes
//## end cDigIODevice%404713CF0138.preface

//## Class: cDigIODevice%404713CF0138
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40472A98029F;cBlockCache { -> F}
//## Uses: <unnamed>%40472D46037A;cAddiStandard { -> F}
//## Uses: <unnamed>%40472D4D0290;cPA150 { -> F}
//## Uses: <unnamed>%40472D550280;cMemIO { -> F}
//## Uses: <unnamed>%40473D820186;cCacheControl { -> F}
//## Uses: <unnamed>%404740E90271;cObjectLock { -> F}

class __DLL_EXPORT__ cDigIODevice : public cDevice  //## Inherits: <unnamed>%4047140201A5
{
  //## begin cDigIODevice%404713CF0138.initialDeclarations preserve=yes
public:
  //## end cDigIODevice%404713CF0138.initialDeclarations

    //## Constructors (generated)
      cDigIODevice();

      cDigIODevice(const cDigIODevice &right);

    //## Constructors (specified)
      //## Operation: cDigIODevice%1078400651
      cDigIODevice (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cDigIODevice();


    //## Other Operations (specified)
      //## Operation: Start%1078400652
      virtual void Start ();

      //## Operation: Stop%1078400653
      virtual void Stop ();

      //## Operation: Cache%1078400654
      virtual void Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Buffer%1078400655
      virtual void Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements = 1);

      //## Operation: Read%1078400656
      virtual void Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Write%1078400657
      virtual void Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CardType%40472B3F03C8
      ULONG_T get_CardType () const;
      void set_CardType (ULONG_T value);

      //## Attribute: Inputs%4047364A038A
      ULONG_T get_Inputs () const;
      void set_Inputs (ULONG_T value);

      //## Attribute: Outputs%4047366102AF
      ULONG_T get_Outputs () const;
      void set_Outputs (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cDigIODevice%404713CF0138.public preserve=yes
      //## end cDigIODevice%404713CF0138.public

  protected:
    // Data Members for Class Attributes

      //## begin cDigIODevice::CardType%40472B3F03C8.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _CardType;
      //## end cDigIODevice::CardType%40472B3F03C8.attr

      //## begin cDigIODevice::Inputs%4047364A038A.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Inputs;
      //## end cDigIODevice::Inputs%4047364A038A.attr

      //## begin cDigIODevice::Outputs%4047366102AF.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Outputs;
      //## end cDigIODevice::Outputs%4047366102AF.attr

    // Data Members for Associations

      //## Association: Control::Device::<unnamed>%40472BE5004E
      //## Role: cDigIODevice::Simulation%40472BE503C8
      //## begin cDigIODevice::Simulation%40472BE503C8.role preserve=no  public: cMemoryAddressedDevice { -> 0..1RFHN}
      cMemoryAddressedDevice *_Simulation;
      //## end cDigIODevice::Simulation%40472BE503C8.role

      //## Association: Control::Device::<unnamed>%404718450251
      //## Role: cDigIODevice::IoCard%404718460177
      //## begin cDigIODevice::IoCard%404718460177.role preserve=no  public: cDigIO { -> 1RFHN}
      cDigIO *_IoCard;
      //## end cDigIODevice::IoCard%404718460177.role

      //## Association: Control::Device::<unnamed>%40472A6702FD
      //## Role: cDigIODevice::InputCache%40472A680271
      //## begin cDigIODevice::InputCache%40472A680271.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_InputCache;
      //## end cDigIODevice::InputCache%40472A680271.role

      //## Association: Control::Device::<unnamed>%41206EFA0290
      //## Role: cDigIODevice::OutputCache%41206EFB01E4
      //## begin cDigIODevice::OutputCache%41206EFB01E4.role preserve=no  public: cCache { -> RFHN}
      cCache *_OutputCache;
      //## end cDigIODevice::OutputCache%41206EFB01E4.role

    // Additional Protected Declarations
      //## begin cDigIODevice%404713CF0138.protected preserve=yes
      //## end cDigIODevice%404713CF0138.protected

  private:
    // Additional Private Declarations
      //## begin cDigIODevice%404713CF0138.private preserve=yes
      //## end cDigIODevice%404713CF0138.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetOutput%1078400659
      void SetOutput (ULONG_T output_no);

      //## Operation: ResetOutput%1078400661
      void ResetOutput (ULONG_T output_no);

      //## Operation: GetInput%1078400660
      BOOL_T GetInput (ULONG_T input_no);

      //## Operation: GetInputs%1078400662
      ULONG_T GetInputs (void *inputs, ULONG_T buf_size);

      //## Operation: DigIOLoad%1078410639
      void DigIOLoad (MEMORY_INFO *info, void *buf, ULONG_T address, ULONG_T len);

      //## Operation: DigIOSaveInputs%1078410640
      void DigIOSaveInputs (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address);

      //## Operation: DigIOSaveOutputs%1078416426
      void DigIOSaveOutputs (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address);

    // Additional Implementation Declarations
      //## begin cDigIODevice%404713CF0138.implementation preserve=yes
      //## end cDigIODevice%404713CF0138.implementation

};

//## begin cDigIODevice%404713CF0138.postscript preserve=yes
//## end cDigIODevice%404713CF0138.postscript

// Class cDigIODevice 

//## begin module%404713CF0138.epilog preserve=yes
//## end module%404713CF0138.epilog


#endif
