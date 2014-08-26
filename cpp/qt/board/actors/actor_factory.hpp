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
};

#endif // ACTOR_FACTORY_HPP
