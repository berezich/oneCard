#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include "grpscreen.h"
#include "grp.h"
#include "cardscreen.h"
#include "cardinfoscreen.h"
#include "galeryscreen.h"
#include "icon.h"
#include "data.h"
#include "appstate.h"
#include "newgrpmodal.h"
class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);

    explicit MainScreen(QApplication *mainApp, QWidget *parent = 0);
    //explicit MainScreen(QScreen *screenInfo, QWidget *parent = 0);
    ~MainScreen();


signals:

public slots:
    void onGrpSelected(int grpId);
    void showGrpScreen(int i);
    void showCardScreen(int i);
    void showCardInfoScreen(int i);
    void showGalleryScreenF();
    void showGalleryScreenB();
    void showGalleryScreen(int i);
    void setCardImgSrc(QString dir, QString fileName);
    void onPressBackGalleryScreen();
    void showGrpNewScreen();

private:
    void resizeEvent(QResizeEvent *event);
    QSize appWidowSize;
    int defaultWidth = 720;
    int defaultHeight = 1280;
    double scaleFactor=1;

    QScreen *screenInfo;
    //double scaleFactor = 1;
    QLayout *mainLayout;

    AppState *appState;
    //GRP_SOURCE grpState = LOCAL;

    QString appDataLocation="/data/data/com.berezich.oneCard/files";
    QString cameraDir="/storage/emulated/0/DCIM/camera/";
    QString cacheDir="cameraCache/";

    Data *dataM;

    GrpScreen *grpScreen;
    CardScreen *cardScreen;
    CardInfoScreen *cardInfoScreen;
    GalleryScreen *galleryScreen;
    NewGrpModal *newGrpModal;
    bool initNewGrpModal = false;
    Overlay *overlay;

    QSize imgSaveSize = QSize(480,360);
    int cacheImgNum = 8;

    void showScreen(SCREEN_TYPE scr);
    void hideAllScreens();

};

#endif // MAINSCREEN_H
