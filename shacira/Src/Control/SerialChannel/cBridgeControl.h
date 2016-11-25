//## begin module%3FBCC1D6009C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBCC1D6009C.cm

//## begin module%3FBCC1D6009C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBCC1D6009C.cp

//## Module: cBridgeControl%3FBCC1D6009C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cBridgeControl.h

#ifndef cBridgeControl_h
#define cBridgeControl_h 1

//## begin module%3FBCC1D6009C.includes preserve=yes
//## end module%3FBCC1D6009C.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cSerialChannel;
class __DLL_EXPORT__ cSerialBridge;

//## begin module%3FBCC1D6009C.additionalDeclarations preserve=yes
//## end module%3FBCC1D6009C.additionalDeclarations


//## begin cBridgeControl%3FBCC1D6009C.preface preserve=yes
//## end cBridgeControl%3FBCC1D6009C.preface

//## Class: cBridgeControl%3FBCC1D6009C
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cBridgeControl : public cControlThread  //## Inherits: <unnamed>%3FBCC2140177
{
  //## begin cBridgeControl%3FBCC1D6009C.initialDeclarations preserve=yes
public:
  //## end cBridgeControl%3FBCC1D6009C.initialDeclarations

    //## Constructors (generated)
      cBridgeControl();

      cBridgeControl(const cBridgeControl &right);

    //## Constructors (specified)
      //## Operation: cBridgeControl%1069326617
      cBridgeControl (cSerialChannel *input, cSerialChannel *output, cSerialBridge *bridge);

    //## Destructor (generated)
      virtual ~cBridgeControl();


    //## Other Operations (specified)
      //## Operation: MainFunc%1069326618
      virtual INT_T MainFunc (void *extra);

  public:
    // Additional Public Declarations
      //## begin cBridgeControl%3FBCC1D6009C.public preserve=yes
      //## end cBridgeControl%3FBCC1D6009C.public

  protected:
    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3FBCC45703B9
      //## Role: cBridgeControl::Bridge%3FBCC459006D
      //## begin cBridgeControl::Bridge%3FBCC459006D.role preserve=no  public: cSerialBridge { -> 1RFHN}
      cSerialBridge *_Bridge;
      //## end cBridgeControl::Bridge%3FBCC459006D.role

      //## Association: Control::SerialChannel::<unnamed>%3FBCC4CA002E
      //## Role: cBridgeControl::Input%3FBCC4CB0157
      //## begin cBridgeControl::Input%3FBCC4CB0157.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_Input;
      //## end cBridgeControl::Input%3FBCC4CB0157.role

      //## Association: Control::SerialChannel::<unnamed>%3FBCC505006D
      //## Role: cBridgeControl::Output%3FBCC50503B9
      //## begin cBridgeControl::Output%3FBCC50503B9.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_Output;
      //## end cBridgeControl::Output%3FBCC50503B9.role

    // Additional Protected Declarations
      //## begin cBridgeControl%3FBCC1D6009C.protected preserve=yes
      //## end cBridgeControl%3FBCC1D6009C.protected

  private:
    // Additional Private Declarations
      //## begin cBridgeControl%3FBCC1D6009C.private preserve=yes
      //## end cBridgeControl%3FBCC1D6009C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cBridgeControl%3FBCC1D6009C.implementation preserve=yes
      //## end cBridgeControl%3FBCC1D6009C.implementation

};

//## begin cBridgeControl%3FBCC1D6009C.postscript preserve=yes
//## end cBridgeControl%3FBCC1D6009C.postscript

// Class cBridgeControl 

//## begin module%3FBCC1D6009C.epilog preserve=yes
//## end module%3FBCC1D6009C.epilog


#endif
