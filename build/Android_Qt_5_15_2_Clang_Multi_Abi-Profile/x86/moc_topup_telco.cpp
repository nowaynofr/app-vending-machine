/****************************************************************************
** Meta object code from reading C++ file 'topup_telco.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/topup_telco.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'topup_telco.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_topup_telco_t {
    QByteArrayData data[9];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_topup_telco_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_topup_telco_t qt_meta_stringdata_topup_telco = {
    {
QT_MOC_LITERAL(0, 0, 11), // "topup_telco"
QT_MOC_LITERAL(1, 12, 18), // "Signal_ToupupTelco"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 46, 19), // "select_home_network"
QT_MOC_LITERAL(5, 66, 12), // "select_price"
QT_MOC_LITERAL(6, 79, 9), // "Back_Home"
QT_MOC_LITERAL(7, 89, 28), // "on_Btn_Ok_Topuptelco_clicked"
QT_MOC_LITERAL(8, 118, 30) // "on_Btn_Back_Topuptelco_clicked"

    },
    "topup_telco\0Signal_ToupupTelco\0\0"
    "MACHINE_STATE\0select_home_network\0"
    "select_price\0Back_Home\0"
    "on_Btn_Ok_Topuptelco_clicked\0"
    "on_Btn_Back_Topuptelco_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_topup_telco[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       5,    2,   50,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x08 /* Private */,
       7,    0,   58,    2, 0x08 /* Private */,
       8,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void topup_telco::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<topup_telco *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_ToupupTelco((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 1: _t->select_home_network((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->select_price((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 3: _t->Back_Home((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_Btn_Ok_Topuptelco_clicked(); break;
        case 5: _t->on_Btn_Back_Topuptelco_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (topup_telco::*)(MACHINE_STATE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&topup_telco::Signal_ToupupTelco)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject topup_telco::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_topup_telco.data,
    qt_meta_data_topup_telco,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *topup_telco::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *topup_telco::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_topup_telco.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int topup_telco::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void topup_telco::Signal_ToupupTelco(MACHINE_STATE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
