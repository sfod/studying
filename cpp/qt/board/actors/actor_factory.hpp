#ifndef ACTOR_FACTORY_HPP
#define ACTOR_FACTORY_HPP

#include <memory>
#include "actor.hpp"

class ActorFactory
{
public:
    ActorFactory();
    ~ActorFactory();

    std::shared_ptr<Actor> create_actor(const char *resource);
    std::shared_ptr<ActorComponent> create_actor_component(
            const std::string &type, const boost_pt::ptree &component_data);
};

#endif // ACTOR_FACTORY_HPP
