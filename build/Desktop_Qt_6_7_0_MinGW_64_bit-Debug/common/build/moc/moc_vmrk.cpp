/****************************************************************************
** Meta object code from reading C++ file 'vmrk.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../view/eledit/vmrk.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vmrk.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSvmrkENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSvmrkENDCLASS = QtMocHelpers::stringData(
    "vmrk",
    "updateView",
    "",
    "closed",
    "restore",
    "changedStyle",
    "t",
    "changedSize",
    "size",
    "changedText",
    "showColor",
    "updateColor",
    "col",
    "colorAccept",
    "colorReject",
    "confirm"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSvmrkENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,
       4,    0,   82,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   83,    2, 0x08,    4 /* Private */,
       7,    1,   86,    2, 0x08,    6 /* Private */,
       9,    1,   89,    2, 0x08,    8 /* Private */,
      10,    0,   92,    2, 0x08,   10 /* Private */,
      11,    1,   93,    2, 0x08,   11 /* Private */,
      13,    0,   96,    2, 0x08,   13 /* Private */,
      14,    0,   97,    2, 0x08,   14 /* Private */,
      15,    0,   98,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject vmrk::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSvmrkENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSvmrkENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSvmrkENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<vmrk, std::true_type>,
        // method 'updateView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changedStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'changedText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'colorAccept'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'colorReject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'confirm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void vmrk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vmrk *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->closed(); break;
        case 2: _t->restore(); break;
        case 3: _t->changedStyle((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->changedSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->changedText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->showColor(); break;
        case 7: _t->updateColor((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 8: _t->colorAccept(); break;
        case 9: _t->colorReject(); break;
        case 10: _t->confirm(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vmrk::*)();
            if (_t _q_method = &vmrk::updateView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vmrk::*)();
            if (_t _q_method = &vmrk::closed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (vmrk::*)();
            if (_t _q_method = &vmrk::restore; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *vmrk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vmrk::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSvmrkENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vmrk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void vmrk::updateView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void vmrk::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void vmrk::restore()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
