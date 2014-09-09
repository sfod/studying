#include "graph_component.hpp"
#include "game/game_app.hpp"

const char *GraphComponent::name_ = "GraphComponent";

GraphComponent::GraphComponent() : pos_(), possible_moves_()
{
    graph_ = GameApp::get()->game_logic()->graph();
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

void GraphComponent::post_init()
{
    const std::shared_ptr<Actor> &actor = owner();
    if (actor) {
        graph_->add_actor(actor->id(), pos_);
    }
}
