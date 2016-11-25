
#ifndef _xmlstruct_h_
#define _xmlstruct_h_

#include "commstruct.h"
#include "bytebuffer.h"

class COMM_EXPORT XMLComponent
{
public:
   XMLComponent()
   {
      increment();
   };
   virtual ~XMLComponent()
   {
      decrement();
   };
   void increment();
   void decrement();
   int componentCount();
   int structCount();
};

class TimeStamp : public XMLComponent
{
public:
   TimeStamp()
   {
   };
   TimeStamp(const string & text)
      : _text(text)
   {
   };
   inline string & text() {return _text;};
private:
   string _text;
};

class Address : public XMLComponent
{
public:
   Address()
   {
   };
   Address(const string & ident, const string & ipAddress)
      : _ident(ident), _ipAddress(ipAddress)
   {
   };
   virtual ~Address()
   {
   };
   inline string & ident() {return _ident;};
   inline string & ipAddress() {return _ipAddress;};
private:
   string _ident;
   string _ipAddress;
};

class VariableSpecification : public XMLComponent
{
public:
   VariableSpecification() : _type(Reference)
   {
   };
   virtual ~VariableSpecification()
   {
   };
   enum SpecificationType {Reference, QualifiedSpecification};
   inline SpecificationType & type() {return _type;};
protected:
   SpecificationType _type;
};
typedef list<VariableSpecification*> VariableSpecificationList;


class Response : public XMLComponent
{
public:
   enum ResponseState {Success, Error};
public:
   Response()
   {
   };
   Response(ResponseState responseState, int errorCode, const string & errorText)
      : _responseState(responseState), _errorCode(errorCode), _errorText(errorText)
   {
   };
   virtual ~Response()
   {
   };
   string stateText() const
   {
      switch (_responseState) {
      case Success: return "Success";
      case Error: return "Error";
      }
      return "?";
   };
   static ResponseState responseStateFromText(const string & text)
   {
      if (text == "Success") {
         return Success;
      } else if (text == "Error") {
         return Error;
      }
      return Error;
   };
   inline ResponseState & responseState() {return _responseState;};
   inline int & errorCode() {return _errorCode;};
   inline string & errorText() {return _errorText;};
private:
   ResponseState _responseState;
   int _errorCode;
   string _errorText;
};

class Value : public XMLComponent
{
public:
   Value()
   {
   };
   Value(const string & value)
   {
      _buffer = buffer(value);
   };
   virtual ~Value()
   {
   };
   bool empty() const
   {
      return (_buffer.size() == 0);
   };
   inline cByteBuffer buffer()
   {
      return _buffer;
   };
   string value() const
   {
      string value;
      if (!empty()) {
         value = (const char*)_buffer.data();
      }
      return value;
   };
   inline string text() const
   {
      return value();
   };
private:
   cByteBuffer buffer(const string & value)
   {
      return cByteBuffer((OCTET_T *)value.c_str(), value.size());
   }
private:
   cByteBuffer _buffer;
};

class QualifiedVariableSpecification : public VariableSpecification
{
public:
   QualifiedVariableSpecification()
   {
      _type = QualifiedSpecification;
   };
   QualifiedVariableSpecification(const string & variableName, int index1 = -1, int index2 = -1, int index3 = -1, int index4 = -1)
      : _variableName(variableName),
        _index1(index1),
        _index2(index2),
        _index3(index3),
        _index4(index4)
   {
      _type = QualifiedSpecification;
   };
   virtual ~QualifiedVariableSpecification()
   {
   };
   inline string & variableName() {return _variableName;};
   inline int & index1() {return _index1;};
   inline int & index2() {return _index2;};
   inline int & index3() {return _index3;};
   inline int & index4() {return _index4;};
   inline string specification() const
   {
      string spec = _variableName;
      if (_index1 != -1) {
         spec += "[";
         spec += itos(_index1);
         spec += "]";
      }
      if (_index2 != -1) {
         spec += "[";
         spec += itos(_index2);
         spec += "]";
      }
      if (_index3 != -1) {
         spec += "[";
         spec += itos(_index3);
         spec += "]";
      }
      if (_index4 != -1) {
         spec += "[";
         spec += itos(_index4);
         spec += "]";
      }
      return spec;
   };
private:
   string _variableName;
   int _index1;
   int _index2;
   int _index3;
   int _index4;
};

class VariableReference : public VariableSpecification
{
public:
   VariableReference()
   {
      _type = Reference;
   };
   VariableReference(const string & reference)
      : _reference(reference)
   {
      _type = Reference;
   };
   virtual ~VariableReference()
   {
   };
   inline string & reference() {return _reference;};
   inline string specification() const
   {
      return _reference;
   };
private:
   string _reference;
};

class Request : public XMLComponent
{
public:
   Request()
      : _sender(NULL), _destination(NULL)
   {
   };
   Request(Address * sender, Address * destination)
      : _sender(sender), _destination(destination)
   {
   };
   virtual ~Request()
   {
      if (_sender != NULL) {
         delete _sender;
      }
      if (_destination != NULL) {
         delete _destination;
      }
   };
   inline Address * sender() const {return _sender;};
   inline Address * destination() const {return _destination;};
private:
   Address * _sender;
   Address * _destination;
};

class Reply : public XMLComponent
{
public:
   Reply()
      : _sender(NULL), _destination(NULL), _response(NULL)
   {
   };
   Reply(Address * sender, Address * destination, Response * response)
      : _sender(sender), _destination(destination), _response(response)
   {
   };
   virtual ~Reply()
   {
      if (_sender != NULL) {
         delete _sender;
      }
      if (_destination != NULL) {
         delete _destination;
      }
      if (_response != NULL) {
         delete _response;
      }
   };
   inline Address * sender() const {return _sender;};
   inline Address * destination() const {return _destination;};
   inline Response * response() const {return _response;};
private:
   Address * _sender;
   Address * _destination;
   Response * _response;
};

class DataRequest : public Request
{
public:
   DataRequest()
      : _timeStamp(NULL)
   {
   };
   DataRequest(Address * sender, Address * destination, TimeStamp * timeStamp)
      : Request(sender, destination), _timeStamp(timeStamp)
   {
   };
   virtual ~DataRequest()
   {
      VariableSpecificationList::const_iterator i = _variableSpecificationList.begin();
      while (i != _variableSpecificationList.end()) {
         VariableSpecification * spec = (*i);
         delete spec;
         i++;
      }
      if (_timeStamp != NULL) {
         delete _timeStamp;
      }
   };
   void add(VariableReference * reference)
   {
      _variableSpecificationList.push_back(reference);
   }
   void add(QualifiedVariableSpecification * specification)
   {
      _variableSpecificationList.push_back(specification);
   }
   inline VariableSpecificationList & variableSpecificationList() {return _variableSpecificationList;};
   inline TimeStamp * timeStamp() {return _timeStamp;};
private:
   VariableSpecificationList _variableSpecificationList;
   TimeStamp * _timeStamp;
};

class EventRequest : public Request
{
public:
   EventRequest()
      : _timeStamp(NULL)
   {
   };
   EventRequest(Address * sender, Address * destination, TimeStamp * timeStamp)
      : Request(sender, destination), _timeStamp(timeStamp)
   {
   };
   virtual ~EventRequest()
   {
      if (_timeStamp != NULL) {
         delete _timeStamp;
      }
   };
   inline TimeStamp * timeStamp() const {return _timeStamp;};
private:
   TimeStamp * _timeStamp;
};

class Data : public XMLComponent
{
public:
   Data()
      : _variableReference(NULL), _qualifiedVariableSpecification(NULL), _value(NULL)
   {
   };
   Data(VariableReference * variableReference, Value * value)
      : _variableReference(variableReference), _qualifiedVariableSpecification(NULL), _value(value)
   {
   };
   Data(QualifiedVariableSpecification * qualifiedVariableSpecification, Value * value)
      : _variableReference(NULL), _qualifiedVariableSpecification(qualifiedVariableSpecification), _value(value)
   {
   };
   virtual ~Data()
   {
      if (_variableReference != NULL) {
         delete _variableReference;
      }
      if (_qualifiedVariableSpecification != NULL) {
         delete _qualifiedVariableSpecification;
      }
      if (_value != NULL) {
         delete _value;
      }
   }
   inline string specification() const
   {
      if (_variableReference != NULL) {
         return _variableReference->specification();
      }
      if (_qualifiedVariableSpecification != NULL) {
         return _qualifiedVariableSpecification->specification();
      }
      return "?";
   };
   inline string valueText() const
   {
      if (_value != NULL) {
         return _value->text();
      }
      return "?";
   };
   inline VariableReference * variableReference() const {return _variableReference;};
   inline QualifiedVariableSpecification * qualifiedVariableSpecification() const {return _qualifiedVariableSpecification;};
   inline Value * value() const {return _value;};
private:
   VariableReference * _variableReference;
   QualifiedVariableSpecification * _qualifiedVariableSpecification;
   Value * _value;
};
typedef list<Data*> DataList;

class SetDataRequest : public Request
{
public:
   SetDataRequest()
   {
   };
   SetDataRequest(Address * sender, Address * destination)
      : Request(sender, destination)
   {
   };
   virtual ~SetDataRequest()
   {
      DataList::const_iterator i = _dataList.begin();
      while (i != _dataList.end()) {
         Data * data = (*i);
         delete data;
         i++;
      }
   };
   void add(Data * data)
   {
      _dataList.push_back(data);
   }
   inline DataList & dataList() {return _dataList;};
private:
   DataList _dataList;
};

class DataReply : public Reply
{
public:
   DataReply()
   {
   };
   DataReply(Address * sender, Address * destination, Response * response)
      : Reply(sender, destination, response)
   {
   };
   virtual ~DataReply()
   {
      DataList::const_iterator i = _dataList.begin();
      while (i != _dataList.end()) {
         Data * data = (*i);
         delete data;
         i++;
      }
   };
   void add(Data * data)
   {
      _dataList.push_back(data);
   }
   inline DataList & dataList() {return _dataList;};
private:
   DataList _dataList;
};

class SetDataReply : public Reply
{
public:
   SetDataReply(Address * sender, Address * destination, Response * response)
      : Reply(sender, destination, response)
   {
   };
   virtual ~SetDataReply()
   {
   };
};

class EventReply : public Reply
{
public:
   EventReply(Address * sender, Address * destination, Response * response)
      : Reply(sender, destination, response)
   {
   };
   virtual ~EventReply()
   {
   };
};

enum State {on, off};
enum DataType {TNumeric, TString, TBinary, TImage};
enum Compression {base64, zip, gzip, uncompressed};
enum ImageType {jpg, png, gif, bmp, wmf};

class COMM_EXPORT cXMLStruct : public cCommStruct
{
public:
   cXMLStruct();
   cXMLStruct(const string & text);
   cXMLStruct(DataRequest * request);
   cXMLStruct(SetDataRequest * request);
   cXMLStruct(EventRequest * request);
   cXMLStruct(DataReply * reply);
   cXMLStruct(SetDataReply * reply);
   cXMLStruct(EventReply * reply);
   virtual ~cXMLStruct();
   virtual int serialize(cByteBuffer & buffer);
   inline DataRequest * dataRequest() const {return _dataRequest;};
   inline SetDataRequest * setDataRequest() const {return _setDataRequest;};
   inline EventRequest * eventRequest() const {return _eventRequest;};
   inline DataReply * dataReply() const {return _dataReply;};
   inline SetDataReply * setDataReply() const {return _setDataReply;};
   inline EventReply * eventReply() const {return _eventReply;};
   inline bool isRequest() const
   {
      if (_dataRequest != NULL ||
          _setDataRequest != NULL ||
          _eventRequest != NULL) {
         return true;
      } else {
         return false;
      }
   };
   inline bool isReply() const
   {
      if (_dataReply != NULL ||
          _setDataReply != NULL ||
          _eventReply != NULL) {
         return true;
      } else {
         return false;
      }
   };
   inline std::string text() const {return _text;};
   static int _count;
   static int _componentCount;
public:
   static cXMLStruct * construct(const OCTET_T * data, LENGTH_T dataLength);
private:
   static cXMLStruct * constructFromDocument(const string & data);
   bool createDocument(string & data);
private:
   DataRequest * _dataRequest;
   SetDataRequest * _setDataRequest;
   EventRequest * _eventRequest;
   DataReply * _dataReply;
   SetDataReply * _setDataReply;
   EventReply * _eventReply;
   std::string _text;
};

#endif // _xmlstruct_h_
