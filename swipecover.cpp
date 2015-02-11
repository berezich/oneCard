#include "swipecover.h"

SwipeCover::SwipeCover(int veiwPortHeigt, int range, QScrollBar *scrollBar, QWidget *parent) : QWidget(parent)
{
//    QPalette Pal(palette());
//    // set black background
//    Pal.setColor(QPalette::Background, Qt::green);
//    setAutoFillBackground(true);
//    setPalette(Pal);
    init();
    this->veiwPortHeigt = veiwPortHeigt;
    this->parentSize = parent->size();
    this->scrollBar = scrollBar;
    this->range = range*k;
    scrollBar->setMinimum(0);
    scrollBar->setMaximum((int)(this->range));
    setPalette(Qt::transparent);
    //setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    setMaximumSize( parent->size());
    setMinimumSize( parent->size());
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    QScroller::grabGesture(this,QScroller::LeftMouseButtonGesture);
    //show();
}

SwipeCover::~SwipeCover()
{

}

bool SwipeCover::event(QEvent *e)
{
    switch (e->type()) {
// ![1]
    case QEvent::ScrollPrepare:
    {
        // We set the snap positions as late as possible so that we are sure
        // we get the correct itemHeight
        //QScroller *scroller = QScroller::scroller(this);
        //scroller->setSnapPositionsY( 600, 300 );
        //scroller->scrollTo(QPointF(0,30));
        for(int i=0; i<delta; i++)
            posLst.append(curPos);
        QScrollPrepareEvent *se = static_cast<QScrollPrepareEvent *>(e);
        se->setViewportSize(QSizeF(parentSize));
        // we claim a huge scrolling area and a huge content position and
        // hope that the user doesn't notice that the scroll area is restricted
        se->setContentPosRange(QRectF(0.0, 0.0, 0.0,range));
        se->setContentPos(QPointF(0.0, curPos));
        se->accept();
        isScrolled=false;
        qDebug()<<"ScrollPrepare";
        return true;
    }
// ![1]
// ![2]
    case QEvent::Scroll:
    {
        QScrollEvent *se = static_cast<QScrollEvent *>(e);
        isScrolled = true;
        curPos  =  se->contentPos().y();
        scrollBar->setValue((int)(curPos/k));
        //qreal y = 0;
        qDebug() <<"Scroll: " << curPos;
        //QScroller *scroller = QScroller::scroller(this);
        //scroller->scrollTo(QPointF(0,curPos));
        //int iy = y - WHEEL_SCROLL_OFFSET;
        //int ih = 10;

// ![2]
// ![3]
        // -- calculate the current item position and offset and redraw the widget
        int ic = 20;
        if (ic>0) {
            //m_currentItem = iy / ih % ic;
            //m_itemOffset = iy % ih;

            // take care when scrolling backwards. Modulo returns negative numbers
//            if (m_itemOffset < 0) {
//                m_itemOffset += ih;
//                m_currentItem--;
//            }

//            if (m_currentItem < 0)
//                m_currentItem += ic;
        }
        // -- repaint
        //update();

        se->accept();

        return true;
// ![3]
    }
    case QEvent::MouseButtonPress:
        isScrolled = false;
        //qDebug()<<"MouseButtonPress!!! "<<((QMouseEvent*)e)->pos();
        return true;
    case QEvent::MouseButtonRelease:
        if(!isScrolled)
        {
            qDebug()<<"MouseButtonClick!!! "<<((QMouseEvent*)e)->pos();
            emit onClick(((QMouseEvent*)e)->pos()+QPoint(0,scrollBar->value()));
        }
        isScrolled = false;
        return true;

    default:
        return QWidget::event(e);
    }
    return true;

}
