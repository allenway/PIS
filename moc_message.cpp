/****************************************************************************
** Meta object code from reading C++ file 'message.h'
**
** Created: Thu Dec 10 16:54:50 2015
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "message.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'message.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataHandle[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DataHandle[] = {
    "DataHandle\0\0ccStatChanged()\0"
    "annunciatorStatChanged()\0"
};

const QMetaObject DataHandle::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DataHandle,
      qt_meta_data_DataHandle, 0 }
};

const QMetaObject *DataHandle::metaObject() const
{
    return &staticMetaObject;
}

void *DataHandle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataHandle))
        return static_cast<void*>(const_cast< DataHandle*>(this));
    return QThread::qt_metacast(_clname);
}

int DataHandle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ccStatChanged(); break;
        case 1: annunciatorStatChanged(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataHandle::ccStatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DataHandle::annunciatorStatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_UartHandle[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_UartHandle[] = {
    "UartHandle\0"
};

const QMetaObject UartHandle::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UartHandle,
      qt_meta_data_UartHandle, 0 }
};

const QMetaObject *UartHandle::metaObject() const
{
    return &staticMetaObject;
}

void *UartHandle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UartHandle))
        return static_cast<void*>(const_cast< UartHandle*>(this));
    return QThread::qt_metacast(_clname);
}

int UartHandle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Message[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      25,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Message[] = {
    "Message\0\0ccStatChanged()\0"
    "annunciatorStatChanged()\0"
};

const QMetaObject Message::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Message,
      qt_meta_data_Message, 0 }
};

const QMetaObject *Message::metaObject() const
{
    return &staticMetaObject;
}

void *Message::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Message))
        return static_cast<void*>(const_cast< Message*>(this));
    return QObject::qt_metacast(_clname);
}

int Message::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ccStatChanged(); break;
        case 1: annunciatorStatChanged(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Message::ccStatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Message::annunciatorStatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
