#ifndef GRAPH_COMPONENT_HPP
#define GRAPH_COMPONENT_HPP

#include <utility>
#include "actor_component.hpp"

class GraphComponent : public ActorComponent
{
public:
    GraphComponent();
    virtual ~GraphComponent();

    virtual bool init(const boost_pt::ptree &component_data) override;
    virtual const char *name() const override { return name_; }

    std::pair<int, int> pos() const { return pos_; }
    std::list<std::pair<int, int>> possible_moves() const { return possible_moves_; }

public:
    static const char *name_;

private:
    std::pair<int, int> pos_;
    std::list<std::pair<int, int>> possible_moves_;
};

#endif // GRAPH_COMPONENT_HPP
