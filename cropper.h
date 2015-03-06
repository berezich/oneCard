#ifndef CROPPER_H
#define CROPPER_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>
#include "imgicon.h"

class Cropper : public ImgIcon
{
    Q_OBJECT
public:
    explicit Cropper(double scale, int id,QString imgScr,  QSize imgSize, bool isExpand=true, QWidget *parent=0);
    ~Cropper();
    void saveCropImg(QString file);
signals:

public slots:
private:
    int frameWidth=5;
    QPoint curPos;
    QPoint startPos;
    QSize screenSize;
    QSize imgSize;
    QString imageSrc;
    int sideOff;
    int bottomOff;
    int topOffset;
    double scaleFactor;
    bool event(QEvent *e);
    void paintEvent(QPaintEvent *e);
};

#endif // CROPPER_H
