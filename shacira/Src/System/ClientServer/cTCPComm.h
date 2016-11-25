//## begin module%429AC0EF031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429AC0EF031C.cm

//## begin module%429AC0EF031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429AC0EF031C.cp

//## Module: cTCPComm%429AC0EF031C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cTCPComm.h

#ifndef cTCPComm_h
#define cTCPComm_h 1

//## begin module%429AC0EF031C.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%429AC0EF031C.includes

//## begin module%429AC0EF031C.additionalDeclarations preserve=yes

#define ERR_SIZE_MISMATCH           9001
#define ERR_SIGNATURE_MISMATCH      9002
#define ERR_SENT_MSG_TOO_SHORT      9003
#define ERR_RECEIVED_MSG_TOO_SHORT  9004

#define WAIT_FOR_EVER   0xFFFFFFFF
#define STREAM_SIGNATURE 0xabcdef01
#define BINARY_TYPE  1
#define ASCII_TYPE   2
typedef struct _stream_header {
   ULONG_T signature;
   ULONG_T request_id;
   ULONG_T data_type;
   ULONG_T data_size;
}  STREAM_HEADER_T;

#define LastError() cTCPComm::LastErr()
#define SocketError() cTCPComm::SocketErr()
#define ErrorString(ec) cTCPComm::ErrString(ec)

class cStreamMsg
{
public:
   cStreamMsg()
   {
      _Msg = NULL;
      _MsgLen = 0;
      _Allocated = false;
      _RefCount = 1;
   };
   cStreamMsg(cStreamMsg & right)
   {
      _Msg = right._Msg;
      _MsgLen = right._MsgLen;
      _Allocated = right._Allocated;
      _RefCount++;
   };
   cStreamMsg(void * msg, ULONG_T msg_len)
   {
      _Msg = msg;
      _MsgLen = msg_len;
      _Allocated = false;
      _RefCount = 1;
   };
   virtual ~cStreamMsg()
   {
      _RefCount--;
      if (_Allocated &&
         _RefCount == 0 &&
         _Msg != NULL &&
         _MsgLen != 0) {
         cSystemUtils::Free(_Msg);
         _Total--;
      }
   };
   void Allocate(ULONG_T size)
   {
      if (_Allocated &&
          _Msg != NULL &&
         _MsgLen != 0) {
         cSystemUtils::Free(_Msg);
         _Total--;
      }
      _Msg = cSystemUtils::Alloc(size);
      _MsgLen = size;
      _Allocated = true;
      _Total++;
   };
   void * MsgBuf()
   {
      return _Msg;
   };
   ULONG_T MsgLen()
   {
      return _MsgLen;
   };
private:
   static ULONG_T _Total;
   void * _Msg;
   ULONG_T _MsgLen;
   BOOL_T _Allocated;
   ULONG_T _RefCount;
};

//## end module%429AC0EF031C.additionalDeclarations


//## begin cTCPComm%429AC0EF031C.preface preserve=yes
//## end cTCPComm%429AC0EF031C.preface

//## Class: cTCPComm%429AC0EF031C
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cTCPComm 
{
  //## begin cTCPComm%429AC0EF031C.initialDeclarations preserve=yes
public:
  //## end cTCPComm%429AC0EF031C.initialDeclarations

    //## Constructors (generated)
      cTCPComm();

      cTCPComm(const cTCPComm &right);

    //## Destructor (generated)
      virtual ~cTCPComm();


    //## Other Operations (specified)
      //## Operation: SendMsg%1117436334
      static int SendMsg (SOCKET socket, cStreamMsg &msg, ULONG_T request_id = 0);

      //## Operation: ReceiveMsg%1117436335
      static int ReceiveMsg (SOCKET socket, cStreamMsg &msg, ULONG_T &request_id);

      //## Operation: ReceiveMsgFrom%1117453525
      static int ReceiveMsgFrom (SOCKET socket, cStreamMsg &msg, ULONG_T &request_id);

      //## Operation: CheckHeader%1117436330
      static BOOL_T CheckHeader (LONG_T nread, STREAM_HEADER_T *header, ULONG_T request_id = 0);

      //## Operation: ShutDownSocket%1117436331
      static void ShutDownSocket (SOCKET &socket);

      //## Operation: SetLastErr%1117453523
      static void SetLastErr (int err_code = 0);

      //## Operation: LastErr%1117436332
      static int LastErr ();

      //## Operation: SocketErr%1117453524
      static int SocketErr ();

      //## Operation: ErrString%1117436333
      static STRING_T ErrString (int err_code);

  public:
    // Additional Public Declarations
      //## begin cTCPComm%429AC0EF031C.public preserve=yes
      //## end cTCPComm%429AC0EF031C.public

  protected:
    // Additional Protected Declarations
      //## begin cTCPComm%429AC0EF031C.protected preserve=yes
      //## end cTCPComm%429AC0EF031C.protected

  private:
    // Additional Private Declarations
      //## begin cTCPComm%429AC0EF031C.private preserve=yes
      //## end cTCPComm%429AC0EF031C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Error%429B38F60242
      //## begin cTCPComm::Error%429B38F60242.attr preserve=no  implementation: static int {U} 0
      static int _Error;
      //## end cTCPComm::Error%429B38F60242.attr

    // Additional Implementation Declarations
      //## begin cTCPComm%429AC0EF031C.implementation preserve=yes
      //## end cTCPComm%429AC0EF031C.implementation

};

//## begin cTCPComm%429AC0EF031C.postscript preserve=yes
//## end cTCPComm%429AC0EF031C.postscript

// Class cTCPComm 

//## begin module%429AC0EF031C.epilog preserve=yes
//## end module%429AC0EF031C.epilog


#endif
