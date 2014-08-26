#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <memory>
#include <vector>

#include <QObject>

#include "events/event_data.hpp"
#include "actors/actor_factory.hpp"
#include "view/iview.hpp"

enum class LogicState {
    LS_Uninitialized,
    LS_MainMenu,
    LS_Game,
    LS_Invalid
};

class GameLogic {
public:
    explicit GameLogic(QObject *qroot);
    void change_state(LogicState state);
    void add_view(std::shared_ptr<IView> view);
    void change_view(std::shared_ptr<IView> view);

private:
    LogicState state_;
    QObject *qroot_;
    ActorFactory *actor_factory_;
    std::vector<std::shared_ptr<IView>> view_list_;
};

#endif // GAME_LOGIC_HPP
