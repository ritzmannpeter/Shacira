//## begin module%3BB1D0ED0224.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D0ED0224.cm

//## begin module%3BB1D0ED0224.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D0ED0224.cp

//## Module: cNameSpace%3BB1D0ED0224; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpace.h

#ifndef cNameSpace_h
#define cNameSpace_h 1

//## begin module%3BB1D0ED0224.includes preserve=yes
//## end module%3BB1D0ED0224.includes

// cNameSpaceIterator
#include "System/Namespace/cNameSpaceIterator.h"

class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cNameSpaceNode;

//## begin module%3BB1D0ED0224.additionalDeclarations preserve=yes
//## end module%3BB1D0ED0224.additionalDeclarations


//## begin cNameSpace%3BB1D0ED0224.preface preserve=yes
//## end cNameSpace%3BB1D0ED0224.preface

//## Class: cNameSpace%3BB1D0ED0224
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BB1DBB70031;cNameSpaceIterator { -> }
//## Uses: <unnamed>%3BB1EB8401B4;cStringUtils { -> F}

class __DLL_EXPORT__ cNameSpace 
{
  //## begin cNameSpace%3BB1D0ED0224.initialDeclarations preserve=yes
public:
  //## end cNameSpace%3BB1D0ED0224.initialDeclarations

    //## Constructors (generated)
      cNameSpace();

      cNameSpace(const cNameSpace &right);

    //## Destructor (generated)
      virtual ~cNameSpace();


    //## Other Operations (specified)
      //## Operation: Add%1001511103
      BOOL_T Add (CONST_STRING_T path);

      //## Operation: Exists%1125306234
      BOOL_T Exists (CONST_STRING_T path);

      //## Operation: Remove%1125306227
      BOOL_T Remove (CONST_STRING_T path);

      //## Operation: Iterator%1001511104
      cNameSpaceIterator Iterator (CONST_STRING_T name = NULL);

      //## Operation: Root%1001511110
      cNameSpaceNode * Root ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Delimiter%3BB1D8840015
      STRING_T get_Delimiter () const;
      void set_Delimiter (STRING_T value);

      //## Attribute: OutDelimiter%3BB3206A0054
      STRING_T get_OutDelimiter () const;
      void set_OutDelimiter (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cNameSpace%3BB1D0ED0224.public preserve=yes
      //## end cNameSpace%3BB1D0ED0224.public

  protected:
    // Data Members for Class Attributes

      //## begin cNameSpace::Delimiter%3BB1D8840015.attr preserve=no  public: STRING_T {U} "/"
      STRING_T _Delimiter;
      //## end cNameSpace::Delimiter%3BB1D8840015.attr

      //## begin cNameSpace::OutDelimiter%3BB3206A0054.attr preserve=no  public: STRING_T {U} "."
      STRING_T _OutDelimiter;
      //## end cNameSpace::OutDelimiter%3BB3206A0054.attr

    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E5B5DA3010A
      //## Role: cNameSpace::Root%3E5B5DA4001B
      //## begin cNameSpace::Root%3E5B5DA4001B.role preserve=no  public: cNameSpaceNode { -> 1RFHN}
      cNameSpaceNode *_Root;
      //## end cNameSpace::Root%3E5B5DA4001B.role

    // Additional Protected Declarations
      //## begin cNameSpace%3BB1D0ED0224.protected preserve=yes
      //## end cNameSpace%3BB1D0ED0224.protected

  private:
    // Additional Private Declarations
      //## begin cNameSpace%3BB1D0ED0224.private preserve=yes
      //## end cNameSpace%3BB1D0ED0224.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AddNode%1001511112
      BOOL_T AddNode (CONST_STRING_T path, cNameSpaceNode *node);

      //## Operation: Exists%1125306235
      BOOL_T Exists (CONST_STRING_T path, cNameSpaceNode *node);

      //## Operation: RemoveNode%1125306228
      BOOL_T RemoveNode (CONST_STRING_T path, cNameSpaceNode *node);

      //## Operation: RemoveRecursive%1125306229
      BOOL_T RemoveRecursive (cNameSpaceNode *node);

      //## Operation: Split%1001511108
      STRING_T Split (CONST_STRING_T path, STRING_T &tail);

      //## Operation: Concat%1001528551
      STRING_T Concat (CONST_STRING_T path, CONST_STRING_T name);

      //## Operation: OutConcat%1001584935
      STRING_T OutConcat (CONST_STRING_T path, CONST_STRING_T name);

    // Additional Implementation Declarations
      //## begin cNameSpace%3BB1D0ED0224.implementation preserve=yes
      //## end cNameSpace%3BB1D0ED0224.implementation

    friend class cNameSpaceIterator;
    friend class __DLL_EXPORT__ cNameSpaceNode;
};

//## begin cNameSpace%3BB1D0ED0224.postscript preserve=yes
//## end cNameSpace%3BB1D0ED0224.postscript

// Class cNameSpace 

//## begin module%3BB1D0ED0224.epilog preserve=yes
//## end module%3BB1D0ED0224.epilog


#endif
