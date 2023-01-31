QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datatable.cc \
    db_handler.cc \
    db_struct.cc \
    main.cc \
    mainwindow.cc \
    passport.cc

HEADERS += \
    datatable.h \
    db_handler.h \
    db_struct.h \
    mainwindow.h \
    passport.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    db_qt_ru_BY.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
