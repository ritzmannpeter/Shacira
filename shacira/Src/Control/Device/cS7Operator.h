//## begin module%40A20C7702AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A20C7702AF.cm

//## begin module%40A20C7702AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A20C7702AF.cp

//## Module: cS7Operator%40A20C7702AF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cS7Operator.h

#ifndef cS7Operator_h
#define cS7Operator_h 1

//## begin module%40A20C7702AF.includes preserve=yes
//## end module%40A20C7702AF.includes

// cBitOperator
#include "Control/Device/cBitOperator.h"
//## begin module%40A20C7702AF.additionalDeclarations preserve=yes
//## end module%40A20C7702AF.additionalDeclarations


//## begin cS7Operator%40A20C7702AF.preface preserve=yes
//## end cS7Operator%40A20C7702AF.preface

//## Class: cS7Operator%40A20C7702AF
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cS7Operator : public cBitOperator  //## Inherits: <unnamed>%40A20C9701F4
{
  //## begin cS7Operator%40A20C7702AF.initialDeclarations preserve=yes
public:
  //## end cS7Operator%40A20C7702AF.initialDeclarations

    //## Constructors (generated)
      cS7Operator();

      cS7Operator(const cS7Operator &right);

    //## Destructor (generated)
      virtual ~cS7Operator();


    //## Other Operations (specified)
      //## Operation: SetValue%1084360930
      virtual void SetValue (UCHAR_T data_type, UCHAR_T value);

      //## Operation: SetValue%1084360931
      virtual void SetValue (UCHAR_T data_type, USHORT_T value);

      //## Operation: SetValue%1084360932
      virtual void SetValue (UCHAR_T data_type, ULONG_T value);

      //## Operation: SetValue%1084360933
      virtual void SetValue (UCHAR_T data_type, CHAR_T value);

      //## Operation: SetValue%1084360934
      virtual void SetValue (UCHAR_T data_type, SHORT_T value);

      //## Operation: SetValue%1084360935
      virtual void SetValue (UCHAR_T data_type, LONG_T value);

      //## Operation: SetValue%1110194497
      virtual void SetValue (UCHAR_T data_type, FLOAT_T value);

      //## Operation: SetValue%1110194498
      virtual void SetValue (UCHAR_T data_type, DOUBLE_T value);

      //## Operation: operator UCHAR_T%1084360936
      virtual operator UCHAR_T ();

      //## Operation: operator USHORT_T%1084360937
      virtual operator USHORT_T ();

      //## Operation: operator ULONG_T%1084360938
      virtual operator ULONG_T ();

      //## Operation: operator CHAR_T%1084360939
      virtual operator CHAR_T ();

      //## Operation: operator SHORT_T%1084360940
      virtual operator SHORT_T ();

      //## Operation: operator LONG_T%1084360941
      virtual operator LONG_T ();

      //## Operation: operator FLOAT_T%1110194507
      virtual operator FLOAT_T ();

      //## Operation: operator DOUBLE_T%1110194508
      virtual operator DOUBLE_T ();

      //## Operation: SetBit%1084360942
      virtual void SetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: ResetBit%1084360943
      virtual void ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetBit%1084360965
      virtual UCHAR_T GetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: SetPattern%1084360944
      virtual void SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetPattern%1084360945
      virtual ULONG_T GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: BytePos%1084360946
      virtual UCHAR_T BytePos (UCHAR_T data_type, UCHAR_T bit_pos);

  public:
    // Additional Public Declarations
      //## begin cS7Operator%40A20C7702AF.public preserve=yes
      //## end cS7Operator%40A20C7702AF.public

  protected:
    // Additional Protected Declarations
      //## begin cS7Operator%40A20C7702AF.protected preserve=yes
      //## end cS7Operator%40A20C7702AF.protected

  private:
    // Additional Private Declarations
      //## begin cS7Operator%40A20C7702AF.private preserve=yes
      //## end cS7Operator%40A20C7702AF.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cS7Operator%40A20C7702AF.implementation preserve=yes
      //## end cS7Operator%40A20C7702AF.implementation

};

//## begin cS7Operator%40A20C7702AF.postscript preserve=yes
//## end cS7Operator%40A20C7702AF.postscript

// Class cS7Operator 

//## begin module%40A20C7702AF.epilog preserve=yes
//## end module%40A20C7702AF.epilog


#endif
