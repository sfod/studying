#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <map>
#include <memory>
#include "actor_component.hpp"

class Actor {
    typedef unsigned long ActorId;

public:
    explicit Actor(ActorId actor_id);
    ~Actor();

    ActorId actor_id() const { return actor_id_; }

private:
    std::map<ComponentId, std::shared_ptr<ActorComponent>> component_list_;
    ActorId actor_id_;
};

#endif // ACTOR_HPP
