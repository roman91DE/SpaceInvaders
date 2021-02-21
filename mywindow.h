#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "ConsoleWindow.h"
#include "spaceInvader.h"

class myWindow : public ConsoleWindow
{
    Q_OBJECT
private:
        Game *game;

public:
    myWindow();
    ~myWindow();
    virtual void onRefresh();
    void drawCurrentState();
};
#endif // MYWINDOW_H
