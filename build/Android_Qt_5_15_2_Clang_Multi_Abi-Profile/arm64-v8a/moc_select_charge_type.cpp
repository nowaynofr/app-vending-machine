/****************************************************************************
** Meta object code from reading C++ file 'select_charge_type.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/select_charge_type.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'select_charge_type.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_select_charge_type_t {
    QByteArrayData data[7];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_select_charge_type_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_select_charge_type_t qt_meta_stringdata_select_charge_type = {
    {
QT_MOC_LITERAL(0, 0, 18), // "select_charge_type"
QT_MOC_LITERAL(1, 19, 25), // "Signal_Select_Charge_Type"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 60, 9), // "Back_Home"
QT_MOC_LITERAL(5, 70, 36), // "on_Btn_Back_SelectChargeType_..."
QT_MOC_LITERAL(6, 107, 26) // "select_charge_type_clicked"

    },
    "select_charge_type\0Signal_Select_Charge_Type\0"
    "\0MACHINE_STATE\0Back_Home\0"
    "on_Btn_Back_SelectChargeType_clicked\0"
    "select_charge_type_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_select_charge_type[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x08 /* Private */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void select_charge_type::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<select_charge_type *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Select_Charge_Type((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 1: _t->Back_Home((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_Btn_Back_SelectChargeType_clicked(); break;
        case 3: _t->select_charge_type_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (select_charge_type::*)(MACHINE_STATE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&select_charge_type::Signal_Select_Charge_Type)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject select_charge_type::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_select_charge_type.data,
    qt_meta_data_select_charge_type,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *select_charge_type::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *select_charge_type::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_select_charge_type.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int select_charge_type::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void select_charge_type::Signal_Select_Charge_Type(MACHINE_STATE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
