#ifndef SIMPLEICON_H
#define SIMPLEICON_H

//#include <QWidget>
#include <QLabel>
#include <QIcon>

class SimpleIcon : public QLabel
{
    Q_OBJECT
public:
    SimpleIcon(int id, QString imgScr,  QString imgPushScr, QSize imgSize, QWidget *parent=0);
    ~SimpleIcon();
signals:
    void click(int iconId);
private:
    int id;
    QIcon *picIcon;
    QIcon *picPushIcon;
    QString imgScr;
    QString imgPushScr;
    QSize imgSize;
    QSize iconSize;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SIMPLEICON_H