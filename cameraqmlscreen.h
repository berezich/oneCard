#ifndef CAMERAQMLSCREEN_H
#define CAMERAQMLSCREEN_H

#include <QWidget>
#include <QQuickWidget>
#include <QQuickView>

class CameraQmlScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CameraQmlScreen(QSize appScrSize, QWidget *parent = 0);
    ~CameraQmlScreen();

signals:
    void pressBack();

public slots:
    void showQML();
private:
    QQuickWidget *mQQuickWidget;
    QSize appScrSize;

};

#endif // CAMERAQMLSCREEN_H
