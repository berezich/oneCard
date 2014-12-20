QT += widgets
QT += xml svg
QTPLUGIN += qsvg

HEADERS       = button.h \
    blankscreen.h \
    icon.h \
    grp.h \
    mainscreen.h \
    grpscreen.h \
    data.h \
    cap.h \
    simpleicon.h \
    cardscreen.h \
    cardinfo.h
SOURCES       = button.cpp \
                main.cpp \
    blankscreen.cpp \
    icon.cpp \
    grp.cpp \
    mainscreen.cpp \
    grpscreen.cpp \
    data.cpp \
    cap.cpp \
    simpleicon.cpp \
    cardscreen.cpp \
    cardinfo.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/oneCard
INSTALLS += target

RESOURCES += \
    onecard_res.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
    android/res/drawable-hdpi/icon.png
    android/res/drawable-ldpi/icon.png
    android/res/drawable-mdpi/icon.png

DISTFILES +=
