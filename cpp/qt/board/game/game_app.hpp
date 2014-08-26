#ifndef GAME_APP_H
#define GAME_APP_H

#include <memory>
#include <vector>

#include <QQmlEngine>
#include <QQmlComponent>

#include "events/event_manager.hpp"
#include "game_logic.hpp"

class GameApp {
public:
    GameApp();
    virtual ~GameApp();

    int run(int argc, char **argv);

    void main_menu_delegate(const std::shared_ptr<EventData> &event);
    void new_game_delegate(const std::shared_ptr<EventData> &event);
    void quit_delegate(const std::shared_ptr<EventData> &event);

private:
    void register_delegates();

private:
    EventManager *event_manager_;
    GameLogic *logic_;
    QQmlEngine *qengine_;
    QQmlComponent *qcomponent_;
    QObject *qroot_;
};

#endif // GAME_APP_H
