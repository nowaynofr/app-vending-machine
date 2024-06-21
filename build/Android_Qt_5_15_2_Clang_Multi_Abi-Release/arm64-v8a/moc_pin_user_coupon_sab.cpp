/****************************************************************************
** Meta object code from reading C++ file 'pin_user_coupon_sab.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/pin_user_coupon_sab.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pin_user_coupon_sab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pin_user_coupon_sab_t {
    QByteArrayData data[7];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pin_user_coupon_sab_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pin_user_coupon_sab_t qt_meta_stringdata_pin_user_coupon_sab = {
    {
QT_MOC_LITERAL(0, 0, 19), // "pin_user_coupon_sab"
QT_MOC_LITERAL(1, 20, 20), // "Signal_PinUserCoupon"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 56, 9), // "Back_Home"
QT_MOC_LITERAL(5, 66, 31), // "on_Btn_Ok_PinUserCoupon_clicked"
QT_MOC_LITERAL(6, 98, 33) // "on_Btn_Back_PinUserCoupon_cli..."

    },
    "pin_user_coupon_sab\0Signal_PinUserCoupon\0"
    "\0MACHINE_STATE\0Back_Home\0"
    "on_Btn_Ok_PinUserCoupon_clicked\0"
    "on_Btn_Back_PinUserCoupon_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pin_user_coupon_sab[] = {

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
       6,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void pin_user_coupon_sab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pin_user_coupon_sab *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_PinUserCoupon((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 1: _t->Back_Home((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_Btn_Ok_PinUserCoupon_clicked(); break;
        case 3: _t->on_Btn_Back_PinUserCoupon_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pin_user_coupon_sab::*)(MACHINE_STATE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pin_user_coupon_sab::Signal_PinUserCoupon)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pin_user_coupon_sab::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_pin_user_coupon_sab.data,
    qt_meta_data_pin_user_coupon_sab,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *pin_user_coupon_sab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pin_user_coupon_sab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pin_user_coupon_sab.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pin_user_coupon_sab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void pin_user_coupon_sab::Signal_PinUserCoupon(MACHINE_STATE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
