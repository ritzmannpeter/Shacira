//## begin module%4104CB250157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4104CB250157.cm

//## begin module%4104CB250157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4104CB250157.cp

//## Module: cUDPClient%4104CB250157; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPClient.h

#ifndef cUDPClient_h
#define cUDPClient_h 1

//## begin module%4104CB250157.includes preserve=yes
//## end module%4104CB250157.includes

// eb_thread
#include "base/eb_thread.hpp"
// cCSMsg
#include "System/ClientServer/cCSMsg.h"
// cCSAddress
#include "System/ClientServer/cCSAddress.h"
// cCSComm
#include "System/ClientServer/cCSComm.h"
// cBlockQueue
#include "System/ClientServer/cBlockQueue.h"


//## begin module%4104CB250157.additionalDeclarations preserve=yes
//## end module%4104CB250157.additionalDeclarations


//## begin cUDPClient%4104CB250157.preface preserve=yes
//## end cUDPClient%4104CB250157.preface

//## Class: cUDPClient%4104CB250157
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4104EB2C037A;cCSAddress { -> }
//## Uses: <unnamed>%4104EB4B03D8;cCSMsg { -> }
//## Uses: <unnamed>%4104FC280186;cCSComm { -> }
//## Uses: <unnamed>%4108B2FC032C;cBlockQueue { -> }

class __DLL_EXPORT__ cUDPClient : public cThread  //## Inherits: <unnamed>%41053E970148
{
  //## begin cUDPClient%4104CB250157.initialDeclarations preserve=yes
public:
  //## end cUDPClient%4104CB250157.initialDeclarations

    //## Constructors (generated)
      cUDPClient();

      cUDPClient(const cUDPClient &right);

    //## Constructors (specified)
      //## Operation: cUDPClient%1090833150
      cUDPClient (cCSComm *comm);

    //## Destructor (generated)
      virtual ~cUDPClient();


    //## Other Operations (specified)
      //## Operation: Start%1090862806
      void Start ();

      //## Operation: Stop%1090862807
      void Stop ();

      //## Operation: onEnter%1090862808
      virtual BOOL_T onEnter (void *extra);

      //## Operation: onMain%1090862809
      virtual INT_T onMain (void *extra);

      //## Operation: onLeave%1090862810
      virtual void onLeave (INT_T rc);

      //## Operation: Send%1090833153
      void Send (cCSMsg *msg, cCSAddress *address = NULL);

      //## Operation: Receive%1090840951
      void Receive (cCSMsg &msg, cCSAddress *client_address, ULONG_T tmo = WAIT_FOR_EVER);

      //## Operation: GetMessage%1090868763
      virtual ULONG_T GetMessage (PTR_T buf, ULONG_T buf_size, ULONG_T tmo, ULONG_T channel);

      //## Operation: FlushInput%1090946393
      void FlushInput (ULONG_T channel);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Terminated%41053F1302AF
      BOOL_T get_Terminated () const;
      void set_Terminated (BOOL_T value);

      STRING_T get_Name() const;
      void set_Name(STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cUDPClient%4104CB250157.public preserve=yes
      //## end cUDPClient%4104CB250157.public

  protected:

    //## Other Operations (specified)
      //## Operation: BlockQueue%1090910857
      cBlockQueue * BlockQueue (ULONG_T channel);

      //## Operation: Dispatch%1090862818
      virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);

    // Data Members for Class Attributes

      //## begin cUDPClient::Terminated%41053F1302AF.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Terminated;
      //## end cUDPClient::Terminated%41053F1302AF.attr

    // Data Members for Associations

      //## Association: System::ClientServer::<unnamed>%4104D4150167
      //## Role: cUDPClient::CSComm%4104D41600DA
      //## begin cUDPClient::CSComm%4104D41600DA.role preserve=no  public: cCSComm {0..1 -> 1RFHN}
      cCSComm *_CSComm;
      //## end cUDPClient::CSComm%4104D41600DA.role

      //## Association: System::ClientServer::<unnamed>%4105F983037A
      //## Role: cUDPClient::BlockQueues%4105F98402BF
      //## Qualifier: channel%4105FA600280; ULONG_T
      //## begin cUDPClient::BlockQueues%4105F98402BF.role preserve=no  public: cBlockQueue { -> 0..nRFHN}
      std::map<ULONG_T, cBlockQueue*> _BlockQueues;
      //## end cUDPClient::BlockQueues%4105F98402BF.role

    // Additional Protected Declarations
      //## begin cUDPClient%4104CB250157.protected preserve=yes
      //## end cUDPClient%4104CB250157.protected

      STRING_T _Name;

  private:
    // Additional Private Declarations
      //## begin cUDPClient%4104CB250157.private preserve=yes
      //## end cUDPClient%4104CB250157.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cUDPClient%4104CB250157.implementation preserve=yes
      //## end cUDPClient%4104CB250157.implementation

};

//## begin cUDPClient%4104CB250157.postscript preserve=yes
//## end cUDPClient%4104CB250157.postscript

// Class cUDPClient 

//## begin module%4104CB250157.epilog preserve=yes
//## end module%4104CB250157.epilog


#endif
