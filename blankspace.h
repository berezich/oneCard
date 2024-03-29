#ifndef BLANKSPACE_H
#define BLANKSPACE_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include "menu.h"

class BlankSpace : public QWidget
{
    Q_OBJECT
public:
    explicit BlankSpace(QSize availSize, double scale, QWidget *parent = 0);
    ~BlankSpace();
    void showMenu();
    void initMenu();
    QScrollArea *scroll;
signals:

public slots:
private:
    Menu *menuWidget;
    double scaleFactor;
    QSize availSize;
};

#endif // BLANKSPACE_H
