/****************************************************************************
** Meta object code from reading C++ file 'trafficlight.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../elements/trafficlight/trafficlight.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trafficlight.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSgrabLampENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSgrabLampENDCLASS = QtMocHelpers::stringData(
    "grabLamp",
    "posChanged",
    "",
    "hoverEnterEvent",
    "QGraphicsSceneHoverEvent*",
    "event",
    "hoverLeaveEvent",
    "mousePressEvent",
    "QGraphicsSceneMouseEvent*",
    "mouseMoveEvent",
    "mouseReleaseEvent"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgrabLampENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   51,    2, 0x08,    2 /* Private */,
       6,    1,   54,    2, 0x08,    4 /* Private */,
       7,    1,   57,    2, 0x08,    6 /* Private */,
       9,    1,   60,    2, 0x08,    8 /* Private */,
      10,    1,   63,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 8,    5,
    QMetaType::Void, 0x80000000 | 8,    5,
    QMetaType::Void, 0x80000000 | 8,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject grabLamp::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSgrabLampENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgrabLampENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgrabLampENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<grabLamp, std::true_type>,
        // method 'posChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hoverEnterEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'hoverLeaveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'mouseMoveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'mouseReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>
    >,
    nullptr
} };

void grabLamp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<grabLamp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->posChanged(); break;
        case 1: _t->hoverEnterEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 2: _t->hoverLeaveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 4: _t->mouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 5: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (grabLamp::*)();
            if (_t _q_method = &grabLamp::posChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *grabLamp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *grabLamp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgrabLampENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    return QObject::qt_metacast(_clname);
}

int grabLamp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void grabLamp::posChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASStrafficlightENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASStrafficlightENDCLASS = QtMocHelpers::stringData(
    "trafficlight",
    "removeSelf",
    "",
    "trafficlight*",
    "it",
    "editSelf",
    "linkLight",
    "light",
    "changeState",
    "id",
    "setLLPosition",
    "addLens",
    "AddLamp*",
    "editItem",
    "removeItem",
    "controlLight",
    "lid",
    "deleteAddLamp",
    "lmp"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASStrafficlightENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    1,   77,    2, 0x06,    3 /* Public */,
       6,    1,   80,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   83,    2, 0x08,    7 /* Private */,
      10,    0,   86,    2, 0x08,    9 /* Private */,
      11,    0,   87,    2, 0x08,   10 /* Private */,
      13,    0,   88,    2, 0x08,   11 /* Private */,
      14,    0,   89,    2, 0x08,   12 /* Private */,
      15,    1,   90,    2, 0x08,   13 /* Private */,
      17,    1,   93,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    0x80000000 | 12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 12,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject trafficlight::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASStrafficlightENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASStrafficlightENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASStrafficlightENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<trafficlight, std::true_type>,
        // method 'removeSelf'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<trafficlight *, std::false_type>,
        // method 'editSelf'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<trafficlight *, std::false_type>,
        // method 'linkLight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'changeState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setLLPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addLens'
        QtPrivate::TypeAndForceComplete<AddLamp *, std::false_type>,
        // method 'editItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'controlLight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'deleteAddLamp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AddLamp *, std::false_type>
    >,
    nullptr
} };

void trafficlight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<trafficlight *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->removeSelf((*reinterpret_cast< std::add_pointer_t<trafficlight*>>(_a[1]))); break;
        case 1: _t->editSelf((*reinterpret_cast< std::add_pointer_t<trafficlight*>>(_a[1]))); break;
        case 2: _t->linkLight((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->changeState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->setLLPosition(); break;
        case 5: { AddLamp* _r = _t->addLens();
            if (_a[0]) *reinterpret_cast< AddLamp**>(_a[0]) = std::move(_r); }  break;
        case 6: _t->editItem(); break;
        case 7: _t->removeItem(); break;
        case 8: _t->controlLight((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->deleteAddLamp((*reinterpret_cast< std::add_pointer_t<AddLamp*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< trafficlight* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< trafficlight* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< AddLamp* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (trafficlight::*)(trafficlight * );
            if (_t _q_method = &trafficlight::removeSelf; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (trafficlight::*)(trafficlight * );
            if (_t _q_method = &trafficlight::editSelf; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (trafficlight::*)(QString );
            if (_t _q_method = &trafficlight::linkLight; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *trafficlight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *trafficlight::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASStrafficlightENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    return QObject::qt_metacast(_clname);
}

int trafficlight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void trafficlight::removeSelf(trafficlight * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void trafficlight::editSelf(trafficlight * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void trafficlight::linkLight(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
