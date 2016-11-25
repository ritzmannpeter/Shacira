//## begin module%3B8A254C02DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A254C02DA.cm

//## begin module%3B8A254C02DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A254C02DA.cp

//## Module: cStringUtils%3B8A254C02DA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cStringUtils.h

#ifndef cStringUtils_h
#define cStringUtils_h 1

//## begin module%3B8A254C02DA.includes preserve=yes
//## end module%3B8A254C02DA.includes

//## begin module%3B8A254C02DA.additionalDeclarations preserve=yes
//## end module%3B8A254C02DA.additionalDeclarations


//## begin cStringUtils%3B8A254C02DA.preface preserve=yes
//## end cStringUtils%3B8A254C02DA.preface

//## Class: cStringUtils%3B8A254C02DA
//	This class offers some methods to manipulate strings and
//	wrapper methods for some STL-string methods.
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cStringUtils 
{
  //## begin cStringUtils%3B8A254C02DA.initialDeclarations preserve=yes
public:
  //## end cStringUtils%3B8A254C02DA.initialDeclarations

    //## Constructors (generated)
      cStringUtils();

      cStringUtils(const cStringUtils &right);

    //## Destructor (generated)
      virtual ~cStringUtils();


    //## Other Operations (specified)
      //## Operation: Trim%998934605
      //	Trim removes leading spaces and spaces at the end of a
      //	string represented by the argument str. A new string
      //	will be returned as result.
      static STRING_T Trim (CONST_STRING_T str, CHAR_T trim_char = ' ');

      //## Operation: Trim%998934606
      //	Trim removes leading spaces and spaces at the end of a
      //	string represented by the argument str. A new string
      //	will be returned as result.
      static CONST_STRING_T Trim (CONST_STRING_T str, CHAR_T *buf, UINT_T buf_size, CHAR_T trim_char = ' ');

      //## Operation: LTrim%998912330
      //	Trim removes leading spaces of a string represented by
      //	the argument str. A new string will be returned as
      //	result.
      static STRING_T LTrim (CONST_STRING_T str, CHAR_T trim_char = ' ');

      //## Operation: RTrim%998912331
      //	Trim removes spaces at the end of a string represented
      //	by the argument str. A new string will be returned as
      //	result.
      static STRING_T RTrim (CONST_STRING_T str, CHAR_T trim_char = ' ');

      //## Operation: Find%1001511106
      //	Finds the first occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T Find (STRING_T &str, CONST_STRING_T sub_str);

      //## Operation: Find%1001511107
      //	Finds the first occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T Find (CONST_STRING_T str, CONST_STRING_T sub_str);

      //## Operation: FindFirstOf%998912332
      //	Finds the first occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T FindFirstOf (STRING_T &str, CONST_STRING_T sub_str);

      //## Operation: FindFirstOf%998912333
      //	Finds the first occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T FindFirstOf (CONST_STRING_T str, CONST_STRING_T sub_str);

      //## Operation: FindLastOf%998912334
      //	Finds the last occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T FindLastOf (STRING_T &str, CONST_STRING_T sub_str);

      //## Operation: FindLastOf%998912335
      //	Finds the last occurence of substring sub_str in string
      //	str and returns the position of this substring. If the
      //	substring cannot be found the method return -1
      static INT_T FindLastOf (CONST_STRING_T str, CONST_STRING_T sub_str);

      //## Operation: Left%998912336
      //	Returns the first len characters of str.
      static STRING_T Left (STRING_T &str, UINT_T len);

      //## Operation: Left%998912337
      //	Returns the first len characters of str.
      static STRING_T Left (CONST_STRING_T str, UINT_T len);

      //## Operation: Right%998912338
      //	Returns the last len characters of str.
      static STRING_T Right (STRING_T &str, UINT_T len);

      //## Operation: Right%998912339
      //	Returns the last len characters of str.
      static STRING_T Right (CONST_STRING_T str, UINT_T len);

      //## Operation: Replace%998912354
      //	Replaces all occurences of substring sub_str by
      //	substring rep_str.
      static STRING_T Replace (STRING_T &str, CONST_STRING_T sub_str, CONST_STRING_T rep_str);

      //## Operation: LeftSplit%1082991646
      static void LeftSplit (CONST_STRING_T str, STRING_T &head, STRING_T &tail, CHAR_T separator);

      //## Operation: GetStringSequence%1108111661
      static void GetStringSequence (CONST_STRING_T str, STRING_T &sequence, int &nchars, CHAR_T separator = '"');

  public:
    // Additional Public Declarations
      //## begin cStringUtils%3B8A254C02DA.public preserve=yes
      //## end cStringUtils%3B8A254C02DA.public

  protected:
    // Additional Protected Declarations
      //## begin cStringUtils%3B8A254C02DA.protected preserve=yes
      //## end cStringUtils%3B8A254C02DA.protected

  private:
    // Additional Private Declarations
      //## begin cStringUtils%3B8A254C02DA.private preserve=yes
      //## end cStringUtils%3B8A254C02DA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cStringUtils%3B8A254C02DA.implementation preserve=yes
      //## end cStringUtils%3B8A254C02DA.implementation

};

//## begin cStringUtils%3B8A254C02DA.postscript preserve=yes
//## end cStringUtils%3B8A254C02DA.postscript

// Class cStringUtils 

//## begin module%3B8A254C02DA.epilog preserve=yes
//## end module%3B8A254C02DA.epilog


#endif
