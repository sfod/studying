#include "game/game_app.hpp"

int main(int argc, char *argv[])
{
    GameApp app;
    if (!app.init(argc, argv)) {
        return EXIT_FAILURE;
    }

    return app.run();
}
