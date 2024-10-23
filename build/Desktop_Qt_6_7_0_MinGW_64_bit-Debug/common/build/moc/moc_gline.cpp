/****************************************************************************
** Meta object code from reading C++ file 'gline.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../elements/simple/line/gline.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSglineENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSglineENDCLASS = QtMocHelpers::stringData(
    "gline",
    "updateLine",
    "",
    "splitLine",
    "gline*",
    "line",
    "removeSelf",
    "editSelf",
    "updateMid",
    "splitItem",
    "repairItem",
    "gpoint*",
    "p",
    "setSubOrder",
    "editItem",
    "paintAll",
    "paintLine"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSglineENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    1,   81,    2, 0x06,    2 /* Public */,
       6,    1,   84,    2, 0x06,    4 /* Public */,
       7,    1,   87,    2, 0x06,    6 /* Public */,
       8,    0,   90,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   91,    2, 0x08,    9 /* Private */,
      10,    1,   92,    2, 0x08,   10 /* Private */,
      13,    0,   95,    2, 0x08,   12 /* Private */,
      14,    0,   96,    2, 0x08,   13 /* Private */,
      15,    0,   97,    2, 0x08,   14 /* Private */,
      16,    0,   98,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject gline::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSglineENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSglineENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSglineENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gline, std::true_type>,
        // method 'updateLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'splitLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gline *, std::false_type>,
        // method 'removeSelf'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gline *, std::false_type>,
        // method 'editSelf'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gline *, std::false_type>,
        // method 'updateMid'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'splitItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'repairItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gpoint *, std::false_type>,
        // method 'setSubOrder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void gline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gline *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateLine(); break;
        case 1: _t->splitLine((*reinterpret_cast< std::add_pointer_t<gline*>>(_a[1]))); break;
        case 2: _t->removeSelf((*reinterpret_cast< std::add_pointer_t<gline*>>(_a[1]))); break;
        case 3: _t->editSelf((*reinterpret_cast< std::add_pointer_t<gline*>>(_a[1]))); break;
        case 4: _t->updateMid(); break;
        case 5: _t->splitItem(); break;
        case 6: _t->repairItem((*reinterpret_cast< std::add_pointer_t<gpoint*>>(_a[1]))); break;
        case 7: _t->setSubOrder(); break;
        case 8: _t->editItem(); break;
        case 9: _t->paintAll(); break;
        case 10: _t->paintLine(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gline* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gline* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gline* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gpoint* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gline::*)();
            if (_t _q_method = &gline::updateLine; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gline::*)(gline * );
            if (_t _q_method = &gline::splitLine; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (gline::*)(gline * );
            if (_t _q_method = &gline::removeSelf; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (gline::*)(gline * );
            if (_t _q_method = &gline::editSelf; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (gline::*)();
            if (_t _q_method = &gline::updateMid; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *gline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gline::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSglineENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    return QObject::qt_metacast(_clname);
}

int gline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void gline::updateLine()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void gline::splitLine(gline * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void gline::removeSelf(gline * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void gline::editSelf(gline * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void gline::updateMid()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
