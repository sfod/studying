#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <utility>
#include "actors/actor.hpp"

struct actor_pos_t {
    std::pair<int, int> pos;
    std::list<std::pair<int, int>> possible_moves_;
};

class Graph {
public:
    Graph();
    ~Graph();

    bool add_actor(ActorId id, const std::pair<int, int> &pos);
    bool move_actor(ActorId id, const std::pair<int, int> &pos);

    std::pair<int, int> pos(ActorId id) const;
    std::list<std::pair<int, int>> possible_moves(ActorId id) const;

private:
    void set_possible_moves(ActorId id);

private:
    std::map<ActorId, actor_pos_t> actor_pos_list_;
};

#endif // GRAPH_HPP
