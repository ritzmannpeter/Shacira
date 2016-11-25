
#include "cGuiEvents.h"

cCommEvent::cCommEvent(CWidgetBase * target, unsigned long event_code) :
   QEvent(QEvent::User)
{
   _Target = target;
   _EventCode = event_code;
}

cCommEvent::~cCommEvent()
{
}

CWidgetBase * cCommEvent::Target()
{
   return _Target;
}

unsigned long cCommEvent::EventCode()
{
   return _EventCode;
}

cNewValueEvent::cNewValueEvent(CWidgetBase * target, const QString & value, ULONG_T id,
                               ULONG_T time_offset, UCHAR_T data_type, ULONG_T size) :
      cCommEvent(target, NEW_VALUE)
{
   _Value = value;
   _Id = id;
   _TimeOffset = time_offset;
   _DataType = data_type;
   _Size = size;
}

cNewValueEvent::~cNewValueEvent()
{
}

QString cNewValueEvent::Value()
{
   return _Value;
}

ULONG_T cNewValueEvent::Id()
{
   return _Id;
}

ULONG_T cNewValueEvent::TimeOffset()
{
   return _TimeOffset;
}

UCHAR_T cNewValueEvent::DataType()
{
   return _DataType;
}

ULONG_T cNewValueEvent::Size()
{
   return _Size;
}


cNewBufEvent::cNewBufEvent(CWidgetBase * target, BUF_T buf, ULONG_T id,
                           ULONG_T time_offset, UCHAR_T data_type, ULONG_T size) :
      cCommEvent(target, NEW_BUF)
{
   _Buf = buf;
   _Id = id;
   _TimeOffset = time_offset;
   _DataType = data_type;
   _Size = size;
}

cNewBufEvent::~cNewBufEvent()
{
}

BUF_T cNewBufEvent::Buf()
{
   return _Buf;
}

ULONG_T cNewBufEvent::Id()
{
   return _Id;
}

ULONG_T cNewBufEvent::TimeOffset()
{
   return _TimeOffset;
}

UCHAR_T cNewBufEvent::DataType()
{
   return _DataType;
}

ULONG_T cNewBufEvent::Size()
{
   return _Size;
}

cNewObjectEvent::cNewObjectEvent(CWidgetBase * target, TRANSIENT_OBJECT_PTR object) :
      cCommEvent(target, NEW_OBJECT)
{
   _Object = object;
}

cNewObjectEvent::~cNewObjectEvent()
{
};

TRANSIENT_OBJECT_PTR cNewObjectEvent::Object()
{
   return _Object;
}

cMessageBoxEvent::cMessageBoxEvent(CWidgetBase * target,
                                   const QString & caption, const QString & text, QMessageBox::Icon icon,
                                   int button0, int button1, int button2,
                                   QFont font)
   : cCommEvent(target, MESSAGE_BOX)
{
   _Caption = caption;
   _Text = text;
   _Icon = icon;
   _Button0 = button0;
   _Button1 = button1;
   _Button2 = button2;
   _Font = font;
};

cMessageBoxEvent::~cMessageBoxEvent()
{
}


