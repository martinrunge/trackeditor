/****************************************************************************
** Meta object code from reading C++ file 'CWintec.h'
**
** Created: Sun Sep 14 23:27:04 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CWintec.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CWintec.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWintec[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      29,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CWintec[] = {
    "CWintec\0\0addData(QByteArray)\0timeout()\0"
};

const QMetaObject CWintec::staticMetaObject = {
    { &IDeviceIO::staticMetaObject, qt_meta_stringdata_CWintec,
      qt_meta_data_CWintec, 0 }
};

const QMetaObject *CWintec::metaObject() const
{
    return &staticMetaObject;
}

void *CWintec::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWintec))
        return static_cast<void*>(const_cast< CWintec*>(this));
    return IDeviceIO::qt_metacast(_clname);
}

int CWintec::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IDeviceIO::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: timeout(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
