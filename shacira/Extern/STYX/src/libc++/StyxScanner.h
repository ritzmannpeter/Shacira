/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScanner.h]      Styx Scanner Implementation (C++)                   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_SCANNER_INCL
#define STYX_SCANNER_INCL


#include <wctype.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>


/** @file
    Styx scan stream and scanner
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxStreamScanner
      Styx scan stream and scanner
  */
  //@{


  /* Scan stream ------------------------------------------------------------ */

  /** @addtogroup StyxStream
      Styx scan stream
  */
  //@{


  /** abstract scan stream */
  class CStyxStream
  {
  protected:
    string File; ///< stream identifier
    int    cEof; ///< EOF: -1 --\> binary, default=0 --\> text
  
  protected:
                    /// (report) stream error
                    /// @param Text error message
    virtual void    error(string Text);

  public:
    /// The constructor creates a base stream.
    /// @param Path stream path / identifier
    CStyxStream(string Path="");
    virtual ~CStyxStream();
  
    virtual bool    valid() = 0;   ///< stream is valid ?
                                   ///< @return true for a valid stream
    virtual bool    unicode() = 0; ///< unicode stream ?
                                   ///< @return true for an unicode stream
    virtual int     sgetc() = 0;   ///< read next character from stream
                                   ///< @return character code

    virtual bool    eof(int c);    ///< end of stream ?
                                   ///< @param c current character 
                                   ///< @return true if c \<= cEof
    virtual void    setFile(string id); 
                                   ///< set stream identifier, e.g. file name
    virtual string& getFile();     ///< get stream identifier, e.g. file name
                                   ///< @return stream identifier, e.g. file name
  };


  /* String stream declaraction ------------------------------------------- */

  /// string stream template
  template <class TC /* token character type */> 
  class TStyxStringStream : public CStyxStream
  {
  public:
    typedef basic_string<TC> tstring;

  protected:
    tstring   txt; ///< stream text
    long int  pos; ///< stream position
  
  public:
    /// The constructor creates a string stream.
    /// @param ntxt stream text
    TStyxStringStream(tstring ntxt=tstring());
    /// The constructor creates a string stream.
    /// @param ntxt stream text
    /// @param id stream path / identifier
    TStyxStringStream(tstring ntxt, string id);
    virtual ~TStyxStringStream();
  
                              /// set stream text
                              /// @param ntxt stream text
    virtual void              setText(tstring ntxt); 
                              /// get stream text
                              /// @return stream text
    virtual basic_string<TC>& getText();             

    virtual bool              valid();   // stream is valid ?
    virtual bool              unicode(); // unicode stream ?
    virtual int               sgetc();   // get next character 
  };

  typedef TStyxStringStream<char>    TStyxStringStreamS;
  typedef TStyxStringStream<wchar_t> TStyxStringStreamU;


  /* File stream declaration ---------------------------------------------- */

  /// file stream template
  template <class TC /* token character type */> 
  class TStyxFileStream : public CStyxStream
  {
  protected:
#ifdef _WIN32
    basic_ifstream<TC,char_traits<TC> > is;
#else
    basic_ifstream<TC> is; ///< input stream
#endif
  
  public:
    /// The constructor creates a file stream.
    /// @param Path stream path
    /// @param id optional stream identifier
    TStyxFileStream(string Path, string id="");
    virtual ~TStyxFileStream();

    virtual bool valid();   // stream is initialized ?
    virtual bool unicode(); // unicode stream ?
    virtual int  sgetc();   // get next character from file stream
  };

  typedef TStyxFileStream<char>    TStyxFileStreamS;
  typedef TStyxFileStream<wchar_t> TStyxFileStreamU;


  /* String stream implementation ----------------------------------------- */
  
  template <class TC>
  TStyxStringStream<TC>::TStyxStringStream(tstring ntxt)
  : CStyxStream("")
  {
    this->txt = ntxt;
    pos       = (long int)0L;
  }
  
  template <class TC>
  TStyxStringStream<TC>::TStyxStringStream(tstring ntxt, string id)
  : CStyxStream(id)
  {
    this->txt = ntxt;
    pos       = (long int)0L;
  }
  
  template <class TC>
  TStyxStringStream<TC>::~TStyxStringStream()
  {
  }
  
  template <class TC>
  bool TStyxStringStream<TC>::valid()
  {
    return true;
  }
  
  template <class TC>
  basic_string<TC>& TStyxStringStream<TC>::getText()
  {
    return txt;
  }
  
  template <class TC>
  void TStyxStringStream<TC>::setText(tstring ntxt)
  {
    this->txt = ntxt;
    pos       = (long int)0L;
  }
  
  template <class TC>
  int TStyxStringStream<TC>::sgetc()
  {
    if( pos >= (long int)txt.length() )
      return 0;
    if( sizeof(TC) == sizeof(char) )
      return (int)((txt[pos++])&0xff);
    else
      return (int)((txt[pos++])&0xffffffff);
  }
  
  template <class TC>
  bool TStyxStringStream<TC>::unicode()
  {
    return sizeof(TC) != sizeof(char);
  }
  

  /* File stream implementation ------------------------------------------- */

  template <class TC>
  TStyxFileStream<TC>::TStyxFileStream(string Path, string id)
  : CStyxStream(id.length()==0?Path:id), is(Path.c_str())
  {
    cEof = -1;
    if( Path.length() == 0 ) error("missing path");
    else
    if( !is )
    {
      error("couldn't open '" + Path + "'");
    }
  }

  template <class TC>
  TStyxFileStream<TC>::~TStyxFileStream()
  {
  }
  
  template <class TC>
  bool TStyxFileStream<TC>::valid()
  {
    return is != 0;
  }

  template <class TC>
  int TStyxFileStream<TC>::sgetc()
  { int c = cEof; TC cc;
    if( !is || !is.get(cc) ) return c;
    return (int)cc;
  }
  
  template <class TC>
  bool TStyxFileStream<TC>::unicode()
  {
    return sizeof(TC) != sizeof(char);
  }

  //@}


  /* Scanner ---------------------------------------------------------------- */

  /** @addtogroup StyxScanner
      Styx scanner
  */
  //@{


  /// stream and scanner position
  struct StyxStreamPos
  {
    typedef vector<wchar_t > V_wchar;

    CStyxStream* Stream;     ///< scan stream
    long         Line;       ///< corresponding stream line
    long         Column;     ///< corresponding stream column
    int          curChar;    ///< corresponding stream character
    V_wchar      Backbuffer; ///< corresponding backbuffer
  };

  class CStyxScanner;
  
  /// scanner
  class CStyxScanner
  {
  public:
    /** token IDs within a dyck scanner */
    enum EStyxDyckTokID
    {
      SCN_DYCKTOKEN_PREFIX  = 1, ///< dyck token prefix (left par)
      SCN_DYCKTOKEN_SUFFIX  = 2, ///< dyck token suffix (right par)
      SCN_DYCKTOKEN_PATTERN = 3  ///< dyck token body
    };
  
    /** token flags */
    enum EStyxTokFlag
    {
      SCN_FLG_IgnoreToken  = 1,  ///< token has to be ignored 
      SCN_FLG_IgnoreCase   = 2,  ///< case insensitive token
      SCN_FLG_EofToken     = 4,  ///< unsupported: eof token in embedded language
      SCN_FLG_SwitchToken  = 8,  ///< unsupported: switch to/from embedded language
      SCN_FLG_CfgToken     = 16, ///< unsupported: embedded language token
      SCN_FLG_IndentToken  = 32, ///< unsupported: (de)indent token
      SCN_FLG_PatternToken = 64, ///< (start or end) pattern token
      SCN_FLG_GroupStack   = 128 ///< push/pop token group
    };
    
    /** all UCS4 character */
    static const unsigned long SCN_CHAR_SET_SIZE = (0xFFFFFFFFu); 
  
    /** separator between token ID and pattern */
    static const char SCN_SEP_TOK_ID_PATTERN = '@';
  
  public:
    typedef set<int >                S_int;
    
  protected:
    typedef unsigned char            byte;
    typedef vector<string>           V_string;
    typedef vector<long  >           V_long;
    typedef vector<short >           V_short;
    typedef vector<byte >            V_byte;
    typedef vector<wchar_t >         V_wchar;
    typedef vector<CStyxScanner>     V_scanner;
    typedef vector<StyxStreamPos>    V_streampos;
    typedef map<short,short>         M_short;
    typedef map<long,string>         M_long2string;
    typedef map<short,CStyxScanner*> M_dscanner;
    typedef bool (CStyxScanner::* T_next)();
    
  protected:
    bool       initok;     ///< scan table import result
    string     Name;       ///< lexical language ( or group ) name
    /** @name SingleScannerAttributes 
        single scanner specification
    */
    //@{
    V_long     StaEdg;     ///< [states] --\> first edge
    V_short    StaFin;     ///< [states] --\> -1 or token index
    wstring    EdgeC ;     ///< [edges]  --\> lower character
    V_long     EdgeS ;     ///< [edges]  --\> state
    V_string   TokId ;     ///< [tokens] --\> internal token names
    V_byte     Flags ;     ///< [tokens] --\> ORed token flags
                           ///< @link #EStyxTokFlag (--\> definition) @endlink
    //@}
    /** @name GroupScannerAttributes 
        group scanner specification
    */
    //@{
    V_scanner  GrpScn;     ///< group scanners
    M_short    Switch;     ///< token --\> group
    V_short    GroupStack; ///< group control stack
    //@}
    /** @name DyckTokenAttributes 
        dyck token specification
    */
    //@{
    V_short    dyckidx;    ///< [dyck tokens] --\> token index
    V_scanner  dyckpat;    ///< [dyck tokens] --\> dyck scanner
    M_dscanner dscanner;   ///< token --\> dyck scanner
    //@}

    /** @name PatternTokenAttributes 
        pattern token specification and attributes
    */
    //@{
    short         cPatTok;  ///< current start pattern token
    short         cPatGrp;  ///< current start pattern group
    string        cPatSym;  ///< current end pattern matchcode
    M_long2string cPatMap;  ///< start pattern (group|token) --\> pattern set
    M_long2string cQPatMap; ///< quotient      (group|token) --\> pattern set/seq
    //@}

    /** current scan stream */
    CStyxStream* cStream;
    /** token and stream location */
    long         cLine, cCol, nLine, nCol;
    /** @name SymbolConstructionAttributes 
        symbol under construction
    */
    //@{
    string       buffer;     ///< buffer with scanned characters
    wstring      wbuffer;    ///< buffer with scanned unicode characters
    bool         lookahead;  ///< character look-ahead enabled ?
    V_wchar      bbuffer;    ///< look-ahead backbuffer
    int          cC;         ///< current character
    short        cTok, Group;///< current token and group
    S_int        skipC;      ///< characters to skip
    T_next       next;       ///< current token separation function
    //@}

    /** @name PreprocessingAttributes 
        preprocessing attributes
    */
    //@{
    bool         preprocess; ///< preprocessing enabled ?
    V_streampos  pstreams;   ///< stream and position stack
    //@}
    
  protected:
                 /// reset scanner (table) and stream
    virtual void reset();
                 /// delete preprocessing streams and reset main stream
    virtual void deleteStreams();
                 /// (report) scanner error
                 /// @param Text error message
    virtual void error(string Text);

    /** @name ImportScannerTable
        scanner table import and validation
    */
    //@{
                 /// set language or group name to current (group) scanner
                 /// @param Language language or group name
    virtual void setLanguage(string Language);
                 /// add token to current (group) scanner
                 /// @param Token internal token name
    virtual void addToken(string Token);
                 /// add token flags to current (group) scanner
                 /// @param Flag ORed token flags
                 /// @link #EStyxTokFlag (--\> definition) @endlink
    virtual bool addTokenFlags(byte Flag);
                 /// add the final token for a state to current (group) scanner
                 /// @param Token token index \>= 0 or -1 for a non-final state
                 /// @return true or false on error
    virtual void addFinalState(short Token);
                 /// add the first edge for a state to current (group) scanner
                 /// @param FirstEdge first edge index \>= 0
    virtual void addFirstEdge(long FirstEdge);
                 /// add the state for an edge to current (group) scanner
                 /// @param State state index \>= 0
    virtual void addEdgeState(long State);
                 /// add the unicode character for an edge to current (group) scanner
                 /// @param Character unicode character
    virtual void addEdgeChar(wchar_t Character);
                 /// add dyck token to current (group) scanner
                 /// @param Token token index \>= 0 
    virtual void addDyckToken(short Token);
                 /// add dyck scanner to current (group) scanner
                 /// @param Scanner dyck scanner
    virtual void addDyckScanner(const CStyxScanner& Scanner);
                 /// create and add a dyck scanner to current (group) scanner
    virtual void addDyckScanner();
                 /// add group scanner
                 /// @param Scanner group scanner
    virtual void addGroupScanner(const CStyxScanner& Scanner);
                 /// create and add a group scanner
    virtual void addGroupScanner();
                 /// add the follow group for a token to current group scanner
                 /// @param Token token index \>= 0 
                 /// @param Group group index \>= 0 
    virtual void addSwitchToken(short Token, short Group);

                          /// get current group scanner
                          /// @return current group scanner
    virtual CStyxScanner* currentGroupScanner();
                          /// get current dyck scanner
                          /// @return current dyck scanner
    virtual CStyxScanner* currentDyckScanner();

                 /// import next scanner table line
                 /// @param line [update] current source line
                 /// @param cScanner [changeable] current (group) scanner
                 /// @param object [result] current resource identifier
                 /// @param tokidx [update] current token index
                 /// @return true or false on error
    virtual bool loadTableLine
                 (
                   string& line, CStyxScanner*& cScanner, 
                   string& object, short& tokidx
                 );

                 /// check scanner table
                 /// @return true for a valid scanner table
    virtual bool checkLoad();
    //@}
  
    /** @name PreparePattern
        pattern and quotient token preparation
    */
    //@{
                 /// get pattern symbol from specification
                 /// @param p pattern symbol specification
                 /// @param seq sequence pattern ?
                 /// @param result [result] pattern symbol
                 /// @return true or false on error
    virtual bool initPatternSymbol(string p, bool seq, string& result);
                 /// add a quotient or pattern token to the corresponding map
                 /// @param p pattern symbol specification
                 /// @param idx combined group and token index \>= 0
                 /// @param pat pattern token ?
                 /// @return true or false on error
    virtual bool initPatternMap(string p, long idx, bool pat);
                 /// collect patterns of pattern and quotient tokens
                 /// @return true or false on error
    virtual bool initPattern();
    //@}
    
    /** @name SeparateToken
        scan process / token separation
    */
    //@{
                 /// separate next token in scan stream
                 /// (default function)
                 /// @return true or false on error
    virtual bool nextToken_default();
                 /// separate dyck token in scan stream
                 /// @return true or false on error
    virtual bool nextToken_dyck();
  
                 /// re-init current scan group
                 /// @param Group scan group index \>= 0 or -1 for the top group on stack
                 /// @param asgflg = false --\> push/pop group to/from stack
                 /// @return true or false on error
    virtual bool switchGroup(short Group, bool asgflg);
                 /// get buffer length of scanned (unicode) characters
                 /// @return buffer length
    virtual long currentLength();
                 /// init next token ( clear buffer, init position )
    virtual void beginToken();
                 /// add (unicode) character to buffer
                 /// @param c (unicode) character
    virtual void addCharacter(int c);
                 /// save current and get next valid (unicode) character
                 /// and update token position
    virtual void getCharacter();
                 /// skip non-valid (unicode) characters in current scan stream
    virtual void skipCharacter();
                 /// finalize next token
                 /// ( handle case, pattern/quotient token and preprocessing )
                 /// @return true or false on error
    virtual bool endToken();
                 /// finalize pattern token
                 /// @return true or false on error
    virtual bool endPattern();
                 /// finalize quotient token
                 /// @return true or false on error
    virtual bool endQuotient();
                 /// save quotient to backbuffer
                 /// @param cBackLen quotient length
    virtual void backbufQuotient(long cBackLen);
                 /// save look-ahead to backbuffer and update stream position
                 /// @param cBackLen look-ahead length
                 /// @param nBackLin stream line
                 /// @param nBackCol stream column
    virtual void backbufLookahead
                 (
                   long cBackLen, long nBackLin, long nBackCol
                 );
    //@}

                 //@{
                 /// preprocess handler if preprocessing is enabled 
                 /// @param PStream [changeable] current scan stream
                 /// \n = initial value --\> update value of current token
                 /// \n = 0             --\> ignore current token
                 /// \n else            --\> rescan new allocated stream,
                 /// \n                      afterwards deleted by the scanner
                 /// @param Token internal name of current token
                 /// @param Value [changeable] value of current token
                 /// @return true or false on error
    virtual bool preprocessToken
                 (
                   CStyxStream*& PStream, const string& Token, string& Value
                 );
    virtual bool preprocessToken
                 (
                   CStyxStream*& PStream, const string& Token, wstring& Value
                 );
                 //@}
  
  public:
    /// The constructor creates an uninitialized scanner.
    /// @param lahead enable n character look-ahead ?
    /// @param process enable preprocessing ?
    CStyxScanner(bool lahead = false, bool process = false);
    virtual ~CStyxScanner();

                         /// scanner and stream are initialized ?
                         /// @return true for an initialized scanner and stream
    virtual bool         initialized();

                         /// n character look-ahead enabled ?
                         /// @return true if n character look-ahead is enabled
    virtual bool         LookaheadEnabled();

                         /// preprocessing enabled ?
                         /// @return true if preprocessing is enabled
    virtual bool         PreprocessEnabled();
  
                         /// get language
                         /// @return language name or ""
    virtual string       getLanguage();
                         /// get number of scan groups
                         /// @return number of scan groups or -1
    virtual short        getGroups();
                         /// get scan group name
                         /// @param GrpIdx scan group index \>= 0
                         /// @return scan group name or ""
    virtual string       getGroupID(short GrpIdx);
                         /// get number of tokens [ in scan group ]
                         /// @param GrpIdx optional scan group index \>= 0
                         /// @return number of tokens [ in scan group ] or -1
    virtual short        getTokens(short GrpIdx=-1);
                         /// get internal token name [ in scan group ]
                         /// @param TokIdx token index \>= 0
                         /// @param GrpIdx optional scan group index \>= 0
                         /// @return internal token name [ in scan group ] or ""
    virtual string       getTokenID(short TokIdx, short GrpIdx=-1);
  
                         /// import scanner table from file 
                         /// @param Path path to the exported scanner table 
                         /// @return true --> initialized scanner or false on error
    virtual bool         loadTableFile(string Path);
                         /// import scanner table from string
                         /// @param Table exported scanner table 
                         /// @return true --> initialized scanner or false on error
    virtual bool         loadTableString(string Table);

                         /// initialize scan process 
                         /// @param Stream scan stream
                         /// @param SkipCharacters skip characters in stream
                         /// @return true or false on error
    virtual bool         scanStream(CStyxStream* Stream, const S_int& SkipCharacters);
                         /// separate next token in scan stream
                         /// @return true or false on error
    virtual bool         nextToken();
                         /// end of scan stream ?
                         /// @return true on end of scan stream
    virtual bool         eos();
                         /// unicode scan stream ?
                         /// @return true for an unicode scan stream
    virtual bool         unicode();
                         /// get (current) scan stream
                         /// @return (current) scan stream or NULL
    virtual const CStyxStream* getStream(); 

                         //@{
                         /// get current token identifier and value
                         /// @param Token [result] internal token name
                         /// @param Value [result] token value
                         /// @return true or false on error
    virtual bool         currentToken(string& Token, string& Value);
    virtual bool         currentToken(string& Token, wstring& Value);
                         //@}
                         /// get external token name
                         /// @param Token internal token name
                         /// @return external token name
    virtual string       externalTokenID(const string& Token);
                         /// current token is not case sensitive ?
                         /// @return true for a case insensitive token
    virtual bool         ignoreCase();

    /** @name CurrentTokenPosition
        current token position
    */
    //@{
                         /// get stream line of current token
    virtual long         getLine(); 
                         /// get stream column of current token
    virtual long         getCol(); 
                         /// get stream identifier
    virtual string       getFile(); 
    //@}
  };

  /* Scanner with standard Styx compliant preprocessing facility ------------ */

  /// scanner with standard Styx compliant preprocessing facility
  class CStyxPScanner : public CStyxScanner
  {
  public:
    /// preprocessing parameter type: index --\> value
    typedef map<short,string>   M_pardfn; 

    /** Indexes of the default macro token identifiers, macro keywords 
        as well as the default include path and characterset
    */
    enum EStyxParIndex
    {
      IDX_TOK_IDE    = 0,  ///< token identifier
      IDX_MAC_DFN    = 1,  ///< token define macro 
      IDX_MAC_SEP    = 2,  ///< token parameter separator (in macro calls)
      IDX_MAC_INC    = 3,  ///< token include
      IDX_MAC_COND   = 4,  ///< token condition
      IDX_MAC_DEL    = 5,  ///< token undefine macro
      IDX_KEY_START  = 6,  ///< initial keyword define macro
      IDX_KEY_END    = 7,  ///< final keyword define macro, condition
      IDX_KEY_IFDEF  = 8,  ///< initial keyword ifdef condition
      IDX_KEY_IFNDEF = 9,  ///< initial keyword ifndef condition
      IDX_KEY_ELSE   = 10, ///< initial keyword else condition
      IDX_KEY_INC    = 11, ///< initial keyword include
      IDX_KEY_UNDEF  = 12, ///< initial keyword undefine macro
      IDX_INC_PATH   = 13, ///< include path
      IDX_INC_CSET   = 14, ///< include characterset
      IDX_PAR_END          ///< end of parameter indexes
    };

  protected:
    typedef vector<bool>           V_bool;

    /// macro definition type: id --\> { formal parameter } text
    typedef map<string,V_string>   M_macdfn; 
    /// macro callstack type: { id { actual parameter } }
    typedef vector<V_string>       V_macexp; 

  protected:
    M_pardfn Parameters; ///< preprocessing parameters
                         ///< @link #EStyxParIndex index @endlink --\> value 
    M_macdfn MacDefines; ///< macro definitions
    V_macexp MacStack;   ///< macro expressions / callstack
    V_bool   CondStack;  ///< condition stack
    int      CurSep;     ///< current parameter separator (in macro calls)
    string   CurPar;     ///< current macro parameter under construction or ""
    bool     MacIgnCase; ///< ignore case in macro identifiers ?
                         ///< ( must be true or match the case specification of the identifier token )

  protected:
                        /// make full path name
                        /// @param dir directory path
                        /// @param file file name
                        /// @param sep path separator
                        /// @return the full path or file name
  virtual               string makePath
                        (
                          const string& dir, const string& file, string sep
                        );
                        /// set substream identifier relative to main stream position
                        /// @param PStream the new substream
   virtual void         setStreamID(CStyxStream* PStream);
                        /// create a new string stream for the evaluated macro
                        /// and set substream identifier relative to main stream position
                        /// @param id macro identifier
                        /// @param Text evaluated macro text
                        /// @return the allocated string stream or 0 on error
   virtual CStyxStream* createMacroStream(const string& id, const string& Text);
                        /// create a new file stream and set substream identifier 
                        /// relative to main stream position
                        /// @param Path stream path
                        /// @return the allocated file stream or 0 on error
   virtual CStyxStream* createFileStream(const string& Path);
                        /// eval include directive
                        /// @param Value include directive
                        /// @return the allocated file stream or 0 on error
   virtual CStyxStream* evalInclude(const string& Value);

                        /// set parameter separator (in macro calls)
                        /// @param Value parameter separator
   virtual void         setSeparator(const string& Value);
                        /// part of an explicit separated parameter ?
                        /// @param Value token value
                        /// @return true for a partial parameter
   virtual bool         partialParameter(const string& Value);

                        /// apply macro
                        /// @param Definition macro definition (formal parameters, text)
                        /// @param Parameters macro call (actual parameters, id)
                        /// @return the evaluated macro text
   virtual string       applyMacro
                        (
                          const V_string& Definition, const V_string& Parameters
                        );
                        /// eval macro parameter
                        /// @param Value macro parameter
                        /// @param id [result] identifier of the evaluated macro
                        /// @return the evaluated macro text or ""
   virtual string       evalMacroParameter(const string& Value, string& id);
                        /// eval macro call
                        /// @param Value macro name
                        /// @param id [result] identifier of the evaluated macro
                        /// @return the evaluated macro text or ""
   virtual string       evalMacroCall(const string& Value, string& id);

                        /// eval undefine macro
                        /// @param Value undefine macro
                        /// @return true or false on error
   virtual bool         evalUndefine(const string& Value);
                        /// eval define macro
                        /// @param Value define macro
                        /// @return true or false on error
   virtual bool         evalDefine(const string& Value);

                        /// eval if[n]def condition
                        /// @param Value if[n]def condition
                        /// @return true --\> scan the if[n]def branch
   virtual bool         evalCondition(const string& Value);
                        /// preprocess condition macro
                        /// @param PStream [update] current scan stream
                        /// (set to 0 --\> ignore current token)
                        /// @param Token internal name of current token
                        /// @param Value value of current token
                        /// @return true or false on error
   virtual bool         preprocessCondition
                        (
                          CStyxStream*& PStream, 
                          const string& Token, const string& Value
                        );

                        //@{
                        /// standard Styx compliant preprocess handler
                        /// @param PStream [changeable] current scan stream
                        /// \n = initial value --\> update value of current token
                        /// \n = 0             --\> ignore current token
                        /// \n else            --\> rescan new allocated stream,
                        /// \n                      afterwards deleted by the scanner
                        /// @param Token internal name of current token
                        /// @param Value [changeable] value of current token
                        /// @return true or false on error
    virtual bool        preprocessToken
                        (
                          CStyxStream*& PStream, const string& Token, string& Value
                        );
    virtual bool        preprocessToken
                        (
                          CStyxStream*& PStream, const string& Token, wstring& Value
                        );
                        //@}

  public:
    /// The constructor creates an uninitialized scanner.
    /// @param lahead enable n character look-ahead ?
    /// @param igncase ignore case in macro identifiers
    CStyxPScanner(bool lahead = false, bool igncase = true);
    virtual ~CStyxPScanner();

                        /// set preprocessing parameters
                        /// @param parmap preprocessing parameters
    virtual void        setParameters(const M_pardfn& parmap);

                        /// get preprocessing parameter
                        /// @param paridx parameter index
                        /// @return parameter value or ""
    virtual string      getParameter(short paridx);
  };

  //@}
  
  //@}

  //@}

}

#endif
