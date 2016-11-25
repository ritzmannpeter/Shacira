
#include "cServiceHandler.h"

cServiceHandler::cServiceHandler(cConnectionHandler * ch, cFrameHandler * fh, bool hold_connection)
{
   _HoldConnection = hold_connection;
_HoldConnection = true;
   _ConnectionHandler = ch;
   _FrameHandler = fh;
   _TransportHandler = NULL;
}

cServiceHandler::~cServiceHandler()
{
}

bool cServiceHandler::Connect()
{
   while (true) {
      _TransportHandler = _ConnectionHandler->Connect();
      _FrameHandler->SetTransportHandler(_TransportHandler);
      if (_TransportHandler != NULL) {
         return true;
      }
   }
}

void cServiceHandler::Disconnect()
{
   _ConnectionHandler->Disconnect();
}

bool cServiceHandler::Start()
{
   while (true) {
      _TransportHandler = _ConnectionHandler->Listen();
      _FrameHandler->SetTransportHandler(_TransportHandler);
      if (_TransportHandler != NULL) {
         ServiceRequests();
         if (!_HoldConnection) {
            delete _TransportHandler;
         }
      }
   }
}

bool cServiceHandler::Stop()
{
   return true;
}

bool cServiceHandler::ServiceRequests()
{
   unsigned char in_frame[0x100] = {0};
   unsigned char out_frame[0x100] = {0};
   long in_length = 0;
   unsigned long out_length = 0;
   while (true) {
      in_length = _FrameHandler->GetFrame(in_frame, sizeof(in_frame));
      if (in_length >= 0) {
         HandleRequest(&in_frame, in_length, out_frame, &out_length);
         _FrameHandler->SendFrame(out_frame, out_length);
         if (!_HoldConnection) {
            return true;
         }
      } else {
//         return false;
      }
   }
}





