/****************************************************************************
** Meta object code from reading C++ file 'DeckManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../DeckManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeckManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11DeckManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto DeckManager::qt_create_metaobjectdata<qt_meta_tag_ZN11DeckManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DeckManager",
        "deckChanged",
        "",
        "deckError",
        "message",
        "addCard",
        "Card*",
        "card",
        "addCommander",
        "removeCard",
        "id",
        "removeCommander",
        "quantity",
        "isInDeck",
        "isLegalForCommander",
        "categoryForCard",
        "entries",
        "QVariantList",
        "category",
        "commanders",
        "clearDeck",
        "saveDeck",
        "filePath",
        "loadDeck",
        "exportDeck",
        "cardCount",
        "commanderCount",
        "commanderColors"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'deckChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'deckError'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Method 'addCard'
        QtMocHelpers::MethodData<bool(Card *)>(5, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'addCommander'
        QtMocHelpers::MethodData<bool(Card *)>(8, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'removeCard'
        QtMocHelpers::MethodData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'removeCommander'
        QtMocHelpers::MethodData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'quantity'
        QtMocHelpers::MethodData<int(const QString &) const>(12, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'isInDeck'
        QtMocHelpers::MethodData<bool(const QString &) const>(13, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'isLegalForCommander'
        QtMocHelpers::MethodData<bool(Card *) const>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'categoryForCard'
        QtMocHelpers::MethodData<QString(Card *) const>(15, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'entries'
        QtMocHelpers::MethodData<QVariantList(const QString &) const>(16, 2, QMC::AccessPublic, 0x80000000 | 17, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'commanders'
        QtMocHelpers::MethodData<QVariantList() const>(19, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Method 'clearDeck'
        QtMocHelpers::MethodData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveDeck'
        QtMocHelpers::MethodData<bool(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'loadDeck'
        QtMocHelpers::MethodData<bool(const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'exportDeck'
        QtMocHelpers::MethodData<bool(const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'cardCount'
        QtMocHelpers::PropertyData<int>(25, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'commanderCount'
        QtMocHelpers::PropertyData<int>(26, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'commanderColors'
        QtMocHelpers::PropertyData<QStringList>(27, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DeckManager, qt_meta_tag_ZN11DeckManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DeckManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11DeckManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11DeckManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11DeckManagerE_t>.metaTypes,
    nullptr
} };

void DeckManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeckManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->deckChanged(); break;
        case 1: _t->deckError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: { bool _r = _t->addCard((*reinterpret_cast<std::add_pointer_t<Card*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->addCommander((*reinterpret_cast<std::add_pointer_t<Card*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->removeCard((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->removeCommander((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: { int _r = _t->quantity((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->isInDeck((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->isLegalForCommander((*reinterpret_cast<std::add_pointer_t<Card*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->categoryForCard((*reinterpret_cast<std::add_pointer_t<Card*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->entries((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->commanders();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->clearDeck(); break;
        case 13: { bool _r = _t->saveDeck((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->loadDeck((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->exportDeck((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Card* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Card* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Card* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Card* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DeckManager::*)()>(_a, &DeckManager::deckChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DeckManager::*)(const QString & )>(_a, &DeckManager::deckError, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->cardCount(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->commanderCount(); break;
        case 2: *reinterpret_cast<QStringList*>(_v) = _t->commanderColors(); break;
        default: break;
        }
    }
}

const QMetaObject *DeckManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeckManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11DeckManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeckManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DeckManager::deckChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeckManager::deckError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
