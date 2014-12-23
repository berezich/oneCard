#ifndef CAP_H
#define CAP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "simpleicon.h"
class Cap : public QWidget
{
Q_OBJECT
public:
    explicit Cap(int height, QString color = "#80bab7", QWidget *parent = 0);
    ~Cap();


signals:

public slots:
    void setTitle(QString txt, double textSize, int leftMargin=0, QString color = "#ffffff");
    void addRightIcon(SimpleIcon *icon, int rightOffset);
    void addLeftIcon(SimpleIcon *icon, int leftOffset);

private:
    int height = 120;
    QString color = "#aaaaaa";
    QHBoxLayout *hLayout;
    QString title=tr("TITLE");
    QLabel *titleLbl;
    QLabel *rightIcon;
    QLabel *leftIcon;
};

#endif // CAP_H
