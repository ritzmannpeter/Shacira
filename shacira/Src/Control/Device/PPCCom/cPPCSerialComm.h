//## begin module%41089B84003E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41089B84003E.cm

//## begin module%41089B84003E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41089B84003E.cp

//## Module: cPPCSerialComm%41089B84003E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCSerialComm.h

#ifndef cPPCSerialComm_h
#define cPPCSerialComm_h 1

//## begin module%41089B84003E.includes preserve=yes
//## end module%41089B84003E.includes

// cCSComm
#include "System/ClientServer/cCSComm.h"

class __DLL_EXPORT__ cSerialChannel;

//## begin module%41089B84003E.additionalDeclarations preserve=yes
//## end module%41089B84003E.additionalDeclarations


//## begin cPPCSerialComm%41089B84003E.preface preserve=yes
//## end cPPCSerialComm%41089B84003E.preface

//## Class: cPPCSerialComm%41089B84003E
//## Category: Control::Device::PPCCom%410896E5001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPPCSerialComm : public cCSComm  //## Inherits: <unnamed>%41089BD801E4
{
  //## begin cPPCSerialComm%41089B84003E.initialDeclarations preserve=yes
public:
  //## end cPPCSerialComm%41089B84003E.initialDeclarations

    //## Constructors (generated)
      cPPCSerialComm();

      cPPCSerialComm(const cPPCSerialComm &right);

    //## Constructors (specified)
      //## Operation: cPPCSerialComm%1091082169
      cPPCSerialComm (cSerialChannel *serial_channel);

    //## Destructor (generated)
      virtual ~cPPCSerialComm();


    //## Other Operations (specified)
      //## Operation: Send%1091082170
      virtual void Send (cCSMsg *msg, cCSAddress *address);

      //## Operation: Reply%1091082171
      virtual void Reply (cCSMsg *msg, cCSAddress *client_address);

      //## Operation: Receive%1091082172
      virtual void Receive (cCSMsg &msg, cCSAddress *sender_address, ULONG_T tmo = WAIT_FOR_EVER);

      //## Operation: ReadAddress%1091085014
      virtual cCSAddress * ReadAddress ();

      //## Operation: WriteAddress%1091085015
      virtual cCSAddress * WriteAddress ();

  public:
    // Additional Public Declarations
      //## begin cPPCSerialComm%41089B84003E.public preserve=yes
      //## end cPPCSerialComm%41089B84003E.public

  protected:
    // Data Members for Associations

      //## Association: Control::Device::PPCCom::<unnamed>%41089CA00138
      //## Role: cPPCSerialComm::SerialCjhannel%41089CA10109
      //## begin cPPCSerialComm::SerialCjhannel%41089CA10109.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_SerialCjhannel;
      //## end cPPCSerialComm::SerialCjhannel%41089CA10109.role

    // Additional Protected Declarations
      //## begin cPPCSerialComm%41089B84003E.protected preserve=yes
      //## end cPPCSerialComm%41089B84003E.protected

  private:
    // Additional Private Declarations
      //## begin cPPCSerialComm%41089B84003E.private preserve=yes
      //## end cPPCSerialComm%41089B84003E.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetReadTimeout%1091082173
      void SetReadTimeout (ULONG_T tmo);

    // Additional Implementation Declarations
      //## begin cPPCSerialComm%41089B84003E.implementation preserve=yes
      //## end cPPCSerialComm%41089B84003E.implementation

};

//## begin cPPCSerialComm%41089B84003E.postscript preserve=yes
//## end cPPCSerialComm%41089B84003E.postscript

// Class cPPCSerialComm 

//## begin module%41089B84003E.epilog preserve=yes
//## end module%41089B84003E.epilog


#endif
