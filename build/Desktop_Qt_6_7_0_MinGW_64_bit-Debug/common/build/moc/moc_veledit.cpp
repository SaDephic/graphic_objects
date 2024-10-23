/****************************************************************************
** Meta object code from reading C++ file 'veledit.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../view/veledit.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'veledit.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSveleditENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSveleditENDCLASS = QtMocHelpers::stringData(
    "veledit",
    "setIO",
    "",
    "gline*",
    "item",
    "setCM",
    "cam*",
    "setMK",
    "mark*",
    "setTL",
    "trafficlight*",
    "hideAll",
    "restore",
    "updateIO",
    "updateCM",
    "updateMK",
    "updateTL"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSveleditENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x0a,    1 /* Public */,
       5,    1,   77,    2, 0x0a,    3 /* Public */,
       7,    1,   80,    2, 0x0a,    5 /* Public */,
       9,    1,   83,    2, 0x0a,    7 /* Public */,
      11,    0,   86,    2, 0x0a,    9 /* Public */,
      12,    0,   87,    2, 0x08,   10 /* Private */,
      13,    0,   88,    2, 0x08,   11 /* Private */,
      14,    0,   89,    2, 0x08,   12 /* Private */,
      15,    0,   90,    2, 0x08,   13 /* Private */,
      16,    0,   91,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, 0x80000000 | 10,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject veledit::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSveleditENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSveleditENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSveleditENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<veledit, std::true_type>,
        // method 'setIO'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gline *, std::false_type>,
        // method 'setCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<cam *, std::false_type>,
        // method 'setMK'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<mark *, std::false_type>,
        // method 'setTL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<trafficlight *, std::false_type>,
        // method 'hideAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateIO'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateMK'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void veledit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<veledit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setIO((*reinterpret_cast< std::add_pointer_t<gline*>>(_a[1]))); break;
        case 1: _t->setCM((*reinterpret_cast< std::add_pointer_t<cam*>>(_a[1]))); break;
        case 2: _t->setMK((*reinterpret_cast< std::add_pointer_t<mark*>>(_a[1]))); break;
        case 3: _t->setTL((*reinterpret_cast< std::add_pointer_t<trafficlight*>>(_a[1]))); break;
        case 4: _t->hideAll(); break;
        case 5: _t->restore(); break;
        case 6: _t->updateIO(); break;
        case 7: _t->updateCM(); break;
        case 8: _t->updateMK(); break;
        case 9: _t->updateTL(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gline* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< cam* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< mark* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< trafficlight* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *veledit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *veledit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSveleditENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int veledit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
