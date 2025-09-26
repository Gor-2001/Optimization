#include <QApplication>

#include "prediction/window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("PSV Optimization Test");
    window.show();

    return app.exec();
}
