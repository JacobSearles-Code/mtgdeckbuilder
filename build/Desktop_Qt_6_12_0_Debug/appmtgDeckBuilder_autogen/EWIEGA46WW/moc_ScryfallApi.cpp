/****************************************************************************
** Meta object code from reading C++ file 'ScryfallApi.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ScryfallApi.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScryfallApi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
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
struct qt_meta_tag_ZN11ScryfallApiE_t {};
} // unnamed namespace

template <> constexpr inline auto ScryfallApi::qt_create_metaobjectdata<qt_meta_tag_ZN11ScryfallApiE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ScryfallApi",
        "loadingChanged",
        "",
        "searchFinished",
        "searchError",
        "message",
        "searchCards",
        "query",
        "loadRecommendations",
        "setCommanderColors",
        "colors",
        "searchModel",
        "CardModel*",
        "loading"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'loadingChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchFinished'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchError'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Method 'searchCards'
        QtMocHelpers::MethodData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'loadRecommendations'
        QtMocHelpers::MethodData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setCommanderColors'
        QtMocHelpers::MethodData<void(const QStringList &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'searchModel'
        QtMocHelpers::PropertyData<CardModel*>(11, 0x80000000 | 12, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'loading'
        QtMocHelpers::PropertyData<bool>(13, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ScryfallApi, qt_meta_tag_ZN11ScryfallApiE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ScryfallApi::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ScryfallApiE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ScryfallApiE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ScryfallApiE_t>.metaTypes,
    nullptr
} };

void ScryfallApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ScryfallApi *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loadingChanged(); break;
        case 1: _t->searchFinished(); break;
        case 2: _t->searchError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->searchCards((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->loadRecommendations(); break;
        case 5: _t->setCommanderColors((*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ScryfallApi::*)()>(_a, &ScryfallApi::loadingChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScryfallApi::*)()>(_a, &ScryfallApi::searchFinished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScryfallApi::*)(const QString & )>(_a, &ScryfallApi::searchError, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CardModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<CardModel**>(_v) = _t->searchModel(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->loading(); break;
        default: break;
        }
    }
}

const QMetaObject *ScryfallApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScryfallApi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ScryfallApiE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScryfallApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ScryfallApi::loadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ScryfallApi::searchFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ScryfallApi::searchError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
