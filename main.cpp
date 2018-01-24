#include <QApplication>
#include "gamescreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameScreen tertrisGame;
    tertrisGame.show();

    return a.exec();
}
