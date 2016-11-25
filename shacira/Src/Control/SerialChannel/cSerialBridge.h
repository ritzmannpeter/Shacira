//## begin module%3FBC9F43000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBC9F43000F.cm

//## begin module%3FBC9F43000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBC9F43000F.cp

//## Module: cSerialBridge%3FBC9F43000F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialBridge.h

#ifndef cSerialBridge_h
#define cSerialBridge_h 1

//## begin module%3FBC9F43000F.includes preserve=yes
//## end module%3FBC9F43000F.includes

// eb_sema
#include "base/eb_sema.hpp"

class __DLL_EXPORT__ cSerialChannel;
class __DLL_EXPORT__ cBridgeControl;
class __DLL_EXPORT__ cMultiplexer;

//## begin module%3FBC9F43000F.additionalDeclarations preserve=yes
//## end module%3FBC9F43000F.additionalDeclarations


//## begin cSerialBridge%3FBC9F43000F.preface preserve=yes
//## end cSerialBridge%3FBC9F43000F.preface

//## Class: cSerialBridge%3FBC9F43000F
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FBCE17903C8;cMutexSem { -> }

class __DLL_EXPORT__ cSerialBridge 
{
  //## begin cSerialBridge%3FBC9F43000F.initialDeclarations preserve=yes
public:
  //## end cSerialBridge%3FBC9F43000F.initialDeclarations

    //## Constructors (generated)
      cSerialBridge();

      cSerialBridge(const cSerialBridge &right);

    //## Constructors (specified)
      //## Operation: cSerialBridge%1069326590
      cSerialBridge (cSerialChannel *front, cSerialChannel *back);

    //## Destructor (generated)
      virtual ~cSerialBridge();

    // Data Members for Class Attributes

      //## Attribute: IOMutex%3FBCE14A02AF
      //## begin cSerialBridge::IOMutex%3FBCE14A02AF.attr preserve=no  public: cMutexSem {U} 
      cMutexSem _IOMutex;
      //## end cSerialBridge::IOMutex%3FBCE14A02AF.attr

  public:
    // Additional Public Declarations
      //## begin cSerialBridge%3FBC9F43000F.public preserve=yes
      //## end cSerialBridge%3FBC9F43000F.public

  protected:
    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3FBCA00E00CB
      //## Role: cSerialBridge::Multiplexer%3FBCA00F01F5
      //## begin cSerialBridge::Multiplexer%3FBCA00F01F5.role preserve=no  public: cMultiplexer {1 -> RFHN}
      cMultiplexer *_Multiplexer;
      //## end cSerialBridge::Multiplexer%3FBCA00F01F5.role

      //## Association: Control::SerialChannel::<unnamed>%3FBC9F9902FD
      //## Role: cSerialBridge::Front%3FBC9F9B032C
      //## begin cSerialBridge::Front%3FBC9F9B032C.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_Front;
      //## end cSerialBridge::Front%3FBC9F9B032C.role

      //## Association: Control::SerialChannel::<unnamed>%3FBC9FB602DE
      //## Role: cSerialBridge::Back%3FBC9FB800DA
      //## begin cSerialBridge::Back%3FBC9FB800DA.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_Back;
      //## end cSerialBridge::Back%3FBC9FB800DA.role

      //## Association: Control::SerialChannel::<unnamed>%3FBCC27203C8
      //## Role: cSerialBridge::InputControl%3FBCC2730222
      //## begin cSerialBridge::InputControl%3FBCC2730222.role preserve=no  public: cBridgeControl { -> 1RFHN}
      cBridgeControl *_InputControl;
      //## end cSerialBridge::InputControl%3FBCC2730222.role

      //## Association: Control::SerialChannel::<unnamed>%3FBCC29C01F4
      //## Role: cSerialBridge::OutputControl%3FBCC29D0203
      //## begin cSerialBridge::OutputControl%3FBCC29D0203.role preserve=no  public: cBridgeControl { -> 1RFHN}
      cBridgeControl *_OutputControl;
      //## end cSerialBridge::OutputControl%3FBCC29D0203.role

    // Additional Protected Declarations
      //## begin cSerialBridge%3FBC9F43000F.protected preserve=yes
      //## end cSerialBridge%3FBC9F43000F.protected

  private:
    // Additional Private Declarations
      //## begin cSerialBridge%3FBC9F43000F.private preserve=yes
      //## end cSerialBridge%3FBC9F43000F.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSerialBridge%3FBC9F43000F.implementation preserve=yes
      //## end cSerialBridge%3FBC9F43000F.implementation

};

//## begin cSerialBridge%3FBC9F43000F.postscript preserve=yes
//## end cSerialBridge%3FBC9F43000F.postscript

// Class cSerialBridge 

//## begin module%3FBC9F43000F.epilog preserve=yes
//## end module%3FBC9F43000F.epilog


#endif
