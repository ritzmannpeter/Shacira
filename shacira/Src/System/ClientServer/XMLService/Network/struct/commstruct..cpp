
#include "commstruct.h"

unsigned long cCommStruct::_currentRequestId = 0;

cCommStruct::cCommStruct()
   : _requestId(0)
{
}

cCommStruct::~cCommStruct()
{
}

void cCommStruct::setRequestId()
{
   _requestId = _currentRequestId++;
}

void cCommStruct::setRequestId(const OCTET_T * data)
{
   _requestId = fromRid(data);
}

void cCommStruct::toRid(unsigned char * rid, unsigned long id)
{
   rid[0] = (unsigned char)(id & 0x000000ff);
   rid[1] = (unsigned char)((id >> 8) & 0x000000ff);
   rid[2] = (unsigned char)((id >> 16) & 0x000000ff);
   rid[3] = (unsigned char)((id >> 24) & 0x000000ff);
}

unsigned long cCommStruct::fromRid(const unsigned char * rid)
{
   unsigned long id = 0;
   unsigned long temp = rid[0];
   id |= (temp);
   temp = rid[1];
   id |= (temp << 8);
   temp = rid[2];
   id |= (temp << 16);
   temp = rid[3];
   id |= (temp << 24);
   return id;
}


