//## begin module%3ABA3DF202B1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABA3DF202B1.cm

//## begin module%3ABA3DF202B1.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3ABA3DF202B1.cp

//## Module: cTimer%3ABA3DF202B1; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cTimer.h

#ifndef cTimer_h
#define cTimer_h 1

//## begin module%3ABA3DF202B1.includes preserve=yes
//## end module%3ABA3DF202B1.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class cConfigurationObject;
class cProgram;

//## begin module%3ABA3DF202B1.additionalDeclarations preserve=yes
   typedef map<STRING_T, long> TIMER_MAP_T;
//## end module%3ABA3DF202B1.additionalDeclarations


//## begin cTimer%3ABA3DF202B1.preface preserve=yes
//## end cTimer%3ABA3DF202B1.preface

//## Class: cTimer%3ABA3DF202B1
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3ABCCC47013E;cConfigurationObject { -> F}

class cTimer : public cControlThread  //## Inherits: <unnamed>%3ABA3E390349
{
  //## begin cTimer%3ABA3DF202B1.initialDeclarations preserve=yes
  //## end cTimer%3ABA3DF202B1.initialDeclarations

  public:
    //## Constructors (generated)
      cTimer();

      cTimer(const cTimer &right);

    //## Constructors (specified)
      //## Operation: cTimer%985267674
      cTimer (cProgram *program, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cTimer();


    //## Other Operations (specified)
      //## Operation: ControlFunc%985267675
      virtual INT_T ControlFunc ();

      //## Operation: CreateTimer%985677026
      BOOL_T CreateTimer (CONST_STRING_T name);

      //## Operation: SetTimer%985677027
      void SetTimer (CONST_STRING_T name, LONG_T value);

      //## Operation: TimerExpired%985677028
      BOOL_T TimerExpired (CONST_STRING_T name);

    //## Get and Set Operations for Associations (generated)

      //## Association: Control::Cell::<unnamed>%3ABA3E6F0275
      //## Role: cTimer::Program%3ABA3E7001E0
      const cProgram * get_Program () const;
      void set_Program (cProgram * value);

    // Additional Public Declarations
      //## begin cTimer%3ABA3DF202B1.public preserve=yes
      //## end cTimer%3ABA3DF202B1.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%3ABA3E6F0275
      //## begin cTimer::Program%3ABA3E7001E0.role preserve=no  public: cProgram {1 -> 1RFHN}
      cProgram *_Program;
      //## end cTimer::Program%3ABA3E7001E0.role

    // Additional Protected Declarations
      //## begin cTimer%3ABA3DF202B1.protected preserve=yes
      //## end cTimer%3ABA3DF202B1.protected

  private:
    // Additional Private Declarations
      //## begin cTimer%3ABA3DF202B1.private preserve=yes
      //## end cTimer%3ABA3DF202B1.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CheckTimers%985677032
      void CheckTimers ();

    // Data Members for Class Attributes

      //## Attribute: TimerMap%3AC062810135
      //## begin cTimer::TimerMap%3AC062810135.attr preserve=no  private: TIMER_MAP_T {U} 
      TIMER_MAP_T _TimerMap;
      //## end cTimer::TimerMap%3AC062810135.attr

    // Additional Implementation Declarations
      //## begin cTimer%3ABA3DF202B1.implementation preserve=yes
      //## end cTimer%3ABA3DF202B1.implementation

    friend class cProgram;
};

//## begin cTimer%3ABA3DF202B1.postscript preserve=yes
//## end cTimer%3ABA3DF202B1.postscript

// Class cTimer 

//## Get and Set Operations for Associations (inline)

inline const cProgram * cTimer::get_Program () const
{
  //## begin cTimer::get_Program%3ABA3E7001E0.get preserve=no
  return _Program;
  //## end cTimer::get_Program%3ABA3E7001E0.get
}

inline void cTimer::set_Program (cProgram * value)
{
  //## begin cTimer::set_Program%3ABA3E7001E0.set preserve=no
  _Program = value;
  //## end cTimer::set_Program%3ABA3E7001E0.set
}

//## begin module%3ABA3DF202B1.epilog preserve=yes
//## end module%3ABA3DF202B1.epilog


#endif
