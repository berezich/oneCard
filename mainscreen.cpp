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
    grpScreen = new GrpScreen(screenInfo,this);
    mainLayout->addWidget(grpScreen);
    //mainLayout->setAlignment()
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    grpScreen->setGrpLst(dataM->getLocalGroups());

    //this->setLayout(mainLayout);
}

MainScreen::~MainScreen()
{

}

