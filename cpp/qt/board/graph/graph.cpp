#include "graph.hpp"
#include <QDebug>

Graph::Graph() : actor_node_list_()
{
}

Graph::~Graph()
{
}

bool Graph::add_actor(ActorId id)
{
    if (actor_node_list_.count(id) == 0) {
        actor_node_t actor_node;
        actor_node_list_[id] = actor_node;
        return true;
    }
    return false;
}

bool Graph::move_actor(ActorId id, const Node &node)
{
    if (actor_node_list_.count(id) > 0) {
        actor_node_list_[id].node = node;
        set_possible_moves(id);
        return true;
    }
    return false;
}

Node Graph::node(ActorId id) const
{
    if (actor_node_list_.count(id) > 0) {
        return actor_node_list_.at(id).node;
    }
    return Node();
}

std::list<Node> Graph::possible_moves(ActorId id) const
{
    if (actor_node_list_.count(id) > 0) {
        return actor_node_list_.at(id).possible_moves_;
    }
    return std::list<Node>();
}

// @fixme
void Graph::set_possible_moves(ActorId id)
{
    if (actor_node_list_.count(id) > 0) {
        actor_node_t &actor_node = actor_node_list_[id];
        Node &node = actor_node.node;

        actor_node.possible_moves_.clear();
        node.neighbours(9, 9, &actor_node.possible_moves_);
    }
}
