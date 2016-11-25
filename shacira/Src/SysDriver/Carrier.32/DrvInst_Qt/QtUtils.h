
class QObject;

class QtUtils {
public:
	static void AddWidgetData(QObject * object, void * data);
	static void * WidgetData(QObject * object);
};

