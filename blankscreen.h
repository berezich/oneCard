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

class BlankScreen : public QWidget
{
    Q_OBJECT
public:
    explicit BlankScreen(QWidget *parent = 0);
    //explicit BlankScreen(QScreen *screenInfo, QWidget *parent = 0);
    explicit BlankScreen(QScreen *screenInfo, QSize appScrSize, QWidget *parent = 0);
    //explicit BlankScreen(QScreen *screenInfo);
    ~BlankScreen();

signals:

public slots:

protected:
    double scaleFactor = 1;
    double scaleFactorH = 1;
    double scaleFactorW = 1;
    QBoxLayout *blankLayout;
    QHBoxLayout *capLayout;
    Cap  *cap;
    QWidget *blankSpace;
    QSize screenSize;
    int capSpacerH = 20;
    int capHeight = 120;
    int titleLeftMargin = 20;
    double textTitleSize = 20;
    int capRightIconOffset = 40;
    int capLeftIconOffset = 10;
    QString backGroundColor = "#e5e5e5";
private:
    int defaultWidth = 720;
    int defaultHeight = 1280;




    QString title = tr("ВАШИ КАРТЫ");
    QScreen *screenInfo;



};

#endif // BLANKSCREEN_H
