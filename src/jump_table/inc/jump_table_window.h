// jump_tablewindow.h

#ifndef JP_WINDOW_H
#define JP_WINDOW_H

#include "../../info/info_window.h"
#include "jump_table_test.h"

class QPushButton;

class JumpTableWindow : public QMainWindow {
    Q_OBJECT
public:
    JumpTableWindow(QWidget *parent = nullptr);

private slots:
    void runTest();

private:
    QPushButton *runButton;
    QTextEdit  *outputBox;

    QSpinBox *spinDataSize;
    QSpinBox *spinRunCount;
};

#endif // JP_WINDOW_H
