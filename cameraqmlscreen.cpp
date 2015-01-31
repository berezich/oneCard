#include "cameraqmlscreen.h"

CameraQmlScreen::CameraQmlScreen(QWidget *parent): QWidget(parent)
{

}

CameraQmlScreen::CameraQmlScreen(QSize appScrSize, QString os, QWidget *parent) : QWidget(parent)
{
    this->appScrSize = appScrSize;
    setMaximumSize(window()->geometry().size());

    mQQuickWidget = new QQuickWidget(QUrl("qrc:/declarative-camera/declarative-camera.qml"), this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(window()->geometry().size());
    mQQuickWidget->rootContext()->setContextProperty("myApp", this);
    //mQQuickWidget->setProperty("os", os);
    //mQQuickWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mQQuickWidget->raise();

}

CameraQmlScreen::~CameraQmlScreen()
{
    while(this->children().length()>0)
        delete(children().last());
}

void CameraQmlScreen::showQML()
{
    /*
    mQQuickWidget = new QQuickWidget(QUrl("qrc:/declarative-camera/declarative-camera.qml"), this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->rootContext()->setContextProperty("myApp", this);
    mQQuickWidget->raise();
    */

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

