#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>

#include "../inc/window.h"
#include "../../define.h"


AAAWindow::AAAWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    // Spin boxes layout
    auto *paramsLayout = new QHBoxLayout();

    mainLayout->addLayout(paramsLayout);

    // Run Test button
    runButton = new QPushButton("Run AAA Test", this);
    mainLayout->addWidget(runButton);

    // Output box
    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);
    mainLayout->addWidget(outputBox);

    setCentralWidget(central);

    // Make window larger by default
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    connect(runButton, &QPushButton::clicked, this, &AAAWindow::runTest);
}

// Helper: print to both QTextEdit and console
void AAAWindow::printResult(const QString &text)
{
    outputBox->append(text);
    qDebug() << text;
}

// Run Prediction test
void AAAWindow::runTest()
{
    printf("AAA");
}

