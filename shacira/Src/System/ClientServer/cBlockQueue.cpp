//## begin module%4105571B0128.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4105571B0128.cm

//## begin module%4105571B0128.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4105571B0128.cp

//## Module: cBlockQueue%4105571B0128; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cBlockQueue.cpp

//## begin module%4105571B0128.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4105571B0128.additionalIncludes

//## begin module%4105571B0128.includes preserve=yes
//## end module%4105571B0128.includes

// cBlockQueue
#include "System/ClientServer/cBlockQueue.h"
//## begin module%4105571B0128.additionalDeclarations preserve=yes

/// PR 30.03.06 - trying to get block after timeout period
/// PR 15.01.07 - new organization of event mechanism to avoid
///               sporadic occuring delay of tmo in GetBlock

//## end module%4105571B0128.additionalDeclarations


// Class cBlockQueue 






cBlockQueue::cBlockQueue()
  //## begin cBlockQueue::cBlockQueue%.hasinit preserve=no
      : _Channel(0)
  //## end cBlockQueue::cBlockQueue%.hasinit
  //## begin cBlockQueue::cBlockQueue%.initialization preserve=yes
  , _Queue(BLOCK_QUEUE_SIZE)
  //## end cBlockQueue::cBlockQueue%.initialization
{
  //## begin cBlockQueue::cBlockQueue%.body preserve=yes
  //## end cBlockQueue::cBlockQueue%.body
}

cBlockQueue::cBlockQueue(const cBlockQueue &right)
  //## begin cBlockQueue::cBlockQueue%copy.hasinit preserve=no
      : _Channel(0)
  //## end cBlockQueue::cBlockQueue%copy.hasinit
  //## begin cBlockQueue::cBlockQueue%copy.initialization preserve=yes
  , _Queue(BLOCK_QUEUE_SIZE)
  //## end cBlockQueue::cBlockQueue%copy.initialization
{
  //## begin cBlockQueue::cBlockQueue%copy.body preserve=yes
  //## end cBlockQueue::cBlockQueue%copy.body
}

cBlockQueue::cBlockQueue (LONG_T channel)
  //## begin cBlockQueue::cBlockQueue%1090868764.hasinit preserve=no
      : _Channel(0)
  //## end cBlockQueue::cBlockQueue%1090868764.hasinit
  //## begin cBlockQueue::cBlockQueue%1090868764.initialization preserve=yes
  , _Queue(BLOCK_QUEUE_SIZE)
  //## end cBlockQueue::cBlockQueue%1090868764.initialization
{
  //## begin cBlockQueue::cBlockQueue%1090868764.body preserve=yes
  //## end cBlockQueue::cBlockQueue%1090868764.body
}


cBlockQueue::~cBlockQueue()
{
  //## begin cBlockQueue::~cBlockQueue%.body preserve=yes
  //## end cBlockQueue::~cBlockQueue%.body
}

//## Other Operations (implementation)
BLOCK_T * cBlockQueue::GetBlock (ULONG_T tmo)
{
  //## begin cBlockQueue::GetBlock%1090868765.body preserve=yes
   BLOCK_T * block = NULL;
   _Mutex.request();
   if (_Queue.isEmpty()) {
      _Event.reset();
      _Mutex.release();
      if (_Event.wait(tmo)) {
         block = _Queue.get();
      } else {
         return NULL;
      }
   } else {
      _Mutex.release();
      block = _Queue.get();
   }
   return block;
  //## end cBlockQueue::GetBlock%1090868765.body
}

void cBlockQueue::Flush ()
{
  //## begin cBlockQueue::Flush%1090946394.body preserve=yes
   _Mutex.request();
   BLOCK_T * block = NULL;
   while (!_Queue.isEmpty()) {
      block = _Queue.get();
      DeleteBlock(block);
   }
   _Mutex.release();
  //## end cBlockQueue::Flush%1090946394.body
}

void cBlockQueue::SetBlock (PTR_T block, ULONG_T block_size)
{
  //## begin cBlockQueue::SetBlock%1090868766.body preserve=yes
   _Mutex.request();
   BLOCK_T * elem = CreateBlock(block, block_size);
   _Queue.put(elem);
   _Event.set();
   _Mutex.release();
  //## end cBlockQueue::SetBlock%1090868766.body
}

void cBlockQueue::ReleaseBlock (BLOCK_T *block)
{
  //## begin cBlockQueue::ReleaseBlock%1090910860.body preserve=yes
   DeleteBlock(block);
  //## end cBlockQueue::ReleaseBlock%1090910860.body
}

BLOCK_T * cBlockQueue::CreateBlock (PTR_T block, ULONG_T block_size)
{
  //## begin cBlockQueue::CreateBlock%1090910858.body preserve=yes
   BLOCK_T * new_block = (BLOCK_T*)calloc(1, sizeof(BLOCK_T));
   PTR_T buf = calloc(1, block_size);
   memcpy(buf, block, block_size);
   new_block->block = buf;
   new_block->block_size = block_size;
   return new_block;
  //## end cBlockQueue::CreateBlock%1090910858.body
}

void cBlockQueue::DeleteBlock (BLOCK_T *block)
{
  //## begin cBlockQueue::DeleteBlock%1090910859.body preserve=yes
   free(block->block);
   free(block);
  //## end cBlockQueue::DeleteBlock%1090910859.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cBlockQueue::get_Channel () const
{
  //## begin cBlockQueue::get_Channel%41055773034B.get preserve=no
  return _Channel;
  //## end cBlockQueue::get_Channel%41055773034B.get
}

// Additional Declarations
  //## begin cBlockQueue%4105571B0128.declarations preserve=yes
  //## end cBlockQueue%4105571B0128.declarations

//## begin module%4105571B0128.epilog preserve=yes
//## end module%4105571B0128.epilog
