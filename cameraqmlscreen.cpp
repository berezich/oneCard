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

    mQQuickWidget->raise();

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
    QString fileName =  file.split('/').last();
    QString dir = file.left(file.lastIndexOf("/")+1);

    emit selectPhoto(dir,fileName);
}

void CameraQmlScreen::closeCamera()
{
    emit pressedCancel();
}

