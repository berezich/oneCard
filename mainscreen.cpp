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

    mainLayout = new QVBoxLayout();

    dataM->getLocalGroups();

    grpScreen = new GrpScreen(screenInfo,this);
    grpScreen->setGrpLst(dataM->getLocalGroups());
    grpScreen->hide();
    connect(grpScreen,SIGNAL(selectLocalGrp(int)),this,SLOT(onLocalGrpSelected(int)));
    mainLayout->addWidget(grpScreen);

    cardScreen = new CardScreen(screenInfo,this);
    cardScreen->hide();
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    mainLayout->addWidget(cardScreen);

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    showScreen(LOCAL_GRP_SCREEN);


}

MainScreen::~MainScreen()
{

}

void MainScreen::onLocalGrpSelected(int grpId)
{
    CardScreen *screen;

    Grp *grp = dataM->getLocalGrp(grpId);
    screen = new CardScreen(screenInfo,this);
    screen ->setCardList(grp->getName(),grp->getImgSrc(),dataM->getLocalCards(grpId));
    mainLayout->replaceWidget(cardScreen,screen);
    cardScreen = screen;
    connect(cardScreen,SIGNAL(backPressed(int)),this,SLOT(showGrpScreen(int)));
    //cardScreen->hide();
    showScreen(CARD_LST_SCREEN);
}

void MainScreen::showGrpScreen(int i)
{
    if(grpState==LOCAL)
        showScreen(LOCAL_GRP_SCREEN);
    else if(grpState==CLOUD)
        showScreen(CLOUD_LST_SCREEN);

}

void MainScreen::showScreen(MainScreen::SCREEN_TYPE scr)
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
        break;
    default:

        break;
    }
}

void MainScreen::hideAllScreens()
{
    grpScreen->hide();
    cardScreen->hide();
}

