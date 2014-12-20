#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include "grpscreen.h"
#include "grp.h"
#include "cardscreen.h"
#include "icon.h"
#include "data.h"

class MainScreen : public QWidget
{
    enum SCREEN_TYPE{LOCAL_GRP_SCREEN,CLOUD_LST_SCREEN,CARD_LST_SCREEN,CARD_INFO_SCREEN};
    enum GRP_SOURCE{LOCAL, CLOUD};
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);
    explicit MainScreen(QScreen *screenInfo, QWidget *parent = 0);
    ~MainScreen();

signals:

public slots:
    void onLocalGrpSelected(int grpId);
    void showGrpScreen(int i);

private:
    GRP_SOURCE grpState = LOCAL;
    int defaultWidth = 720;
    int defaultHeight = 1280;
    QSize screenSize;
    QScreen *screenInfo;
    double scaleFactor = 1;
    QLayout *mainLayout;
    GrpScreen *grpScreen;
    CardScreen *cardScreen;
    Data *dataM;

    void showScreen(SCREEN_TYPE scr);
    void hideAllScreens();

};

#endif // MAINSCREEN_H
