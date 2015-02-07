#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QWindow>
#include <QPoint>
#include <QFileDialog>
#include <QTranslator>
#include <QApplication>
#include <QIODevice>
#include <QFile>
#include <QCloseEvent>
#include "mainchoicescreen.h"
#include "grpscreen.h"
#include "grp.h"
#include "cardscreen.h"
#include "cardinfoscreen.h"
#include "galeryscreen.h"
#include "cameraqmlscreen.h"
#include "msgscreen.h"
#include "icon.h"
#include "data.h"
#include "appstate.h"
#include "newgrpmodal.h"
#include "server.h"
#include "servererrors.h"
#include "interface.h"
#include "settings.h"
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

    void onMainIconPressed(MAIN_ICONS icon);
    void showGrpScreen();
    void onGrpSelected(int grpId);
    void onGrpBackPressed();
    //void updateGrpScreen();
    void showCardScreen();
    void onCardSelected(int cardId);
    void showCardInfoScreen();
    void showGalleryScreenF();
    void showGalleryScreenB();
    void showGalleryScreen(int i);
    void setCardImgSrcGallery(QString dir, QString fileName);
    void setCardImgSrc(QString file);
    void setCardImgSrc(QString dir, QString fileName);
    void onPressBackGalleryScreen();
    void showCameraQmlScreenF();
    void showCameraQmlScreenB();
    void showCameraQmlScreen(int i);
    void onPressBackCameraQmlScreen();
    void showGrpNewScreen();
    void newGrpConfigured(QString name, QString grpImgSrc);
    void onNewCardSelected();
    void showFileDialog();

    void onAppStateChange(Qt::ApplicationState state);

    //slots for server
    void onGetGrpFinished(SERVER_ERRORS servError, QString errorMsg);
    void onGetCardLstFinished(SERVER_ERRORS servError, QString errorMsg);
    void onCardDataDownloaded(SERVER_ERRORS servError, QString errorMsg);



private:
    QGuiApplication *mainApp;
    QSize appWidowSize;
    int defaultWidth;
    int defaultHeight;
    double scaleFactor;

    QScreen *screenInfo;
    QRect screenAvailableGeometry;
    //double scaleFactor = 1;
    QLayout *mainLayout;

    AppState *appState;
    Settings *settings;

    QString appDataLocation;
    QString cameraDir;
    QString cacheDir;

    QString ip;
    int port;
    QString path;

    QString login;
    QString pass;

    Data *dataM;
    Server *server;

    MainChoiceScreen *mainChoiceScreen;
    GrpScreen *grpScreen;
    CardScreen *cardScreen;
    CardInfoScreen *cardInfoScreen;
    GalleryScreen *galleryScreen;
    CameraQmlScreen *cameraQmlScreen;
    NewGrpModal *newGrpModal;
    MsgScreen *msgScreen;
    bool initNewGrpModal;
    Overlay *overlay;

    QSize imgSaveSize;
    int cacheImgNum;

    QString msgWaitLoading;
    void showScreen(SCREEN_TYPE scr);
    void showMsgScreen(QString msg);
    void hideAllScreens();
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void translateNames()
    {
        msgWaitLoading = tr("Пожалуйста подождите...\nЗагрузка данных с сервера");
    }
    void init()
    {
        defaultWidth = 720;
        defaultHeight = 1280;
        scaleFactor=1;

        appDataLocation="/data/data/com.berezich.oneCard/files";
        cameraDir="/storage/emulated/0/DCIM/camera/";
        cacheDir="/cameraCache/";

        /*
        ip = "http://onecard.bsv-grip.com";
        port = -1;
        path = "";

        login = "oneCard";
        pass = "123456";
        */

        initNewGrpModal = false;
        imgSaveSize = QSize(480,360);
        cacheImgNum = 8;

        msgScreen = NULL;
        newGrpModal = NULL;

        translateNames();
    }
    bool serializeData();
    bool deserializeData();
};

#endif // MAINSCREEN_H
