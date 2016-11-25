//## begin module%3EBF96A80213.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EBF96A80213.cm

//## begin module%3EBF96A80213.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EBF96A80213.cp

//## Module: cEventAdapter%3EBF96A80213; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cEventAdapter.h

#ifndef cEventAdapter_h
#define cEventAdapter_h 1

//## begin module%3EBF96A80213.includes preserve=yes
//## end module%3EBF96A80213.includes

// cAdapter
#include "System/Channel/cAdapter.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cPtrList;
class __DLL_EXPORT__ cEventControl;

//## begin module%3EBF96A80213.additionalDeclarations preserve=yes
//## end module%3EBF96A80213.additionalDeclarations


//## begin cEventAdapter%3EBF96A80213.preface preserve=yes
//## end cEventAdapter%3EBF96A80213.preface

//## Class: cEventAdapter%3EBF96A80213
//## Category: Client::Adapters%3DCC05190174
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EBFAEDD03A9;cPtrList { -> F}
//## Uses: <unnamed>%3EBFAFF40119;cEventControl { -> F}
//## Uses: <unnamed>%3EBFB41101E4;cTransientObject { -> F}
//## Uses: <unnamed>%40E17A2303B9;cObjectLock { -> F}

class __DLL_EXPORT__ cEventAdapter : public cAdapter  //## Inherits: <unnamed>%3F86C5860000
{
  //## begin cEventAdapter%3EBF96A80213.initialDeclarations preserve=yes
public:
  //## end cEventAdapter%3EBF96A80213.initialDeclarations

    //## Constructors (generated)
      cEventAdapter();

      cEventAdapter(const cEventAdapter &right);

    //## Constructors (specified)
      //## Operation: cEventAdapter%1054828773
      cEventAdapter (CONST_STRING_T cell_name);

    //## Destructor (generated)
      virtual ~cEventAdapter();


    //## Other Operations (specified)
      //## Operation: Object%1052744771
      virtual void Object (cTransientObject *object);

      //## Operation: RegisterControl%1052744772
      virtual void RegisterControl (cEventControl *event_control);

      //## Operation: UnRegisterControl%1052744773
      virtual void UnRegisterControl (cEventControl *event_control);

      //## Operation: Lock%1088517102
      void Lock ();

      //## Operation: Unlock%1088517103
      void Unlock ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CellName%3EBF975E02EE
      STRING_T get_CellName () const;

  public:
    // Additional Public Declarations
      //## begin cEventAdapter%3EBF96A80213.public preserve=yes
      //## end cEventAdapter%3EBF96A80213.public

  protected:
    // Data Members for Class Attributes

      //## begin cEventAdapter::CellName%3EBF975E02EE.attr preserve=no  public: STRING_T {U} 
      STRING_T _CellName;
      //## end cEventAdapter::CellName%3EBF975E02EE.attr

    // Additional Protected Declarations
      //## begin cEventAdapter%3EBF96A80213.protected preserve=yes
      //## end cEventAdapter%3EBF96A80213.protected

  private:
    // Additional Private Declarations
      //## begin cEventAdapter%3EBF96A80213.private preserve=yes
      //## end cEventAdapter%3EBF96A80213.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Controls%3EBFAEA70168
      //## begin cEventAdapter::Controls%3EBFAEA70168.attr preserve=no  protected: cPtrList * {U} NULL
      cPtrList *_Controls;
      //## end cEventAdapter::Controls%3EBFAEA70168.attr

    // Additional Implementation Declarations
      //## begin cEventAdapter%3EBF96A80213.implementation preserve=yes
      //## end cEventAdapter%3EBF96A80213.implementation

};

//## begin cEventAdapter%3EBF96A80213.postscript preserve=yes
//## end cEventAdapter%3EBF96A80213.postscript

// Class cEventAdapter 

//## begin module%3EBF96A80213.epilog preserve=yes
//## end module%3EBF96A80213.epilog


#endif
