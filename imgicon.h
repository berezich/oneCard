#ifndef IMGICON_H
#define IMGICON_H
#include <QLabel>
#include <QIcon>
#include <QImage>
#include <QTransform>

class ImgIcon : public QLabel
{
public:

    Q_OBJECT
public:
    ImgIcon(int id, QString imgScr,  QSize imgSize, bool isExpand=true, QWidget *parent=0);
    ~ImgIcon();
    QImage *getQImg(){return picImg;}
signals:
    void click(int iconId);
private:
    int id;
    QIcon *picIcon;
    QImage *picImg;
    QImage *picImgRotate;
    QPixmap pixmap;
    QString imgScr;
    QSize imgSize;
    QSize iconSize;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // IMGICON_H
