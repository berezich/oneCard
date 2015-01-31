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
    GalleryScreen(QScreen *screenInfo,QSize appScrSize, SKIN_COLOR_NAME colorName,QString fotoDir,QWidget *parent=0);
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
    int columnsNum;
    int rowsNum;
    QSize iconSize;
    QSize imgSaveSize;

    QString title;
    QStringList photoLst;
    QGridLayout *gridLayout;

    QString cameraDir;
    QWidgetList childWidgets;
    QList<QLayout *> childLayouts;
protected:
    QWidget *blankSpace;
    void init()
    {
        columnsNum = 2;
        rowsNum = 4;
        iconSize = QSize(345,262);
        imgSaveSize = QSize(480,360);
        title=tr("ПОСЛЕДНИЕ ФОТО");
        cameraDir = "/storage/emulated/0/DCIM/camera/";
        //QString cameraDir = "file:///D:/BEREZ/Фоты/";
    }

};

#endif // GALERYSCREEN_H
