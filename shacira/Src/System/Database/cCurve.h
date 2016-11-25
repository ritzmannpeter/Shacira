//## begin module%4045D069007D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4045D069007D.cm

//## begin module%4045D069007D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4045D069007D.cp

//## Module: cCurve%4045D069007D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cCurve.h

#ifndef cCurve_h
#define cCurve_h 1

//## begin module%4045D069007D.includes preserve=yes
//## end module%4045D069007D.includes

//## begin module%4045D069007D.additionalDeclarations preserve=yes

typedef struct curve_header {
   ULONG_T buf_size;
   ULONG_T coords;
   ULONG_T data;
}  CURVE_HEADER_T;

typedef struct coord {
   double x;
   double y;
}  COORD_T;

//## end module%4045D069007D.additionalDeclarations


//## begin cCurve%4045D069007D.preface preserve=yes
//## end cCurve%4045D069007D.preface

//## Class: cCurve%4045D069007D
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCurve 
{
  //## begin cCurve%4045D069007D.initialDeclarations preserve=yes
public:
  //## end cCurve%4045D069007D.initialDeclarations

    //## Constructors (generated)
      cCurve();

      cCurve(const cCurve &right);

    //## Constructors (specified)
      //## Operation: cCurve%1078318183
      cCurve (BUF_T buf);

      //## Operation: cCurve%1078318184
      cCurve (ULONG_T coords);

    //## Destructor (generated)
      virtual ~cCurve();


    //## Other Operations (specified)
      //## Operation: IsEmpty%1078318185
      BOOL_T IsEmpty ();

      //## Operation: GetCurveSize%1078318186
      ULONG_T GetCurveSize ();

      //## Operation: GetCurveData%1078318187
      BUF_T GetCurveData ();

      //## Operation: GetXVec%1078318188
      void GetXVec (DOUBLE_T *xvec, ULONG_T coords);

      //## Operation: GetYVec%1078318189
      void GetYVec (DOUBLE_T *yvec, ULONG_T coords);

      //## Operation: GetSize%1078318190
      ULONG_T GetSize ();

      //## Operation: GetData%1078318191
      BUF_T GetData ();

      //## Operation: GetCoord%1078318192
      void GetCoord (ULONG_T pos, DOUBLE_T &x, DOUBLE_T &y);

      //## Operation: SetCoord%1078318193
      void SetCoord (ULONG_T pos, DOUBLE_T x, DOUBLE_T y);

  public:
    // Additional Public Declarations
      //## begin cCurve%4045D069007D.public preserve=yes
      //## end cCurve%4045D069007D.public

  protected:
    // Additional Protected Declarations
      //## begin cCurve%4045D069007D.protected preserve=yes
      //## end cCurve%4045D069007D.protected

  private:
    // Additional Private Declarations
      //## begin cCurve%4045D069007D.private preserve=yes
      //## end cCurve%4045D069007D.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Coords%4045D1A10109
      //## begin cCurve::Coords%4045D1A10109.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Coords;
      //## end cCurve::Coords%4045D1A10109.attr

      //## Attribute: CurveHeader%4045D1BD0128
      //## begin cCurve::CurveHeader%4045D1BD0128.attr preserve=no  implementation: CURVE_HEADER_T * {U} NULL
      CURVE_HEADER_T *_CurveHeader;
      //## end cCurve::CurveHeader%4045D1BD0128.attr

      //## Attribute: BufSize%4045D21203A9
      //## begin cCurve::BufSize%4045D21203A9.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _BufSize;
      //## end cCurve::BufSize%4045D21203A9.attr

      //## Attribute: Buffer%4045D21D001F
      //## begin cCurve::Buffer%4045D21D001F.attr preserve=no  implementation: BUF_T {U} NULL
      BUF_T _Buffer;
      //## end cCurve::Buffer%4045D21D001F.attr

      //## Attribute: CurveData%4045D22F0128
      //## begin cCurve::CurveData%4045D22F0128.attr preserve=no  implementation: BUF_T {U} NULL
      BUF_T _CurveData;
      //## end cCurve::CurveData%4045D22F0128.attr

      //## Attribute: BufferAllocated%40501F9D01D4
      //## begin cCurve::BufferAllocated%40501F9D01D4.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _BufferAllocated;
      //## end cCurve::BufferAllocated%40501F9D01D4.attr

    // Additional Implementation Declarations
      //## begin cCurve%4045D069007D.implementation preserve=yes
      //## end cCurve%4045D069007D.implementation

};

//## begin cCurve%4045D069007D.postscript preserve=yes
//## end cCurve%4045D069007D.postscript

// Class cCurve 

//## begin module%4045D069007D.epilog preserve=yes
//## end module%4045D069007D.epilog


#endif
