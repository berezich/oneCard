#include "cameraqmlscreen.h"

CameraQmlScreen::CameraQmlScreen(QSize appScrSize, QString os, QWidget *parent) : QWidget(parent)
{
    this->appScrSize = appScrSize;
    //setWindowState(Qt::WindowMaximized);
    //setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setMaximumSize(window()->geometry().size());
    //setMaximumSize(appScrSize);
//    QQuickView *view = new QQuickView();
//    QWidget *container = QWidget::createWindowContainer(view, this);
//    container->setContentsMargins(0,0,0,0);
//    container->setMinimumSize(720, 1280);
//    container->setMaximumSize(720, 1280);
//    container->setFocusPolicy(Qt::TabFocus);
//    view->setSource(QUrl("qrc:/rect.qml"));

    mQQuickWidget = new QQuickWidget(QUrl("qrc:/declarative-camera/declarative-camera.qml"), this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(window()->geometry().size());
    mQQuickWidget->rootContext()->setContextProperty("myApp", this);
    //mQQuickWidget->setProperty("os", os);
    //mQQuickWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mQQuickWidget->raise();
    //mQQuickWidget->setUpdatesEnabled(true);
}

CameraQmlScreen::~CameraQmlScreen()
{
    while(this->children().length()>0)
        delete(children().last());
}

void CameraQmlScreen::showQML()
{
    show();
    setMaximumSize(window()->geometry().size());
    mQQuickWidget->resize(window()->geometry().size());
}

void CameraQmlScreen::onPhotoOk(QString file)
{
    qDebug()<< "onPhotoOk file!!! = "<<file;
    QString fileName =  file.split('/').last();
    QString dir = file.left(file.lastIndexOf("/")+1);

    emit selectPhoto(dir,fileName);
}

void CameraQmlScreen::closeCamera()
{
    qDebug()<< "closeCamera!!!";
    emit pressedCancel();
}

