// main_window.h

#ifndef MAIN_MENU_WINDOW_H
#define MAIN_MENU_WINDOW_H

#include <QMainWindow>
#include "main_utils.h"

class QPushButton;

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);

private slots:
    void openPTWindow();
    void openJTWindow();
    void openAAAWindow();

private:
    QPushButton *openButton;
};

#endif // MAIN_MENU_WINDOW_H
