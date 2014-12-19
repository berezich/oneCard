#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include "grpscreen.h"
#include "grp.h"
#include "icon.h"
#include "data.h"

class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);
    explicit MainScreen(QScreen *screenInfo, QWidget *parent = 0);
    ~MainScreen();

signals:

public slots:
private:
    int defaultWidth = 720;
    int defaultHeight = 1280;
    QSize screenSize;
    QScreen *screenInfo;
    double scaleFactor = 1;
    QLayout *mainLayout;
    GrpScreen *grpScreen;
    Data *dataM;


};

#endif // MAINSCREEN_H
