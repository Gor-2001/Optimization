#ifndef PREDICTION_WINDOW_H
#define PREDICTION_WINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>

class QPushButton;

class PredictionWindow : public QMainWindow {
    Q_OBJECT
public:
    PredictionWindow(QWidget *parent = nullptr);

private slots:
    void runTest();

private:
    QPushButton *runButton;
    QTextEdit  *outputBox;

    QSpinBox *spinVectorSize;
    QSpinBox *spinSeparators;
    QSpinBox *spinRunCount;
    QSpinBox *spinRange;

    void printResult(const QString &text);  // helper to print to QTextEdit and console
};

#endif // PREDICTION_WINDOW_H
