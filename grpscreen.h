#ifndef GRPSCREEN_H
#define GRPSCREEN_H
#include "blankscreen.h"
#include <QSize>
#include "grp.h"
#include "icon.h"
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
#include <QScroller>
#include <QEvent>
#include "menu.h"
#include "swipecover.h"

class GrpScreen : public BlankScreen
{
    Q_OBJECT
public:
    explicit GrpScreen(QWidget *parent=0);
    GrpScreen(QScreen *screenInfo,QSize appScrSize, int colorName,QWidget *parent=0);
    void onKeyBackPressed(QKeyEvent *event);
    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst, QString grpIconPath, bool isSwipe, bool editable=true);
protected:
    QWidget *blankSpace;
signals:
    void backPressed();
    void selectLocalGrp(int grpId);
private slots:
    void clearGrid();
    void onClickGrpIcon(int grpId);
    void onClickPos(QPoint pos);
private:
    int columnsNum;
    int rowsNum;
    QSize iconSize;
    QSize iconPlusSize;
    QSize gridItemSize;
    double textSize;
    int colorName;
    QString title;
    QScrollArea *scroll;
    QScrollBar *scrollBar;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    SwipeCover *swipeCover;
    QList<Grp> grpLst;

    void init()
    {
        columnsNum = 3;
        rowsNum = 4;
        iconSize = QSize(170,170);
        iconPlusSize = QSize(130,130);
        textSize = 15;
        title=tr("ВАШИ КАРТЫ");
    }
};

#endif // GRPSCREEN_H
