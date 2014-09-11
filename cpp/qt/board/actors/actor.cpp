#include "actor.hpp"
#include <QDebug>

Actor::Actor(ActorId id) : component_list_(), id_(id), type_()
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

void Actor::post_init()
{
    for (auto component : component_list_) {
        component.second->post_init();
    }
}

void Actor::add_component(std::shared_ptr<ActorComponent> &component)
{
    component_list_[component->id()] = component;
}

std::shared_ptr<ActorComponent> Actor::component(ComponentId id) const
{
    if (component_list_.count(id) > 0) {
        return component_list_.at(id);
    }
    return std::shared_ptr<ActorComponent>();
}
