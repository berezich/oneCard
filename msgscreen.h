#ifndef MSGSCREEN_H
#define MSGSCREEN_H
#include <QBasicTimer>
#include <QPainter>
#include <QTimerEvent>
#include <QVBoxLayout>
#include "overlay.h"
#include "spinner.h"
#include "qmath.h"
#include "simpleicon.h"


class MsgScreen : public Overlay
{
    Q_OBJECT
public:
    MsgScreen(QSize size, double scale,QString msg,QWidget *parent = 0);
    ~MsgScreen();
    void showSpinner(bool val);
    void showOkIcon(bool val);
    void setMsgText(QString txt){msg = txt;}
private slots:
    void onIconPressed(){this->hide();}
private:
    QSize screenSize;
    double scaleFactor;
    double msgTxtSize;
    QString msgTxtColor;
    QString msg;
    double fontSize;
    QString txtColor;
    int txtOffset;
    int txtBottomOffset;
    QWidget *iconWidget;

    int frameCenterOffset;
    QPoint rectPoint;
    QSize rectSize;
    qreal xRound;
    qreal yRound;
    QString backGroundColor;
    Spinner *spin;
    QSize iconSize;

    int angel;

    QVBoxLayout *scrLayout;

    void paintEvent(QPaintEvent *e);

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
        iconSize = QSize(70,70);
        angel = 0;
        spin=NULL;
        iconWidget = NULL;
    }
};

#endif // MSGSCREEN_H
