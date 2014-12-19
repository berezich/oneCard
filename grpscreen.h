#ifndef GRPSCREEN_H
#define GRPSCREEN_H
#include "blankscreen.h"
#include <QSize>
#include "grp.h"
#include "icon.h"
class GrpScreen : public BlankScreen
{
public:
    //explicit GrpScreen(QWidget *parent);
    //explicit GrpScreen(QScreen *screenInfo);
    explicit GrpScreen(QScreen *screenInfo,QWidget *parent=0);
    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst);
    void setTitle(QString txt);
private:
    int columnsNum = 3;
    int rowsNum = 4;
    int iconHeight = 190;
    int iconWidth = 190;
    QSize iconSize = QSize(190,190);
    int textSize = 15;
    QString title;

    QGridLayout *gridLayout;
};

#endif // GRPSCREEN_H
