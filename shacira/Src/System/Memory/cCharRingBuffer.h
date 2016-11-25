//## begin module%3C348D8E0012.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C348D8E0012.cm

//## begin module%3C348D8E0012.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C348D8E0012.cp

//## Module: cCharRingBuffer%3C348D8E0012; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cCharRingBuffer.h

#ifndef cCharRingBuffer_h
#define cCharRingBuffer_h 1

//## begin module%3C348D8E0012.includes preserve=yes
//## end module%3C348D8E0012.includes

//## begin module%3C348D8E0012.additionalDeclarations preserve=yes
//## end module%3C348D8E0012.additionalDeclarations


//## begin cCharRingBuffer%3C348D8E0012.preface preserve=yes
//## end cCharRingBuffer%3C348D8E0012.preface

//## Class: cCharRingBuffer%3C348D8E0012
//	This class implements a character ring buffer.
//## Category: System::Memory%3DC92B0D00DE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCharRingBuffer 
{
  //## begin cCharRingBuffer%3C348D8E0012.initialDeclarations preserve=yes
public:
  //## end cCharRingBuffer%3C348D8E0012.initialDeclarations

    //## Constructors (generated)
      cCharRingBuffer();

      cCharRingBuffer(const cCharRingBuffer &right);

    //## Constructors (specified)
      //## Operation: cCharRingBuffer%1010077552
      //	Constructs a character ring buffer with a certain size.
      cCharRingBuffer (ULONG_T size);

    //## Destructor (generated)
      virtual ~cCharRingBuffer();


    //## Other Operations (specified)
      //## Operation: Put%1010077553
      //	Puts amount cahracters into the ring buffer.
      ULONG_T Put (CONST_STRING_T buffer, ULONG_T amount);

      //## Operation: Get%1010077554
      //	Gets amount cahracters into the ring buffer.
      ULONG_T Get (STRING_BUF_T buffer, ULONG_T amount);

      //## Operation: Clear%1010131285
      //	Clears the ring buffer.
      void Clear ();

      //## Operation: IsEmpty%1010077555
      //	Queries a ring buffer to determine if its empty or not.
      BOOL_T IsEmpty ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Buffer%3C348DD5010E
      STRING_BUF_T get_Buffer () const;

      //## Attribute: BufferSize%410FB86C0203
      ULONG_T get_BufferSize () const;

  public:
    // Additional Public Declarations
      //## begin cCharRingBuffer%3C348D8E0012.public preserve=yes
      //## end cCharRingBuffer%3C348D8E0012.public

  protected:
    // Data Members for Class Attributes

      //## begin cCharRingBuffer::Buffer%3C348DD5010E.attr preserve=no  public: STRING_BUF_T {U} NULL
      STRING_BUF_T _Buffer;
      //## end cCharRingBuffer::Buffer%3C348DD5010E.attr

      //## begin cCharRingBuffer::BufferSize%410FB86C0203.attr preserve=no  public: ULONG_T {U} 0x2000
      ULONG_T _BufferSize;
      //## end cCharRingBuffer::BufferSize%410FB86C0203.attr

    // Additional Protected Declarations
      //## begin cCharRingBuffer%3C348D8E0012.protected preserve=yes
      //## end cCharRingBuffer%3C348D8E0012.protected

  private:
    // Additional Private Declarations
      //## begin cCharRingBuffer%3C348D8E0012.private preserve=yes
      //## end cCharRingBuffer%3C348D8E0012.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CreateBuffer%1091549391
      void CreateBuffer ();

      //## Operation: Space%1091549392
      ULONG_T Space ();

      //## Operation: Fill%1091549393
      ULONG_T Fill ();

    // Data Members for Class Attributes

      //## Attribute: ReadPtr%3C348E39037F
      //## begin cCharRingBuffer::ReadPtr%3C348E39037F.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ReadPtr;
      //## end cCharRingBuffer::ReadPtr%3C348E39037F.attr

      //## Attribute: WritePtr%3C348E5902D1
      //## begin cCharRingBuffer::WritePtr%3C348E5902D1.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _WritePtr;
      //## end cCharRingBuffer::WritePtr%3C348E5902D1.attr

    // Additional Implementation Declarations
      //## begin cCharRingBuffer%3C348D8E0012.implementation preserve=yes
      //## end cCharRingBuffer%3C348D8E0012.implementation

};

//## begin cCharRingBuffer%3C348D8E0012.postscript preserve=yes
//## end cCharRingBuffer%3C348D8E0012.postscript

// Class cCharRingBuffer 

//## begin module%3C348D8E0012.epilog preserve=yes
//## end module%3C348D8E0012.epilog


#endif
