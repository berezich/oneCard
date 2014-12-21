#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include "grpscreen.h"
#include "grp.h"
#include "cardscreen.h"
#include "cardinfoscreen.h"
#include "icon.h"
#include "data.h"
#include "appstate.h"
class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);
    explicit MainScreen(QScreen *screenInfo, QWidget *parent = 0);
    ~MainScreen();

signals:

public slots:
    void onGrpSelected(int grpId);
    void showGrpScreen(int i);
    void showCardScreen(int i);
    void showCardInfoScreen(int i);
private:

    int defaultWidth = 720;
    int defaultHeight = 1280;
    QSize screenSize;
    QScreen *screenInfo;
    double scaleFactor = 1;
    QLayout *mainLayout;

    AppState *appState;
    //GRP_SOURCE grpState = LOCAL;


    Data *dataM;

    GrpScreen *grpScreen;
    CardScreen *cardScreen;
    CardInfoScreen *cardInfoScreen;


    void showScreen(SCREEN_TYPE scr);
    void hideAllScreens();

};

#endif // MAINSCREEN_H
