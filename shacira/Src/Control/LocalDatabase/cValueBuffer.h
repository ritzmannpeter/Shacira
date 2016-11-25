//## begin module%3C6A7DFE0288.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C6A7DFE0288.cm

//## begin module%3C6A7DFE0288.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C6A7DFE0288.cp

//## Module: cValueBuffer%3C6A7DFE0288; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cValueBuffer.h

#ifndef cValueBuffer_h
#define cValueBuffer_h 1

//## begin module%3C6A7DFE0288.includes preserve=yes
//## end module%3C6A7DFE0288.includes


class __DLL_EXPORT__ cSHVariant;

//## begin module%3C6A7DFE0288.additionalDeclarations preserve=yes
//## end module%3C6A7DFE0288.additionalDeclarations


//## begin cValueBuffer%3C6A7DFE0288.preface preserve=yes
//## end cValueBuffer%3C6A7DFE0288.preface

//## Class: cValueBuffer%3C6A7DFE0288; implementation
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EF864A1008C;cSHVariant { -> F}

class __DLL_EXPORT__ cValueBuffer 
{
  //## begin cValueBuffer%3C6A7DFE0288.initialDeclarations preserve=yes
public:
  //## end cValueBuffer%3C6A7DFE0288.initialDeclarations

    //## Constructors (generated)
      cValueBuffer();

      cValueBuffer(const cValueBuffer &right);

    //## Constructors (specified)
      //## Operation: cValueBuffer%1013620385
      cValueBuffer (UCHAR_T data_type, ULONG_T elements, ULONG_T element_size);

    //## Destructor (generated)
      virtual ~cValueBuffer();


    //## Other Operations (specified)
      //## Operation: ValueSize%1071244255
      ULONG_T ValueSize ();

      //## Operation: Get%1056464037
      virtual void Get (ULONG_T pos, CHAR_T &value);

      //## Operation: Get%1056464038
      virtual void Get (ULONG_T pos, UCHAR_T &value);

      //## Operation: Get%1056464039
      virtual void Get (ULONG_T pos, SHORT_T &value);

      //## Operation: Get%1056464040
      virtual void Get (ULONG_T pos, USHORT_T &value);

      //## Operation: Get%1015514460
      virtual void Get (ULONG_T pos, LONG_T &value);

      //## Operation: Get%1056464041
      void Get (ULONG_T pos, ULONG_T &value);

      //## Operation: Get%1056464042
      virtual void Get (ULONG_T pos, FLOAT_T &value);

      //## Operation: Get%1015514462
      void Get (ULONG_T pos, DOUBLE_T &value);

      //## Operation: Get%1015514458
      virtual void Get (ULONG_T pos, STRING_T &value);

      //## Operation: Get%1056464044
      virtual void Get (ULONG_T pos, WSTRING_T &value);

      //## Operation: Get%1071244156
      virtual void Get (ULONG_T pos, BUF_T &buf);

      //## Operation: Get%1071244157
      virtual void Get (ULONG_T pos, BUF_T buf, ULONG_T len, ULONG_T buf_size);

      //## Operation: Set%1056464045
      virtual BOOL_T Set (ULONG_T pos, CHAR_T value);

      //## Operation: Set%1056464046
      virtual BOOL_T Set (ULONG_T pos, UCHAR_T value);

      //## Operation: Set%1056464047
      virtual BOOL_T Set (ULONG_T pos, SHORT_T value);

      //## Operation: Set%1056464048
      virtual BOOL_T Set (ULONG_T pos, USHORT_T value);

      //## Operation: Set%1015514461
      virtual BOOL_T Set (ULONG_T pos, LONG_T value);

      //## Operation: Set%1056464049
      virtual BOOL_T Set (ULONG_T pos, ULONG_T value);

      //## Operation: Set%1056464050
      virtual BOOL_T Set (ULONG_T pos, FLOAT_T value);

      //## Operation: Set%1015514463
      virtual BOOL_T Set (ULONG_T pos, DOUBLE_T value);

      //## Operation: Set%1056464051
      virtual BOOL_T Set (ULONG_T pos, UCHAR_T *buf, ULONG_T len);

      //## Operation: Set%1015514459
      virtual BOOL_T Set (ULONG_T pos, CHAR_T *value);

      //## Operation: Set%1056464053
      virtual BOOL_T Set (ULONG_T pos, const CHAR_T *value);

      //## Operation: Set%1056464052
      virtual BOOL_T Set (ULONG_T pos, WCHAR_T *value);

      //## Operation: Set%1056464054
      virtual BOOL_T Set (ULONG_T pos, const WCHAR_T *value);

      //## Operation: Set%1071244158
      virtual BOOL_T Set (ULONG_T pos, CONST_BUF_T buf, ULONG_T len);

      //## Operation: GetBuf%1077613264
      BUF_T GetBuf ();

      //## Operation: GetBufSize%1077613265
      ULONG_T GetBufSize ();

  public:
    // Additional Public Declarations
      //## begin cValueBuffer%3C6A7DFE0288.public preserve=yes
      //## end cValueBuffer%3C6A7DFE0288.public

  protected:
    // Additional Protected Declarations
      //## begin cValueBuffer%3C6A7DFE0288.protected preserve=yes
      //## end cValueBuffer%3C6A7DFE0288.protected

  private:
    // Additional Private Declarations
      //## begin cValueBuffer%3C6A7DFE0288.private preserve=yes
      //## end cValueBuffer%3C6A7DFE0288.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AllocBuf%1056621172
      UCHAR_T * AllocBuf (ULONG_T size);

      //## Operation: FreeBuf%1056621173
      void FreeBuf (UCHAR_T *buf);

    // Data Members for Class Attributes

      //## Attribute: DataType%3C87865E00D0
      //## begin cValueBuffer::DataType%3C87865E00D0.attr preserve=no  implementation: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cValueBuffer::DataType%3C87865E00D0.attr

      //## Attribute: Elements%3C8786170395
      //## begin cValueBuffer::Elements%3C8786170395.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Elements;
      //## end cValueBuffer::Elements%3C8786170395.attr

      //## Attribute: ElementSize%3C878683014C
      //## begin cValueBuffer::ElementSize%3C878683014C.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ElementSize;
      //## end cValueBuffer::ElementSize%3C878683014C.attr

      //## Attribute: Size%3C87868E0089
      //## begin cValueBuffer::Size%3C87868E0089.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Size;
      //## end cValueBuffer::Size%3C87868E0089.attr

      //## Attribute: Buffer%3C6D1E8B0224
      //## begin cValueBuffer::Buffer%3C6D1E8B0224.attr preserve=no  implementation: UCHAR_T * {U} NULL
      UCHAR_T *_Buffer;
      //## end cValueBuffer::Buffer%3C6D1E8B0224.attr

    // Additional Implementation Declarations
      //## begin cValueBuffer%3C6A7DFE0288.implementation preserve=yes
      //## end cValueBuffer%3C6A7DFE0288.implementation

};

//## begin cValueBuffer%3C6A7DFE0288.postscript preserve=yes
//## end cValueBuffer%3C6A7DFE0288.postscript

// Class cValueBuffer 

//## begin module%3C6A7DFE0288.epilog preserve=yes
//## end module%3C6A7DFE0288.epilog


#endif
