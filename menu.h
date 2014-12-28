#ifndef MENU_H
#define MENU_H
#include "overlay.h"
#include <QVBoxLayout>
#include <QtCore/qmath.h>
#include <QLabel>
#include <QMouseEvent>

class Menu : public Overlay
{
public:
    Menu(QSize size,double scale, QWidget *parent);
    ~Menu();
protected:
private:
    //QVBoxLayout *formBasic;
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
    //QPoint rectPoint;
    //QSize rectSize = QSize(630,907);
    int menuWidth = 500;
    QStringList menuItemTxt; //{"НАСТРОЙКИ","синхронизация устройства","синхронизация с сервером","интерфейс","язык"};
    QList<QLabel*> menuItemLst;
    void mousePressEvent(QMouseEvent *event);
};

#endif // MENU_H
