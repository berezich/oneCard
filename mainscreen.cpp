#include "mainscreen.h"
#include "grpscreen.h"

MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{

}

MainScreen::MainScreen(QApplication *mainApp, QWidget *parent)
{
    QDesktopWidget *desktop = mainApp->desktop();
    QRect screenAvailableGeometry = desktop->availableGeometry();
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
        appDataLocation = dirs.at(0);


    //this->screenInfo = screenInfo;

    appWidowSize.setWidth(screenAvailableGeometry.width());
    appWidowSize.setHeight(screenAvailableGeometry.height());
    if(appWidowSize != QSize(0,0))
        appWidowSize = QSize(defaultWidth,defaultHeight)*0.45;
    else
        appWidowSize = QSize(screenInfo->geometry().width(),screenInfo->geometry().height());
    //scaleFactor = screenSize.width()/defaultWidth;

    double scaleFactorW = ((double)appWidowSize.width())/(double)defaultWidth;
    double scaleFactorH = ((double)appWidowSize.height())/(double)defaultHeight;

    scaleFactor = qMin(scaleFactorW,scaleFactorH);

    dataM = new Data();
    //qDebug()<<"scale = "<< scaleFactor;

    //setMinimumSize(screenSize);

    appState = new AppState();

    mainLayout = new QVBoxLayout();

    dataM->getLocalGroups();

    //grpScreen = new GrpScreen(screenInfo,this);
    grpScreen = new GrpScreen(screenInfo,appWidowSize,this);
    grpScreen->setGrpLst(dataM->getLocalGroups());
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

    /*
    galleryScreen = new GalleryScreen(screenInfo,appWidowSize,this);
    //galleryScreen->showCameraPhotos();
    galleryScreen->hide();
    connect(galleryScreen,SIGNAL(pressBack()),this,SLOT(onPressBackGalleryScreen()));
    connect(galleryScreen,SIGNAL(selectPic(QString)),this,SLOT(setCardImgSrc(QString)));
    mainLayout->addWidget(galleryScreen);
    */

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    //newGrpModal = new NewGrpModal(scaleFactor,dataM->getGrpImgSrc(),this);



    appState->setCurGrpType(LOCAL);
    showScreen(LOCAL_GRP_SCREEN);
    //showScreen(GALLERY_SCREEN);

    //overlay = new Overlay(this);

}

void MainScreen::resizeEvent(QResizeEvent *event)
{
    //if(!initNewGrpModal)
      //  newGrpModal->resize(event->size());
    event->accept();
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
    connect(cardInfoScreen,SIGNAL(editFrontSideImg()),this,SLOT(showGalleryScreenF()));
    connect(cardInfoScreen,SIGNAL(editBackSideImg()),this,SLOT(showGalleryScreenB()));

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
    /*
    GalleryScreen *screen = new GalleryScreen(screenInfo,appWidowSize,this);
    screen->showCameraPhotos();
    mainLayout->replaceWidget(galleryScreen,screen);
    delete(galleryScreen);
    galleryScreen = screen;
    */

    galleryScreen = new GalleryScreen(screenInfo,appWidowSize,appDataLocation+cacheDir,this);
    galleryScreen->hide();
    galleryScreen->showCameraPhotos();
    mainLayout->addWidget(galleryScreen);

    connect(galleryScreen,SIGNAL(pressBack()),this,SLOT(onPressBackGalleryScreen()));
    connect(galleryScreen,SIGNAL(selectPic(QString,QString)),this,SLOT(setCardImgSrc(QString,QString)));

    showScreen(GALLERY_SCREEN);

}

void MainScreen::setCardImgSrc(QString dir, QString fileName)
{
    if(galleryScreen!=NULL)
        delete(galleryScreen);

    int cardId = appState->getCurCardId();
    int grpId = appState->getCurGrpId();
    CardInfo *cardInf = dataM->getLocalCard(grpId, cardId);
    QString imgName = cardInf->getCardName()+"_"+fileName;
    QString saveSrc = appDataLocation+"/"+imgName;

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

void MainScreen::showGrpNewScreen()
{

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

void MainScreen::showScreen(SCREEN_TYPE scr)
{
    hideAllScreens();

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
    default:

        break;
    }
}

void MainScreen::hideAllScreens()
{
    grpScreen->hide();
    cardScreen->hide();
    cardInfoScreen->hide();
    //galleryScreen->hide();
}

