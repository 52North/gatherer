TEMPLATE = app

QT += qml quick widgets
QT += quick androidextras

HEADERS += message.h \
    dataobject.h

SOURCES += main.cpp \
    dataobject.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)



