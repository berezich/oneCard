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
private slots:
    void onEditName();
    void onEditCard(int i);
signals:
    void backPressed(int i);
    void editCard(QString name, QString src);
private:
    int capLeftIconOffset = 10;

    int capSpacerH = 20;

    QString title = tr("ИНФОРМАЦИЯ О КАРТЕ");

    int spacingSize = 20;
    QSize cardIconSize = QSize(480,360);
    QString imgSrc;
    //int leftCardOffset = 20;
    CardInfo *cardInfo;
    //int leftNameCardOffset = 25;
    double textCardNameSize = 25;
    QString colorTextNameCard = "#000000";
    QLineEdit *nameEditLine;

    QSize editIconSize = QSize(80,80);
    int rightEditIconOffset = 15;

    QVBoxLayout *cardInfoListLayout;
};

#endif // CARDINFOSCREEN_H
