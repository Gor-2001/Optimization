#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "window.h"
#include "prediction/inc/window.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Main Menu");
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT); // use constants

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    openButton = new QPushButton("Open PSV Window", this);
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &MainMenuWindow::openPSVWindow);

    setCentralWidget(central);
}

void MainMenuWindow::openPSVWindow()
{
    MainWindow *psvWindow = new MainWindow(this); // create PSV window
    psvWindow->show();
}
