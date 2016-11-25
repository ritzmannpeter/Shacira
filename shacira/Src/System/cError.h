//## begin module%39AB9829007C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%39AB9829007C.cm

//## begin module%39AB9829007C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%39AB9829007C.cp

//## Module: cError%39AB9829007C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cError.h

#ifndef cError_h
#define cError_h 1

//## begin module%39AB9829007C.includes preserve=yes
//## end module%39AB9829007C.includes


class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cText;

//## begin module%39AB9829007C.additionalDeclarations preserve=yes

#include "System/Text/SystemText.h"

//## end module%39AB9829007C.additionalDeclarations


//## begin cError%39AB9829007C.preface preserve=yes
//## end cError%39AB9829007C.preface

//## Class: cError%39AB9829007C
//	cError is the base Exception class used in the Shacira
//	framework.
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D24426C02BE;cStringUtils { -> F}
//## Uses: <unnamed>%3DE1FD0E02BC;cConvUtils { -> F}
//## Uses: <unnamed>%42412BD80232;cText { -> F}

class __DLL_EXPORT__ cError 
{
  //## begin cError%39AB9829007C.initialDeclarations preserve=yes
public:
  //## end cError%39AB9829007C.initialDeclarations

    //## Constructors (generated)
      cError();

      cError(const cError &right);

    //## Constructors (specified)
      //## Operation: cError%967547765
      cError (LONG_T text_id, LONG_T native_code = 0, CONST_STRING_T param1 = NULL, CONST_STRING_T param2 = NULL, CONST_STRING_T param3 = NULL, CONST_STRING_T param4 = NULL);

      //## Operation: cError%1111566664
      cError (STRING_T text, LONG_T native_code, CONST_STRING_T param1 = NULL, CONST_STRING_T param2 = NULL, CONST_STRING_T param3 = NULL, CONST_STRING_T param4 = NULL);

    //## Destructor (generated)
      virtual ~cError();


    //## Other Operations (specified)
      //## Operation: TextIndex%1093344841
      virtual ULONG_T TextIndex ();

      //## Operation: ErrMsg%1014996956
      virtual STRING_T ErrMsg ();

      //## Operation: operator CONST_STRING_T%989323343
      virtual operator CONST_STRING_T ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ErrCode%39ABB5A40088
      INT_T get_ErrCode () const;
      void set_ErrCode (INT_T value);

      //## Attribute: NativeCode%3A914EC7003F
      LONG_T get_NativeCode () const;
      void set_NativeCode (LONG_T value);

      //## Attribute: Text%424129210109
      STRING_T get_Text () const;
      void set_Text (STRING_T value);

      //## Attribute: Params%3A922DBF0094
      ULONG_T get_Params () const;

      //## Attribute: Param1%39ABB5DF001F
      STRING_T get_Param1 () const;
      void set_Param1 (STRING_T value);

      //## Attribute: Param2%3A914EFE00CA
      STRING_T get_Param2 () const;
      void set_Param2 (STRING_T value);

      //## Attribute: Param3%3A914EFF0343
      STRING_T get_Param3 () const;
      void set_Param3 (STRING_T value);

      //## Attribute: Param4%3A914F010219
      STRING_T get_Param4 () const;
      void set_Param4 (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cError%39AB9829007C.public preserve=yes
      //## end cError%39AB9829007C.public

  protected:
    // Data Members for Class Attributes

      //## begin cError::ErrCode%39ABB5A40088.attr preserve=no  public: INT_T {U} 0
      INT_T _ErrCode;
      //## end cError::ErrCode%39ABB5A40088.attr

      //## begin cError::NativeCode%3A914EC7003F.attr preserve=no  public: LONG_T {U} 0
      LONG_T _NativeCode;
      //## end cError::NativeCode%3A914EC7003F.attr

      //## begin cError::Text%424129210109.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text;
      //## end cError::Text%424129210109.attr

      //## begin cError::Params%3A922DBF0094.attr preserve=no  public: ULONG_T {U} 
      ULONG_T _Params;
      //## end cError::Params%3A922DBF0094.attr

      //## begin cError::Param1%39ABB5DF001F.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param1;
      //## end cError::Param1%39ABB5DF001F.attr

      //## begin cError::Param2%3A914EFE00CA.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param2;
      //## end cError::Param2%3A914EFE00CA.attr

      //## begin cError::Param3%3A914EFF0343.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param3;
      //## end cError::Param3%3A914EFF0343.attr

      //## begin cError::Param4%3A914F010219.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param4;
      //## end cError::Param4%3A914F010219.attr

      //## Attribute: MsgText%3AF7E0C8013E
      //## begin cError::MsgText%3AF7E0C8013E.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _MsgText;
      //## end cError::MsgText%3AF7E0C8013E.attr

    // Additional Protected Declarations
      //## begin cError%39AB9829007C.protected preserve=yes
      //## end cError%39AB9829007C.protected

  private:
    // Additional Private Declarations
      //## begin cError%39AB9829007C.private preserve=yes
      //## end cError%39AB9829007C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SubstParams%1014996957
      virtual STRING_T SubstParams (CONST_STRING_T text);

    // Additional Implementation Declarations
      //## begin cError%39AB9829007C.implementation preserve=yes
      //## end cError%39AB9829007C.implementation

};

//## begin cError%39AB9829007C.postscript preserve=yes
//## end cError%39AB9829007C.postscript

// Class cError 

//## begin module%39AB9829007C.epilog preserve=yes
//## end module%39AB9829007C.epilog


#endif
