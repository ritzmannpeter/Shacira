//## begin module%3C4EE4B900CF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE4B900CF.cm

//## begin module%3C4EE4B900CF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE4B900CF.cp

//## Module: cProxyTable%3C4EE4B900CF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyTable.h

#ifndef cProxyTable_h
#define cProxyTable_h 1

//## begin module%3C4EE4B900CF.includes preserve=yes
//## end module%3C4EE4B900CF.includes


class __DLL_EXPORT__ cCellProxy;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cChannelProxy;

//## begin module%3C4EE4B900CF.additionalDeclarations preserve=yes
//## end module%3C4EE4B900CF.additionalDeclarations


//## begin cProxyTable%3C4EE4B900CF.preface preserve=yes
//## end cProxyTable%3C4EE4B900CF.preface

//## Class: cProxyTable%3C4EE4B900CF
//## Category: System::Comm%3A8CE33700FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C551CC60357;cChannelProxy { -> F}
//## Uses: <unnamed>%3D04D34C0320;cConvUtils { -> F}
//## Uses: <unnamed>%3DCABCE203B0;cCellProxy { -> F}
//## Uses: <unnamed>%3DCBA5B90126;cObjectLock { -> F}

class __DLL_EXPORT__ cProxyTable 
{
  //## begin cProxyTable%3C4EE4B900CF.initialDeclarations preserve=yes
public:
  //## end cProxyTable%3C4EE4B900CF.initialDeclarations

    //## Constructors (generated)
      cProxyTable();

      cProxyTable(const cProxyTable &right);

    //## Destructor (generated)
      virtual ~cProxyTable();


    //## Other Operations (specified)
      //## Operation: Proxy%1011794629
      cProxy * Proxy (CONST_STRING_T name);

      //## Operation: CellProxy%1011861108
      cCellProxy * CellProxy (CONST_STRING_T name);

      //## Operation: ChannelProxy%1011948773
      cChannelProxy * ChannelProxy (CONST_STRING_T name);

      //## Operation: SetProxy%1011794627
      void SetProxy (cProxy *proxy);

  public:
    // Additional Public Declarations
      //## begin cProxyTable%3C4EE4B900CF.public preserve=yes
      //## end cProxyTable%3C4EE4B900CF.public

  protected:
    // Data Members for Associations

      //## Association: Orb::<unnamed>%3C556229004C
      //## Role: cProxyTable::Proxies%3C55622902FF
      //## Qualifier: name%3C5562700301; STRING_T
      //## begin cProxyTable::Proxies%3C55622902FF.role preserve=no  public: cProxy { -> 0..nRFHN}
      std::map<STRING_T, cProxy*> _Proxies;
      //## end cProxyTable::Proxies%3C55622902FF.role

    // Additional Protected Declarations
      //## begin cProxyTable%3C4EE4B900CF.protected preserve=yes
      //## end cProxyTable%3C4EE4B900CF.protected

  private:
    // Additional Private Declarations
      //## begin cProxyTable%3C4EE4B900CF.private preserve=yes
      //## end cProxyTable%3C4EE4B900CF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: TableMutex%3DCBA5260110
      //## begin cProxyTable::TableMutex%3DCBA5260110.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _TableMutex;
      //## end cProxyTable::TableMutex%3DCBA5260110.attr

    // Additional Implementation Declarations
      //## begin cProxyTable%3C4EE4B900CF.implementation preserve=yes
      //## end cProxyTable%3C4EE4B900CF.implementation

};

//## begin cProxyTable%3C4EE4B900CF.postscript preserve=yes
//## end cProxyTable%3C4EE4B900CF.postscript

// Class cProxyTable 

//## begin module%3C4EE4B900CF.epilog preserve=yes
//## end module%3C4EE4B900CF.epilog


#endif
