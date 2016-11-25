
#ifndef cStringBuffer_h
#define cStringBuffer_h 1

#ifdef lassma
class cSHFile;
#endif

#include <string>

class cStringBuffer
{
public:
   cStringBuffer(const char * path);
   ~cStringBuffer();
   cStringBuffer & operator+= (const std::string & str)
   {
      _Output = str;
      Update();
      return *this;
   };
   cStringBuffer & operator+= (const char* s)
   {
      _Output = s;
      Update();
      return *this;
   };
   cStringBuffer & operator+= (char c)
   {
      _Output = c;
      Update();
      return *this;
   };
   cStringBuffer & operator= (const std::string & str)
   {
      Reset();
      _Output = str;
      Update();
      return *this;
   };
   cStringBuffer & operator= (const char* s)
   {
      Reset();
      _Output = s;
      Update();
      return *this;
   };
   cStringBuffer & operator= (char c)
   {
      Reset();
      _Output = c;
      Update();
      return *this;
   };
   unsigned long size();
protected:
   void Reset();
   void Update();
   unsigned long Size();
protected:
   std::string _Path;
   std::string _Output;
   unsigned long _Size;
   char _TempPath[MAX_PATH + 10];
   char _TempFile[MAX_PATH + 10];
#ifdef lassma
   cSHFile * _File;
#endif
};

#endif
