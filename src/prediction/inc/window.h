#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>

class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

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

#endif // MAIN_WINDOW_H
