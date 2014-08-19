#ifndef GAME_APP_H
#define GAME_APP_H

#include <memory>
#include <vector>

#include "game_logic.hpp"

class GameApp
{
public:
    GameApp();
    virtual ~GameApp();

    int run(int argc, char **argv);

private:
    GameLogic logic_;
};

#endif // GAME_APP_H
