
#ifndef __carctl__
#define __carctl__

#define CARRIER_DEVICE_TYPE       40000
//#define CARRIER_DEVICE_TYPE       0x00000022

typedef struct _CARRIER_CTL_STRUCT {
   unsigned long Long1;
   unsigned long Long2;
   unsigned char * pByte;
} CARRIER_CTL_STRUCT;

#ifndef FILE_ANY_ACCESS

#define FILE_ANY_ACCESS       0
#define FILE_READ_ACCESS    ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS   ( 0x0002 )    // file & pipe

#define METHOD_BUFFERED    0
#define METHOD_IN_DIRECT   1
#define METHOD_OUT_DIRECT  2
#define METHOD_NEITHER     3

#define CTL_CODE( DeviceType, Function, Method, Access ) (\
                  ((DeviceType) << 16) | ((Access) << 14) | \
                  ((Function) << 2) | (Method) \
                  )

#endif

#define IOCTL_CARRIER_CHECK       CTL_CODE(CARRIER_DEVICE_TYPE,0x801,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_SEEK        CTL_CODE(CARRIER_DEVICE_TYPE,0x802,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_READ        CTL_CODE(CARRIER_DEVICE_TYPE,0x803,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_WRITE       CTL_CODE(CARRIER_DEVICE_TYPE,0x804,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_GET_PARAM   CTL_CODE(CARRIER_DEVICE_TYPE,0x805,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_SET_PARAM   CTL_CODE(CARRIER_DEVICE_TYPE,0x806,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_GET_LAST_ERROR   CTL_CODE(CARRIER_DEVICE_TYPE,0x807,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)

#endif /*__carctl__*/


