#ifndef TITLEMENU_H
#define TITLEMENU_H
#include <QLabel>

class TitleMenu : public QLabel
{
    Q_OBJECT
private:
    QString txtColor = "#ffffff";
    //QString txtPressColor = "#81d4fa";
    QString txtPressColor = "#b2dfdb";

    int textLeftOffset;
    int textTopOffset;
    int id;
signals:
    void click(int id);
public:
    TitleMenu(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent=0);
    ~TitleMenu();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif
