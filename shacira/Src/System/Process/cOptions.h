//## begin module%3B87B9CC0371.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B87B9CC0371.cm

//## begin module%3B87B9CC0371.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B87B9CC0371.cp

//## Module: cOptions%3B87B9CC0371; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOptions.h

#ifndef cOptions_h
#define cOptions_h 1

//## begin module%3B87B9CC0371.includes preserve=yes
//## end module%3B87B9CC0371.includes


class __DLL_EXPORT__ cSHFile;

//## begin module%3B87B9CC0371.additionalDeclarations preserve=yes
//## end module%3B87B9CC0371.additionalDeclarations


//## begin cOptions%3B87B9CC0371.preface preserve=yes
//## end cOptions%3B87B9CC0371.preface

//## Class: cOptions%3B87B9CC0371
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%400E877E030D;cSHFile { -> F}

class __DLL_EXPORT__ cOptions 
{
  //## begin cOptions%3B87B9CC0371.initialDeclarations preserve=yes
public:
  //## end cOptions%3B87B9CC0371.initialDeclarations

    //## Constructors (generated)
      cOptions();

      cOptions(const cOptions &right);

    //## Constructors (specified)
      //## Operation: cOptions%998750938
      cOptions (int argc, char **argv);

    //## Destructor (generated)
      virtual ~cOptions();


    //## Other Operations (specified)
      //## Operation: SetOption%1074682887
      void SetOption (CONST_STRING_T option_name, CONST_STRING_T value);

      //## Operation: GetOption%1074682888
      void GetOption (CONST_STRING_T option_name, STRING_T &value);

      //## Operation: GetOption%1074682889
      void GetOption (CONST_STRING_T option_name, LONG_T &value);

      //## Operation: GetOption%1074682890
      void GetOption (CONST_STRING_T option_name, DOUBLE_T &value);

      //## Operation: GetOption%1074682891
      void GetOption (CONST_STRING_T option_name, BOOL_T &value);

      //## Operation: IsSet%998750940
      BOOL_T IsSet (CONST_STRING_T option_name);
      BOOL_T IsArgsFileFound ();

  public:
    // Additional Public Declarations
      //## begin cOptions%3B87B9CC0371.public preserve=yes
      //## end cOptions%3B87B9CC0371.public

  protected:
    // Additional Protected Declarations
      //## begin cOptions%3B87B9CC0371.protected preserve=yes
      //## end cOptions%3B87B9CC0371.protected

  private:
    // Additional Private Declarations
      //## begin cOptions%3B87B9CC0371.private preserve=yes
      //## end cOptions%3B87B9CC0371.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Option%1074682892
      BOOL_T Option (CONST_STRING_T option_name, STRING_T &value);

      //## Operation: Parse%1074682894
      void Parse (CONST_STRING_T option_string);

      //## Operation: ReadArgs%1074682895
      STRING_T ReadArgs ();

    // Data Members for Class Attributes

      //## Attribute: Options%3B87BC620124
      //## begin cOptions::Options%3B87BC620124.attr preserve=no  implementation: STRING_MAP_T {U} 
      STRING_MAP_T _Options;
      //## end cOptions::Options%3B87BC620124.attr

    // Additional Implementation Declarations
      //## begin cOptions%3B87B9CC0371.implementation preserve=yes
      //## end cOptions%3B87B9CC0371.implementation

};

//## begin cOptions%3B87B9CC0371.postscript preserve=yes
//## end cOptions%3B87B9CC0371.postscript

// Class cOptions 

//## begin module%3B87B9CC0371.epilog preserve=yes
//## end module%3B87B9CC0371.epilog


#endif
