//## begin module%3E9EF7DD02AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E9EF7DD02AF.cm

//## begin module%3E9EF7DD02AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E9EF7DD02AF.cp

//## Module: cSHFile%3E9EF7DD02AF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSHFile.h

#ifndef cSHFile_h
#define cSHFile_h 1

//## begin module%3E9EF7DD02AF.includes preserve=yes
//## end module%3E9EF7DD02AF.includes


class __DLL_EXPORT__ cTimeObject;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3E9EF7DD02AF.additionalDeclarations preserve=yes

#define FILE_ACCESS_APPEND		   0x00000001
#define FILE_ACCESS_READ_ONLY	   0x00000002
#define FILE_MODE_BINARY			0x00000004
#define FILE_MODE_CREATE			0x00000008

//## end module%3E9EF7DD02AF.additionalDeclarations


//## begin cSHFile%3E9EF7DD02AF.preface preserve=yes
//## end cSHFile%3E9EF7DD02AF.preface

//## Class: cSHFile%3E9EF7DD02AF
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E9EF8590271;cFileSystemUtils { -> F}
//## Uses: <unnamed>%41AF45E902FD;cTimeObject { -> F}

class __DLL_EXPORT__ cSHFile 
{
  //## begin cSHFile%3E9EF7DD02AF.initialDeclarations preserve=yes
public:
  //## end cSHFile%3E9EF7DD02AF.initialDeclarations

    //## Constructors (generated)
      cSHFile();

      cSHFile(const cSHFile &right);

    //## Constructors (specified)
      //## Operation: cSHFile%1050605979
      cSHFile (CONST_STRING_T file_name);

    //## Destructor (generated)
      virtual ~cSHFile();

    //## Assignment Operation (generated)
      const cSHFile & operator=(const cSHFile &right);


    //## Other Operations (specified)
      //## Operation: Open%1050605980
      BOOL_T Open (ULONG_T flags = FILE_ACCESS_READ_ONLY);

      //## Operation: Close%1050605981
      void Close ();

      //## Operation: Seek%1077548355
      BOOL_T Seek (ULONG_T pos);

      //## Operation: SeekEnd%1135258641
      BOOL_T SeekEnd ();

      //## Operation: Rewind%1135258642
      BOOL_T Rewind ();

      //## Operation: Read%1050605982
      ULONG_T Read (void *buf, ULONG_T buf_size, ULONG_T bytes);

      //## Operation: ReadLine%1050605983
      BOOL_T ReadLine (STRING_BUF_T buf, ULONG_T buf_size);

      //## Operation: ToString%1090486621
      STRING_T ToString ();

      //## Operation: Write%1053510999
      ULONG_T Write (void *buf, ULONG_T bytes);

      //## Operation: WriteBlock%1108486027
      BOOL_T WriteBlock (void *buf, ULONG_T bytes);

      //## Operation: ReadLine%1051885629
      BOOL_T ReadLine (STRING_T &buf);

      //## Operation: Printf%1050605984
      void Printf (CONST_STRING_T fmt_str, ... );

      //## Operation: Lock%1050605985
      void Lock ();

      //## Operation: UnLock%1050605986
      void UnLock ();

      //## Operation: Exists%1050605987
      BOOL_T Exists ();

      //## Operation: Remove%1050605988
      void Remove ();

      //## Operation: Move%1106850060
      void Move (CONST_STRING_T location);

      //## Operation: Path%1050605989
      STRING_T Path ();

      //## Operation: Size%1053511000
      ULONG_T Size ();

      //## Operation: Time%1102005112
      ULONG_T Time (ULONG_T ctrl = 0);

      //## Operation: SetReadOnly%1053513442
      void SetReadOnly (BOOL_T read_only);

      //## Operation: IsAsciiFile%1123070425
      static BOOL_T IsAsciiFile (CONST_STRING_T path);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Path%3E9EF83700CB
      STRING_T get_Path () const;

  public:
    // Additional Public Declarations
      //## begin cSHFile%3E9EF7DD02AF.public preserve=yes
      //## end cSHFile%3E9EF7DD02AF.public

  protected:
    // Data Members for Class Attributes

      //## begin cSHFile::Path%3E9EF83700CB.attr preserve=no  public: STRING_T {U} 
      STRING_T _Path;
      //## end cSHFile::Path%3E9EF83700CB.attr

    // Additional Protected Declarations
      //## begin cSHFile%3E9EF7DD02AF.protected preserve=yes
      //## end cSHFile%3E9EF7DD02AF.protected

  private:
    // Additional Private Declarations
      //## begin cSHFile%3E9EF7DD02AF.private preserve=yes
      //## end cSHFile%3E9EF7DD02AF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Stream%3E9EFB4503B9
      //## begin cSHFile::Stream%3E9EFB4503B9.attr preserve=no  implementation: FILE * {U} NULL
      FILE *_Stream;
      //## end cSHFile::Stream%3E9EFB4503B9.attr

    // Additional Implementation Declarations
      //## begin cSHFile%3E9EF7DD02AF.implementation preserve=yes
      //## end cSHFile%3E9EF7DD02AF.implementation

};

//## begin cSHFile%3E9EF7DD02AF.postscript preserve=yes
//## end cSHFile%3E9EF7DD02AF.postscript

// Class cSHFile 

//## begin module%3E9EF7DD02AF.epilog preserve=yes
//## end module%3E9EF7DD02AF.epilog


#endif
