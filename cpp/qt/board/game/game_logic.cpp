#include "game_logic.hpp"
#include <QDebug>
#include <boost/bind.hpp>

#include "events/event_manager.hpp"
#include "view/main_menu_view.hpp"
#include "view/player_view.hpp"

GameLogic::GameLogic(QObject *qroot)
    : state_(LogicState::LS_Uninitialized), qroot_(qroot), view_list_()
{
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
    case LogicState::LS_Game:
        view.reset(new PlayerView(qroot_));
        view->init();
        change_view(view);
        break;
    case LogicState::LS_Invalid:
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
