
#ifndef __carsim_h__
#define __carsim_h__

#define CT_READ   1
#define CT_WRITE   2

typedef struct {
   unsigned int low;
   unsigned int high;
   unsigned int cmd;
   unsigned int write;
   unsigned int read;
   unsigned int status;
   unsigned char v_low;
   unsigned char v_high;
   unsigned char v_cmd;
   unsigned char v_write;
   unsigned char v_read;
   unsigned char v_status;
   unsigned char adr_low;
   unsigned char adr_high;
   unsigned char command_type;
   unsigned char command;
   unsigned char line;
   unsigned long read_address;
   unsigned long write_address;
   unsigned long memsize;
   unsigned char * memory;
}  HARDWARE;

void * SetSimHardware(void * ccb);
void SetSimulatedSize(unsigned long size);

#endif   /* __carsim_h__ */


