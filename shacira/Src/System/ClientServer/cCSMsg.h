//## begin module%4102753A033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4102753A033C.cm

//## begin module%4102753A033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4102753A033C.cp

//## Module: cCSMsg%4102753A033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cCSMsg.h

#ifndef cCSMsg_h
#define cCSMsg_h 1

//## begin module%4102753A033C.includes preserve=yes
//## end module%4102753A033C.includes

//## begin module%4102753A033C.additionalDeclarations preserve=yes

typedef struct {
   ULONG_T magic;
   ULONG_T client_id;
   ULONG_T request_id;
   ULONG_T data_size;
   ULONG_T data_offset;
   ULONG_T msg_size;
   ULONG_T msg_offset;
   ULONG_T block_no;
   ULONG_T block_count;
   USHORT_T listener_port;
   UCHAR_T reserved[32];
}  EXTENDED_CS_MSG_T;

//## end module%4102753A033C.additionalDeclarations


//## begin cCSMsg%4102753A033C.preface preserve=yes
//## end cCSMsg%4102753A033C.preface

//## Class: cCSMsg%4102753A033C
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCSMsg 
{
  //## begin cCSMsg%4102753A033C.initialDeclarations preserve=yes
public:
  //## end cCSMsg%4102753A033C.initialDeclarations

    //## Constructors (generated)
      cCSMsg();

      cCSMsg(const cCSMsg &right);

    //## Constructors (specified)
      //## Operation: cCSMsg%1107416646
      cCSMsg (PTR_T data, ULONG_T data_size, ULONG_T client_id, ULONG_T request_id, ULONG_T block_no, ULONG_T block_count, ULONG_T msg_size, ULONG_T msg_offset, USHORT_T listener_port);

      //## Operation: cCSMsg%1090681456
      cCSMsg (PTR_T data, ULONG_T data_size, BOOL_T copy = false);

      //## Operation: cCSMsg%1090862811
      cCSMsg (ULONG_T data_size);

    //## Destructor (generated)
      virtual ~cCSMsg();


    //## Other Operations (specified)
      //## Operation: Data%1090681468
      virtual PTR_T Data ();

      //## Operation: DataSize%1090681469
      virtual ULONG_T DataSize ();

      //## Operation: AppData%1107416635
      virtual PTR_T AppData ();

      //## Operation: AppDataSize%1090860526
      virtual ULONG_T AppDataSize ();

      //## Operation: SetAppDataSize%1090860527
      virtual void SetAppDataSize (ULONG_T size);

      //## Operation: CopyMsg%1107416633
      virtual cCSMsg * CopyMsg ();

      //## Operation: ClientId%1107416636
      ULONG_T ClientId ();

      //## Operation: RequestId%1107416637
      ULONG_T RequestId ();

      //## Operation: MsgSize%1107416638
      ULONG_T MsgSize ();

      //## Operation: MsgOffset%1107416639
      ULONG_T MsgOffset ();

      //## Operation: BlockNo%1107416640
      ULONG_T BlockNo ();

      //## Operation: BlockCount%1107416641
      ULONG_T BlockCount ();

      //## Operation: ListenerPort%1107780743
      USHORT_T ListenerPort ();

      //## Operation: SetBlockNo%1107869859
      void SetBlockNo (ULONG_T block_no);

      //## Operation: SetMsgOffset%1107869860
      void SetMsgOffset (ULONG_T msg_offset);

      //## Operation: SetRequestId%1107939282
      void SetRequestId (ULONG_T request_id);

      //## Operation: Copy%1107416642
      cCSMsg * Copy (ULONG_T &offset, ULONG_T size);

      //## Operation: Paste%1107416643
      void Paste (cCSMsg *msg);

      //## Operation: IsComplete%1107416644
      BOOL_T IsComplete ();

  public:
    // Additional Public Declarations
      //## begin cCSMsg%4102753A033C.public preserve=yes
      //## end cCSMsg%4102753A033C.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: Header%4201FB3D0290
      //## begin cCSMsg::Header%4201FB3D0290.attr preserve=no  protected: EXTENDED_CS_MSG_T * {U} NULL
      EXTENDED_CS_MSG_T *_Header;
      //## end cCSMsg::Header%4201FB3D0290.attr

      //## Attribute: Data%41027E9D0222
      //## begin cCSMsg::Data%41027E9D0222.attr preserve=no  protected: PTR_T {U} NULL
      PTR_T _Data;
      //## end cCSMsg::Data%41027E9D0222.attr

      //## Attribute: DataSize%41027EBF035B
      //## begin cCSMsg::DataSize%41027EBF035B.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _DataSize;
      //## end cCSMsg::DataSize%41027EBF035B.attr

      //## Attribute: AppData%4201F0B3005D
      //## begin cCSMsg::AppData%4201F0B3005D.attr preserve=no  protected: PTR_T {U} NULL
      PTR_T _AppData;
      //## end cCSMsg::AppData%4201F0B3005D.attr

      //## Attribute: AppDataSize%4201F0B3005E
      //## begin cCSMsg::AppDataSize%4201F0B3005E.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _AppDataSize;
      //## end cCSMsg::AppDataSize%4201F0B3005E.attr

      //## Attribute: Allocated%4105524D0119
      //## begin cCSMsg::Allocated%4105524D0119.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Allocated;
      //## end cCSMsg::Allocated%4105524D0119.attr

      //## Attribute: RefCount%41F79BA0036B
      //## begin cCSMsg::RefCount%41F79BA0036B.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _RefCount;
      //## end cCSMsg::RefCount%41F79BA0036B.attr

      //## Attribute: ReceivedBlocks%420223CE0399
      //## begin cCSMsg::ReceivedBlocks%420223CE0399.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _ReceivedBlocks;
      //## end cCSMsg::ReceivedBlocks%420223CE0399.attr

      //## Attribute: IsComplete%4209F4BC02AF
      //## begin cCSMsg::IsComplete%4209F4BC02AF.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _IsComplete;
      //## end cCSMsg::IsComplete%4209F4BC02AF.attr

    // Additional Protected Declarations
      //## begin cCSMsg%4102753A033C.protected preserve=yes
      //## end cCSMsg%4102753A033C.protected

  private:
    // Additional Private Declarations
      //## begin cCSMsg%4102753A033C.private preserve=yes
      //## end cCSMsg%4102753A033C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCSMsg%4102753A033C.implementation preserve=yes
      //## end cCSMsg%4102753A033C.implementation

};

//## begin cCSMsg%4102753A033C.postscript preserve=yes
//## end cCSMsg%4102753A033C.postscript

// Class cCSMsg 

//## begin module%4102753A033C.epilog preserve=yes
//## end module%4102753A033C.epilog


#endif
