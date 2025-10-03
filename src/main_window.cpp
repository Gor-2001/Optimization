// main_window.cpp

#include "main_window.h"
#include "main_utils.h"

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

    // Button: Jump Table Test
    QPushButton *jumpTableButton = new QPushButton("Open Jump Table Test", this);
    jumpTableButton->setFixedSize(200, 40);
    mainLayout->addWidget(jumpTableButton, 0, Qt::AlignHCenter);
    connect(jumpTableButton, &QPushButton::clicked, this, &MainMenuWindow::openJTWindow);

    // Optional: add stretch to push buttons slightly up
    mainLayout->addStretch();

    setCentralWidget(central);
}


void MainMenuWindow::openPTWindow()
{
    PredictionWindow *ptWindow = new PredictionWindow(this); // create PT window
    ptWindow->show();
}

void MainMenuWindow::openJTWindow()
{
    JTWindow *jtWindow = new JTWindow(this); // create JT window
    jtWindow->show();
}