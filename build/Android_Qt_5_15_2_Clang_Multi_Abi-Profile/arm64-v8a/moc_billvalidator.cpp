/****************************************************************************
** Meta object code from reading C++ file 'billvalidator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Machine/billvalidator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'billvalidator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BillValidator_t {
    QByteArrayData data[15];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BillValidator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BillValidator_t qt_meta_stringdata_BillValidator = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BillValidator"
QT_MOC_LITERAL(1, 14, 13), // "bill_accepted"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "data"
QT_MOC_LITERAL(4, 34, 15), // "bill_identified"
QT_MOC_LITERAL(5, 50, 15), // "bill_unAccepted"
QT_MOC_LITERAL(6, 66, 10), // "bill_error"
QT_MOC_LITERAL(7, 77, 1), // "s"
QT_MOC_LITERAL(8, 79, 11), // "bill_status"
QT_MOC_LITERAL(9, 91, 13), // "bill_response"
QT_MOC_LITERAL(10, 105, 5), // "error"
QT_MOC_LITERAL(11, 111, 7), // "timeout"
QT_MOC_LITERAL(12, 119, 3), // "run"
QT_MOC_LITERAL(13, 123, 5), // "start"
QT_MOC_LITERAL(14, 129, 4) // "stop"

    },
    "BillValidator\0bill_accepted\0\0data\0"
    "bill_identified\0bill_unAccepted\0"
    "bill_error\0s\0bill_status\0bill_response\0"
    "error\0timeout\0run\0start\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BillValidator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    1,   75,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,
       9,    1,   84,    2, 0x06 /* Public */,
      10,    1,   87,    2, 0x06 /* Public */,
      11,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   93,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    0,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BillValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BillValidator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->bill_accepted((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 1: _t->bill_identified((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: _t->bill_unAccepted((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 3: _t->bill_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->bill_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->bill_response((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->timeout((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->run(); break;
        case 9: _t->start(); break;
        case 10: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BillValidator::*)(const double & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_accepted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(const double & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_identified)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(const double & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_unAccepted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_error)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_status)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::bill_response)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::error)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (BillValidator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BillValidator::timeout)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BillValidator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BillValidator.data,
    qt_meta_data_BillValidator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BillValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BillValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BillValidator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BillValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BillValidator::bill_accepted(const double & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BillValidator::bill_identified(const double & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BillValidator::bill_unAccepted(const double & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BillValidator::bill_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BillValidator::bill_status(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BillValidator::bill_response(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void BillValidator::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void BillValidator::timeout(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
