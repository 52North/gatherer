TEMPLATE = app

QT += qml quick widgets positioning network
QT += quick

HEADERS += \
    dataobject.h \
    downloadtemplate.h \
    qtquickcontrolsapplication.h \
    currentobservation.h \
    options.h

SOURCES += main.cpp \
    dataobject.cpp \
    downloadtemplate.cpp \
    currentobservation.cpp \
    options.cpp

RESOURCES += qml.qrc



# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


