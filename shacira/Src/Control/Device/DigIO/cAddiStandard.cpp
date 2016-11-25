//## begin module%404717710000.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404717710000.cm

//## begin module%404717710000.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404717710000.cp

//## Module: cAddiStandard%404717710000; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cAddiStandard.cpp

//## begin module%404717710000.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%404717710000.additionalIncludes

//## begin module%404717710000.includes preserve=yes
//## end module%404717710000.includes

// cAddiStandard
#include "Control/Device/DigIO/cAddiStandard.h"
//## begin module%404717710000.additionalDeclarations preserve=yes

//#define UNIVERSAL_ADDRESS(pos)   ((unsigned char)(pos-1))
#define UNIVERSAL_ADDRESS(pos)   ((UCHAR_T)pos)
#define UNIVERSAL_GET_ERROR()    -1

//## end module%404717710000.additionalDeclarations


// Class cAddiStandard 


cAddiStandard::cAddiStandard()
  //## begin cAddiStandard::cAddiStandard%.hasinit preserve=no
      : _Handle(INVALID_DRIVER_HANDLE)
  //## end cAddiStandard::cAddiStandard%.hasinit
  //## begin cAddiStandard::cAddiStandard%.initialization preserve=yes
  //## end cAddiStandard::cAddiStandard%.initialization
{
  //## begin cAddiStandard::cAddiStandard%.body preserve=yes
#if defined(_WIN32)
   int rc = i_ADDIDATA_OpenWin32Driver(ADDIDATA_DLL_COMPILER_C, &_Handle);
   if (rc == 0) {
		USHORT_T inputs = 0;
		USHORT_T outputs = 0;
      if (!b_ADDIDATA_GetNumberOfDigitalInputs(_Handle, &inputs)) {
         throw cError(ADDI_UNIVERSAL_GET_INPUT_NO, 0);
      }
		if (!b_ADDIDATA_GetNumberOfDigitalOutputs(_Handle, &outputs)) {
         throw cError(ADDI_UNIVERSAL_GET_OUTPUT_NO, UNIVERSAL_GET_ERROR());
      } else {
         if (!b_ADDIDATA_SetDigitalOutputMemoryOn(_Handle)) {
            throw cError(ADDI_UNIVERSAL_SET_OUTPUT_MEM, UNIVERSAL_GET_ERROR());
         }
         _Inputs = inputs;
         _Outputs = outputs;
      }
   } else {
      throw cError(ADDI_UNIVERSAL_OPEN, UNIVERSAL_GET_ERROR());
   }
#else
#endif
  //## end cAddiStandard::cAddiStandard%.body
}

cAddiStandard::cAddiStandard(const cAddiStandard &right)
  //## begin cAddiStandard::cAddiStandard%copy.hasinit preserve=no
      : _Handle(INVALID_DRIVER_HANDLE)
  //## end cAddiStandard::cAddiStandard%copy.hasinit
  //## begin cAddiStandard::cAddiStandard%copy.initialization preserve=yes
  //## end cAddiStandard::cAddiStandard%copy.initialization
{
  //## begin cAddiStandard::cAddiStandard%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cAddiStandard::cAddiStandard%copy.body
}


cAddiStandard::~cAddiStandard()
{
  //## begin cAddiStandard::~cAddiStandard%.body preserve=yes
#if defined(_WIN32)
   if (_Handle != INVALID_DRIVER_HANDLE) b_ADDIDATA_CloseWin32Driver(_Handle);
#endif
  //## end cAddiStandard::~cAddiStandard%.body
}



//## Other Operations (implementation)
void cAddiStandard::SetOutput (ULONG_T output_no)
{
  //## begin cAddiStandard::SetOutput%1078400675.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   if (!b_ADDIDATA_Set1DigitalOutputOn(_Handle, UNIVERSAL_ADDRESS(output_no))) {
      throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_ON, UNIVERSAL_GET_ERROR(),
                   cConvUtils::StringValue(output_no).c_str());
   }
#else
#endif
  //## end cAddiStandard::SetOutput%1078400675.body
}

void cAddiStandard::ResetOutput (ULONG_T output_no)
{
  //## begin cAddiStandard::ResetOutput%1078400676.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   if (!b_ADDIDATA_Set1DigitalOutputOff(_Handle, UNIVERSAL_ADDRESS(output_no))) {
      throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR(),
                   cConvUtils::StringValue(output_no).c_str());
   }
#else
#endif
  //## end cAddiStandard::ResetOutput%1078400676.body
}

BOOL_T cAddiStandard::GetInput (ULONG_T input_no)
{
  //## begin cAddiStandard::GetInput%1078400677.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   BYTE_ value = 0;
   if (!b_ADDIDATA_Read1DigitalInput(_Handle, UNIVERSAL_ADDRESS(input_no), &value)) {
      throw cError(ADDI_UNIVERSAL_READ1_INPUT, UNIVERSAL_GET_ERROR());
   }
   if (value == 0) {
      return false;
   } else {
      return true;
   }
#else
   return false;
#endif
  //## end cAddiStandard::GetInput%1078400677.body
}

ULONG_T cAddiStandard::GetInputs (void *inputs, ULONG_T buf_size)
{
  //## begin cAddiStandard::GetInputs%1078400678.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   BOOL_T success = false;
   if (_Inputs == 32) {
      DWORD val = 0;
      success = b_ADDIDATA_Read32DigitalInputs(_Handle, 0, (PDWORD)&val);
      if (success) {
         *(DWORD*)inputs = val;
         return 4;
      }
   } else if (_Inputs == 16) {
      WORD val = 0;
      success = b_ADDIDATA_Read16DigitalInputs(_Handle, 0, (PWORD)&val);
      if (success) {
         *(WORD*)inputs = val;
         return 2;
      }
   } else if (_Inputs == 8) {
      BYTE val = 0;
      success = b_ADDIDATA_Read8DigitalInputs(_Handle, 0, (PBYTE)&val);
      if (success) {
         *(BYTE*)inputs = val;
         return 1;
      }
   } else if (_Inputs == 4) {
      BYTE val = 0;
      success = b_ADDIDATA_Read4DigitalInputs(_Handle, 0, (PBYTE)&val);
      if (success) {
         *(BYTE*)inputs = val;
         return 1;
      }
   } else if (_Inputs == 2) {
      BYTE val = 0;
      success = b_ADDIDATA_Read2DigitalInputs(_Handle, 0, (PBYTE_)&val);
      if (success) {
         *(BYTE*)inputs = val;
         return 1;
      }
   } else {
      throw cError(ADDI_UNIVERSAL_INVALID_NOOFINPUTS, UNIVERSAL_GET_ERROR(),
                   cConvUtils::StringValue(_Inputs).c_str());
   }
   return 0;
#else
   return 0;
#endif
  //## end cAddiStandard::GetInputs%1078400678.body
}

ULONG_T cAddiStandard::WriteOutputs (void *outputs, ULONG_T len)
{
  //## begin cAddiStandard::WriteOutputs%1078410644.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   BOOL_T success = false;
   if (_Outputs == 32) {
      DWORD mask = *(DWORD*)outputs;
      if (!b_ADDIDATA_Set32DigitalOutputsOff(_Handle, 0, ~mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      if (!b_ADDIDATA_Set32DigitalOutputsOn(_Handle, 0, mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 4;
   } else if (_Outputs == 16) {
      WORD mask = *(WORD*)outputs;
      if (!b_ADDIDATA_Set16DigitalOutputsOff(_Handle, 0, ~mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      if (!b_ADDIDATA_Set16DigitalOutputsOn(_Handle, 0, mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 2;
   } else if (_Outputs == 8) {
      BYTE mask = *(BYTE*)outputs;
      if (!b_ADDIDATA_Set8DigitalOutputsOff(_Handle, 0, ~mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      if (!b_ADDIDATA_Set8DigitalOutputsOn(_Handle, 0, mask)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 1;
   } else {
      throw cError(ADDI_UNIVERSAL_INVALID_NOOFINPUTS, UNIVERSAL_GET_ERROR(),
                   cConvUtils::StringValue(_Outputs).c_str());
   }
   return 0;
#else
   return 0;
#endif
  //## end cAddiStandard::WriteOutputs%1078410644.body
}

ULONG_T cAddiStandard::ReadOutputs (void *buf, ULONG_T buf_size)
{
  //## begin cAddiStandard::ReadOutputs%1078416424.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   if (_Outputs == 32) {
      if (!b_ADDIDATA_Get32DigitalOutputStatus(_Handle, 0, (PDWORD)buf)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 4;
   } else if (_Outputs == 16) {
      if (!b_ADDIDATA_Get16DigitalOutputStatus(_Handle, 0, (PWORD)buf)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 2;
   } else if (_Outputs == 8) {
      if (!b_ADDIDATA_Get8DigitalOutputStatus(_Handle, 0, (PBYTE)buf)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
      return 1;
   }
   return 0;
#else
   return 0;
#endif
  //## end cAddiStandard::ReadOutputs%1078416424.body
}

void cAddiStandard::SetAllOutputs ()
{
  //## begin cAddiStandard::SetAllOutputs%1078416418.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   if (_Outputs == 32) {
      if (!b_ADDIDATA_Set32DigitalOutputsOn(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   } else if (_Outputs == 16) {
      if (!b_ADDIDATA_Set16DigitalOutputsOn(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   } else if (_Outputs == 8) {
      if (!b_ADDIDATA_Set8DigitalOutputsOn(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   }
#else
#endif
  //## end cAddiStandard::SetAllOutputs%1078416418.body
}

void cAddiStandard::ResetAllOutputs ()
{
  //## begin cAddiStandard::ResetAllOutputs%1078416419.body preserve=yes
#if defined(_WIN32)
_ASSERT_COND(_Handle != INVALID_DRIVER_HANDLE)
   if (_Outputs == 32) {
      if (!b_ADDIDATA_Set32DigitalOutputsOff(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   } else if (_Outputs == 16) {
      if (!b_ADDIDATA_Set16DigitalOutputsOff(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   } else if (_Outputs == 8) {
      if (!b_ADDIDATA_Set8DigitalOutputsOff(_Handle, 0, 0xff)) {
         throw cError(ADDI_UNIVERSAL_SET1_OUTPUT_OFF, UNIVERSAL_GET_ERROR());
      }
   }
#else
#endif
  //## end cAddiStandard::ResetAllOutputs%1078416419.body
}

// Additional Declarations
  //## begin cAddiStandard%404717710000.declarations preserve=yes
  //## end cAddiStandard%404717710000.declarations

//## begin module%404717710000.epilog preserve=yes
//## end module%404717710000.epilog
