// main_window.cpp

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "main_window.h"
#include "prediction/inc/prediction_window.h"
#include "aaa/inc/aaa_window.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Main Menu");
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT); // use constants

    QWidget *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    // Remove unnecessary spacing and margins
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Button: Prediction Test
    QPushButton *predictionButton = new QPushButton("Open Prediction Test", this);
    predictionButton->setFixedSize(200, 40);
    mainLayout->addWidget(predictionButton, 0, Qt::AlignHCenter);
    connect(predictionButton, &QPushButton::clicked, this, &MainMenuWindow::openPTWindow);

    // Button: AAA Test
    QPushButton *aaaButton = new QPushButton("Open AAA Test", this);
    aaaButton->setFixedSize(200, 40);
    mainLayout->addWidget(aaaButton, 0, Qt::AlignHCenter);
    connect(aaaButton, &QPushButton::clicked, this, &MainMenuWindow::openAAAWindow);

    // Optional: add stretch to push buttons slightly up
    mainLayout->addStretch();

    setCentralWidget(central);
}


void MainMenuWindow::openPTWindow()
{
    PredictionWindow *ptWindow = new PredictionWindow(this); // create PT window
    ptWindow->show();
}

void MainMenuWindow::openAAAWindow()
{
    AAAWindow *aaaWindow = new AAAWindow(this); // create PT window
    aaaWindow->show();
}