#ifndef ICON_H
#define ICON_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QIcon>
#include <QFrame>
#include <QLabel>

class Icon : public QWidget
{
    Q_OBJECT
public:
    explicit Icon(QWidget *parent = 0);
    Icon(int id, QString name, int textSize, QString imgScr,  QString imgPushScr, QSize imgSize, QSize iconSize = QSize(0,0), QString textColor="#000000", QWidget *parent = 0);
    ~Icon();

signals:
    void clickIcon(int id);
public slots:
private slots:

private:
    int id;
    QIcon *picIcon;
    QIcon *picPushIcon;
    QString name;
    QString imgScr;
    QString imgPushScr;
    QSize imgSize;
    QSize iconSize;
    QLabel *labelIcon;
    QVBoxLayout *vLayout;
    QString textColor;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ICON_H
