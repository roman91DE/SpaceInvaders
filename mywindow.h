#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

class myWindow : public QMainWindow
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = nullptr);
    ~myWindow();
};
#endif // MYWINDOW_H
