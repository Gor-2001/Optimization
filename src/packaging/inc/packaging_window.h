// packaging_window.h

#ifndef PACKAGING_WINDOW_H
#define PACKAGING_WINDOW_H

#include "packaging_test.h"
#include "../../info/info_window.h"

class QPushButton;

class PackagingWindow : public QMainWindow {
    Q_OBJECT
public:
    PackagingWindow(QWidget *parent = nullptr);

private slots:
    void runTest();

private:
    QPushButton *runButton;
    QPushButton *openButton;
    QTextEdit  *outputBox;

    QSpinBox *spinDataSize;
    QSpinBox *spinSeparators;
    QSpinBox *spinRunCount;
    QSpinBox *spinRange;
};

#endif // PACKAGING_WINDOW_H
