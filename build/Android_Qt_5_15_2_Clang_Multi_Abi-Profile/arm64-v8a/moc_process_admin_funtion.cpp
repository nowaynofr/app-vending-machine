/****************************************************************************
** Meta object code from reading C++ file 'process_admin_funtion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/AdminProcess/process_admin_funtion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'process_admin_funtion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_process_admin_funtion_t {
    QByteArrayData data[8];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_process_admin_funtion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_process_admin_funtion_t qt_meta_stringdata_process_admin_funtion = {
    {
QT_MOC_LITERAL(0, 0, 21), // "process_admin_funtion"
QT_MOC_LITERAL(1, 22, 28), // "Signal_Admin_Funtion_Process"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 66, 13), // "ProcessSelect"
QT_MOC_LITERAL(5, 80, 39), // "on_Btn_Ok_Admin_Funtion_Proce..."
QT_MOC_LITERAL(6, 120, 41), // "on_Btn_Back_Admin_Funtion_Pro..."
QT_MOC_LITERAL(7, 162, 20) // "Update_LineEdit_Sale"

    },
    "process_admin_funtion\0"
    "Signal_Admin_Funtion_Process\0\0"
    "MACHINE_STATE\0ProcessSelect\0"
    "on_Btn_Ok_Admin_Funtion_Process_clicked\0"
    "on_Btn_Back_Admin_Funtion_Process_clicked\0"
    "Update_LineEdit_Sale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_process_admin_funtion[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08 /* Private */,
       5,    0,   45,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void process_admin_funtion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<process_admin_funtion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Admin_Funtion_Process((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 1: _t->ProcessSelect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_Btn_Ok_Admin_Funtion_Process_clicked(); break;
        case 3: _t->on_Btn_Back_Admin_Funtion_Process_clicked(); break;
        case 4: _t->Update_LineEdit_Sale(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (process_admin_funtion::*)(MACHINE_STATE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&process_admin_funtion::Signal_Admin_Funtion_Process)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject process_admin_funtion::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_process_admin_funtion.data,
    qt_meta_data_process_admin_funtion,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *process_admin_funtion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *process_admin_funtion::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_process_admin_funtion.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int process_admin_funtion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void process_admin_funtion::Signal_Admin_Funtion_Process(MACHINE_STATE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
