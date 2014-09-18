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
    player_list_(), graph_(new Graph), view_list_(), player_idx_(1)
{
    register_delegates();
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
        if (view->init()) {
            change_view(view);
        }
        break;
    case LogicState::LS_Options:
        view.reset(new OptionsView(qroot_));
        if (view->init()) {
            change_view(view);
        }
        break;
    case LogicState::LS_Game: {
        view_list_.clear();
        for (auto actor : player_list_) {
            view.reset(new GameView(qroot_));
            if (view->init()) {
                add_view(view);
                view->attach(actor->id());
            }
        }
        set_players();
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

void GameLogic::main_menu_win_delegate(const std::shared_ptr<EventData> &/*event*/)
{
    change_state(LogicState::LS_MainMenu);
}

void GameLogic::options_win_delegate(const std::shared_ptr<EventData> &/*event*/)
{
    change_state(LogicState::LS_Options);
}

void GameLogic::game_win_delegate(const std::shared_ptr<EventData> &/*event*/)
{
    change_state(LogicState::LS_Game);
}

void GameLogic::game_end_delegate(const std::shared_ptr<EventData> &/*event*/)
{
    player_list_.clear();
    player_idx_ = 1;
}

void GameLogic::req_actor_new_delegate(const std::shared_ptr<EventData> &event)
{
    auto req_new_event = std::dynamic_pointer_cast<EventData_RequestNewActor>(event);
    create_player(player_idx_);
    ++player_idx_;
}

void GameLogic::req_actor_move_delegate(const std::shared_ptr<EventData> &event)
{
    auto req_move_event = std::dynamic_pointer_cast<EventData_RequestActorMove>(event);

    const std::shared_ptr<Actor> &actor = actor_keeper_->actor(req_move_event->actor_id());
    if (actor) {
        ComponentId cid = ActorComponent::id(GraphComponent::name_);
        auto graph_comp = std::dynamic_pointer_cast<GraphComponent>(actor->component(cid));
        if (graph_comp && graph_comp->move_actor(req_move_event->node())) {
            auto move_event = std::make_shared<EventData_MoveActor>(
                    actor->id(),
                    graph_comp->node(),
                    graph_comp->possible_moves());
            EventManager::get()->queue_event(move_event);
        }
    }
}

void GameLogic::register_delegates()
{
    bs2::connection conn;

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::main_menu_win_delegate, this, _1),
            EventData_MainMenu::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::options_win_delegate, this, _1),
            EventData_Options::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::game_win_delegate, this, _1),
            EventData_Game::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::game_end_delegate, this, _1),
            EventData_GameEnd::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::req_actor_new_delegate, this, _1),
            EventData_RequestNewActor::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameLogic::req_actor_move_delegate, this, _1),
            EventData_RequestActorMove::event_type_);
    conn_list_.push_back(conn);
}

void GameLogic::create_player(int idx)
{
    std::string resource_file = "../board/data/player_" + std::to_string(idx) + ".json";
    std::shared_ptr<Actor> actor = actor_factory_->create_actor(resource_file.c_str());
    if (actor) {
        player_list_.push_back(actor);
    }
}

void GameLogic::set_players()
{
    for (auto actor : player_list_) {
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
