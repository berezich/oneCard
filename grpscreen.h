#ifndef GRPSCREEN_H
#define GRPSCREEN_H
#include "blankscreen.h"
#include <QSize>
#include <QApplication>
#include "grp.h"
#include "icon.h"
//#include "overlay.h"
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
#include "menu.h"
#include "blankspace.h"

class GrpScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit GrpScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit GrpScreen(QScreen *screenInfo,QSize appScrSize, SKIN_COLOR_NAME colorName,QWidget *parent=0);
    void showMenu();
    void initMenu();
    void onKeyBackPressed(QKeyEvent *event);
    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst);
protected:
   //BlankSpace *blankSpace;
    QWidget *blankSpace;
signals:
    void selectLocalGrp(int grpId);
private slots:
    void onClickGrpIcon(int grpId);
    void onMenuClick();
private:
    int columnsNum = 3;
    int rowsNum = 4;
    QSize iconSize = QSize(170,170);
    double textSize = 15;
    QString title=tr("ВАШИ КАРТЫ");
    QScrollArea *scroll;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    Menu *menuWidget;
    //OverLay *overlay;
    //void resizeEvent(QResizeEvent *event);
};

#endif // GRPSCREEN_H
