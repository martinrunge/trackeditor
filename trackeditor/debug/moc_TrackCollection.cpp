/****************************************************************************
** Meta object code from reading C++ file 'TrackCollection.h'
**
** Created: Sat Sep 6 12:45:01 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TrackCollection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackCollection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrackCollection[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      37,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TrackCollection[] = {
    "TrackCollection\0\0topLeft,bottomRight\0"
    "editFinished(QModelIndex,QModelIndex)\0"
};

const QMetaObject TrackCollection::staticMetaObject = {
    { &QStandardItemModel::staticMetaObject, qt_meta_stringdata_TrackCollection,
      qt_meta_data_TrackCollection, 0 }
};

const QMetaObject *TrackCollection::metaObject() const
{
    return &staticMetaObject;
}

void *TrackCollection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrackCollection))
        return static_cast<void*>(const_cast< TrackCollection*>(this));
    if (!strcmp(_clname, "QList<Track*>"))
        return static_cast< QList<Track*>*>(const_cast< TrackCollection*>(this));
    if (!strcmp(_clname, "CommonAttributes"))
        return static_cast< CommonAttributes*>(const_cast< TrackCollection*>(this));
    return QStandardItemModel::qt_metacast(_clname);
}

int TrackCollection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStandardItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editFinished((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
