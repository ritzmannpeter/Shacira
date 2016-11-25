
#include "FirstHeader.h"
#include "cEM17Data.h"
#include "cFMFatFile.h"

cEM17Data::cEM17Data(cFMFatFile * file, cSubfile * subfile, void * data, ULONG_T data_size)
{
   _File = file;
   _Subfile = subfile;
   _DataSize = data_size;
   _Data = cSystemUtils::Alloc(_DataSize);
   memcpy(_Data, data, data_size);
   _Subfile->SetEM17Data(this);
}

cEM17Data::~cEM17Data()
{
   cSystemUtils::Free(_Data);
}

void cEM17Data::Print(STRING_T & doc)
{
char temp_buf[0x2000] = {0};
   sprintf(temp_buf, "euromap 17 data length %d\n",
           _DataSize);
   doc += temp_buf;
}

ULONG_T cEM17Data::DataSize()
{
   return _DataSize;
}

void * cEM17Data::Data()
{
   return _Data;
}

