#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>

class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget *parent = 0);
    ~Overlay();

protected:

    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QWidget *blankSpace;
    QSize size;

};

#endif // OVERLAY_H
