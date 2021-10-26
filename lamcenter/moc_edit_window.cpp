/****************************************************************************
** Meta object code from reading C++ file 'edit_window.h'
**
** Created: Wed Jan 27 14:45:29 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "edit_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edit_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Edit_Window[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      21,   12,   12,   12, 0x08,
      28,   12,   12,   12, 0x08,
      41,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Edit_Window[] = {
    "Edit_Window\0\0reset()\0save()\0getPidFile()\0"
    "getInitdFile()\0"
};

const QMetaObject Edit_Window::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Edit_Window,
      qt_meta_data_Edit_Window, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Edit_Window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Edit_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Edit_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Edit_Window))
        return static_cast<void*>(const_cast< Edit_Window*>(this));
    return QDialog::qt_metacast(_clname);
}

int Edit_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: reset(); break;
        case 1: save(); break;
        case 2: getPidFile(); break;
        case 3: getInitdFile(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
