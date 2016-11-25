// cFormRequest.cpp: Implementierung der Klasse cFormRequest.
//
//////////////////////////////////////////////////////////////////////
#include "cFormRequest.h"
#include <qstringlist.h>
#include <qdir.h>

//---------------------------------------------------------------------
//  cFormData
//---------------------------------------------------------------------
cFormData::cFormData()
: _Elements()
{
}

cFormData::~cFormData()
{
}

void cFormData::Parse(char* data,  int lenData, REQMETHOD method)
{
   QString query = data;
#ifdef QT4
   QStringList	list = query.split("&");
   for ( QStringList::Iterator it = list.begin(); it != list.end(); ++it ) {
		QStringList token = (*it).split("=");
		QString key = (token.at(0)).simplified();
		QString value = (token.at(1)).simplified();
		if(method == POST) value = cFormRequest::Decode(value);
		_Elements[key] = value;
	}
#else
   QStringList	list = QStringList::split("&", query);
   for ( QStringList::Iterator it = list.begin(); it != list.end(); ++it ) {
		QStringList token = QStringList::split("=", (*it));
		QString key = (*token.at(0)).stripWhiteSpace();
		QString value = (*token.at(1)).stripWhiteSpace();
		if(method == POST) value = cFormRequest::Decode(value);
		_Elements[key] = value;
	}
#endif
}


//---------------------------------------------------------------------
//  cMultipartFormData
//---------------------------------------------------------------------
cMultipartFormData::cMultipartFormData()
: _FileName(), _Boundary(), _UploadData(NULL), _LenUpload(-1)
{
}

cMultipartFormData::~cMultipartFormData()
{
	if(_UploadData != NULL) delete [] _UploadData;
}

void cMultipartFormData::Parse(char* data,  int lenData, REQMETHOD method)
{
    SetBoundary(data);
	SetFileName(data);
	SetUploadData(data, lenData);
	SetElements(data, lenData, method);
}

void cMultipartFormData::SetFileName(char* data)
{
	QString query = data;
	QString file_name = "filename=\"";
#ifdef QT4
   int pos = query.indexOf(file_name);
	if(pos != -1){
		pos += file_name.length(); 
		_FileName = query.right(query.length() - pos);
		pos = _FileName.indexOf("\"");
		_FileName = _FileName.left(pos);
		pos = _FileName.indexOf("\\");
		if (pos != -1) _FileName = _FileName.right(_FileName.length() - (pos + 1));
		_Elements["datei"] = _FileName;
	} else {
		throw cFormRequestException("Invalid Format. ");
	}
#else
   int pos = query.find(file_name);
	if(pos != -1){
		pos += file_name.length(); 
		_FileName = query.right(query.length() - pos);
		pos = _FileName.find("\"");
		_FileName = _FileName.left(pos);
		pos = _FileName.findRev("\\");
		if (pos != -1) _FileName = _FileName.right(_FileName.length() - (pos + 1));
		_Elements["datei"] = _FileName;
	} else {
		throw cFormRequestException("Invalid Format. ");
	}
#endif
}

void cMultipartFormData::SetUploadData(char* data, int lenData)
{
#ifdef QT4
   QString query(data);
	int pos = query.indexOf("Content-Type:");
	QString ct;
	if(pos != -1){
		pos += 14;
		ct = query.right(query.length() - pos);
		int pos1 = ct.indexOf("\n");
		if(pos == -1) ct.indexOf("\r\n");
		if(pos != -1){
			ct = ct.left(pos1 - 1);
		} else {
			throw cFormRequestException("Uploadata not found. ");
		}
	} else {
		throw cFormRequestException("FileType not found. ");
	}
   int begin = query.indexOf(ct) + ct.length();
	begin += strlen("\r\n\r\n");
	int lenBuffer = lenData - begin;
	char* buffer = new char[lenBuffer];
	memcpy(buffer, &data[begin], lenBuffer);
	_LenUpload = Find(buffer, lenBuffer, CONST_STRING(_Boundary), _Boundary.length());
	if(_LenUpload != -1) {
		_LenUpload -= strlen("\r\n");
		_UploadData = new char[_LenUpload];
		memcpy(_UploadData, buffer, _LenUpload);
	}
	delete [] buffer;
#else
   QString query(data);
	int pos = query.find("Content-Type:");
	QString ct;
	if(pos != -1){
		pos += 14;
		ct = query.right(query.length() - pos);
		int pos1 = ct.find("\n");
		if(pos == -1) ct.find("\r\n");
		if(pos != -1){
			ct = ct.left(pos1 - 1);
		} else {
			throw cFormRequestException("Uploadata not found. ");
		}
	} else {
		throw cFormRequestException("FileType not found. ");
	}
   int begin = query.find(ct) + ct.length();
	begin += strlen("\r\n\r\n");
	int lenBuffer = lenData - begin;
	char* buffer = new char[lenBuffer];
	memcpy(buffer, &data[begin], lenBuffer);
	_LenUpload = Find(buffer, lenBuffer, (const char*)_Boundary, _Boundary.length());
	if(_LenUpload != -1) {
		_LenUpload -= strlen("\r\n");
		_UploadData = new char[_LenUpload];
		memcpy(_UploadData, buffer, _LenUpload);
	}
	delete [] buffer;
#endif
}


void cMultipartFormData::SetElements(char* data, int lenData, REQMETHOD method)
{
	QString disp = "Content-Disposition: form-data; name=\"";
	int beginKey = -1;
	int endKey = -1;
	int beginValue = -1;
	int endValue = -1;
	
	beginKey = Find(data , lenData, CONST_STRING(disp), disp.length());
	while(beginKey != -1){
		beginKey += disp.length() + 1;
		endKey = Find(data, lenData, "\"", 1, beginKey);
		if(endKey != -1) {
			int lenKey = (endKey - beginKey) + 1;
			char* key = new char[lenKey + 1];
			memset(key, 0, lenKey + 1);
			memcpy(key, &data[beginKey - 1], lenKey);
			if(strcmp(key, "datei") != 0) {
				beginValue = endKey + 1 + strlen("\r\n\r\n");
				if( beginValue > 0) {
					endValue = Find(data, lenData, CONST_STRING(_Boundary), _Boundary.length(), beginValue + 1);
					if( endValue != -1) {
						int lenValue = (endValue - strlen("\r\n") - beginValue); 
						char* value = new char[lenValue + 1];
						memset(value, 0, lenValue + 1);
						memcpy(value, &data[beginValue], lenValue);
						_Elements[key] = value;
						delete [] value;
					}
				}
			}
			delete [] key;
			beginKey = Find(data , lenData, CONST_STRING(disp), disp.length(), beginKey);
		} else {
			beginKey = -1;
		}
	}
}

void cMultipartFormData::SetBoundary(char* data)
{
	QString query = data;
#ifdef QT4
   int pos = query.indexOf("Content-Disposition:");
#else
   int pos = query.find("Content-Disposition:");
#endif
   if(pos != -1) {
		_Boundary += query.left(pos - 2);
	} else {
		throw cFormRequestException("Boundary not found. ");
	}
}

int cMultipartFormData::Find(const char* buffer, int lenBuffer, 
					         const char* toFind, int lenFind, int startIndex)
{
	int pos = 0;
	char *hit = 0;

	if(startIndex >= lenBuffer) return -1;
	for(int j = startIndex; j < lenBuffer; j++) { 
		hit = (char*)memchr( &buffer[j], toFind[0], lenBuffer - startIndex);
		if(hit != 0) {
			pos = hit - buffer;
			j = pos + 1;
			if(lenFind == 1) return pos;
			for(int i = 1; i < lenFind; i++) {
				if( buffer[j] != toFind[i] ) break;
				if( i == lenFind - 1 ) return pos;
				j++;
			}	
		} 
	}
	return -1;
}


//---------------------------------------------------------------------
//  cFormRequest
//---------------------------------------------------------------------
cFormRequest::cFormRequest()
: _Data(NULL), _IsMultipart(false)
{
}

cFormRequest::~cFormRequest()
{
	if (_Data != NULL) delete _Data;
}


void cFormRequest::Parse(char* data, int lenQuery, REQMETHOD method)
{
    QString query = data;
#ifdef QT4
    if(query.indexOf("Content-Disposition:") != -1) {
#else
    if(query.find("Content-Disposition:") != -1) {
#endif
       _Data = new cMultipartFormData(); 
        _IsMultipart = true;
    } else {
        _Data = new cFormData();
    }
	_Data->Parse(data, lenQuery, method);
}

QString cFormRequest::Decode (QString str)
{
	QString res = "";
	for (unsigned int i = 0; i < str.length(); ++i) {
		if ( str.at(i) == '%' ) {
			char c = HexToChar( str.at(i+1) ) * 16 + HexToChar( str.at(i + 2) );
			res.append(c);
			i = i + 2;
		} else if ( str.at(i) == '+' ) {
			res.append(' ');
		} else {
			res.append(str.at(i));
		}
	}
	return res;
}

char cFormRequest::HexToChar ( QChar c )
{
#if QT_VERSION >= QT_VERSION_CHECK(4,0,0)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   // ??
   char ch = c.toLatin1();
#else
   char ch = c.toAscii();
#endif
   if (('0' <= ch) && (ch <= '9')) return ch -'0';
	else if (('a' <= ch) && (ch <= 'f')) return ch - 'a' + 10;
	else if (('A' <= ch) && (ch <= 'F')) return ch - 'A' + 10;
	else return 0;
#else
   if (('0' <= c) && (c <= '9')) return c -'0';
	else if (('a' <= c) && (c <= 'f')) return c - 'a' + 10;
	else if (('A' <= c) && (c <= 'F')) return c - 'A' + 10;
	else return 0;
#endif
}

QString cFormRequest::ToString()
{
   QString result;
#ifdef QT4
	ELEMENT_MAP_T field_map = _Data->GetElements();
	ELEMENT_MAP_T::Iterator it;
	for ( it = field_map.begin(); it != field_map.end(); ++it ) {
		if(it.key() != NULL) result += it.key();
		if(it.value() != NULL) {
			result += "=";
			result += it.value();
		}
		result += ";";
	}
#else
	ELEMENT_MAP_T field_map = _Data->GetElements();
	ELEMENT_MAP_T::Iterator it;
	for ( it = field_map.begin(); it != field_map.end(); ++it ) {
		if(it.key() != NULL) result += it.key();
		if(it.data() != NULL) {
			result += "=";
			result += it.data();
		}
		result += ";";
	}
#endif
   return result;
}


void cFormRequest::Upload(QString path)
{
    if(!_IsMultipart) return;
    QDir d(path);
    if (!d.exists()) {
		if(!d.mkdir(path)) {
			QString msg = "Upload directory: " + path +  " could not be created.";
			throw cFormRequestException(msg);
		}
	}
	if(!path.endsWith("/")) path += "/";
	path += ((cMultipartFormData*)_Data)->GetFileName();
	QFile file(path);

	int len = ((cMultipartFormData*)_Data)->GetLenUpload();
	char* data = ((cMultipartFormData*)_Data)->GetUploadData();
#ifdef QT4
   if(file.open(QIODevice::WriteOnly)){
		file.write(data, len);
		file.close();
	}
#else
   if(file.open(IO_WriteOnly)){
		file.writeBlock(data, len);
		file.close();
	}
#endif
}

//---------------------------------------------------------------------
//  cFormRequestException
//---------------------------------------------------------------------
cFormRequestException::cFormRequestException()
: _Message()
{
}

cFormRequestException::cFormRequestException(QString msg)
: _Message(msg)
{
}

cFormRequestException::~cFormRequestException()
{
}
