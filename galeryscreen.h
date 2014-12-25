#ifndef GALERYSCREEN_H
#define GALERYSCREEN_H
#include "blankscreen.h"
#include <QDir>
#include <QObject>
#include "imgicon.h"
#include <QStandardPaths>

class GalleryScreen : public BlankScreen
{
    Q_OBJECT
public:
    GalleryScreen(QScreen *screenInfo,QSize appScrSize,QString fotoDir,QWidget *parent=0);
    ~GalleryScreen();
    void clearScreen();
    void showCameraPhotos();
    void setPhotoLst(QString path);
signals:
    void selectPic(QString path, QString fileName);
    void pressBack();
private slots:
    void onClickPhotoIcon(int iPhoto);
private:
    int columnsNum = 2;
    int rowsNum = 4;
    QSize iconSize = QSize(350,262);
    QSize imgSaveSize = QSize(480,360);

    //double textSize = 15;
    QString title=tr("ПОСЛЕДНИЕ ФОТО");
    QStringList photoLst;
    QGridLayout *gridLayout;

    QString cameraDir = "/storage/emulated/0/DCIM/camera/";
    //QString cameraDir = "file:///D:/BEREZ/Фоты/";
    QWidgetList childWidgets;
    QList<QLayout *> childLayouts;

};

#endif // GALERYSCREEN_H
