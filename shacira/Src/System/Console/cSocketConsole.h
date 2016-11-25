//## begin module%3DD3932702C4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3932702C4.cm

//## begin module%3DD3932702C4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3932702C4.cp

//## Module: cSocketConsole%3DD3932702C4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cSocketConsole.h

#ifndef cSocketConsole_h
#define cSocketConsole_h 1

//## begin module%3DD3932702C4.includes preserve=yes
//## end module%3DD3932702C4.includes

// cConsole
#include "System/Sys/cSockets.h"
#include "System/Console/cConsole.h"

class __DLL_EXPORT__ cSockets;
class __DLL_EXPORT__ cConvUtils;

//## begin module%3DD3932702C4.additionalDeclarations preserve=yes
//## end module%3DD3932702C4.additionalDeclarations


//## begin cSocketConsole%3DD3932702C4.preface preserve=yes
//## end cSocketConsole%3DD3932702C4.preface

//## Class: cSocketConsole%3DD3932702C4
//## Category: System::Console%3DC92CF602A4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD3974F01AC;cSockets { -> F}
//## Uses: <unnamed>%3DD39DC30157;cConvUtils { -> F}

class __DLL_EXPORT__ cSocketConsole : public cConsole  //## Inherits: <unnamed>%3DD3941600A1
{
  //## begin cSocketConsole%3DD3932702C4.initialDeclarations preserve=yes
public:
  //## end cSocketConsole%3DD3932702C4.initialDeclarations

    //## Constructors (generated)
      cSocketConsole();

      cSocketConsole(const cSocketConsole &right);

    //## Constructors (specified)
      //## Operation: cSocketConsole%1037267677
      cSocketConsole (CONST_STRING_T ip_address, ULONG_T port, INT_T direction = DIRECTION_OUTPUT);

    //## Destructor (generated)
      virtual ~cSocketConsole();


    //## Other Operations (specified)
      //## Operation: Write%1037267678
      virtual void Write (CONST_STRING_T text);

      //## Operation: Read%1037267679
      virtual LONG_T Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout = 0);

      //## Operation: FlushInput%1037267680
      virtual void FlushInput ();

      //## Operation: FlushOutput%1037267681
      virtual void FlushOutput ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IPAddress%3DD393AF0297
      STRING_T get_IPAddress () const;

      //## Attribute: Port%3DD393AF02A1
      ULONG_T get_Port () const;

  public:
    // Additional Public Declarations
      //## begin cSocketConsole%3DD3932702C4.public preserve=yes
      //## end cSocketConsole%3DD3932702C4.public

  protected:
    // Data Members for Class Attributes

      //## begin cSocketConsole::IPAddress%3DD393AF0297.attr preserve=no  public: STRING_T {U} "127.0.0.1"
      STRING_T _IPAddress;
      //## end cSocketConsole::IPAddress%3DD393AF0297.attr

      //## begin cSocketConsole::Port%3DD393AF02A1.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Port;
      //## end cSocketConsole::Port%3DD393AF02A1.attr

    // Additional Protected Declarations
      //## begin cSocketConsole%3DD3932702C4.protected preserve=yes
      //## end cSocketConsole%3DD3932702C4.protected

  private:
    // Additional Private Declarations
      //## begin cSocketConsole%3DD3932702C4.private preserve=yes
      //## end cSocketConsole%3DD3932702C4.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetSockets%1037267682
      void SetSockets ();

      //## Operation: CloseSockets%1037267683
      void CloseSockets ();

      //## Operation: Receive%1037267686
      LONG_T Receive (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout);

      //## Operation: Send%1037267687
      void Send (CONST_STRING_T msg);

    // Data Members for Class Attributes

      //## Attribute: Socket%3DD398950287
      //## begin cSocketConsole::Socket%3DD398950287.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cSocketConsole::Socket%3DD398950287.attr

    // Additional Implementation Declarations
      //## begin cSocketConsole%3DD3932702C4.implementation preserve=yes
      //## end cSocketConsole%3DD3932702C4.implementation

};

//## begin cSocketConsole%3DD3932702C4.postscript preserve=yes
//## end cSocketConsole%3DD3932702C4.postscript

// Class cSocketConsole 

//## begin module%3DD3932702C4.epilog preserve=yes
//## end module%3DD3932702C4.epilog


#endif
