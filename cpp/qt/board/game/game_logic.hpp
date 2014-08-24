#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <memory>
#include <vector>
#include "events/event_data.hpp"
#include "view/iview.hpp"

class GameLogic {
public:
    GameLogic();
    void add_view(std::shared_ptr<IView> view);
    void change_view(std::shared_ptr<IView> view);

    void new_game_delegate(const std::shared_ptr<EventData> &event);

private:
    std::vector<std::shared_ptr<IView>> view_list_;
};

#endif // GAME_LOGIC_HPP
