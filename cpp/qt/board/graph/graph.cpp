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
    actor_pos_list_[id] = pos;
    return true;
}
