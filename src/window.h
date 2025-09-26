#ifndef MAIN_MENU_WINDOW_H
#define MAIN_MENU_WINDOW_H

#include <QMainWindow>
#include "define.h"

class QPushButton;

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);

private slots:
    void openPSVWindow();

private:
    QPushButton *openButton;
};

#endif // MAIN_MENU_WINDOW_H
