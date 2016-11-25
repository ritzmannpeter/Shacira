//## begin module%3A55D27901F5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A55D27901F5.cm

//## begin module%3A55D27901F5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A55D27901F5.cp

//## Module: cTokenizer%3A55D27901F5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cTokenizer.h

#ifndef cTokenizer_h
#define cTokenizer_h 1

//## begin module%3A55D27901F5.includes preserve=yes
//## end module%3A55D27901F5.includes

//## begin module%3A55D27901F5.additionalDeclarations preserve=yes
//## end module%3A55D27901F5.additionalDeclarations


//## begin cTokenizer%3A55D27901F5.preface preserve=yes
//## end cTokenizer%3A55D27901F5.preface

//## Class: cTokenizer%3A55D27901F5
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cTokenizer 
{
  //## begin cTokenizer%3A55D27901F5.initialDeclarations preserve=yes
public:
  //## end cTokenizer%3A55D27901F5.initialDeclarations

    //## Constructors (generated)
      cTokenizer();

      cTokenizer(const cTokenizer &right);

    //## Constructors (specified)
      //## Operation: cTokenizer%978694295
      cTokenizer (CONST_STRING_T buf, ULONG_T bufsize);

    //## Destructor (generated)
      virtual ~cTokenizer();


    //## Other Operations (specified)
      //## Operation: Reset%1002702339
      void Reset ();

      //## Operation: GetToken%978694296
      virtual CONST_STRING_T GetToken ();

      //## Operation: GetToken%978694297
      virtual CONST_STRING_T GetToken (CONST_STRING_T whitespace);

  public:
    // Additional Public Declarations
      //## begin cTokenizer%3A55D27901F5.public preserve=yes
      //## end cTokenizer%3A55D27901F5.public

  protected:
    // Additional Protected Declarations
      //## begin cTokenizer%3A55D27901F5.protected preserve=yes
      //## end cTokenizer%3A55D27901F5.protected

  private:
    // Additional Private Declarations
      //## begin cTokenizer%3A55D27901F5.private preserve=yes
      //## end cTokenizer%3A55D27901F5.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: IsWhiteSpace%978694298
      BOOL_T IsWhiteSpace (INT_T c, CONST_STRING_T whitespace);

    // Data Members for Class Attributes

      //## Attribute: Token%3A55D2B202F1
      //## begin cTokenizer::Token%3A55D2B202F1.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Token;
      //## end cTokenizer::Token%3A55D2B202F1.attr

      //## Attribute: Buf%3A55D2B202FB
      //## begin cTokenizer::Buf%3A55D2B202FB.attr preserve=no  implementation: CONST_STRING_T {U} NULL
      CONST_STRING_T _Buf;
      //## end cTokenizer::Buf%3A55D2B202FB.attr

      //## Attribute: BufSize%3A55D2B202FC
      //## begin cTokenizer::BufSize%3A55D2B202FC.attr preserve=no  implementation: UINT_T {U} 0
      UINT_T _BufSize;
      //## end cTokenizer::BufSize%3A55D2B202FC.attr

      //## Attribute: BufPos%3A55D2B202FD
      //## begin cTokenizer::BufPos%3A55D2B202FD.attr preserve=no  implementation: UINT_T {U} 0
      UINT_T _BufPos;
      //## end cTokenizer::BufPos%3A55D2B202FD.attr

    // Additional Implementation Declarations
      //## begin cTokenizer%3A55D27901F5.implementation preserve=yes
      //## end cTokenizer%3A55D27901F5.implementation

};

//## begin cTokenizer%3A55D27901F5.postscript preserve=yes
//## end cTokenizer%3A55D27901F5.postscript

// Class cTokenizer 

//## begin module%3A55D27901F5.epilog preserve=yes
//## end module%3A55D27901F5.epilog


#endif
