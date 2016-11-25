
#include "legacy.h"
#include "Dnc/CarItf/CarItf.h"

#ifdef lassma

static HANDLE _Handle = INVALID_HANDLE_VALUE;

int BASIC_Check()
{
   if (_Handle == INVALID_HANDLE_VALUE) {
      _Handle = CARITF_Open();
   }
   return CARITF_Check(_Handle);
}

int BASIC_Read(long address, long size, void * buffer)
{
   int nread = CARITF_Read(_Handle, address, (unsigned char *)buffer, 10000, size);
   if (nread == size) {
      return 0;
   } else {
      return nread;
   }
}

int BASIC_Write(long address, long size, void * buffer)
{
   int nwrite = CARITF_Write(_Handle, address, (unsigned char *)buffer, size);
   if (nwrite == size) {
      return 0;
   } else {
      return nwrite;
   }
}

#endif

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

USR_BYTE Checksum(USR_BYTE * buffer, int src, int offs)
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

int FMT2_TestChecksum()
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

int FMT2_2F_TestChecksum()
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

int FMT2_3F_TestChecksum()
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

int DeviceError(int hnd)
{
   PARAMETER device_error;
   DevGetParam(hnd, DEV_ID_ERROR, &device_error);
   return (int)device_error;
}

