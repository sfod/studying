#include "graph_component.hpp"

const char *GraphComponent::name_ = "GraphComponent";

GraphComponent::GraphComponent()
{
}

GraphComponent::~GraphComponent()
{
}

bool GraphComponent::init(const boost::property_tree::ptree &component_data)
{
    boost::optional<const boost_pt::ptree &> pos =
            component_data.get_child_optional("position");
    if (pos && ((*pos).size() == 2)) {
        auto it = (*pos).begin();
        pos_.first = it->second.get_value<int>();
        pos_.second = (++it)->second.get_value<int>();
    }
    return true;
}
