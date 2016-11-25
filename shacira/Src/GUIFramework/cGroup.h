//## begin module%4005261001B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4005261001B5.cm

//## begin module%4005261001B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4005261001B5.cp

//## Module: cGroup%4005261001B5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cGroup.h

#ifndef cGroup_h
#define cGroup_h 1

//## begin module%4005261001B5.includes preserve=yes
//## end module%4005261001B5.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cDataChangeAdapter;
class __DLL_EXPORT__ cEventAdapter;

//## begin module%4005261001B5.additionalDeclarations preserve=yes
//## end module%4005261001B5.additionalDeclarations


//## begin cGroup%4005261001B5.preface preserve=yes
//## end cGroup%4005261001B5.preface

//## Class: cGroup%4005261001B5
//## Category: GUIFramework%4005256D03D8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cGroup 
{
  //## begin cGroup%4005261001B5.initialDeclarations preserve=yes
  //## end cGroup%4005261001B5.initialDeclarations

    //## Constructors (generated)
      cGroup();

      cGroup(const cGroup &right);

    //## Constructors (specified)
      //## Operation: cGroup%1074080281
      cGroup (cContext *context, cDataChangeAdapter *data_change_adapter, cEventAdapter *event_adapter);

    //## Destructor (generated)
      virtual ~cGroup();

  public:
    // Additional Public Declarations
      //## begin cGroup%4005261001B5.public preserve=yes
      //## end cGroup%4005261001B5.public

  protected:
    // Data Members for Associations

      //## Association: GUIFramework::Interface::<unnamed>%400529A0029F
      //## Role: cGroup::DataChangeAdapter%400529A10186
      //## begin cGroup::DataChangeAdapter%400529A10186.role preserve=no  public: cDataChangeAdapter { -> 1RFHN}
      cDataChangeAdapter *_DataChangeAdapter;
      //## end cGroup::DataChangeAdapter%400529A10186.role

      //## Association: GUIFramework::Interface::<unnamed>%400529CA0203
      //## Role: cGroup::Context%400529CB0280
      //## begin cGroup::Context%400529CB0280.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cGroup::Context%400529CB0280.role

      //## Association: GUIFramework::Interface::<unnamed>%400529EA038A
      //## Role: cGroup::EventAdapter%400529EC02BF
      //## begin cGroup::EventAdapter%400529EC02BF.role preserve=no  public: cEventAdapter { -> 1RFHN}
      cEventAdapter *_EventAdapter;
      //## end cGroup::EventAdapter%400529EC02BF.role

    // Additional Protected Declarations
      //## begin cGroup%4005261001B5.protected preserve=yes
      //## end cGroup%4005261001B5.protected

  private:
    // Additional Private Declarations
      //## begin cGroup%4005261001B5.private preserve=yes
      //## end cGroup%4005261001B5.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cGroup%4005261001B5.implementation preserve=yes
      //## end cGroup%4005261001B5.implementation

};

//## begin cGroup%4005261001B5.postscript preserve=yes
//## end cGroup%4005261001B5.postscript

// Class cGroup 

//## begin module%4005261001B5.epilog preserve=yes
//## end module%4005261001B5.epilog


#endif
