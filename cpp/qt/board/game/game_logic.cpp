#include "game_logic.hpp"
#include <QDebug>
#include <boost/bind.hpp>
#include "events/event_manager.hpp"

GameLogic::GameLogic() : view_list_()
{
    EventManager::get()->add_listener(
                boost::bind(&GameLogic::new_game_delegate, this, _1),
                EventData_NewGame::event_type_);
}

void GameLogic::add_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}

void GameLogic::change_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}

void GameLogic::new_game_delegate(const std::shared_ptr<EventData> &event)
{
    (void) event;
    qDebug() << "new game delegate called";
}
