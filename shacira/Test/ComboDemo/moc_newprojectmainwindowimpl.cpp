/****************************************************************************
** NewProjectMainWindowImpl meta object code from reading C++ file 'newprojectmainwindowimpl.h'
**
** Created: Do 10. Mrz 20:35:38 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "newprojectmainwindowimpl.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NewProjectMainWindowImpl::className() const
{
    return "NewProjectMainWindowImpl";
}

QMetaObject *NewProjectMainWindowImpl::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NewProjectMainWindowImpl( "NewProjectMainWindowImpl", &NewProjectMainWindowImpl::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NewProjectMainWindowImpl::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NewProjectMainWindowImpl", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NewProjectMainWindowImpl::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NewProjectMainWindowImpl", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NewProjectMainWindowImpl::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = NewProjectMainWindow::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "pos", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"SelectionChanged", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "SelectionChanged(int)", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"NewProjectMainWindowImpl", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NewProjectMainWindowImpl.setMetaObject( metaObj );
    return metaObj;
}

void* NewProjectMainWindowImpl::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NewProjectMainWindowImpl" ) )
	return this;
    return NewProjectMainWindow::qt_cast( clname );
}

bool NewProjectMainWindowImpl::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: SelectionChanged((int)static_QUType_int.get(_o+1)); break;
    default:
	return NewProjectMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NewProjectMainWindowImpl::qt_emit( int _id, QUObject* _o )
{
    return NewProjectMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NewProjectMainWindowImpl::qt_property( int id, int f, QVariant* v)
{
    return NewProjectMainWindow::qt_property( id, f, v);
}

bool NewProjectMainWindowImpl::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
