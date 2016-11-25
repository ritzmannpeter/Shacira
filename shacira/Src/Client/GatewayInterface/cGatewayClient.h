//## begin module%429C5CE7035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C5CE7035B.cm

//## begin module%429C5CE7035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429C5CE7035B.cp

//## Module: cGatewayClient%429C5CE7035B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\GatewayInterface\cGatewayClient.h

#ifndef cGatewayClient_h
#define cGatewayClient_h 1

//## begin module%429C5CE7035B.includes preserve=yes
//## end module%429C5CE7035B.includes


class __DLL_EXPORT__ cClient;

//## begin module%429C5CE7035B.additionalDeclarations preserve=yes
//## end module%429C5CE7035B.additionalDeclarations


//## begin cGatewayClient%429C5CE7035B.preface preserve=yes
//## end cGatewayClient%429C5CE7035B.preface

//## Class: cGatewayClient%429C5CE7035B
//## Category: Client::GatewayInterface%4200D7C40213
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cGatewayClient 
{
  //## begin cGatewayClient%429C5CE7035B.initialDeclarations preserve=yes
public:
  //## end cGatewayClient%429C5CE7035B.initialDeclarations

    //## Constructors (generated)
      cGatewayClient();

      cGatewayClient(const cGatewayClient &right);

    //## Constructors (specified)
      //## Operation: cGatewayClient%1117544868
      cGatewayClient (ULONG_T client_id, USHORT_T server_port, CONST_STRING_T server_host = "localhost");

    //## Destructor (generated)
      virtual ~cGatewayClient();


    //## Other Operations (specified)
      //## Operation: GetValue%1117544869
      int GetValue (CONST_STRING_T cell_name, CONST_STRING_T var_spec, CHAR_T *buf, ULONG_T buf_size);

      //## Operation: SetValue%1117544870
      int SetValue (CONST_STRING_T cell_name, CONST_STRING_T var_spec, CONST_STRING_T value);

      //## Operation: GetPage%1127151467
      int GetPage (CONST_STRING_T cell_name, CONST_STRING_T page, CHAR_T *buf, ULONG_T buf_size);

      //## Operation: GetContextList%1117544871
      int GetContextList (CHAR_T *buf, ULONG_T buf_size);

      //## Operation: Request%1136191750
      int Request (CONST_STRING_T cell_name, CONST_STRING_T request, CHAR_T *buf, ULONG_T buf_size);

  public:
    // Additional Public Declarations
      //## begin cGatewayClient%429C5CE7035B.public preserve=yes
      //## end cGatewayClient%429C5CE7035B.public

  protected:
    // Data Members for Associations

      //## Association: Client::GatewayInterface::<unnamed>%429C630303A9
      //## Role: cGatewayClient::Client%429C630401A5
      //## begin cGatewayClient::Client%429C630401A5.role preserve=no  public: cClient { -> 1RFHN}
      cClient *_Client;
      //## end cGatewayClient::Client%429C630401A5.role

    // Additional Protected Declarations
      //## begin cGatewayClient%429C5CE7035B.protected preserve=yes
      //## end cGatewayClient%429C5CE7035B.protected

  private:
    // Additional Private Declarations
      //## begin cGatewayClient%429C5CE7035B.private preserve=yes
      //## end cGatewayClient%429C5CE7035B.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ClientId%429C5FD50157
      //## begin cGatewayClient::ClientId%429C5FD50157.attr preserve=no  private: ULONG_T {U} 0
      ULONG_T _ClientId;
      //## end cGatewayClient::ClientId%429C5FD50157.attr

    // Additional Implementation Declarations
      //## begin cGatewayClient%429C5CE7035B.implementation preserve=yes
      //## end cGatewayClient%429C5CE7035B.implementation

};

//## begin cGatewayClient%429C5CE7035B.postscript preserve=yes
//## end cGatewayClient%429C5CE7035B.postscript

// Class cGatewayClient 

//## begin module%429C5CE7035B.epilog preserve=yes
//## end module%429C5CE7035B.epilog


#endif
