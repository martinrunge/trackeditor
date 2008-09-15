/****************************************************************************
** Meta object code from reading C++ file 'TrackEditor.h'
**
** Created: Sun Sep 14 22:34:56 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TrackEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogReader[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      28,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   10,   10,   10, 0x0a,
      74,   67,   10,   10, 0x0a,
      90,   10,   10,   10, 0x0a,
     106,   10,   10,   10, 0x0a,
     125,   10,   10,   10, 0x0a,
     143,  135,   10,   10, 0x0a,
     157,   10,   10,   10, 0x0a,
     173,   10,   10,   10, 0x0a,
     197,  191,   10,   10, 0x0a,
     217,  214,   10,   10, 0x0a,
     242,  214,   10,   10, 0x0a,
     267,   10,   10,   10, 0x0a,
     284,   10,   10,   10, 0x0a,
     300,   10,   10,   10, 0x0a,
     312,   10,   10,   10, 0x0a,
     324,   10,   10,   10, 0x0a,
     344,  338,   10,   10, 0x0a,
     375,  373,   10,   10, 0x0a,
     428,  423,   10,   10, 0x0a,
     448,  423,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LogReader[] = {
    "LogReader\0\0setText(QString)\0"
    "emitData(QByteArray)\0actionTriggered()\0"
    "dev_fd\0readDevice(int)\0connectDevice()\0"
    "disconnectDevice()\0readLog()\0percent\0"
    "progress(int)\0cancelReadLog()\0"
    "readLogFinished()\0track\0newTrack(Track*)\0"
    "tp\0newWayPoint(TrackPoint*)\0"
    "newLogPoint(TrackPoint*)\0startRecording()\0"
    "stopRecording()\0loadTrack()\0saveTrack()\0"
    "saveTrackAs()\0index\0treeViewClicked(QModelIndex)\0"
    ",\0selectionChanged(QItemSelection,QItemSelection)\0"
    "data\0addData(QByteArray)\0sendData(QByteArray)\0"
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
        case 1: emitData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: actionTriggered(); break;
        case 3: readDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: connectDevice(); break;
        case 5: disconnectDevice(); break;
        case 6: readLog(); break;
        case 7: progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: cancelReadLog(); break;
        case 9: readLogFinished(); break;
        case 10: newTrack((*reinterpret_cast< Track*(*)>(_a[1]))); break;
        case 11: newWayPoint((*reinterpret_cast< TrackPoint*(*)>(_a[1]))); break;
        case 12: newLogPoint((*reinterpret_cast< TrackPoint*(*)>(_a[1]))); break;
        case 13: startRecording(); break;
        case 14: stopRecording(); break;
        case 15: loadTrack(); break;
        case 16: saveTrack(); break;
        case 17: saveTrackAs(); break;
        case 18: treeViewClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 19: selectionChanged((*reinterpret_cast< QItemSelection(*)>(_a[1])),(*reinterpret_cast< QItemSelection(*)>(_a[2]))); break;
        case 20: addData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 21: sendData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void LogReader::setText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LogReader::emitData(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
