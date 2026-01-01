/****************************************************************************
** Meta object code from reading C++ file 'socket.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../socket.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socket.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6SocketE_t {};
} // unnamed namespace

template <> constexpr inline auto Socket::qt_create_metaobjectdata<qt_meta_tag_ZN6SocketE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Socket",
        "stateChanged",
        "",
        "usernameChanged",
        "state",
        "STATES",
        "username",
        "sendUsername",
        "onConnection",
        "CONNECTING",
        "RECONNECTING",
        "AUTHENTICATION",
        "MENU",
        "ROOM",
        "EVENTS",
        "CONNECTED",
        "DISCONNECTED",
        "USERNAME_ESTABLISHED"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'stateChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'usernameChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'state'
        QtMocHelpers::SlotData<STATES()>(4, 2, QMC::AccessPublic, 0x80000000 | 5),
        // Slot 'username'
        QtMocHelpers::SlotData<QString()>(6, 2, QMC::AccessPublic, QMetaType::QString),
        // Slot 'sendUsername'
        QtMocHelpers::SlotData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'onConnection'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'state'
        QtMocHelpers::PropertyData<STATES>(4, 0x80000000 | 5, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'username'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'STATES'
        QtMocHelpers::EnumData<STATES>(5, 5, QMC::EnumFlags{}).add({
            {    9, STATES::CONNECTING },
            {   10, STATES::RECONNECTING },
            {   11, STATES::AUTHENTICATION },
            {   12, STATES::MENU },
            {   13, STATES::ROOM },
        }),
        // enum 'EVENTS'
        QtMocHelpers::EnumData<EVENTS>(14, 14, QMC::EnumFlags{}).add({
            {   15, EVENTS::CONNECTED },
            {   16, EVENTS::DISCONNECTED },
            {   17, EVENTS::USERNAME_ESTABLISHED },
        }),
    };
    return QtMocHelpers::metaObjectData<Socket, qt_meta_tag_ZN6SocketE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Socket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6SocketE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6SocketE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6SocketE_t>.metaTypes,
    nullptr
} };

void Socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Socket *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->usernameChanged(); break;
        case 2: { STATES _r = _t->state();
            if (_a[0]) *reinterpret_cast< STATES*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->username();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->sendUsername((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onConnection(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Socket::*)()>(_a, &Socket::stateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Socket::*)()>(_a, &Socket::usernameChanged, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<STATES*>(_v) = _t->state(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->username(); break;
        default: break;
        }
    }
}

const QMetaObject *Socket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Socket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6SocketE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Socket::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Socket::usernameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
