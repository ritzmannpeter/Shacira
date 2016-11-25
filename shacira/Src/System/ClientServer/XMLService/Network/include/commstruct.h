
#ifndef _commstruct_h_
#define _commstruct_h_

#include "comm.h"
#include "bytebuffer.h"

class COMM_EXPORT cCommStruct
{
public:
   cCommStruct();
   virtual ~cCommStruct();
   virtual int serialize(cByteBuffer & buffer) = 0;
   inline unsigned long requestId() const {return _requestId;};
   inline void setRequestId(unsigned long requestId) {_requestId = requestId;};
   void setRequestId(const OCTET_T * data);
   void setRequestId();
protected:
   void toRid(unsigned char * rid, unsigned long id);
   unsigned long fromRid(const unsigned char * rid);
protected:
   unsigned long _requestId;
   static unsigned long _currentRequestId;
};

#endif // _commstruct_h_
