#include "mainscreen.h"
#include "grpscreen.h"

MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{

}

MainScreen::MainScreen(QApplication *mainApp, QWidget *parent)
{
    QDesktopWidget *desktop = mainApp->desktop();
    screenAvailableGeometry = desktop->availableGeometry();
    int dpiY = desktop->physicalDpiY();
    int dpiX = desktop->physicalDpiX();
    double displayWidthInch = screenAvailableGeometry.width() / dpiX;
    double displayHeightInch = screenAvailableGeometry.height() / dpiY;
    double displayDiagonalInch = sqrt(displayWidthInch*displayWidthInch + displayHeightInch*displayHeightInch); // screen diagonal size in inches
    this->screenInfo = mainApp->primaryScreen();



    QStringList dirs = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    for(int i=0; i<dirs.length(); i++)
        qDebug()<< "dir"<<i<<" = "<<dirs.at(i);
    if(dirs.length()>0)
    {
        appDataLocation = dirs.at(0);
        qDebug() << "appDataLocation = " <<appDataLocation;
    }


    //this->screenInfo = screenInfo;

    appWidowSize.setWidth(screenAvailableGeometry.width());
    appWidowSize.setHeight(screenAvailableGeometry.height());
    appState = new AppState();
    if(appWidowSize != QSize(0,0))
    {
        double k = 0.85;
        if(appWidowSize.height()*k<defaultHeight)
            appWidowSize = QSize(defaultWidth*appWidowSize.height()*k/defaultHeight,appWidowSize.height()*k);
        else
            appWidowSize = QSize(defaultWidth,defaultHeight);

        appState->setCurOS(WINDOWS);
    }
    else
    {
        appWidowSize = QSize(screenInfo->geometry().width(),screenInfo->geometry().height());
        appState->setCurOS(NONE);
        //setWindowState(Qt::WindowMaximized);
    }

    //setMaximumSize(appWidowSize);


    double scaleFactorW = ((double)appWidowSize.width())/(double)defaultWidth;
    double scaleFactorH = ((double)appWidowSize.height())/(double)defaultHeight;

    scaleFactor = qMin(scaleFactorW,scaleFactorH);

    dataM = new Data();
    //qDebug()<<"scale = "<< scaleFactor;

    //setMinimumSize(screenSize);



    mainLayout = new QVBoxLayout();

    dataM->getLocalGroups();

    //grpScreen = new GrpScreen(screenInfo,this);
    grpScreen = new GrpScreen(screenInfo,appWidowSize,this);
    grpScreen->setGrpLst(dataM->getLocalGroups());
    grpScreen->initMenu();
    grpScreen->hide();
    connect(grpScreen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    mainLayout->addWidget(grpScreen);



    //newGrpModal->hide();

    //cardScreen = new CardScreen(screenInfo,this);
    cardScreen = new CardScreen(screenInfo,appWidowSize,this);
    cardScreen->hide();
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    mainLayout->addWidget(cardScreen);

    //cardInfoScreen = new CardInfoScreen(screenInfo,this);
    cardInfoScreen = new CardInfoScreen(screenInfo,appWidowSize,this);
    imgSaveSize = cardInfoScreen->getCardIconSize();
    cardInfoScreen->hide();
    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));
    mainLayout->addWidget(cardInfoScreen);

    // cache!!!!!!!!! !!!
    dataM->cacheLastImg(cameraDir,appDataLocation+cacheDir,cacheImgNum,imgSaveSize);
    // cache!!!!!!!!! !!!

    cameraQmlScreen = new CameraQmlScreen(appWidowSize);
    mainLayout->addWidget(cameraQmlScreen);
    connect(cameraQmlScreen,SIGNAL(pressedCancel()),this,SLOT(onPressBackCameraQmlScreen()));
    connect(cameraQmlScreen,SIGNAL(selectPhoto(QString,QString)),this,SLOT(setCardImgSrc(QString,QString)));

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    appState->setCurGrpType(LOCAL);
    showScreen(LOCAL_GRP_SCREEN);

}

MainScreen::~MainScreen()
{

}

void MainScreen::onGrpSelected(int grpId)
{
    if(grpId==-1)
    {
        //добавление новой группы
        showGrpNewScreen();
        return;
    }
    appState->setCurGrpId(grpId);
    showCardScreen(0);

}

void MainScreen::showGrpScreen(int i)
{
    GrpScreen *screen = new GrpScreen(screenInfo,appWidowSize,this);
    screen->setGrpLst(dataM->getLocalGroups());
    screen->initMenu();
    screen->hide();
    connect(screen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    mainLayout->replaceWidget(grpScreen,screen);
    delete(grpScreen);
    grpScreen = screen;

    if(appState->getCurGrpType()==LOCAL)
        showScreen(LOCAL_GRP_SCREEN);
    else if(appState->getCurGrpType()==CLOUD)
        showScreen(CLOUD_LST_SCREEN);

}

void MainScreen::showCardScreen(int i)
{
    Grp *grp;
    int grpId = appState->getCurGrpId();
    //CardScreen *screen = new CardScreen(screenInfo,this);
    CardScreen *screen = new CardScreen(screenInfo,appWidowSize,this);
    if(appState->getCurGrpType()==LOCAL)
    {
        grp = dataM->getLocalGrp(grpId);
        screen ->setCardList(grp->getName(),grp->getImgSrc(),dataM->getLocalCards(grpId));
    }
    mainLayout->replaceWidget(cardScreen,screen);
    delete(cardScreen);
    cardScreen = screen;
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    connect(cardScreen,SIGNAL(cardSelected(int)),this,SLOT(showCardInfoScreen(int)));
    connect(cardScreen,SIGNAL(addCardSelected()),this,SLOT(onNewCardSelected()));

    //cardScreen->hide();
    showScreen(CARD_LST_SCREEN);

}
void MainScreen::showCardInfoScreen(int cardId)
{
    int grpId = appState->getCurGrpId();
    appState->setCurCardId(cardId);
    //CardInfoScreen *screen = new CardInfoScreen(screenInfo,this);
    CardInfoScreen *screen = new CardInfoScreen(screenInfo,appWidowSize,this);
    if(appState->getCurGrpType()==LOCAL)
    {
        screen->showCardInfo(dataM->getLocalCard(grpId,cardId));
    }
    mainLayout->replaceWidget(cardInfoScreen,screen);
    delete(cardInfoScreen);
    cardInfoScreen = screen;

    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));
    connect(cardInfoScreen,SIGNAL(editFrontSideGalleryImg()),this,SLOT(showGalleryScreenF()));
    connect(cardInfoScreen,SIGNAL(editFrontSideCameraImg()),this,SLOT(showCameraQmlScreenF()));
    connect(cardInfoScreen,SIGNAL(editBackSideGalleryImg()),this,SLOT(showGalleryScreenB()));
    connect(cardInfoScreen,SIGNAL(editBackSideCameraImg()),this,SLOT(showCameraQmlScreenB()));

//    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));
//    connect(cardInfoScreen,SIGNAL(editFrontSideImg()),this,SLOT(showGalleryScreenF()));

//    //--------TEST----------
//    //connect(cardInfoScreen,SIGNAL(editBackSideImg()),this,SLOT(showGalleryScreenB()));
//    connect(cardInfoScreen,SIGNAL(editBackSideImg()),this,SLOT(showCameraQmlScreenB()));

    showScreen(CARD_INFO_SCREEN);

}

void MainScreen::showGalleryScreenF()
{
    appState->setCurCardSideState(FRONTSIDE);
    showGalleryScreen(0);
}
void MainScreen::showGalleryScreenB()
{
    appState->setCurCardSideState(BACKSIDE);
    showGalleryScreen(0);
}
void MainScreen::showGalleryScreen(int i)
{

    galleryScreen = new GalleryScreen(screenInfo,appWidowSize,appDataLocation+cacheDir,this);
    galleryScreen->hide();
    galleryScreen->showCameraPhotos();
    mainLayout->addWidget(galleryScreen);

    connect(galleryScreen,SIGNAL(pressBack()),this,SLOT(onPressBackGalleryScreen()));

    connect(galleryScreen,SIGNAL(selectPic(QString,QString)),this,SLOT(setCardImgSrcGallery(QString,QString)));

    showScreen(GALLERY_SCREEN);

}

void MainScreen::setCardImgSrcGallery(QString dir, QString fileName)
{
    if(galleryScreen != NULL)
        delete(galleryScreen);
    setCardImgSrc(dir,fileName);
}

void MainScreen::setCardImgSrc(QString dir, QString fileName)
{
    //if(galleryScreen!=NULL)
    //    delete(galleryScreen);

    int cardId = appState->getCurCardId();
    int grpId = appState->getCurGrpId();
    CardInfo *cardInf = dataM->getLocalCard(grpId, cardId);
    //QString imgName = cardInf->getCardName()+"_"+fileName;
    QString imgName;
    if(appState->getCurCardSideState()==FRONTSIDE)
        imgName= cardInf->getCardName()+"_front";
    else
        imgName= cardInf->getCardName()+"_back";
    QString saveSrc = appDataLocation+"/"+imgName;
    qDebug()<<"dir+fileName = "<<dir+fileName;
    qDebug()<<"saveSrc = "<<saveSrc;
    dataM->saveImg(dir+fileName,saveSrc,imgSaveSize);

    if(appState->getCurCardSideState()==FRONTSIDE)
        dataM->getLocalCard(grpId,cardId)->setCardImgSrc(saveSrc);
    else
        dataM->getLocalCard(grpId,cardId)->setCardImgBackSrc(saveSrc);

    showCardInfoScreen(cardId);
}

void MainScreen::onPressBackGalleryScreen()
{
    delete(galleryScreen);
    showCardInfoScreen(appState->getCurCardId());
}

void MainScreen::showCameraQmlScreenF()
{
    appState->setCurCardSideState(FRONTSIDE);
    showCameraQmlScreen(0);
}
void MainScreen::showCameraQmlScreenB()
{
    appState->setCurCardSideState(BACKSIDE);
    showCameraQmlScreen(0);
}
void MainScreen::showCameraQmlScreen(int i)
{
    delete(cameraQmlScreen);
    cameraQmlScreen = new CameraQmlScreen(appWidowSize);
    mainLayout->addWidget(cameraQmlScreen);
    connect(cameraQmlScreen,SIGNAL(pressedCancel()),this,SLOT(onPressBackCameraQmlScreen()));
    connect(cameraQmlScreen,SIGNAL(selectPhoto(QString,QString)),this,SLOT(setCardImgSrc(QString,QString)));

    //window()->setUpdatesEnabled(true);
    window()->update();
    showScreen(CAMERAQML_SCREEN);

}
void MainScreen::onPressBackCameraQmlScreen()
{
    //delete(cameraQmlScreen);
    showCardInfoScreen(appState->getCurCardId());
}

void MainScreen::showGrpNewScreen()
{
    appState->setCurScreen(NEW_GRP_SCREEN);
    //newGrpModal->setIconLst();
    newGrpModal = new NewGrpModal(appWidowSize,scaleFactor,dataM->getGrpImgSrc(),this);
    newGrpModal->show();
    newGrpModal->setIconLst();
    connect(newGrpModal,SIGNAL(newGrpConfigured(QString,QString)),this,SLOT(newGrpConfigured(QString,QString)));
}

void MainScreen::newGrpConfigured(QString name, QString grpImgSrc)
{
    dataM->addNewGrp(name,grpImgSrc);
    grpScreen->setGrpLst(dataM->getLocalGroups());
    showGrpScreen(0);
}

void MainScreen::onNewCardSelected()
{
    int grpId = appState->getCurGrpId();
    Grp *grp = dataM->getLocalGrp(grpId);
    CardInfo *card = grp->createNewCard();
    appState->setCurCardId( card->getId());
    showCardInfoScreen(card->getId());
}

void MainScreen::showScreen(SCREEN_TYPE scr)
{
    hideAllScreens();
    appState->setCurScreen(scr);

    switch (scr) {
    case LOCAL_GRP_SCREEN:
        grpScreen->show();
        break;
    case CARD_LST_SCREEN:
        cardScreen->show();
        break;
    case CLOUD_LST_SCREEN:
        break;
    case CARD_INFO_SCREEN:
        cardInfoScreen->show();
        break;
    case GALLERY_SCREEN:
        galleryScreen->show();
        break;
    case CAMERAQML_SCREEN:

        cameraQmlScreen->showQML();
        break;
    default:

        break;
    }
}

void MainScreen::hideAllScreens()
{
    grpScreen->hide();
    cardScreen->hide();
    cardInfoScreen->hide();
    cameraQmlScreen->hide();
    //galleryScreen->hide();
}

void MainScreen::resizeEvent(QResizeEvent *event)
{

    if(appState->getCurOS() == WINDOWS)
    {
        window()->move(screenAvailableGeometry.width()/4,(screenAvailableGeometry.height()-appWidowSize.height())/5);
    }
    if(!appState->getIsFixedWinSize() || appState->getCurOS() != WINDOWS)
    {
        setMinimumSize(this->window()->geometry().width(),this->window()->geometry().height());
        setMaximumSize(this->window()->geometry().width(),this->window()->geometry().height());
    }
}

void MainScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Back)
    {
        switch (appState->getCurScreen()) {
        case LOCAL_GRP_SCREEN:
            grpScreen->onKeyBackPressed(event);
            return;
        case CARD_LST_SCREEN:
            showGrpScreen(0);
            return;
        case CLOUD_LST_SCREEN:
            break;
        case CARD_INFO_SCREEN:
            showCardScreen(0);
            return;
        case GALLERY_SCREEN:
            showCardInfoScreen(appState->getCurCardId());
            return;
        case CAMERAQML_SCREEN:
            showCardInfoScreen(appState->getCurCardId());
            return;
        case NEW_GRP_SCREEN:
            showGrpScreen(0);
            return;

        default:

            break;
        }
    }
    QWidget::keyPressEvent(event);
}

