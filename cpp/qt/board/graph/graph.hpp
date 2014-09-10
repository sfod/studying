#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include "node.hpp"
#include "actors/actor.hpp"

struct actor_node_t {
    Node node;
    std::list<Node> possible_moves_;
};

class Graph {
public:
    Graph();
    ~Graph();

    bool add_actor(ActorId id);
    bool move_actor(ActorId id, const Node &node);

    Node node(ActorId id) const;
    std::list<Node> possible_moves(ActorId id) const;

private:
    void set_possible_moves(ActorId id);

private:
    std::map<ActorId, actor_node_t> actor_node_list_;
};

#endif // GRAPH_HPP
