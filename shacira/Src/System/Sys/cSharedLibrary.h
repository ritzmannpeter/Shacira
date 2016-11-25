//## begin module%412ADD260213.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412ADD260213.cm

//## begin module%412ADD260213.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412ADD260213.cp

//## Module: cSharedLibrary%412ADD260213; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSharedLibrary.h

#ifndef cSharedLibrary_h
#define cSharedLibrary_h 1

//## begin module%412ADD260213.includes preserve=yes
//## end module%412ADD260213.includes

//## begin module%412ADD260213.additionalDeclarations preserve=yes

class cSharedLibrary;
typedef void (*SHARED_FUNCTION_ADDRESS_T)();
#define INVALID_LIBRARY_HANDLE   NULL

#if defined(_WIN32)

typedef HMODULE LIBRARY_HANDLE_T;

#endif

#if defined(__linux)

typedef void * LIBRARY_HANDLE_T;

#endif

typedef std::map<STRING_T,cSharedLibrary*> SHARED_LIBRARY_MAP_T;
typedef std::map<STRING_T,SHARED_FUNCTION_ADDRESS_T> SHARED_FUNCTION_MAP_T;


//## end module%412ADD260213.additionalDeclarations


//## begin cSharedLibrary%412ADD260213.preface preserve=yes
//## end cSharedLibrary%412ADD260213.preface

//## Class: cSharedLibrary%412ADD260213
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cSharedLibrary 
{
  //## begin cSharedLibrary%412ADD260213.initialDeclarations preserve=yes
public:
  //## end cSharedLibrary%412ADD260213.initialDeclarations

    //## Constructors (generated)
      cSharedLibrary();

      cSharedLibrary(const cSharedLibrary &right);

    //## Constructors (specified)
      //## Operation: cSharedLibrary%1093328409
      cSharedLibrary (CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cSharedLibrary();


    //## Other Operations (specified)
      //## Operation: Load%1093328410
      LONG_T Load ();

      //## Operation: FunctionAddress%1093328411
      SHARED_FUNCTION_ADDRESS_T FunctionAddress (CONST_STRING_T func_name);

      //## Operation: Error%1093328413
      LONG_T Error ();

      //## Operation: Handle%1093328414
      LIBRARY_HANDLE_T Handle ();

      //## Operation: LibraryName%1093328415
      STRING_T LibraryName ();

      //## Operation: Library%1093328416
      static cSharedLibrary * Library (CONST_STRING_T name);

  public:
    // Additional Public Declarations
      //## begin cSharedLibrary%412ADD260213.public preserve=yes
      //## end cSharedLibrary%412ADD260213.public

  protected:
    // Additional Protected Declarations
      //## begin cSharedLibrary%412ADD260213.protected preserve=yes
      //## end cSharedLibrary%412ADD260213.protected

  private:
    // Additional Private Declarations
      //## begin cSharedLibrary%412ADD260213.private preserve=yes
      //## end cSharedLibrary%412ADD260213.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SharedLibraryName%1093328412
      STRING_T SharedLibraryName (CONST_STRING_T name);

    // Data Members for Class Attributes

      //## Attribute: Name%412ADD4A006D
      //## begin cSharedLibrary::Name%412ADD4A006D.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Name;
      //## end cSharedLibrary::Name%412ADD4A006D.attr

      //## Attribute: LibraryName%412ADD690109
      //## begin cSharedLibrary::LibraryName%412ADD690109.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _LibraryName;
      //## end cSharedLibrary::LibraryName%412ADD690109.attr

      //## Attribute: Handle%412ADF4D033C
      //## begin cSharedLibrary::Handle%412ADF4D033C.attr preserve=no  implementation: LIBRARY_HANDLE_T {U} INVALID_LIBRARY_HANDLE
      LIBRARY_HANDLE_T _Handle;
      //## end cSharedLibrary::Handle%412ADF4D033C.attr

      //## Attribute: NativeError%412AEBE6009C
      //## begin cSharedLibrary::NativeError%412AEBE6009C.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _NativeError;
      //## end cSharedLibrary::NativeError%412AEBE6009C.attr

      //## Attribute: Functions%412AECAA0261
      //## begin cSharedLibrary::Functions%412AECAA0261.attr preserve=no  implementation: SHARED_FUNCTION_MAP_T {U} 
      SHARED_FUNCTION_MAP_T _Functions;
      //## end cSharedLibrary::Functions%412AECAA0261.attr

      //## Attribute: Libraries%412AECDA038A
      //## begin cSharedLibrary::Libraries%412AECDA038A.attr preserve=no  implementation: static SHARED_LIBRARY_MAP_T {U} 
      static SHARED_LIBRARY_MAP_T _Libraries;
      //## end cSharedLibrary::Libraries%412AECDA038A.attr

    // Additional Implementation Declarations
      //## begin cSharedLibrary%412ADD260213.implementation preserve=yes
      //## end cSharedLibrary%412ADD260213.implementation

};

//## begin cSharedLibrary%412ADD260213.postscript preserve=yes
//## end cSharedLibrary%412ADD260213.postscript

// Class cSharedLibrary 

//## begin module%412ADD260213.epilog preserve=yes
//## end module%412ADD260213.epilog


#endif
