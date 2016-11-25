//## begin module%400525C90290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%400525C90290.cm

//## begin module%400525C90290.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%400525C90290.cp

//## Module: cNode%400525C90290; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cNode.h

#ifndef cNode_h
#define cNode_h 1

//## begin module%400525C90290.includes preserve=yes
//## end module%400525C90290.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cEventAdapter;
class __DLL_EXPORT__ cDataChangeAdapter;

//## begin module%400525C90290.additionalDeclarations preserve=yes
//## end module%400525C90290.additionalDeclarations


//## begin cNode%400525C90290.preface preserve=yes
//## end cNode%400525C90290.preface

//## Class: cNode%400525C90290
//## Category: GUIFramework%4005256D03D8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNode 
{
  //## begin cNode%400525C90290.initialDeclarations preserve=yes
public:
  //## end cNode%400525C90290.initialDeclarations

    //## Constructors (generated)
      cNode();

      cNode(const cNode &right);

    //## Constructors (specified)
      //## Operation: cNode%1074080284
      cNode (cContext *context, cDataChangeAdapter *data_change_adapter, cEventAdapter *event_adapter);

    //## Destructor (generated)
      virtual ~cNode();


    //## Other Operations (specified)
      //## Operation: Context%1074084964
      cContext * Context ();

      //## Operation: DataChangeAdapter%1074084965
      cDataChangeAdapter * DataChangeAdapter ();

      //## Operation: EventAdapter%1074084966
      cEventAdapter * EventAdapter ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%40052CE10196
      STRING_T get_Name () const;
      void set_Name (STRING_T value);

      //## Attribute: IsRemote%42DCFE9C02AF
      BOOL_T get_IsRemote () const;

  public:
    // Additional Public Declarations
      //## begin cNode%400525C90290.public preserve=yes
      //## end cNode%400525C90290.public

  protected:
    // Data Members for Class Attributes

      //## begin cNode::Name%40052CE10196.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cNode::Name%40052CE10196.attr

      //## begin cNode::IsRemote%42DCFE9C02AF.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsRemote;
      //## end cNode::IsRemote%42DCFE9C02AF.attr

    // Data Members for Associations

      //## Association: GUIFramework::Interface::<unnamed>%400529090167
      //## Role: cNode::Context%4005290A0157
      //## begin cNode::Context%4005290A0157.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cNode::Context%4005290A0157.role

      //## Association: GUIFramework::Interface::<unnamed>%40052932036B
      //## Role: cNode::DataChangeAdapter%4005293400BB
      //## begin cNode::DataChangeAdapter%4005293400BB.role preserve=no  public: cDataChangeAdapter { -> 1RFHN}
      cDataChangeAdapter *_DataChangeAdapter;
      //## end cNode::DataChangeAdapter%4005293400BB.role

      //## Association: GUIFramework::Interface::<unnamed>%400529580290
      //## Role: cNode::EventAdapter%40052959038A
      //## begin cNode::EventAdapter%40052959038A.role preserve=no  public: cEventAdapter { -> 1RFHN}
      cEventAdapter *_EventAdapter;
      //## end cNode::EventAdapter%40052959038A.role

    // Additional Protected Declarations
      //## begin cNode%400525C90290.protected preserve=yes
      //## end cNode%400525C90290.protected

  private:
    // Additional Private Declarations
      //## begin cNode%400525C90290.private preserve=yes
      //## end cNode%400525C90290.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNode%400525C90290.implementation preserve=yes
      //## end cNode%400525C90290.implementation

};

//## begin cNode%400525C90290.postscript preserve=yes
//## end cNode%400525C90290.postscript

// Class cNode 

//## begin module%400525C90290.epilog preserve=yes
//## end module%400525C90290.epilog


#endif
