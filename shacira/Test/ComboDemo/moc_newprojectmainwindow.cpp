/****************************************************************************
** NewProjectMainWindow meta object code from reading C++ file 'newprojectmainwindow.h'
**
** Created: Do 10. Mrz 20:42:43 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "newprojectmainwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NewProjectMainWindow::className() const
{
    return "NewProjectMainWindow";
}

QMetaObject *NewProjectMainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NewProjectMainWindow( "NewProjectMainWindow", &NewProjectMainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NewProjectMainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NewProjectMainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NewProjectMainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NewProjectMainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NewProjectMainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "languageChange()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"NewProjectMainWindow", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NewProjectMainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* NewProjectMainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NewProjectMainWindow" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool NewProjectMainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NewProjectMainWindow::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NewProjectMainWindow::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool NewProjectMainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
