//## begin module%3BA21C2A0140.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA21C2A0140.cm

//## begin module%3BA21C2A0140.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BA21C2A0140.cp

//## Module: cTimeObject%3BA21C2A0140; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cTimeObject.h

#ifndef cTimeObject_h
#define cTimeObject_h 1

//## begin module%3BA21C2A0140.includes preserve=yes
//## end module%3BA21C2A0140.includes

//## begin module%3BA21C2A0140.additionalDeclarations preserve=yes
//## end module%3BA21C2A0140.additionalDeclarations


//## begin cTimeObject%3BA21C2A0140.preface preserve=yes
//## end cTimeObject%3BA21C2A0140.preface

//## Class: cTimeObject%3BA21C2A0140
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cTimeObject 
{
  //## begin cTimeObject%3BA21C2A0140.initialDeclarations preserve=yes
public:

   typedef enum {MSECOND=1,SECOND=2,MINUTE=3,HOUR=4,DAY=5,YDAY=6,MONTH=7,YEAR=8, WDAY=9} Dimensions;

  //## end cTimeObject%3BA21C2A0140.initialDeclarations

    //## Constructors (generated)
      cTimeObject();

      cTimeObject(const cTimeObject &right);

    //## Constructors (specified)
      //## Operation: cTimeObject%1000474830
      cTimeObject (time_t time);

      //## Operation: cTimeObject%1000474831
      cTimeObject (ULONG_T time);

      //## Operation: cTimeObject%1134980236
      cTimeObject (int time);

    //## Destructor (generated)
      virtual ~cTimeObject();


    //## Other Operations (specified)
      //## Operation: Now%1000474832
      void Now ();

      //## Operation: Elapsed%1000474833
      cTimeObject Elapsed ();

      //## Operation: Get%1000474834
      INT_T Get (Dimensions dimension) const;

      //## Operation: Set%1000474835
      void Set (Dimensions dimension, INT_T value);

      //## Operation: Set%1053529581
      void Set (CONST_STRING_T value);

      //## Operation: Set%1134552276
      void Set (INT_T sec, INT_T min, INT_T hour, INT_T day, INT_T month, INT_T year);

      //## Operation: SetSystime%1092322933
      void SetSystime ();

      //## Operation: operator time_t%1000474837
      operator time_t () const;

      //## Operation: operator ULONG_T%1000474838
      operator ULONG_T () const;

      //## Operation: operator CONST_STRING_T%1000474839
      operator CONST_STRING_T ();

      //## Operation: operator -%1006258483
      cTimeObject operator - (const cTimeObject &right);

      //## Operation: operator +%1006258484
      cTimeObject operator + (const cTimeObject &right);

      //## Operation: Duration%1053332827
      STRING_T Duration ();

  public:
    // Additional Public Declarations
      //## begin cTimeObject%3BA21C2A0140.public preserve=yes
      //## end cTimeObject%3BA21C2A0140.public

  protected:
    // Additional Protected Declarations
      //## begin cTimeObject%3BA21C2A0140.protected preserve=yes
      //## end cTimeObject%3BA21C2A0140.protected

  private:
    // Additional Private Declarations
      //## begin cTimeObject%3BA21C2A0140.private preserve=yes
      //## end cTimeObject%3BA21C2A0140.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Time%3BA21C2A0153
      //## begin cTimeObject::Time%3BA21C2A0153.attr preserve=no  implementation: time_t {U} 0
      time_t _Time;
      //## end cTimeObject::Time%3BA21C2A0153.attr

      //## Attribute: Text%3BA21C2A0154
      //## begin cTimeObject::Text%3BA21C2A0154.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Text;
      //## end cTimeObject::Text%3BA21C2A0154.attr

    // Additional Implementation Declarations
      //## begin cTimeObject%3BA21C2A0140.implementation preserve=yes
      //## end cTimeObject%3BA21C2A0140.implementation

};

//## begin cTimeObject%3BA21C2A0140.postscript preserve=yes
//## end cTimeObject%3BA21C2A0140.postscript

// Class cTimeObject 

//## begin module%3BA21C2A0140.epilog preserve=yes
//## end module%3BA21C2A0140.epilog


#endif
