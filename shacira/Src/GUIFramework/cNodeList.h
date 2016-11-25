//## begin module%400525E50157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%400525E50157.cm

//## begin module%400525E50157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%400525E50157.cp

//## Module: cNodeList%400525E50157; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cNodeList.h

#ifndef cNodeList_h
#define cNodeList_h 1

//## begin module%400525E50157.includes preserve=yes
//## end module%400525E50157.includes


class __DLL_EXPORT__ cNode;

//## begin module%400525E50157.additionalDeclarations preserve=yes
//## end module%400525E50157.additionalDeclarations


//## begin cNodeList%400525E50157.preface preserve=yes
//## end cNodeList%400525E50157.preface

//## Class: cNodeList%400525E50157
//## Category: GUIFramework%4005256D03D8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNodeList 
{
  //## begin cNodeList%400525E50157.initialDeclarations preserve=yes
public:
  //## end cNodeList%400525E50157.initialDeclarations

    //## Constructors (generated)
      cNodeList();

      cNodeList(const cNodeList &right);

    //## Destructor (generated)
      virtual ~cNodeList();


    //## Other Operations (specified)
      //## Operation: AddNode%1074080283
      void AddNode (cNode *node);

      //## Operation: NodeNames%1074084959
      ULONG_T NodeNames (STRING_LIST_T &node_names);

      //## Operation: Node%1074084960
      cNode * Node (CONST_STRING_T name);

  public:
    // Additional Public Declarations
      //## begin cNodeList%400525E50157.public preserve=yes
      //## end cNodeList%400525E50157.public

  protected:
    // Data Members for Associations

      //## Association: GUIFramework::Interface::<unnamed>%400527C702DE
      //## Role: cNodeList::Nodes%400527C800FA
      //## Qualifier: name%400527FA004E; STRING_T
      //## begin cNodeList::Nodes%400527C800FA.role preserve=no  public: cNode { -> 0..nRFHN}
      std::map<STRING_T, cNode*> _Nodes;
      //## end cNodeList::Nodes%400527C800FA.role

    // Additional Protected Declarations
      //## begin cNodeList%400525E50157.protected preserve=yes
      //## end cNodeList%400525E50157.protected

  private:
    // Additional Private Declarations
      //## begin cNodeList%400525E50157.private preserve=yes
      //## end cNodeList%400525E50157.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNodeList%400525E50157.implementation preserve=yes
      //## end cNodeList%400525E50157.implementation

};

//## begin cNodeList%400525E50157.postscript preserve=yes
//## end cNodeList%400525E50157.postscript

// Class cNodeList 

//## begin module%400525E50157.epilog preserve=yes
//## end module%400525E50157.epilog


#endif
