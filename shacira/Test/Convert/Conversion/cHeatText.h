
#ifndef _cHeatText_h_
#define _cHeatText_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
class cFMFatFile;

class cHeatGroup;
class cHeatText {
public:
   cHeatText(cFMFatFile * file, cSubfile * sub_file, int reg_no, int ind1, int ind2, const char * text);
   virtual ~cHeatText();
   void Print(STRING_T & doc);
   STRING_T Text();
public:
   cSubfile * _Subfile;
   int _RegNo;
   int _Ind1;
   int _Ind2;
   STRING_T _Text;
private:
   cFMFatFile * _File;
};

#endif
