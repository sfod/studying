#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <utility>
#include "actors/actor.hpp"

class Graph {
public:
    Graph();
    ~Graph();

    bool add_actor(ActorId id, const std::pair<int, int> &pos);

private:
    std::map<ActorId, std::pair<int, int>> actor_pos_list_;
};

#endif // GRAPH_HPP
