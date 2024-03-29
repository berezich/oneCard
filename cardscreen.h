#ifndef CARDSCREEN_H
#define CARDSCREEN_H
#include <blankscreen.h>
#include <QSize>
#include <QVBoxLayout>
#include "cardinfo.h"
#include "simpleicon.h"
#include "imgicon.h"
#include <QSpacerItem>
#include <QKeyEvent>
#include <QEvent>
#include <QScrollPrepareEvent>
#include "interface.h"
#include "datalocationtype.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include "swipecover.h"

//screen which shows list of cards in the group, which was selected
class CardScreen : public BlankScreen
{
    Q_OBJECT
public:
    explicit CardScreen(QScreen *screenInfo,QSize appScrSize, int colorName, DATA_SOURCE srcType = LOCAL, QWidget *parent=0);
    ~CardScreen();
    void setCardList(QString title, QString grpImgSrc, QList<CardInfo> *cardList, bool isSwipe);
public slots:
    void onCapBack(int i);
private slots:
    void onClickPos(QPoint pos);
signals:
    void backPressed(int i);
    void cardSelected(int cardId);
    void addCardSelected();
private:
    int capLeftIconOffset;

    int capSpacerH;
    QString title;
    int spacingSize;
    QSize cardIconSize;
    int leftCardOffset;
    QString imgNoPhotoSrc;
    QWidget *blankSpace;
    QScrollArea *scroll;

    int leftNameCardOffset;
    double textCardNameSize;
    QString colorTextNameCard;

    QSize nextIconSize;
    int rightNextIconOffset;
    int rightScrollOffset;

    QVBoxLayout *cardListLayout;
    QWidget *cardLstWidget;
    SwipeCover *swipeCover;
    QScrollBar *scrollBar;

    QList<CardInfo> *cardList;

    DATA_SOURCE srcType;
    int colorName;
     void keyPressEvent(QKeyEvent *event);
     void init()
     {
         capLeftIconOffset = 10;
         capSpacerH = 20;
         title = tr("Название группы");
         spacingSize = 20;
         cardIconSize = QSize(160,90);
         leftCardOffset = 20;
         imgNoPhotoSrc = "nophoto.svg";
         leftNameCardOffset = 25;
         textCardNameSize = 15;
         colorTextNameCard = "#000000";
         nextIconSize = QSize(80,80);
         rightNextIconOffset = 20;
         rightScrollOffset = 15;
     }
};

#endif // CARDSCREEN_H
