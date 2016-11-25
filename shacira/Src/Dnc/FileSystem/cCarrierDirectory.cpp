//## begin module%3B98FC59007F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FC59007F.cm

//## begin module%3B98FC59007F.cp preserve=no
//## end module%3B98FC59007F.cp

//## Module: cCarrierDirectory%3B98FC59007F; Pseudo Package body
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cCarrierDirectory.cpp

//## begin module%3B98FC59007F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98FC59007F.additionalIncludes

//## begin module%3B98FC59007F.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "errcode.h"
#include "iqtdev.h"
#include "devdisk.h"
#include "fmfat.h"
#include "fmt2.h"
#include "fmt1.h"
#include "fx25.h"

//## end module%3B98FC59007F.includes

// cCarrierDirectory
#include "Dnc\FileSystem\cCarrierDirectory.h"
// cCarrier
#include "Dnc\Carrier\cCarrier.h"
//## begin module%3B98FC59007F.additionalDeclarations preserve=yes

#ifdef __cplusplus
extern "C" {
#endif

static cCarrier * _CarrierRef = NULL;

int BASIC_Check()
{
   if (_CarrierRef == NULL) return -1;
   return _CarrierRef->Size();
}

int BASIC_Read(long address, long size, void * buffer)
{
   if (_CarrierRef == NULL) return -1;
   int nread = _CarrierRef->Read(buffer, address, size);
   if (nread == size) {
      return 0;
   } else {
      return nread;
   }
}

int BASIC_Write(long address, long size, void * buffer)
{
   if (_CarrierRef == NULL) return -1;
   int nwrite = _CarrierRef->Write(buffer, address, size);
   if (nwrite == size) {
      return 0;
   } else {
      return nwrite;
   }
}

#define DRIVE_NO     DISK_DRV_EEP1

#define MAX_FMT2_FILES  3

#define MIN_HEADER_LEN	78
#define MAX_HEADER_LEN	252

long CarrierPos(int fileno, int object)
{
   switch (object) {
   case ID_SUBHEADER:
      switch (fileno) {
      case 1: return ADR_SUBHEADER_1;
      case 2: return ADR_SUBHEADER_2;
      case 3: return ADR_SUBHEADER_3;
      }
   case ID_LIST:
      switch (fileno) {
      case 1: return ADR_LIST_1;
      case 2: return ADR_LIST_2;
      case 3: return ADR_LIST_3;
      }
   }
   return -42L;
}

LOCAL USR_BYTE Checksum(USR_BYTE * buffer, int src, int offs)
{  USR_BYTE val;
   USR_BYTE checksum;
   long i;

   checksum = 0;
   For (i=src; i<src+offs; i++) Do
      val = buffer[i];
      checksum ^= val;
   Endfor
   return checksum;
}

LOCAL int FMT2_TestChecksum()
{
   int err;
   unsigned char temp_buf[4096] = {0};
   USR_BYTE checksum1 = 0, checksum2 = 0, checksum3 = 0,
            checksum = 0;
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_1, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   If (checksum1 != checksum) Then
      return FMT2_CHECKSUM1;
   Endif
   if ((err = BASIC_Read(0x3f, 1, &checksum2)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_2, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   If (checksum2 != checksum) Then
      return FMT2_CHECKSUM2;
   Endif
   if ((err = BASIC_Read(0x57, 1, &checksum3)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_3, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   If (checksum3 != checksum) Then
      return FMT2_CHECKSUM3;
   Endif
   return USR_NO_ERROR;
}

LOCAL int FMT2_2F_TestChecksum()
{
   int err;
   unsigned char temp_buf[4096] = {0};
   USR_BYTE checksum1 = 0, checksum = 0;
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_2F, DATA_SIZE_2F, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_2F);
   If (checksum1 != checksum) Then
      return FMT2_2F_CHECKSUM;
   Endif
   return USR_NO_ERROR;
}

LOCAL int FMT2_3F_TestChecksum()
{
   int err;
   unsigned char temp_buf[4096] = {0};
   USR_BYTE checksum1 = 0, checksum = 0;
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_3F, DATA_SIZE_3F, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_3F);
   If (checksum1 != checksum) Then
      return FMT2_3F_CHECKSUM;
   Endif
   return USR_NO_ERROR;
}

static int DeviceError(int hnd)
{
   PARAMETER device_error;
   DevGetParam(hnd, DEV_ID_ERROR, &device_error);
   return (int)device_error;
}

#ifdef __cplusplus
}
#endif

//## end module%3B98FC59007F.additionalDeclarations


// Class cCarrierDirectory 


cCarrierDirectory::cCarrierDirectory()
  //## begin cCarrierDirectory::cCarrierDirectory%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierDirectory::cCarrierDirectory%.hasinit
  //## begin cCarrierDirectory::cCarrierDirectory%.initialization preserve=yes
  //## end cCarrierDirectory::cCarrierDirectory%.initialization
{
  //## begin cCarrierDirectory::cCarrierDirectory%.body preserve=yes
  //## end cCarrierDirectory::cCarrierDirectory%.body
}

cCarrierDirectory::cCarrierDirectory(const cCarrierDirectory &right)
  //## begin cCarrierDirectory::cCarrierDirectory%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierDirectory::cCarrierDirectory%copy.hasinit
  //## begin cCarrierDirectory::cCarrierDirectory%copy.initialization preserve=yes
  //## end cCarrierDirectory::cCarrierDirectory%copy.initialization
{
  //## begin cCarrierDirectory::cCarrierDirectory%copy.body preserve=yes
  //## end cCarrierDirectory::cCarrierDirectory%copy.body
}

cCarrierDirectory::cCarrierDirectory (cFileSystem *file_system, CONST_STRING_T path)
  //## begin cCarrierDirectory::cCarrierDirectory%999877036.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierDirectory::cCarrierDirectory%999877036.hasinit
  //## begin cCarrierDirectory::cCarrierDirectory%999877036.initialization preserve=yes
   , cDirectory(file_system, path)
  //## end cCarrierDirectory::cCarrierDirectory%999877036.initialization
{
  //## begin cCarrierDirectory::cCarrierDirectory%999877036.body preserve=yes
   _Carrier = new cCarrier;
   _CarrierRef = _Carrier;
   DISK_INIT_BLOCK disk_init_block;
   disk_init_block.DebugMask = 0;
   DevInit(DEV_MAIN, NULL);
   DevInit(DEV_DISK, &disk_init_block);
  //## end cCarrierDirectory::cCarrierDirectory%999877036.body
}


cCarrierDirectory::~cCarrierDirectory()
{
  //## begin cCarrierDirectory::~cCarrierDirectory%.body preserve=yes
   DELETE_OBJECT(cCarrier, _Carrier)
  //## end cCarrierDirectory::~cCarrierDirectory%.body
}



//## Other Operations (implementation)
int cCarrierDirectory::Refresh ()
{
  //## begin cCarrierDirectory::Refresh%999877039.body preserve=yes
   _Format = FORMAT_UNKNOWN;
   RemoveFiles();
   int size = _Carrier->Size();
   switch (size) {
   case 4:
   case 8:
      _Format = FMT2Refresh();
      if (_Format == FORMAT_UNKNOWN) _Format = FMT1Refresh();
      if (_Format == FORMAT_UNKNOWN) _Format = FX25Refresh();
      break;
   case 32:
   case 64:
      _Format = FMFatRefresh();
      break;
   default:
      break;
   }
   return _Format;
  //## end cCarrierDirectory::Refresh%999877039.body
}

int cCarrierDirectory::FMFatRefresh ()
{
  //## begin cCarrierDirectory::FMFatRefresh%1000119061.body preserve=yes
   int err, i;
   int dir_entries;
   DISK_PARAM_BLOCK param;
   USR_HANDLE hnd = 0;
   PARAMETER size = 0L;
   DISK_DIR_STRUCT * dev_dir;
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = DISK_OP_READ;
   param.FileName = NULL;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      return FORMAT_UNKNOWN;
   }
   if ((err = DevGetParam(hnd, DISK_ID_SIZE, &size)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      return FORMAT_UNKNOWN;
	}
   if (size == 0L) Then
      DevClose(hnd);
      return FORMAT_UNKNOWN;
	}
   dir_entries = (USR_WORD)(size / sizeof(DISK_DIR_STRUCT));
   dev_dir = (DISK_DIR_STRUCT*)malloc((USR_WORD)size);
   if (dev_dir == NULL) Then
      DevClose(hnd);
      int device_error = ERR_DRAM_ALLOC;
      return FORMAT_UNKNOWN;
   } else {
      memset(dev_dir, 0, size);
   }
   if ((err = DevSetParam(hnd, DISK_ID_FILEPOS , 0L)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      free(dev_dir);
      return FORMAT_UNKNOWN;
   }
   if ((err = DevRead(hnd, (char*)dev_dir, (int)size, NULL, (TIME)0)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      free(dev_dir);
      return FORMAT_UNKNOWN;
   } else {
      DevClose(hnd);
   }
   for (i=0; i<dir_entries; i++) {
      cFMFatFile * file = new cFMFatFile(this, dev_dir[i].FileName);
      _Files[dev_dir[i].FileName] = file;
   }
   free(dev_dir);
   return FMFAT;
  //## end cCarrierDirectory::FMFatRefresh%1000119061.body
}

int cCarrierDirectory::FMT2Refresh ()
{
  //## begin cCarrierDirectory::FMT2Refresh%1000119062.body preserve=yes
   int i, err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER subheader;
   long carrierpos;
   if (FMT2_TestChecksum() != USR_NO_ERROR) return FORMAT_UNKNOWN;
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
   for (i=0; i<MAX_FMT2_FILES; i++) {
      carrierpos = CarrierPos(i + 1, ID_SUBHEADER);
      if ((err = BASIC_Read(carrierpos, sizeof(subheader),
                              (char*)&subheader)) != USR_NO_ERROR) return err;
      if (subheader.Date[1] != 0) {
         char file_name[128] = {0};
         sprintf(file_name, "OLDCAR.%03d", i + 1);
         cFMT2File * file = new cFMT2File(this, file_name);
         _Files[file_name] = file;
      }
   }
   return FMT2;
  //## end cCarrierDirectory::FMT2Refresh%1000119062.body
}

int cCarrierDirectory::FMT1Refresh ()
{
  //## begin cCarrierDirectory::FMT1Refresh%1000119063.body preserve=yes
return FORMAT_UNKNOWN;
   return FMT1;
  //## end cCarrierDirectory::FMT1Refresh%1000119063.body
}

int cCarrierDirectory::FX25Refresh ()
{
  //## begin cCarrierDirectory::FX25Refresh%1000119064.body preserve=yes
return FORMAT_UNKNOWN;
   return FX25;
  //## end cCarrierDirectory::FX25Refresh%1000119064.body
}

// Additional Declarations
  //## begin cCarrierDirectory%3B98FC59007F.declarations preserve=yes
  //## end cCarrierDirectory%3B98FC59007F.declarations

//## begin module%3B98FC59007F.epilog preserve=yes
//## end module%3B98FC59007F.epilog
