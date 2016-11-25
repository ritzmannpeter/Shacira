
#ifndef plc_comm_layout_h
#define plc_comm_layout_h 1

#ifdef _WIN32
#pragma pack(push,1)
#endif

typedef short _INT;
typedef int _DINT;
typedef unsigned short _W;
typedef unsigned int _DW;

/* Definition des Kommunikations-Layouts */

typedef struct _db80 {
   _INT Version;
   _DINT MachineNr;
   _DINT ErrorNr;
   _INT ErrorType;
   _INT MachineState;
   _DINT OutputDiag;
   _INT StepNr;
   _INT StepInfo;
   _INT PCState;
}  DB80_T;

typedef struct _db81 {
   _INT MachineState;
   _INT WorkingStep;
   _DW PCState;
   _DW Reserve1;
   _DW MachineSettings;
   _INT Reserve2;
   _INT Reserve3;
   _INT Reserve4;
   _W AutoMode;
   _W PlateSpecial;
   _INT Reserve5;
   _INT Reserve6;
   _INT Reserve7;
   _INT Reserve8;
   _INT Reserve9;
   _INT Reserve10;
   _DINT TotalPlates;
   _DINT DayPlates;
   _DINT BadPlates;
   _DINT EmptyPlates;
   _DINT SpecialCounter;
   _INT OilCycles;
   _INT OilTime;
   _INT CoolingTime;
}  DB81_T;

typedef struct _db82 {
   _W FormatState;
   _W FormatDetection;
   _W Format1;
   _W Format2;
}  DB82_T;

typedef struct _db83 {
   _W StackerState;
   _W PCState;
   _INT BinNumber1;
   _INT BinNumber2;
   _INT BinNumber3;
   _INT BinNumber4;
   _INT BinNumber5;
   _INT Reserve1;
   _INT Reserve2;
   _DINT PLCountBCL1;
   _DINT PLCountBCL2;
   _DINT PLCountBCL3;
   _DINT PLCountBCL4;
   _DINT PLCountBCL5;
   _DINT BinState1;
   _DINT BinState17;
   _DINT BinState33;
   _DINT BinState49;
   _DINT BinState65;
}  DB83_T;

typedef struct _inputs {
   unsigned char data[0x100];
}  INPUTS_T;

typedef struct _outputs {
   unsigned char data[0x100];
}  OUTPUTS_T;

typedef struct plc_comm_layout {
   DB80_T db80;
   DB81_T db81;
   DB82_T db82;
   DB83_T db83;
   INPUTS_T inputs;
   OUTPUTS_T outputs;
/*   char dummy[0x200]; */
}  PLC_COMM_LAYOUT_T;

#ifdef _WIN32
#pragma pack(pop)
#endif

#endif

