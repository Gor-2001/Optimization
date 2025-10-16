// main_window.cpp

#include "main_window.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    const uint16_t spaceSize = 10;
    const uint16_t marginSize = 20;
    const uint16_t buttonWidth = 200;
    const uint16_t buttonHeight = 40;

    setWindowTitle("Main Menu");
    setMinimumSize(BaseWindow::window_width, BaseWindow::window_height); // use constants

    QWidget *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    // Remove unnecessary spacing and margins
    mainLayout->setSpacing(spaceSize);
    mainLayout->setContentsMargins(marginSize, marginSize, marginSize, marginSize);

    // Button: Prediction Test
    QPushButton *predictionButton = new QPushButton("Open Prediction Test", this);
    predictionButton->setFixedSize(buttonWidth, buttonHeight);
    mainLayout->addWidget(predictionButton, 0, Qt::AlignHCenter);
    connect(predictionButton, &QPushButton::clicked, this, &MainMenuWindow::openPredictionWindow);

    // Button: Jump Table Test
    QPushButton *jumpTableButton = new QPushButton("Open Jump Table Test", this);
    jumpTableButton->setFixedSize(buttonWidth, buttonHeight);
    mainLayout->addWidget(jumpTableButton, 0, Qt::AlignHCenter);
    connect(jumpTableButton, &QPushButton::clicked, this, &MainMenuWindow::openJumpTableWindow);

    // Button: Dependency Test
    QPushButton *dependencyButton = new QPushButton("Open Dependency Test", this);
    dependencyButton->setFixedSize(buttonWidth, buttonHeight);
    mainLayout->addWidget(dependencyButton, 0, Qt::AlignHCenter);
    connect(dependencyButton, &QPushButton::clicked, this, &MainMenuWindow::openDependencyWindow);

    // Button: Packaging  Test
    QPushButton *packagingButton = new QPushButton("Open Packaging Test", this);
    packagingButton->setFixedSize(buttonWidth, buttonHeight);
    mainLayout->addWidget(packagingButton, 0, Qt::AlignHCenter);
    connect(packagingButton, &QPushButton::clicked, this, &MainMenuWindow::openPackagingWindow);

    // Optional: add stretch to push buttons slightly up
    mainLayout->addStretch();

    setCentralWidget(central);
}


void MainMenuWindow::openPredictionWindow()
{
    PredictionWindow *ptWindow = new PredictionWindow(this); // create PT window
    ptWindow->show();
}

void MainMenuWindow::openJumpTableWindow()
{
    JumpTableWindow *jump_tableWindow = new JumpTableWindow(this); // create JumpTable window
    jump_tableWindow->show();
}

void MainMenuWindow::openDependencyWindow()
{
    DependencyWindow *dependencyWindow = new DependencyWindow(this); // create Dependency window
    dependencyWindow->show();
}


void MainMenuWindow::openPackagingWindow()
{
    PackagingWindow *packagingWindow = new PackagingWindow(this); // create Packaging window
    packagingWindow->show();
}