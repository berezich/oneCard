#include "msgscreen.h"

MsgScreen::MsgScreen(QSize size, double scale, QString msg, QWidget *parent):Overlay(parent)
{
    init();
    this->msg = msg;
    scaleFactor = scale;
    screenSize = size;
    setMinimumSize(size);
    setMaximumSize(size);
    rectSize = rectSize*scale;
    iconSize = iconSize*scale;
    frameCenterOffset = frameCenterOffset*scale;
    rectPoint= QPoint((screenSize.width()-rectSize.width())/2,(screenSize.height()-rectSize.height())/2-frameCenterOffset);
    fontSize = fontSize * qSqrt(qSqrt(scaleFactor));
    txtOffset = txtOffset*scaleFactor;
    txtBottomOffset = txtBottomOffset*scaleFactor;
    scrLayout = new QVBoxLayout();

    showSpinner(true);

}

MsgScreen::~MsgScreen()
{
    while(this->children().length()>0)
        delete(children().last());
}

void MsgScreen::showSpinner(bool val)
{
    if(val)
    {
        if(spin!=NULL)
            delete(spin);
        spin = new Spinner(scaleFactor,this);
        scrLayout->addWidget(spin);
    }
    else
    {
        if(spin!=NULL)
        {
            spin->hide();
            //delete(spin);
            //spin=NULL;
        }
    }
}

void MsgScreen::showOkIcon(bool val)
{
    if(val)
    {
        if(iconWidget!=NULL)
        {
            iconWidget->show();
            //delete(iconWidget);
            //iconWidget = NULL;
        }
        else
        {
            iconWidget = new QWidget(this);
            iconWidget->setMinimumSize(screenSize);
            iconWidget->setMaximumSize(screenSize);

            scrLayout->addWidget(iconWidget);
            QVBoxLayout *iconLayout = new QVBoxLayout(iconWidget);
            iconWidget->setLayout(iconLayout);
            //iconLayout->addStretch(1);
            SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/loginok.svg","",iconSize,false,iconWidget);
            connect(icon,SIGNAL(click(int)),this,SLOT(onIconPressed()));
            icon->setAlignment(Qt::AlignCenter);
            iconLayout->addWidget(icon);
            iconWidget->show();
            update();
            //iconLayout->addStretch(1);
        }
    }
    else
    {
        if(iconWidget!=NULL)
            iconWidget->hide();
    }


}

void MsgScreen::paintEvent(QPaintEvent *e)
{
    QPainter customPainter(this);
    QFont font ("Calibri",fontSize);
    //QPen pen(QColor(txtColor));
    QPen pen(txtColor);
    customPainter.setRenderHint(QPainter::Antialiasing);
    customPainter.setBrush(QBrush(QColor(backGroundColor)));
    customPainter.drawRoundedRect(QRect(rectPoint,rectSize),xRound,yRound);
    customPainter.setFont(font);
    customPainter.setPen(pen);
    customPainter.drawText(QRect(rectPoint+QPoint(txtOffset,txtOffset),rectSize-QSize(txtOffset*2,txtBottomOffset)), Qt::AlignCenter, msg);
    customPainter.end();
}


