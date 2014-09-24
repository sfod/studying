#include "randomer_brain.hpp"
#include <ctime>
#include <boost/random/uniform_int_distribution.hpp>
#include "events/event_manager.hpp"

RandomerBrain::RandomerBrain() : actor_id_(-1), graph_(), gen_()
{
    gen_.seed(static_cast<unsigned int>(std::time(NULL)));
}

void RandomerBrain::make_move()
{
    const std::list<Node> &moves = graph_->possible_moves(actor_id_);
    boost::random::uniform_int_distribution<> dist(0, moves.size() - 1);
    int r = dist(gen_);

    int i = 0;
    auto it = moves.begin();
    while (i < r) {
        ++it;
        ++i;
    }

    auto req_move_event = std::make_shared<EventData_RequestActorMove>(actor_id_, *it);
    EventManager::get()->queue_event(req_move_event);
}
