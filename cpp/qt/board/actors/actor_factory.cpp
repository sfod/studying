#include "actor_factory.hpp"

static ActorId g_actor_id = 0;

ActorFactory::ActorFactory()
{
}

// @todo init actor from resource
std::shared_ptr<Actor> ActorFactory::create_actor(const char *resource)
{
    (void) resource;

    std::shared_ptr<Actor> actor(new Actor(++g_actor_id));
    return actor;
}
