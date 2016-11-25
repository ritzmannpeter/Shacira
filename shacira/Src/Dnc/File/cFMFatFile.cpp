//## begin module%3B9C9CC3008F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9CC3008F.cm

//## begin module%3B9C9CC3008F.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9CC3008F.cp

//## Module: cFMFatFile%3B9C9CC3008F; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMFatFile.cpp

//## begin module%3B9C9CC3008F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9C9CC3008F.additionalIncludes

//## begin module%3B9C9CC3008F.includes preserve=yes
//## end module%3B9C9CC3008F.includes

// cFMFatFile
#include "Dnc/File/cFMFatFile.h"
//## begin module%3B9C9CC3008F.additionalDeclarations preserve=yes
static int Header(FILE_HEADER_T * header, void * object)
{
   printf("Header size %d\n", header->HeaderSize);
   return 0;
}

static int SubfileTab(SUBFILE_TAB_T * subfile_tab, void * object)
{
   printf("Subfile Tabelle\n");
   return 0;
}

static int Subfile(SUBFILE_T * subfile, void * object)
{
   printf("Subfile %s size %ld offset %ld\n", subfile->description,
                                              subfile->size,
                                              subfile->offset);
   return 0;
}

static int Register(REGISTER_T * reg, void * object)
{
   int dim = DIM(reg);
   printf("Register %d dim %d\n", reg->reg_no, dim);
   return 0;
}

static void Subst(char * buf, char c, char subst, int len)
{
   int i;
   for (i=0; i<len; i++) {
      if (buf[i] == c) buf[i] = subst;
   }
}

static int Text(TEXT_T * text, void * object)
{
   char buf[4096] = {0};
   printf("Text %d, size %d, length %d\n", text->id, text->size, text->length);
   memcpy(buf, text->buffer, text->size);
   Subst(buf, ' ', '.', sizeof(buf));
   printf("%s\n", buf);
   return 0;
}

static int Heatgroup(HEATGROUP_T * heatgroup, void * object)
{
   printf("Heatgroup %d stored zones %d\n", heatgroup->heatgroup, heatgroup->stored_zones);
   return 0;
}

static int Zone(ZONE_T * zone, void * object)
{
   printf("heat zone [%d,%d]\n", zone->zone_id, zone->unit_id);
   return 0;
}

static FMFAT_BUFFER_CALLBACK_MODULE_T CallbackModule =
{
   NULL,
   Header,
   SubfileTab,
   Subfile,
   Register,
   Text,
   Heatgroup,
   Zone
};

//## end module%3B9C9CC3008F.additionalDeclarations


// Class cFMFatFile 



cFMFatFile::cFMFatFile()
  //## begin cFMFatFile::cFMFatFile%.hasinit preserve=no
      : _FBuf(NULL), _FATBuf(NULL)
  //## end cFMFatFile::cFMFatFile%.hasinit
  //## begin cFMFatFile::cFMFatFile%.initialization preserve=yes
  //## end cFMFatFile::cFMFatFile%.initialization
{
  //## begin cFMFatFile::cFMFatFile%.body preserve=yes
  //## end cFMFatFile::cFMFatFile%.body
}

cFMFatFile::cFMFatFile(const cFMFatFile &right)
  //## begin cFMFatFile::cFMFatFile%copy.hasinit preserve=no
      : _FBuf(NULL), _FATBuf(NULL)
  //## end cFMFatFile::cFMFatFile%copy.hasinit
  //## begin cFMFatFile::cFMFatFile%copy.initialization preserve=yes
  //## end cFMFatFile::cFMFatFile%copy.initialization
{
  //## begin cFMFatFile::cFMFatFile%copy.body preserve=yes
  //## end cFMFatFile::cFMFatFile%copy.body
}

cFMFatFile::cFMFatFile (TOOLFILE_HEADER_T *file_header, cToolFileSystem *file_system)
  //## begin cFMFatFile::cFMFatFile%1000119065.hasinit preserve=no
      : _FBuf(NULL), _FATBuf(NULL)
  //## end cFMFatFile::cFMFatFile%1000119065.hasinit
  //## begin cFMFatFile::cFMFatFile%1000119065.initialization preserve=yes
   , cToolFile(file_header, file_system)
  //## end cFMFatFile::cFMFatFile%1000119065.initialization
{
  //## begin cFMFatFile::cFMFatFile%1000119065.body preserve=yes
  //## end cFMFatFile::cFMFatFile%1000119065.body
}


cFMFatFile::~cFMFatFile()
{
  //## begin cFMFatFile::~cFMFatFile%.body preserve=yes
   if (_FATBuf != NULL) {
      DeleteFatBuffer(_FATBuf);
      DeleteFileBuffer(_FBuf);
   }
  //## end cFMFatFile::~cFMFatFile%.body
}



//## Other Operations (implementation)
void cFMFatFile::Save (cToolFileSystem *file_system)
{
  //## begin cFMFatFile::Save%1062507891.body preserve=yes
  //## end cFMFatFile::Save%1062507891.body
}

// Additional Declarations
  //## begin cFMFatFile%3B9C9CC3008F.declarations preserve=yes
  //## end cFMFatFile%3B9C9CC3008F.declarations

//## begin module%3B9C9CC3008F.epilog preserve=yes
//## end module%3B9C9CC3008F.epilog
