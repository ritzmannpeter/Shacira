//## begin module%40A20CD9032C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A20CD9032C.cm

//## begin module%40A20CD9032C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A20CD9032C.cp

//## Module: cPPCOperator%40A20CD9032C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCOperator.h

#ifndef cPPCOperator_h
#define cPPCOperator_h 1

//## begin module%40A20CD9032C.includes preserve=yes
//## end module%40A20CD9032C.includes

// cBitOperator
#include "Control/Device/cBitOperator.h"
//## begin module%40A20CD9032C.additionalDeclarations preserve=yes
//## end module%40A20CD9032C.additionalDeclarations


//## begin cPPCOperator%40A20CD9032C.preface preserve=yes
//## end cPPCOperator%40A20CD9032C.preface

//## Class: cPPCOperator%40A20CD9032C
//## Category: Control::Device::PPCCom%410896E5001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPPCOperator : public cBitOperator  //## Inherits: <unnamed>%40A20CF701A5
{
  //## begin cPPCOperator%40A20CD9032C.initialDeclarations preserve=yes
public:
  //## end cPPCOperator%40A20CD9032C.initialDeclarations

    //## Constructors (generated)
      cPPCOperator();

      cPPCOperator(const cPPCOperator &right);

    //## Destructor (generated)
      virtual ~cPPCOperator();


    //## Other Operations (specified)
      //## Operation: SetValue%1084360948
      virtual void SetValue (UCHAR_T data_type, UCHAR_T value);

      //## Operation: SetValue%1084360949
      virtual void SetValue (UCHAR_T data_type, USHORT_T value);

      //## Operation: SetValue%1084360950
      virtual void SetValue (UCHAR_T data_type, ULONG_T value);

      //## Operation: SetValue%1084360951
      virtual void SetValue (UCHAR_T data_type, CHAR_T value);

      //## Operation: SetValue%1084360952
      virtual void SetValue (UCHAR_T data_type, SHORT_T value);

      //## Operation: SetValue%1084360953
      virtual void SetValue (UCHAR_T data_type, LONG_T value);

      //## Operation: SetValue%1110194503
      virtual void SetValue (UCHAR_T data_type, FLOAT_T value);

      //## Operation: SetValue%1110194504
      virtual void SetValue (UCHAR_T data_type, DOUBLE_T value);

      //## Operation: operator UCHAR_T%1084360954
      virtual operator UCHAR_T ();

      //## Operation: operator USHORT_T%1084360955
      virtual operator USHORT_T ();

      //## Operation: operator ULONG_T%1084360956
      virtual operator ULONG_T ();

      //## Operation: operator CHAR_T%1084360957
      virtual operator CHAR_T ();

      //## Operation: operator SHORT_T%1084360958
      virtual operator SHORT_T ();

      //## Operation: operator LONG_T%1084360959
      virtual operator LONG_T ();

      //## Operation: operator FLOAT_T%1110194509
      virtual operator FLOAT_T ();

      //## Operation: operator DOUBLE_T%1110194510
      virtual operator DOUBLE_T ();

      //## Operation: SetBit%1084360960
      virtual void SetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: ResetBit%1084360961
      virtual void ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetBit%1084360967
      virtual UCHAR_T GetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: SetPattern%1084360962
      virtual void SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetPattern%1084360963
      virtual ULONG_T GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: BytePos%1084360964
      virtual UCHAR_T BytePos (UCHAR_T data_type, UCHAR_T bit_pos);

  public:
    // Additional Public Declarations
      //## begin cPPCOperator%40A20CD9032C.public preserve=yes
      //## end cPPCOperator%40A20CD9032C.public

  protected:
    // Additional Protected Declarations
      //## begin cPPCOperator%40A20CD9032C.protected preserve=yes
      //## end cPPCOperator%40A20CD9032C.protected

  private:
    // Additional Private Declarations
      //## begin cPPCOperator%40A20CD9032C.private preserve=yes
      //## end cPPCOperator%40A20CD9032C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cPPCOperator%40A20CD9032C.implementation preserve=yes
      //## end cPPCOperator%40A20CD9032C.implementation

};

//## begin cPPCOperator%40A20CD9032C.postscript preserve=yes
//## end cPPCOperator%40A20CD9032C.postscript

// Class cPPCOperator 

//## begin module%40A20CD9032C.epilog preserve=yes
//## end module%40A20CD9032C.epilog


#endif
