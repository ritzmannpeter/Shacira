//## begin module%3AE83FE50190.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE83FE50190.cm

//## begin module%3AE83FE50190.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AE83FE50190.cp

//## Module: cSysProcess%3AE83FE50190; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSysProcess.h

#ifndef cSysProcess_h
#define cSysProcess_h 1

//## begin module%3AE83FE50190.includes preserve=yes
//## end module%3AE83FE50190.includes

//## begin module%3AE83FE50190.additionalDeclarations preserve=yes
//## end module%3AE83FE50190.additionalDeclarations


//## begin cSysProcess%3AE83FE50190.preface preserve=yes
//## end cSysProcess%3AE83FE50190.preface

//## Class: cSysProcess%3AE83FE50190
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cSysProcess 
{
  //## begin cSysProcess%3AE83FE50190.initialDeclarations preserve=yes
public:
  //## end cSysProcess%3AE83FE50190.initialDeclarations

    //## Constructors (generated)
      cSysProcess();

      cSysProcess(const cSysProcess &right);

    //## Constructors (specified)
      //## Operation: cSysProcess%1171392475
      cSysProcess (BOOL_T auto_terminate);

    //## Destructor (generated)
      virtual ~cSysProcess();


    //## Other Operations (specified)
      //## Operation: Create%988300376
      BOOL_T Create (CONST_STRING_T name, CONST_STRING_T args = NULL);

      //## Operation: Spawn%988306473
      BOOL_T Spawn (CONST_STRING_T name, CONST_STRING_T args = NULL);

      //## Operation: Execute%1171386482
      BOOL_T Execute (int &exit_code, CONST_STRING_T name, CONST_STRING_T args = NULL);

      //## Operation: Terminate%988300377
      BOOL_T Terminate ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Pid%3AE8408B03D4
      INT_T get_Pid () const;

      //## Attribute: AutoTerminate%45D2075101C5
      BOOL_T get_AutoTerminate () const;
      void set_AutoTerminate (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cSysProcess%3AE83FE50190.public preserve=yes
      //## end cSysProcess%3AE83FE50190.public

  protected:
    // Data Members for Class Attributes

      //## begin cSysProcess::Pid%3AE8408B03D4.attr preserve=no  public: INT_T {U} 0
      INT_T _Pid;
      //## end cSysProcess::Pid%3AE8408B03D4.attr

      //## begin cSysProcess::AutoTerminate%45D2075101C5.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _AutoTerminate;
      //## end cSysProcess::AutoTerminate%45D2075101C5.attr

    // Additional Protected Declarations
      //## begin cSysProcess%3AE83FE50190.protected preserve=yes
      //## end cSysProcess%3AE83FE50190.protected

  private:
    // Additional Private Declarations
      //## begin cSysProcess%3AE83FE50190.private preserve=yes
      //## end cSysProcess%3AE83FE50190.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ProcessHandle%3AE840A903D7
      //## begin cSysProcess::ProcessHandle%3AE840A903D7.attr preserve=no  implementation: HANDLE {U} NULL
      HANDLE _ProcessHandle;
      //## end cSysProcess::ProcessHandle%3AE840A903D7.attr

      //## Attribute: ThreadHandle%45D1F08F0399
      //## begin cSysProcess::ThreadHandle%45D1F08F0399.attr preserve=no  implementation: HANDLE {U} NULL
      HANDLE _ThreadHandle;
      //## end cSysProcess::ThreadHandle%45D1F08F0399.attr

      //## Attribute: Name%3AE844A901BD
      //## begin cSysProcess::Name%3AE844A901BD.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Name;
      //## end cSysProcess::Name%3AE844A901BD.attr

      //## Attribute: Args%3AE845C00087
      //## begin cSysProcess::Args%3AE845C00087.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Args;
      //## end cSysProcess::Args%3AE845C00087.attr

    // Additional Implementation Declarations
      //## begin cSysProcess%3AE83FE50190.implementation preserve=yes
      //## end cSysProcess%3AE83FE50190.implementation

};

//## begin cSysProcess%3AE83FE50190.postscript preserve=yes
//## end cSysProcess%3AE83FE50190.postscript

// Class cSysProcess 

//## begin module%3AE83FE50190.epilog preserve=yes
//## end module%3AE83FE50190.epilog


#endif
