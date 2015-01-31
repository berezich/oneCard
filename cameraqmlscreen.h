#ifndef CAMERAQMLSCREEN_H
#define CAMERAQMLSCREEN_H

#include <QWidget>
#include <QQuickWidget>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>

class CameraQmlScreen : public QWidget
{
    Q_OBJECT
public:
    CameraQmlScreen(QWidget *parent = 0);
    CameraQmlScreen(QSize appScrSize,QString os, QWidget *parent = 0);
    ~CameraQmlScreen();

signals:
    void pressedCancel();
    void selectPhoto(QString,QString);

public slots:
    void showQML();
    void onPhotoOk(QString file);
    void closeCamera();
private:
    QQuickWidget *mQQuickWidget;
    QSize appScrSize;

};

#endif // CAMERAQMLSCREEN_H
