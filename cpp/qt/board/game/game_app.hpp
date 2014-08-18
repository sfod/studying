#ifndef GAME_APP_H
#define GAME_APP_H

#include <memory>
#include <vector>

#include <QGuiApplication>
#include <QQuickView>

//#include "game_logic.hpp"
//#include "view/iview.hpp"

class GameApp
{
public:
    GameApp();
    virtual ~GameApp();

    bool init(int argc, char **argv);
    int run();

private:
    QGuiApplication *qapp_;
    QQuickView *qview_;
//    GameLogic logic_;
};

#endif // GAME_APP_H
