//## begin module%3BB1D5320154.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D5320154.cm

//## begin module%3BB1D5320154.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D5320154.cp

//## Module: cNameSpaceNode%3BB1D5320154; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpaceNode.h

#ifndef cNameSpaceNode_h
#define cNameSpaceNode_h 1

//## begin module%3BB1D5320154.includes preserve=yes
//## end module%3BB1D5320154.includes


class __DLL_EXPORT__ cNameSpace;

//## begin module%3BB1D5320154.additionalDeclarations preserve=yes
typedef enum {Leaf, Branch} NodeTypes;
//## end module%3BB1D5320154.additionalDeclarations


//## begin cNameSpaceNode%3BB1D5320154.preface preserve=yes
//## end cNameSpaceNode%3BB1D5320154.preface

//## Class: cNameSpaceNode%3BB1D5320154
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNameSpaceNode 
{
  //## begin cNameSpaceNode%3BB1D5320154.initialDeclarations preserve=yes
public:
  //## end cNameSpaceNode%3BB1D5320154.initialDeclarations

    //## Constructors (generated)
      cNameSpaceNode();

      cNameSpaceNode(const cNameSpaceNode &right);

    //## Constructors (specified)
      //## Operation: cNameSpaceNode%1001511095
      cNameSpaceNode (CONST_STRING_T name, cNameSpaceNode *parent, cNameSpace *name_space);

    //## Destructor (generated)
      virtual ~cNameSpaceNode();


    //## Other Operations (specified)
      //## Operation: AddChild%1001511097
      cNameSpaceNode * AddChild (CONST_STRING_T name, cNameSpace *name_space);

      //## Operation: RemoveChild%1125306230
      BOOL_T RemoveChild (CONST_STRING_T name, cNameSpaceNode *node);

      //## Operation: Child%1001511105
      cNameSpaceNode * Child (CONST_STRING_T name);

      //## Operation: Parent%1001511111
      cNameSpaceNode * Parent ();

      //## Operation: Path%1001528552
      STRING_T Path ();

      //## Operation: Children%1001511113
      INT_T Children (STRING_LIST_T &names);

      //## Operation: Leafs%1001584927
      INT_T Leafs (STRING_LIST_T &names);

      //## Operation: Branches%1001584928
      INT_T Branches (STRING_LIST_T &names);

      //## Operation: FullNames%1001584929
      INT_T FullNames (STRING_LIST_T &names);

      //## Operation: FullName%1001584933
      STRING_T FullName ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3BB1D69C006E
      STRING_T get_Name () const;

      //## Attribute: Type%3BB2F9B20245
      NodeTypes get_Type () const;

  public:
    // Additional Public Declarations
      //## begin cNameSpaceNode%3BB1D5320154.public preserve=yes
      //## end cNameSpaceNode%3BB1D5320154.public

  protected:
    // Data Members for Class Attributes

      //## begin cNameSpaceNode::Name%3BB1D69C006E.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cNameSpaceNode::Name%3BB1D69C006E.attr

      //## begin cNameSpaceNode::Type%3BB2F9B20245.attr preserve=no  public: NodeTypes {U} Leaf
      NodeTypes _Type;
      //## end cNameSpaceNode::Type%3BB2F9B20245.attr

    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E5B5B220361
      //## Role: cNameSpaceNode::Parent%3E5B5B2F0021
      //## begin cNameSpaceNode::Parent%3E5B5B2F0021.role preserve=no  public: cNameSpaceNode { -> 0..1RFHN}
      cNameSpaceNode *_Parent;
      //## end cNameSpaceNode::Parent%3E5B5B2F0021.role

      //## Association: System::Namespace::<unnamed>%3E5B5BE501EF
      //## Role: cNameSpaceNode::Children%3E5B5BEE017A
      //## Qualifier: name%3E5B5C1B0138; STRING_T
      //## begin cNameSpaceNode::Children%3E5B5BEE017A.role preserve=no  public: cNameSpaceNode { -> 0..nRFHN}
      std::map<STRING_T, cNameSpaceNode*> _Children;
      //## end cNameSpaceNode::Children%3E5B5BEE017A.role

      //## Association: System::Namespace::<unnamed>%3E5B5B790276
      //## Role: cNameSpaceNode::NameSpace%3E5B5B7A010F
      //## begin cNameSpaceNode::NameSpace%3E5B5B7A010F.role preserve=no  public: cNameSpace { -> 1RFHN}
      cNameSpace *_NameSpace;
      //## end cNameSpaceNode::NameSpace%3E5B5B7A010F.role

    // Additional Protected Declarations
      //## begin cNameSpaceNode%3BB1D5320154.protected preserve=yes
      //## end cNameSpaceNode%3BB1D5320154.protected

  private:
    // Additional Private Declarations
      //## begin cNameSpaceNode%3BB1D5320154.private preserve=yes
      //## end cNameSpaceNode%3BB1D5320154.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNameSpaceNode%3BB1D5320154.implementation preserve=yes
      //## end cNameSpaceNode%3BB1D5320154.implementation

};

//## begin cNameSpaceNode%3BB1D5320154.postscript preserve=yes
//## end cNameSpaceNode%3BB1D5320154.postscript

// Class cNameSpaceNode 

//## begin module%3BB1D5320154.epilog preserve=yes
//## end module%3BB1D5320154.epilog


#endif
