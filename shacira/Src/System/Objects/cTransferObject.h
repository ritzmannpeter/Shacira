//## begin module%3E5A568D005E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E5A568D005E.cm

//## begin module%3E5A568D005E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E5A568D005E.cp

//## Module: cTransferObject%3E5A568D005E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cTransferObject.h

#ifndef cTransferObject_h
#define cTransferObject_h 1

//## begin module%3E5A568D005E.includes preserve=yes
//## end module%3E5A568D005E.includes

// cTokenizer
#include "System/cTokenizer.h"
// cTimeObject
#include "System/cTimeObject.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cMemoryPtr;

//## begin module%3E5A568D005E.additionalDeclarations preserve=yes

typedef enum {ObjectHeader,
              ObjectBody,
              ObjectParams,
              ObjectParamValues,
              ObjectFlags} AreaType;

//## end module%3E5A568D005E.additionalDeclarations


//## begin cTransferObject%3E5A568D005E.preface preserve=yes
//## end cTransferObject%3E5A568D005E.preface

//## Class: cTransferObject%3E5A568D005E
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A617C035C;cTimeObject { -> }
//## Uses: <unnamed>%3E704EBB02AF;cTokenizer { -> }
//## Uses: <unnamed>%4165879603D8;cObjectLock { -> F}
//## Uses: <unnamed>%43D369A50037;cMemoryPtr { -> F}

class __DLL_EXPORT__ cTransferObject 
{
  //## begin cTransferObject%3E5A568D005E.initialDeclarations preserve=yes
public:
  //## end cTransferObject%3E5A568D005E.initialDeclarations

    //## Constructors (generated)
      cTransferObject();

      cTransferObject(const cTransferObject &right);

    //## Constructors (specified)
      //## Operation: cTransferObject%1047469645
      cTransferObject (CONST_STRING_T serialized_object);

    //## Destructor (generated)
      virtual ~cTransferObject();


    //## Other Operations (specified)
      //## Operation: Parse%1046095020
      INT_T Parse (CONST_STRING_T serialized_obj);

      //## Operation: ObjectType%1047543049
      static INT_T ObjectType (CONST_STRING_T serialized_obj);

      //## Operation: AddAttribute%1046094996
      void AddAttribute (ULONG_T index, CONST_STRING_T value, AreaType area);

      //## Operation: AddAttribute%1046095001
      void AddAttribute (ULONG_T index, LONG_T value, AreaType area);

      //## Operation: AddAttribute%1046095006
      void AddAttribute (ULONG_T index, ULONG_T value, AreaType area);

      //## Operation: AddAttribute%1046095016
      void AddAttribute (ULONG_T index, INT_T value, AreaType area);

      //## Operation: AddAttribute%1046095002
      void AddAttribute (ULONG_T index, DOUBLE_T value, AreaType area);

      //## Operation: AddAttribute%1046095007
      void AddAttribute (ULONG_T index, BOOL_T value, AreaType area);

      //## Operation: AddAttribute%1046095013
      void AddAttribute (ULONG_T index, cTimeObject &value, AreaType area);

      //## Operation: AddAttribute%1051102667
      void AddAttribute (ULONG_T index, void *value, AreaType area);

      //## Operation: GetAttribute%1046095008
      void GetAttribute (ULONG_T index, STRING_T &value, AreaType area);

      //## Operation: GetAttribute%1046095009
      void GetAttribute (ULONG_T index, LONG_T &value, AreaType area);

      //## Operation: GetAttribute%1046095010
      void GetAttribute (ULONG_T index, ULONG_T &value, AreaType area);

      //## Operation: GetAttribute%1046095017
      void GetAttribute (ULONG_T index, INT_T &value, AreaType area);

      //## Operation: GetAttribute%1046095011
      void GetAttribute (ULONG_T index, DOUBLE_T &value, AreaType area);

      //## Operation: GetAttribute%1046095012
      void GetAttribute (ULONG_T index, BOOL_T &value, AreaType area);

      //## Operation: GetAttribute%1046095014
      void GetAttribute (ULONG_T index, cTimeObject &value, AreaType area);

      //## Operation: GetAttribute%1051102668
      void GetAttribute (ULONG_T index, void * &value, AreaType area);

      //## Operation: Params%1047655607
      ULONG_T Params ();

      //## Operation: Serialize%1046095005
      STRING_T Serialize ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Type%3E703CFF008C
      INT_T get_Type () const;
      void set_Type (INT_T value);

      //## Attribute: SubType%3FBF5D980177
      INT_T get_SubType () const;
      void set_SubType (INT_T value);

  public:
    // Additional Public Declarations
      //## begin cTransferObject%3E5A568D005E.public preserve=yes
      //## end cTransferObject%3E5A568D005E.public

  protected:
    // Data Members for Class Attributes

      //## begin cTransferObject::Type%3E703CFF008C.attr preserve=no  public: INT_T {U} UNDEFINED
      INT_T _Type;
      //## end cTransferObject::Type%3E703CFF008C.attr

      //## begin cTransferObject::SubType%3FBF5D980177.attr preserve=no  public: INT_T {U} UNDEFINED
      INT_T _SubType;
      //## end cTransferObject::SubType%3FBF5D980177.attr

    // Additional Protected Declarations
      //## begin cTransferObject%3E5A568D005E.protected preserve=yes
      //## end cTransferObject%3E5A568D005E.protected

  private:
    // Additional Private Declarations
      //## begin cTransferObject%3E5A568D005E.private preserve=yes
      //## end cTransferObject%3E5A568D005E.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetVec%1047469646
      STRING_VECTOR_T * GetVec (AreaType area, ULONG_T index);

      //## Operation: GetVec%1047469647
      STRING_VECTOR_T * GetVec (AreaType area);

    // Data Members for Class Attributes

      //## Attribute: SerializedObject%3E6F7B9700AB
      //## begin cTransferObject::SerializedObject%3E6F7B9700AB.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _SerializedObject;
      //## end cTransferObject::SerializedObject%3E6F7B9700AB.attr

      //## Attribute: Header%3E5A56C302AA
      //## begin cTransferObject::Header%3E5A56C302AA.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Header;
      //## end cTransferObject::Header%3E5A56C302AA.attr

      //## Attribute: Body%3E6F899101F4
      //## begin cTransferObject::Body%3E6F899101F4.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Body;
      //## end cTransferObject::Body%3E6F899101F4.attr

      //## Attribute: Parameters%3E5A56DF00D4
      //## begin cTransferObject::Parameters%3E5A56DF00D4.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Parameters;
      //## end cTransferObject::Parameters%3E5A56DF00D4.attr

      //## Attribute: ParameterValues%3E720ABA00DA
      //## begin cTransferObject::ParameterValues%3E720ABA00DA.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _ParameterValues;
      //## end cTransferObject::ParameterValues%3E720ABA00DA.attr

      //## Attribute: ParseBuf%41657781033C
      //## begin cTransferObject::ParseBuf%41657781033C.attr preserve=no  implementation: static cMemoryPtr * {U} NULL
      static cMemoryPtr *_ParseBuf;
      //## end cTransferObject::ParseBuf%41657781033C.attr

      //## Attribute: BufMutex%4165875700BB
      //## begin cTransferObject::BufMutex%4165875700BB.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _BufMutex;
      //## end cTransferObject::BufMutex%4165875700BB.attr

      //## Attribute: Flags%41AC0C380148
      //## begin cTransferObject::Flags%41AC0C380148.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Flags;
      //## end cTransferObject::Flags%41AC0C380148.attr

    // Additional Implementation Declarations
      //## begin cTransferObject%3E5A568D005E.implementation preserve=yes
      //## end cTransferObject%3E5A568D005E.implementation

};

//## begin cTransferObject%3E5A568D005E.postscript preserve=yes
//## end cTransferObject%3E5A568D005E.postscript

// Class cTransferObject 

//## begin module%3E5A568D005E.epilog preserve=yes
//## end module%3E5A568D005E.epilog


#endif
