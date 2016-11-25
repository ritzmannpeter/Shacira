//## begin module%3B98FC59007F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FC59007F.cm

//## begin module%3B98FC59007F.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98FC59007F.cp

//## Module: cCarrierFileSystem%3B98FC59007F; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCarrierFileSystem.cpp

//## begin module%3B98FC59007F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98FC59007F.additionalIncludes

//## begin module%3B98FC59007F.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "syntax.h"
#include "errcode.h"
#include "iqtdev.h"
#include "devdisk.h"
#include "fmfat.h"

//## end module%3B98FC59007F.includes

// cCarrierBase
#include "Dnc/Carrier/cCarrierBase.h"
// cCarrierSource
#include "Dnc/FileSystem/cCarrierSource.h"
// cCarrierFileSystem
#include "Dnc/FileSystem/cCarrierFileSystem.h"
//## begin module%3B98FC59007F.additionalDeclarations preserve=yes

#ifdef __cplusplus
extern "C" {
#endif

static cCarrierBase * _CarrierRef = NULL;

int BASIC_Check()
{
   if (_CarrierRef == NULL) return FSYS_NO_CARRIER;
   return _CarrierRef->Size();
}

int BASIC_Read(long address, long size, void * buffer)
{
   if (_CarrierRef == NULL) return FSYS_NO_CARRIER;
   int nread = _CarrierRef->Read(buffer, address, size);
   if (nread == size) {
      return 0;
   } else {
      return nread;
   }
}

int BASIC_Write(long address, long size, void * buffer)
{
   if (_CarrierRef == NULL) return FSYS_NO_CARRIER;
   int nwrite = _CarrierRef->Write(buffer, address, size);
   if (nwrite == size) {
      return 0;
   } else {
      return nwrite;
   }
}

#define DRIVE_NO     DISK_DRV_EEP1

#define MIN_HEADER_LEN	78
#define MAX_HEADER_LEN	252

static int DeviceError(int hnd)
{
   PARAMETER device_error;
   DevGetParam(hnd, DEV_ID_ERROR, &device_error);
   return (int)device_error;
}

long MakeFileTime()
{
   struct tm * act_time = NULL;
	time_t now;
	int year, day, month, hour, sec, min;
	time(&now);
	act_time = localtime(&now);
	year = act_time->tm_year;
	month = act_time->tm_mon + 1;
	day = act_time->tm_mday;
	hour = act_time->tm_hour;
	min = act_time->tm_min;
	sec = act_time->tm_sec;
   return DISK_MAKE_DATE(day, month, year, hour, min, sec);
}

long CarrierFileSize(int hnd)
{
   int err = 0;
   PARAMETER file_size;
   if ((err = DevGetParam(hnd, DISK_ID_SIZE, (PARAMETER*)&file_size)) != USR_NO_ERROR) {
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      return device_error;
   } else {
      return (long)file_size;
   }
}

#ifdef __cplusplus
}
#endif

//## end module%3B98FC59007F.additionalDeclarations


// Class cCarrierFileSystem 


cCarrierFileSystem::cCarrierFileSystem()
  //## begin cCarrierFileSystem::cCarrierFileSystem%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierFileSystem::cCarrierFileSystem%.hasinit
  //## begin cCarrierFileSystem::cCarrierFileSystem%.initialization preserve=yes
  //## end cCarrierFileSystem::cCarrierFileSystem%.initialization
{
  //## begin cCarrierFileSystem::cCarrierFileSystem%.body preserve=yes
  //## end cCarrierFileSystem::cCarrierFileSystem%.body
}

cCarrierFileSystem::cCarrierFileSystem(const cCarrierFileSystem &right)
  //## begin cCarrierFileSystem::cCarrierFileSystem%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierFileSystem::cCarrierFileSystem%copy.hasinit
  //## begin cCarrierFileSystem::cCarrierFileSystem%copy.initialization preserve=yes
  //## end cCarrierFileSystem::cCarrierFileSystem%copy.initialization
{
  //## begin cCarrierFileSystem::cCarrierFileSystem%copy.body preserve=yes
  //## end cCarrierFileSystem::cCarrierFileSystem%copy.body
}

cCarrierFileSystem::cCarrierFileSystem (cCarrierSource *file_source, CONST_STRING_T path)
  //## begin cCarrierFileSystem::cCarrierFileSystem%999877036.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierFileSystem::cCarrierFileSystem%999877036.hasinit
  //## begin cCarrierFileSystem::cCarrierFileSystem%999877036.initialization preserve=yes
   , cFileSystem(path)
  //## end cCarrierFileSystem::cCarrierFileSystem%999877036.initialization
{
  //## begin cCarrierFileSystem::cCarrierFileSystem%999877036.body preserve=yes
   _CarrierRef = _Carrier = file_source->Carrier();
   DISK_INIT_BLOCK disk_init_block;
   disk_init_block.DebugMask = 0;
   DevInit(DEV_MAIN, NULL);
   DevInit(DEV_DISK, &disk_init_block);
  //## end cCarrierFileSystem::cCarrierFileSystem%999877036.body
}


cCarrierFileSystem::~cCarrierFileSystem()
{
  //## begin cCarrierFileSystem::~cCarrierFileSystem%.body preserve=yes
  //## end cCarrierFileSystem::~cCarrierFileSystem%.body
}



//## Other Operations (implementation)
INT_T cCarrierFileSystem::Format (INT_T format)
{
  //## begin cCarrierFileSystem::Format%1000119088.body preserve=yes
   if (format == FMT_FMFAT) {
      USR_HANDLE hnd;
      DISK_PARAM_BLOCK param_block;
      int err = 0;
      param_block.Drive = (PARAMETER)DRIVE_NO;
      param_block.Mode = DISK_OP_DELETE;
      param_block.FileName = NULL;
      if ((err = DevOpen(&hnd, DEV_DISK, &param_block)) != USR_NO_ERROR) {
         return DeviceError(hnd);
      } else {
   		if ((err = DevClose(hnd)) != USR_NO_ERROR) {
            return DeviceError(hnd);
         } else {
            return USR_NO_ERROR;
   		}
      }
   } else {
      return FSYS_FORMAT_NOT_SUPPORTED;
   }
  //## end cCarrierFileSystem::Format%1000119088.body
}

INT_T cCarrierFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cCarrierFileSystem::Directory%1000119089.body preserve=yes
   _Format = FORMAT_UNKNOWN;
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
      throw cError(DeviceError(hnd), 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   if ((err = DevGetParam(hnd, DISK_ID_SIZE, &size)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
	}
   if (size == 0L) Then
      DevClose(hnd);
      _Format = FMT_FMFAT;
      return _Format;
	}
   dir_entries = (USR_WORD)(size / sizeof(DISK_DIR_STRUCT));
   dev_dir = (DISK_DIR_STRUCT*)malloc((USR_WORD)size);
   if (dev_dir == NULL) Then
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
   } else {
      memset(dev_dir, 0, size);
   }
   if ((err = DevSetParam(hnd, DISK_ID_FILEPOS , 0L)) != USR_NO_ERROR) Then
      free(dev_dir);
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   if ((err = DevRead(hnd, (char*)dev_dir, (int)size, NULL, (TIME)0)) != USR_NO_ERROR) Then
      free(dev_dir);
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
   } else {
      DevClose(hnd);
   }
   for (i=0; i<dir_entries; i++) {
      STRING_T file_name = dev_dir[i].FileName;
      file_names.push_back(file_name);
   }
   free(dev_dir);
   _Format = FMT_FMFAT;
   return _Format;
  //## end cCarrierFileSystem::Directory%1000119089.body
}

LONG_T cCarrierFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cCarrierFileSystem::Load%1000119090.body preserve=yes
   USR_HANDLE hnd = 0;
   int err = 0;
   DISK_PARAM_BLOCK param = {0};
   param.Date = (PARAMETER)MakeFileTime();
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = (PARAMETER)DISK_OP_READ;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      throw cError(DeviceError(hnd), 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   int file_size = CarrierFileSize(hnd);
   if (file_size < 0) {
      DevClose(hnd);
      return file_size;
   } else if (file_size == 0) {
      DevClose(hnd);
      return 0;
   } else if (file_size > buf_size) {
      DevClose(hnd);
      return FSYS_BUF_SIZE;
   }
   if ((err = DevRead(hnd, (char*)buf, file_size, NULL, 0)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   DevClose(hnd);
   return file_size;
  //## end cCarrierFileSystem::Load%1000119090.body
}

LONG_T cCarrierFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cCarrierFileSystem::Save%1000119091.body preserve=yes
   USR_HANDLE hnd = 0;
   int err = 0;
   DISK_PARAM_BLOCK param = {0};
   param.Date = (PARAMETER)MakeFileTime();
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = (PARAMETER)(PARAMETER)DISK_OP_WRITE | (PARAMETER)DISK_OP_CREATE;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      throw cError(DeviceError(hnd), 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   if ((err = DevWrite(hnd, (char*)buf, size, NULL, 0)) != USR_NO_ERROR) Then
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(device_error, 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   DevClose(hnd);
   return size;
  //## end cCarrierFileSystem::Save%1000119091.body
}

INT_T cCarrierFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cCarrierFileSystem::Delete%1000119092.body preserve=yes
   int err = 0;
   USR_HANDLE hnd;
   DISK_PARAM_BLOCK  param;
	param.Drive = (PARAMETER) DRIVE_NO;
   param.Mode = DISK_OP_DELETE;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) != USR_NO_ERROR) {
		return DeviceError(hnd);
   } else {
      DevClose(hnd);
      return USR_NO_ERROR;
   }
  //## end cCarrierFileSystem::Delete%1000119092.body
}

LONG_T cCarrierFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cCarrierFileSystem::FileSize%1000386738.body preserve=yes
   USR_HANDLE hnd = 0;
   int err = 0;
   DISK_PARAM_BLOCK param = {0};
   param.Date = (PARAMETER)MakeFileTime();
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = (PARAMETER)DISK_OP_READ;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      throw cError(DeviceError(hnd), 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   long file_size = CarrierFileSize(hnd);
   DevClose(hnd);
   return file_size;
  //## end cCarrierFileSystem::FileSize%1000386738.body
}

cFile * cCarrierFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cCarrierFileSystem::File%1000386739.body preserve=yes
   USR_HANDLE hnd = 0;
   int err = 0;
   DISK_PARAM_BLOCK param = {0};
   param.Date = (PARAMETER)MakeFileTime();
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = (PARAMETER)DISK_OP_READ;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      throw cError(DeviceError(hnd), 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
   DevClose(hnd);
   return new cFMFatFile(file_name, this);
  //## end cCarrierFileSystem::File%1000386739.body
}

cTimeObject cCarrierFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cCarrierFileSystem::GetTime%1000456417.body preserve=yes
  //## end cCarrierFileSystem::GetTime%1000456417.body
}

// Additional Declarations
  //## begin cCarrierFileSystem%3B98FC59007F.declarations preserve=yes
  //## end cCarrierFileSystem%3B98FC59007F.declarations

//## begin module%3B98FC59007F.epilog preserve=yes
//## end module%3B98FC59007F.epilog
