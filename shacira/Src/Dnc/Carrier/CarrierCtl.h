
#ifndef __CarrierCtl__
#define __CarrierCtl__

#define CARRIER_DEVICE  "\\\\.\\Carrier"
#define CARRIER_VXD     "\\\\.\\Carrier.vxd"

typedef struct _CARRIER_CTL_STRUCT {
   unsigned long Long1;
   unsigned long Long2;
   unsigned char * pByte;
} CARRIER_CTL_STRUCT;

#define FILE_ANY_ACCESS       0
#define FILE_READ_ACCESS    ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS   ( 0x0002 )    // file & pipe

#define METHOD_BUFFERED    0
#define METHOD_IN_DIRECT   1
#define METHOD_OUT_DIRECT  2
#define METHOD_NEITHER     3

#define FILE_DEVICE_UNKNOWN  0x00000022

#define CTL_CODE( DeviceType, Function, Method, Access ) (\
                  ((DeviceType) << 16) | ((Access) << 14) | \
                  ((Function) << 2) | (Method) \
                  )

#define IOCTL_CARRIER_CHECK       CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_SEEK        CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_READ        CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_WRITE       CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_GET_PARAM   CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_SET_PARAM   CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CARRIER_LAST_ERROR  CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,\
                                           METHOD_BUFFERED,FILE_ANY_ACCESS)

#endif /*__CarrierCtl__*/


