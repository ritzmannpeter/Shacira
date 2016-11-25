/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScanner.cs]     Styx Scanner Implementation (C#)                    */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2008 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

using System;
using System.Text;
using System.IO;
using System.Collections;


/** @file
    Styx scan stream and scanner
*/


namespace styx
{

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
  public abstract class CStyxStream
  {  
    //! (report) stream error
    //! @param Text error message
    protected virtual void error(string Text)
    {
      Console.Error.WriteLine(Text);
    }

    public abstract bool valid(); //!< stream is valid ?
                                  //!< @return true for a valid stream

    public abstract int  sgetc(); //!< read next character from stream
                                  //!< @return character code

    public virtual bool eof(int c) //!< end of stream ?
    {                              //!< @param c current character 
      return c <= cEof;            //!< @return true if c \<= cEof
    }

    public virtual string getFile() //!< get stream identifier
    {                               //!< @return stream identifier
      return File;
    }
  
    //! set stream identifier
    //! @param id stream identifier
    public virtual void setFile(string id)
    {
      File = id;
    }

    protected string File; //!< stream identifier

    protected int cEof; //!< EOF: -1 --\> binary, default=0 --\> text

    public CStyxStream()
    {
      cEof = 0;
      File = "";
    }
  }


  /* String stream -------------------------------------------------------- */

  //! string stream 
  public class CStyxStringStream : CStyxStream
  {
    protected string txt; //!< stream text
    protected long   pos; //!< stream position
  
    //! The constructor creates a string stream.
    //! @param ntxt stream text
    public CStyxStringStream(string ntxt) : base()
    {
      this.cEof = 0;
      txt = ntxt;
      pos = (long)0;
    }

    //! The constructor creates a string stream.
    //! @param ntxt stream text
    //! @param id stream path / identifier
    public CStyxStringStream(string ntxt, string id) : base()
    {
      txt = ntxt;
      pos = (long)0;
    }
  
                          //! set stream text
                          //! @param ntxt stream text
    public virtual void   setText(string ntxt)
    {
      txt = ntxt;
      pos = (long)0;
    }

                          //! get stream text
                          //! @return stream text
    public virtual string getText()
    {
      return txt;
    }

    public override bool   valid()   // stream is valid ?
    {
      return true;
    }

    public override int    sgetc()   // get next character 
    {
      if( pos >= (long)txt.Length )
        return 0;
      return (int)((txt[(int)pos++])&0xffff);
    }
  }


  /* File stream ---------------------------------------------------------- */

  //! file stream template
  public class CStyxFileStream : CStyxStream
  {
    protected StreamReader reader;

    //! The constructor creates a file stream.
    //! @param Path stream path
    //! @param id optional stream identifier
    public CStyxFileStream(string Path, string id) : base()
    {
      this.cEof = -1;
      if( id.Length > 0 ) this.File = id;
      else this.File = Path;
      try
      {
        reader = new StreamReader(Path);
      }
      catch(Exception e)
      {
        error("couldn't open '" + Path + "'" + Environment.NewLine + e.ToString());
      }
    }

    //! The constructor creates a file stream according the given encoding.
    //! @param Path stream path
    //! @param id optional stream identifier
    public CStyxFileStream(string Path, string id, Encoding code) : base()
    {
      this.cEof = -1;
      if( id.Length > 0 ) this.File = id;
      else this.File = Path;
      try
      {
        reader = new StreamReader(Path,code);
      }
      catch(Exception e)
      {
        error("couldn't open '" + Path + "'" + Environment.NewLine + e.ToString());
      }
    }

    ~CStyxFileStream()
    {
      if( reader != null ) reader.Close();
    }

    public override bool valid()   // stream is initialized ?
    {
      return reader != null;
    }

    public override int  sgetc()   // get next character from file stream
    {
      try
      {
        return ( reader == null ) ? -1 : reader.Read();
      }
      catch(Exception e)
      {
        error("read character failed" + Environment.NewLine + e.ToString());
        return -1;
      }
    }
  }

  //@}


  /* Scanner ---------------------------------------------------------------- */

  /** @addtogroup StyxScanner
      Styx scanner
  */
  //@{


  //! stream and scanner position
  public struct StyxStreamPos
  {
    public CStyxStream Stream;     //!< scan stream
    public long        Line;       //!< corresponding stream line
    public long        Column;     //!< corresponding stream column
    public int         curChar;    //!< corresponding stream character
    public ArrayList   Backbuffer; //!< corresponding backbuffer (int)
  }

  //! scanner
  public class CStyxScanner
  {
    protected static short i32HighValue(int v)
    {
      return (short)(((int)(v)) >> 16);
    }

    protected static short i32LowValue(int v)
    {
      return (short)(((int)(v)) & 0xFFFFL);
    }

    protected static int i32Value(short h, short l)
    {
      return   
          (int)((((int)(h)) << 16) & 0xFFFF0000L) 
        | (int)(((int)(l)) & ((int)0x0000FFFFL));
    }
    
    /** token IDs within a dyck scanner */
    public enum EStyxDyckTokID
    {
      SCN_DYCKTOKEN_PREFIX  = 1, //!< dyck token prefix (left par)
      SCN_DYCKTOKEN_SUFFIX  = 2, //!< dyck token suffix (right par)
      SCN_DYCKTOKEN_PATTERN = 3  //!< dyck token body
    }
  
    /** token flags */
    public enum EStyxTokFlag
    {
      SCN_FLG_IgnoreToken  = 1,  //!< token has to be ignored 
      SCN_FLG_IgnoreCase   = 2,  //!< case insensitive token
      SCN_FLG_EofToken     = 4,  //!< unsupported: eof token in embedded language
      SCN_FLG_SwitchToken  = 8,  //!< unsupported: switch to/from embedded language
      SCN_FLG_CfgToken     = 16, //!< unsupported: embedded language token
      SCN_FLG_IndentToken  = 32, //!< unsupported: (de)indent token
      SCN_FLG_PatternToken = 64, //!< (start or end) pattern token
      SCN_FLG_GroupStack   = 128 //!< push/pop token group
    }
    
    /** all UCS4 character */
    public static uint SCN_CHAR_SET_SIZE
    { 
      get { return (0xFFFFFFFFu); } 
    }
  
    /** separator between token ID and pattern */
    public static char SCN_SEP_TOK_ID_PATTERN 
    {
      get { return '@'; }
    }
  
    protected delegate bool T_next();
    
    protected bool       initok;     //!< scan table import result
    protected string     Name;       //!< lexical language ( or group ) name
    /** @name SingleScannerAttributes 
        single scanner specification
    */
    //@{
    protected ArrayList  StaEdg;     //!< [states] --\> first edge (int)
    protected ArrayList  StaFin;     //!< [states] --\> -1 or token index (short)
    protected ArrayList  EdgeC ;     //!< [edges]  --\> lower character (uint[])
    protected ArrayList  EdgeS ;     //!< [edges]  --\> state (int)
    protected ArrayList  TokId ;     //!< [tokens] --\> internal token names (string)
    protected ArrayList  Flags ;     //!< [tokens] --\> ORed token flags (byte)
                                     //!< @link #EStyxTokFlag (--\> definition) @endlink
    //@}
    /** @name GroupScannerAttributes 
        group scanner specification
    */
    //@{
    protected ArrayList  GrpScn;     //!< group scanners (CStyxScanner)
    protected Hashtable  Switch;     //!< token --\> group (short,short)
    protected ArrayList  GroupStack; //!< group control stack (short)
    //@}
    /** @name DyckTokenAttributes 
        dyck token specification
    */
    //@{
    protected ArrayList  dyckidx;    //!< [dyck tokens] --\> token index (short)
    protected ArrayList  dyckpat;    //!< [dyck tokens] --\> dyck scanner (CStyxScanner)
    protected Hashtable  dscanner;   //!< token --\> dyck scanner (short,CStyxScanner)
    //@}

    /** @name PatternTokenAttributes 
        pattern token specification and attributes
    */
    //@{
    protected short      cPatTok;  //!< current start pattern token
    protected short      cPatGrp;  //!< current start pattern group
    protected string     cPatSym;  //!< current end pattern matchcode
    protected Hashtable  cPatMap;  //!< start pattern (group|token) --\> pattern set (long,string)
    protected Hashtable  cQPatMap; //!< quotient      (group|token) --\> pattern set/seq (long,string)
    //@}

    /** current scan stream */
    protected CStyxStream cStream;
    /** token and stream location */
    protected long        cLine, cCol, nLine, nCol;
    /** @name SymbolConstructionAttributes 
        symbol under construction
    */
    //@{
    protected string      buffer;      //!< buffer with scanned unicode characters
    protected bool        lookahead;   //!< character look-ahead enabled ?
    protected ArrayList   bbuffer;     //!< look-ahead backbuffer (char,besser:uint?)
    protected int         cC;          //!< current character
    protected short       cTok, Group; //!< current token and group
    protected Hashtable   skipC;       //!< characters to skip (uint,null)
    protected T_next      next;        //!< current token separation function
    //@}

    /** @name PreprocessingAttributes 
        preprocessing attributes
    */
    //@{
    protected bool         preprocess; //!< preprocessing enabled ?
    protected ArrayList    pstreams;   //!< stream and position stack (StyxStreamPos)
    //@}

    //! reset scanner (table) and stream
    protected virtual void reset()
    {
      initok  = false;
      Name    = "";
      if( pstreams == null ) pstreams = new ArrayList();
      deleteStreams();
      cC      = cTok = Group = -1;
      cLine   = cCol = nLine = nCol = 1;
      next    = new T_next(this.nextToken_default);
      cPatTok = cPatGrp = -1;
      StaEdg = new ArrayList();
      StaFin = new ArrayList();
      EdgeC = new ArrayList();
      EdgeS = new ArrayList();
      TokId = new ArrayList();
      Flags = new ArrayList();
      GrpScn = new ArrayList();
      Switch = new Hashtable();
      GroupStack = new ArrayList();
      dyckidx = new ArrayList();
      dyckpat = new ArrayList();
      dscanner = new Hashtable();
      cPatMap = new Hashtable();
      cQPatMap = new Hashtable();
      bbuffer = new ArrayList();
      skipC = new Hashtable();
      buffer = "";
    }
    //! delete preprocessing streams and reset main stream
    protected virtual void deleteStreams()
    {
      pstreams.Clear();
      cStream = null;
    }
    //! (report) scanner error
    //! @param Text error message
    protected virtual void error(string Text)
    {
      Console.Error.WriteLine(Text);
    }

    /** @name ImportScannerTable
        scanner table import and validation
    */
    //@{
    //! set language or group name to current (group) scanner
    //! @param Language language or group name
    protected virtual void setLanguage(string Language)
    {
      Name = Language;
    }

    //! add token to current (group) scanner
    //! @param Token internal token name
    protected virtual void addToken(string Token)
    {
      TokId.Add(Token);
    }

    //! add token flags to current (group) scanner
    //! @param Flag ORed token flags
    //! @link #EStyxTokFlag (--\> definition) @endlink
    protected virtual bool addTokenFlags(byte Flag)
    {
      Flags.Add(Flag);
      bool result = (Flag&(byte)EStyxTokFlag.SCN_FLG_IndentToken) == 0 &&
                    (Flag&(byte)EStyxTokFlag.SCN_FLG_CfgToken)    == 0 &&
                    (Flag&(byte)EStyxTokFlag.SCN_FLG_EofToken)    == 0 &&
                    (Flag&(byte)EStyxTokFlag.SCN_FLG_SwitchToken) == 0;
      if( !result )
        error("unsupported token flags");
      return result;
    }

    //! add the final token for a state to current (group) scanner
    //! @param Token token index \>= 0 or -1 for a non-final state
    //! @return true or false on error
    protected virtual void addFinalState(short Token)
    {
      StaFin.Add(Token);
    }

    //! add the first edge for a state to current (group) scanner
    //! @param FirstEdge first edge index \>= 0
    protected virtual void addFirstEdge(long FirstEdge)
    {
      StaEdg.Add(FirstEdge);
    }

    //! add the state for an edge to current (group) scanner
    //! @param State state index \>= 0
    protected virtual void addEdgeState(long State)
    {
      EdgeS.Add(State);
    }

    //! add the unicode character for an edge to current (group) scanner
    //! @param Character unicode character
    protected virtual void addEdgeChar(uint Character)
    {
      EdgeC.Add(Character);
    }

    //! add dyck token to current (group) scanner
    //! @param Token token index \>= 0 
    protected virtual void addDyckToken(short Token)
    {
      dyckidx.Add(Token);
    }

    //! add dyck scanner to current (group) scanner
    //! @param Scanner dyck scanner
    protected virtual void addDyckScanner(ref CStyxScanner Scanner)
    {
      dyckpat.Add(Scanner);
    }

    //! create and add a dyck scanner to current (group) scanner
    protected virtual void addDyckScanner()
    {
      dyckpat.Add(new CStyxScanner());
    }

    //! add group scanner
    //! @param Scanner group scanner
    protected virtual void addGroupScanner(ref CStyxScanner Scanner)
    {
      GrpScn.Add(Scanner);
    }

    //! create and add a group scanner
    protected virtual void addGroupScanner()
    {
      GrpScn.Add(new CStyxScanner());
    }

    //! add the follow group for a token to current group scanner
    //! @param Token token index \>= 0 
    //! @param Group group index \>= 0 
    protected virtual void addSwitchToken(short Token, short Group)
    {
      Switch[Token] = Group;
    }

    //! get current group scanner
    //! @param cScanner [result] current group scanner
    protected virtual void currentGroupScanner(ref CStyxScanner cScanner)
    {
      if( GrpScn.Count > 0 )
      {
        cScanner = (CStyxScanner)GrpScn[GrpScn.Count-1];
      }
      else
      {
        cScanner = this;
      }
    }

    //! get current dyck scanner
    //! @param cScanner [result] current dyck scanner
    protected virtual void currentDyckScanner(ref CStyxScanner cScanner)
    {
      CStyxScanner curgrp = null;
      currentGroupScanner(ref curgrp);
      if( curgrp.dyckpat.Count > 0 )
      {
        cScanner = (CStyxScanner)curgrp.dyckpat[curgrp.dyckpat.Count-1];
      }
      else
      {
        cScanner = null;
      }
    }

    //! import next scanner table line
    //! @param line [update] current source line
    //! @param cScanner [changeable] current (group) scanner
    //! @param Object [result] current resource identifier
    //! @param tokidx [update] current token index
    //! @return true or false on error
    protected virtual bool loadTableLine
                           (
                             ref string line, ref CStyxScanner cScanner, 
                             ref string Object, ref short tokidx
                           )
    {
      if( line.Length > 0 && line[0] != '#' )
      { 
        int pos = line.IndexOf("Name=");
        if( pos >= 0 && pos < line.Length )
        {
          cScanner.setLanguage(line.Substring(pos+5));
        }
        else
        if( line == "Group" )
        {
          addGroupScanner();
          currentGroupScanner(ref cScanner);
        }
        else
        if( line == "Dyck" )
        {
          cScanner.addDyckScanner();
          currentDyckScanner(ref cScanner);
        }
        else
        if( line == "Language" )
        {
          cScanner = this;
        }
        else
        if( line[0] != '-' && !Char.IsDigit(line[0]) && !Char.IsWhiteSpace(line[0]) )
        {
          Object = line;
          tokidx = 0;
        }
        else
        if( Char.IsWhiteSpace(line[0]) )
        {
          cScanner.addToken(line.Substring(1));
        }
        else
        if( line[0] == '-' || Char.IsDigit(line[0]) )
        { 
          long v = System.Convert.ToInt64(line);
          if( Object == "StaEdg" )
          {
            cScanner.addFirstEdge((long)v);
          }
          else
          if( Object == "StaFin" )
          {
            cScanner.addFinalState((short)v);
          }
          else
          if( Object == "EdgeC" )
          {
            cScanner.addEdgeChar((uint)v);
          }
          else
          if( Object == "EdgeS" )
          {
            cScanner.addEdgeState((long)v);
          }
          else
          if( Object == "Flags" )
          {
            if( !cScanner.addTokenFlags((byte)v) )
            {
              return false;
            }
          }
          else
          if( Object == "Switch" )
          {
            cScanner.addSwitchToken(tokidx,(short)v);
            tokidx++;
          }
          else
          if( Object == "DyckToken" )
          {
            currentGroupScanner(ref cScanner);
            cScanner.addDyckToken((short)v);
          }
        }
      }
      line = "";
      return true;
    }

    //! check scanner table
    //! @return true for a valid scanner table
    protected virtual bool checkLoad()
    {
      bool result = GrpScn.Count > 0 ||
                    StaFin.Count > 0 && StaEdg.Count > 0 && 
                    EdgeS.Count > 0 && EdgeC.Count > 0 &&
                    TokId.Count > 0 && TokId.Count == Flags.Count;
      if( !result ) error("invalid scanner table format");
      return result;
    }
    //@}
  
    /** @name PreparePattern
        pattern and quotient token preparation
    */
    //@{
    //! get pattern symbol from specification
    //! @param p pattern symbol specification
    //! @param seq sequence pattern ?
    //! @param result [result] pattern symbol
    //! @return true or false on error
    protected virtual bool initPatternSymbol(string p, bool seq, ref string result)
    {
      int len = p.Length;
      result = "";
      if( len > 0 && len % 3 != 0 )
      {
        error("invalid start pattern or quotient token ID");
        return false;
      }
      for( int i=0; i < len; i+=3 )
      { 
        char[] buf = new char[4]; int c1, c2;
        buf[0] = p[i];
        buf[1] = p[i+1];
        buf[2] = p[i+2];
        buf[3] = '\0';
        c1 = System.Convert.ToInt32(buf);
        if( i == 0 )
        {
          if( seq )
          {
            if( ((char)c1) != '"' && ((char)c1) != '\'' )
            {
              error("invalid quotient token ID");
              return false;
            }
          }
          else
          {
            if( c1 != 0 )
            {
              error("invalid pattern token ID");
              return false;
            }
            continue;
          }
        }
        result += (char)c1;
        if( p[i+3] == '.' )
        {
          if( i+9 >= len )
          {
            error("invalid start pattern or quotient token ID");
            return false;
          }
          i += 6;
          buf[0] = p[i];
          buf[1] = p[i+1];
          buf[2] = p[i+2];
          buf[3] = '\0';
          c2 = System.Convert.ToInt32(buf);
          while( ++c1 <= c2 )
          {
            result += (char)c1;
          }
        }
      }
      if( !seq && result.Length == 0 )
      {
        error("missing pattern characters");
        return false;
      }
      return true;
    }

    //! add a quotient or pattern token to the corresponding map
    //! @param p pattern symbol specification
    //! @param idx combined group and token index \>= 0
    //! @param pat pattern token ?
    //! @return true or false on error
    protected virtual bool initPatternMap(string p, long idx, bool pat)
    {
      string patsym = "";
      if( pat )
      { int pos = p.IndexOf(SCN_SEP_TOK_ID_PATTERN);
        if( pos >= 0 && pos < p.Length )
        { string p1, p2;
          p1 = p.Substring(0,pos);
          p2 = p.Substring(pos+1);
          if( !cPatMap.Contains(idx) )
          {
            if( ! initPatternSymbol(p1,false,ref patsym) )
              return false;
            cPatMap[idx] = patsym;
          }
          if( !cQPatMap.Contains(idx) )
          {
            if( ! initPatternSymbol(p2,true,ref patsym) )
              return false;
            cQPatMap[idx] = patsym;
          }
        }
        else
        {
          if( p.Substring(0,3) == "000" )
          {
            if( !cPatMap.Contains(idx) )
            {
              if( ! initPatternSymbol(p,false,ref patsym) )
                return false;
              cPatMap[idx] = patsym;
            }
          }
          else
          {
            if( !cQPatMap.Contains(idx) )
            {
              if( ! initPatternSymbol(p,true,ref patsym) )
                return false;
              cQPatMap[idx] = patsym;
            }
          }
        }
      }
      else
      { 
        if( !cQPatMap.Contains(idx) )
        {
          if( ! initPatternSymbol(p,true,ref patsym) )
            return false;
          cQPatMap[idx] = patsym;
        }
      }
      return true;
    }

    //! collect patterns of pattern and quotient tokens
    //! @return true or false on error
    protected virtual bool initPattern()
    {
      if( GrpScn.Count > 0 )
      {
        for( int i=0; i < GrpScn.Count; ++i )
        {
          for( int j=0; j < ((CStyxScanner)GrpScn[i]).TokId.Count; j++)
          { 
            string tokid = (string)((CStyxScanner)GrpScn[i]).TokId[j];
            int    pos   = tokid.IndexOf(SCN_SEP_TOK_ID_PATTERN);
            if( pos >= 0 && pos < tokid.Length )
            { 
              bool ok = initPatternMap
                        (
                          tokid.Substring(pos+1), i32Value((short)i,(short)j),
                          ((byte)((CStyxScanner)GrpScn[i]).Flags[j]&(byte)EStyxTokFlag.SCN_FLG_PatternToken)!=0 
                        );
              if( !ok ) return false;
            }
          }
        }
      }
      else
      {
        for (int j=0; j < TokId.Count; j++)
        { 
          string tokid = (string)TokId[j];
          int    pos   = tokid.IndexOf(SCN_SEP_TOK_ID_PATTERN);
          if( pos >= 0 && pos < tokid.Length )
          { bool ok = initPatternMap
                      (
                        tokid.Substring(pos+1), i32Value(-1,(short)j),
                        ((byte)Flags[j]&(byte)EStyxTokFlag.SCN_FLG_PatternToken)!=0
                      );
            if( !ok ) return false;
          }
        }
      }
      return true;
    }
    //@}
    
    /** @name SeparateToken
        scan process / token separation
    */
    //@{
    //! separate next token in scan stream
    //! (default function)
    //! @return true or false on error
    protected virtual bool nextToken_default()
    {
      int state = 0;
      beginToken(); 
      if( GrpScn.Count > 0 && cTok >= 0 && 
          cTok == cPatTok && Group == cPatGrp && cPatSym.Length == 0 )
      { /* end pattern token switch already done */
        cPatGrp = -1; cPatTok = -1;
      }
      else
      if( GrpScn.Count > 0 && cTok >= 0 && 
          ((short)((CStyxScanner)GrpScn[Group]).Switch[cTok] >= 0 || 
            ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_GroupStack) != 0) &&
          !switchGroup((short)((CStyxScanner)GrpScn[Group]).Switch[cTok],false) )
        return false;
    LOOP:
      /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
      cTok = -1; /* -1 == ETX */
      if ( !cStream.eof(cC) )
      { 
        /*
        register wchar_t* i; 
        wchar_t* s = (wchar_t*)EdgeC.data();
        */
        // handle character look-ahead ...
        long  cBackLen = -1, nBackLin = -1, nBackCol = -1;
        short cBackTok = -1;
        // ... handle character look-ahead
        /*
        state = 0;
        for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
        state = EdgeS[i-s-1]-1;
        */
        state = 0;
        long i, s;
        for( s = i = (long)StaEdg[state]; (uint)EdgeC[(int)i++] > (uint)cC; );
        state = (int)((long)EdgeS[(int)(i-s-1)]-1);
        while (state >= 0)
        {
          /* n character look-ahead:
             jeweils den größten Endzustand merken, zusammen mit Tokenlänge.
             nach der schleife, 
             1) wert oder fehler 
             2) fehler mit vorangegangenem Wert --> 
                zurücksetzen auf ende wertposition via backbuffer und fortsetzen
          */
          cTok = (short)StaFin[state]; getCharacter();
          // handle character look-ahead ...
          if( lookahead && cTok > 0 )
          {
            cBackLen = currentLength(); 
            nBackLin = nLine; nBackCol = nCol;
            cBackTok = cTok;
          }
          // ... handle character look-ahead
          if ( cStream.eof(cC) )
          {
            break;
          }
          /*
          for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
          state = EdgeS[i-s-1]-1;
          */
          for( i = (long)StaEdg[state]; (uint)EdgeC[(int)i++] > (uint)cC; );
          state = (int)((long)EdgeS[(int)(i-s-1)]-1);
        }
        // handle character look-ahead ...
        if( lookahead && cTok == 0 && cBackTok > 0 )
        {
          cTok = cBackTok; backbufLookahead(cBackLen,nBackLin,nBackCol);
        }
        // ... handle character look-ahead
        if( currentLength() == 0 && !cStream.eof(cC) )
        { getCharacter(); cTok = 0; }
        // process dyck token ...
        if( dscanner.Contains(cTok) && !nextToken_dyck() )
          return false;
        // ... process dyck token
        if( ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_IgnoreToken) != 0 )
        { beginToken(); 
          if( GrpScn.Count > 0 && cTok >= 0 && 
              ((short)((CStyxScanner)GrpScn[Group]).Switch[cTok] >= 0 || 
                ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_GroupStack) != 0) &&
              !switchGroup((short)((CStyxScanner)GrpScn[Group]).Switch[cTok],false) )
            return false;
          goto LOOP; 
        }
      }
      return endToken();
    }
    
    //! separate dyck token in scan stream
    //! @return true or false on error
    protected virtual bool nextToken_dyck()
    {
      int state = 0, cnt = 1; long cLen = currentLength(); 
      short dTok = cTok;
      CStyxScanner dyck = (CStyxScanner)dscanner[cTok];
    LOOP:
      cLen    = currentLength();
      cTok = -1; /* -1 == ETX */
      if ( !cStream.eof(cC) )
      { 
        /*
        register wchar_t* i; 
        wchar_t* s = (wchar_t*)dyck.EdgeC.data();
        state = 0;
        for (i = &s[dyck.StaEdg[state]]; *i++ > cC; );
        state = dyck.EdgeS[i-s-1]-1;
        */
        state = 0;
        long i, s;
        for( s = i = (long)dyck.StaEdg[state]; (uint)EdgeC[(int)i++] > cC; );
        state = (int)((long)dyck.EdgeS[(int)(i-s-1)]-1);

        while (state >= 0)
        {
          cTok = (short)dyck.StaFin[state]; getCharacter();
          if ( cStream.eof(cC) )
            break;

          /*
          for (i = &s[dyck.StaEdg[state]]; *i++ > cC; );
          state = dyck.EdgeS[i-s-1]-1;
          */
          for( i = (long)dyck.StaEdg[state]; (uint)EdgeC[(int)i++] > cC; );
          state = (int)((long)dyck.EdgeS[(int)(i-s-1)]-1);
        }
        if((currentLength() - cLen) == 0 && !cStream.eof(cC)) 
        { getCharacter(); cTok = 0; }
      }
      if( cTok > 0 || ( cTok == 0 && dyck.TokId.Count == 3 ) )
      {
        if( cTok == (short)EStyxDyckTokID.SCN_DYCKTOKEN_PREFIX ) ++cnt;
        else
        if( cTok == (short)EStyxDyckTokID.SCN_DYCKTOKEN_SUFFIX ) --cnt;
        if( cnt == 0 ) cTok = dTok;
        else goto LOOP;
      }
      return true;
    }
  
    //! re-init current scan group
    //! @param Group scan group index \>= 0 or -1 for the top group on stack
    //! @param asgflg = false --\> push/pop group to/from stack
    //! @return true or false on error
    protected virtual bool switchGroup(short Group, bool asgflg)
    {
      if( !asgflg )
      {
        if( Group == -1 )
        {
          if (cTok < 0 || 
              ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_GroupStack) == 0 ||
              GroupStack.Count <= 0) 
          {
            error("group switch failed");
            return false;
          }
          Group = (short)GroupStack[GroupStack.Count-1];
          GroupStack.RemoveAt(GroupStack.Count-1);
        }
        else
        if( ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_GroupStack) != 0 )
        {
          GroupStack.Add(this.Group);
        }
      }
      if( this.Group != Group )
      { 
        this.Group = Group;
        StaEdg     = ((CStyxScanner)GrpScn[Group]).StaEdg;
        StaFin     = ((CStyxScanner)GrpScn[Group]).StaFin;
        EdgeC      = ((CStyxScanner)GrpScn[Group]).EdgeC;
        EdgeS      = ((CStyxScanner)GrpScn[Group]).EdgeS;
        Flags      = ((CStyxScanner)GrpScn[Group]).Flags;
        dscanner.Clear();
        for( int i=0; i < ((CStyxScanner)GrpScn[Group]).dyckidx.Count; ++i )
        {
          dscanner[(short)((CStyxScanner)GrpScn[Group]).dyckidx[i]] = 
            (CStyxScanner)((CStyxScanner)GrpScn[Group]).dyckpat[i];
        }
      }
      return true;
    }

    //! get buffer length of scanned (unicode) characters
    //! @return buffer length
    protected virtual long currentLength()
    {
      return (long)buffer.Length;
    }

    //! init next token ( clear buffer, init position )
    protected virtual void beginToken()
    {
      cCol = nCol; cLine = nLine;
      buffer = "";
    }

    //! add (unicode) character to buffer
    //! @param c (unicode) character
    protected virtual void addCharacter(int c)
    {
      buffer += (char)c;
    }

    //! save current and get next valid (unicode) character
    //! and update token position
    protected virtual void getCharacter()
    {
      addCharacter(cC);
      if (cC == (int)'\n')
      { nLine += 1; nCol = 1; }
      else
      { nCol += 1; }
      if( bbuffer.Count > 0 )
      {
        cC = (int)bbuffer[bbuffer.Count-1];
        bbuffer.RemoveAt(bbuffer.Count-1);
      }
      else
      {
        cC = cStream.sgetc();
        if( skipC.Count > 0 ) skipCharacter();
      }
    }

    //! skip non-valid (unicode) characters in current scan stream
    protected virtual void skipCharacter()
    {
      while( skipC.Contains(cC) )
      {
        if (cC == (int)'\n')
        { nLine += 1; nCol = 1; }
        else
        { nCol += 1; }
        cC = cStream.sgetc();
      }
    }

    //! finalize next token
    //! ( handle case, pattern/quotient token and preprocessing )
    //! @return true or false on error
    protected virtual bool endToken()
    {
      //Console.WriteLine("TOKEN-BUFFER="+buffer);
      if (cTok >= 0 && ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_IgnoreCase) != 0) 
      {
        buffer = buffer.ToLower(); //FIXME:cultureinfo
      }
      if( cTok == -1 ) /* EOF */
      {
        if( pstreams.Count > 0 )
        {
          if( cStream != null ) cStream = null; 
          cStream = ((StyxStreamPos)pstreams[pstreams.Count-1]).Stream;
          nLine   = ((StyxStreamPos)pstreams[pstreams.Count-1]).Line;
          nCol    = ((StyxStreamPos)pstreams[pstreams.Count-1]).Column;
          bbuffer = ((StyxStreamPos)pstreams[pstreams.Count-1]).Backbuffer;
          cC      = ((StyxStreamPos)pstreams[pstreams.Count-1]).curChar;
          pstreams.RemoveAt(pstreams.Count-1);
          return nextToken();
        }
      }
      else
      if( cTok > 0 )
      {
        if( cQPatMap.Count > 0 && !endQuotient() ) 
          return false;
        if( cTok > 0 && 
            ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_PatternToken) != 0 && 
            !endPattern() )
          return false;
        if( cTok > 0 && preprocess )
        { 
          CStyxStream PStream = cStream;
          string Token = "";
          string Value = "";
          if( !currentToken(ref Token,ref Value) ) 
            return false;
          //Console.WriteLine("preprocess "+Token);
          if( !preprocessToken(ref PStream,ref Token,ref Value) ) 
          {
            error("preprocessing failed");
            return false;
          }
          if( PStream == cStream ) buffer = Value;
          //Console.WriteLine("preprocess2 "+Token);
          if( PStream != cStream )
          {
            if( PStream != null )
            { StyxStreamPos curStreamPos = new StyxStreamPos();
              curStreamPos.Stream     = cStream;
              curStreamPos.Line       = nLine;
              curStreamPos.Column     = nCol;
              curStreamPos.Backbuffer = bbuffer;
              curStreamPos.curChar    = cC;
              pstreams.Add(curStreamPos);
              cStream = PStream;
              cC = cStream.sgetc();
              nLine = nCol = 1;
              bbuffer.Clear();
              //Console.WriteLine("preprocess3 "+PStream.getFile());
            }
            return nextToken();
          }
          //Console.WriteLine("preprocess4");
        }
      }
      return true;
    }

    //! finalize pattern token
    //! @return true or false on error
    protected virtual bool endPattern()
    {
      long idx = -1;
      if( GrpScn.Count > 0 )
        idx = i32Value((short)this.Group,(short)cTok);
      else
        idx = i32Value((short)-1,(short)cTok);
      if( cPatSym.Length == 0 && cPatMap.Contains(idx) )
      { /* start pattern token */
        cPatTok = cTok;
        if( GrpScn.Count > 0 )
          cPatGrp = Group;
        /* get pattern set */
        string pat = (string)cPatMap[idx];
        /* get pattern */
        long i;
        for( i=0; i < buffer.Length; ++i )
        {
          int pos = pat.IndexOf(buffer[(int)i]);
          if( pos >= 0 && pos < pat.Length )
            break;
        }
        for( ; i < buffer.Length; ++i )
        {
          int pos = pat.IndexOf(buffer[(int)i]);
          if( pos >= 0 && pos < pat.Length )
            cPatSym += buffer[(int)i];
          else break;
        }
        if( cPatSym.Length == 0 )
          cTok = 0; /* error */
      }
      else
      if( cPatSym.Length > 0 && !cPatMap.Contains(idx) )
      { /* end pattern token, try to match pattern */
        long pos = buffer.IndexOf(cPatSym);
        if( pos >= 0 && pos < buffer.Length )
        { /* pattern found */
          cTok = cPatTok; cPatSym = "";
          if( GrpScn.Count > 0 && !switchGroup(cPatGrp,true) )
            return false;
        }
      }
      else cTok = 0; /* error */
      return true;
    }

    //! finalize quotient token
    //! @return true or false on error
    protected virtual bool endQuotient()
    {
      long idx = -1;
      if( GrpScn.Count > 0 )
        idx = i32Value((short)this.Group,(short)cTok);
      else
        idx = i32Value((short)-1,(short)cTok);
      if( cQPatMap.Contains(idx) )
      {
        /* get quotient pattern */
        string pat = (string)cQPatMap[idx];
        long   len = pat.Length-1;
        /* push back quotient */
        if( len > 0 )
        {
          if( pat[0] == '"' ) /* sequence */
          {
            if( buffer.Length <= len )
              cTok = 0; /* error; = --> endless recursion */
            else
            {
              long pos = buffer.IndexOf(pat.Substring(1),(int)(buffer.Length-len));
              if( pos >= 0 && pos < buffer.Length )
                backbufQuotient(buffer.Length-len);
              else
                cTok = 0; /* error; = --> endless recursion */
            }
          }
          else
          { long i;
            pat = pat.Substring(1);
            for( i=buffer.Length-1; i >= 0; --i )
            {
              int pos = pat.IndexOf(buffer[(int)i]);
              if( pos < 0 || pos >= pat.Length )
                break;
            }
            if( i < 0 ) cTok = 0; /* error: endless recursion */
            else
            if( i < buffer.Length-1 )
              backbufQuotient(i+1);
          }
        }
      }
      return true;
    }

    //! save quotient to backbuffer
    //! @param cBackLen quotient length
    protected virtual void backbufQuotient(long cBackLen)
    {
      long i;
      bbuffer.Add((char)cC);
      for( i=((long)buffer.Length)-1; i > cBackLen; --i )
        bbuffer.Add(buffer[(int)i]);
      cC = (int)buffer[(int)i];
      buffer.Remove((int)i,1);
      for( i=0, nLine=cLine, nCol=cCol; i < cBackLen; ++i )
      {
        if( buffer[(int)i] == '\n' )
        { nLine += 1; nCol = 1; }
        else
        { nCol += 1; }
      }
    }

    //! save look-ahead to backbuffer and update stream position
    //! @param cBackLen look-ahead length
    //! @param nBackLin stream line
    //! @param nBackCol stream column
    protected virtual void backbufLookahead
                      (
                        long cBackLen, long nBackLin, long nBackCol
                      )
    {
      long i;
      bbuffer.Add((char)cC);
      for( i=((long)buffer.Length)-1; i > cBackLen; --i )
        bbuffer.Add(buffer[(int)i]);
      cC = (int)buffer[(int)i];
      buffer.Remove((int)i,1);
      nLine = nBackLin; nCol = nBackCol;
    }
    //@}

    //! preprocess handler if preprocessing is enabled 
    //! @param PStream [changeable] current scan stream
    //! \n = initial value --\> update value of current token
    //! \n = 0             --\> ignore current token
    //! \n else            --\> rescan new allocated stream,
    //! \n                      afterwards deleted by the scanner
    //! @param Token internal name of current token
    //! @param Value [changeable] value of current token
    //! @return true or false on error
    protected virtual bool preprocessToken
                           (
                             ref CStyxStream PStream, ref string Token, ref string Value
                           )
    {
      return true;
    }
  
    //! The constructor creates an uninitialized scanner.
    public CStyxScanner(/*bool lahead = false, bool process = false*/)
    {
      lookahead  = false;
      preprocess = false;
      reset();
    }

    //! The constructor creates an uninitialized scanner.
    //! @param lahead enable n character look-ahead ?
    //! @param process enable preprocessing ?
    public CStyxScanner(bool lahead, bool process)
    {
      lookahead  = lahead;
      preprocess = process;
      reset();
    }

    //! scanner and stream are initialized ?
    //! @return true for an initialized scanner and stream
    public virtual bool initialized()
    {
      return initok && cStream != null && cStream.valid();
    }

    //! n character look-ahead enabled ?
    //! @return true if n character look-ahead is enabled
    public virtual bool LookaheadEnabled()
    {
      return lookahead;
    }

    //! preprocessing enabled ?
    //! @return true if preprocessing is enabled
    public virtual bool PreprocessEnabled()
    {
      return preprocess;
    }
  
    //! get language
    //! @return language name or ""
    public virtual string getLanguage()
    {
      if( !initok ) return "";
      return Name;
    }

    //! get number of scan groups
    //! @return number of scan groups or -1
    public virtual short getGroups()
    {
      if( !initok ) return -1;
      return (short)GrpScn.Count;
    }

    //! get scan group name
    //! @param GrpIdx scan group index \>= 0
    //! @return scan group name or ""
    public virtual string getGroupID(short GrpIdx)
    {
      if( !initok ) return "";
      return GrpIdx >= 0 && GrpIdx < GrpScn.Count
             ? ((CStyxScanner)GrpScn[GrpIdx]).Name : "";
    }

    //! get number of tokens 
    //! @return number of tokens or -1
    public virtual short getTokens()
    {
      if( !initok ) return -1;
      return (short)TokId.Count;
    }

    //! get number of tokens in scan group 
    //! @param GrpIdx scan group index \>= 0
    //! @return number of tokens in scan group or -1
    public virtual short getTokens(short GrpIdx)
    {
      if( !initok ) return -1;
      if( GrpIdx == -1 )
        return (short)TokId.Count;
      else
        return GrpIdx >= 0 && GrpIdx < GrpScn.Count
               ? (short)((CStyxScanner)GrpScn[GrpIdx]).TokId.Count : (short)-1;
    }

    //! get internal token name in scan group
    //! @param TokIdx token index \>= 0
    //! @return internal token name or ""
    public virtual string getTokenID(short TokIdx)
    {
      if( !initok ) return "";
      return TokIdx >= 0 && TokIdx < TokId.Count
             ? (string)TokId[TokIdx] : "";
    }

    //! get internal token name in scan group
    //! @param TokIdx token index \>= 0
    //! @param GrpIdx scan group index \>= 0
    //! @return internal token name in scan group or ""
    public virtual string getTokenID(short TokIdx, short GrpIdx)
    {
      if( !initok ) return "";
      if( GrpIdx == -1 )
        return TokIdx >= 0 && TokIdx < TokId.Count
               ? (string)TokId[TokIdx] : "";
      else
        return GrpIdx >= 0 && GrpIdx < GrpScn.Count &&
               TokIdx >= 0 && TokIdx < ((CStyxScanner)GrpScn[GrpIdx]).TokId.Count
               ? (string)((CStyxScanner)GrpScn[GrpIdx]).TokId[TokIdx] : "";
    }
  
    //! import scanner table from file 
    //! @param Path path to the exported scanner table 
    //! @return true --> initialized scanner or false on error
    public virtual bool loadTableFile(string Path)
    {
      reset();
      try
      {
        using( StreamReader reader = new StreamReader(Path) ) //FIXME:Encoding
        {
          string line = "", Object = ""; 
          CStyxScanner cScanner = this;
          short tokidx = 0;
          int c;
          while( (c = reader.Read()) >= 0 )
          {
            if( (char)c == '\n' )
            {
              if( !loadTableLine(ref line,ref cScanner,ref Object,ref tokidx) )
                return false;
            }
            else line += (char)c;
          }
        }
      }
      catch(Exception e)
      {
        error("couldn't read '" + Path + "'" + Environment.NewLine + e.ToString());
        return false;
      }
      initok = checkLoad() && initPattern();
      return initok;
    }

    //! import scanner table from string
    //! @param Table exported scanner table 
    //! @return true --> initialized scanner or false on error
    public virtual bool loadTableString(string Table)
    {
      reset();
      string line = "", Object = ""; 
      CStyxScanner cScanner = this;
      short tokidx = 0;
      char c;
      for( long i=0; i < Table.Length; ++i )
      {
        c = Table[(int)i];
        if( c == '\n' )
        {
          if( !loadTableLine(ref line,ref cScanner,ref Object,ref tokidx) )
            return false;
        }
        else line += c;
      }
      initok = checkLoad() && initPattern();
      return initok;
    }

    //! initialize scan process 
    //! @param Stream scan stream
    //! @param SkipCharacters skip characters in stream
    //! @return true or false on error
    public virtual bool scanStream(ref CStyxStream Stream, ref Hashtable SkipCharacters /*uint,null*/)
    {
      if( !initok ) return false;
      cStream = Stream;
      if( cStream == null || !cStream.valid() )
      {
        error("invalid stream");
        return false;
      }
      skipC = SkipCharacters;
      if( skipC == null ) skipC = new Hashtable();
      next  = new T_next(this.nextToken_default);
      if( GrpScn.Count > 0 )
      {
        Group   = 0;
        StaEdg  = ((CStyxScanner)GrpScn[0]).StaEdg;
        StaFin  = ((CStyxScanner)GrpScn[0]).StaFin;
        EdgeC   = ((CStyxScanner)GrpScn[0]).EdgeC;
        EdgeS   = ((CStyxScanner)GrpScn[0]).EdgeS;
        Flags   = ((CStyxScanner)GrpScn[0]).Flags;
        for( int i=0; i < ((CStyxScanner)GrpScn[0]).dyckidx.Count; ++i )
        {
          dscanner[(short)((CStyxScanner)GrpScn[Group]).dyckidx[i]] = 
            (CStyxScanner)((CStyxScanner)GrpScn[Group]).dyckpat[i];
        }
      }
      else 
      {
        Group   = -1;
        for( int i=0; i < dyckidx.Count; ++i )
        {
          dscanner[(short)dyckidx[i]] = (CStyxScanner)dyckpat[i];
        }
      }
      cC      = cStream.sgetc();
      nLine   = 1;
      nCol    = 1;
      cTok    = 0;
      cPatTok = cPatGrp = -1;
      cPatSym = "";
      bbuffer.Clear();
      return initialized();
    }

    //! separate next token in scan stream
    //! @return true or false on error
    public virtual bool nextToken()
    {
      if( !initok || cStream == null ) return false;
      if( next() ) return true;
      deleteStreams();
      return false;
    }

    //! end of scan stream ?
    //! @return true on end of scan stream
    public virtual bool eos()
    {
      return (cTok == -1); 
    }

    //! get (current) scan stream
    //! @param PStream [result] current scan stream or NULL
    public virtual void getStream(ref CStyxStream PStream) 
    {
      PStream = cStream;
    }

    //! get current token identifier and value
    //! @param Token [result] internal token name
    //! @param Value [result] token value
    //! @return true or false on error
    public virtual bool currentToken(ref string Token, ref string Value)
    {
      if( initok && cStream != null )
      {
        if (cTok == -1) 
        {
          Token = "[EOF]";
          return true;
        }
        else
        if( GrpScn.Count > 0 )
        {
          Token = (string)((CStyxScanner)GrpScn[Group]).TokId[cTok];
        }
        else
        {
          Token = (string)TokId[cTok];
        }
        Value = buffer;
        return true;
      }
      return false;
    }

    //! get external token name
    //! @param Token internal token name
    //! @return external token name
    public virtual string externalTokenID(ref string Token)
    {
      int pos = Token.IndexOf(SCN_SEP_TOK_ID_PATTERN);
      if( pos < 0 || pos >= Token.Length )
        return Token;
      else
        return Token.Substring(0,pos); 
    }

    //! current token is not case sensitive ?
    //! @return true for a case insensitive token
    public virtual bool ignoreCase()
    {
      if( !initok ) return false;
      return (cTok >= 0 && 
             ((byte)Flags[cTok]&(byte)EStyxTokFlag.SCN_FLG_IgnoreCase) != 0); 
    }

    /** @name CurrentTokenPosition
        current token position
    */
    //@{
    //! get stream line of current token
    public virtual long getLine() 
    {
      return cLine;
    }

    //! get stream column of current token
    public virtual long getCol()
    {
      return cCol;
    }

    //! get stream identifier
    public virtual string getFile()
    {
      return cStream != null ? cStream.getFile() : "";
    }
    //@}
  }

  /* Scanner with standard Styx compliant preprocessing facility ------------ */

  //! scanner with standard Styx compliant preprocessing facility
  public class CStyxPScanner : CStyxScanner
  {
    //! preprocessing parameter type: index --\> value

    /** Indexes of the default macro token identifiers, macro keywords 
        as well as the default include path and characterset
    */
    public enum EStyxParIndex
    {
      IDX_TOK_IDE    = 0,  //!< token identifier
      IDX_MAC_DFN    = 1,  //!< token define macro 
      IDX_MAC_SEP    = 2,  //!< token parameter separator (in macro calls)
      IDX_MAC_INC    = 3,  //!< token include
      IDX_MAC_COND   = 4,  //!< token condition
      IDX_MAC_DEL    = 5,  //!< token undefine macro
      IDX_KEY_START  = 6,  //!< initial keyword define macro
      IDX_KEY_END    = 7,  //!< final keyword define macro, condition
      IDX_KEY_IFDEF  = 8,  //!< initial keyword ifdef condition
      IDX_KEY_IFNDEF = 9,  //!< initial keyword ifndef condition
      IDX_KEY_ELSE   = 10, //!< initial keyword else condition
      IDX_KEY_INC    = 11, //!< initial keyword include
      IDX_KEY_UNDEF  = 12, //!< initial keyword undefine macro
      IDX_INC_PATH   = 13, //!< include path
      IDX_INC_CSET   = 14, //!< include characterset
      IDX_PAR_END          //!< end of parameter indexes
    }


/*
  protected:
    typedef vector<bool>           V_bool;

    //! macro definition type: id --\> { formal parameter } text
    typedef map<string,V_string>   M_macdfn; 
    //! macro callstack type: { id { actual parameter } }
    typedef vector<V_string>       V_macexp; 
*/

    protected string[]  MacParDefaults;

    protected Hashtable Parameters; //!< preprocessing parameters (short,string)
                                    //!< @link #EStyxParIndex index @endlink --\> value 
    protected Hashtable MacDefines; //!< macro definitions (string,string[])
    protected ArrayList MacStack;   //!< macro expressions / callstack (string[])
    protected ArrayList CondStack;  //!< condition stack (bool)
    protected int       CurSep;     //!< current parameter separator (in macro calls)
    protected string    CurPar;     //!< current macro parameter under construction or ""
    protected bool      MacIgnCase; //!< ignore case in macro identifiers ?
                                    //!< ( must be true or match the case specification of the identifier token )

    //! make full path name
    //! @param dir directory path
    //! @param file file name
    //! @param sep path separator
    //! @return the full path or file name
    protected virtual string makePath
                      (
                        ref string dir, ref string file, string sep
                      )
    {
      if( dir.Length > 0 )
      {
        if( dir[dir.Length-1] == '/' ||
            dir[dir.Length-1] == '\\' )
        {
          return dir + file;
        }
        else
        if( sep.Length == 1 )
        {
          return dir + (( sep[0] == ':' ) ? "/" : "\\") + file;
        }
        else
        {
          int pos = dir.IndexOf("\\");
          if( pos >= 0 && pos < dir.Length )
          {
            return dir + "\\" + file;
          }
          else
          {
            return dir + "/" + file;
          }
        }
      }
      return file;
    }

    //! set substream identifier relative to main stream position
    //! @param PStream the new substream
    protected virtual void setStreamID(ref CStyxStream PStream)
    {
      if( PStream == null ) return;
      string id = getFile();
      id += "(";
      id += getLine().ToString();
      id += ",";
      id += getCol().ToString();
      id += ")#";
      id += PStream.getFile();
      PStream.setFile(id);
    }
    //! create a new string stream for the evaluated macro
    //! and set substream identifier relative to main stream position
    //! @param id macro identifier
    //! @param Text evaluated macro text
    //! @return the allocated string stream or null on error
    protected virtual CStyxStream createMacroStream(ref string id, ref string Text)
    {
      try
      {
        CStyxStream result = new CStyxStringStream(Text,id);
        setStreamID(ref result);
        return result;
      }
      catch(Exception e)
      {
        error("couldn't create macro stream '" + id + "'" + Environment.NewLine + e.ToString());
        return null;
      }
    }

    //! create a new file stream and set substream identifier 
    //! relative to main stream position
    //! @param Path stream path
    //! @return the allocated file stream or null on error
    protected virtual CStyxStream createFileStream(ref string Path)
    {
      try
      {
        CStyxStream result = new CStyxFileStream(Path,"");
        setStreamID(ref result);
        return result;
      }
      catch(Exception e)
      {
        error("couldn't create file stream '" + Path + "'" + Environment.NewLine + e.ToString());
        return null;
      }
    }

    //! eval include directive
    //! @param Value include directive
    //! @return the allocated file stream or null on error
    protected virtual CStyxStream evalInclude(ref string Value)
    {
      string k = (string)Parameters[(short)EStyxParIndex.IDX_KEY_INC];
      int pos = Value.IndexOf(k);
      if( pos != 0 )
      {
        error("unknown include keyword");
        return null;
      }
      pos += k.Length;
      while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
      {
        pos += 1;
      }
      if( pos >= Value.Length )
      {
        error("missing include file");
        return null;
      }
      string f = Value.Substring(pos);
      if( File.Exists(f) )
      {
        return createFileStream(ref f);
      }
      string p = System.Environment.GetEnvironmentVariable(f);
      if( p == null ) p = f;
      string s = ";:";
      pos = p.IndexOfAny(s.ToCharArray());
      if( pos >= 0 && pos < p.Length )
      {
        if( p[pos] == ';' ) s = ";";
        else
        if( pos < p.Length - 1 && p[pos+1] == '\\' )
          s = ";";
        else s = ":";
      }
      while( pos >= 0 && pos < p.Length )
      {
        string d = p.Substring(0,pos);
        if( d.Length > 0 )
        {
          string fp = makePath(ref d,ref f,s);
          if( fp.Length > 0 && File.Exists(fp) )
          {
            return createFileStream(ref fp);
          }
        }
        p = p.Substring(pos+1);
        pos = p.IndexOf(s);
      }
      if( p.Length > 0 )
      {
        string fp = makePath(ref p,ref f,s);
        if( fp.Length > 0 && File.Exists(fp) )
        {
          return createFileStream(ref fp);
        }
      }
      error("'" + f + "' not found");
      return null;
    }

    //! set parameter separator (in macro calls)
    //! @param Value parameter separator
    protected virtual void setSeparator(ref string Value)
    {
      if( Value.Length >= 2 && !Char.IsWhiteSpace(Value[1]) )
        CurSep = (int)Value[1];
      else CurSep = 0;
    }

    //! part of an explicit separated parameter ?
    //! @param Value token value
    //! @return true for a partial parameter
    protected virtual bool partialParameter(ref string Value)
    {
      return CurSep != 0 && 
             ( Value.Length != 1 || ((int)Value[0]) != CurSep );
    }

    //! apply macro
    //! @param Definition macro definition (formal parameters, text)
    //! @param Parameters macro call (actual parameters, id)
    //! @return the evaluated macro text
    protected virtual string applyMacro
                      (
                        ref ArrayList/*string*/ Definition, ref ArrayList/*string*/ Parameters
                      )
    {
      if( Definition.Count == 0 ) return "";
      string text = (string)Definition[Definition.Count-1]; 
      string res = "";
      for( int i=0, j=0; i < text.Length; )
      { 
        for( j=0; j < Definition.Count-1; ++j )
        { 
          int pos = text.IndexOf((string)Definition[j],i);
          if( pos == i ) break;
        }
        if( j < Definition.Count-1 )
        {
          res += (string)Parameters[j+1];
          i += ((string)Definition[j]).Length;
        }
        else 
        {
          res += text[i]; ++i;
        }
      }
      return res;
    }

    //! eval macro parameter
    //! @param Value macro parameter
    //! @param id [result] identifier of the evaluated macro
    //! @return the evaluated macro text or ""
    protected virtual string evalMacroParameter(ref string Value, ref string id)
    {
      if( MacStack.Count == 0 ) return "";
      ArrayList macexp = (ArrayList)MacStack[MacStack.Count-1];
      id = (string)macexp[0];
      macexp.Add(Value);
      MacStack[MacStack.Count-1] = macexp;
      ArrayList macdfn = (ArrayList)MacDefines[id];
      if( macdfn.Count == macexp.Count )
      { 
        string text = applyMacro(ref macdfn,ref macexp);
        MacStack.RemoveAt(MacStack.Count-1);
        if( MacStack.Count == 0 ) return text;
        return evalMacroParameter(ref text, ref id);
      }
      return "";
    }

    //! eval macro call
    //! @param Value macro name
    //! @param id [result] identifier of the evaluated macro
    //! @return the evaluated macro text or ""
    protected virtual string evalMacroCall(ref string Value, ref string id)
    {
      if( !MacDefines.Contains(Value) ) return "";
      ArrayList macdfn = (ArrayList)MacDefines[Value];
      ArrayList call = new ArrayList();
      id = Value;
      if( MacStack.Count == 0 )
      {
        if( macdfn.Count == 0 ) return "";
        if( macdfn.Count == 1 ) return (string)macdfn[0];
        call.Add(Value);
        MacStack.Add(call);
        return "";
      }
      string par = "";
      if( macdfn.Count == 0 ) 
        return evalMacroParameter(ref par,ref id);
      if( macdfn.Count == 1 )
      {
        par = (string)macdfn[0];
        return evalMacroParameter(ref par,ref id);
      }
      call.Add(Value);
      MacStack.Add(call);
      return "";
    }

    //! eval undefine macro
    //! @param Value undefine macro
    //! @return true or false on error
    protected virtual bool evalUndefine(ref string Value)
    {
      string u = (string)Parameters[(short)EStyxParIndex.IDX_KEY_UNDEF];
      int pos = Value.IndexOf(u);
      if( pos != 0 )
      {
        error("unknown undefine keyword");
        return false;
      }
      string id = "";
      pos += u.Length;
      while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
      {
        ++pos;
      }
      if( pos >= Value.Length )
      {
        error("missing macro name");
        return false;
      }
      while( pos < Value.Length && !Char.IsWhiteSpace(Value[pos]) )
      {
        id += MacIgnCase ? Char.ToLower(Value[pos]) : Value[pos];
        ++pos;
      }
      MacDefines.Remove(id);
      return true;
    }

    //! eval define macro
    //! @param Value define macro
    //! @return true or false on error
    protected virtual bool evalDefine(ref string Value)
    {
      string d = (string)Parameters[(short)EStyxParIndex.IDX_KEY_START];
      int pos = Value.IndexOf(d);
      if( pos != 0 )
      {
        error("unknown define keyword");
        return false;
      }
      string id = ""; 
      ArrayList pars = new ArrayList();
      pos += d.Length;
      while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
        ++pos;
      while( pos < Value.Length && !Char.IsWhiteSpace(Value[pos]) &&
             Value[pos] != '(' && Value[pos] != '=' )
      {
        id += MacIgnCase ? Char.ToLower(Value[pos]) : Value[pos];
        ++pos;
      }
      while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
        ++pos;
      if( pos < Value.Length )
      { string v = Value.Substring(pos+1);
        if( Value[pos] == '(' )
        { 
          string s = ",)";
          pos = v.IndexOfAny(s.ToCharArray());
          while( pos >= 0 && pos < v.Length )
          { string p = ""; 
            for( int i=0; i < pos; ++i )
            {
              if( !Char.IsWhiteSpace(v[i]) ) p += v[i];
            }
            if( p.Length == 0 )
            {
              error("missing formal macro parameter");
              return false;
            }
            pars.Add(p);
            if( v[pos] == ')' ) break;
            v   = v.Substring(pos+1);
            pos = v.IndexOfAny(s.ToCharArray());
          }
          if( pos >= v.Length || v[pos] != ')' )
          {
            error("unexpected macro parameter syntax");
            return false;
          }
          pos = v.IndexOf("=",pos+1);
          if( pos >= 0 && pos < v.Length )
            v = v.Substring(pos+1);
          else v = "";
        }
        if( v.Length > 0 )
        {
          pos = v.IndexOf((string)Parameters[(short)EStyxParIndex.IDX_KEY_END]);
          if( pos < 0 || pos >= v.Length )
          {
            error("unexpected end of macro definition");
            return false;
          }
          pars.Add(v.Substring(0,pos));
        }
      }

      MacDefines[id] = pars;
      return true;
    }

    //! eval if[n]def condition
    //! @param Value if[n]def condition
    //! @return true --\> scan the if[n]def branch
    protected virtual bool evalCondition(ref string Value)
    {
      string t = (string)Parameters[(short)EStyxParIndex.IDX_KEY_IFDEF];
      int pos = Value.IndexOf(t);
      string id = "";
      if( pos == 0 )
      {
        pos += t.Length;
        while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
          ++pos;
        while( pos < Value.Length && !Char.IsWhiteSpace(Value[pos]) )
        {
          id += MacIgnCase ? Char.ToLower(Value[pos]) : Value[pos];
          ++pos;
        }
        return MacDefines.Contains(id);
      }
      string f = (string)Parameters[(short)EStyxParIndex.IDX_KEY_IFNDEF];
      pos = Value.IndexOf(f);
      if( pos == 0 )
      {
        pos += f.Length;
        while( pos < Value.Length && Char.IsWhiteSpace(Value[pos]) )
          ++pos;
        while( pos < Value.Length && !Char.IsWhiteSpace(Value[pos]) )
        {
          id += MacIgnCase ? Char.ToLower(Value[pos]) : Value[pos];
          ++pos;
        }
        return MacDefines.Contains(id);
      }
      error("unknown condition keyword");
      return false;
    }

    //! preprocess condition macro
    //! @param PStream [update] current scan stream
    //! (set to 0 --\> ignore current token)
    //! @param Token internal name of current token
    //! @param Value value of current token
    //! @return true or false on error
    protected virtual bool preprocessCondition
                           (
                             ref CStyxStream PStream, 
                             ref string Token, ref string Value
                           )
    {
      if( (string)Parameters[(short)EStyxParIndex.IDX_KEY_END] == Value )
      {
        if( CondStack.Count == 0 )
        {
          error("unexpected end condition");
          return false;
        }
        CondStack.RemoveAt(CondStack.Count-1);
      }
      else
      if( (string)Parameters[(short)EStyxParIndex.IDX_KEY_ELSE] == Value )
      {
        if( CondStack.Count == 0 )
        {
          error("unexpected else condition");
          return false;
        }
        if( (bool)CondStack[CondStack.Count-1] )
          CondStack[CondStack.Count-1] = false;
        else
        if( CondStack.Count == 1 ||
            (bool)CondStack[CondStack.Count-2] )
          CondStack[CondStack.Count-1] = true;
      }
      else
      if( CondStack.Count == 0 || (bool)CondStack[CondStack.Count-1] )
      {
        // eval condition
        CondStack.Add(evalCondition(ref Value));
      }
      else 
      {
        CondStack.Add(false);
      }
      PStream = null;
      return true;
    }

    //! standard Styx compliant preprocess handler
    //! @param PStream [changeable] current scan stream
    //! \n = initial value --\> update value of current token
    //! \n = 0             --\> ignore current token
    //! \n else            --\> rescan new allocated stream,
    //! \n                      afterwards deleted by the scanner
    //! @param Token internal name of current token
    //! @param Value [changeable] value of current token
    //! @return true or false on error
     protected override bool preprocessToken
                        (
                          ref CStyxStream PStream, ref string Token, ref string Value
                        )
    {
      if( (string)Parameters[(short)EStyxParIndex.IDX_MAC_COND] == Token )
      {
        return preprocessCondition(ref PStream,ref Token,ref Value);
      }
      if( CondStack.Count > 0 && !(bool)CondStack[CondStack.Count-1] )
      {
        PStream = null; return true;
      }
      if( (string)Parameters[(short)EStyxParIndex.IDX_MAC_INC] == Token )
      {
        PStream = evalInclude(ref Value);
        return PStream != null;
      }
      if( (string)Parameters[(short)EStyxParIndex.IDX_MAC_DFN] == Token )
      {
        PStream = null;
        return evalDefine(ref Value);
      }
      if( (string)Parameters[(short)EStyxParIndex.IDX_MAC_DEL] == Token )
      {
        PStream = null;
        return evalUndefine(ref Value);
      }
      string id = "", text = "";
      if( (string)Parameters[(short)EStyxParIndex.IDX_TOK_IDE] == Token )
      {
        if( MacIgnCase ) 
        {
          id = Value; 
          id = id.ToLower(); //FIXME:cultureinfo
        }
        else
        if( ignoreCase() )
        {
          error("case ignore mismatch between macros and identifier token");
          return false;
        }
        string mid = id.Length > 0 ? id : Value;
        if( MacDefines.Contains(mid) )
        { 
          string sid = "";
          text = evalMacroCall(ref mid,ref sid);
          if( text.Length > 0 )
          {
            PStream = createMacroStream(ref sid,ref text);
            return PStream != null;
          }
          PStream = null; return true;
        }
      }
      if( (string)Parameters[(short)EStyxParIndex.IDX_MAC_SEP] == Token )
      {
        setSeparator(ref Value);
        if( MacStack.Count > 0 && CurSep == 0 && CurPar.Length > 0 )
        { 
          text = evalMacroParameter(ref CurPar,ref id);
          CurPar = "";
          if( text.Length > 0 )
          {
            PStream = createMacroStream(ref id,ref text);
            return PStream != null;
          }
        }
        PStream = null; return true;
      }
      if( MacStack.Count > 0 )
      {
        if( CurSep == 0 && CurPar.Length == 0 )
        { 
          text = evalMacroParameter(ref Value,ref id);
          if( text.Length > 0 )
          {
            PStream = createMacroStream(ref id,ref text);
            return PStream != null;
          }
          PStream = null; return true;
        }
        if( partialParameter(ref Value) )
        {
          CurPar += Value; PStream = null; return true;
        }
        text = evalMacroParameter(ref CurPar,ref id);
        CurPar = "";
        if( text.Length > 0 )
        {
          PStream = createMacroStream(ref id,ref text);
          return PStream != null;
        }
        PStream = null; return true;
      }
      return true;
    }

    //! initialize scanner with preprocessing defaults.
    //! @param igncase ignore case in macro identifiers
    protected virtual void initPreprocessing(bool igncase)
    {
      MacIgnCase = igncase;
      CurSep     = 0; // space separator
      MacParDefaults = new string[15] 
      {
        "Ide", "MacDfn", "MacSep", "MacInc", "MacCond", "MacDel", 
        "#macro", "#end", "#ifdef", "#ifndef", "#else", "#include", "#undefine", 
        "PATH", "" 
      };
      Parameters = new Hashtable();
      MacDefines = new Hashtable();
      MacStack   = new ArrayList();
      CondStack  = new ArrayList();
      for( short i=0; i < (short)EStyxParIndex.IDX_PAR_END; ++i )
      {
        Parameters[i] = MacParDefaults[i];
      }
    }

    //! The constructor creates an uninitialized scanner.
    public CStyxPScanner(/*bool lahead = false, bool igncase = true*/) : base()
    {
      initPreprocessing(true);
    }

    //! The constructor creates an uninitialized scanner.
    //! @param lahead enable n character look-ahead ?
    //! @param igncase ignore case in macro identifiers
    public CStyxPScanner(bool lahead, bool igncase) : base(lahead,true)
    {
      initPreprocessing(igncase);
    }

    //! set preprocessing parameters
    //! @param parmap preprocessing parameters
    public virtual void setParameters(ref Hashtable/*short,string*/ parmap)
    {
      if( parmap == null ) return;
      IEnumerator keys = parmap.Keys.GetEnumerator();
      keys.Reset();
      while( keys.MoveNext() )
      {
        short paridx = (short)keys.Current;
        if( Parameters.Contains(paridx) )
        {
          Parameters[paridx] = parmap[paridx];
        }
      }
    }

    //! get preprocessing parameter
    //! @param paridx parameter index
    //! @return parameter value or ""
    public virtual string getParameter(short paridx)
    {
      if( Parameters.Contains(paridx) )
      {
        return (string)Parameters[paridx];
      }
      return "";
    }
  }

  //@}
  
  //@}

  //@}

}

