/****************************************************************************
** Meta object code from reading C++ file 'process_setting_quantity_funtion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/AdminProcess/process_setting_quantity_funtion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'process_setting_quantity_funtion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_process_setting_quantity_funtion_t {
    QByteArrayData data[7];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_process_setting_quantity_funtion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_process_setting_quantity_funtion_t qt_meta_stringdata_process_setting_quantity_funtion = {
    {
QT_MOC_LITERAL(0, 0, 32), // "process_setting_quantity_funtion"
QT_MOC_LITERAL(1, 33, 45), // "Signal_Admin_Setting_Quantity..."
QT_MOC_LITERAL(2, 79, 0), // ""
QT_MOC_LITERAL(3, 80, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 94, 56), // "on_Btn_Ok_Admin_Setting_Quant..."
QT_MOC_LITERAL(5, 151, 58), // "on_Btn_Back_Admin_Setting_Qua..."
QT_MOC_LITERAL(6, 210, 21) // "onSpinBoxValueChanged"

    },
    "process_setting_quantity_funtion\0"
    "Signal_Admin_Setting_Quantity_Funtion_Process\0"
    "\0MACHINE_STATE\0"
    "on_Btn_Ok_Admin_Setting_Quantity_Funtion_Process_clicked\0"
    "on_Btn_Back_Admin_Setting_Quantity_Funtion_Process_clicked\0"
    "onSpinBoxValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_process_setting_quantity_funtion[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void process_setting_quantity_funtion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<process_setting_quantity_funtion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Admin_Setting_Quantity_Funtion_Process((*reinterpret_cast< MACHINE_STATE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->on_Btn_Ok_Admin_Setting_Quantity_Funtion_Process_clicked(); break;
        case 2: _t->on_Btn_Back_Admin_Setting_Quantity_Funtion_Process_clicked(); break;
        case 3: _t->onSpinBoxValueChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (process_setting_quantity_funtion::*)(MACHINE_STATE , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&process_setting_quantity_funtion::Signal_Admin_Setting_Quantity_Funtion_Process)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject process_setting_quantity_funtion::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_process_setting_quantity_funtion.data,
    qt_meta_data_process_setting_quantity_funtion,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *process_setting_quantity_funtion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *process_setting_quantity_funtion::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_process_setting_quantity_funtion.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int process_setting_quantity_funtion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void process_setting_quantity_funtion::Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
