/****************************************************************************
** Meta object code from reading C++ file 'vcam.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../view/eledit/vcam.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vcam.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSvcamENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSvcamENDCLASS = QtMocHelpers::stringData(
    "vcam",
    "updateView",
    "",
    "closed",
    "restore",
    "changedCamSize",
    "size",
    "changedName",
    "t",
    "changedTextSize",
    "changedUrl",
    "changedStop",
    "changedUp",
    "changedDown",
    "changedLeft",
    "changedRight",
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

Q_CONSTINIT static const uint qt_meta_data_CLASSvcamENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x06,    1 /* Public */,
       3,    0,  117,    2, 0x06,    2 /* Public */,
       4,    0,  118,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,  119,    2, 0x08,    4 /* Private */,
       7,    1,  122,    2, 0x08,    6 /* Private */,
       9,    1,  125,    2, 0x08,    8 /* Private */,
      10,    1,  128,    2, 0x08,   10 /* Private */,
      11,    1,  131,    2, 0x08,   12 /* Private */,
      12,    1,  134,    2, 0x08,   14 /* Private */,
      13,    1,  137,    2, 0x08,   16 /* Private */,
      14,    1,  140,    2, 0x08,   18 /* Private */,
      15,    1,  143,    2, 0x08,   20 /* Private */,
      16,    0,  146,    2, 0x08,   22 /* Private */,
      17,    1,  147,    2, 0x08,   23 /* Private */,
      19,    0,  150,    2, 0x08,   25 /* Private */,
      20,    0,  151,    2, 0x08,   26 /* Private */,
      21,    0,  152,    2, 0x08,   27 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject vcam::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSvcamENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSvcamENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSvcamENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<vcam, std::true_type>,
        // method 'updateView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changedCamSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'changedName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedTextSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'changedUrl'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedLeft'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changedRight'
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

void vcam::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vcam *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->closed(); break;
        case 2: _t->restore(); break;
        case 3: _t->changedCamSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->changedName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->changedTextSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->changedUrl((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->changedStop((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->changedUp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->changedDown((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->changedLeft((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->changedRight((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->showColor(); break;
        case 13: _t->updateColor((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 14: _t->colorAccept(); break;
        case 15: _t->colorReject(); break;
        case 16: _t->confirm(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vcam::*)();
            if (_t _q_method = &vcam::updateView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vcam::*)();
            if (_t _q_method = &vcam::closed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (vcam::*)();
            if (_t _q_method = &vcam::restore; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *vcam::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vcam::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSvcamENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vcam::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void vcam::updateView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void vcam::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void vcam::restore()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
