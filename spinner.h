#ifndef SPINNER_H
#define SPINNER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QSize>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDebug>

class Spinner : public QWidget
{
    Q_OBJECT
public:
    explicit Spinner(double scale,QWidget *parent = 0);
    ~Spinner();

signals:

public slots:
private:
    QSize screenSize;
    QSize spinSize;
    QString spinImgSrc;
    int angel;
    int startAngle;
    int spanAngle;
    QImage *image;
    QPoint imgPos;
    int penWidth;
    QString spinColor;
    QString spinColor1;
    QBasicTimer timer;
    QPen *pen;
    QPen *pen1;
    QRectF *rectangle;
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void init()
    {
        angel = 0;
        startAngle = 0;
        spanAngle = 340;
        penWidth = 10;
        spinColor = "#8e0606";
        //spinColor1 = "#9a4848";
        spinColor1 = "#955f5f";
        spinSize = QSize(70,70);
        spinImgSrc = ":/svg/tools/spinner.svg";
    }
};

#endif // SPINNER_H
