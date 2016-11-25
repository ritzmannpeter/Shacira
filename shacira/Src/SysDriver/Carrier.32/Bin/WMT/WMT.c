
#include "stdio.h"
#include "../CarDLL32/cardll32.h"

#define FILE_SIZE 0x2000
#define BUF_SIZE  0x8000
typedef unsigned char BUF_TYPE_T;
BUF_TYPE_T _Buffer[BUF_SIZE] = {0};

static int CheckSum(BUF_TYPE_T * buffer, int sum_addr, int start_addr, int length)
{
   BUF_TYPE_T sum = 0;
   BUF_TYPE_T byte = 0;
   BUF_TYPE_T read_sum = 0;
   int i = 0;
   for (i = start_addr; i < start_addr + length; i++) {
      byte = buffer[i];
      sum ^= byte;
   }
   read_sum = buffer[sum_addr];
   if (read_sum == sum) {
      return 1;
   } else {
      return 0;
   }
}


static void Test()
{
#ifdef zur_doku
CARDLL32_API HANDLE CAR_Open();
CARDLL32_API void CAR_Close(HANDLE hnd);
CARDLL32_API long CAR_SetParam(HANDLE hnd, const char * param_name, long param_value);
CARDLL32_API long CAR_GetParam(HANDLE hnd, const char * param_name, long * param_value);
CARDLL32_API long CAR_Check(HANDLE hnd);
CARDLL32_API long CAR_Read(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long bufsize, unsigned long amount);
CARDLL32_API long CAR_Write(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long amount);
#endif
   int size = 0;
   int nwrite = 0;
   const char * file_name = "carrier.dump";
   FILE * stream = NULL;
   int err = 0;
   HANDLE hnd = CAR_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
      size = CAR_Check(hnd);
      if (size == 4 ||
          size == 8 ||
          size == 32) {
         size *= 1024;
         printf("size = %d\n", size);
         err = CAR_Read(hnd, 0, _Buffer, sizeof(_Buffer), size);
         if (err >= 0) {
            if (!CheckSum(_Buffer, 25, 80, 1024)) {
               printf("Failed to verify Checksum 1\n");
               CAR_Close(hnd);
               return;
            }
            if (!CheckSum(_Buffer, 45, 1104, 1024)) {
               printf("Failed to verify Checksum 2\n");
               CAR_Close(hnd);
               return;
            }
            if (!CheckSum(_Buffer, 65, 2128, 1024)) {
               printf("Failed to verify Checksum 3\n");
               CAR_Close(hnd);
               return;
            }
         } else {
            printf("read error: %d\n", err);
            CAR_Close(hnd);
            return;
         }
      } else {
         printf("check error: %d\n", size);
         CAR_Close(hnd);
         return;
      }
      CAR_Close(hnd);
   } else {
      printf("Failed to open carrier device\n");
      return;
   }
   stream = fopen(file_name, "wb");
   if (stream == NULL) {
      printf("failed to open file %s\n", file_name);
      return;
   }
   nwrite = fwrite(_Buffer, 1, size, stream);
   if (nwrite != size) {
      printf("failed to write to file %s\n", file_name);
      fclose(stream);
      return;
   }
   fclose(stream);
}

int main(int argc, char ** argv)
{
   short snd = 0;
   const char * file_name = argv[1];
   FILE * stream = NULL;
   int nread = 0;
Test();
return 0;
   if (file_name == NULL) {
      printf("no file specified\n");
      return 0;
   }
   stream = fopen(file_name, "rb");
   if (stream == NULL) {
      printf("failed to open file %s\n", file_name);
      return 0;
   }
   nread = fread(_Buffer, 1, BUF_SIZE, stream);
   if (nread != BUF_SIZE) {
      printf("failed to read file %s\n", file_name);
      fclose(stream);
      return 0;
   }
   fclose(stream);
   if (!CheckSum(_Buffer, 25, 80, 1024)) {
      printf("Failed to verify Checksum 1\n");
      return 0;
   }
   if (!CheckSum(_Buffer, 45, 1104, 1024)) {
      printf("Failed to verify Checksum 2\n");
      return 0;
   }
   if (!CheckSum(_Buffer, 65, 2128, 1024)) {
      printf("Failed to verify Checksum 3\n");
      return 0;
   }
   snd = *(short *)&_Buffer[18];
   printf("screw = %d\n", snd);
   return 0;
}
