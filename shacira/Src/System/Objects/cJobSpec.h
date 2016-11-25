//## begin module%3DDBC48B032A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC48B032A.cm

//## begin module%3DDBC48B032A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC48B032A.cp

//## Module: cJobSpec%3DDBC48B032A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cJobSpec.h

#ifndef cJobSpec_h
#define cJobSpec_h 1

//## begin module%3DDBC48B032A.includes preserve=yes
//## end module%3DDBC48B032A.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%3DDBC48B032A.additionalDeclarations preserve=yes
//## end module%3DDBC48B032A.additionalDeclarations


//## begin cJobSpec%3DDBC48B032A.preface preserve=yes
//## end cJobSpec%3DDBC48B032A.preface

//## Class: cJobSpec%3DDBC48B032A
//	A job spec object comes as a set of property names. This
//	property sets can be used to configure operations that
//	involve the collection of sets of data items. Every
//	property name can be marked with up to 32 flags to add
//	additional information to a property name.
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A57FB015F;cTransferObject { -> F}

class __DLL_EXPORT__ cJobSpec : public cTransientObject  //## Inherits: <unnamed>%3DDBC4A700D1
{
  //## begin cJobSpec%3DDBC48B032A.initialDeclarations preserve=yes
public:
  //## end cJobSpec%3DDBC48B032A.initialDeclarations

    //## Constructors (generated)
      cJobSpec();

      cJobSpec(const cJobSpec &right);

    //## Constructors (specified)
      //## Operation: cJobSpec%1047655597
      cJobSpec (cStaticObject *source, CONST_STRING_T job_name, UCHAR_T refresh_type, ULONG_T refresh_value);

    //## Destructor (generated)
      virtual ~cJobSpec();


    //## Other Operations (specified)
      //## Operation: Properties%1047655598
      //	Returns the current property count of a job spec.
      ULONG_T Properties ();

      //## Operation: Property%1047655599
      //	Retrieves the property specification at position index.
      STRING_T Property (ULONG_T index);

      //## Operation: AddProperty%1047655600
      //	Adds a new property name to the job spec object.
      void AddProperty (CONST_STRING_T property_name);

      void RemoveProperty(CONST_STRING_T property_name);

      //## Operation: SetNameList%1138452345
      void SetNameList (STRING_LIST_T name_list);

      //## Operation: SetNameList%1138452346
      void SetNameList (CONST_STRING_T *name_list);

      //## Operation: Exists%1048090498
      //	This method returns true if it contains a property name
      //	of property_name, false otherwise.
      virtual BOOL_T Exists (CONST_STRING_T property_name);

      //## Operation: Serialize%1046160460
      virtual STRING_T Serialize ();

      //## Operation: Construct%1046160461
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

      //## Operation: SetFlags%1100678884
      //	Sets all flags of aproperty name to the specified value.
      BOOL_T SetFlags (CONST_STRING_T property_name, ULONG_T flags);

      //## Operation: SetFlag%1100678885
      //	Sets the flag of a property name to the specified value.
      //	The flag is denoted by flag_pos.
      BOOL_T SetFlag (CONST_STRING_T property_name, UCHAR_T flag_pos, BOOL_T state);

      //## Operation: GetFlags%1100678886
      //	Returns all flags of aproperty name as an unsigned long
      //	value.
      ULONG_T GetFlags (CONST_STRING_T property_name);

      //## Operation: GetFlag%1100678887
      //	Returns the state of the flag denoted by flag_pos.
      BOOL_T GetFlag (CONST_STRING_T property_name, UCHAR_T flag_pos);

      //## Operation: Matches%1106841437
      //	Returns true if two job specs match, false otherwise.
      //	Two job specs are considered matching when they contain
      //	the same property names in the same order.
      virtual BOOL_T Matches (cJobSpec *job_spec);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: JobName%3DDCDB400236
      STRING_T get_JobName () const;
      void set_JobName (STRING_T value);

      //## Attribute: RefreshType%3E71F31500BB
      ULONG_T get_RefreshType () const;
      void set_RefreshType (ULONG_T value);

      //## Attribute: RefreshValue%3E71F3440290
      ULONG_T get_RefreshValue () const;
      void set_RefreshValue (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cJobSpec%3DDBC48B032A.public preserve=yes
      //## end cJobSpec%3DDBC48B032A.public

  protected:
    // Data Members for Class Attributes

      //## begin cJobSpec::JobName%3DDCDB400236.attr preserve=no  public: STRING_T {U} 
      STRING_T _JobName;
      //## end cJobSpec::JobName%3DDCDB400236.attr

      //## begin cJobSpec::RefreshType%3E71F31500BB.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _RefreshType;
      //## end cJobSpec::RefreshType%3E71F31500BB.attr

      //## begin cJobSpec::RefreshValue%3E71F3440290.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RefreshValue;
      //## end cJobSpec::RefreshValue%3E71F3440290.attr

    // Additional Protected Declarations
      //## begin cJobSpec%3DDBC48B032A.protected preserve=yes
      //## end cJobSpec%3DDBC48B032A.protected

  private:
    // Additional Private Declarations
      //## begin cJobSpec%3DDBC48B032A.private preserve=yes
      //## end cJobSpec%3DDBC48B032A.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Resize%1047655601
      void Resize (ULONG_T index);

    // Data Members for Class Attributes

      //## Attribute: Properties%3E71F3610399
      //## begin cJobSpec::Properties%3E71F3610399.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Properties;
      //## end cJobSpec::Properties%3E71F3610399.attr

      //## Attribute: FlagMap%419B1DDC00DA
      //## begin cJobSpec::FlagMap%419B1DDC00DA.attr preserve=no  implementation: ULONG_MAP_T {U} 
      ULONG_MAP_T _FlagMap;
      //## end cJobSpec::FlagMap%419B1DDC00DA.attr

    // Additional Implementation Declarations
      //## begin cJobSpec%3DDBC48B032A.implementation preserve=yes
      //## end cJobSpec%3DDBC48B032A.implementation

};

//## begin cJobSpec%3DDBC48B032A.postscript preserve=yes
//## end cJobSpec%3DDBC48B032A.postscript

// Class cJobSpec 

//## begin module%3DDBC48B032A.epilog preserve=yes
//## end module%3DDBC48B032A.epilog


#endif
