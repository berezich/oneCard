QT += widgets quick qml quickwidgets core gui xml svg multimedia
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
    menuitem.h \
    titlemenu.h \
    cameraqmlscreen.h \
    server.h \
    httpmanager.h \
    servererrors.h \
    interface.h \
    datalocationtype.h \
    mainchoicescreen.h \
    spinner.h \
    msgscreen.h \
    settings.h \
    swipecover.h \
    cropimgscreen.h \
    cropper.h
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
    menuitem.cpp \
    titlemenu.cpp \
    cameraqmlscreen.cpp \
    server.cpp \
    httpmanager.cpp \
    mainchoicescreen.cpp \
    spinner.cpp \
    msgscreen.cpp \
    settings.cpp \
    swipecover.cpp \
    cropimgscreen.cpp \
    cropper.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/oneCard
INSTALLS += target

RESOURCES += \
    onecard_res.qrc

TRANSLATIONS = onecard_ru.ts \
               onecard_en.ts

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

DISTFILES +=
