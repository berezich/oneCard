#ifndef MAINCHOICESCREEN_H
#define MAINCHOICESCREEN_H

#include <QWidget>
#include <QGridLayout>
#include "interface.h"
#include "icon.h"
#include "menu.h"

class MainChoiceScreen : public QWidget
{
    Q_OBJECT
public:
    //explicit MainChoiceScreen(QWidget *parent = 0);
    explicit MainChoiceScreen(QScreen *screenInfo,QSize appScrSize, SKIN_COLOR_NAME colorName,bool checkBoxEnabled,QWidget *parent=0);
    ~MainChoiceScreen();
    void setGrpLst();

signals:

public slots:
    void showMainChoice();
private slots:
    void onClickMainIcon(int iconId);
    void onCheckBoxChanged();
private:
    QSize screenSize;

    QString backGroundColor;
    SKIN_COLOR_NAME skinColor;

    double scaleFactor;
    double scaleFactorH;
    double scaleFactorW;

    int defaultWidth;
    int defaultHeight;

    int topOffset;
    int columnsNum;
    int rowsNum;
    QSize iconSize ;
    double textSize;
    QSize okIconSize;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    Menu *menuWidget;

    QString catalogIconSrc;
    QString srvCatalogIconSrc;
    QString devCatalogIconSrc;
    QString optionsIconSrc;

    QString catalogName;
    QString srvCatalogName;
    QString devCatalogName;
    QString optionsName;

    QString defText;
    double defTextSize;
    int defTextLeftOffset;
    QString defTextColor;
    bool checkBoxEnabled;
    SimpleIcon *checkBox;

    void init(){
        skinColor = TEAL;
        backGroundColor = InterFace::getSkinColor(skinColor).head();

        scaleFactor = 1;
        scaleFactorH = 1;
        scaleFactorW = 1;

        defaultWidth = 720;
        defaultHeight = 1280;

        iconSize = QSize(280,280);
        textSize = 20;
        okIconSize = QSize(80,80);


        columnsNum = 2;
        rowsNum = 3;

        topOffset = 120;

        catalogName = tr("Каталог");
        srvCatalogName = tr("Сервер");
        devCatalogName = tr("Устройство");
        optionsName  = tr("Настройки");

        catalogIconSrc = ":/svg/main_screen/catalog.svg";
        srvCatalogIconSrc = ":/svg/main_screen/server.svg";
        devCatalogIconSrc = ":/svg/main_screen/device.svg";
        optionsIconSrc = ":/svg/main_screen/settingsicon.svg";

        defText = tr("При запуске переходить в каталог");
        defTextSize = 17;
        defTextLeftOffset = 30;
        defTextColor = "#FFFFFF";
    }
};

#endif // MAINCHOICESCREEN_H
