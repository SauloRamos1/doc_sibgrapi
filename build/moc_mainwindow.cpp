/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[395];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_pushButton_released"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 31), // "on_listWidget_currentRowChanged"
QT_MOC_LITERAL(4, 67, 10), // "currentRow"
QT_MOC_LITERAL(5, 78, 30), // "on_contoursampling_sliderMoved"
QT_MOC_LITERAL(6, 109, 8), // "position"
QT_MOC_LITERAL(7, 118, 27), // "on_gridsampling_sliderMoved"
QT_MOC_LITERAL(8, 146, 29), // "on_slider_lshapes_sliderMoved"
QT_MOC_LITERAL(9, 176, 26), // "on_slider_lsym_sliderMoved"
QT_MOC_LITERAL(10, 203, 31), // "on_slider_ldepthsym_sliderMoved"
QT_MOC_LITERAL(11, 235, 29), // "on_slider_lisland_sliderMoved"
QT_MOC_LITERAL(12, 265, 34), // "on_slider_ldepthisland_slider..."
QT_MOC_LITERAL(13, 300, 35), // "on_slider_adjnewcontour_slide..."
QT_MOC_LITERAL(14, 336, 31), // "on_slider_ldepthadj_sliderMoved"
QT_MOC_LITERAL(15, 368, 26) // "on_slider_ladj_sliderMoved"

    },
    "MainWindow\0on_pushButton_released\0\0"
    "on_listWidget_currentRowChanged\0"
    "currentRow\0on_contoursampling_sliderMoved\0"
    "position\0on_gridsampling_sliderMoved\0"
    "on_slider_lshapes_sliderMoved\0"
    "on_slider_lsym_sliderMoved\0"
    "on_slider_ldepthsym_sliderMoved\0"
    "on_slider_lisland_sliderMoved\0"
    "on_slider_ldepthisland_sliderMoved\0"
    "on_slider_adjnewcontour_sliderMoved\0"
    "on_slider_ldepthadj_sliderMoved\0"
    "on_slider_ladj_sliderMoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      13,    1,   99,    2, 0x08 /* Private */,
      14,    1,  102,    2, 0x08 /* Private */,
      15,    1,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_released(); break;
        case 1: _t->on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_contoursampling_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_gridsampling_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_slider_lshapes_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_slider_lsym_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_slider_ldepthsym_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_slider_lisland_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_slider_ldepthisland_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_slider_adjnewcontour_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_slider_ldepthadj_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_slider_ladj_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
