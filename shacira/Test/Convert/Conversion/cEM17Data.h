
#ifndef _cEM17Data_h_
#define _cEM17Data_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
class cFMFatFile;

class cEM17Data {
public:
   cEM17Data(cFMFatFile * file, cSubfile * subfile, void * data, ULONG_T data_size);
   virtual ~ cEM17Data();
   void Print(STRING_T & doc);
   ULONG_T DataSize();
   void * Data();
private:
   cFMFatFile * _File;
   ULONG_T _DataSize;
   void * _Data;
   cSubfile * _Subfile;
};

#endif





