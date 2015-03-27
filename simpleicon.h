#ifndef SIMPLEICON_H
#define SIMPLEICON_H

#include <QLabel>
#include <QIcon>

class SimpleIcon : public QLabel
{
    Q_OBJECT
public:
    SimpleIcon(int id, QString imgScr,  QString imgPushScr, QSize imgSize, bool staySelected=false ,QWidget *parent=0);
    ~SimpleIcon();

signals:
    void click(int iconId);
public slots:
    void unselectIcon();
    void selectIcon();
private:
    int id;
    QIcon *picIcon;
    QIcon *picPushIcon;
    QString imgScr;
    QString imgPushScr;
    QSize imgSize;
    QSize iconSize;
    bool staySelected;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    QString getImgSrc(){return imgScr.split("/")[imgScr.split("/").length()-1];}
};

#endif // SIMPLEICON_H
