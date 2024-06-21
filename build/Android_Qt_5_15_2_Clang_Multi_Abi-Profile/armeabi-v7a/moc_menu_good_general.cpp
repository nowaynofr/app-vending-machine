/****************************************************************************
** Meta object code from reading C++ file 'menu_good_general.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Process/menu_good_general.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu_good_general.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_menu_good_general_t {
    QByteArrayData data[10];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_menu_good_general_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_menu_good_general_t qt_meta_stringdata_menu_good_general = {
    {
QT_MOC_LITERAL(0, 0, 17), // "menu_good_general"
QT_MOC_LITERAL(1, 18, 24), // "Signal_Menu_Good_General"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 13), // "MACHINE_STATE"
QT_MOC_LITERAL(4, 58, 30), // "on_Btn_Ok_Menu_General_clicked"
QT_MOC_LITERAL(5, 89, 32), // "on_Btn_Back_Menu_General_clicked"
QT_MOC_LITERAL(6, 122, 45), // "on_Btn_increase_quantity_Menu..."
QT_MOC_LITERAL(7, 168, 45), // "on_Btn_decrease_quantity_Menu..."
QT_MOC_LITERAL(8, 214, 9), // "Back_Home"
QT_MOC_LITERAL(9, 224, 19) // "select_good_clicked"

    },
    "menu_good_general\0Signal_Menu_Good_General\0"
    "\0MACHINE_STATE\0on_Btn_Ok_Menu_General_clicked\0"
    "on_Btn_Back_Menu_General_clicked\0"
    "on_Btn_increase_quantity_Menu_General_clicked\0"
    "on_Btn_decrease_quantity_Menu_General_clicked\0"
    "Back_Home\0select_good_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_menu_good_general[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void menu_good_general::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<menu_good_general *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Menu_Good_General((*reinterpret_cast< MACHINE_STATE(*)>(_a[1]))); break;
        case 1: _t->on_Btn_Ok_Menu_General_clicked(); break;
        case 2: _t->on_Btn_Back_Menu_General_clicked(); break;
        case 3: _t->on_Btn_increase_quantity_Menu_General_clicked(); break;
        case 4: _t->on_Btn_decrease_quantity_Menu_General_clicked(); break;
        case 5: _t->Back_Home((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->select_good_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (menu_good_general::*)(MACHINE_STATE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menu_good_general::Signal_Menu_Good_General)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject menu_good_general::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_menu_good_general.data,
    qt_meta_data_menu_good_general,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *menu_good_general::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *menu_good_general::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_menu_good_general.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int menu_good_general::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void menu_good_general::Signal_Menu_Good_General(MACHINE_STATE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
