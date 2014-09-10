#include "graph.hpp"
#include <QDebug>

Graph::Graph() : actor_pos_list_()
{
}

Graph::~Graph()
{
}

bool Graph::add_actor(ActorId id, const std::pair<int, int> &pos)
{
    actor_pos_t actor_pos;
    actor_pos.pos = pos;
    actor_pos_list_[id] = actor_pos;
    set_possible_moves(id);
    return true;
}

bool Graph::move_actor(ActorId id, const std::pair<int, int> &pos)
{
    actor_pos_list_[id].pos = pos;
    set_possible_moves(id);
    return true;
}

std::pair<int, int> Graph::pos(ActorId id) const
{
    if (actor_pos_list_.count(id) > 0) {
        return actor_pos_list_.at(id).pos;
    }
    return std::make_pair<int, int>(-1, -1);
}

std::list<std::pair<int, int> > Graph::possible_moves(ActorId id) const
{
    if (actor_pos_list_.count(id) > 0) {
        return actor_pos_list_.at(id).possible_moves_;
    }
    return std::list<std::pair<int, int>>();
}

// @fixme
void Graph::set_possible_moves(ActorId id)
{
    if (actor_pos_list_.count(id) > 0) {
        actor_pos_t &actor_pos = actor_pos_list_[id];
        std::pair<int, int> &pos = actor_pos.pos;

        actor_pos.possible_moves_.clear();

        std::pair<int, int> move;
        if (pos.first > 0) {
            move.first = pos.first - 1;
        }
        else {
            move.first = pos.first + 1;
        }

        if (pos.second > 0) {
            move.second = pos.second - 1;
        }
        else {
            move.second = pos.second + 1;
        }

        actor_pos.possible_moves_.push_back(move);
    }
}
