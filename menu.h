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

class Menu : public Overlay
{
    Q_OBJECT
public:
    Menu(QSize size,double scale, QWidget *parent);
    ~Menu();
    bool isMenuOpen(){return menuExists;}
public slots:
    void showMainMenu(bool showInAnyway=false);
protected:
private:
    bool menuExists = false;
    QSize blankSize;
    QVBoxLayout *menuLayout;
    QVBoxLayout *menuBasicLayout;
    QWidget *menuWidget;
    QString backGroundColor = "#b2dfdb";
    double scaleFactor = 1;
    double menuTitleTxtSize = 20;
    double menuItemTxtSize = 17;
    QString lblTxtColor = "#000000";
    QString titleColor = "#ffffff";
    QSize arrowBackSize = QSize(40,40);
    int menuWidth = 500;
    QStringList mainMenuItemTxt; //{"НАСТРОЙКИ","синхронизация устройства","синхронизация с сервером","интерфейс","язык"};
    QStringList languages;
    QStringList skins;
    //123/158=0,78
    QSize iconBluetoothSize = QSize(46,60)*2;
    // 226/272=0,83
    QSize iconDevSyncSize = QSize(50,60)*2;

    QSize iconAuthOkSize = QSize(60,60)*1.5;

    QLineEdit *login;
    QLineEdit *pass;

    //QList<MenuItem*> menuItemBLst;
    void mousePressEvent(QMouseEvent *event);

private slots:
    void showSubMenu(int mainItem);
    void backToMainMenu();
};

#endif // MENU_H
