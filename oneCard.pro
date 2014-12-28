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
    cardinfo.h \
    cardinfoscreen.h \
    appstate.h \
    galeryscreen.h \
    imgicon.h \
    overlay.h \
    newgrpmodal.h \
    menu.h \
    blankspace.h \
    menuitem.h \
    titlemenu.h
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
    cardinfo.cpp \
    cardinfoscreen.cpp \
    appstate.cpp \
    galeryscreen.cpp \
    imgicon.cpp \
    overlay.cpp \
    newgrpmodal.cpp \
    menu.cpp \
    blankspace.cpp \
    menuitem.cpp \
    titlemenu.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/oneCard
INSTALLS += target

RESOURCES += \
    onecard_res.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

DISTFILES +=
