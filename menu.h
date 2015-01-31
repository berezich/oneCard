#ifndef MENU_H
#define MENU_H
#include "overlay.h"
#include <QVBoxLayout>
#include <QtCore/qmath.h>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include "menuitem.h"
#include "simpleicon.h"
#include "titlemenu.h"
#include "interface.h"

class Menu : public Overlay
{
    Q_OBJECT
public:
    Menu(QSize size,double scale, SKIN_COLOR_NAME colorName, QWidget *parent);
    ~Menu();
    bool isMenuOpen(){return menuExists;}
public slots:
    void showMainMenu(bool showInAnyway=false);
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
    QStringList mainMenuItemTxt; //{"НАСТРОЙКИ","синхронизация устройства","синхронизация с сервером","интерфейс","язык"};
    QStringList languages;
    QStringList skins;
    QSize iconBluetoothSize;
    QSize iconDevSyncSize;
    QSize iconAuthOkSize;

    QLineEdit *login;
    QLineEdit *pass;

    //QList<MenuItem*> menuItemBLst;
    void mousePressEvent(QMouseEvent *event);
    void init()
    {
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
        // 226/272=0,83
        iconDevSyncSize = QSize(50,60)*2;

        iconAuthOkSize = QSize(60,60)*1.5;
    }

private slots:
    void showSubMenu(int mainItem);
    void backToMainMenu();
};

#endif // MENU_H
