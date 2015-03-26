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
    GalleryScreen(QScreen *screenInfo,QSize appScrSize, int colorName,QString fotoDir,QWidget *parent=0);
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

    QString title;
    QStringList photoLst;
    QGridLayout *gridLayout;

    QString cameraDir;
    //QWidgetList childWidgets;
    //QList<QLayout *> childLayouts;
protected:
    QWidget *blankSpace;
    void init()
    {
        columnsNum = 2;
        rowsNum = 4;
        iconSize = QSize(345,262);
        title=tr("ПОСЛЕДНИЕ ФОТО");
        cameraDir = "/storage/emulated/0/DCIM/camera/";
    }

};

#endif // GALERYSCREEN_H
