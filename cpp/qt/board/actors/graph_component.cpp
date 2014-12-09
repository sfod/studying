#include <QObject>  // include it first to avoid error with boost::Q_FOREACH
#include "graph_component.hpp"
#include "game/game_app.hpp"

const char *GraphComponent::name_ = "GraphComponent";

GraphComponent::GraphComponent() : node_(), possible_moves_()
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
        node_.set_row(it->second.get_value<int>());
        node_.set_col((++it)->second.get_value<int>());
    }
    return true;
}

void GraphComponent::post_init()
{
    const std::shared_ptr<Actor> &actor = owner();
    if (actor) {
        graph_->add_actor(actor->id());
        move_actor(node_);
    }
}

bool GraphComponent::move_actor(const Node &pos)
{
    bool res = graph_->move_actor(owner()->id(), pos);
    if (res) {
        node_ = pos;
        possible_moves_ = graph_->possible_moves(owner()->id());
    }
    return res;
}

std::list<Node> GraphComponent::possible_moves() const
{
    return possible_moves_;
}
