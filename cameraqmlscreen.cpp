#include "cameraqmlscreen.h"

CameraQmlScreen::CameraQmlScreen(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(720, 1280);
    setMaximumSize(720, 1280);
    setContentsMargins(0,0,0,0);
    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setContentsMargins(0,0,0,0);
    container->setMinimumSize(720, 1280);
    container->setMaximumSize(720, 1280);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("qrc:/rect.qml"));
}

CameraQmlScreen::~CameraQmlScreen()
{
    while(this->children().length()>0)
        delete(children().last());
}

