#include "game_logic.hpp"
#include <QDebug>
#include <boost/bind.hpp>

#include "view/main_menu_view.hpp"
#include "view/options_view.hpp"
#include "view/game_view.hpp"
#include "actors/graph_component.hpp"

GameLogic::GameLogic(QObject *qroot)
    : state_(LogicState::LS_Uninitialized), qroot_(qroot), conn_list_(),
    actor_factory_(new ActorFactory), actor_keeper_(new ActorKeeper),
    graph_(new Graph), view_list_()
{
    bs2::connection conn = EventManager::get()->add_listener(
                boost::bind(&GameLogic::req_actor_move_delegate, this, _1),
                EventData_RequestActorMove::event_type_);
    conn_list_.push_back(conn);
}

GameLogic::~GameLogic()
{
    for (auto conn : conn_list_) {
        conn.disconnect();
    }
}

void GameLogic::change_state(LogicState state)
{
    std::shared_ptr<IView> view;

    switch (state) {
    case LogicState::LS_Uninitialized:
        break;
    case LogicState::LS_MainMenu:
        view.reset(new MainMenuView(qroot_));
        view->init();
        change_view(view);
        break;
    case LogicState::LS_Options:
        view.reset(new OptionsView(qroot_));
        view->init();
        change_view(view);
        break;
    case LogicState::LS_Game: {
        view.reset(new GameView(qroot_));
        view->init();

        set_player(1);
        set_player(2);

        change_view(view);
        break;
    }
    case LogicState::LS_Invalid:
        break;
    default:
        break;
    }
}

void GameLogic::add_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}

void GameLogic::change_view(std::shared_ptr<IView> view)
{
    if (!view_list_.empty()) {
        view_list_.pop_back();
    }
    view_list_.push_back(view);
}

void GameLogic::req_actor_move_delegate(const std::shared_ptr<EventData> &event)
{
    std::shared_ptr<EventData_RequestActorMove> req_event =
            std::dynamic_pointer_cast<EventData_RequestActorMove>(event);

    const std::shared_ptr<Actor> &actor = actor_keeper_->actor(req_event->actor_id());
    if (actor) {
        ComponentId cid = ActorComponent::id(GraphComponent::name_);
        auto graph_comp = std::dynamic_pointer_cast<GraphComponent>(actor->component(cid));
        if (graph_comp && graph_comp->move_actor(req_event->node())) {
            auto move_event = std::make_shared<EventData_MoveActor>(
                    actor->id(),
                    graph_comp->node(),
                    graph_comp->possible_moves());
            EventManager::get()->queue_event(move_event);
        }
    }
}

void GameLogic::set_player(int idx)
{
    std::string resource_file = "../board/data/player_" + std::to_string(idx) + ".json";
    std::shared_ptr<Actor> actor = actor_factory_->create_actor(resource_file.c_str());
    if (actor) {
        auto new_event = std::make_shared<EventData_NewActor>(actor->id());
        EventManager::get()->trigger_event(new_event);

        ComponentId cid = ActorComponent::id(GraphComponent::name_);
        auto graph_comp = std::dynamic_pointer_cast<GraphComponent>(actor->component(cid));
        if (graph_comp) {
            auto move_event = std::make_shared<EventData_MoveActor>(
                    actor->id(),
                    graph_comp->node(),
                    graph_comp->possible_moves());
            EventManager::get()->queue_event(move_event);
        }
    }
}
