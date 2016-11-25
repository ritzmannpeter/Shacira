//## begin module%3E8469320119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E8469320119.cm

//## begin module%3E8469320119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E8469320119.cp

//## Module: cTree%3E8469320119; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cTree.h

#ifndef cTree_h
#define cTree_h 1

//## begin module%3E8469320119.includes preserve=yes
//## end module%3E8469320119.includes


class __DLL_EXPORT__ cNodeObject;
class __DLL_EXPORT__ cNodeContext;

//## begin module%3E8469320119.additionalDeclarations preserve=yes

class cTree;
typedef std::map<cTree*,cTree*> TREE_MAP_T;

//## end module%3E8469320119.additionalDeclarations


//## begin cTree%3E8469320119.preface preserve=yes
//## end cTree%3E8469320119.preface

//## Class: cTree%3E8469320119
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cTree 
{
  //## begin cTree%3E8469320119.initialDeclarations preserve=yes
public:
  //## end cTree%3E8469320119.initialDeclarations

    //## begin cTree::TreeIterator%3E87FE2A009C.preface preserve=yes
    //## end cTree::TreeIterator%3E87FE2A009C.preface

    //## Class: TreeIterator%3E87FE2A009C
    //## Category: System::Namespace%3DFF203A0098
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    class __DLL_EXPORT__ TreeIterator 
    {
      //## begin cTree::TreeIterator%3E87FE2A009C.initialDeclarations preserve=yes
    public:
      //## end cTree::TreeIterator%3E87FE2A009C.initialDeclarations

        //## Constructors (generated)
          TreeIterator();

          TreeIterator(const TreeIterator &right);

        //## Constructors (specified)
          //## Operation: TreeIterator%1049099897
          TreeIterator (cTree *tree);

        //## Destructor (generated)
          virtual ~TreeIterator();


        //## Other Operations (specified)
          //## Operation: First%1049099898
          cTree * First ();

          //## Operation: Last%1049099899
          cTree * Last ();

          //## Operation: Next%1049099892
          cTree * Next ();

          //## Operation: Previous%1049099893
          cTree * Previous ();

          //## Operation: FirstLeaf%1049099900
          cTree * FirstLeaf ();

          //## Operation: LastLeaf%1049099901
          cTree * LastLeaf ();

          //## Operation: NextLeaf%1049099894
          cTree * NextLeaf ();

          //## Operation: PreviousLeaf%1049099895
          cTree * PreviousLeaf ();

      public:
        // Additional Public Declarations
          //## begin cTree::TreeIterator%3E87FE2A009C.public preserve=yes
          //## end cTree::TreeIterator%3E87FE2A009C.public

      protected:
        // Additional Protected Declarations
          //## begin cTree::TreeIterator%3E87FE2A009C.protected preserve=yes
          //## end cTree::TreeIterator%3E87FE2A009C.protected

      private:
        // Additional Private Declarations
          //## begin cTree::TreeIterator%3E87FE2A009C.private preserve=yes
          //## end cTree::TreeIterator%3E87FE2A009C.private

      private: //## implementation

        //## Other Operations (specified)
          //## Operation: NextNode%1049099906
          cTree * NextNode (cTree *node);

          //## Operation: NextRightNode%1049124942
          cTree * NextRightNode (cTree *node);

          //## Operation: RightNode%1049114547
          cTree * RightNode (cTree *node);

          //## Operation: Touched%1049114546
          BOOL_T Touched (cTree *node);

        // Data Members for Class Attributes

          //## Attribute: Tree%3E88091C03C8
          //## begin cTree::TreeIterator::Tree%3E88091C03C8.attr preserve=no  implementation: cTree * {U} NULL
          cTree *_Tree;
          //## end cTree::TreeIterator::Tree%3E88091C03C8.attr

          //## Attribute: NextNode%3E880BB40186
          //## begin cTree::TreeIterator::NextNode%3E880BB40186.attr preserve=no  implementation: cTree * {U} NULL
          cTree *_NextNode;
          //## end cTree::TreeIterator::NextNode%3E880BB40186.attr

          //## Attribute: TouchedNodes%3E883F2A0251
          //## begin cTree::TreeIterator::TouchedNodes%3E883F2A0251.attr preserve=no  implementation: TREE_MAP_T {U} 
          TREE_MAP_T _TouchedNodes;
          //## end cTree::TreeIterator::TouchedNodes%3E883F2A0251.attr

        // Additional Implementation Declarations
          //## begin cTree::TreeIterator%3E87FE2A009C.implementation preserve=yes
          //## end cTree::TreeIterator%3E87FE2A009C.implementation

    };

    //## begin cTree::TreeIterator%3E87FE2A009C.postscript preserve=yes
    friend class TreeIterator;
    //## end cTree::TreeIterator%3E87FE2A009C.postscript

    //## Constructors (generated)
      cTree();

      cTree(const cTree &right);

    //## Constructors (specified)
      //## Operation: cTree%1048867681
      cTree (CONST_STRING_T name, cTree *parent = NULL);

    //## Destructor (generated)
      virtual ~cTree();


    //## Other Operations (specified)
      //## Operation: Add%1048867682
      void Add (CONST_STRING_T path);

      //## Operation: Node%1048867683
      cTree * Node (CONST_STRING_T path);

      //## Operation: Node%1049099904
      cTree * Node (ULONG_T index);

      //## Operation: Root%1048867672
      cTree * Root ();

      //## Operation: SetObject%1048867679
      void SetObject (cNodeObject *object);

      //## Operation: Object%1048867677
      cNodeObject * Object ();

      //## Operation: SetContext%1048867680
      void SetContext (cNodeContext *context);

      //## Operation: Context%1048867678
      cNodeContext * Context ();

      //## Operation: Initialize%1048867684
      virtual void Initialize ();

      //## Operation: Show%1048867685
      virtual void Show ();

      //## Operation: CreateNode%1049191555
      virtual cTree * CreateNode (CONST_STRING_T node_name, cTree *parent = NULL);

      //## Operation: Path%1048867687
      virtual STRING_T Path ();

      //## Operation: Iterator%1049099896
      cTree::TreeIterator Iterator ();

      //## Operation: Children%1049099905
      ULONG_T Children ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3E8486BB02BF
      STRING_T get_Name () const;

      //## Attribute: Level%3E8889410290
      ULONG_T get_Level () const;
      void set_Level (ULONG_T value);

      //## Attribute: Index%3E880E710000
      ULONG_T get_Index () const;
      void set_Index (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cTree%3E8469320119.public preserve=yes
      //## end cTree%3E8469320119.public

  protected:
    // Data Members for Class Attributes

      //## begin cTree::Name%3E8486BB02BF.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cTree::Name%3E8486BB02BF.attr

      //## begin cTree::Level%3E8889410290.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Level;
      //## end cTree::Level%3E8889410290.attr

      //## begin cTree::Index%3E880E710000.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Index;
      //## end cTree::Index%3E880E710000.attr

    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E84741500AB
      //## Role: cTree::Parent%3E84741F035C
      //## begin cTree::Parent%3E84741F035C.role preserve=no  public: cTree {0..n -> 1RFHN}
      cTree *_Parent;
      //## end cTree::Parent%3E84741F035C.role

      //## Association: System::Namespace::<unnamed>%3E84741500AB
      //## Role: cTree::Children%3E84741F035B
      //## begin cTree::Children%3E84741F035B.role preserve=no  public: cTree {1 -> 0..nRFHN}
      std::vector<cTree*> _Children;
      //## end cTree::Children%3E84741F035B.role

      //## Association: System::Namespace::<unnamed>%3E846AC5037A
      //## Role: cTree::Object%3E846AC7004E
      //## begin cTree::Object%3E846AC7004E.role preserve=no  public: cNodeObject {0..1 -> 0..1RFHN}
      cNodeObject *_Object;
      //## end cTree::Object%3E846AC7004E.role

      //## Association: System::Namespace::<unnamed>%3E846AC901D4
      //## Role: cTree::Context%3E846ACA01A5
      //## begin cTree::Context%3E846ACA01A5.role preserve=no  public: cNodeContext {0..1 -> 0..1RFHN}
      cNodeContext *_Context;
      //## end cTree::Context%3E846ACA01A5.role

    // Additional Protected Declarations
      //## begin cTree%3E8469320119.protected preserve=yes
      //## end cTree%3E8469320119.protected

  private:
    // Additional Private Declarations
      //## begin cTree%3E8469320119.private preserve=yes
      //## end cTree%3E8469320119.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Child%1048867690
      cTree * Child (CONST_STRING_T name);

      //## Operation: AddChild%1048867691
      void AddChild (cTree *child);

      //## Operation: LeftSplit%1048867688
      static STRING_T LeftSplit (CONST_STRING_T path, STRING_T &tail);

      //## Operation: RightSplit%1048867689
      static STRING_T RightSplit (CONST_STRING_T path, STRING_T &tail);

    // Additional Implementation Declarations
      //## begin cTree%3E8469320119.implementation preserve=yes
      //## end cTree%3E8469320119.implementation

};

//## begin cTree%3E8469320119.postscript preserve=yes
//## end cTree%3E8469320119.postscript

// Class cTree::TreeIterator 

// Class cTree 

//## begin module%3E8469320119.epilog preserve=yes
//## end module%3E8469320119.epilog


#endif
