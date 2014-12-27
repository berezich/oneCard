#ifndef GRPSCREEN_H
#define GRPSCREEN_H
#include "blankscreen.h"
#include <QSize>
#include <QApplication>
#include "grp.h"
#include "icon.h"
//#include "overlay.h"
#include <QResizeEvent>

class GrpScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit GrpScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit GrpScreen(QScreen *screenInfo,QSize appScrSize,QWidget *parent=0);

    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst);
signals:
    void selectLocalGrp(int grpId);
private slots:
    void onClickGrpIcon(int grpId);
private:
    int columnsNum = 3;
    int rowsNum = 4;
    QSize iconSize = QSize(170,170);
    double textSize = 15;
    QString title=tr("ВАШИ КАРТЫ");

    QGridLayout *gridLayout;
    //OverLay *overlay;
    //void resizeEvent(QResizeEvent *event);
};

#endif // GRPSCREEN_H
