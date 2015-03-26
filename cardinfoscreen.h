#ifndef CARDINFOSCREEN_H
#define CARDINFOSCREEN_H
#include "blankscreen.h"
#include "cardinfo.h"
#include <QLineEdit>
#include <QStandardPaths>
#include <QDir>
#include <QApplication>
#include <QInputMethod>
#include <QMouseEvent>
#include <QKeyEvent>
#include "interface.h"
#include "datalocationtype.h"
#include "appstate.h"
#include "imgicon.h"

class CardInfoScreen : public BlankScreen
{
    Q_OBJECT
public:
    explicit CardInfoScreen(QScreen *screenInfo, QSize appScrSize, int colorName,QWidget *parent=0);
    ~CardInfoScreen();
    void showCardInfo(CardInfo *card,DATA_SOURCE dataSrc = LOCAL);
    QSize getCardIconSize(){return cardIconSize;}
    void updateImg(CARD_SIDE cardSide);
public slots:
private slots:
    void onEditName();
    void onEditCard();
    void editFlagMagnetLine();
    void clearFocusAll();
signals:
    void backPressed(bool cancelChanges=false);
    void editCard(QString name, QString src);
    void editFrontSideCameraImg();
    void editFrontSideGalleryImg();
    void editBackSideCameraImg();
    void editBackSideGalleryImg();
    void editFrontSideImg();
    void editFrontSideCropImg();
    void editBackSideCropImg();
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
    QString iconsFolder;

    QVBoxLayout *cardInfoListLayout;
    ImgIcon *cardFIcon;
    QHBoxLayout *lineFSide;
    ImgIcon *cardBIcon;
    QHBoxLayout *lineBSide;

    SimpleIcon *iconMagnet;
    QHBoxLayout *lineMagnetLayout;
    QLineEdit *magnetLineEdit;
    double textMagnetLineSize;
    void 	mousePressEvent ( QMouseEvent * event );
    void keyPressEvent(QKeyEvent *event);
    void init()
    {
        capLeftIconOffset = 10;
        capSpacerH = 20;
        title = tr("ИНФОРМАЦИЯ О КАРТЕ");
        spacingSize = 20;
        cardIconSize = QSize(480,360);
        imgNoPhotoSrc = "nophoto.svg";
        textCardNameSize = 25;
        colorTextNameCard = "#000000";
        editIconSize = QSize(80,80);
        rightEditIconOffset = 15;

        infoIconSize = QSize(110,65);
        textMagnetLineSize = 15;
        magnetLineEdit = NULL;
    }

protected:
    QWidget *blankSpace;
};

#endif // CARDINFOSCREEN_H
