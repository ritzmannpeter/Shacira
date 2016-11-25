
#ifndef _asioclient_h_
#define _asioclient_h_

#ifdef USE_BOOST

#include "client.h"
#include "binaryframehandler.h"
#include "asiodriver.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/condition.hpp>
using boost::asio::ip::tcp;

#undef SIMPLE_WAITABLE_CONDITION
#ifdef SIMPLE_WAITABLE_CONDITION

class cWaitableCondition : private boost::noncopyable
{
public:
   cWaitableCondition() {}
   // set and reset the condition
   void set(bool state)
   { 
      boost::mutex::scoped_lock lock(_mutex);
      _condition.notify_one();
   }
   void waitUntilTrue(void)
   {
      boost::mutex::scoped_lock lock(_mutex); 
      _condition.wait(lock);
   }
   // Wait until condition becomes true (return true)
   // or the given timeout has elapsed (return false)
   bool timedWaitUntilTrue(unsigned long timeoutMs)
   {
      boost::mutex::scoped_lock lock(_mutex);
      boost::system_time timeInterval = convertFromMilliSec(timeoutMs);
      return _condition.timed_wait(lock, timeInterval);
   }
private:
   boost::system_time convertFromMilliSec(unsigned long timeoutMs)
   {
      boost::posix_time::time_duration duration(0, 0, timeoutMs, 4);
      boost::system_time const timeout = boost::get_system_time() + duration;
      return timeout;
   }
private:
   boost::mutex _mutex;
   boost::condition _condition;
};

#else

class cWaitableCondition : private boost::noncopyable
{
public:
   cWaitableCondition(bool autoReset = true) : _autoReset(autoReset), _condIsTrue(false) {}
   // set and reset the condition
   void set(bool state)
   { 
      boost::mutex::scoped_lock lock(_mutex);
      _condIsTrue = state;
      if (_condIsTrue ) {
           _condition.notify_one();
      }
   }
   // Wait until condition becomes true
   // If the condition has already been set the function
   // will immediately return without calling boost-wait().
   void waitUntilTrue(void)
   {
      boost::mutex::scoped_lock lock(_mutex); 
      if (!_condIsTrue) {
         // we really have to wait until someone calls
         // set(true)
         _condition.wait(lock);
      }
      if (_autoReset) {
         _condIsTrue = false;
      }
   }
   // Wait until condition becomes true (return true)
   // or the given timeout has elapsed (return false)
   bool timedWaitUntilTrue(unsigned long timeoutMs)
   {
      boost::mutex::scoped_lock lock(_mutex);
      if (!_condIsTrue) {
         boost::system_time timeInterval = convertFromMilliSec(timeoutMs);
         if (!_condition.timed_wait(lock, timeInterval)) {
            return false;
         }
      }
      if (_autoReset) {
         _condIsTrue = false;
      }
      return true;
   }
private:
   boost::system_time convertFromMilliSec(unsigned long timeoutMs)
   {
      boost::posix_time::time_duration duration(0, 0, timeoutMs, 4);
      boost::system_time const timeout = boost::get_system_time() + duration;
      return timeout;
   }
private:
   bool _autoReset;
   bool _condIsTrue;
   boost::mutex _mutex;
   boost::condition _condition;
};

#endif

class cAsioClient : public cClient
{
public:
   cAsioClient(boost::asio::io_service & io_service, cAsioDriver * driver);
   virtual ~cAsioClient();
   virtual int execute();
   virtual int send(const OCTET_T * output, LENGTH_T length);
   virtual int connect();
   inline int unlockState() {return _unlockState;};
private:
   int wait(unsigned long timeout = WAIT_FOR_EVER);
   void handle_resolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
   void handle_connect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
   void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
   void readInput();
   void handle_write_request(const boost::system::error_code& err);
private:
   boost::asio::io_service & _io_service;
   tcp::resolver _resolver;
   tcp::socket _socket;
   boost::asio::streambuf _request;
   boost::asio::streambuf _response;
   boost::thread * _thread;
   boost::mutex _waitMutex;
   cWaitableCondition _waitableCondition;
   int _unlockState;
   enum { max_length = 1024 };
   char _data[max_length];
};

#endif // USE_BOOST

#endif // _asioclient_h_
