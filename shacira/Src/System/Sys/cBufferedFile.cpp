//## begin module%440803760014.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440803760014.cm

//## begin module%440803760014.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440803760014.cp

//## Module: cBufferedFile%440803760014; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cBufferedFile.cpp

//## begin module%440803760014.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%440803760014.additionalIncludes

//## begin module%440803760014.includes preserve=yes
//## end module%440803760014.includes

// cBufferedFile
#include "System/Sys/cBufferedFile.h"
//## begin module%440803760014.additionalDeclarations preserve=yes
#define TEXT_BUFFER_SIZE       0x4000
#define OUT_BUFFER_SIZE        0x4000
static char _Text[TEXT_BUFFER_SIZE] = {0};
static char _Buffer[TEXT_BUFFER_SIZE] = {0};
//## end module%440803760014.additionalDeclarations


// Class cBufferedFile 

cBufferedFile::cBufferedFile()
  //## begin cBufferedFile::cBufferedFile%.hasinit preserve=no
  //## end cBufferedFile::cBufferedFile%.hasinit
  //## begin cBufferedFile::cBufferedFile%.initialization preserve=yes
  //## end cBufferedFile::cBufferedFile%.initialization
{
  //## begin cBufferedFile::cBufferedFile%.body preserve=yes
   memset(_Buffer, 0, sizeof(_Buffer));
  //## end cBufferedFile::cBufferedFile%.body
}

cBufferedFile::cBufferedFile(const cBufferedFile &right)
  //## begin cBufferedFile::cBufferedFile%copy.hasinit preserve=no
  //## end cBufferedFile::cBufferedFile%copy.hasinit
  //## begin cBufferedFile::cBufferedFile%copy.initialization preserve=yes
  //## end cBufferedFile::cBufferedFile%copy.initialization
{
  //## begin cBufferedFile::cBufferedFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBufferedFile::cBufferedFile%copy.body
}


cBufferedFile::~cBufferedFile()
{
  //## begin cBufferedFile::~cBufferedFile%.body preserve=yes
   memset(_Buffer, 0, sizeof(_Buffer));
  //## end cBufferedFile::~cBufferedFile%.body
}



//## Other Operations (implementation)
STRING_T cBufferedFile::Buffer ()
{
  //## begin cBufferedFile::Buffer%1141375553.body preserve=yes
   return _Buffer;
  //## end cBufferedFile::Buffer%1141375553.body
}

BOOL_T cBufferedFile::Printf (CONST_STRING_T fmt_str, ... )
{
  //## begin cBufferedFile::Printf%1141375554.body preserve=yes
   memset(_Text, 0, sizeof(_Text));
   va_list args;
   va_start(args, fmt_str);
   int nprint = _vsnprintf(_Text, TEXT_BUFFER_SIZE, fmt_str, args);
   if (nprint == -1) {
      ErrorPrintf("text buffer of %d too small to format string (%s,%d)\n", TEXT_BUFFER_SIZE, __FILE__, __LINE__);
      return false;
   }
   va_end(args);
   nprint = _snprintf(_Buffer, OUT_BUFFER_SIZE, "%s%s", _Buffer, _Text);
   if (nprint == -1) {
      ErrorPrintf("output buffer size of %d too small to format string (%s,%d)\n", OUT_BUFFER_SIZE, __FILE__, __LINE__);
      return false;
   }
   return true;
  //## end cBufferedFile::Printf%1141375554.body
}

// Additional Declarations
  //## begin cBufferedFile%440803760014.declarations preserve=yes
  //## end cBufferedFile%440803760014.declarations

//## begin module%440803760014.epilog preserve=yes
//## end module%440803760014.epilog
