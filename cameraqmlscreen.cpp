#include "cameraqmlscreen.h"

CameraQmlScreen::CameraQmlScreen(QSize appScrSize, QWidget *parent) : QWidget(parent)
{
    this->appScrSize = appScrSize;
    setMinimumSize(appScrSize);
    setMaximumSize(appScrSize);
    setContentsMargins(0,0,0,0);
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
    mQQuickWidget->resize(appScrSize);
    mQQuickWidget->raise();
}

CameraQmlScreen::~CameraQmlScreen()
{
    while(this->children().length()>0)
        delete(children().last());
}

void CameraQmlScreen::showQML()
{
    //mQQuickWidget->raise();
}

