
#ifndef _cRegister_h_
#define _cRegister_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
class cFMFatFile;

class cRegister {
public:
   cRegister(cFMFatFile * file, cSubfile * subfile, REGISTER_T * reg);
   virtual ~ cRegister();
   void Print(STRING_T & doc);
   LONG_T LongValue(LONG_T index = -1);
   DOUBLE_T DoubleValue(LONG_T index = -1);
   STRING_T StringValue(LONG_T index = -1);
public:
   ULONG_T _RegNo;
   ULONG_T _SubfileId;
   LONG_VECTOR_T _Values;
   ULONG_T _RegType;
   ULONG_T _Size;
   ULONG_T _ValueSize;
   ULONG_T _Elements;
   STRING_T _Text;
   UCHAR_T _Precision;
   BOOL_T _HasDescription;
private:
   cFMFatFile * _File;
   cSubfile * _Subfile;
};

#endif





