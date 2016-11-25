//## begin module%3B8A315401D5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A315401D5.cm

//## begin module%3B8A315401D5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A315401D5.cp

//## Module: cFileSystemUtils%3B8A315401D5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cFileSystemUtils.h

#ifndef cFileSystemUtils_h
#define cFileSystemUtils_h 1

//## begin module%3B8A315401D5.includes preserve=yes
//## end module%3B8A315401D5.includes

// cStringUtils
#include "System/cStringUtils.h"
//## begin module%3B8A315401D5.additionalDeclarations preserve=yes

typedef enum {FSYS_WINDOWS=1, FSYS_UNIX=2} FileSystemTypes;
#define PATH_DELIMITERS    "/\\"
#define BACK_SLASH_STRING  "\\"
#define SLASH_STRING       "/"
#define SLASH              '/'
#define BACK_SLASH         '\\'

#define RESTRICT_TO_ONE_PROCESSOR   0x00000001

//## end module%3B8A315401D5.additionalDeclarations


//## begin cFileSystemUtils%3B8A315401D5.preface preserve=yes
//## end cFileSystemUtils%3B8A315401D5.preface

//## Class: cFileSystemUtils%3B8A315401D5
//	This class offers methods to query and manipulate the
//	underlying file system.
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B8A4DF60030;cStringUtils { -> }

class __DLL_EXPORT__ cFileSystemUtils 
{
  //## begin cFileSystemUtils%3B8A315401D5.initialDeclarations preserve=yes
public:
  //## end cFileSystemUtils%3B8A315401D5.initialDeclarations

    //## Constructors (generated)
      cFileSystemUtils();

      cFileSystemUtils(const cFileSystemUtils &right);

    //## Destructor (generated)
      virtual ~cFileSystemUtils();


    //## Other Operations (specified)
      //## Operation: CreateDir%998912344
      //	This methods creates the directory denoted by
      //	directory.The directory is created even if there is
      //	actually no path to this directory. All missing
      //	directories are created.
      static BOOL_T CreateDir (CONST_STRING_T directory);

      //## Operation: RemoveFile%1037294318
      //	This methods removes a file from the file system.
      static BOOL_T RemoveFile (CONST_STRING_T file);

      //## Operation: RenameFile%1141375555
      static BOOL_T RenameFile (CONST_STRING_T src_path, CONST_STRING_T dst_path);

      //## Operation: DirExists%998912345
      //	This checks for existence of the specified directory.
      static BOOL_T DirExists (CONST_STRING_T path);

      //## Operation: FileExists%998912346
      //	This checks for existence of the specified file.
      static BOOL_T FileExists (CONST_STRING_T path);

      //## Operation: FileExistence%1044520499
      //	This method checks the existence of a file in a couple
      //	of paths and return a path to the file taht is first
      //	found.
      static BOOL_T FileExistence (STRING_VECTOR_T &paths, CONST_STRING_T file_name, STRING_T &file);

      //## Operation: FileSize%1013674760
      //	This checks for existence of the specified file.
      static ULONG_T FileSize (CONST_STRING_T path);

      //## Operation: FileList%1000386745
      //	Lists files of a specified directory that matches
      //	pattern.
      static BOOL_T FileList (STRING_LIST_T &file_names, CONST_STRING_T path = "", CONST_STRING_T pattern = "*");

      //## Operation: FullPath%998912347
      //	This method returns the full path to the file specified
      //	in path.
      static STRING_T FullPath (CONST_STRING_T path);

      //## Operation: LeftSplit%998912348
      //	This method splits a path specification in tow parts
      //	delivering a head and a tail. The split operation is
      //	done on the first path delimiter found.
      static void LeftSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail);

      //## Operation: RightSplit%998912349
      //	This method splits a path specification in tow parts
      //	delivering a head and a tail. The split operation is
      //	done on the last path delimiter found.
      static void RightSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail);

      //## Operation: AppendPath%998912355
      //	This method appends one part of a path to another part
      //	of a path.
      static STRING_T AppendPath (CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter = SLASH_STRING);

      //## Operation: FileName%998912350
      //	This method returns the file name of the specified in
      //	path.
      static STRING_T FileName (CONST_STRING_T path);

      //## Operation: BaseFileName%1074777877
      //	This method returns the drive name of the specified in
      //	path.
      static STRING_T BaseFileName (CONST_STRING_T path);

      //## Operation: DirName%998912351
      //	This method returns the directory name of the specified
      //	in path.
      static STRING_T DirName (CONST_STRING_T path);

      //## Operation: DriveName%998912359
      //	This method returns the drive name of the specified in
      //	path.
      static STRING_T DriveName (CONST_STRING_T path);

      //## Operation: FileExtension%998912352
      //	This method returns the file extension of the specified
      //	in path.
      static STRING_T FileExtension (CONST_STRING_T path);

      //## Operation: CurrentDir%998912356
      //	This method returns the current directory of the process.
      static STRING_T CurrentDir ();

      //## Operation: CurrentDrive%998912363
      //	This method returns the current directory of the process.
      static STRING_T CurrentDrive ();

      //## Operation: StartupDir%998912357
      //	This method returns the current directory of the process
      //	when starting up.
      static STRING_T StartupDir ();

      //## Operation: IsRelativePath%998912360
      //	Returns true if the specified path is a relative path
      //	specification.
      static BOOL_T IsRelativePath (CONST_STRING_T path);

      //## Operation: IsAbsolutePath%998912361
      //	Returns true if the specified path is an absolute path
      //	specification (not depending on the currentdirectory).
      static BOOL_T IsAbsolutePath (CONST_STRING_T path);

      //## Operation: IsUNCPath%998912365
      //	Returns true if the specified path is an absolute path
      //	specification (not depending on the currentdirectory).
      static BOOL_T IsUNCPath (CONST_STRING_T path);

      //## Operation: IsPathDelimiter%998912362
      //	Returns true if the path specified as UNC path.
      static BOOL_T IsPathDelimiter (CHAR_T c);

      //## Operation: IsDrive%998912364
      //	Returns true if the path specified a drive specification.
      static BOOL_T IsDrive (CONST_STRING_T path);

      //## Operation: IsUNCRoot%1141396797
      //	Returns true if the root part of a UNC path.
      static BOOL_T IsUNCRoot (CONST_STRING_T path);

      //## Operation: IsDriveChar%998912366
      //	Returns true if the path specified as UNC path.
      static BOOL_T IsDriveChar (CHAR_T c);

      //## Operation: WriteProfileString%1046178221
      static INT_T WriteProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value, CONST_STRING_T file);

      //## Operation: GetProfileString%1053266946
      static STRING_T GetProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T default_value, CONST_STRING_T file);

      //## Operation: LeftStrip%1144065933
      static STRING_T LeftStrip (CONST_STRING_T path);

      //## Operation: LeftStrip%1144065935
      static STRING_T LeftStrip (CONST_STRING_T path, STRING_T &component);

      //## Operation: RightStrip%1144065934
      static STRING_T RightStrip (CONST_STRING_T path);

      //## Operation: RightStrip%1144065936
      static STRING_T RightStrip (CONST_STRING_T path, STRING_T &component);

      //## Operation: NameComponents%1144078177
      static void NameComponents (CONST_STRING_T file_name, STRING_T &base_name, STRING_T &extension);

      //## Operation: Resolve%1144143457
      static STRING_T Resolve (CONST_STRING_T path);
      static BOOL_T GetDiskInfo (CONST_STRING_T path, ULONG_T &free_space, ULONG_T &occupied_space, ULONG_T flags);

      static void FlushFile(const char * filename);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Type%3B8A340400E4
      static FileSystemTypes get_Type ();
      static void set_Type (FileSystemTypes value);

  public:
    // Additional Public Declarations
      //## begin cFileSystemUtils%3B8A315401D5.public preserve=yes
      //## end cFileSystemUtils%3B8A315401D5.public

  protected:
    // Data Members for Class Attributes

      //## begin cFileSystemUtils::Type%3B8A340400E4.attr preserve=no  public: static FileSystemTypes {U} FSYS_WINDOWS
      static FileSystemTypes _Type;
      //## end cFileSystemUtils::Type%3B8A340400E4.attr

    // Additional Protected Declarations
      //## begin cFileSystemUtils%3B8A315401D5.protected preserve=yes
      //## end cFileSystemUtils%3B8A315401D5.protected

  private:
    // Additional Private Declarations
      //## begin cFileSystemUtils%3B8A315401D5.private preserve=yes
      //## end cFileSystemUtils%3B8A315401D5.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: StartupDirectory%3B8A5B5A0292
      //## begin cFileSystemUtils::StartupDirectory%3B8A5B5A0292.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _StartupDirectory;
      //## end cFileSystemUtils::StartupDirectory%3B8A5B5A0292.attr

    // Additional Implementation Declarations
      //## begin cFileSystemUtils%3B8A315401D5.implementation preserve=yes
      //## end cFileSystemUtils%3B8A315401D5.implementation

};

//## begin cFileSystemUtils%3B8A315401D5.postscript preserve=yes
//## end cFileSystemUtils%3B8A315401D5.postscript

// Class cFileSystemUtils 

//## begin module%3B8A315401D5.epilog preserve=yes
//## end module%3B8A315401D5.epilog


#endif
