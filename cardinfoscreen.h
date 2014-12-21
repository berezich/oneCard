#ifndef CARDINFOSCREEN_H
#define CARDINFOSCREEN_H
#include "blankscreen.h"
#include "cardinfo.h"
#include <QLineEdit>
class CardInfoScreen : public BlankScreen
{
    Q_OBJECT
public:
    explicit CardInfoScreen(QScreen *screenInfo,QWidget *parent=0);
    ~CardInfoScreen();
    void showCardInfo(CardInfo *card);

public slots:
    //void onCapBack(int i);
signals:
    void backPressed(int i);
private:
    int capLeftIconOffset = 10;

    int capSpacerH = 0;

    QString title = tr("ИНФОРМАЦИЯ О КАРТЕ");

    int spacingSize = 0;
    QSize cardIconSize = QSize(480,360);
    //int leftCardOffset = 20;

    //int leftNameCardOffset = 25;
    int textCardNameSize = 25;
    QString colorTextNameCard = "#000000";

    QSize editIconSize = QSize(80,80);
    int rightEditIconOffset = 20;

    QVBoxLayout *cardInfoListLayout;
};

#endif // CARDINFOSCREEN_H
