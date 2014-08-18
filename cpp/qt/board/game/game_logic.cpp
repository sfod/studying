#include "game_logic.hpp"

GameLogic::GameLogic() : view_list_()
{
}

void GameLogic::add_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}
