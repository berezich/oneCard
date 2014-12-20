#ifndef GRPSCREEN_H
#define GRPSCREEN_H
#include "blankscreen.h"
#include <QSize>
#include "grp.h"
#include "icon.h"
class GrpScreen : public BlankScreen
{
    Q_OBJECT
public:
    explicit GrpScreen(QScreen *screenInfo,QWidget *parent=0);
    ~GrpScreen();
    void setGrpLst(QList<Grp> grpLst);
    void setTitle(QString txt);
signals:
    void selectLocalGrp(int grpId);
private slots:
    void onClickGrpIcon(int grpId);
private:
    int columnsNum = 3;
    int rowsNum = 4;
    QSize iconSize = QSize(190,190);
    int textSize = 15;
    QString title=tr("ВАШИ КАРТЫ");

    QGridLayout *gridLayout;
};

#endif // GRPSCREEN_H
