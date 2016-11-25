//## begin module%411212750138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411212750138.cm

//## begin module%411212750138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%411212750138.cp

//## Module: cSubFile%411212750138; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cSubFile.h

#ifndef cSubFile_h
#define cSubFile_h 1

//## begin module%411212750138.includes preserve=yes
//## end module%411212750138.includes


class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cStringBuffer;

//## begin module%411212750138.additionalDeclarations preserve=yes
//## end module%411212750138.additionalDeclarations


//## begin cSubFile%411212750138.preface preserve=yes
//## end cSubFile%411212750138.preface

//## Class: cSubFile%411212750138
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4112259B00FA;cVarDef { -> F}

class __DLL_EXPORT__ cSubFile 
{
  //## begin cSubFile%411212750138.initialDeclarations preserve=yes
public:
  //## end cSubFile%411212750138.initialDeclarations

    //## Constructors (generated)
      cSubFile();

      cSubFile(const cSubFile &right);

    //## Constructors (specified)
      //## Operation: cSubFile%1091705311
      cSubFile (CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cSubFile();


    //## Other Operations (specified)
      //## Operation: AddVariable%1091699609
      void AddVariable (CONST_STRING_T name, cVariable *variable);

      //## Operation: PrintVariables%1092126570
      void PrintVariables(STRING_T &buf);
      // cStringBuffer based method PrintVariables
      void PrintVariables(cStringBuffer &buf);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%411219CC006D
      STRING_T get_Name () const;

  public:
    // Additional Public Declarations
      //## begin cSubFile%411212750138.public preserve=yes
      //## end cSubFile%411212750138.public

  protected:
    // Data Members for Class Attributes

      //## begin cSubFile::Name%411219CC006D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cSubFile::Name%411219CC006D.attr

    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%42E6567E0232
      //## Role: cSubFile::Variables%42E6567F0222
      //## Qualifier: name%42E656C8001F; STRING_T
      //## begin cSubFile::Variables%42E6567F0222.role preserve=no  public: cVariable { -> 0..nRFHN}
      std::map<STRING_T, cVariable*> _Variables;
      //## end cSubFile::Variables%42E6567F0222.role

    // Additional Protected Declarations
      //## begin cSubFile%411212750138.protected preserve=yes
      //## end cSubFile%411212750138.protected

  private:
    // Additional Private Declarations
      //## begin cSubFile%411212750138.private preserve=yes
      //## end cSubFile%411212750138.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSubFile%411212750138.implementation preserve=yes
      //## end cSubFile%411212750138.implementation

};

//## begin cSubFile%411212750138.postscript preserve=yes
//## end cSubFile%411212750138.postscript

// Class cSubFile 

//## begin module%411212750138.epilog preserve=yes
//## end module%411212750138.epilog


#endif
