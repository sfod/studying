#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <memory>
#include <vector>

#include <QObject>

#include "events/event_manager.hpp"
#include "events/event_data.hpp"
#include "actors/actor_factory.hpp"
#include "actors/actor_keeper.hpp"
#include "graph/graph.hpp"
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
    ~GameLogic();

    std::shared_ptr<ActorKeeper> actor_keeper() const { return actor_keeper_; }
    std::shared_ptr<Graph> graph() const { return graph_; }

    void change_state(LogicState state);
    void add_view(std::shared_ptr<IView> view);
    void change_view(std::shared_ptr<IView> view);

    void req_actor_move_delegate(const std::shared_ptr<EventData> &event);

private:
    void set_player(int idx);

private:
    LogicState state_;
    QObject *qroot_;
    std::list<bs2::connection> conn_list_;
    ActorFactory *actor_factory_;
    std::shared_ptr<ActorKeeper> actor_keeper_;
    std::shared_ptr<Graph> graph_;
    std::vector<std::shared_ptr<IView>> view_list_;
};

#endif // GAME_LOGIC_HPP
