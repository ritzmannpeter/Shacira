//---------------------------------------------------------------------------
#ifndef FileBufferH
#define FileBufferH
//---------------------------------------------------------------------------

#include "Legacy.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define BLOCK_SIZE   2048
#define BLOCK_SIZE  1024L

typedef int (*BUF_INIT_T)(void * fbuf, unsigned_32 size);
typedef int (*BUF_LOAD_FILE_T)(void * fbuf, const char * path);
typedef int (*BUF_SAVE_FILE_T)(void * fbuf, const char * path);
typedef int (*BUF_SEEK_T)(void * fbuf, unsigned_32 pos);
typedef int (*BUF_READ_T)(void * fbuf, void * buffer, unsigned_32 size);
typedef int (*BUF_WRITE_T)(void * fbuf, void * buffer, unsigned_32 size);
typedef unsigned_32 (*BUF_SEEK_POS_T)(void * fbuf);
typedef unsigned_32 (*BUF_FILE_SIZE_T)(void * fbuf);

typedef struct
{
   void * buffer;
   unsigned_32 buf_size;
   unsigned_32 file_size;
   unsigned_32 seek_pos;
   BUF_INIT_T Init;
   BUF_LOAD_FILE_T LoadFile;
   BUF_SAVE_FILE_T SaveFile;
   BUF_SEEK_T Seek;
   BUF_READ_T Read;
   BUF_WRITE_T Write;
   BUF_SEEK_POS_T SeekPos;
   BUF_FILE_SIZE_T FileSize;
}  FILE_BUFFER_T;
#define _buffer ((FILE_BUFFER_T*)fbuf)->buffer
#define _file_size ((FILE_BUFFER_T*)fbuf)->file_size
#define _buf_size ((FILE_BUFFER_T*)fbuf)->buf_size
#define _seek_pos ((FILE_BUFFER_T*)fbuf)->seek_pos
#define _Init ((FILE_BUFFER_T*)fbuf)->Init
#define _LoadFile ((FILE_BUFFER_T*)fbuf)->LoadFile
#define _SaveFile ((FILE_BUFFER_T*)fbuf)->SaveFile
#define _Seek ((FILE_BUFFER_T*)fbuf)->Seek
#define _Read ((FILE_BUFFER_T*)fbuf)->Read
#define _Write ((FILE_BUFFER_T*)fbuf)->Write
#define _SeekPos ((FILE_BUFFER_T*)fbuf)->SeekPos
#define _FileSize ((FILE_BUFFER_T*)fbuf)->FileSize

FILE_BUFFER_T * NewFileBuffer(const char * path);
int DeleteFileBuffer(FILE_BUFFER_T * fbuf);

#ifdef __cplusplus
}
#endif

#endif

