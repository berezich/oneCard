#ifndef CARDINFOSCREEN_H
#define CARDINFOSCREEN_H
#include "blankscreen.h"
#include "cardinfo.h"
#include <QLineEdit>
#include <QStandardPaths>
#include <QDir>

class CardInfoScreen : public BlankScreen
{
    Q_OBJECT
public:
    //explicit CardInfoScreen(QScreen *screenInfo,QWidget *parent=0);
    explicit CardInfoScreen(QScreen *screenInfo, QSize appScrSize,QWidget *parent=0);
    ~CardInfoScreen();
    void showCardInfo(CardInfo *card);
    QSize getCardIconSize(){return cardIconSize;}
public slots:
    //void onCapBack(int i);
private slots:
    void onEditName();
    void onEditCard(int i);
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
    int capLeftIconOffset = 10;

    int capSpacerH = 20;

    QString title = tr("ИНФОРМАЦИЯ О КАРТЕ");

    int spacingSize = 20;
    QSize cardIconSize = QSize(480,360);
    QString imgSrc;
    QString imgNoPhotoSrc = ":/svg/tools/photono.svg";
    //int leftCardOffset = 20;
    CardInfo *cardInfo;
    //int leftNameCardOffset = 25;
    double textCardNameSize = 25;
    QString colorTextNameCard = "#000000";
    QLineEdit *nameEditLine;

    QSize editIconSize = QSize(80,80);
    int rightEditIconOffset = 15;

    QSize infoIconSize = QSize(110,110);

    QVBoxLayout *cardInfoListLayout;

    QWidgetList childWidgets;
    QList<QLayout*> childLayouts;

    SimpleIcon *iconMagnet;
    QHBoxLayout *lineMagnetLayout;
protected:
    QWidget *blankSpace;
};

#endif // CARDINFOSCREEN_H
