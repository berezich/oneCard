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
    explicit BlankScreen(QScreen *screenInfo, QWidget *parent = 0);
    //explicit BlankScreen(QScreen *screenInfo);
    ~BlankScreen();

signals:

public slots:

protected:
    double scaleFactor = 1;
    QBoxLayout *blankLayout;
    QHBoxLayout *capLayout;
    Cap  *cap;
    QWidget *blankSpace;

private:
    int defaultWidth = 720;
    int defaultHeight = 1280;
    int capHeight = 120;
    int capSpacerH = 50;
    int capRightIconOffset = 40;
    QString title = tr("ВАШИ КАРТЫ");
    int titleLeftMargin = 20;
    int textTitleSize = 15;

    QSize screenSize;
    QScreen *screenInfo;



};

#endif // BLANKSCREEN_H
