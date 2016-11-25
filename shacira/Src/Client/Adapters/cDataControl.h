//## begin module%3D0775C501BC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D0775C501BC.cm

//## begin module%3D0775C501BC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D0775C501BC.cp

//## Module: cDataControl%3D0775C501BC; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cDataControl.h

#ifndef cDataControl_h
#define cDataControl_h 1

//## begin module%3D0775C501BC.includes preserve=yes
//## end module%3D0775C501BC.includes


class __DLL_EXPORT__ cVarRef;

//## begin module%3D0775C501BC.additionalDeclarations preserve=yes
//## end module%3D0775C501BC.additionalDeclarations


//## begin cDataControl%3D0775C501BC.preface preserve=yes
//## end cDataControl%3D0775C501BC.preface

//## Class: cDataControl%3D0775C501BC
//## Category: Client::Adapters%3DCC05190174
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cDataControl 
{
  //## begin cDataControl%3D0775C501BC.initialDeclarations preserve=yes
public:
  //## end cDataControl%3D0775C501BC.initialDeclarations

    //## Constructors (generated)
      cDataControl();

      cDataControl(const cDataControl &right);

    //## Constructors (specified)
      //## Operation: cDataControl%1043914507
      cDataControl (cVarRef *var_ref);

    //## Destructor (generated)
      virtual ~cDataControl();


    //## Other Operations (specified)
      //## Operation: NewValue%1023899454
      virtual void NewValue (CONST_STRING_T value, ULONG_T time_offset, UCHAR_T data_type, ULONG_T size, ULONG_T data_set);

      //## Operation: NewValue%1073907456
      virtual void NewValue (BUF_T buf, ULONG_T time_offset, UCHAR_T data_type, ULONG_T size, ULONG_T data_set);

      //## Operation: UpdateValue%1043914506
      virtual void UpdateValue ();

  public:
    // Additional Public Declarations
      //## begin cDataControl%3D0775C501BC.public preserve=yes
         virtual void * Widget() const;
         virtual STRING_T Name() const;
      //## end cDataControl%3D0775C501BC.public

  protected:
    // Data Members for Associations

      //## Association: System::Comm::<unnamed>%3D07768D01D7
      //## Role: cDataControl::VarRef%3D07768E0298
      //## begin cDataControl::VarRef%3D07768E0298.role preserve=no  public: cVarRef {1 -> 1RFHN}
      cVarRef *_VarRef;
      //## end cDataControl::VarRef%3D07768E0298.role

    // Additional Protected Declarations
      //## begin cDataControl%3D0775C501BC.protected preserve=yes
      //## end cDataControl%3D0775C501BC.protected

  private:
    // Additional Private Declarations
      //## begin cDataControl%3D0775C501BC.private preserve=yes
      //## end cDataControl%3D0775C501BC.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDataControl%3D0775C501BC.implementation preserve=yes
      //## end cDataControl%3D0775C501BC.implementation

};

//## begin cDataControl%3D0775C501BC.postscript preserve=yes
//## end cDataControl%3D0775C501BC.postscript

// Class cDataControl 

//## begin module%3D0775C501BC.epilog preserve=yes
//## end module%3D0775C501BC.epilog


#endif
