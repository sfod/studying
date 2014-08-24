#include "game_logic.hpp"
#include <QDebug>
#include <boost/bind.hpp>
#include "events/event_manager.hpp"

GameLogic::GameLogic() : view_list_()
{
}

void GameLogic::add_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}

void GameLogic::change_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}
