// jump_tablewindow.h

#ifndef JP_WINDOW_H
#define JP_WINDOW_H

#include "../../info/info_window.h"

class QPushButton;

class JTWindow : public QMainWindow {
    Q_OBJECT
public:
    JTWindow(QWidget *parent = nullptr);

private slots:
    void runTest();

private:
    QPushButton *runButton;
    QTextEdit  *outputBox;

    QSpinBox *spinVectorSize;
    QSpinBox *spinRunCount;

    void printResult(const QString &text);  // helper to print to QTextEdit and console
};

#endif // JP_WINDOW_H
