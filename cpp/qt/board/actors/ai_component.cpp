#include <QObject>  // include it to avoid error with boost::Q_FOREACH
#include "ai_component.hpp"
#include "game/game_app.hpp"
#include "graph_component.hpp"
#include "AI/randomer_brain.hpp"

const char *AIComponent::name_ = "AIComponent";

AIComponent::AIComponent() : brain_()
{
}

AIComponent::~AIComponent()
{
}

bool AIComponent::init(const boost::property_tree::ptree &component_data)
{
    boost::optional<const boost_pt::ptree &> brain_type =
            component_data.get_child_optional("brain");
    if (brain_type) {
        brain_ = std::make_shared<RandomerBrain>();
        return true;
    }
    return false;
}

void AIComponent::post_init()
{
    brain_->set_graph(GameApp::get()->game_logic()->graph());
    brain_->set_actor_id(owner()->id());

    auto cid = GraphComponent::id(GraphComponent::name_);
    auto graph_comp = std::dynamic_pointer_cast<GraphComponent>(owner()->component(cid));
    brain_->set_goal_nodes(graph_comp->goal_nodes());
}

void AIComponent::make_move()
{
    brain_->make_move();
}
