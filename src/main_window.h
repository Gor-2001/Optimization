// main_window.h

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "prediction/prediction_window.h"
#include "jump_table/jump_table_window.h"
#include "dependency/dependency_window.h"

class QPushButton;

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);

private slots:
    void openPredictionWindow();
    void openJumpTableWindow();
    void openDependencyWindow();
    
private:
    QPushButton *openButton;
};

#endif // MAIN_WINDOW_H
