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
    }


    double scaleFactorW = ((double)appWidowSize.width())/(double)defaultWidth;
    double scaleFactorH = ((double)appWidowSize.height())/(double)defaultHeight;

    scaleFactor = qMin(scaleFactorW,scaleFactorH);


//    appState->setCurSkinColor(RED);
//    appState->setCurSkinColor(PINK);
//    appState->setCurSkinColor(DEEP_PURPLE);
    appState->setCurSkinColor(INDIGO);
//    appState->setCurSkinColor(BLUE);
//    appState->setCurSkinColor(CYAN);
//    appState->setCurSkinColor(TEAL);
//    appState->setCurSkinColor(GREEN);
//    appState->setCurSkinColor(DEEP_ORANGE);
//    appState->setCurSkinColor(BROWN);
//    appState->setCurSkinColor(GRAY);

    //appState->setCurGrpType(LOCAL);
    appState->setCurGrpType(LOCAL);
    appState->setDefEnterApp(false);

    dataM = new Data();

    server = new Server();
    server->setEndPoint(ip);
    server->setLgnPwd(login,pass);

    mainLayout = new QVBoxLayout();

    mainChoiceScreen = new MainChoiceScreen(screenInfo,appWidowSize,appState->curSkinColor(),appState->defEnterApp(),this);
    mainLayout->addWidget(mainChoiceScreen);
    mainChoiceScreen->hide();

    grpScreen = new GrpScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    grpScreen->setGrpLst(dataM->getGroups(appState->getCurGrpType()));
    grpScreen->initMenu();
    grpScreen->hide();
    connect(grpScreen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    if(appState->getCurGrpType()==SERVER)
    {
        connect(server,SIGNAL(getGrpLstFinish(SERVER_ERRORS, QString)),this,SLOT(onGetGrpFinished(SERVER_ERRORS, QString)));
        server->getGrpLstStart();
    }
    mainLayout->addWidget(grpScreen);

    cardScreen = new CardScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    cardScreen->hide();
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen()));
    mainLayout->addWidget(cardScreen);

    cardInfoScreen = new CardInfoScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    imgSaveSize = cardInfoScreen->getCardIconSize();
    cardInfoScreen->hide();
    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));
    mainLayout->addWidget(cardInfoScreen);

    // cache!!!!!!!!! !!!
    dataM->cacheLastImg(cameraDir,appDataLocation+cacheDir,cacheImgNum,imgSaveSize);
    // cache!!!!!!!!! !!!

    if(appState->getCurOS()==WINDOWS)
        cameraQmlScreen = new CameraQmlScreen(appWidowSize,"WINDOWS");
    else
        cameraQmlScreen = new CameraQmlScreen(appWidowSize,"NONE");
    mainLayout->addWidget(cameraQmlScreen);
    connect(cameraQmlScreen,SIGNAL(pressedCancel()),this,SLOT(onPressBackCameraQmlScreen()));
    connect(cameraQmlScreen,SIGNAL(selectPhoto(QString,QString)),this,SLOT(setCardImgSrc(QString,QString)));

    mainLayout->setMargin(0);
    setLayout(mainLayout);



    //showScreen(GRP_SCREEN);
    showScreen(MAIN_CHOICE_SCREEN);


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

void MainScreen::showGrpScreen()
{
    GrpScreen *screen = new GrpScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    //screen->setGrpLst(dataM->getLocalGroups());
    screen->setGrpLst(dataM->getGroups(appState->getCurGrpType()));
    screen->initMenu();
    screen->hide();
    connect(screen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    if(appState->getCurGrpType()==SERVER)
        connect(server,SIGNAL(getGrpLstFinish(SERVER_ERRORS, QString)),this,SLOT(onGetGrpFinished(SERVER_ERRORS, QString)));
    mainLayout->replaceWidget(grpScreen,screen);
    delete(grpScreen);
    grpScreen = screen;

    showScreen(GRP_SCREEN);

    /*
    if(appState->getCurGrpType()==LOCAL)
        showScreen(LOCAL_GRP_SCREEN);
    else if(appState->getCurGrpType()==CLOUD)
        showScreen(CLOUD_LST_SCREEN);
        */

}
/*
void MainScreen::showGrpSrvScreen(int i)
{
    GrpScreen *screen = new GrpScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    //connect(screen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    //connect(server,SIGNAL(getGrpLstFinish(int, QString)),this,SLOT(updateGrpSrvScreen()));
    connect(server,SIGNAL(getGrpLstFinish(SERVER_ERRORS, QString)),this,SLOT(onGetGrpFinished(SERVER_ERRORS, QString)));

    appState->setCurGrpType(SERVER);
    showScreen(CLOUD_LST_SCREEN);
    mainLayout->replaceWidget(grpScreen,screen);
    delete(grpScreen);
    grpScreen = screen;
    server->getGrpLstStart();
}
*/
void MainScreen::updateGrpScreen()
{
    if(appState->getCurGrpType()==SERVER)
    {
        grpScreen->setGrpLst(*(server->getGrpLastLst()));
        grpScreen->initMenu();
    }
    //grpScreen->hide();

}

void MainScreen::showCardScreen(int i)
{
    Grp *grp;
    int grpId = appState->getCurGrpId();
    //CardScreen *screen = new CardScreen(screenInfo,this);
    CardScreen *screen = new CardScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
    if(appState->getCurGrpType()==LOCAL)
    {
        grp = dataM->getLocalGrp(grpId);
        screen ->setCardList(grp->getName(),grp->getImgSrc(),dataM->getLocalCards(grpId));
    }
    mainLayout->replaceWidget(cardScreen,screen);
    delete(cardScreen);
    cardScreen = screen;
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen()));
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
    CardInfoScreen *screen = new CardInfoScreen(screenInfo,appWidowSize,appState->curSkinColor(),this);
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

    if(appState->getCurOS()==WINDOWS)
        showFileDialog();
    else
    {
        galleryScreen = new GalleryScreen(screenInfo,appWidowSize,appState->curSkinColor(),appDataLocation+cacheDir,this);
        galleryScreen->hide();
        galleryScreen->showCameraPhotos();
        mainLayout->addWidget(galleryScreen);

        connect(galleryScreen,SIGNAL(pressBack()),this,SLOT(onPressBackGalleryScreen()));

        connect(galleryScreen,SIGNAL(selectPic(QString,QString)),this,SLOT(setCardImgSrcGallery(QString,QString)));

        showScreen(GALLERY_SCREEN);
    }

}

void MainScreen::setCardImgSrcGallery(QString dir, QString fileName)
{
    if(galleryScreen != NULL)
        delete(galleryScreen);
    setCardImgSrc(dir,fileName);
}

void MainScreen::setCardImgSrc(QString dir, QString fileName)
{
    setCardImgSrc(dir+fileName);
}

void MainScreen::setCardImgSrc(QString file)
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
    qDebug()<<"dir+fileName = "<<file;
    qDebug()<<"saveSrc = "<<saveSrc;
    dataM->saveImg(file,saveSrc,imgSaveSize);

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
    if(appState->getCurOS()==WINDOWS)
        cameraQmlScreen = new CameraQmlScreen(appWidowSize,"WINDOWS");
    else
        cameraQmlScreen = new CameraQmlScreen(appWidowSize,"NONE");
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
    //grpScreen->setGrpLst(dataM->getLocalGroups());
    grpScreen->setGrpLst(dataM->getGroups(LOCAL));
    showGrpScreen();
}

void MainScreen::onNewCardSelected()
{
    int grpId = appState->getCurGrpId();
    Grp *grp = dataM->getLocalGrp(grpId);
    CardInfo *card = grp->createNewCard();
    appState->setCurCardId( card->getId());
    showCardInfoScreen(card->getId());
}

void MainScreen::showFileDialog()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        if(fileNames.length()>0)
            setCardImgSrc(fileNames.first());

    }
}

void MainScreen::onGetGrpFinished(SERVER_ERRORS servError, QString errorMsg)
{
    qDebug()<< "getGrpResp: "+errorMsg;
    switch (servError) {
    case REQ_OK:
        updateGrpScreen();
        break;
    case TIMEOUT:
        //qDebug()<< "gerGrpResp: "+errorMsg;
    default:
        break;
    }
}

void MainScreen::showScreen(SCREEN_TYPE scr)
{
    hideAllScreens();
    appState->setCurScreen(scr);

    switch (scr) {
    case MAIN_CHOICE_SCREEN:
        //mainChoiceScreen->showMainChoice();
        mainChoiceScreen->show();
        break;
    case GRP_SCREEN:
        grpScreen->show();
        break;
    case CARD_LST_SCREEN:
        cardScreen->show();
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
    mainChoiceScreen->hide();
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
        case GRP_SCREEN:
            grpScreen->onKeyBackPressed(event);
            return;
        case CARD_LST_SCREEN:
            showGrpScreen();
            return;
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
            showGrpScreen();
            return;

        default:

            break;
        }
    }
    QWidget::keyPressEvent(event);
}

