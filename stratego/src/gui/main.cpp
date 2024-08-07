#include "MainWindow.h"
#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    stratego::Game game{};
    //stratego::ControllerG controller{game};
    //controller.startGame();
    MainWindow view{game};
    view.show();
    return app.exec();
}
