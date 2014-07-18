TEMPLATE = app

QT += qml quick widgets
QT += quick

HEADERS += message.h \
    dataobject.h \
    downloadtemplate.h

SOURCES += main.cpp \
    dataobject.cpp \
    downloadtemplate.cpp

RESOURCES += qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)



