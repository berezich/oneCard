#ifndef SWIPECOVER_H
#define SWIPECOVER_H

#include <QWidget>
#include <QScroller>
#include <QScrollPrepareEvent>
#include <QDebug>
#include <QScrollBar>
#include <QList>
#include <QPoint>

class SwipeCover : public QWidget
{
    Q_OBJECT
public:
    explicit SwipeCover(int veiwPortHeigt,int range, QScrollBar *scrollBar, QWidget *parent = 0);
    ~SwipeCover();

signals:
    void onClick(QPoint pos);
public slots:
private:
    QList<qreal> posLst;
    qreal curPos;
    qreal range;
    int veiwPortHeigt;
    QSize parentSize;
    QScrollBar *scrollBar;
    qreal k;
    int delta;
    bool isScrolled;
    bool event(QEvent *e);
    void init()
    {
        curPos = 0;
        k=0.8;
        posLst.clear();
        delta = 1;

    }
    /*
    qreal getCurPos(qreal pos)
    {
        qreal res=curPos;
        if(delta > 1)
        {
            qreal dx0 =posLst[1] - posLst[0];
            qreal dx1;
            for(int i=1; i<delta-1; i++)
            {
                dx1 = posLst[i+1]-posLst[i];
                if(dx0*dx1<0)
                    break;
                dx0 = dx1;
                if(i==delta-2)
                    if((pos - posLst[delta-1])*dx0>=0)
                        res = pos;
            }
            if(delta==2)
                if((pos - posLst[1])*dx0>=0)
                    res = pos;
            for(int i=0; i<delta-1; i++)
                posLst[i]=posLst[i+1];
            posLst[delta-1]=pos;
            return res;
        }
        else if(delta==1)
            return pos;
        else
            return 0;


    }
    */
};

#endif // SWIPECOVER_H
