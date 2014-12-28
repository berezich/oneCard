#ifndef CARDSCREEN_H
#define CARDSCREEN_H
#include <blankscreen.h>
#include <QSize>
#include <QVBoxLayout>
#include "cardinfo.h"
#include "simpleicon.h"
#include <QSpacerItem>
class CardScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit CardScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit CardScreen(QScreen *screenInfo,QSize appScrSize,QWidget *parent=0);
    ~CardScreen();
    void setCardList(QString title, QString grpImgSrc, QList<CardInfo> *cardList);

public slots:
    void onCapBack(int i);
signals:
    void backPressed(int i);
    void cardSelected(int cardId);
    void addCardSelected();
private:
    int capLeftIconOffset = 10;

    int capSpacerH = 20;
    QString title = tr("Название группы");
    int spacingSize = 20;
    QSize cardIconSize = QSize(160,90);
    int leftCardOffset = 20;
    QString imgNoPhotoSrc = ":/svg/tools/photono.svg";
    QWidget *blankSpace;

    int leftNameCardOffset = 25;
    double textCardNameSize = 15;
    QString colorTextNameCard = "#000000";

    QSize nextIconSize = QSize(80,80);
    int rightNextIconOffset = 20;

    QVBoxLayout *cardListLayout;
    QWidgetList childWidgets;
    QList<QLayout *> childLayouts;
};

#endif // CARDSCREEN_H
