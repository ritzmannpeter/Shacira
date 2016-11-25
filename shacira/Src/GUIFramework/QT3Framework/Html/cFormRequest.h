// cFormRequest.h: Schnittstelle für die Klasse cFormRequest.
//
//////////////////////////////////////////////////////////////////////
#ifndef CFORMREQUEST_H
#define CFORMREQUEST_H

#include "qt4port.h"
#include <qstring.h>
#include <qmap.h>

/**
  * @typedef ELEMENT_MAP_T
  * Map of formular elements. The first parameter represents the name of the element, 
  * the second respresents the value.
  */
typedef QMap<QString, QString> ELEMENT_MAP_T;
/**
  * @enum REQMETHOD Request methods.
  */
enum REQMETHOD { GET=0, POST=1 };


//---------------------------------------------------------------------
//  cFormData
//---------------------------------------------------------------------
/**
  * @brief Represents formular data sended by an HTTP request.
  * It provides methods for analysing the request string and extracting the sended informations.
  */
class cFormData
{
protected:
    /**
      * @brief Map of formular elements with name - value pairs.
      */
	ELEMENT_MAP_T	_Elements;
public:
    /**
      * @brief Constructs a cFormularData object.
      */
	cFormData();
	virtual ~cFormData();

    /**
      * @brief Gets the map of formular elements which had been sended.
      */
	ELEMENT_MAP_T& GetElements()		{ return _Elements; };
    /**
      * @brief Parses the request string and sets the properties with the appendant informations.
      */
	virtual void Parse(char* data, int lenQuery, REQMETHOD method);
};

//---------------------------------------------------------------------
//  cMultipartFormData
//---------------------------------------------------------------------
/**
  * @brief Represents multipart formular data sended by an HTTP request.
  * It provides methods for analysing the request string and extracting the sended informations.
  * 
  * For uploading file the request must be sended as multipart/form-data like:
  * <table class="no" border = "0">
  *     <tr>
  *         <td colspan="3"> \<FORM method="POST" enctype="multipart/form-data"\> </td>
  *         <td></td>
  *     </tr>
  *     <tr>
  *         <td></td>
  *         <td colspan="2">\<INPUT type="file" name="uploadFile"/></td>    		
  *     </tr>
  *     <tr>
  *         <td></td>
  *         <td colspan="2">\<INPUT type="submit" VALUE="Send"\></td>    		
  *     </tr>
  *      <tr>
  *         <td colspan="3"> \</FORM\> </td>
  *         <td></td>
  *      </tr>
  *  </table>
  */
class cMultipartFormData : public cFormData
{
protected:
     /**
      * @brief File name of upload. 
      */
	QString _FileName;
    /**
      * @brief Data of upload.
      */
	char* _UploadData;
    /**
      * @brief Length of upload data.
      */
	int _LenUpload;
    /**
      * @brief String which seperates the parts of the request.
      */
	QString _Boundary;
public:
    /**
      * @brief Constructs a cFormularData object.
      */
	cMultipartFormData();
	virtual ~cMultipartFormData();
    
    /**
      * @brief Parses the request string an setting the properties with the appendant informations.
      */
    virtual void Parse(char* data,  int lenData, REQMETHOD method);
    /**
      * @brief Gets the filename of upload. 
      * @return Returns the filename if upload data has been sended otherwise returns NULL..
      */
	QString GetFileName()				{ return _FileName; };
    /**
      * @brief Gets the pointer to the data which has been uploaded.
      * @return The pointer to the upload data.
      */
	char* GetUploadData()				{ return _UploadData; };
    /**
      * @brief Gets the length of the data which has been uploaded.
      * @return Length of upload data.
      */
	int GetLenUpload()					{ return _LenUpload; };

protected:
    /**
      * @brief Sets cMultipartFormData::_Boundary by parsing the request.
      * @throw cFormRequestException will be thrown if the boundary information could not be found.
      */
	void SetBoundary(char* data);
    /**
      * @brief Sets cMultipartFormData::_FileName by parsing the request.
      * @throw cFormRequestException will be thrown if the filename information could not be found.
      */
	void SetFileName(char* data);
    /**
      * @brief Sets cMultipartFormData::_UploadData by parsing the request.
      * @throw cFormRequestException will be thrown if the upload data information could not be found.
      */
	void SetUploadData(char* data, int lenData);
    /**
      * @brief Sets cMultipartFormData::_Elements by parsing the request.
      */
	void SetElements(char* data, int lenData, REQMETHOD method);
    /**
      * @brief Helperfunction to find data in a buffer.
      * @param buffer Buffer to search.
      * @param lenBuffer Length of the buffer.
      * @param toFind Data to find in buffer.
      * @param lenFind Length of data to find.
      * @param startIndex Index of buffer to start the search.
      * @return The position of the first occurence of toFind.
      */
	int  Find(	const char* buffer, int lenBuffer, 
				const char* toFind, int lenFind, 
				int startIndex = 0);
};

//---------------------------------------------------------------------
//  cFormRequest
//---------------------------------------------------------------------
/**
  * @brief Represents an HTTP request sending formular data.
  * It provides methods for analysing the request string and uploading data.
  */
class cFormRequest  
{
protected:
    /**
      * @brief A pointer to a form data object. 
      * This property will be set by parsing the request string.
      */
	cFormData* _Data;
    /**
      * @brief Indicates if multipart/form-data has been sended.
      *         - true: the formular data has been sended by \<form enctype="multipart/form-data"\>
      *         - false: otherwise.
      */
    bool _IsMultipart;
public:
    /**
      * @brief Construct a form request object.
      */
	cFormRequest();
    ~cFormRequest();
    /**
      * @brief Gets the pointer to the data which has been sended.
      */
	cFormData* GetFormData()			{ return _Data; };
    /**
      * @brief Indicates if multipart/form-data has been sended.
      * @return 
      *         - true: the formular data has been sended by \<form enctype="multipart/form-data"\>
      *         - false: otherwise.
      */
    bool IsMultipart()                  { return _IsMultipart; }; 
    /**
      * @brief Parses the request data.
      * Calls cFormRequest::Parse(char* data, int lenQuery, REQMETHOD method) and sets 
      * the _Data property. 
      * @param query Data sended by the request.
      * @param lenQuery Length of request data.
      * @param method Request method. Valid values are POST or GET
      */
	void Parse(char* query,  int lenQuery, REQMETHOD method);
    /**
      * @brief Loads the data up to the given path using the file name from the source file. 
      * If the directory doesn't exists it will be created. 
      * If the file already exists it will be overwritten.
      * @param path Upload directory.
      */
	void Upload(QString path);
    /**
      * @brief Converts the request to string.
      * @throw cFormRequestException
      */
	QString ToString();
    /**
      * @brief Helper for decoding the request string. 
      * Handles the seperator "+" and special characters indicated by "%".
      */
	static QString Decode(QString str);
private:
	 static char HexToChar(QChar c);
};

//---------------------------------------------------------------------
//  cFormRequestException
//---------------------------------------------------------------------
/**
  * @brief Exception thrown by the cFormRequest and cMultipartFormData classes.
  */
class cFormRequestException
{
private:
	QString _Message;
public:
    /**
      * Constructs a cFormRequestException object.
      */
	cFormRequestException();
    /**
      * Constructs a cFormRequestException object with the given message.
      */
	cFormRequestException(QString msg);
	~cFormRequestException();
    /**
      * Sets the exception message.
      */
	void SetMessage(QString msg)	{ _Message = msg; };
    /**
      * Gets the exception message.
      */
	QString GetMessage()			{ return _Message; };

};

#endif //CFORMREQUEST_H
