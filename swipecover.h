#ifndef SWIPECOVER_H
#define SWIPECOVER_H

#include <QWidget>
#include <QScroller>
#include <QScrollPrepareEvent>
#include <QDebug>
#include <QScrollBar>
#include <QList>
#include <QPoint>

//QWidget which is displayed over the list (grps or cards) in oder to implement scrolling with swipe
//only for Andorid
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
};

#endif // SWIPECOVER_H
