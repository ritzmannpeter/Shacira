

#include "Carrier.h"
#include <stdio.h>
#include <windows.h>

static unsigned char _Data[32 * 1024];

static HARDWARE SimHardware = {0};

void * SetSimHardware(void * ccb)
{
   CCB * _ccb = (CCB*)ccb;
   _ccb->SimulatedHardware = &SimHardware;
   SimHardware.low = _ccb->addr_low;
   SimHardware.high = _ccb->addr_high;
   SimHardware.cmd = _ccb->addr_cmd;
   SimHardware.write = _ccb->addr_write;
   SimHardware.read = _ccb->addr_read;
   SimHardware.status = _ccb->addr_status;
   SimHardware.v_low = 0xff;
   SimHardware.v_high = 0xff;
   SimHardware.v_cmd = 0xff;
   SimHardware.v_write = 0xff;
   SimHardware.v_read = 0xff;
   SimHardware.v_status = 0x7e;
   SimHardware.memory = _Data;
   if (SimHardware.memory != NULL) {
      unsigned long i = 0;
      unsigned char * mem = SimHardware.memory;
      SimHardware.memsize = sizeof(_Data);
      return &SimHardware;
   }
   return NULL;
}

unsigned char SimulatedInport(unsigned short port)
{
   HARDWARE * hp = &SimHardware;
   if (port == hp->low) {
      return hp->v_low;
   } else if (port == hp->high) {
      return hp->v_high;
   } else if (port == hp->cmd) {
      return hp->v_cmd;
   } else if (port == hp->read) {
      // get address and read
      unsigned long address = (hp->read_address % hp->memsize);
      unsigned char value = hp->memory[address];
      return value;
   } else if (port == hp->write) {
      return hp->v_write;
   } else if (port == hp->status) {
      return hp->v_status;
   }
   return 0xff;
}

void SimulatedOutport(unsigned short port, unsigned char value)
{ 
   HARDWARE * hp = &SimHardware;
   if (port == hp->low) {
      hp->v_low = value;
   } else if (port == hp->high) {
      hp->v_high = value;
   } else if (port == hp->cmd) {
      hp->v_cmd = value;
      if (value != NO_OP) {
         unsigned char line = 0;
         hp->command_type = (value & 0x80) ? CT_READ : CT_WRITE;
         hp->command = value & 0x07;
         line = value;
         line = line & 0x78;
         line = line >> 3;
         line = line & 0x0f;
         line = line | 0xf0;
         line = ~line;
         hp->line = line;
         if (hp->command_type == CT_READ) {
            hp->read_address = hp->v_low + (hp->v_high << 8);
         } else if (hp->command_type == CT_WRITE) {
            hp->write_address = hp->v_low + (hp->v_high << 8);
         }
      }
   } else if (port == hp->read) {
      hp->v_read = value;
   } else if (port == hp->write) {
      // get address and write
      unsigned long address = (hp->write_address % hp->memsize);
      hp->memory[address] = value;
   }
}

void SetSimulatedSize(unsigned long size)
{
   unsigned long new_size = size * 1024;
   if (size > sizeof(_Data)) return;
   SimHardware.memsize = new_size; 
}



