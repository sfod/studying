#include "actor.hpp"
#include <QDebug>

Actor::Actor(ActorId actor_id)
    : component_list_(), actor_id_(actor_id), type_()
{
}

Actor::~Actor()
{
}

bool Actor::init(const boost_pt::ptree &actor_data)
{
    type_ = actor_data.get<std::string>("type", "");
    if (type_ == "") {
        return false;
    }

    qDebug() << "actor type: " << type_.c_str();

    return true;
}

void Actor::add_component(std::shared_ptr<ActorComponent> &component)
{
    qDebug() << "adding component" << component->id();
    component_list_[component->id()] = component;
}
