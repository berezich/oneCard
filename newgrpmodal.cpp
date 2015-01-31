#include "newgrpmodal.h"

NewGrpModal::NewGrpModal(QSize size,double scale,QStringList grpIconLst, QWidget *parent):Overlay(parent)
{
    init();
    scaleFactor = scale;
    screenSize = size;
    setMinimumSize(size);
    setMaximumSize(size);
    gridSpace = gridSpace*scale;
    rectSize = rectSize*scale;
    rectPoint= QPoint((screenSize.width()-rectSize.width())/2,(screenSize.height()-rectSize.height())/2);

    xRound = xRound *scale;
    yRound = yRound *scale;
    lblTxtSize = qSqrt(qSqrt(scale))*lblTxtSize;
    iconSize = iconSize*scale;
    iconOkSize = iconOkSize*scale;

    imgSrcLst = grpIconLst;
}

NewGrpModal::~NewGrpModal()
{

}

void NewGrpModal::setIconLst()
{
    SimpleIcon *icon;

    QLabel *formWindow = new QLabel();
    QIcon *picIcon = new QIcon(":/svg/tools/modalwindow.svg");
    formWindow->setPixmap(picIcon->pixmap(rectSize));
    formWindow->setAlignment(Qt::AlignCenter);

    formBasic = new QVBoxLayout();
    formWidget = new QWidget();
    formBasic->setContentsMargins(rectPoint.x()+10*scaleFactor,rectPoint.y(),rectPoint.x()+10*scaleFactor,rectPoint.y()-12*scaleFactor);

    formBasic->addWidget(formWidget);
    setLayout(formBasic);

    formLayout = new QVBoxLayout();
    formLayout->setSpacing(0);
    formWidget->setLayout(formLayout);

    nameLbl = new QLabel(lbl1);
    nameLbl->setFont(QFont("Calibri",lblTxtSize));
    nameLbl->setStyleSheet("QLabel { color : "+lblTxtColor+"; }");
    formLayout->addWidget(nameLbl);

    QWidget *editName = new QWidget();
    QHBoxLayout *editNameLayout = new QHBoxLayout();
    editName->setLayout(editNameLayout);
    editNameLayout->addSpacing(20*scaleFactor);
    grpName = new QLineEdit();
    grpName->setFont(QFont("Calibri",lblTxtSize));

    grpName->setStyleSheet(" color : "+lblTxtColor+/*"; border: 0px solid gray; background: "+backGroundColor+*/";");
    //nameEditLine->setStyleSheet("border: 0px solid gray; border-radius: 10px; padding: 0 8px; background: "+backGroundColor+"; selection-background-color: darkgray;");
    grpName->setAlignment(Qt::AlignCenter);
    grpName->setMaxLength(10);
    editNameLayout->addWidget(grpName);
    editNameLayout->addSpacing(20*scaleFactor);
    //formLayout->addWidget(grpName);
    formLayout->addWidget(editName);

    choiceLbl = new QLabel(lbl2);
    choiceLbl->setFont(QFont("Calibri",lblTxtSize));
    choiceLbl->setStyleSheet("QLabel { color : "+lblTxtColor+"; }");
    formLayout->addWidget(choiceLbl);

    QWidget *lineWidget = new QWidget();
    QHBoxLayout *lineGridLayout = new QHBoxLayout();
    lineWidget->setLayout(lineGridLayout);

    gridWidget = new QWidget();
    //gridWidget->setContentsMargins(0,0,0,0);
    gridLayout = new QGridLayout();
    //gridWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    gridLayout->setSpacing(gridSpace);
    lineGridLayout->addStretch(1);
    lineGridLayout->addWidget(gridWidget);
    lineGridLayout->addStretch(1);

    gridWidget->setLayout(gridLayout);
    formLayout->addWidget(lineWidget);

    for(int i=0; i<columnsNum*rowsNum; i++)
    {
        if(i < imgSrcLst.length())
        {
            //icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), QSize(190*scaleFactor,190*scaleFactor)/*,*new QSize(230*scaleFactor,210*scaleFactor)*/);
            icon = new SimpleIcon(i,imgSrcLst[i],"",iconSize,true);
            if(i==0)
            {
                icon->selectIcon();
                selectedIcon = i;

            }
            iconsGrid.append(icon);
            icon->setAlignment(Qt::AlignVCenter /*| Qt::AlignRight*/);
            //icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), QSize(190*scaleFactor,190*scaleFactor)/*,*new QSize(230*scaleFactor,210*scaleFactor)*/);
            connect(icon,SIGNAL(click(int)),this,SLOT(onClickGrpIcon(int)));
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }
    formLayout->addStretch(1);

    //SimpleIcon *icon;
    QWidget *confLineWidget = new QWidget();
    QHBoxLayout *confLineLayout = new QHBoxLayout();
    confLineWidget->setLayout(confLineLayout);
    confLineLayout->addStretch(1);
    confLineLayout->setContentsMargins(0,0,0,0);

    icon = new SimpleIcon(-1,":/svg/tools/close.svg","",iconOkSize);
    icon->setAlignment(Qt::AlignHCenter|Qt::AlignBottom /*| Qt::AlignRight*/);
    connect(icon,SIGNAL(click(int)),this,SLOT(onClickGrpCancel()));
    icon->adjustSize();
    confLineLayout->addWidget(icon);
    confLineLayout->addStretch(1);
    icon = new SimpleIcon(-1,":/svg/tools/arrowok.svg","",iconOkSize);
    icon->setAlignment(Qt::AlignHCenter|Qt::AlignBottom /*| Qt::AlignRight*/);
    icon->adjustSize();
    connect(icon,SIGNAL(click(int)),this,SLOT(onClickGrpOk()));
    confLineLayout->addWidget(icon);
    confLineLayout->addStretch(1);

    formLayout->addWidget(confLineWidget);
    //this->hide();
}

void NewGrpModal::paintEvent(QPaintEvent *event)
{
    //Overlay::paintEvent(event);
    QPainter customPainter(this);
    customPainter.setRenderHint(QPainter::Antialiasing);
    customPainter.setBrush(QBrush(QColor(backGroundColor)));
    customPainter.drawRoundedRect(QRect(rectPoint,rectSize),xRound,yRound);
    //setIconLst();
}

void NewGrpModal::onClickGrpOk()
{
    this->hide();
    emit newGrpConfigured(grpName->text(),iconsGrid[selectedIcon]->getImgSrc());
}

void NewGrpModal::onClickGrpIcon(int i)
{
    if(selectedIcon>=0 && selectedIcon!=i)
        iconsGrid[selectedIcon]->unselectIcon();
    selectedIcon = i;
}

void NewGrpModal::onClickGrpCancel()
{
    this->hide();
}



