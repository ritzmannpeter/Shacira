//## begin module%3AB878F3028A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB878F3028A.cm

//## begin module%3AB878F3028A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AB878F3028A.cp

//## Module: cLogFile%3AB878F3028A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cLogFile.h

#ifndef cLogFile_h
#define cLogFile_h 1

//## begin module%3AB878F3028A.includes preserve=yes
//## end module%3AB878F3028A.includes

// cTimeObject
#include "System/cTimeObject.h"
// cStaticObject
#include "System/Objects/cStaticObject.h"

class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3AB878F3028A.additionalDeclarations preserve=yes

#define CLOSE_ON_IDLE

//## end module%3AB878F3028A.additionalDeclarations


//## begin cLogFile%3AB878F3028A.preface preserve=yes
//## end cLogFile%3AB878F3028A.preface

//## Class: cLogFile%3AB878F3028A
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AB8C00103B2;cTokenizer { -> F}
//## Uses: <unnamed>%3B8A8CC101ED;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3DCA4FF70209;cTimeObject { -> }
//## Uses: <unnamed>%3DCA55C802D1;cObjectLock { -> F}

class __DLL_EXPORT__ cLogFile : public cStaticObject  //## Inherits: <unnamed>%3DCA510B018D
{
  //## begin cLogFile%3AB878F3028A.initialDeclarations preserve=yes
public:
  //## end cLogFile%3AB878F3028A.initialDeclarations

    //## Constructors (generated)
      cLogFile();

      cLogFile(const cLogFile &right);

    //## Constructors (specified)
      //## Operation: cLogFile%985174332
      cLogFile (CONST_STRING_T file, BOOL_T read_only = true);

    //## Destructor (generated)
      virtual ~cLogFile();


    //## Other Operations (specified)
      //## Operation: Printf%985174333
      BOOL_T Printf (CONST_STRING_T fmt_str, ... );

      //## Operation: LogPrintf%985174334
      BOOL_T LogPrintf (CONST_STRING_T fmt_str, ... );

      //## Operation: IsNewFile%985174353
      BOOL_T IsNewFile ();

      //## Operation: IsNewDir%985174336
      BOOL_T IsNewDir ();

  public:
    // Additional Public Declarations
      //## begin cLogFile%3AB878F3028A.public preserve=yes
      //## end cLogFile%3AB878F3028A.public

  protected:
    // Additional Protected Declarations
      //## begin cLogFile%3AB878F3028A.protected preserve=yes
      //## end cLogFile%3AB878F3028A.protected

  private:
    // Additional Private Declarations
      //## begin cLogFile%3AB878F3028A.private preserve=yes
      //## end cLogFile%3AB878F3028A.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CreateDir%985174337
      BOOL_T CreateDir (CONST_STRING_T dir);

      //## Operation: SetReadOnly%985197430
      BOOL_T SetReadOnly (BOOL_T read_only);

    // Data Members for Class Attributes

      //## Attribute: Time%3AB87C9300D6
      //## begin cLogFile::Time%3AB87C9300D6.attr preserve=no  private: cTimeObject {U} 
      cTimeObject _Time;
      //## end cLogFile::Time%3AB87C9300D6.attr

      //## Attribute: File%3AB89484031E
      //## begin cLogFile::File%3AB89484031E.attr preserve=no  private: STRING_T {U} 
      STRING_T _File;
      //## end cLogFile::File%3AB89484031E.attr

      //## Attribute: Directory%3AB8A4DF017A
      //## begin cLogFile::Directory%3AB8A4DF017A.attr preserve=no  private: STRING_T {U} 
      STRING_T _Directory;
      //## end cLogFile::Directory%3AB8A4DF017A.attr

      //## Attribute: FileName%3AB8A4FA0114
      //## begin cLogFile::FileName%3AB8A4FA0114.attr preserve=no  private: STRING_T {U} 
      STRING_T _FileName;
      //## end cLogFile::FileName%3AB8A4FA0114.attr

      //## Attribute: Stream%3AB893EF0297
      //## begin cLogFile::Stream%3AB893EF0297.attr preserve=no  private: FILE * {U} NULL
      FILE *_Stream;
      //## end cLogFile::Stream%3AB893EF0297.attr

      //## Attribute: IsNewFile%3AB8CC3B01A0
      //## begin cLogFile::IsNewFile%3AB8CC3B01A0.attr preserve=no  private: BOOL_T {U} true
      BOOL_T _IsNewFile;
      //## end cLogFile::IsNewFile%3AB8CC3B01A0.attr

      //## Attribute: IsNewDir%3AB8CC580043
      //## begin cLogFile::IsNewDir%3AB8CC580043.attr preserve=no  private: BOOL_T {U} true
      BOOL_T _IsNewDir;
      //## end cLogFile::IsNewDir%3AB8CC580043.attr

      //## Attribute: ReadOnly%3AB8F20C02F5
      //## begin cLogFile::ReadOnly%3AB8F20C02F5.attr preserve=no  private: BOOL_T {U} false
      BOOL_T _ReadOnly;
      //## end cLogFile::ReadOnly%3AB8F20C02F5.attr

    // Additional Implementation Declarations
      //## begin cLogFile%3AB878F3028A.implementation preserve=yes
      //## end cLogFile%3AB878F3028A.implementation

};

//## begin cLogFile%3AB878F3028A.postscript preserve=yes
//## end cLogFile%3AB878F3028A.postscript

// Class cLogFile 

//## begin module%3AB878F3028A.epilog preserve=yes
//## end module%3AB878F3028A.epilog


#endif
