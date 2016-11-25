//## begin module%3BB1D19403AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D19403AB.cm

//## begin module%3BB1D19403AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D19403AB.cp

//## Module: cNameSpaceIterator%3BB1D19403AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpaceIterator.h

#ifndef cNameSpaceIterator_h
#define cNameSpaceIterator_h 1

//## begin module%3BB1D19403AB.includes preserve=yes
//## end module%3BB1D19403AB.includes


class __DLL_EXPORT__ cNameSpaceNode;
class __DLL_EXPORT__ cNameSpace;

//## begin module%3BB1D19403AB.additionalDeclarations preserve=yes
//## end module%3BB1D19403AB.additionalDeclarations


//## begin cNameSpaceIterator%3BB1D19403AB.preface preserve=yes
//## end cNameSpaceIterator%3BB1D19403AB.preface

//## Class: cNameSpaceIterator%3BB1D19403AB
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class cNameSpaceIterator 
{
  //## begin cNameSpaceIterator%3BB1D19403AB.initialDeclarations preserve=yes
  //## end cNameSpaceIterator%3BB1D19403AB.initialDeclarations

  public:
    //## Constructors (generated)
      cNameSpaceIterator();

      cNameSpaceIterator(const cNameSpaceIterator &right);

    //## Constructors (specified)
      //## Operation: cNameSpaceIterator%1001511098
      cNameSpaceIterator (cNameSpace *name_space, CONST_STRING_T path = NULL);

    //## Destructor (generated)
      virtual ~cNameSpaceIterator();

    //## Stream Operations (generated)
      friend ostream & operator<<(ostream &stream,const cNameSpaceIterator &right);

      friend istream & operator>>(istream &stream,cNameSpaceIterator &object);


    //## Other Operations (specified)
      //## Operation: Reset%1001511117
      BOOL_T Reset ();

      //## Operation: SetPath%1001511100
      BOOL_T SetPath (CONST_STRING_T path);

      //## Operation: Up%1001511101
      BOOL_T Up ();

      //## Operation: Down%1001511102
      BOOL_T Down (CONST_STRING_T name);

      //## Operation: Name%1001511114
      STRING_T Name ();

      //## Operation: Path%1001528550
      STRING_T Path ();

      //## Operation: Names%1001511115
      INT_T Names (STRING_LIST_T &names);

      //## Operation: Leafs%1001584930
      INT_T Leafs (STRING_LIST_T &names);

      //## Operation: Branches%1001584931
      INT_T Branches (STRING_LIST_T &names);

      //## Operation: FullNames%1001584932
      INT_T FullNames (STRING_LIST_T &names);

      //## Operation: FullName%1001584934
      STRING_T FullName ();

    // Additional Public Declarations
      //## begin cNameSpaceIterator%3BB1D19403AB.public preserve=yes
      //## end cNameSpaceIterator%3BB1D19403AB.public

  protected:
    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E5B5D1501A6
      //## Role: cNameSpaceIterator::Node%3E5B5D16027A
      //## begin cNameSpaceIterator::Node%3E5B5D16027A.role preserve=no  public: cNameSpaceNode { -> 1RFHN}
      cNameSpaceNode *_Node;
      //## end cNameSpaceIterator::Node%3E5B5D16027A.role

      //## Association: System::Namespace::<unnamed>%3E5B5C7D0324
      //## Role: cNameSpaceIterator::NameSpace%3E5B5C7E034D
      //## begin cNameSpaceIterator::NameSpace%3E5B5C7E034D.role preserve=no  public: cNameSpace { -> 1RFHN}
      cNameSpace *_NameSpace;
      //## end cNameSpaceIterator::NameSpace%3E5B5C7E034D.role

    // Additional Protected Declarations
      //## begin cNameSpaceIterator%3BB1D19403AB.protected preserve=yes
      //## end cNameSpaceIterator%3BB1D19403AB.protected

  private:
    // Additional Private Declarations
      //## begin cNameSpaceIterator%3BB1D19403AB.private preserve=yes
      //## end cNameSpaceIterator%3BB1D19403AB.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetNode%1001511109
      BOOL_T SetNode (cNameSpaceNode *node);

    // Additional Implementation Declarations
      //## begin cNameSpaceIterator%3BB1D19403AB.implementation preserve=yes
      //## end cNameSpaceIterator%3BB1D19403AB.implementation

};

//## begin cNameSpaceIterator%3BB1D19403AB.postscript preserve=yes
//## end cNameSpaceIterator%3BB1D19403AB.postscript

// Class cNameSpaceIterator 

//## begin module%3BB1D19403AB.epilog preserve=yes
//## end module%3BB1D19403AB.epilog


#endif
