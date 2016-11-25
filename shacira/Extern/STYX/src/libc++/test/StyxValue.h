/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxValue.h]  Styx Term Value Implementation (C++)                      */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_VALUE_INCL
#define STYX_VALUE_INCL


#include <wctype.h>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;


namespace styx
{

  /* term value declaration ------------------------------------------------ */

  class StyxValue;

  class StyxValue
  {
  public:
    typedef unsigned char          byte;
    typedef map<string,StyxValue>  M_Value;
    typedef vector<StyxValue>      V_Value;

  protected:
    enum
    {
      VALUE_VOID, 
      VALUE_LONG, 
      VALUE_POINTER, 
      VALUE_STRING, 
      VALUE_WSTRING,
      VALUE_VECTOR,
      VALUE_MAP
    };

  protected:
    byte t;
    union 
    {
      void*      p;
      long       l;
      string*    s;
      wstring*   ws;
      M_Value*   m;
      V_Value*   v;
    } u;

    virtual void erase()
    {
      if( t == VALUE_STRING ) 
      { if( u.s ) delete u.s; u.s = 0; }
      else
      if( t == VALUE_WSTRING ) 
      { if( u.ws ) delete u.ws; u.ws = 0; }
      else
      if( t == VALUE_MAP )
      { delete u.m; u.m = 0; }
      else
      if( t == VALUE_VECTOR )
      { delete u.v; u.v = 0; }
      t = VALUE_VOID;
    }

  public:
    // constructors
    StyxValue() { t = VALUE_VOID;                }
    StyxValue(void* p)
    { t = VALUE_POINTER; u.p  = p;               }
    StyxValue(const long l)
    { t = VALUE_LONG;    u.l  = l;               }
    StyxValue(const string s)
    { t = VALUE_STRING;  u.s  = new string(s);   }
    StyxValue(const wstring ws)
    { t = VALUE_STRING;  u.ws = new wstring(ws); }
    StyxValue(const M_Value& m)
    { t = VALUE_MAP;     u.m  = new M_Value(m);  }
    StyxValue(const V_Value& v)
    { t = VALUE_VECTOR;  u.v  = new V_Value(v);  }

    StyxValue(const StyxValue& v) { *this = v;   }

    // assignment operators
    StyxValue& operator =(const StyxValue& v)
    { 
      erase();
      switch( v.t )
      {
        case VALUE_POINTER:
          t = VALUE_POINTER; u.p  = v.u.p;                break;
        case VALUE_LONG:
          t = VALUE_LONG;    u.l  = v.u.l;                break;
        case VALUE_STRING:
          t = VALUE_STRING;  u.s  = new string(*v.u.s);   break;
        case VALUE_WSTRING:
          t = VALUE_WSTRING; u.ws = new wstring(*v.u.ws); break;
        case VALUE_MAP:
          t = VALUE_MAP;     u.m  = new M_Value(*v.u.m);  break;
        case VALUE_VECTOR:
          t = VALUE_VECTOR;  u.v  = new V_Value(*v.u.v);  break;
        default:                                          break;
      };
      return *this;
    }

    StyxValue& operator= (const long l)
    { erase(); t = VALUE_LONG;    u.l  = l;               return *this; }
    StyxValue& operator= (void* p)
    { erase(); t = VALUE_POINTER; u.p  = p;               return *this; }
    StyxValue& operator= (const string s)
    { erase(); t = VALUE_STRING;  u.s  = new string(s);   return *this; }
    StyxValue& operator= (const wstring ws)
    { erase(); t = VALUE_WSTRING; u.ws = new wstring(ws); return *this; }
    StyxValue& operator= (const M_Value& m)
    { erase(); t = VALUE_MAP;     u.m  = new M_Value(m);  return *this; }
    StyxValue& operator= (const V_Value& v)
    { erase(); t = VALUE_VECTOR;  u.v  = new V_Value(v);  return *this; }

    // cast operators
    operator long&() const 
    { 
      if ( t != VALUE_LONG ) throw "illegal cast long&()";
      return (long&)u.l;
    }
    operator void*&() const 
    { 
      if ( t != VALUE_POINTER ) throw "illegal cast void*&()";
      return (void*&)u.p;
    }
    operator string&() const 
    { 
      if ( t != VALUE_STRING ) throw "illegal cast string&()";
      return *u.s;
    }
    operator wstring&() const 
    { 
      if ( t != VALUE_WSTRING ) throw "illegal cast wstring&()";
      return *u.ws;
    }
    operator M_Value&() const 
    { 
      if ( t != VALUE_MAP ) throw "illegal cast M_Value&()";
      return *u.m;
    }
    operator V_Value&() const 
    { 
      if ( t != VALUE_VECTOR ) throw "illegal cast V_Value&()";
      return *u.v;
    }

    // type predicates
    bool isVoid()    const { return t == VALUE_VOID;    }
    bool isLong()    const { return t == VALUE_LONG;    }
    bool isPointer() const { return t == VALUE_POINTER; }
    bool isString()  const { return t == VALUE_STRING;  }
    bool isWString() const { return t == VALUE_WSTRING; }
    bool isVector()  const { return t == VALUE_VECTOR;  }
    bool isMap()     const { return t == VALUE_MAP;     }

    // destructor
    virtual ~StyxValue() { erase(); }
  };

  /* term value implementation --------------------------------------------- */

}

#endif
