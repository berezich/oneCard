#include "mainscreen.h"
#include "grpscreen.h"

MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{

}

MainScreen::MainScreen(QScreen *screenInfo, QWidget *parent): QWidget(parent)
{

    this->screenInfo = screenInfo;
    screenSize = screenInfo->geometry().size();
    scaleFactor = screenSize.width()/defaultWidth;
    dataM = new Data();
    qDebug()<<"scale = "<< scaleFactor;
    setMinimumSize(screenSize);

    appState = new AppState();

    mainLayout = new QVBoxLayout();

    dataM->getLocalGroups();

    grpScreen = new GrpScreen(screenInfo,this);
    grpScreen->setGrpLst(dataM->getLocalGroups());
    grpScreen->hide();
    connect(grpScreen,SIGNAL(selectLocalGrp(int)),this,SLOT(onGrpSelected(int)));
    mainLayout->addWidget(grpScreen);

    cardScreen = new CardScreen(screenInfo,this);
    cardScreen->hide();
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    mainLayout->addWidget(cardScreen);

    cardInfoScreen = new CardInfoScreen(screenInfo,this);
    cardInfoScreen->hide();
    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));
    mainLayout->addWidget(cardInfoScreen);

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    appState->setCurGrpType(LOCAL);
    showScreen(LOCAL_GRP_SCREEN);
    //appState->setCurGrpId(1);
    //appState->setCurCardId(100);
    //showCardInfoScreen(appState->getCurCardId());


}

MainScreen::~MainScreen()
{

}

void MainScreen::onGrpSelected(int grpId)
{
    if(grpId==-1)
    {
        //добавление новой группы
        return;
    }
    appState->setCurGrpId(grpId);
    showCardScreen(0);

}

void MainScreen::showGrpScreen(int i)
{
    if(appState->getCurGrpType()==LOCAL)
        showScreen(LOCAL_GRP_SCREEN);
    else if(appState->getCurGrpType()==CLOUD)
        showScreen(CLOUD_LST_SCREEN);

}

void MainScreen::showCardScreen(int i)
{
    Grp *grp;
    int grpId = appState->getCurGrpId();
    CardScreen *screen = new CardScreen(screenInfo,this);
    if(appState->getCurGrpType()==LOCAL)
    {
        grp = dataM->getLocalGrp(grpId);
        screen ->setCardList(grp->getName(),grp->getImgSrc(),dataM->getLocalCards(grpId));
    }
    mainLayout->replaceWidget(cardScreen,screen);
    cardScreen = screen;
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    connect(cardScreen,SIGNAL(cardSelected(int)),this,SLOT(showCardInfoScreen(int)));
    //cardScreen->hide();
    showScreen(CARD_LST_SCREEN);

}
void MainScreen::showCardInfoScreen(int cardId)
{
    int grpId = appState->getCurGrpId();
    CardInfoScreen *screen = new CardInfoScreen(screenInfo,this);
    if(appState->getCurGrpType()==LOCAL)
    {
        screen->showCardInfo(dataM->getLocalCard(grpId,cardId));
    }
    mainLayout->replaceWidget(cardInfoScreen,screen);
    cardInfoScreen = screen;
    connect(cardInfoScreen,SIGNAL(backPressed(int)),this,SLOT(showCardScreen(int)));


    showScreen(CARD_INFO_SCREEN);

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
    default:

        break;
    }
}

void MainScreen::hideAllScreens()
{
    grpScreen->hide();
    cardScreen->hide();
    cardInfoScreen->hide();
}

