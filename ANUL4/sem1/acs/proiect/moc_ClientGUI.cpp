/****************************************************************************
** Meta object code from reading C++ file 'ClientGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ClientGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientGUI_t {
    QByteArrayData data[26];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientGUI_t qt_meta_stringdata_ClientGUI = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ClientGUI"
QT_MOC_LITERAL(1, 10, 15), // "applyRemoteEdit"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "text"
QT_MOC_LITERAL(4, 32, 16), // "applyRemoteClear"
QT_MOC_LITERAL(5, 49, 11), // "clearEditor"
QT_MOC_LITERAL(6, 61, 14), // "updateUserList"
QT_MOC_LITERAL(7, 76, 4), // "list"
QT_MOC_LITERAL(8, 81, 12), // "updateStatus"
QT_MOC_LITERAL(9, 94, 3), // "msg"
QT_MOC_LITERAL(10, 98, 13), // "onFileChanged"
QT_MOC_LITERAL(11, 112, 8), // "fileName"
QT_MOC_LITERAL(12, 121, 15), // "onStatusChanged"
QT_MOC_LITERAL(13, 137, 6), // "status"
QT_MOC_LITERAL(14, 144, 7), // "setBold"
QT_MOC_LITERAL(15, 152, 9), // "setItalic"
QT_MOC_LITERAL(16, 162, 12), // "setUnderline"
QT_MOC_LITERAL(17, 175, 16), // "toggleBulletList"
QT_MOC_LITERAL(18, 192, 16), // "toggleNumberList"
QT_MOC_LITERAL(19, 209, 11), // "insertTable"
QT_MOC_LITERAL(20, 221, 15), // "changeTextColor"
QT_MOC_LITERAL(21, 237, 21), // "changeBackgroundColor"
QT_MOC_LITERAL(22, 259, 10), // "changeFont"
QT_MOC_LITERAL(23, 270, 4), // "font"
QT_MOC_LITERAL(24, 275, 14), // "changeFontSize"
QT_MOC_LITERAL(25, 290, 4) // "size"

    },
    "ClientGUI\0applyRemoteEdit\0\0text\0"
    "applyRemoteClear\0clearEditor\0"
    "updateUserList\0list\0updateStatus\0msg\0"
    "onFileChanged\0fileName\0onStatusChanged\0"
    "status\0setBold\0setItalic\0setUnderline\0"
    "toggleBulletList\0toggleNumberList\0"
    "insertTable\0changeTextColor\0"
    "changeBackgroundColor\0changeFont\0font\0"
    "changeFontSize\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x0a /* Public */,
       4,    0,  102,    2, 0x0a /* Public */,
       5,    0,  103,    2, 0x0a /* Public */,
       6,    1,  104,    2, 0x0a /* Public */,
       8,    1,  107,    2, 0x0a /* Public */,
      10,    1,  110,    2, 0x0a /* Public */,
      12,    1,  113,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,
      20,    0,  122,    2, 0x0a /* Public */,
      21,    0,  123,    2, 0x0a /* Public */,
      22,    1,  124,    2, 0x0a /* Public */,
      24,    1,  127,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,   23,
    QMetaType::Void, QMetaType::QString,   25,

       0        // eod
};

void ClientGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientGUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->applyRemoteEdit((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->applyRemoteClear(); break;
        case 2: _t->clearEditor(); break;
        case 3: _t->updateUserList((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onFileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onStatusChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setBold(); break;
        case 8: _t->setItalic(); break;
        case 9: _t->setUnderline(); break;
        case 10: _t->toggleBulletList(); break;
        case 11: _t->toggleNumberList(); break;
        case 12: _t->insertTable(); break;
        case 13: _t->changeTextColor(); break;
        case 14: _t->changeBackgroundColor(); break;
        case 15: _t->changeFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 16: _t->changeFontSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientGUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ClientGUI.data,
    qt_meta_data_ClientGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientGUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ClientGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
