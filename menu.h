#ifndef MENU_H
#define MENU_H
#include "overlay.h"
#include <QVBoxLayout>
#include <QtCore/qmath.h>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QWidgetList>
#include <QApplication>
#include <QTranslator>
#include "menuitem.h"
#include "simpleicon.h"
#include "titlemenu.h"
#include "interface.h"
#include "settings.h"


class Menu : public Overlay
{
    Q_OBJECT
public:
    Menu(QSize size,double scale, Settings *settings, QWidget *parent);
    ~Menu();
    bool isMenuOpen(){return menuExists;}
public slots:
    void showMainMenu(bool showInAnyway=false);
signals:
    void changeSettings(OPTIONS option);
private slots:
    void showSubMenu(int mainItem);
    void backToMainMenu();
    void onChangeColor(int color);
    void onChangeServer();
    void onChangeLanguage(int lang);
    void onChangeGrpView(int grpView);
    void onChangeDefEnter(int isEnter);

protected:
private:
    bool menuExists;
    QSize blankSize;
    QVBoxLayout *menuLayout;
    QVBoxLayout *menuBasicLayout;
    QWidget *menuWidget;
    QString backGroundColor;

    double scaleFactor;
    double menuTitleTxtSize;
    double menuItemTxtSize;
    QString lblTxtColor;
    QString titleColor;
    QSize arrowBackSize;
    int menuWidth;
    QStringList mainMenuItemTxt;
    QStringList languages;
    QStringList skins;
    QStringList grpViews;
    QString grpViewLblText;
    QSize iconBluetoothSize;
    QSize iconDevSyncSize;
    QSize iconAuthOkSize;

    QWidgetList colorOptions;
    QWidgetList grpViewOptions;
    QWidgetList languageOptions;
    QWidgetList defEnterOptions;

    Settings *settings;

    QLineEdit *login;
    QLineEdit *pass;
    QLineEdit *endPoint;

    int curSubMenu;

    QTranslator *myappTranslator;

    void mousePressEvent(QMouseEvent *event);
    void translateNames()
    {
        mainMenuItemTxt.clear();
        mainMenuItemTxt.append(tr("синхронизация устройства"));
        mainMenuItemTxt.append(tr("синхронизация с сервером"));
        mainMenuItemTxt.append(tr("интерфейс"));
        mainMenuItemTxt.append(tr("язык"));
        mainMenuItemTxt.append(tr("переход в каталог"));

        languages.clear();
        for(int lng=RUSSIAN; lng<=ENGLISH; lng++)
            languages.append(Languages::getLangName(lng));

        skins.clear();
        for(int skin=RED; skin<=GRAY;skin++)
            skins.append(InterFace::getSkinColor(skin).normalName());

        grpViews.clear();
        for(int view=STANDART; view<=NON_STANDART; view++)
            grpViews.append(InterFace::getGrpViewName(view));
        grpViewLblText = tr("вид иконок");


    }

    void init()
    {
        myappTranslator = NULL;


        menuExists = false;
        backGroundColor = "#b2dfdb";

        scaleFactor = 1;
        menuTitleTxtSize = 20;
        menuItemTxtSize = 17;
        lblTxtColor = "#000000";
        titleColor = "#ffffff";
        arrowBackSize = QSize(40,40);
        menuWidth = 500;

        iconBluetoothSize = QSize(46,60)*2;
        iconDevSyncSize = QSize(50,60)*2;

        iconAuthOkSize = QSize(60,60)*1.5;
        translateNames();
    }

};

#endif // MENU_H
