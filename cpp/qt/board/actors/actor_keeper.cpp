#include "actor_keeper.hpp"

ActorKeeper::ActorKeeper() : actor_id_list_()
{
}

ActorKeeper::~ActorKeeper()
{
}

void ActorKeeper::add_actor(std::shared_ptr<Actor> &actor)
{
    if (actor_id_list_.count(actor->id()) == 0) {
        actor_id_list_[actor->id()] = actor;
    }
}

std::shared_ptr<Actor> ActorKeeper::actor(ActorId id) const
{
    if (actor_id_list_.count(id) != 0) {
        return actor_id_list_.at(id);
    }
    return std::shared_ptr<Actor>();
}
