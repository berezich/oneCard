#ifndef CAP_H
#define CAP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include "simpleicon.h"
#include "interface.h"
class Cap : public QWidget
{
Q_OBJECT
public:
    //explicit Cap(int height, QString color = "#80bab7", QWidget *parent = 0);
    explicit Cap(int height, int colorName, QWidget *parent = 0);
    ~Cap();


signals:

public slots:
    void setTitle(QString txt, double textSize, int leftMargin=0, QString color = "#ffffff");
    void addRightIcon(SimpleIcon *icon, int rightOffset);
    void addLeftIcon(SimpleIcon *icon, int leftOffset);

private:
    int height;
    QString color;
    QHBoxLayout *hLayout;
    QString title;
    QLabel *titleLbl;
    QLabel *rightIcon;
    QLabel *leftIcon;
    QWidgetList childWidgets;
    QList<QLayout *> childLayouts;
    void init()
    {
        height = 120;
        color = "#aaaaaa";
    }
};

#endif // CAP_H
