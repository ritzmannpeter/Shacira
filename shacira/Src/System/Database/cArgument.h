//## begin module%3C7E425B0200.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E425B0200.cm

//## begin module%3C7E425B0200.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E425B0200.cp

//## Module: cArgument%3C7E425B0200; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cArgument.h

#ifndef cArgument_h
#define cArgument_h 1

//## begin module%3C7E425B0200.includes preserve=yes
//## end module%3C7E425B0200.includes


class __DLL_EXPORT__ cFuncRef;

//## begin module%3C7E425B0200.additionalDeclarations preserve=yes
//## end module%3C7E425B0200.additionalDeclarations


//## begin cArgument%3C7E425B0200.preface preserve=yes
//## end cArgument%3C7E425B0200.preface

//## Class: cArgument%3C7E425B0200
//	This class implements concrete function argument
//	information in a function reference (function call).
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40EAE74D02DE;cFuncRef { -> F}

class __DLL_EXPORT__ cArgument 
{
  //## begin cArgument%3C7E425B0200.initialDeclarations preserve=yes
public:
  //## end cArgument%3C7E425B0200.initialDeclarations

    //## Constructors (generated)
      cArgument();

      cArgument(const cArgument &right);

    //## Destructor (generated)
      virtual ~cArgument();


    //## Other Operations (specified)
      //## Operation: GetValue%1042646888
      //	Method to retrieve an argument value. This method is
      //	abstract and must be reimplemented by all derived
      //	argument classes. To deal with different data types
      //	there is more than one form of the GetValue method.
      virtual void GetValue (LONG_T &value) = 0;

      //## Operation: GetValue%1088678759
      virtual void GetValue (ULONG_T &value) = 0;

      //## Operation: GetValue%1088678760
      virtual void GetValue (FLOAT_T &value) = 0;

      //## Operation: GetValue%1042646889
      virtual void GetValue (DOUBLE_T &value) = 0;

      //## Operation: GetValue%1042646887
      virtual void GetValue (STRING_T &value) = 0;

      //## Operation: GetValue%1088678761
      virtual void GetValue (WSTRING_T &value) = 0;

      //## Operation: GetValue%1088678762
      virtual void GetValue (PTR_T &value) = 0;

      //## Operation: GetFuncRef%1089133001
      //	Retrieves the function address of function type
      //	arguments. All other types of arguments return a null
      //	pointer when this method is called.
      virtual cFuncRef * GetFuncRef ();

      //## Operation: DataType%1061805339
      //	Retrieves the data type of the argument.
      UCHAR_T DataType ();

    // Data Members for Class Attributes

      //## Attribute: DataType%3F49C76D00DA
      //## begin cArgument::DataType%3F49C76D00DA.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cArgument::DataType%3F49C76D00DA.attr

  public:
    // Additional Public Declarations
      //## begin cArgument%3C7E425B0200.public preserve=yes
      //## end cArgument%3C7E425B0200.public

  protected:
    // Additional Protected Declarations
      //## begin cArgument%3C7E425B0200.protected preserve=yes
      //## end cArgument%3C7E425B0200.protected

  private:
    // Additional Private Declarations
      //## begin cArgument%3C7E425B0200.private preserve=yes
      //## end cArgument%3C7E425B0200.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cArgument%3C7E425B0200.implementation preserve=yes
      //## end cArgument%3C7E425B0200.implementation

};

//## begin cArgument%3C7E425B0200.postscript preserve=yes

typedef std::vector<cArgument*> ARG_VECTOR_T;

//## end cArgument%3C7E425B0200.postscript

// Class cArgument 

//## begin module%3C7E425B0200.epilog preserve=yes
//## end module%3C7E425B0200.epilog


#endif
