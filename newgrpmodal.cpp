#include "newgrpmodal.h"

NewGrpModal::NewGrpModal(QSize size,double scale,QStringList grpIconLst, QWidget *parent):Overlay(parent)
{
    scaleFactor = scale;
    screenSize = size;
    gridSpace = gridSpace*scale;
    rectSize = rectSize*scale;
    rectPoint= QPoint((screenSize.width()-rectSize.width())/2,(screenSize.height()-rectSize.height())/2-yRound*scale);

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
    for(int i=0; i<columnsNum*rowsNum; i++)
    {
        if(i < imgSrcLst.length())
        {
            //icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), QSize(190*scaleFactor,190*scaleFactor)/*,*new QSize(230*scaleFactor,210*scaleFactor)*/);
            icon = new SimpleIcon(i,imgSrcLst[i],"",iconSize);
            icon->setAlignment(Qt::AlignVCenter /*| Qt::AlignRight*/);
            //icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), QSize(190*scaleFactor,190*scaleFactor)/*,*new QSize(230*scaleFactor,210*scaleFactor)*/);
            connect(icon,SIGNAL(click(int)),this,SLOT(onClickGrpIcon(int)));
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }
    //this->hide();
}

void NewGrpModal::paintEvent(QPaintEvent *event)
{
    Overlay::paintEvent(event);
    QPainter customPainter(this);
    customPainter.setRenderHint(QPainter::Antialiasing);
    customPainter.setBrush(QBrush(QColor(backGroundColor)));
    customPainter.drawRoundedRect(QRect(rectPoint,rectSize),xRound,yRound/*,backGroundColor*/);

    QLabel *formWindow = new QLabel();
    QIcon *picIcon = new QIcon(":/svg/tools/modalwindow.svg");
    formWindow->setPixmap(picIcon->pixmap(rectSize));
    formWindow->setAlignment(Qt::AlignCenter);
    //formWindow->setMinimumSize(rectSize);
    //formWindow->setMaximumSize(rectSize);
    //formWindow->adjustSize();
    formWindow->setContentsMargins(rectPoint.x(),rectPoint.y(),rectPoint.x(),rectPoint.y());

    formBasic = new QVBoxLayout();
    formWidget = new QWidget();
    formBasic->setContentsMargins(rectPoint.x(),rectPoint.y(),rectPoint.x(),rectPoint.y());

    formBasic->addWidget(formWidget);
    //formBasic->addWidget(formWindow);

    // set black background
    //QPalette Pal(formWidget->palette());
    //Pal.setColor(QPalette::Background, Qt::red);
    //formWidget->setAutoFillBackground(true);
    //formWidget->setPalette(Pal);

    setLayout(formBasic);

    formLayout = new QVBoxLayout();
    formWidget->setLayout(formLayout);
    //formWindow->setLayout(formLayout);

    nameLbl = new QLabel(lbl1);
    nameLbl->setFont(QFont("Calibri",lblTxtSize));
    nameLbl->setStyleSheet("QLabel { color : "+lblTxtColor+"; }");
    formLayout->addWidget(nameLbl);

    grpName = new QLineEdit();
    grpName->setFont(QFont("Calibri",lblTxtSize));
    grpName->setStyleSheet("QLabel { color : "+lblTxtColor+"; }");
    formLayout->addWidget(grpName);

    choiceLbl = new QLabel(lbl2);
    choiceLbl->setFont(QFont("Calibri",lblTxtSize));
    choiceLbl->setStyleSheet("QLabel { color : "+lblTxtColor+"; }");
    formLayout->addWidget(choiceLbl);

    QWidget *lineWidget = new QWidget();
    QHBoxLayout *lineGridLayout = new QHBoxLayout();
    lineWidget->setLayout(lineGridLayout);

    gridWidget = new QWidget();
    gridLayout = new QGridLayout();
    //gridWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    gridLayout->setSpacing(gridSpace);
    lineGridLayout->addStretch(1);
    lineGridLayout->addWidget(gridWidget);
    lineGridLayout->addStretch(1);

    gridWidget->setLayout(gridLayout);
    formLayout->addWidget(lineWidget);

    setIconLst();

    formLayout->addStretch(1);

    SimpleIcon *icon;
    icon = new SimpleIcon(-1,":/svg/tools/arrowok.svg","",iconOkSize);
    icon->setAlignment(Qt::AlignHCenter|Qt::AlignBottom /*| Qt::AlignRight*/);

    formLayout->addWidget(icon);



}

void NewGrpModal::onClickGrpCreated()
{
    //emit newGrpConfigured(grpName->text(),grpImgSrcSelected);
}

void NewGrpModal::onClickGrpIcon(int i)
{
    grpImgSrcSelected = imgSrcLst[i];
}



