
#ifndef _cTransportHandler_h
#define _cTransportHandler_h

class cTransportHandler
{
public:
   cTransportHandler();
   virtual ~cTransportHandler();
   virtual int SendBuffer(const unsigned char * buffer, unsigned long buffer_length) = 0;
   virtual int ReceiveBuffer(unsigned char * buffer, unsigned long buffer_size, int timeout) = 0;
};

#endif
