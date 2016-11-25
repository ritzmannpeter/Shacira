//## begin module%3CFDF5550396.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CFDF5550396.cm

//## begin module%3CFDF5550396.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CFDF5550396.cp

//## Module: cDataChange%3CFDF5550396; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cDataChange.h

#ifndef cDataChange_h
#define cDataChange_h 1

//## begin module%3CFDF5550396.includes preserve=yes
//## end module%3CFDF5550396.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cTransferObject;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cBlob;

//## begin module%3CFDF5550396.additionalDeclarations preserve=yes

/// change flags
#define CH_FLAG_FILE_INPUT     0x00000001

#include "Pack_1"

typedef struct {
   TRANSIENT_OBJECT_T transient_object;
   char var_name[TEXT_LENGTH+1];
   LONG_T var_id;
   LONG_T index1;
   LONG_T index2;
   LONG_T index3;
   LONG_T index4;
   char old_value[TEXT_LENGTH+1];
   char value[TEXT_LENGTH+1];
}  DATA_CHANGE_OBJECT_T;

#include "UnPack"

//## end module%3CFDF5550396.additionalDeclarations


//## begin cDataChange%3CFDF5550396.preface preserve=yes
//## end cDataChange%3CFDF5550396.preface

//## Class: cDataChange%3CFDF5550396
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E106DEB0227;cVarRef { -> F}
//## Uses: <unnamed>%3E5A57E501FD;cTransferObject { -> F}
//## Uses: <unnamed>%402C887F0119;cBlob { -> F}
//## Uses: <unnamed>%41662E9D0177;cStringUtils { -> F}

class __DLL_EXPORT__ cDataChange : public cTransientObject  //## Inherits: <unnamed>%3E5A507E0343
{
  //## begin cDataChange%3CFDF5550396.initialDeclarations preserve=yes
public:
  //## end cDataChange%3CFDF5550396.initialDeclarations

    //## Constructors (generated)
      cDataChange();

      cDataChange(const cDataChange &right);

    //## Constructors (specified)
      //## Operation: cDataChange%1023287637
      cDataChange (CONST_STRING_T var_name, LONG_T var_id, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: cDataChange%1073900392
      cDataChange (CONST_STRING_T var_name, LONG_T var_id, BUF_T buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

    //## Destructor (generated)
      virtual ~cDataChange();


    //## Other Operations (specified)
      //## Operation: Serialize%1023780987
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023780988
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: VarName%3CFDF6240023
      STRING_T get_VarName () const;
      void set_VarName (STRING_T value);

      //## Attribute: VarId%3D08572D0224
      LONG_T get_VarId () const;
      void set_VarId (LONG_T value);

      //## Attribute: Index1%3D0856C6003B
      LONG_T get_Index1 () const;
      void set_Index1 (LONG_T value);

      //## Attribute: Index2%3D0856E0034F
      LONG_T get_Index2 () const;
      void set_Index2 (LONG_T value);

      //## Attribute: Index3%3D0856E20077
      LONG_T get_Index3 () const;
      void set_Index3 (LONG_T value);

      //## Attribute: Index4%3D0856E301FF
      LONG_T get_Index4 () const;
      void set_Index4 (LONG_T value);

      //## Attribute: OldValue%3E79A29F035B
      STRING_T get_OldValue () const;
      void set_OldValue (STRING_T value);

      //## Attribute: Value%3CFDF624002D
      STRING_T get_Value () const;
      void set_Value (STRING_T value);

      //## Attribute: BufPtr%40026F620222
      BUF_T get_BufPtr () const;
      void set_BufPtr (BUF_T value);

      //## Attribute: DataSet%4039EC2C007D
      ULONG_T get_DataSet () const;
      void set_DataSet (ULONG_T value);

      //## Attribute: State%429AB70B02AF
      ULONG_T get_State () const;
      void set_State (ULONG_T value);

      //## Attribute: DataType%40228F66006D
      ULONG_T get_DataType () const;
      void set_DataType (ULONG_T value);

      //## Attribute: VarType%417CCF4500AB
      ULONG_T get_VarType () const;
      void set_VarType (ULONG_T value);

      //## Attribute: Precision%40D09ACA0196
      ULONG_T get_Precision () const;
      void set_Precision (ULONG_T value);

      //## Attribute: ValueSize%40228F83004E
      ULONG_T get_ValueSize () const;
      void set_ValueSize (ULONG_T value);

      //## Attribute: PersistenceType%403B2E9402AF
      ULONG_T get_PersistenceType () const;
      void set_PersistenceType (ULONG_T value);

      //## Attribute: TimeOffset%40228F44031C
      ULONG_T get_TimeOffset () const;
      void set_TimeOffset (ULONG_T value);

      //## Attribute: Pos%429ABA0B0148
      ULONG_T get_Pos () const;
      void set_Pos (ULONG_T value);

      ULONG_T get_UnitCode () const;
      void set_UnitCode (ULONG_T value);
      STRING_T get_UnitText () const;
      void set_UnitText (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cDataChange%3CFDF5550396.public preserve=yes
      //## end cDataChange%3CFDF5550396.public

  protected:
    // Data Members for Class Attributes

      //## begin cDataChange::VarName%3CFDF6240023.attr preserve=no  public: STRING_T {U} 
      STRING_T _VarName;
      //## end cDataChange::VarName%3CFDF6240023.attr

      //## begin cDataChange::VarId%3D08572D0224.attr preserve=no  public: LONG_T {U} -1
      LONG_T _VarId;
      //## end cDataChange::VarId%3D08572D0224.attr

      //## begin cDataChange::Index1%3D0856C6003B.attr preserve=no  public: LONG_T {U} -1
      LONG_T _Index1;
      //## end cDataChange::Index1%3D0856C6003B.attr

      //## begin cDataChange::Index2%3D0856E0034F.attr preserve=no  public: LONG_T {U} -1
      LONG_T _Index2;
      //## end cDataChange::Index2%3D0856E0034F.attr

      //## begin cDataChange::Index3%3D0856E20077.attr preserve=no  public: LONG_T {U} -1
      LONG_T _Index3;
      //## end cDataChange::Index3%3D0856E20077.attr

      //## begin cDataChange::Index4%3D0856E301FF.attr preserve=no  public: LONG_T {U} -1
      LONG_T _Index4;
      //## end cDataChange::Index4%3D0856E301FF.attr

      //## begin cDataChange::OldValue%3E79A29F035B.attr preserve=no  public: STRING_T {U} 
      STRING_T _OldValue;
      //## end cDataChange::OldValue%3E79A29F035B.attr

      //## begin cDataChange::Value%3CFDF624002D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Value;
      //## end cDataChange::Value%3CFDF624002D.attr

      //## begin cDataChange::BufPtr%40026F620222.attr preserve=no  public: BUF_T {U} NULL
      BUF_T _BufPtr;
      //## end cDataChange::BufPtr%40026F620222.attr

      //## begin cDataChange::DataSet%4039EC2C007D.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _DataSet;
      //## end cDataChange::DataSet%4039EC2C007D.attr

      //## begin cDataChange::State%429AB70B02AF.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _State;
      //## end cDataChange::State%429AB70B02AF.attr

      //## begin cDataChange::DataType%40228F66006D.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _DataType;
      //## end cDataChange::DataType%40228F66006D.attr

      //## begin cDataChange::VarType%417CCF4500AB.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _VarType;
      //## end cDataChange::VarType%417CCF4500AB.attr

      //## begin cDataChange::Precision%40D09ACA0196.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Precision;
      //## end cDataChange::Precision%40D09ACA0196.attr

      //## begin cDataChange::ValueSize%40228F83004E.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ValueSize;
      //## end cDataChange::ValueSize%40228F83004E.attr

      //## begin cDataChange::PersistenceType%403B2E9402AF.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _PersistenceType;
      //## end cDataChange::PersistenceType%403B2E9402AF.attr

      //## begin cDataChange::TimeOffset%40228F44031C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TimeOffset;
      //## end cDataChange::TimeOffset%40228F44031C.attr

      //## begin cDataChange::Pos%429ABA0B0148.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Pos;
      //## end cDataChange::Pos%429ABA0B0148.attr

      ULONG_T _UnitCode;
      STRING_T _UnitText;

    // Additional Protected Declarations
      //## begin cDataChange%3CFDF5550396.protected preserve=yes
      //## end cDataChange%3CFDF5550396.protected

  private:
    // Additional Private Declarations
      //## begin cDataChange%3CFDF5550396.private preserve=yes
      //## end cDataChange%3CFDF5550396.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDataChange%3CFDF5550396.implementation preserve=yes
      //## end cDataChange%3CFDF5550396.implementation

private:
   ULONG_T _ChangeFlags;
public:
   ULONG_T get_ChangeFlags () const;
   void set_ChangeFlags (ULONG_T value);
};

//## begin cDataChange%3CFDF5550396.postscript preserve=yes
//## end cDataChange%3CFDF5550396.postscript

// Class cDataChange 

//## begin module%3CFDF5550396.epilog preserve=yes
//## end module%3CFDF5550396.epilog


#endif
