TEMPLATE = app

QT += qml quick

QT += xml svg

QTPLUGIN += qsvg

SOURCES += main.cpp

RESOURCES += qml.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=
