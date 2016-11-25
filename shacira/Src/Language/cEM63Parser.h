//## begin module%438055180281.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438055180281.cm

//## begin module%438055180281.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438055180281.cp

//## Module: cEM63Parser%438055180281; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Language\cEM63Parser.h

#ifndef cEM63Parser_h
#define cEM63Parser_h 1

//## begin module%438055180281.includes preserve=yes
//## end module%438055180281.includes


class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cEM63Session;
class __DLL_EXPORT__ cEM63Job;

//## begin module%438055180281.additionalDeclarations preserve=yes
//## end module%438055180281.additionalDeclarations


//## begin cEM63Parser%438055180281.preface preserve=yes
//## end cEM63Parser%438055180281.preface

//## Class: cEM63Parser%438055180281
//## Category: Language%3E0C4A4402CD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4380573B03DB;cContext { -> F}
//## Uses: <unnamed>%438057460261;cVarRef { -> F}
//## Uses: <unnamed>%4395DFAE0349;cEM63Session { -> F}
//## Uses: <unnamed>%43B269400227;cEM63Job { -> F}

class __DLL_EXPORT__ cEM63Parser 
{
  //## begin cEM63Parser%438055180281.initialDeclarations preserve=yes
public:
  //## end cEM63Parser%438055180281.initialDeclarations

    //## Constructors (generated)
      cEM63Parser();

      cEM63Parser(const cEM63Parser &right);

    //## Destructor (generated)
      virtual ~cEM63Parser();


    //## Other Operations (specified)
      //## Operation: ParseSessionRequest%1134738531
      virtual BOOL_T ParseSessionRequest (cEM63Session *session, CONST_STRING_T file, CONST_STRING_T source_code) = 0;

      //## Operation: ParsePresentationRequest%1134738532
      virtual BOOL_T ParsePresentationRequest (cEM63Session *session, cEM63Job *job, CONST_STRING_T file, CONST_STRING_T source_code) = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: File%43A7EE330224
      STRING_T get_File () const;

      //## Attribute: Line%43A7EE330234
      int get_Line () const;

      //## Attribute: Column%43A7EE330235
      int get_Column () const;

      //## Attribute: ErrorText%43A7EEAE0040
      STRING_T get_ErrorText () const;

  public:
    // Additional Public Declarations
      //## begin cEM63Parser%438055180281.public preserve=yes
      //## end cEM63Parser%438055180281.public

  protected:
    // Data Members for Class Attributes

      //## begin cEM63Parser::File%43A7EE330224.attr preserve=no  public: STRING_T {U} 
      STRING_T _File;
      //## end cEM63Parser::File%43A7EE330224.attr

      //## begin cEM63Parser::Line%43A7EE330234.attr preserve=no  public: int {U} -1
      int _Line;
      //## end cEM63Parser::Line%43A7EE330234.attr

      //## begin cEM63Parser::Column%43A7EE330235.attr preserve=no  public: int {U} -1
      int _Column;
      //## end cEM63Parser::Column%43A7EE330235.attr

      //## begin cEM63Parser::ErrorText%43A7EEAE0040.attr preserve=no  public: STRING_T {U} 
      STRING_T _ErrorText;
      //## end cEM63Parser::ErrorText%43A7EEAE0040.attr

    // Additional Protected Declarations
      //## begin cEM63Parser%438055180281.protected preserve=yes
      //## end cEM63Parser%438055180281.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Parser%438055180281.private preserve=yes
      //## end cEM63Parser%438055180281.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cEM63Parser%438055180281.implementation preserve=yes
      //## end cEM63Parser%438055180281.implementation

};

//## begin cEM63Parser%438055180281.postscript preserve=yes
//## end cEM63Parser%438055180281.postscript

// Class cEM63Parser 

//## begin module%438055180281.epilog preserve=yes
//## end module%438055180281.epilog


#endif
