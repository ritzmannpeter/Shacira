//## begin module%3ABA1A7A023D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABA1A7A023D.cm

//## begin module%3ABA1A7A023D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3ABA1A7A023D.cp

//## Module: cInfo%3ABA1A7A023D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cInfo.h

#ifndef cInfo_h
#define cInfo_h 1

//## begin module%3ABA1A7A023D.includes preserve=yes
//## end module%3ABA1A7A023D.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%3ABA1A7A023D.additionalDeclarations preserve=yes
//## end module%3ABA1A7A023D.additionalDeclarations


//## begin cInfo%3ABA1A7A023D.preface preserve=yes
//## end cInfo%3ABA1A7A023D.preface

//## Class: cInfo%3ABA1A7A023D
//	A cInfo object can be used to transport general
//	informations that are semantically not bound through the
//	Shacira channel system.
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A57C0013C;cTransferObject { -> F}

class __DLL_EXPORT__ cInfo : public cTransientObject  //## Inherits: <unnamed>%3ABA1B2F00FC
{
  //## begin cInfo%3ABA1A7A023D.initialDeclarations preserve=yes
public:
  //## end cInfo%3ABA1A7A023D.initialDeclarations

    //## Constructors (generated)
      cInfo();

      cInfo(const cInfo &right);

    //## Constructors (specified)
      //## Operation: cInfo%985267668
      cInfo (cStaticObject *source, ULONG_T info_type, ULONG_T info_text_id, CONST_STRING_T info_text = NULL);

    //## Destructor (generated)
      virtual ~cInfo();


    //## Other Operations (specified)
      //## Operation: Serialize%1023780979
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023780980
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: InfoType%3E5B712C00D9
      ULONG_T get_InfoType () const;
      void set_InfoType (ULONG_T value);

      //## Attribute: InfoCustomType%41FFCD830203
      ULONG_T get_InfoCustomType () const;
      void set_InfoCustomType (ULONG_T value);

      //## Attribute: InfoId%41FFCDB00109
      ULONG_T get_InfoId () const;
      void set_InfoId (ULONG_T value);

      //## Attribute: InfoTextId%3ABA1AC40026
      ULONG_T get_InfoTextId () const;
      void set_InfoTextId (ULONG_T value);

      //## Attribute: InfoText%4132D9E40271
      STRING_T get_InfoText () const;
      void set_InfoText (STRING_T value);

      //## Attribute: Param1%4132DFB2008C
      STRING_T get_Param1 () const;
      void set_Param1 (STRING_T value);

      //## Attribute: Param2%4132DFB2008D
      STRING_T get_Param2 () const;
      void set_Param2 (STRING_T value);

      //## Attribute: Param3%4132DFB2008E
      STRING_T get_Param3 () const;
      void set_Param3 (STRING_T value);

      //## Attribute: Param4%4132DFB2009C
      STRING_T get_Param4 () const;
      void set_Param4 (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cInfo%3ABA1A7A023D.public preserve=yes
      //## end cInfo%3ABA1A7A023D.public

  protected:
    // Data Members for Class Attributes

      //## begin cInfo::InfoType%3E5B712C00D9.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _InfoType;
      //## end cInfo::InfoType%3E5B712C00D9.attr

      //## begin cInfo::InfoCustomType%41FFCD830203.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _InfoCustomType;
      //## end cInfo::InfoCustomType%41FFCD830203.attr

      //## begin cInfo::InfoId%41FFCDB00109.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _InfoId;
      //## end cInfo::InfoId%41FFCDB00109.attr

      //## begin cInfo::InfoTextId%3ABA1AC40026.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _InfoTextId;
      //## end cInfo::InfoTextId%3ABA1AC40026.attr

      //## begin cInfo::InfoText%4132D9E40271.attr preserve=no  public: STRING_T {U} 
      STRING_T _InfoText;
      //## end cInfo::InfoText%4132D9E40271.attr

      //## begin cInfo::Param1%4132DFB2008C.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param1;
      //## end cInfo::Param1%4132DFB2008C.attr

      //## begin cInfo::Param2%4132DFB2008D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param2;
      //## end cInfo::Param2%4132DFB2008D.attr

      //## begin cInfo::Param3%4132DFB2008E.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param3;
      //## end cInfo::Param3%4132DFB2008E.attr

      //## begin cInfo::Param4%4132DFB2009C.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param4;
      //## end cInfo::Param4%4132DFB2009C.attr

    // Additional Protected Declarations
      //## begin cInfo%3ABA1A7A023D.protected preserve=yes
      //## end cInfo%3ABA1A7A023D.protected

  private:
    // Additional Private Declarations
      //## begin cInfo%3ABA1A7A023D.private preserve=yes
      //## end cInfo%3ABA1A7A023D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cInfo%3ABA1A7A023D.implementation preserve=yes
      //## end cInfo%3ABA1A7A023D.implementation

};

//## begin cInfo%3ABA1A7A023D.postscript preserve=yes
//## end cInfo%3ABA1A7A023D.postscript

// Class cInfo 

//## begin module%3ABA1A7A023D.epilog preserve=yes
//## end module%3ABA1A7A023D.epilog


#endif
