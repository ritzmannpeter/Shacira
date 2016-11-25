

#ifndef _cguievents_h_
#define _cguievents_h_

#include <qevent.h>
#include <qmessagebox.h>
#include "CWidgetBase.h"

class cCommEvent : public QEvent
{
public:
   cCommEvent(CWidgetBase * target, unsigned long event_code);
   virtual ~cCommEvent();
   CWidgetBase * Target();
   unsigned long EventCode();
private:
   CWidgetBase * _Target;
   unsigned long _EventCode;
};

class cNewValueEvent : public cCommEvent
{
public:
   cNewValueEvent(CWidgetBase * target, const QString & value, ULONG_T id,
                  ULONG_T time_offset, UCHAR_T data_type, ULONG_T size);
   virtual ~cNewValueEvent();
   QString Value();
   ULONG_T Id();
   ULONG_T TimeOffset();
   UCHAR_T DataType();
   ULONG_T Size();
private:
   QString _Value;
   ULONG_T _Id;
   ULONG_T _TimeOffset;
   UCHAR_T _DataType;
   ULONG_T _Size;
};

class cNewBufEvent : public cCommEvent
{
public:
   cNewBufEvent(CWidgetBase * target, BUF_T buf, ULONG_T id,
                ULONG_T time_offset, UCHAR_T data_type, ULONG_T size);
   virtual ~cNewBufEvent();
   BUF_T Buf();
   ULONG_T Id();
   ULONG_T TimeOffset();
   UCHAR_T DataType();
   ULONG_T Size();
private:
   BUF_T _Buf;
   ULONG_T _Id;
   ULONG_T _TimeOffset;
   UCHAR_T _DataType;
   ULONG_T _Size;
};

class cNewObjectEvent : public cCommEvent
{
public:
   cNewObjectEvent(CWidgetBase * target, TRANSIENT_OBJECT_PTR object);
   virtual ~cNewObjectEvent();
   TRANSIENT_OBJECT_PTR Object();
private:
   TRANSIENT_OBJECT_PTR _Object;
};

class cMessageBoxEvent : public cCommEvent
{
public:
   cMessageBoxEvent(CWidgetBase * target,
                    const QString & caption, const QString & text, QMessageBox::Icon icon,
                    int button0, int button1, int button2,
                    QFont font);
   virtual ~cMessageBoxEvent();
public:
   QString _Caption;
   QString _Text;
   QMessageBox::Icon _Icon;
   int _Button0;
   int _Button1;
   int _Button2;
   QFont _Font;
};

#endif


