
#ifdef USE_BOOST

#include "asioclient.h"

cAsioClient::cAsioClient(boost::asio::io_service & io_service, cAsioDriver * driver)
    : cClient(driver),
      _resolver(io_service),
      _socket(io_service),
      _io_service(io_service),
      _unlockState(0)
{
   _thread = new boost::thread(boost::bind(&cAsioClient::execute, this));
}

cAsioClient::~cAsioClient()
{
   if (_thread != NULL) {
      delete _thread;
   }
}

int cAsioClient::execute()
{
   while (true) {
      connect();
      _io_service.run();
      _io_service.reset();
      _connected = false;
      _terminated = true;
   }
   return 0;
}

int cAsioClient::send(const OCTET_T * output, LENGTH_T length)
{
   cByteBuffer::show("->", output, length);
   cByteBuffer byteBuffer;
   _service->frameHandler()->pack(output, length, byteBuffer);
   std::ostream request_stream(&_request);
   request_stream.write((const char*)byteBuffer.data(), (int)byteBuffer.size());
   boost::asio::async_write(_socket, _request,
                            boost::bind(&cAsioClient::handle_write_request, this,
                                        boost::asio::placeholders::error));
//   return wait();
//   return wait(10000);
   return wait(100);
}

int cAsioClient::connect()
{
   if (_connected) {
      return 0;
   }
   // Start an asynchronous resolve to translate the server and service names
   // into a list of endpoints.
   cAsioDriver * driver = static_cast<cAsioDriver*>(_driver);
   std::string host = driver->host();
   short port = driver->port();
   std::string portText = itos(port);
   tcp::resolver::query query(tcp::v4(), host, portText);
   _resolver.async_resolve(query,
                           boost::bind(&cAsioClient::handle_resolve, this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::iterator));
   return 0;
}



int cAsioClient::wait(unsigned long timeout)
{
   int rc = 0;
   bool success = true;
   if (timeout == WAIT_FOR_EVER) {
      _waitableCondition.waitUntilTrue();
      rc = unlockState();
   } else {
      success = _waitableCondition.timedWaitUntilTrue(timeout);
      if (success) {
         rc = unlockState();
      } else {
         rc = -1;
      }
   }
   return rc;
}

void cAsioClient::handle_resolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator)
{
   if (!err) {
      // Attempt a connection to the first endpoint in the list. Each endpoint
      // will be tried until we successfully establish a connection.
      tcp::endpoint endpoint = * endpoint_iterator;
      _socket.async_connect(endpoint,
                            boost::bind(&cAsioClient::handle_connect, this,
//                            boost::asio::placeholders::error, ++endpoint_iterator));
                            boost::asio::placeholders::error, endpoint_iterator));
   } else {
      std::cout << "Error: " << err.message() << "\n";
   }
}

void cAsioClient::handle_connect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator)
{
   if (!err) {
      cout << "connected !" << endl;
      _connected = true;
      readInput();
#ifdef lassma
   } else if (endpoint_iterator != tcp::resolver::iterator()) {
      _connected = false;
      // The connection failed. Try the next endpoint in the list.
      _socket.close();
      tcp::endpoint endpoint = *endpoint_iterator;
      _socket.async_connect(endpoint,
                            boost::bind(&cAsioClient::handle_connect, this,
                                        boost::asio::placeholders::error, ++endpoint_iterator));
#endif
   } else {
      std::cout << "Error: " << err.message() << " retry connect\n";
      _connected = false;
      Sleep(2000);
      // Attempt a connection to the first endpoint in the list. Each endpoint
      // will be tried until we successfully establish a connection.
      _socket.close();
      tcp::endpoint endpoint = * endpoint_iterator;
      _socket.async_connect(endpoint,
                            boost::bind(&cAsioClient::handle_connect, this,
                            boost::asio::placeholders::error, endpoint_iterator));
   }
}

void cAsioClient::handle_read(const boost::system::error_code& err, size_t bytes_transferred)
{
   if (!err) {
      cByteBuffer frameBuffer;
      cFrameHandler * frameHandler = _service->frameHandler();
      bool frameReceived = frameHandler->add((unsigned char*)&_data, (int)bytes_transferred, frameBuffer);
      if (frameReceived) {
         LENGTH_T frameLength = frameBuffer.size();
         const OCTET_T * frame = frameBuffer.data();
         _receiveBuffer = frameBuffer;
         _receiveBuffer.show("<-");
         _unlockState = 0;
         _waitableCondition.set(true);
      }
      // read more response data
      readInput();
   } else {
      _connected = false;
      _unlockState = -1;
      _waitableCondition.set(true);
      std::cout << "Error: " << err << "\n";
   }
}

void cAsioClient::readInput()
{
   _socket.async_read_some(boost::asio::buffer(_data, max_length),
                           boost::bind(&cAsioClient::handle_read, this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

void cAsioClient::handle_write_request(const boost::system::error_code& err)
{
   if (!err) {
   } else {
      _connected = false;
      _unlockState = -1;
      _waitableCondition.set(true);
      std::cout << "Error: " << err.message() << "\n";
   }
}

#endif USE_BOOST
