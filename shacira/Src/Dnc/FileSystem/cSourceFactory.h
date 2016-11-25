//## begin module%3F4DFB980290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4DFB980290.cm

//## begin module%3F4DFB980290.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4DFB980290.cp

//## Module: cSourceFactory%3F4DFB980290; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cSourceFactory.h

#ifndef cSourceFactory_h
#define cSourceFactory_h 1

//## begin module%3F4DFB980290.includes preserve=yes
//## end module%3F4DFB980290.includes


class __DLL_EXPORT__ cFTPSource;
class __DLL_EXPORT__ cDiskSource;
class __DLL_EXPORT__ cCellSource;
class __DLL_EXPORT__ cCarrierSource;
class __DLL_EXPORT__ cToolFileSource;

//## begin module%3F4DFB980290.additionalDeclarations preserve=yes
//## end module%3F4DFB980290.additionalDeclarations


//## begin cSourceFactory%3F4DFB980290.preface preserve=yes
//## end cSourceFactory%3F4DFB980290.preface

//## Class: cSourceFactory%3F4DFB980290
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F4DFCB40000;cCarrierSource { -> F}
//## Uses: <unnamed>%3F4DFCCC00FA;cDiskSource { -> F}
//## Uses: <unnamed>%3F4DFCE001E4;cCellSource { -> F}
//## Uses: <unnamed>%3F4DFD99037A;cFTPSource { -> F}
//## Uses: <unnamed>%3F4E17A402FD;cToolFileSource { -> F}

class __DLL_EXPORT__ cSourceFactory 
{
  //## begin cSourceFactory%3F4DFB980290.initialDeclarations preserve=yes
public:
  //## end cSourceFactory%3F4DFB980290.initialDeclarations

    //## Constructors (generated)
      cSourceFactory();

      cSourceFactory(const cSourceFactory &right);

    //## Destructor (generated)
      virtual ~cSourceFactory();


    //## Other Operations (specified)
      //## Operation: CreateSource%1062075838
      static cToolFileSource * CreateSource (CONST_STRING_T path = NULL);

  public:
    // Additional Public Declarations
      //## begin cSourceFactory%3F4DFB980290.public preserve=yes
      //## end cSourceFactory%3F4DFB980290.public

  protected:
    // Additional Protected Declarations
      //## begin cSourceFactory%3F4DFB980290.protected preserve=yes
      //## end cSourceFactory%3F4DFB980290.protected

  private:
    // Additional Private Declarations
      //## begin cSourceFactory%3F4DFB980290.private preserve=yes
      //## end cSourceFactory%3F4DFB980290.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSourceFactory%3F4DFB980290.implementation preserve=yes
      //## end cSourceFactory%3F4DFB980290.implementation

};

//## begin cSourceFactory%3F4DFB980290.postscript preserve=yes
//## end cSourceFactory%3F4DFB980290.postscript

// Class cSourceFactory 

//## begin module%3F4DFB980290.epilog preserve=yes
//## end module%3F4DFB980290.epilog


#endif
