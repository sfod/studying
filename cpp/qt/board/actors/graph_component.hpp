#ifndef GRAPH_COMPONENT_HPP
#define GRAPH_COMPONENT_HPP

#include <utility>
#include "actor_component.hpp"
#include "graph/graph.hpp"

class GraphComponent : public ActorComponent
{
public:
    GraphComponent();
    virtual ~GraphComponent();

    virtual bool init(const boost_pt::ptree &component_data) override;
    virtual void post_init() override;
    virtual const char *name() const override { return name_; }

    bool move_actor(const std::pair<int, int> &pos);

    std::pair<int, int> pos() const { return pos_; }
    std::list<std::pair<int, int>> possible_moves() const;

public:
    static const char *name_;

private:
    std::shared_ptr<Graph> graph_;
    std::pair<int, int> pos_;
    std::list<std::pair<int, int>> possible_moves_;
};

#endif // GRAPH_COMPONENT_HPP
