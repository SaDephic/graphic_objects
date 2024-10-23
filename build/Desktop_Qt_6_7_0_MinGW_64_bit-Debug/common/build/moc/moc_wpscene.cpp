/****************************************************************************
** Meta object code from reading C++ file 'wpscene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../view/workplace/wpscene.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wpscene.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSwpsceneENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSwpsceneENDCLASS = QtMocHelpers::stringData(
    "wpscene",
    "addNode",
    "",
    "addRTL",
    "addTTL",
    "addCW",
    "addCM",
    "addMK",
    "setCenter",
    "paintMidArea",
    "splitLine",
    "gline*",
    "line",
    "saveMiddlePos",
    "nullCenter"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwpsceneENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x0a,    1 /* Public */,
       3,    0,   81,    2, 0x0a,    2 /* Public */,
       4,    0,   82,    2, 0x0a,    3 /* Public */,
       5,    0,   83,    2, 0x0a,    4 /* Public */,
       6,    0,   84,    2, 0x0a,    5 /* Public */,
       7,    0,   85,    2, 0x0a,    6 /* Public */,
       8,    0,   86,    2, 0x0a,    7 /* Public */,
       9,    0,   87,    2, 0x0a,    8 /* Public */,
      10,    1,   88,    2, 0x08,    9 /* Private */,
      13,    0,   91,    2, 0x08,   11 /* Private */,
      14,    0,   92,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject wpscene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_CLASSwpsceneENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwpsceneENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwpsceneENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<wpscene, std::true_type>,
        // method 'addNode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addRTL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addTTL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addCW'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addMK'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCenter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintMidArea'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'splitLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<gline *, std::false_type>,
        // method 'saveMiddlePos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nullCenter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void wpscene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<wpscene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addNode(); break;
        case 1: _t->addRTL(); break;
        case 2: _t->addTTL(); break;
        case 3: _t->addCW(); break;
        case 4: _t->addCM(); break;
        case 5: _t->addMK(); break;
        case 6: _t->setCenter(); break;
        case 7: _t->paintMidArea(); break;
        case 8: _t->splitLine((*reinterpret_cast< std::add_pointer_t<gline*>>(_a[1]))); break;
        case 9: _t->saveMiddlePos(); break;
        case 10: _t->nullCenter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< gline* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *wpscene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wpscene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwpsceneENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int wpscene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
