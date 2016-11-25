//## begin module%41413E860232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41413E860232.cm

//## begin module%41413E860232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41413E860232.cp

//## Module: cFlatObject%41413E860232; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cFlatObject.h

#ifndef cFlatObject_h
#define cFlatObject_h 1

//## begin module%41413E860232.includes preserve=yes
//## end module%41413E860232.includes


class __DLL_EXPORT__ cVarRef;

//## begin module%41413E860232.additionalDeclarations preserve=yes

#define FLAT_OBJECT_HEADER_SIZE  0x100
#define OBJECT_NAME_LEN          0x80
#define FLAT_OBJECT_SIGNATURE    0x02020202
#define FO_OBJECT_RING           1
#define FO_GRAPHIC_CURVE         2

#include "Pack_1"

typedef struct {
   ULONG_T flat_object_type;
   ULONG_T flat_object_signature;
   ULONG_T header_size;
   PTR_T data;
   ULONG_T data_size;
   PTR_T object_data;
   ULONG_T object_data_size;
   CHAR_T object_name[OBJECT_NAME_LEN];
}  FLAT_OBJECT_HEADER_T;

#include "UnPack"

//## end module%41413E860232.additionalDeclarations


//## begin cFlatObject%41413E860232.preface preserve=yes
//## end cFlatObject%41413E860232.preface

//## Class: cFlatObject%41413E860232
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%41D2CAA400DA;cVarRef { -> F}

class __DLL_EXPORT__ cFlatObject 
{
  //## begin cFlatObject%41413E860232.initialDeclarations preserve=yes
public:
  //## end cFlatObject%41413E860232.initialDeclarations

    //## Constructors (generated)
      cFlatObject();

      cFlatObject(const cFlatObject &right);

    //## Constructors (specified)
      //## Operation: cFlatObject%1104332377
      cFlatObject (cVarRef *var_ref);

      //## Operation: cFlatObject%1094795547
      cFlatObject (PTR_T data, ULONG_T data_size);

      //## Operation: cFlatObject%1095144437
      cFlatObject (PTR_T data);

    //## Destructor (generated)
      virtual ~cFlatObject();


    //## Other Operations (specified)
      //## Operation: GetHeader%1094795548
      virtual PTR_T GetHeader ();

      //## Operation: GetHeaderSize%1094795549
      virtual ULONG_T GetHeaderSize ();

      //## Operation: GetData%1094795550
      virtual PTR_T GetData ();

      //## Operation: GetDataSize%1094795551
      virtual ULONG_T GetDataSize ();

      //## Operation: GetObjectData%1094795552
      virtual PTR_T GetObjectData ();

      //## Operation: GetObjectDataSize%1094795553
      virtual ULONG_T GetObjectDataSize ();

      //## Operation: SetObjectName%1110025033
      virtual void SetObjectName (CONST_STRING_T object_name);

      //## Operation: GetObjectName%1110025034
      virtual CONST_STRING_T GetObjectName ();

      //## Operation: IsValid%1151501385
      virtual BOOL_T IsValid ();

  public:
    // Additional Public Declarations
      //## begin cFlatObject%41413E860232.public preserve=yes
      //## end cFlatObject%41413E860232.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: Header%41413EFF034B
      //## begin cFlatObject::Header%41413EFF034B.attr preserve=no  protected: PTR_T {U} NULL
      PTR_T _Header;
      //## end cFlatObject::Header%41413EFF034B.attr

      //## Attribute: Data%41413EFF034C
      //## begin cFlatObject::Data%41413EFF034C.attr preserve=no  protected: PTR_T {U} NULL
      PTR_T _Data;
      //## end cFlatObject::Data%41413EFF034C.attr

      //## Attribute: ObjectValid%42245BFD03A9
      //## begin cFlatObject::ObjectValid%42245BFD03A9.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _ObjectValid;
      //## end cFlatObject::ObjectValid%42245BFD03A9.attr

    // Additional Protected Declarations
      //## begin cFlatObject%41413E860232.protected preserve=yes
      //## end cFlatObject%41413E860232.protected

  private:
    // Additional Private Declarations
      //## begin cFlatObject%41413E860232.private preserve=yes
      //## end cFlatObject%41413E860232.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFlatObject%41413E860232.implementation preserve=yes
      //## end cFlatObject%41413E860232.implementation

};

//## begin cFlatObject%41413E860232.postscript preserve=yes
//## end cFlatObject%41413E860232.postscript

// Class cFlatObject 

//## begin module%41413E860232.epilog preserve=yes
//## end module%41413E860232.epilog


#endif
