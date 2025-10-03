// main_window.h

#ifndef MAIN_MENU_WINDOW_H
#define MAIN_MENU_WINDOW_H

#include "prediction/inc/prediction_window.h"
#include "jump_table/inc/jump_table_window.h"

class QPushButton;

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);

private slots:
    void openPTWindow();
    void openJumpTableWindow();

private:
    QPushButton *openButton;
};

#endif // MAIN_MENU_WINDOW_H
