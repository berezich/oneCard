#ifndef BLANKSCREEN_H
#define BLANKSCREEN_H

#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QtCore/qmath.h>
#include <QScreen>
#include <QSize>
#include <QDebug>
#include <QLabel>
#include "cap.h"
#include "icon.h"
#include "simpleicon.h"
#include "interface.h"

//parent QWidget for all screens with cap

class BlankScreen : public QWidget
{
    Q_OBJECT
public:
    explicit BlankScreen(QWidget *parent = 0);
    BlankScreen(QScreen *screenInfo, QSize appScrSize, int colorName, QWidget *parent = 0);
    ~BlankScreen();

signals:

public slots:

protected:
    double scaleFactor;
    double scaleFactorH;
    double scaleFactorW;
    QBoxLayout *blankLayout;
    QHBoxLayout *capLayout;
    Cap  *cap;
    QSize screenSize;
    int capSpacerH;
    int capHeight;
    int titleLeftMargin;
    double textTitleSize;
    int capRightIconOffset;
    int capLeftIconOffset;
    QString backGroundColor;
    int skinColor;
private:
    int defaultWidth;
    int defaultHeight;
    QString title;
    QScreen *screenInfo;
    void init()
    {
        scaleFactor = 1;
        scaleFactorH = 1;
        scaleFactorW = 1;
        capSpacerH = 20;
        capHeight = 120;
        titleLeftMargin = 20;
        textTitleSize = 20;
        capRightIconOffset = 40;
        capLeftIconOffset = 10;
        backGroundColor = "#e5e5e5";

        defaultWidth = 720;
        defaultHeight = 1230;
        title = tr("ВАШИ КАРТЫ");
    }


};

#endif // BLANKSCREEN_H
