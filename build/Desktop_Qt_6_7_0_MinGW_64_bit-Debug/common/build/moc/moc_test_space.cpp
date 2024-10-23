/****************************************************************************
** Meta object code from reading C++ file 'test_space.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../test_space.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_space.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASStest_spaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASStest_spaceENDCLASS = QtMocHelpers::stringData(
    "test_space",
    "logout",
    "",
    "saveCurrentData",
    "saveHowObject",
    "loadCrossData",
    "setCurrentCross",
    "changeCrossBackMap",
    "openObject",
    "showPermissions",
    "swapuser"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASStest_spaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject test_space::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASStest_spaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASStest_spaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASStest_spaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<test_space, std::true_type>,
        // method 'logout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveCurrentData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveHowObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadCrossData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCurrentCross'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeCrossBackMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPermissions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'swapuser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void test_space::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_space *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logout(); break;
        case 1: _t->saveCurrentData(); break;
        case 2: _t->saveHowObject(); break;
        case 3: _t->loadCrossData(); break;
        case 4: _t->setCurrentCross(); break;
        case 5: _t->changeCrossBackMap(); break;
        case 6: _t->openObject(); break;
        case 7: _t->showPermissions(); break;
        case 8: _t->swapuser(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (test_space::*)();
            if (_t _q_method = &test_space::logout; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *test_space::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_space::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASStest_spaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int test_space::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void test_space::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
