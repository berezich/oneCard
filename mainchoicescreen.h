#ifndef MAINCHOICESCREEN_H
#define MAINCHOICESCREEN_H

#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QKeyEvent>
#include "interface.h"
#include "icon.h"
#include "menu.h"
#include "settings.h"
enum MAIN_ICONS{LOCAL_ICON, SRV_ICON, DEV_ICON, OPTIONS_ICON};
class MainChoiceScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainChoiceScreen(QSize appScrSize, Settings *settings,QWidget *parent=0);
    ~MainChoiceScreen();
    void setGrpLst();

signals:
    void iconPressed(MAIN_ICONS icon);
    void changeSettings(OPTIONS option);
public slots:
    void showMainChoice();
    void onKeyBackPressed(QKeyEvent *event);
private slots:
    void onClickMainIcon(int iconId);
    void onCheckBoxChanged();
    void onChangeSettings(OPTIONS option);
private:
    QSize screenSize;

    QString backGroundColor;

    Settings *settings;

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

    QLabel *defLabel;
    QString defText;
    double defTextSize;
    int defTextLeftOffset;
    QString defTextColor;
    SimpleIcon *checkBox;
    QWidgetList icons;
    void retranslate();
    void changeEvent(QEvent *e);

    void translateNames()
    {
        catalogName = tr("Каталог");
        srvCatalogName = tr("Сервер");
        devCatalogName = tr("Устройство");
        optionsName  = tr("Настройки");
        defText = tr("При запуске переходить в каталог");
    }

    void init(){
        backGroundColor = InterFace::getSkinColor(TEAL).head();

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



        catalogIconSrc = ":/svg/main_screen/catalog.svg";
        srvCatalogIconSrc = ":/svg/main_screen/server.svg";
        devCatalogIconSrc = ":/svg/main_screen/device.svg";
        optionsIconSrc = ":/svg/main_screen/settingsicon.svg";


        defTextSize = 17;
        defTextLeftOffset = 30;
        defTextColor = "#FFFFFF";

        translateNames();
    }
};

#endif // MAINCHOICESCREEN_H
