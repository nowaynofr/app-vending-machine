/****************************************************************************
** Meta object code from reading C++ file 'machine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Machine/machine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'machine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Machine_t {
    QByteArrayData data[20];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Machine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Machine_t qt_meta_stringdata_Machine = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Machine"
QT_MOC_LITERAL(1, 8, 12), // "stateChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "data"
QT_MOC_LITERAL(4, 27, 7), // "killApp"
QT_MOC_LITERAL(5, 35, 14), // "killProcessApp"
QT_MOC_LITERAL(6, 50, 14), // "getListUsbPort"
QT_MOC_LITERAL(7, 65, 8), // "mountUsb"
QT_MOC_LITERAL(8, 74, 7), // "syncUsb"
QT_MOC_LITERAL(9, 82, 8), // "setState"
QT_MOC_LITERAL(10, 91, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(11, 105, 5), // "state"
QT_MOC_LITERAL(12, 111, 12), // "setLastState"
QT_MOC_LITERAL(13, 124, 5), // "input"
QT_MOC_LITERAL(14, 130, 7), // "keycode"
QT_MOC_LITERAL(15, 138, 7), // "KillApp"
QT_MOC_LITERAL(16, 146, 14), // "KillProcessApp"
QT_MOC_LITERAL(17, 161, 14), // "GetListUsbPort"
QT_MOC_LITERAL(18, 176, 8), // "MountUsb"
QT_MOC_LITERAL(19, 185, 7) // "SyncUsb"

    },
    "Machine\0stateChanged\0\0data\0killApp\0"
    "killProcessApp\0getListUsbPort\0mountUsb\0"
    "syncUsb\0setState\0MACHINE_STATE\0state\0"
    "setLastState\0input\0keycode\0KillApp\0"
    "KillProcessApp\0GetListUsbPort\0MountUsb\0"
    "SyncUsb"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Machine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    0,   88,    2, 0x06 /* Public */,
       6,    0,   89,    2, 0x06 /* Public */,
       7,    0,   90,    2, 0x06 /* Public */,
       8,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   94,    2, 0x0a /* Public */,
      12,    1,   97,    2, 0x0a /* Public */,
      13,    1,  100,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    0,  105,    2, 0x0a /* Public */,
      18,    0,  106,    2, 0x0a /* Public */,
      19,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariantMap,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Machine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Machine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 1: _t->killApp(); break;
        case 2: _t->killProcessApp(); break;
        case 3: _t->getListUsbPort(); break;
        case 4: _t->mountUsb(); break;
        case 5: _t->syncUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setState((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 7: _t->setLastState((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 8: _t->input((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->KillApp(); break;
        case 10: _t->KillProcessApp(); break;
        case 11: _t->GetListUsbPort(); break;
        case 12: _t->MountUsb(); break;
        case 13: _t->SyncUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Machine::*)(QVariantMap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Machine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::killApp)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Machine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::killProcessApp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Machine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::getListUsbPort)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Machine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::mountUsb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Machine::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Machine::syncUsb)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Machine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Machine.data,
    qt_meta_data_Machine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Machine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Machine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Machine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Machine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Machine::stateChanged(QVariantMap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Machine::killApp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Machine::killProcessApp()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Machine::getListUsbPort()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Machine::mountUsb()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Machine::syncUsb(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
