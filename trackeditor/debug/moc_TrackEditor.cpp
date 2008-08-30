/****************************************************************************
** Meta object code from reading C++ file 'TrackEditor.h'
**
** Created: Wed Aug 27 16:28:54 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TrackEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogReader[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   10,   10,   10, 0x0a,
      53,   46,   10,   10, 0x0a,
      69,   10,   10,   10, 0x0a,
      79,   10,   10,   10, 0x0a,
      91,   10,   10,   10, 0x0a,
     103,   10,   10,   10, 0x0a,
     123,  117,   10,   10, 0x0a,
     154,  152,   10,   10, 0x0a,
     207,  202,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LogReader[] = {
    "LogReader\0\0setText(QString)\0"
    "actionTriggered()\0dev_fd\0readDevice(int)\0"
    "readLog()\0loadTrack()\0saveTrack()\0"
    "saveTrackAs()\0index\0treeViewClicked(QModelIndex)\0"
    ",\0selectionChanged(QItemSelection,QItemSelection)\0"
    "data\0addData(QByteArray)\0"
};

const QMetaObject LogReader::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LogReader,
      qt_meta_data_LogReader, 0 }
};

const QMetaObject *LogReader::metaObject() const
{
    return &staticMetaObject;
}

void *LogReader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogReader))
	return static_cast<void*>(const_cast< LogReader*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LogReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: actionTriggered(); break;
        case 2: readDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: readLog(); break;
        case 4: loadTrack(); break;
        case 5: saveTrack(); break;
        case 6: saveTrackAs(); break;
        case 7: treeViewClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: selectionChanged((*reinterpret_cast< QItemSelection(*)>(_a[1])),(*reinterpret_cast< QItemSelection(*)>(_a[2]))); break;
        case 9: addData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void LogReader::setText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
