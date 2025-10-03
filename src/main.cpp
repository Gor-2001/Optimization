// main.cpp

#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainMenuWindow menu;
    menu.show();

    return app.exec();
}
