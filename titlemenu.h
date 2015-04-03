#ifndef TITLEMENU_H
#define TITLEMENU_H
#include <QLabel>

class TitleMenu : public QLabel
{
    Q_OBJECT
private:
    QString txtColor;
    QString txtPressColor;

    int textLeftOffset;
    int textTopOffset;
    int id;
    void init()
    {
        txtColor = "#ffffff";
        txtPressColor = "#b2dfdb";
    }

signals:
    void click(int id);
public:
    TitleMenu(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent=0);
    ~TitleMenu();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif
