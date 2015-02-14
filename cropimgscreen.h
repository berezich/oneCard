#ifndef CROPIMGSCREEN_H
#define CROPIMGSCREEN_H
#include "overlay.h"
#include "QVBoxLayout"
#include <QPainter>
#include <QPoint>
#include <QVBoxLayout>
#include "imgicon.h"
#include "cropper.h"
#include "simpleicon.h"

class CropImgScreen : public Overlay
{
    Q_OBJECT
public:
    CropImgScreen(QSize size, double scale,QString imgSrc,QWidget *parent = 0);
    ~CropImgScreen();
private:
    int frameWidth;
    double scaleFactor;
    QSize screenSize;
    QSize iconSize;
    Cropper *imgIcon;
    Cropper *cropper;
    QVBoxLayout *layout;
    SimpleIcon *iconOk;
    SimpleIcon *iconNo;
    int sideOff;
    void init()
    {
        sideOff = 20;
        iconSize = QSize(100,100);
        frameWidth = 5;
    }
private slots:
    void onIconPressed(int i);
};

#endif // CROPIMGSCREEN_H
