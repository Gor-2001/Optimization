// prediction_window.h

#ifndef PREDICTION_WINDOW_H
#define PREDICTION_WINDOW_H

#include "prediction_test.h"
#include "../../info/info_window.h"

class QPushButton;

class PredictionWindow : public QMainWindow {
    Q_OBJECT
public:
    PredictionWindow(QWidget *parent = nullptr);

private slots:
    void runTest();

private:

    QPushButton *runButton;
    QPushButton *openButton;
    QTextEdit   *outputBox;

    QSpinBox    *spinDataSize;
    QSpinBox    *spinSeparators;
    QSpinBox    *spinRunCount;
    QSpinBox    *spinRange;
};

#endif // PREDICTION_WINDOW_H
