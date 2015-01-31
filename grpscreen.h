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
//#include "blankspace.h"

class GrpScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit GrpScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit GrpScreen(QWidget *parent=0);
    GrpScreen(QScreen *screenInfo,QSize appScrSize, SKIN_COLOR_NAME colorName,QWidget *parent=0);
    void showMenu();
    void initMenu();
    void onKeyBackPressed(QKeyEvent *event);
    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst);
protected:
   //BlankSpace *blankSpace;
    QWidget *blankSpace;
signals:
    void backPressed();
    void selectLocalGrp(int grpId);
private slots:
    void clearGrid();
    void onClickGrpIcon(int grpId);
    void onMenuClick();
private:
    int columnsNum;
    int rowsNum;
    QSize iconSize;
    double textSize;
    QString title;
    QScrollArea *scroll;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    Menu *menuWidget;
    void init()
    {
        columnsNum = 3;
        rowsNum = 4;
        iconSize = QSize(170,170);
        textSize = 15;
        title=tr("ВАШИ КАРТЫ");
    }
};

#endif // GRPSCREEN_H
