
#ifndef _cindreqvalue_h_
#define _cindreqvalue_h_

#include "CReqValue.h"


#ifndef QT_PLUGIN
#include "cViewInterface.h"
#endif

typedef struct ref
{
   VAR_REF_PTR var_ref;
   DATA_VIEW_PTR view;
   ULONG_T id;
}  REF_T;

#ifdef QT_PLUGIN
typedef void * REF_MAP_T;
typedef void * ACTREF_MAP_T;
#else
typedef std::map<QString, REF_T*> REF_MAP_T;
typedef std::map <void*, REF_T*> ACTREF_MAP_T;
#endif

class cIndexBase
{
public:
   cIndexBase(CWidgetBase * base);
   ~cIndexBase();
#ifdef QT4
   void Configure(const QString & base_name,
                  QByteArray & varSpec,
                  VAR_REF_PTR & ref,
                  DATA_VIEW_PTR & view,
                  ULONG_T id,
                  ULONG_T i1 = -1,
                  ULONG_T i2 = -1,
                  ULONG_T i3 = -1,
                  ULONG_T i4 = -1);
#else
   void Configure(const QString & base_name,
                  QCString & varSpec,
                  VAR_REF_PTR & ref,
                  DATA_VIEW_PTR & view,
                  ULONG_T id,
                  ULONG_T i1 = -1,
                  ULONG_T i2 = -1,
                  ULONG_T i3 = -1,
                  ULONG_T i4 = -1);
#endif
private:
   static REF_MAP_T _Refs;
   static ACTREF_MAP_T _ActRefs;
   CWidgetBase * _BaseWidget;
private:
   REF_T * AllocRef(VAR_REF_PTR var_ref, DATA_VIEW_PTR viewl, ULONG_T id);
   REF_T * Ref(const QString & ref_spec);
   void AddRef(const QString & ref_spec, REF_T * ref);
   REF_T * ActRef(void * control);
   void AddActRef(void * control, REF_T * ref);
};


/**!
  * @brief Specific display widget derived from CReqValue that interpretes CCS variable references
  * as index into a text table. The index selects the text that will be
  * displayed instead of the numeric value.
  */
class _CWIDGET_EXPORT_ CIndReqValue : public CReqValue
{

// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   Q_ENUMS(SetTypes)
   PROPERTY_2i(QByteArray,BaseName)
   PROPERTY_2i(int,Ident)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

public slots:
   void NewIndex(int i1, int i2, int i3, int i4);
   void NewVarName(const QString VarName, int i1, int i2, int i3, int i4);

signals:
   void ValueChanged(QString value, int id, int i1, int i2, int i3, int i4);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CReqValue::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e);
   virtual void focusOutEvent(QFocusEvent * e);
   void keyReleaseEvent(QKeyEvent * e);

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange() {};

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public:
   CIndReqValue(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CIndReqValue();

private:
protected:
   cIndexBase * _IndexBase;
   int _Index1;
   int _Index2;
   int _Index3;
   int _Index4;
};

#endif


