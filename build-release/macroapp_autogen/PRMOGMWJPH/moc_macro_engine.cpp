/****************************************************************************
** Meta object code from reading C++ file 'macro_engine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/macro_engine.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macro_engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN11MacroEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto MacroEngine::qt_create_metaobjectdata<qt_meta_tag_ZN11MacroEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MacroEngine",
        "eventCaptured",
        "",
        "MacroEvent",
        "event",
        "recordingStarted",
        "recordingStopped",
        "playbackStarted",
        "playbackStopped"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'eventCaptured'
        QtMocHelpers::SignalData<void(const MacroEvent &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'recordingStarted'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'recordingStopped'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playbackStarted'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playbackStopped'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MacroEngine, qt_meta_tag_ZN11MacroEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MacroEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MacroEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MacroEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MacroEngineE_t>.metaTypes,
    nullptr
} };

void MacroEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MacroEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->eventCaptured((*reinterpret_cast< std::add_pointer_t<MacroEvent>>(_a[1]))); break;
        case 1: _t->recordingStarted(); break;
        case 2: _t->recordingStopped(); break;
        case 3: _t->playbackStarted(); break;
        case 4: _t->playbackStopped(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MacroEngine::*)(const MacroEvent & )>(_a, &MacroEngine::eventCaptured, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacroEngine::*)()>(_a, &MacroEngine::recordingStarted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacroEngine::*)()>(_a, &MacroEngine::recordingStopped, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacroEngine::*)()>(_a, &MacroEngine::playbackStarted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacroEngine::*)()>(_a, &MacroEngine::playbackStopped, 4))
            return;
    }
}

const QMetaObject *MacroEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MacroEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MacroEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MacroEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MacroEngine::eventCaptured(const MacroEvent & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MacroEngine::recordingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MacroEngine::recordingStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MacroEngine::playbackStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MacroEngine::playbackStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
