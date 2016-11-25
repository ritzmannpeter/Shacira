
#ifndef _cTextVar_h_
#define _cTextVar_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
#include "cFMFatFile.h"

class cTextVar {
public:
   cTextVar(cFMFatFile * file, cSubfile * subfile, TEXT_T * text);
   virtual ~cTextVar();
   STRING_T Text();
   void Print(STRING_T & doc);
public:
   ULONG_T _TextId;
   ULONG_T _SubfileId;
   ULONG_T _Columns;
   ULONG_T _Rows;
   ULONG_T _Size;
   STRING_T _Text;
private:
   cFMFatFile * _File;
   cSubfile * _Subfile;
};

#endif





