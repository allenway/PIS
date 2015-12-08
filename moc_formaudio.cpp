/****************************************************************************
** Meta object code from reading C++ file 'formaudio.h'
**
** Created: Mon Dec 7 16:12:29 2015
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "formaudio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formaudio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormAudio[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      39,   10,   10,   10, 0x08,
      67,   10,   10,   10, 0x08,
      95,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormAudio[] = {
    "FormAudio\0\0on_pushButtonNext_clicked()\0"
    "on_pushButtonPrev_clicked()\0"
    "on_pushButtonStop_clicked()\0"
    "on_pushButtonPlay_clicked()\0"
};

const QMetaObject FormAudio::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormAudio,
      qt_meta_data_FormAudio, 0 }
};

const QMetaObject *FormAudio::metaObject() const
{
    return &staticMetaObject;
}

void *FormAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormAudio))
        return static_cast<void*>(const_cast< FormAudio*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButtonNext_clicked(); break;
        case 1: on_pushButtonPrev_clicked(); break;
        case 2: on_pushButtonStop_clicked(); break;
        case 3: on_pushButtonPlay_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
