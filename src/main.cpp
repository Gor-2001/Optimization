// main.h

#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainMenuWindow menu;
    menu.show();

    return app.exec();
}
