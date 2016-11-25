
#include "FirstHeader.h"
#include "System/cTimeObject.h"
#include "System/Sys/cSHFile.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Sys/cStringBuffer.h"

cStringBuffer::cStringBuffer(const char * path) : _Path(path), _Size(0)
{
   DWORD rc1 = GetTempPath(sizeof(_TempPath), _TempPath);
   if (rc1 > 0) {
      UINT rc2 = GetTempFileName(_TempPath, "", 42, _TempFile);
      if (rc2 == 42) {
         const char * fn = _TempFile;
         int dummy = 0;
      }  
   }
}

cStringBuffer::~cStringBuffer()
{
   const char * fn1 = _TempFile;
   const char * fn2 = _Path.c_str();
   int rc = remove(_Path.c_str());
   rc = rename(_TempFile, _Path.c_str());
   rc = remove(_TempFile);
   int dummy = 0;
#ifdef lassma
   if (_File) {
      _File->Close();
      delete _File;
   }
#endif
}

unsigned long cStringBuffer::size()
{
   return _Size;
}

void cStringBuffer::Reset()
{
   int rc = remove(_Path.c_str());
   _Size = 0;
#ifdef lassma
   _File = new cSHFile(_Path.c_str());
   _File->Open(FILE_ACCESS_APPEND);
#endif
}

void cStringBuffer::Update()
{
   long nwrite = 0;
   if (!_Output.empty()) {
      FILE * stream = fopen(_TempFile, "a");
      if (stream != NULL) {
         fprintf(stream, "%s", _Output.c_str());
         fclose(stream);
      }
      _Size += _Output.length();
      _Output.clear();
#ifdef lassma
      nwrite = _file->Write((void*)_output.c_str(), _output.length());
      if (nwrite > 0) {
         _size += nwrite;
      }
#endif
   }
}

unsigned long cStringBuffer::Size()
{
   return _Size;
}


