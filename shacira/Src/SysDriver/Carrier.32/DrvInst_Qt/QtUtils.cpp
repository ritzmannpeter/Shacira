
#include "QObject.h"
#include "QtUtils.h"

static void * _ObjectData = NULL;

void QtUtils::AddWidgetData(QObject * object, void * data)
{
#ifdef that_doesnt_work
	QVariant * var_ptr = new QVariant((int)data);
	if (object->setProperty("__OBJECT_DATA__", *var_ptr)) {
		int dummy = NULL;
	} else {
		int dummy = NULL;
	}
#else
	_ObjectData = data;
#endif
}

void * QtUtils::WidgetData(QObject * object)
{
#ifdef that_doesnt_work
	QVariant variant = object->property("__OBJECT_DATA__");
	if (!variant.isValid()) {
		return NULL;
	} else {
		return (void*)(int)(variant.toInt());
	}
#else
	return _ObjectData;
#endif
}

