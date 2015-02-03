#ifndef CARDINFOSCREEN_H
#define CARDINFOSCREEN_H
#include "blankscreen.h"
#include "cardinfo.h"
#include <QLineEdit>
#include <QStandardPaths>
#include <QDir>
#include "interface.h"
#include "datalocationtype.h"

class CardInfoScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit CardInfoScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit CardInfoScreen(QScreen *screenInfo, QSize appScrSize, SKIN_COLOR_NAME colorName,QWidget *parent=0);
    ~CardInfoScreen();
    void showCardInfo(CardInfo *card,DATA_SOURCE dataSrc = LOCAL);
    QSize getCardIconSize(){return cardIconSize;}
public slots:
    //void onCapBack(int i);
private slots:
    void onEditName();
    void onEditCard();
    void editFlagMagnetLine();
signals:
    void backPressed(int i);
    void editCard(QString name, QString src);
    void editFrontSideCameraImg();
    void editFrontSideGalleryImg();
    void editBackSideCameraImg();
    void editBackSideGalleryImg();
    void editFrontSideImg();
    void editBackSideImg();
private:
    int capLeftIconOffset;
    int capSpacerH;
    QString title;
    int spacingSize;
    QSize cardIconSize;
    QString imgSrc;
    QString imgNoPhotoSrc;
    CardInfo *cardInfo;
    double textCardNameSize;
    QString colorTextNameCard;
    QLineEdit *nameEditLine;
    QSize editIconSize;
    int rightEditIconOffset;
    QSize infoIconSize;

    QVBoxLayout *cardInfoListLayout;

    QWidgetList childWidgets;
    QList<QLayout*> childLayouts;

    SimpleIcon *iconMagnet;
    QHBoxLayout *lineMagnetLayout;

    void init()
    {
        capLeftIconOffset = 10;
        capSpacerH = 20;
        title = tr("ИНФОРМАЦИЯ О КАРТЕ");
        spacingSize = 20;
        cardIconSize = QSize(480,360);
        imgNoPhotoSrc = ":/svg/tools/photono.svg";
        textCardNameSize = 25;
        colorTextNameCard = "#000000";
        editIconSize = QSize(80,80);
        rightEditIconOffset = 15;

        infoIconSize = QSize(110,110);
    }

protected:
    QWidget *blankSpace;
};

#endif // CARDINFOSCREEN_H
