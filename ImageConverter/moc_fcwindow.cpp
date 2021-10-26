/****************************************************************************
** Meta object code from reading C++ file 'fcwindow.h'
**
** Created: Thu Aug 20 14:54:06 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fcwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fcwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FCWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      47,    9,    9,    9, 0x08,
      79,    9,    9,    9, 0x08,
     106,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FCWindow[] = {
    "FCWindow\0\0on_checkBox_resize_stateChanged(int)\0"
    "on_pushButton_wybierz_clicked()\0"
    "on_pushButton_OK_clicked()\0"
    "on_pushButton_Cancel_clicked()\0"
};

const QMetaObject FCWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FCWindow,
      qt_meta_data_FCWindow, 0 }
};

const QMetaObject *FCWindow::metaObject() const
{
    return &staticMetaObject;
}

void *FCWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FCWindow))
        return static_cast<void*>(const_cast< FCWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int FCWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_checkBox_resize_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_pushButton_wybierz_clicked(); break;
        case 2: on_pushButton_OK_clicked(); break;
        case 3: on_pushButton_Cancel_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
