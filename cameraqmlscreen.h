#ifndef CAMERAQMLSCREEN_H
#define CAMERAQMLSCREEN_H

#include <QWidget>
#include <QQuickView>

class CameraQmlScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CameraQmlScreen(QWidget *parent = 0);
    ~CameraQmlScreen();

signals:
    void pressBack();
public slots:

};

#endif // CAMERAQMLSCREEN_H
