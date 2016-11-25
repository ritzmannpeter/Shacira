//## begin module%41DBCB6503B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41DBCB6503B9.cm

//## begin module%41DBCB6503B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41DBCB6503B9.cp

//## Module: cNullOperator%41DBCB6503B9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cNullOperator.h

#ifndef cNullOperator_h
#define cNullOperator_h 1

//## begin module%41DBCB6503B9.includes preserve=yes
//## end module%41DBCB6503B9.includes

// cBitOperator
#include "Control/Device/cBitOperator.h"
//## begin module%41DBCB6503B9.additionalDeclarations preserve=yes
//## end module%41DBCB6503B9.additionalDeclarations


//## begin cNullOperator%41DBCB6503B9.preface preserve=yes
//## end cNullOperator%41DBCB6503B9.preface

//## Class: cNullOperator%41DBCB6503B9
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNullOperator : public cBitOperator  //## Inherits: <unnamed>%41DBCBAD00DA
{
  //## begin cNullOperator%41DBCB6503B9.initialDeclarations preserve=yes
public:
  //## end cNullOperator%41DBCB6503B9.initialDeclarations

    //## Constructors (generated)
      cNullOperator();

      cNullOperator(const cNullOperator &right);

    //## Destructor (generated)
      virtual ~cNullOperator();


    //## Other Operations (specified)
      //## Operation: SetValue%1104923575
      virtual void SetValue (UCHAR_T data_type, UCHAR_T value);

      //## Operation: SetValue%1104923576
      virtual void SetValue (UCHAR_T data_type, USHORT_T value);

      //## Operation: SetValue%1104923577
      virtual void SetValue (UCHAR_T data_type, ULONG_T value);

      //## Operation: SetValue%1104923578
      virtual void SetValue (UCHAR_T data_type, CHAR_T value);

      //## Operation: SetValue%1104923579
      virtual void SetValue (UCHAR_T data_type, SHORT_T value);

      //## Operation: SetValue%1104923580
      virtual void SetValue (UCHAR_T data_type, LONG_T value);

      //## Operation: SetValue%1110194495
      virtual void SetValue (UCHAR_T data_type, FLOAT_T value);

      //## Operation: SetValue%1110194496
      virtual void SetValue (UCHAR_T data_type, DOUBLE_T value);

      //## Operation: operator UCHAR_T%1104923581
      virtual operator UCHAR_T ();

      //## Operation: operator USHORT_T%1104923582
      virtual operator USHORT_T ();

      //## Operation: operator ULONG_T%1104923583
      virtual operator ULONG_T ();

      //## Operation: operator CHAR_T%1104923584
      virtual operator CHAR_T ();

      //## Operation: operator SHORT_T%1104923585
      virtual operator SHORT_T ();

      //## Operation: operator LONG_T%1104923586
      virtual operator LONG_T ();

      //## Operation: operator FLOAT_T%1110194505
      virtual operator FLOAT_T ();

      //## Operation: operator DOUBLE_T%1110194506
      virtual operator DOUBLE_T ();

      //## Operation: SetBit%1104923587
      virtual void SetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: ResetBit%1104923588
      virtual void ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetBit%1104923589
      virtual UCHAR_T GetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: SetPattern%1104923590
      virtual void SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetPattern%1104923591
      virtual ULONG_T GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: BytePos%1104923592
      virtual UCHAR_T BytePos (UCHAR_T data_type, UCHAR_T bit_pos);

  public:
    // Additional Public Declarations
      //## begin cNullOperator%41DBCB6503B9.public preserve=yes
      //## end cNullOperator%41DBCB6503B9.public

  protected:
    // Additional Protected Declarations
      //## begin cNullOperator%41DBCB6503B9.protected preserve=yes
      //## end cNullOperator%41DBCB6503B9.protected

  private:
    // Additional Private Declarations
      //## begin cNullOperator%41DBCB6503B9.private preserve=yes
      //## end cNullOperator%41DBCB6503B9.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNullOperator%41DBCB6503B9.implementation preserve=yes
      //## end cNullOperator%41DBCB6503B9.implementation

};

//## begin cNullOperator%41DBCB6503B9.postscript preserve=yes
//## end cNullOperator%41DBCB6503B9.postscript

// Class cNullOperator 

//## begin module%41DBCB6503B9.epilog preserve=yes
//## end module%41DBCB6503B9.epilog


#endif
