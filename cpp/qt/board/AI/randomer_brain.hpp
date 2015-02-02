#ifndef RANDOMER_BRAIN_HPP
#define RANDOMER_BRAIN_HPP

#include "brain.hpp"
#include <boost/random/mersenne_twister.hpp>
#include "graph/graph.hpp"

class RandomerBrain : public Brain {
public:
    RandomerBrain();

    virtual void make_move() override;
    virtual void set_actor_id(ActorId actor_id) { actor_id_ = actor_id; }
    virtual void set_graph(const std::shared_ptr<Graph> &graph) { graph_ = graph; }
    virtual void set_goal_nodes(const std::set<Node> & /*goal_nodes*/) {}

private:
    ActorId actor_id_;
    std::shared_ptr<Graph> graph_;
    boost::random::mt19937 gen_;
};

#endif // RANDOMER_BRAIN_HPP
