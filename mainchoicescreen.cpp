#include "mainchoicescreen.h"

MainChoiceScreen::MainChoiceScreen( QSize appScrSize, Settings *settings, QWidget *parent): QWidget(parent)
{
    init();
    this->settings = settings;
    //this->screenInfo = screenInfo;
    //screenSize = screenInfo->geometry().size();
    screenSize = appScrSize;
    backGroundColor = InterFace::getSkinColor(settings->skinColor()).head();

    scaleFactorW = ((double)screenSize.width())/(double)defaultWidth;
    scaleFactorH = ((double)screenSize.height())/(double)defaultHeight;

    scaleFactor = qMin(scaleFactorW,scaleFactorH);

    setMinimumSize(screenSize);
    setMaximumSize(screenSize);

    setContentsMargins(0,0,0,0);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, backGroundColor);
    setAutoFillBackground(true);
    setPalette(Pal);

    iconSize = iconSize*scaleFactor;
    textSize = textSize*qSqrt(qSqrt(scaleFactor));
    topOffset = topOffset*scaleFactor;

    okIconSize = okIconSize*scaleFactor;
    defTextSize = defTextSize*qSqrt(qSqrt(scaleFactor));
    defTextLeftOffset = defTextLeftOffset*scaleFactor;

    QVBoxLayout *basicLayout = new QVBoxLayout(this);
    setLayout(basicLayout);
    basicLayout->setContentsMargins(0,0,0,0);
    gridWidget = new QWidget();
    basicLayout->addSpacing(topOffset);
    basicLayout->addWidget(gridWidget);

    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);
    gridWidget->setLayout(gridLayout);


    basicLayout->addStretch(1);


    QWidget *defEnterWidget = new QWidget(this);
    QHBoxLayout *defEnterLayout = new QHBoxLayout(defEnterWidget);
    defEnterLayout->setContentsMargins(screenSize.width()/6,0,screenSize.width()/6,0);
    defEnterWidget->setLayout(defEnterLayout);
    basicLayout->addWidget(defEnterWidget);

    checkBox = new SimpleIcon(0,":/svg/main_screen/greenok.svg","",okIconSize,true);
    connect(checkBox,SIGNAL(click(int)),this,SLOT(onCheckBoxChanged()));
    checkBox->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    if(!settings->defEnterApp())
        checkBox->unselectIcon();
    else
        checkBox->selectIcon();
    defEnterLayout->addWidget(checkBox);

    defEnterLayout->addSpacing(defTextLeftOffset);

    defLabel = new QLabel(defText);
    defLabel->setWordWrap(true);
    defLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    defLabel->setFont(QFont("Calibri",defTextSize));
    defLabel->setStyleSheet("QLabel { color : "+defTextColor+"; }");
    defLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    defEnterLayout->addWidget(defLabel);



    basicLayout->addStretch(1);

    setGrpLst();

    menuWidget = new Menu(screenSize,scaleFactor,settings,this);
    menuWidget->hide();
    connect(menuWidget,SIGNAL(changeSettings(OPTIONS)),this,SLOT(onChangeSettings(OPTIONS)));

}
void MainChoiceScreen::setGrpLst()
{
    for(int i=0; i<icons.length(); i++)
        delete icons[i];
    icons.clear();

    Icon *icon;

    QSize gridItemSize = QSize(screenSize.width()/columnsNum,(screenSize.height())/rowsNum - 10*scaleFactor);

    icon = new Icon(int(LOCAL_ICON),catalogName,textSize, catalogIconSrc, "", iconSize, gridItemSize,defTextColor);
    connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickMainIcon(int)));
    gridLayout->addWidget(icon, 0,0);
    icons.append(icon);

    icon = new Icon(int(SRV_ICON),srvCatalogName,textSize, srvCatalogIconSrc, "", iconSize, gridItemSize,defTextColor);
    connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickMainIcon(int)));
    gridLayout->addWidget(icon, 0,1);
    icons.append(icon);

    icon = new Icon(int(DEV_ICON),devCatalogName,textSize, devCatalogIconSrc, "", iconSize, gridItemSize,defTextColor);
    connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickMainIcon(int)));
    gridLayout->addWidget(icon, 1,0);
    icons.append(icon);

    icon = new Icon(int(OPTIONS_ICON),optionsName,textSize, optionsIconSrc, "", iconSize, gridItemSize,defTextColor);
    connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickMainIcon(int)));
    gridLayout->addWidget(icon, 1,1);
    icons.append(icon);
}

void MainChoiceScreen::showMainChoice()
{
    show();
    setMaximumSize(window()->geometry().size());

}

void MainChoiceScreen::onKeyBackPressed(QKeyEvent *event)
{
    if(menuWidget->isMenuOpen())
        menuWidget->showMainMenu();
    else
        QWidget::keyPressEvent(event);
}

void MainChoiceScreen::onClickMainIcon(int iconId)
{
    if(iconId == OPTIONS_ICON)
    {
        menuWidget->showMainMenu();
    }
    else
    {
        emit iconPressed((MAIN_ICONS) iconId);
    }

}

void MainChoiceScreen::onCheckBoxChanged()
{
    if(settings->defEnterApp())
        checkBox->unselectIcon();
    else
        checkBox->selectIcon();

    settings->setDefEnterApp(!(settings->defEnterApp()));

}

void MainChoiceScreen::onChangeSettings(OPTIONS option)
{
    switch (option) {
    case COLOR:
        backGroundColor = InterFace::getSkinColor(settings->skinColor()).head();
        QPalette Pal(palette());
        // set black background
        Pal.setColor(QPalette::Background, backGroundColor);
        setAutoFillBackground(true);
        setPalette(Pal);
        show();
        break;
    }


    emit changeSettings(option);
}

void MainChoiceScreen::retranslate()
{
    translateNames();
    defLabel->setText(defText);
    setGrpLst();
}

void MainChoiceScreen::changeEvent(QEvent *e)
{
    if(e->type()==QEvent::LanguageChange)
    {
        retranslate();
    }
    QWidget::changeEvent(e);
}


MainChoiceScreen::~MainChoiceScreen()
{
    while(children().length()>0)
        if(children().last())
            delete(children().last());
}

