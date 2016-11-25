
#include "FirstHeader.h"
#include "cTextVar.h"
#include "cFMFatFile.h"

cTextVar::cTextVar(cFMFatFile * file, cSubfile * subfile, TEXT_T * text)
{
   _File = file;
   _Subfile = subfile;
   _TextId = text->id;
   _SubfileId = text->subfile_id;
   _Columns = text->cols;
   _Rows = text->rows;
   _Size = text->size;
   _Text = text->buffer;
   subfile->AddTextVar(this);
}

cTextVar::~cTextVar()
{
}

STRING_T cTextVar::Text()
{
   return _Text;
}

void cTextVar::Print(STRING_T & doc)
{
static char temp_buf[0x2000] = {0};
   sprintf(temp_buf, "textvar %d rows %d cols %d value:\n%s\n",
           _TextId, _Rows, _Columns, _Text.c_str());
   doc += temp_buf;
}




