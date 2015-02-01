#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <QBasicTimer>
#include <QPainter>
#include <QTimerEvent>
#include <QVBoxLayout>
#include "overlay.h"
#include "spinner.h"
#include "qmath.h"


class LoadingScreen : public Overlay
{
public:
    LoadingScreen(QSize size, double scale,QString msg,QWidget *parent = 0);
    ~LoadingScreen();
private:
    QSize screenSize;
    double scaleFactor;
    double msgTxtSize;
    QString msgTxtColor;
    QString msg;
    double fontSize;
    QString txtColor;
    QFont *font;
    int txtOffset;
    int txtBottomOffset;
    QPen *pen;

    int frameCenterOffset;
    QPoint rectPoint;
    QSize rectSize;
    qreal xRound;
    qreal yRound;
    QString backGroundColor;
    Spinner *spin;
    //QWidget *msgFrame;


    //QBasicTimer timer;
    int angel;



    QVBoxLayout *scrLayout;

    void paintEvent(QPaintEvent *e);
    //void timerEvent(QTimerEvent *event);

    void init()
    {
        fontSize = 18;
        txtColor = "#000000";
        txtOffset = 15;
        txtBottomOffset = 130;
        xRound = 4;
        yRound = 4;
        frameCenterOffset = 70;
        rectSize = QSize(550,250);
        backGroundColor = "#e5e5e5";
        //spinSize = QSize(70,70);
        //spinImgSrc = ":/svg/tools/spinner.svg";
        angel = 0;
    }
};

#endif // LOADINGSCREEN_H
