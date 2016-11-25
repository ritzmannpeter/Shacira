//## begin module%3BA1C07F01D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA1C07F01D3.cm

//## begin module%3BA1C07F01D3.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA1C07F01D3.cp

//## Module: cFreeFile%3BA1C07F01D3; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFreeFile.cpp

//## begin module%3BA1C07F01D3.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BA1C07F01D3.additionalIncludes

//## begin module%3BA1C07F01D3.includes preserve=yes
//## end module%3BA1C07F01D3.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"
// cFreeFile
#include "Dnc/File/cFreeFile.h"
//## begin module%3BA1C07F01D3.additionalDeclarations preserve=yes
//## end module%3BA1C07F01D3.additionalDeclarations


// Class cFreeFile 


cFreeFile::cFreeFile()
  //## begin cFreeFile::cFreeFile%.hasinit preserve=no
  //## end cFreeFile::cFreeFile%.hasinit
  //## begin cFreeFile::cFreeFile%.initialization preserve=yes
  //## end cFreeFile::cFreeFile%.initialization
{
  //## begin cFreeFile::cFreeFile%.body preserve=yes
   _FileFormat = FMT_FREE;
   _FileVersion = VERS_FREE;
  //## end cFreeFile::cFreeFile%.body
}

cFreeFile::cFreeFile(const cFreeFile &right)
  //## begin cFreeFile::cFreeFile%copy.hasinit preserve=no
  //## end cFreeFile::cFreeFile%copy.hasinit
  //## begin cFreeFile::cFreeFile%copy.initialization preserve=yes
  //## end cFreeFile::cFreeFile%copy.initialization
{
  //## begin cFreeFile::cFreeFile%copy.body preserve=yes
  //## end cFreeFile::cFreeFile%copy.body
}

cFreeFile::cFreeFile (CONST_STRING_T name, cFileSystem *file_system)
  //## begin cFreeFile::cFreeFile%1000456408.hasinit preserve=no
  //## end cFreeFile::cFreeFile%1000456408.hasinit
  //## begin cFreeFile::cFreeFile%1000456408.initialization preserve=yes
   : cFile(name, file_system)
  //## end cFreeFile::cFreeFile%1000456408.initialization
{
  //## begin cFreeFile::cFreeFile%1000456408.body preserve=yes
   _FileFormat = FMT_FREE;
   _FileVersion = VERS_FREE;
  //## end cFreeFile::cFreeFile%1000456408.body
}


cFreeFile::~cFreeFile()
{
  //## begin cFreeFile::~cFreeFile%.body preserve=yes
  //## end cFreeFile::~cFreeFile%.body
}


// Additional Declarations
  //## begin cFreeFile%3BA1C07F01D3.declarations preserve=yes
  //## end cFreeFile%3BA1C07F01D3.declarations

//## begin module%3BA1C07F01D3.epilog preserve=yes
//## end module%3BA1C07F01D3.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cFreeFile::GetVariableValue%1000456409.body preserve=no
   int err = 0;
   if (_Size > 0) {
      if (strcmp(name, "FIRST_LINE") == 0) {
         _FilePos = 0;
         char * buf_ptr = &((char*)_FileBuffer->Memory())[_FilePos];
         long line_size = 0;
         for (line_size = 0; (line_size + _FilePos) < _Size; line_size++) {
            if (buf_ptr[line_size] == '\r') {
               if (buf_ptr[line_size+1] == '\n') break;
            }
         }
         value = string(buf_ptr, line_size);
         _FilePos += (line_size + 2);
         return 0;
      } else if (strcmp(name, "NEXT_LINE") == 0) {
         if (_FilePos >= _Size) return FILE_END_OF_FILE;
         char * buf_ptr = &((char*)_FileBuffer->Memory())[_FilePos];
         long line_size = 0;
         for (line_size = 0; (line_size + _FilePos) < _Size; line_size++) {
            if (buf_ptr[line_size] == '\r') {
               if (buf_ptr[line_size+1] == '\n') break;
            }
         }
         value = string(buf_ptr, line_size);
         _FilePos += (line_size + 2);
         return 0;
      } else {
         return FILE_INVALID_VARIABLE;
      }
   } else {
      return FILE_END_OF_FILE;
   }
//## end cFreeFile::GetVariableValue%1000456409.body

//## begin cFreeFile::GetTime%1000456411.body preserve=no
   return _FileSystem->GetTime(_Name.c_str());
//## end cFreeFile::GetTime%1000456411.body

#endif
