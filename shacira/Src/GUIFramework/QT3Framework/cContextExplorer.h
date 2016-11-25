//## begin module%416814BE0186.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%416814BE0186.cm

//## begin module%416814BE0186.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%416814BE0186.cp

//## Module: cContextExplorer%416814BE0186; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\QTFramework\cContextExplorer.h

#ifndef cContextExplorer_h
#define cContextExplorer_h 1

//## begin module%416814BE0186.includes preserve=yes

#include "ContextExplorerDialog.h"

//## end module%416814BE0186.includes

// cContextChooser
#include "GUIFramework/Interface/cContextChooser.h"
//## begin module%416814BE0186.additionalDeclarations preserve=yes
//## end module%416814BE0186.additionalDeclarations


//## begin cContextExplorer%416814BE0186.preface preserve=yes
//## end cContextExplorer%416814BE0186.preface

//## Class: cContextExplorer%416814BE0186
//## Category: GUIFramework::QTFramework%40054AF903A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cContextExplorer : public cContextChooser  //## Inherits: <unnamed>%416814F40280
{
  //## begin cContextExplorer%416814BE0186.initialDeclarations preserve=yes
public:
  //## end cContextExplorer%416814BE0186.initialDeclarations

    //## Constructors (generated)
      cContextExplorer();

      cContextExplorer(const cContextExplorer &right);

    //## Constructors (specified)
      //## Operation: cContextExplorer%1097340230
      cContextExplorer (QWidget *parent);

    //## Destructor (generated)
      virtual ~cContextExplorer();


    //## Other Operations (specified)
      //## Operation: GetContext%1097340229
      virtual cContext * GetContext ();

  public:
    // Additional Public Declarations
      //## begin cContextExplorer%416814BE0186.public preserve=yes
      //## end cContextExplorer%416814BE0186.public

  protected:
    // Additional Protected Declarations
      //## begin cContextExplorer%416814BE0186.protected preserve=yes
      //## end cContextExplorer%416814BE0186.protected

  private:
    // Additional Private Declarations
      //## begin cContextExplorer%416814BE0186.private preserve=yes
      //## end cContextExplorer%416814BE0186.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Parent%416817E70261
      //## begin cContextExplorer::Parent%416817E70261.attr preserve=no  implementation: QWidget * {U} NULL
      QWidget *_Parent;
      //## end cContextExplorer::Parent%416817E70261.attr

    // Additional Implementation Declarations
      //## begin cContextExplorer%416814BE0186.implementation preserve=yes
      //## end cContextExplorer%416814BE0186.implementation

};

//## begin cContextExplorer%416814BE0186.postscript preserve=yes
//## end cContextExplorer%416814BE0186.postscript

// Class cContextExplorer 

//## begin module%416814BE0186.epilog preserve=yes
//## end module%416814BE0186.epilog


#endif
