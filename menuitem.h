#ifndef MENUITEM_H
#define MENUITEM_H
#include <QPushButton>
#include <QPalette>
#include <QHBoxLayout>
#include <QMouseEvent>
class MenuItem : public QPushButton
{
    Q_OBJECT
private:
    QString txtColor;
    QString txtPressColor;
    int textLeftOffset;
    int textTopOffset;
    double textSize;
    int id;
    void init()
    {
        txtColor = "#000000";
        txtPressColor = "#ffffff";
    }

signals:
    void click(int id);
public:
    MenuItem(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent=0);
    ~MenuItem();
    void setUnerLine(bool val);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MENUITEM_H
