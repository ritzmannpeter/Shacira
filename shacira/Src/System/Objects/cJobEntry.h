//## begin module%3DDBC4B0023D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC4B0023D.cm

//## begin module%3DDBC4B0023D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC4B0023D.cp

//## Module: cJobEntry%3DDBC4B0023D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cJobEntry.h

#ifndef cJobEntry_h
#define cJobEntry_h 1

//## begin module%3DDBC4B0023D.includes preserve=yes
//## end module%3DDBC4B0023D.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;
class __DLL_EXPORT__ cJobSpec;

//## begin module%3DDBC4B0023D.additionalDeclarations preserve=yes

#define TEXT_BUF_LENGTH 0x200
#define MAX_FLAG_COUNT  40

#include "Pack_1"

typedef struct {
   TRANSIENT_OBJECT_T transient_object;
   char job_name[TEXT_LENGTH+1];
   ULONG_T refresh_type;
   ULONG_T refresh_value;
   LONG_T shot;
   LONG_T quality;
   char ident[TEXT_LENGTH+1];
   char properties[TEXT_BUF_LENGTH+1];
   char property_values[TEXT_BUF_LENGTH+1];
   ULONG_T flags[MAX_FLAG_COUNT];
}  JOB_ENTRY_OBJECT_T;

#include "UnPack"

//## end module%3DDBC4B0023D.additionalDeclarations


//## begin cJobEntry%3DDBC4B0023D.preface preserve=yes
//## end cJobEntry%3DDBC4B0023D.preface

//## Class: cJobEntry%3DDBC4B0023D
//	A job entry object comes as a set of properties. A
//	property consists of a property name and a property
//	value. A job entry object therefore is an extension of
//	the job spec object.
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A5806006A;cTransferObject { -> F}
//## Uses: <unnamed>%41F9114300DA;cJobSpec { -> F}

class __DLL_EXPORT__ cJobEntry : public cTransientObject  //## Inherits: <unnamed>%3DDBC4C700A5
{
  //## begin cJobEntry%3DDBC4B0023D.initialDeclarations preserve=yes
public:
  //## end cJobEntry%3DDBC4B0023D.initialDeclarations

    //## Constructors (generated)
      cJobEntry();

      cJobEntry(const cJobEntry &right);

    //## Constructors (specified)
      //## Operation: cJobEntry%1047655602
      cJobEntry (cStaticObject *source, CONST_STRING_T job_name);

      //## Operation: cJobEntry%1138452012
      cJobEntry (cStaticObject *source, cJobSpec *job_spec);

    //## Destructor (generated)
      virtual ~cJobEntry();


    //## Other Operations (specified)
      //## Operation: Properties%1047655603
      ULONG_T Properties ();

      //## Operation: PropertyExists%1047655618
      BOOL_T PropertyExists (CONST_STRING_T property_name);

      //## Operation: Property%1047655613
      STRING_T Property (ULONG_T index);

      //## Operation: PropertyValue%1047655614
      STRING_T PropertyValue (ULONG_T index);

      //## Operation: PropertyValue%1047655615
      STRING_T PropertyValue (CONST_STRING_T property_name);

      //## Operation: AddProperty%1047655616
      void AddProperty (CONST_STRING_T property_name);

      //## Operation: AddPropertyValue%1047655617
      void AddPropertyValue (CONST_STRING_T property_name, CONST_STRING_T value);

      //## Operation: AddPropertyValue%1047655619
      void AddPropertyValue (ULONG_T index, CONST_STRING_T property_name, CONST_STRING_T value);

      //## Operation: Serialize%1046160458
      virtual STRING_T Serialize ();

      //## Operation: Construct%1046160459
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

      //## Operation: SetPropertyValue%1097751638
      void SetPropertyValue (ULONG_T index, CONST_STRING_T value);

      //## Operation: SetFlags%1100678880
      BOOL_T SetFlags (CONST_STRING_T property, ULONG_T flags);

      //## Operation: SetFlag%1100678881
      BOOL_T SetFlag (CONST_STRING_T property, UCHAR_T flag_pos, BOOL_T state);

      //## Operation: GetFlags%1100678882
      ULONG_T GetFlags (CONST_STRING_T property);

      //## Operation: GetFlag%1100678883
      BOOL_T GetFlag (CONST_STRING_T property, UCHAR_T flag_pos);

      //## Operation: Matches%1106841435
      virtual BOOL_T Matches (cJobEntry *job_entry);

      //## Operation: Matches%1106841436
      virtual BOOL_T Matches (cJobSpec *job_spec);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: JobName%3DDCDB590296
      STRING_T get_JobName () const;
      void set_JobName (STRING_T value);

      //## Attribute: RefreshType%41374A7301D4
      ULONG_T get_RefreshType () const;
      void set_RefreshType (ULONG_T value);

      //## Attribute: RefreshValue%41374A7301D5
      ULONG_T get_RefreshValue () const;
      void set_RefreshValue (ULONG_T value);

      //## Attribute: Shot%3E5B7F880157
      LONG_T get_Shot () const;
      void set_Shot (LONG_T value);

      //## Attribute: Quality%3E5B7FB30376
      INT_T get_Quality () const;
      void set_Quality (INT_T value);

      //## Attribute: Ident%3E5B7FC60264
      STRING_T get_Ident () const;
      void set_Ident (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cJobEntry%3DDBC4B0023D.public preserve=yes
      //## end cJobEntry%3DDBC4B0023D.public

  protected:
    // Data Members for Class Attributes

      //## begin cJobEntry::JobName%3DDCDB590296.attr preserve=no  public: STRING_T {U} 
      STRING_T _JobName;
      //## end cJobEntry::JobName%3DDCDB590296.attr

      //## begin cJobEntry::RefreshType%41374A7301D4.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _RefreshType;
      //## end cJobEntry::RefreshType%41374A7301D4.attr

      //## begin cJobEntry::RefreshValue%41374A7301D5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RefreshValue;
      //## end cJobEntry::RefreshValue%41374A7301D5.attr

      //## begin cJobEntry::Shot%3E5B7F880157.attr preserve=no  public: LONG_T {U} 0
      LONG_T _Shot;
      //## end cJobEntry::Shot%3E5B7F880157.attr

      //## begin cJobEntry::Quality%3E5B7FB30376.attr preserve=no  public: INT_T {U} NO_QUALITY
      INT_T _Quality;
      //## end cJobEntry::Quality%3E5B7FB30376.attr

      //## begin cJobEntry::Ident%3E5B7FC60264.attr preserve=no  public: STRING_T {U} 
      STRING_T _Ident;
      //## end cJobEntry::Ident%3E5B7FC60264.attr

    // Additional Protected Declarations
      //## begin cJobEntry%3DDBC4B0023D.protected preserve=yes
      //## end cJobEntry%3DDBC4B0023D.protected

  private:
    // Additional Private Declarations
      //## begin cJobEntry%3DDBC4B0023D.private preserve=yes
      //## end cJobEntry%3DDBC4B0023D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Resize%1047655606
      void Resize (ULONG_T index);

      //## Operation: SetProperties%1094142498
      void SetProperties (CHAR_T *prop_dst, CHAR_T *val_dst);

      //## Operation: GetProperties%1094142499
      void GetProperties (CONST_STRING_T prop_src, CONST_STRING_T val_src);

      //## Operation: SetFlagValues%1101801393
      void SetFlagValues (ULONG_T *flag_buf);

      //## Operation: GetFlagValues%1101801394
      void GetFlagValues (ULONG_T *flag_buf);

    // Data Members for Class Attributes

      //## Attribute: Properties%3E72057402DE
      //## begin cJobEntry::Properties%3E72057402DE.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Properties;
      //## end cJobEntry::Properties%3E72057402DE.attr

      //## Attribute: PropertyValues%3E72057402DF
      //## begin cJobEntry::PropertyValues%3E72057402DF.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _PropertyValues;
      //## end cJobEntry::PropertyValues%3E72057402DF.attr

      //## Attribute: PropertyMap%3E72057402EE
      //## begin cJobEntry::PropertyMap%3E72057402EE.attr preserve=no  implementation: ULONG_MAP_T {U} 
      ULONG_MAP_T _PropertyMap;
      //## end cJobEntry::PropertyMap%3E72057402EE.attr

      //## Attribute: FlagMap%419B1CA3009C
      //## begin cJobEntry::FlagMap%419B1CA3009C.attr preserve=no  implementation: ULONG_MAP_T {U} 
      ULONG_MAP_T _FlagMap;
      //## end cJobEntry::FlagMap%419B1CA3009C.attr

    // Additional Implementation Declarations
      //## begin cJobEntry%3DDBC4B0023D.implementation preserve=yes
      //## end cJobEntry%3DDBC4B0023D.implementation

};

//## begin cJobEntry%3DDBC4B0023D.postscript preserve=yes
//## end cJobEntry%3DDBC4B0023D.postscript

// Class cJobEntry 

//## begin module%3DDBC4B0023D.epilog preserve=yes
//## end module%3DDBC4B0023D.epilog


#endif
