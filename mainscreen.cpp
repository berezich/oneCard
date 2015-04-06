#include "mainscreen.h"


MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{

}

MainScreen::MainScreen(QApplication *mainApp, QWidget *parent): QWidget(parent)
{

    init();
    this->mainApp = mainApp;
    QDesktopWidget *desktop = ((QApplication*)mainApp)->desktop();
    screenAvailableGeometry = desktop->availableGeometry();
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
    imgSaveSize = imgSaveSize*scaleFactor;
    settings = new Settings();
    dataM = new Data();
    deserializeData();

    QTranslator *myappTranslator = new QTranslator();
    QString tsFile = Languages::getLangTs(settings->lang());
    myappTranslator->load(tsFile);
    QApplication::instance()->installTranslator(myappTranslator);
    qDebug()<<"set ts file = "+tsFile;

    connect(mainApp,SIGNAL(applicationStateChanged(Qt::ApplicationState)),this,SLOT( onAppStateChange(Qt::ApplicationState)));

    server = new Server();
    connect(server,SIGNAL(getGrpLstFinish(SERVER_ERRORS, QString)),this,SLOT(onGetGrpFinished(SERVER_ERRORS, QString)));
    connect(server,SIGNAL(getCardLstFinish(SERVER_ERRORS, QString)),this,SLOT(onGetCardLstFinished(SERVER_ERRORS,QString)));
    connect(server,SIGNAL(downloadCardDataFinish(SERVER_ERRORS,QString)),this,SLOT(onCardDataDownloaded(SERVER_ERRORS,QString)));

    mainLayout = new QVBoxLayout();

    mainChoiceScreen = new MainChoiceScreen(appWidowSize,settings,this);
    mainLayout->addWidget(mainChoiceScreen);
    mainChoiceScreen->hide();
    connect(mainChoiceScreen,SIGNAL(iconPressed(MAIN_ICONS)),this,SLOT(onMainIconPressed(MAIN_ICONS)));

    grpScreen = new GrpScreen(screenInfo,appWidowSize,settings->skinColor(),this);
    mainLayout->addWidget(grpScreen);

    cardScreen = new CardScreen(screenInfo,appWidowSize,settings->skinColor(),LOCAL,this);
    cardScreen->hide();
    mainLayout->addWidget(cardScreen);

    cardInfoScreen = new CardInfoScreen(screenInfo,appWidowSize,settings->skinColor(),this);
    cardInfoScreen->hide();
    mainLayout->addWidget(cardInfoScreen);

    // cache last photo form camera dir
    if(appState->getCurOS()!=WINDOWS)
        dataM->cacheLastImg(cameraDir,appDataLocation+cacheDir,cacheImgNum,imgSaveSize);
    // ----cache-----

    if(appState->getCurOS()==WINDOWS)
        cameraQmlScreen = NULL;
    else
    {
        cameraQmlScreen = new CameraQmlScreen(appWidowSize,"NONE");
        mainLayout->addWidget(cameraQmlScreen);
        cameraQmlScreen->turnOfCamera();
    }
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    if(settings->defEnterApp())
    {
        appState->setCurGrpType(LOCAL);
        showGrpScreen();
    }
    else
        showScreen(MAIN_CHOICE_SCREEN);
}

MainScreen::~MainScreen()
{

}

void MainScreen::onMainIconPressed(MAIN_ICONS icon)
{
    switch (icon) {
    case LOCAL_ICON:
        appState->setCurGrpType(LOCAL);
        showGrpScreen();
        break;
    case SRV_ICON:
        appState->setCurGrpType(SERVER);
        if(!server->isGrpLstDownloaded())
        {
            showMsgScreen(msgWaitLoading);
            server->setEndPoint(settings->endPoint());
            server->setLgnPwd(settings->login(),settings->pass());
            server->getGrpLstStart();
        }
        else
            showGrpScreen();
        break;
    case DEV_ICON:
        appState->setCurGrpType(DEVICE);
        break;
    default:
        break;
    }
}

void MainScreen::onGrpSelected(int grpId)
{
    if(grpId==-1)
    {
        //new group add
        showGrpNewScreen();
        return;
    }
    appState->setCurGrpId(grpId);
    if(appState->getCurGrpType()==LOCAL)
        showCardScreen();
    else if(appState->getCurGrpType()==SERVER)
    {
        Grp *grp = server->getGrpTmp(grpId);
        if(grp==NULL)
            return;
        else if(grp->getCards()==NULL)
        {
            showMsgScreen(msgWaitLoading);
            server->setEndPoint(settings->endPoint());
            server->setLgnPwd(settings->login(),settings->pass());
            server->getCardLstStart(grpId);

        }
        else
        {
            showCardScreen();
        }
    }

}

void MainScreen::onGrpBackPressed()
{
    showScreen(MAIN_CHOICE_SCREEN);
}

void MainScreen::showGrpScreen()
{
    adjustSize();
    GrpScreen *screen = new GrpScreen(screenInfo,window()->size(),settings->skinColor(),this);

    if(appState->getCurGrpType()==SERVER)
    {
        screen->setGrpLst(*(server->getGrpLastLst()),InterFace::getGrpViewFolder(settings->grpView()),(appState->getCurOS()!=WINDOWS),false);
    }
    else
        screen->setGrpLst(dataM->getLocalGroups(),InterFace::getGrpViewFolder(settings->grpView()),(appState->getCurOS()!=WINDOWS));
    screen->hide();
    connect(screen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    connect(screen,SIGNAL(backPressed()),this,SLOT(onGrpBackPressed()));
    mainLayout->replaceWidget(grpScreen,screen);
    delete(grpScreen);
    grpScreen = screen;
    showScreen(GRP_SCREEN);
}

void MainScreen::showCardScreen()
{
    Grp *grp;
    int grpId = appState->getCurGrpId();
    CardScreen *screen=NULL;
    if(appState->getCurGrpType()==LOCAL)
    {
        grp = dataM->getLocalGrp(grpId);
    }
    else if(appState->getCurGrpType()==SERVER)
    {
        grp = server->getGrpTmp(grpId);
    }
    if(grp!=NULL)
    {
        screen = new CardScreen(screenInfo,window()->size(),settings->skinColor(),appState->getCurGrpType(),this);
        screen ->setCardList(grp->getName(),InterFace::getGrpViewFolder(settings->grpView())+ grp->getImgSrc(),grp->getCards(),appState->getCurOS()!=WINDOWS);
    }
    else
    {
        return;
    }
    mainLayout->replaceWidget(cardScreen,screen);
    delete(cardScreen);
    cardScreen = screen;
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen()));
    if(appState->getCurGrpType()==LOCAL)
    {
        connect(cardScreen,SIGNAL(cardSelected(int)),this,SLOT(onCardSelected(int)));
        connect(cardScreen,SIGNAL(addCardSelected()),this,SLOT(onNewCardSelected()));
    }
    else if(appState->getCurGrpType()==SERVER)
    {
        connect(cardScreen,SIGNAL(cardSelected(int)),this,SLOT(onCardSelected(int)));
    }
    showScreen(CARD_LST_SCREEN);
}

void MainScreen::onCardSelected(int cardId)
{
    int grpId = appState->getCurGrpId();
    appState->setCurCardId(cardId);

    if(appState->getCurGrpType()==LOCAL)
        showCardInfoScreen();
    else if(appState->getCurGrpType() == SERVER)
    {
        Grp *grp = server->getGrpTmp(grpId);
        CardInfo *card;
        if(grp==NULL)
            return;
        else if((card = grp->getCardInfo(cardId))!=NULL)
        {
            if(!card->isImgLocal())
            {
                showMsgScreen(msgWaitLoading);
                server->setEndPoint(settings->endPoint());
                server->setLgnPwd(settings->login(),settings->pass());
                server->downloadCardDataStart(cardId,grpId);
            }
            else
            {
                showCardInfoScreen();
            }
        }
        else
            return;
    }

}
void MainScreen::showCardInfoScreen(bool fromTmpCardInfo)
{
    int cardId = appState->getCurCardId();
    int grpId = appState->getCurGrpId();
    CardInfo *card;

    CardInfoScreen *screen = new CardInfoScreen(screenInfo,window()->size(),settings->skinColor(),this);

    if(appState->getCurGrpType()==LOCAL)
    {
        if(!fromTmpCardInfo)
            appState->setTmpCardInfo(dataM->getLocalCard(grpId,cardId));
        screen->showCardInfo(appState->tmpCardInfo());
    }
    else
    {
        if(!fromTmpCardInfo)
        {
            card = server->getCardTmp(grpId,cardId);
            appState->setTmpCardInfo(card);
        }
        screen->showCardInfo(appState->tmpCardInfo(),SERVER);
    }

    mainLayout->replaceWidget(cardInfoScreen,screen);
    delete(cardInfoScreen);
    cardInfoScreen = screen;

    connect(cardInfoScreen,SIGNAL(backPressed(bool)),this,SLOT(onPressBackCardInfo(bool)));
    connect(cardInfoScreen,SIGNAL(editFrontSideGalleryImg()),this,SLOT(showGalleryScreenF()));
    connect(cardInfoScreen,SIGNAL(editFrontSideCameraImg()),this,SLOT(showCameraQmlScreenF()));
    connect(cardInfoScreen,SIGNAL(editBackSideGalleryImg()),this,SLOT(showGalleryScreenB()));
    connect(cardInfoScreen,SIGNAL(editBackSideCameraImg()),this,SLOT(showCameraQmlScreenB()));
    connect(cardInfoScreen,SIGNAL(editFrontSideCropImg()),this,SLOT(showCropScreenFront()));
    connect(cardInfoScreen,SIGNAL(editBackSideCropImg()),this,SLOT(showCropScreenBack()));

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
        galleryScreen = new GalleryScreen(screenInfo,window()->size(),settings->skinColor(),appDataLocation+cacheDir,this);
        galleryScreen->hide();
        galleryScreen->showCameraPhotos();
        mainLayout->addWidget(galleryScreen);

        connect(galleryScreen,SIGNAL(pressBack()),this,SLOT(onPressBackGalleryScreen()));

        connect(galleryScreen,SIGNAL(selectPic(QString,QString)),this,SLOT(setCardImgSrcGallery(QString,QString)));
        setFocus();
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

void MainScreen::onPressBackCardInfo(bool cancelChanges)
{
    if(appState->getCurGrpType()==LOCAL && !cancelChanges)
    {
        dataM->setCardInfo(appState->getCurGrpId(),appState->getCurCardId(),appState->tmpCardInfo());
    }
    setFocus();
    showCardScreen();
}

void MainScreen::setCardImgSrc(QString file)
{
    int cardId = appState->getCurCardId();
    int grpId = appState->getCurGrpId();
    CardInfo *cardInf = appState->tmpCardInfo();
    QString imgName;
    if(appState->getCurCardSideState()==FRONTSIDE)
        imgName= cardInf->getCardName()+"_"+QString::number(grpId)+"_"+QString::number(cardId)+"_f";
    else
        imgName= cardInf->getCardName()+"_"+QString::number(grpId)+"_"+QString::number(cardId)+"_b";
    QString saveSrc = appDataLocation+"/"+imgName;
    qDebug()<<"dir+fileName = "<<file;
    qDebug()<<"saveSrc = "<<saveSrc;
    dataM->saveImg(file,saveSrc,imgSaveSize);

    if(appState->getCurCardSideState()==FRONTSIDE)
        cardInf->setCardImgSrc(saveSrc);
    else
        cardInf->setCardImgBackSrc(saveSrc);

    showCardInfoScreen(true);
}

void MainScreen::onPressBackGalleryScreen()
{
    delete(galleryScreen);
    showCardInfoScreen(true);
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
    if(cameraQmlScreen!=NULL)
        delete(cameraQmlScreen);
    if(appState->getCurOS()==WINDOWS)
        cameraQmlScreen = new CameraQmlScreen(window()->size(),"WINDOWS");
    else
        cameraQmlScreen = new CameraQmlScreen(window()->size(),"NONE");
    mainLayout->addWidget(cameraQmlScreen);
    connect(cameraQmlScreen,SIGNAL(pressedCancel()),this,SLOT(onPressBackCameraQmlScreen()));
    connect(cameraQmlScreen,SIGNAL(selectPhoto(QString,QString)),this,SLOT(setCardImgSrc(QString,QString)));
    window()->update();
    setFocus();
    showScreen(CAMERAQML_SCREEN);
}
void MainScreen::onPressBackCameraQmlScreen()
{
    cameraQmlScreen->turnOfCamera();
    showCardInfoScreen(true);
}

void MainScreen::showCropScreenFront()
{
    appState->setCurCardSideState(FRONTSIDE);
    showCropScreen();
}

void MainScreen::showCropScreenBack()
{
    appState->setCurCardSideState(BACKSIDE);
    showCropScreen();
}

void MainScreen::showCropScreen()
{
    if(cropImgScreen!=NULL)
    {
        delete(cropImgScreen);
        cropImgScreen = NULL;
    }
    if(appState->getCurCardSideState()==FRONTSIDE)
    {
        if(appState->tmpCardInfo()->getCardImgSrc()=="")
            return;
        cropImgScreen = new CropImgScreen(window()->size(),scaleFactor,appState->tmpCardInfo()->getCardImgSrc(),appDataLocation+"/"+appState->tmpCardInfo()->getCardName()+"_"+QString::number(appState->tmpCardInfo()->getGrpId())+"_"+QString::number(appState->tmpCardInfo()->getId())+"_f.png",this);
    }
    else
    {
        if(appState->tmpCardInfo()->getCardImgBackSrc()=="")
            return;
        cropImgScreen = new CropImgScreen(window()->size(),scaleFactor,appState->tmpCardInfo()->getCardImgBackSrc(),appDataLocation+"/"+appState->tmpCardInfo()->getCardName()+"_"+QString::number( appState->tmpCardInfo()->getGrpId())+"_"+QString::number(appState->tmpCardInfo()->getId())+"_b.png",this);
    }
    connect(cropImgScreen,SIGNAL(imgCropped(QString)),this,SLOT(onImgCropped(QString)));
    cropImgScreen->show();
    cropImgScreen->setFocus();
}


void MainScreen::showGrpNewScreen()
{
    appState->setCurScreen(NEW_GRP_SCREEN);
    if(newGrpModal!=NULL)
    {
        delete(newGrpModal);
        newGrpModal = NULL;
    }
    newGrpModal = new NewGrpModal(window()->size(),scaleFactor,dataM->getGrpImgSrc(),InterFace::getGrpViewFolder(settings->grpView()),this);
    newGrpModal->show();
    newGrpModal->setIconLst();
    connect(newGrpModal,SIGNAL(newGrpConfigured(QString,QString)),this,SLOT(newGrpConfigured(QString,QString)));
}

void MainScreen::newGrpConfigured(QString name, QString grpImgSrc)
{
    dataM->addNewGrp(name,grpImgSrc);
    grpScreen->setGrpLst(dataM->getLocalGroups(),InterFace::getGrpViewFolder(settings->grpView()),(appState->getCurOS()!=WINDOWS));
    showGrpScreen();
}

void MainScreen::onNewCardSelected()
{
    int grpId = appState->getCurGrpId();
    Grp *grp = dataM->getLocalGrp(grpId);
    CardInfo *card = grp->createNewCard();
    appState->setCurCardId( card->getId());
    showCardInfoScreen();
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

void MainScreen::onImgCropped(QString fileName)
{
    if(appState->getCurCardSideState()==FRONTSIDE)
        appState->tmpCardInfo()->setCardImgSrc(fileName);
    else
        appState->tmpCardInfo()->setCardImgBackSrc(fileName);
    cardInfoScreen->updateImg(appState->getCurCardSideState());
}

void MainScreen::onAppStateChange(Qt::ApplicationState state)
{
    switch (state) {
    case Qt::ApplicationActive:
        qDebug()<<"state = active";
        break;
    case Qt::ApplicationHidden:
        qDebug()<<"state = hidden";
        break;
    case Qt::ApplicationInactive:
        qDebug()<<"state = inactive";
        break;
    case Qt::ApplicationSuspended:
        qDebug()<<"state = suspended";
        serializeData();
        QApplication::instance()->quit();
        break;
    default:
        break;
    }
}

void MainScreen::showMsgScreen(QString msg)
{
    if(msgScreen!=NULL)
    {
        delete(msgScreen);
        msgScreen = NULL;
    }
    msgScreen = new MsgScreen(window()->size(),scaleFactor,msg,this);
    msgScreen->show();
}

void MainScreen::onGetGrpFinished(SERVER_ERRORS servError, QString errorMsg)
{
    qDebug()<< "getGrpResp: "+errorMsg;

    switch (servError) {
    case REQ_OK:
        msgScreen->hide();
        showGrpScreen();
        break;
    case TIMEOUT:
    default:
        msgScreen->setMsgText(errorMsg);
        msgScreen->showSpinner(false);
        msgScreen->showOkIcon(true);
        break;
    }
}

void MainScreen::onGetCardLstFinished(SERVER_ERRORS servError, QString errorMsg)
{
    qDebug()<< "getCardLstResp: "+errorMsg;

    switch (servError) {
    case REQ_OK:
        msgScreen->hide();
        showCardScreen();
        break;
    default:
        msgScreen->setMsgText(errorMsg);
        msgScreen->showSpinner(false);
        msgScreen->showOkIcon(true);
        break;
    }
}

void MainScreen::onCardDataDownloaded(SERVER_ERRORS servError, QString errorMsg)
{
    qDebug()<< "cardDataDownloadedResp: "+errorMsg;
    switch (servError) {
    case REQ_OK:
        dataM->saveCardFromSrv(server->getGrpTmp(appState->getCurGrpId()),server->getCardTmp(appState->getCurGrpId(),appState->getCurCardId()),appDataLocation,imgSaveSize);
        msgScreen->hide();
        showCardInfoScreen();
        break;
    default:
        msgScreen->setMsgText(errorMsg);
        msgScreen->showSpinner(false);
        msgScreen->showOkIcon(true);
        break;
    }
}

void MainScreen::showScreen(SCREEN_TYPE scr)
{
    hideAllScreens();
    appState->setCurScreen(scr);
    switch (scr) {
    case MAIN_CHOICE_SCREEN:
        mainChoiceScreen->showMainChoice();
        break;
    case GRP_SCREEN:
        grpScreen->show();
        break;
    case CARD_LST_SCREEN:
        cardScreen->show();
        break;
    case CARD_INFO_SCREEN:
        cardInfoScreen->show();
        cardInfoScreen->setFocus();
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
    if(cameraQmlScreen!=NULL)
        cameraQmlScreen->hide();
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
        qDebug() << "Key_Back event screen = " << appState->getCurScreen();
        switch (appState->getCurScreen()) {
        case MAIN_CHOICE_SCREEN:
            mainChoiceScreen->onKeyBackPressed(event);
            return;
        case GRP_SCREEN:
             showScreen(MAIN_CHOICE_SCREEN);
            return;
        case CARD_LST_SCREEN:
            showGrpScreen();
            return;
        case CARD_INFO_SCREEN:
            showCardScreen();
            return;
        case GALLERY_SCREEN:
            delete(galleryScreen);
            showCardInfoScreen(true);
            return;
        case CAMERAQML_SCREEN:
            showCardInfoScreen(true);
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

void MainScreen::changeEvent(QEvent *e)
{
    if(e->type()==QEvent::LanguageChange)
        translateNames();
    QWidget::changeEvent(e);
}

void MainScreen::closeEvent(QCloseEvent *event)
 {
    serializeData();
    event->accept();
 }

bool MainScreen::serializeData()
{
    QString folderForCache = "/saveData/";
    QFile file(appDataLocation+folderForCache+"oneCardData.dat");
    QDir dir(appDataLocation+folderForCache);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream<<*settings<<*dataM;
        file.close();
        return true;
    }
    else
        return false;
}

bool MainScreen::deserializeData()
{
    QString folderForCache = "/saveData/";
    QFile file(appDataLocation+folderForCache+"oneCardData.dat");

    if(file.exists())
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            stream>>*settings>>*dataM;
            file.close();
            return true;
        }

    return false;

}

