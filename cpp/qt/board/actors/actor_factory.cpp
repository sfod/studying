#include "actor_factory.hpp"
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "physics_component.hpp"

static ActorId g_actor_id = 0;

ActorFactory::ActorFactory()
{
}

std::shared_ptr<Actor> ActorFactory::create_actor(const char *resource)
{
    boost_pt::ptree pt;
    boost_pt::read_json(resource, pt);  // @todo handle exception

    boost::optional<boost_pt::ptree &> actor_data = pt.get_child_optional("actor");
    if (!actor_data) {
        return std::shared_ptr<Actor>();
    }

    std::shared_ptr<Actor> actor(new Actor(++g_actor_id));
    if (!actor->init(*actor_data)) {
        return std::shared_ptr<Actor>();
    }

    boost::optional<boost_pt::ptree &> actor_components =
            pt.get_child_optional("actor.components");
    if (actor_components) {
        for (auto component_data : *actor_components) {
            std::shared_ptr<ActorComponent> component =
                    create_actor_component(component_data.first, component_data.second);
            if (component) {
                actor->add_component(component);
                component->set_owner(actor);
            }
        }
    }

    return actor;
}

std::shared_ptr<ActorComponent> ActorFactory::create_actor_component(
        const std::string &type, const boost_pt::ptree &component_data)
{
    if (type == "PhysicsComponent") {
        std::shared_ptr<ActorComponent> component(new PhysicsComponent);
        if (!component->init(component_data)) {
            return std::shared_ptr<ActorComponent>();
        }
        return component;
    }
    else {
        return std::shared_ptr<ActorComponent>();
    }
}
