//## begin module%4104CB250157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4104CB250157.cm

//## begin module%4104CB250157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4104CB250157.cp

//## Module: cUDPClient%4104CB250157; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPClient.cpp

//## begin module%4104CB250157.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4104CB250157.additionalIncludes

//## begin module%4104CB250157.includes preserve=yes
#include "System/ClientServer/cs.h"
//## end module%4104CB250157.includes

// cUDPClient
#include "System/ClientServer/cUDPClient.h"
//## begin module%4104CB250157.additionalDeclarations preserve=yes

#define MSG_BUF_SIZE    0x2000
#define CLIENT_IDLE_TIME   10

//## end module%4104CB250157.additionalDeclarations


// Class cUDPClient 




cUDPClient::cUDPClient()
  //## begin cUDPClient::cUDPClient%.hasinit preserve=no
      : _Terminated(false), _CSComm(NULL)
  //## end cUDPClient::cUDPClient%.hasinit
  //## begin cUDPClient::cUDPClient%.initialization preserve=yes
  //## end cUDPClient::cUDPClient%.initialization
{
  //## begin cUDPClient::cUDPClient%.body preserve=yes
  //## end cUDPClient::cUDPClient%.body
}

cUDPClient::cUDPClient(const cUDPClient &right)
  //## begin cUDPClient::cUDPClient%copy.hasinit preserve=no
      : _Terminated(false), _CSComm(NULL)
  //## end cUDPClient::cUDPClient%copy.hasinit
  //## begin cUDPClient::cUDPClient%copy.initialization preserve=yes
  //## end cUDPClient::cUDPClient%copy.initialization
{
  //## begin cUDPClient::cUDPClient%copy.body preserve=yes
  //## end cUDPClient::cUDPClient%copy.body
}

cUDPClient::cUDPClient (cCSComm *comm)
  //## begin cUDPClient::cUDPClient%1090833150.hasinit preserve=no
      : _Terminated(false), _CSComm(NULL)
  //## end cUDPClient::cUDPClient%1090833150.hasinit
  //## begin cUDPClient::cUDPClient%1090833150.initialization preserve=yes
  //## end cUDPClient::cUDPClient%1090833150.initialization
{
  //## begin cUDPClient::cUDPClient%1090833150.body preserve=yes
   _CSComm = comm;
  //## end cUDPClient::cUDPClient%1090833150.body
}


cUDPClient::~cUDPClient()
{
  //## begin cUDPClient::~cUDPClient%.body preserve=yes
  //## end cUDPClient::~cUDPClient%.body
}



//## Other Operations (implementation)
void cUDPClient::Start ()
{
  //## begin cUDPClient::Start%1090862806.body preserve=yes
   if (start(teStart)) {
      InfoPrintf("%s started\n", get_Name().c_str());
   } else {
      InfoPrintf("failed to start %s\n", get_Name().c_str());
   }
   waitFor(teStart);
  //## end cUDPClient::Start%1090862806.body
}

void cUDPClient::Stop ()
{
  //## begin cUDPClient::Stop%1090862807.body preserve=yes
   _Terminated = true;
   waitFor(teEnd);
  //## end cUDPClient::Stop%1090862807.body
}

BOOL_T cUDPClient::onEnter (void *extra)
{
  //## begin cUDPClient::onEnter%1090862808.body preserve=yes
   return true;
  //## end cUDPClient::onEnter%1090862808.body
}

INT_T cUDPClient::onMain (void *extra)
{
  //## begin cUDPClient::onMain%1090862809.body preserve=yes
   char buf[0x2000] = {0};
   cCSMsg rcv_msg(buf, sizeof(buf));
   try {
      cCSAddress * server_address = NULL;
      while (!_Terminated) {
         try {
            if (_CSComm != NULL) {
               server_address = _CSComm->ReadAddress();
               _CSComm->Receive(rcv_msg, server_address);
               if (rcv_msg.AppDataSize() > 0) {
                  Dispatch(&rcv_msg, server_address);
               }
            } else {
               cSystemUtils::Suspend(CLIENT_IDLE_TIME);
            }
         } catch (cError & e) {
            ErrorPrintf("error %s in %s main thread\n", (const char*)e, get_Name().c_str());
            cSystemUtils::Suspend(CLIENT_IDLE_TIME);
         } catch (...) {
            ErrorPrintf("unhandled exception in %s main thread\n", get_Name().c_str());
            cSystemUtils::Suspend(CLIENT_IDLE_TIME);
         }
      }
       InfoPrintf("termination requested on %s ...\n", get_Name().c_str());
       return 0;
   } catch (...) {
      ErrorPrintf("unhandled exception in %s terminating\n", get_Name().c_str());
      return -2;
   }
  //## end cUDPClient::onMain%1090862809.body
}

void cUDPClient::onLeave (INT_T rc)
{
  //## begin cUDPClient::onLeave%1090862810.body preserve=yes
  //## end cUDPClient::onLeave%1090862810.body
}

void cUDPClient::Send (cCSMsg *msg, cCSAddress *address)
{
  //## begin cUDPClient::Send%1090833153.body preserve=yes
   if (_CSComm != NULL) {
      _CSComm->Send(msg, address);
   } else {
      cSystemUtils::Suspend(100);
   }
  //## end cUDPClient::Send%1090833153.body
}

void cUDPClient::Receive (cCSMsg &msg, cCSAddress *client_address, ULONG_T tmo)
{
  //## begin cUDPClient::Receive%1090840951.body preserve=yes
   if (_CSComm != NULL) {
      _CSComm->Receive(msg, client_address);
   } else {
      cSystemUtils::Suspend(100);
   }
  //## end cUDPClient::Receive%1090840951.body
}

ULONG_T cUDPClient::GetMessage (PTR_T buf, ULONG_T buf_size, ULONG_T tmo, ULONG_T channel)
{
  //## begin cUDPClient::GetMessage%1090868763.body preserve=yes
   cBlockQueue * block_queue = BlockQueue(channel);
   if (block_queue != NULL) {
      BLOCK_T * block = block_queue->GetBlock(tmo);
      if (block != NULL) {
         ULONG_T size = block->block_size;
         if (buf_size < size) {
            size = buf_size;
         }
         memcpy(buf, block->block, size);
         block_queue->ReleaseBlock(block);
         return size;
      }
   }
   return 0;
  //## end cUDPClient::GetMessage%1090868763.body
}

void cUDPClient::FlushInput (ULONG_T channel)
{
  //## begin cUDPClient::FlushInput%1090946393.body preserve=yes
   cBlockQueue * block_queue = BlockQueue(channel);
   if (block_queue != NULL) {
      block_queue->Flush();
   }
  //## end cUDPClient::FlushInput%1090946393.body
}

cBlockQueue * cUDPClient::BlockQueue (ULONG_T channel)
{
  //## begin cUDPClient::BlockQueue%1090910857.body preserve=yes
   std::map<ULONG_T,cBlockQueue*>::const_iterator i = _BlockQueues.find(channel);
   if (i == _BlockQueues.cend()) {
      cBlockQueue * queue = new cBlockQueue(channel);
      _BlockQueues[channel] = queue;
      return queue;
   } else {
      return (*i).second;   
   }
  //## end cUDPClient::BlockQueue%1090910857.body
}

void cUDPClient::Dispatch (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cUDPClient::Dispatch%1090862818.body preserve=yes
   PTR_T block = msg->AppData();
   ULONG_T block_size = msg->AppDataSize();
   cBlockQueue * block_queue = BlockQueue(0);
   if (block_queue != NULL) {
      block_queue->SetBlock(block, block_size);
   }
  //## end cUDPClient::Dispatch%1090862818.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cUDPClient::get_Terminated () const
{
  //## begin cUDPClient::get_Terminated%41053F1302AF.get preserve=no
  return _Terminated;
  //## end cUDPClient::get_Terminated%41053F1302AF.get
}

void cUDPClient::set_Terminated (BOOL_T value)
{
  //## begin cUDPClient::set_Terminated%41053F1302AF.set preserve=no
  _Terminated = value;
  //## end cUDPClient::set_Terminated%41053F1302AF.set
}

STRING_T cUDPClient::get_Name () const
{
   return _Name;
}

void cUDPClient::set_Name (STRING_T value)
{
   _Name = value;
}

// Additional Declarations
  //## begin cUDPClient%4104CB250157.declarations preserve=yes
  //## end cUDPClient%4104CB250157.declarations

//## begin module%4104CB250157.epilog preserve=yes
//## end module%4104CB250157.epilog
