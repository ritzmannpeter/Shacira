
#ifndef __cInstall_h__
#define __cInstall_h__

#include "System/Config/cConfigurationObject.h"


typedef enum {WIN95,WIN98,WINME, WINNT, WIN2000, WINXP, LINUX} Systems;

class cSystem
{
private:
   cConfigurationObject * _ConfigObj;
public:
   cSystem();
   virtual ~cSystem();
   Systems SystemType();
   STRING_T SystemDir();
   STRING_T ProgDir();
private:
};

class cPath
{
private:
   cConfigurationObject * _ConfigObj;
public:
   cPath();
   virtual ~cPath();
   void Add(const char * path);
   void Set();
private:
};

class cVolume
{
private:
   cConfigurationObject * _ConfigObj;
   STRING_T _Source;
   ULONG_T _MaxVolumeSize;
public:
   cVolume();
   virtual ~cVolume();
   void SetSource();
   STRING_T Source();
   void Create();
private:
};

class cSourceTree
{
private:
   cConfigurationObject * _ConfigObj;
public:
   cSourceTree();
   virtual ~cSourceTree();
   void SetSource();
   STRING_T Source();
private:
};

class cInstallDest
{
private:
   cConfigurationObject * _ConfigObj;
public:
   cInstallDest();
   virtual ~cInstallDest();
   void SetSource();
   STRING_T Source();
private:
};

#endif
