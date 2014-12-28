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
    QString txtColor = "#000000";
    QString txtPressColor = "#ffffff";
    int textLeftOffset;
    int textTopOffset;
    int id;
signals:
    void click(int id);
public:
    MenuItem(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent=0);
    ~MenuItem();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MENUITEM_H
