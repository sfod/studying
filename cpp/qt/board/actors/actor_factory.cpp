#include "actor_factory.hpp"
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

static ActorId g_actor_id = 0;

ActorFactory::ActorFactory()
{
}

std::shared_ptr<Actor> ActorFactory::create_actor(const char *resource)
{
    boost_pt::ptree pt;
    boost_pt::read_json(resource, pt);

    boost::optional<boost_pt::ptree &> actor_data = pt.get_child_optional("actor");
    if (!actor_data) {
        return std::shared_ptr<Actor>();
    }

    std::shared_ptr<Actor> actor(new Actor(++g_actor_id));
    if (!actor->init(*actor_data)) {
        return std::shared_ptr<Actor>();
    }

    boost::optional<boost_pt::ptree &> actor_components = pt.get_child_optional("actor.components");
    if (actor_components) {
        for (auto component : *actor_components) {
            qDebug() << "\tcomponent type:" << component.first.c_str();
        }
    }

    return actor;
}
