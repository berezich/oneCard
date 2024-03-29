#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>

//empty screen with semi-transparent background
class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget *parent = 0);
    ~Overlay();

private:
    QWidget *blankSpace;
    QSize size;

};

#endif // OVERLAY_H
