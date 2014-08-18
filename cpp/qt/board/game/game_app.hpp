#ifndef GAME_APP_H
#define GAME_APP_H

#include <QApplication>

class GameApp
{
public:
    GameApp();
    virtual ~GameApp();

    bool init(int argc, char **argv);
    int run();

private:
    QApplication *app_;
};

#endif // GAME_APP_H
