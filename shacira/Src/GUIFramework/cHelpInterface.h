//## begin module%41500F2C0222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41500F2C0222.cm

//## begin module%41500F2C0222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41500F2C0222.cp

//## Module: cHelpInterface%41500F2C0222; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\QTFramework\cHelpInterface.h

#ifndef cHelpInterface_h
#define cHelpInterface_h 1

//## begin module%41500F2C0222.includes preserve=yes
//## end module%41500F2C0222.includes

//## begin module%41500F2C0222.additionalDeclarations preserve=yes
//## end module%41500F2C0222.additionalDeclarations


//## begin cHelpInterface%41500F2C0222.preface preserve=yes
//## end cHelpInterface%41500F2C0222.preface

//## Class: cHelpInterface%41500F2C0222
//## Category: GUIFramework::QTFramework%40054AF903A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cHelpInterface 
{
  //## begin cHelpInterface%41500F2C0222.initialDeclarations preserve=yes
public:
  //## end cHelpInterface%41500F2C0222.initialDeclarations

    //## Constructors (generated)
      cHelpInterface();

      cHelpInterface(const cHelpInterface &right);

    //## Destructor (generated)
      virtual ~cHelpInterface();


    //## Other Operations (specified)
      //## Operation: Show%1095771619
      virtual void Show ();

      //## Operation: Hide%1095771620
      virtual void Hide ();

      //## Operation: Active%1095771621
      virtual BOOL_T Active ();

      //## Operation: ShowHelp%1095765931
      virtual bool ShowHelp (const QString & help_id1, const QString & help_id2);

      //## Operation: ExistHelpFile
      virtual bool ExistHelpFile(const QString & help_id1, const QString & help_id2);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Active%415272280203
      BOOL_T get_Active () const;
      void set_Active (BOOL_T value);

      STRING_T get_AdditionalPath () const;
      void set_AdditionalPath (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cHelpInterface%41500F2C0222.public preserve=yes
      //## end cHelpInterface%41500F2C0222.public

  protected:
    // Data Members for Class Attributes

      //## begin cHelpInterface::Active%415272280203.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Active;
      //## end cHelpInterface::Active%415272280203.attr

      STRING_T _AdditionalPath;

    // Additional Protected Declarations
      //## begin cHelpInterface%41500F2C0222.protected preserve=yes
      //## end cHelpInterface%41500F2C0222.protected

  private:
    // Additional Private Declarations
      //## begin cHelpInterface%41500F2C0222.private preserve=yes
      //## end cHelpInterface%41500F2C0222.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cHelpInterface%41500F2C0222.implementation preserve=yes
      //## end cHelpInterface%41500F2C0222.implementation

};

//## begin cHelpInterface%41500F2C0222.postscript preserve=yes
//## end cHelpInterface%41500F2C0222.postscript

// Class cHelpInterface 

//## begin module%41500F2C0222.epilog preserve=yes
//## end module%41500F2C0222.epilog


#endif
