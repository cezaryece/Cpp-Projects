/****************************************************************************
** Meta object code from reading C++ file 'pdfimpose.h'
**
** Created: Wed Feb 17 12:23:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pdfimpose.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdfimpose.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PDFimpose[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      21,   10,   10,   10, 0x08,
      31,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PDFimpose[] = {
    "PDFimpose\0\0OpenPDF()\0InfoPDF()\0"
    "ExportPDF()\0"
};

const QMetaObject PDFimpose::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PDFimpose,
      qt_meta_data_PDFimpose, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PDFimpose::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PDFimpose::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PDFimpose::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PDFimpose))
        return static_cast<void*>(const_cast< PDFimpose*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PDFimpose::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OpenPDF(); break;
        case 1: InfoPDF(); break;
        case 2: ExportPDF(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
