
#ifndef _bytebuffer_h_
#define _bytebuffer_h_

#include "comm.h"
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

class COMM_EXPORT cByteBuffer
{
protected:
   struct buffer {
      long refCount;
      OCTET_T * data;
   };
public:
   cByteBuffer();
   cByteBuffer(const OCTET_T * data, LENGTH_T size);
   cByteBuffer(const cByteBuffer & right);
   cByteBuffer & operator= (const cByteBuffer & right);
   void append(const OCTET_T * data, LENGTH_T size);
   void append(const char * data, LENGTH_T size);
   virtual ~cByteBuffer();
   LENGTH_T  size() const;
   const OCTET_T * data() const;
   inline const char * c_str() const {return (const char *)data();};
   static int allocatedBuffers();
   void show(const char * header) const;
   static void show(const char * header, const OCTET_T * data, LENGTH_T size);
   static void setVerbose(bool state);
private:
   LENGTH_T _size;
   struct buffer * _buffer;
   static unsigned char _emptyData;
   static int _allocatedBuffers;
   static bool _verbose;
};

#endif // _bytebuffer_h_
