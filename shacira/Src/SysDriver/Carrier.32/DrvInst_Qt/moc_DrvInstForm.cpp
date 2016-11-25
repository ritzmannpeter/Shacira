/****************************************************************************
** DrvInstForm meta object code from reading C++ file 'DrvInstForm.h'
**
** Created: Mo 10. Mrz 15:53:10 2003
**      by: The Qt MOC ($Id:  qt/moc_yacc.cpp   3.0.3   edited Mar 12 07:51 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "DrvInstForm.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DrvInstForm::className() const
{
    return "DrvInstForm";
}

QMetaObject *DrvInstForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DrvInstForm;

#ifndef QT_NO_TRANSLATION
QString DrvInstForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DrvInstForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DrvInstForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DrvInstForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DrvInstForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"Test_clicked", 0, 0 };
    static const QUMethod slot_1 = {"Install_clicked", 0, 0 };
    static const QUMethod slot_2 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "Test_clicked()", &slot_0, QMetaData::Public },
	{ "Install_clicked()", &slot_1, QMetaData::Public },
	{ "init()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"DrvInstForm", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DrvInstForm.setMetaObject( metaObj );
    return metaObj;
}

void* DrvInstForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DrvInstForm" ) ) return (DrvInstForm*)this;
    return QMainWindow::qt_cast( clname );
}

bool DrvInstForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: Test_clicked(); break;
    case 1: Install_clicked(); break;
    case 2: init(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DrvInstForm::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool DrvInstForm::qt_property( int _id, int _f, QVariant* _v)
{
    return QMainWindow::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
