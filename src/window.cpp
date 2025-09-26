#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "window.h"
#include "prediction/inc/window.h"
#include "aaa/inc/window.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Main Menu");
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT); // use constants

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    openButton = new QPushButton("Open Prediction Test", this);
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &MainMenuWindow::openPTWindow);

    openButton = new QPushButton("Open AAA Test", this);
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &MainMenuWindow::openAAAWindow);

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