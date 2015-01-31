#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include "overlay.h"

class LoadingScreen : public Overlay
{
public:
    LoadingScreen(QSize size, double scale,QWidget *parent = 0);
    ~LoadingScreen();
};

#endif // LOADINGSCREEN_H
