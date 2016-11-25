//## begin module%3DDBC52A0206.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC52A0206.cm

//## begin module%3DDBC52A0206.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC52A0206.cp

//## Module: cAlarm%3DDBC52A0206; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cAlarm.h

#ifndef cAlarm_h
#define cAlarm_h 1

//## begin module%3DDBC52A0206.includes preserve=yes
//## end module%3DDBC52A0206.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%3DDBC52A0206.additionalDeclarations preserve=yes

typedef enum SeverityTypes
{
   SevInfo = 0,
   SevWarning = 1,
   SevError = 2,
   SevSeriousError = 3
};

#include "Pack_1"

typedef struct {
   TRANSIENT_OBJECT_T transient_object;
   ULONG_T ident;
   SeverityTypes severity;
   BOOL_T state;
   ULONG_T text_id1;
   char text1[TEXT_LENGTH+1];
   ULONG_T text_id2;
   char text2[TEXT_LENGTH+1];
   ULONG_T text_id3;
   char text3[TEXT_LENGTH+1];
   ULONG_T text_id4;
   char text4[TEXT_LENGTH+1];
   char param1[TEXT_LENGTH+1];
   char param2[TEXT_LENGTH+1];
   char param3[TEXT_LENGTH+1];
   char param4[TEXT_LENGTH+1];
}  ALARM_OBJECT_T;

#include "UnPack"

//## end module%3DDBC52A0206.additionalDeclarations


//## begin cAlarm%3DDBC52A0206.preface preserve=yes
//## end cAlarm%3DDBC52A0206.preface

//## Class: cAlarm%3DDBC52A0206
//	A alarm object transports alarm info through the Shacira
//	channel system. Alarm objects have semantical bindings
//	when passing the Shacira cell.
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A5810019B;cTransferObject { -> F}

class __DLL_EXPORT__ cAlarm : public cTransientObject  //## Inherits: <unnamed>%3DDBC53F021A
{
  //## begin cAlarm%3DDBC52A0206.initialDeclarations preserve=yes
public:
  //## end cAlarm%3DDBC52A0206.initialDeclarations

    //## Constructors (generated)
      cAlarm();

      cAlarm(const cAlarm &right);

    //## Constructors (specified)
      //## Operation: cAlarm%1043349076
      cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state);

      //## Operation: cAlarm%1093283177
      cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state, ULONG_T text_id);

      //## Operation: cAlarm%1093283178
      cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state, CONST_STRING_T text);

    //## Destructor (generated)
      virtual ~cAlarm();


    //## Other Operations (specified)
      //## Operation: Reset%1081345949
      cAlarm * Reset ();

      //## Operation: Serialize%1043349077
      virtual STRING_T Serialize ();

      //## Operation: Construct%1043349078
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Ident%3DDCDB7B01C3
      ULONG_T get_Ident () const;
      void set_Ident (ULONG_T value);

      //## Attribute: Severity%407262F20203
      SeverityTypes get_Severity () const;
      void set_Severity (SeverityTypes value);

      //## Attribute: State%3E3042C303C8
      BOOL_T get_State () const;
      void set_State (BOOL_T value);

      //## Attribute: TextId1%412A2C6701A5
      ULONG_T get_TextId1 () const;
      void set_TextId1 (ULONG_T value);

      //## Attribute: Text1%3DDCDB9800CA
      STRING_T get_Text1 () const;
      void set_Text1 (STRING_T value);

      //## Attribute: TextId2%412A2C810242
      ULONG_T get_TextId2 () const;
      void set_TextId2 (ULONG_T value);

      //## Attribute: Text2%407261CA0186
      STRING_T get_Text2 () const;
      void set_Text2 (STRING_T value);

      //## Attribute: TextId3%412A2C8C03D8
      ULONG_T get_TextId3 () const;
      void set_TextId3 (ULONG_T value);

      //## Attribute: Text3%407406BD01A5
      STRING_T get_Text3 () const;
      void set_Text3 (STRING_T value);

      //## Attribute: TextId4%412A2C950242
      ULONG_T get_TextId4 () const;
      void set_TextId4 (ULONG_T value);

      //## Attribute: Text4%4074071A034B
      STRING_T get_Text4 () const;
      void set_Text4 (STRING_T value);

      //## Attribute: Param1%407261B002CE
      STRING_T get_Param1 () const;
      void set_Param1 (STRING_T value);

      //## Attribute: Param2%407261B002CF
      STRING_T get_Param2 () const;
      void set_Param2 (STRING_T value);

      //## Attribute: Param3%407261B002D0
      STRING_T get_Param3 () const;
      void set_Param3 (STRING_T value);

      //## Attribute: Param4%407261B002D1
      STRING_T get_Param4 () const;
      void set_Param4 (STRING_T value);

      //## Attribute: AcknowledgedTimeStamp%45A38210006D
      cTimeObject get_AcknowledgedTimeStamp () const;
      void set_AcknowledgedTimeStamp (cTimeObject value);

      STRING_T get_HelpId () const;
      void set_HelpId (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cAlarm%3DDBC52A0206.public preserve=yes
      //## end cAlarm%3DDBC52A0206.public

  protected:
    // Data Members for Class Attributes

      //## begin cAlarm::Ident%3DDCDB7B01C3.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Ident;
      //## end cAlarm::Ident%3DDCDB7B01C3.attr

      //## begin cAlarm::Severity%407262F20203.attr preserve=no  public: SeverityTypes {U} SevError
      SeverityTypes _Severity;
      //## end cAlarm::Severity%407262F20203.attr

      //## begin cAlarm::State%3E3042C303C8.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _State;
      //## end cAlarm::State%3E3042C303C8.attr

      //## begin cAlarm::TextId1%412A2C6701A5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TextId1;
      //## end cAlarm::TextId1%412A2C6701A5.attr

      //## begin cAlarm::Text1%3DDCDB9800CA.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text1;
      //## end cAlarm::Text1%3DDCDB9800CA.attr

      //## begin cAlarm::TextId2%412A2C810242.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TextId2;
      //## end cAlarm::TextId2%412A2C810242.attr

      //## begin cAlarm::Text2%407261CA0186.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text2;
      //## end cAlarm::Text2%407261CA0186.attr

      //## begin cAlarm::TextId3%412A2C8C03D8.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TextId3;
      //## end cAlarm::TextId3%412A2C8C03D8.attr

      //## begin cAlarm::Text3%407406BD01A5.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text3;
      //## end cAlarm::Text3%407406BD01A5.attr

      //## begin cAlarm::TextId4%412A2C950242.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TextId4;
      //## end cAlarm::TextId4%412A2C950242.attr

      //## begin cAlarm::Text4%4074071A034B.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text4;
      //## end cAlarm::Text4%4074071A034B.attr

      //## begin cAlarm::Param1%407261B002CE.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param1;
      //## end cAlarm::Param1%407261B002CE.attr

      //## begin cAlarm::Param2%407261B002CF.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param2;
      //## end cAlarm::Param2%407261B002CF.attr

      //## begin cAlarm::Param3%407261B002D0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param3;
      //## end cAlarm::Param3%407261B002D0.attr

      //## begin cAlarm::Param4%407261B002D1.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param4;
      //## end cAlarm::Param4%407261B002D1.attr

      //## begin cAlarm::AcknowledgedTimeStamp%45A38210006D.attr preserve=no  public: cTimeObject {U} 
      cTimeObject _AcknowledgedTimeStamp;
      //## end cAlarm::AcknowledgedTimeStamp%45A38210006D.attr

      STRING_T _HelpId;

    // Additional Protected Declarations
      //## begin cAlarm%3DDBC52A0206.protected preserve=yes
      //## end cAlarm%3DDBC52A0206.protected

  private:
    // Additional Private Declarations
      //## begin cAlarm%3DDBC52A0206.private preserve=yes
      //## end cAlarm%3DDBC52A0206.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAlarm%3DDBC52A0206.implementation preserve=yes
      //## end cAlarm%3DDBC52A0206.implementation

};

//## begin cAlarm%3DDBC52A0206.postscript preserve=yes

typedef std::map<ULONG_T,cAlarm*> ALARM_MAP_T;

//## end cAlarm%3DDBC52A0206.postscript

// Class cAlarm 

//## begin module%3DDBC52A0206.epilog preserve=yes
//## end module%3DDBC52A0206.epilog


#endif
