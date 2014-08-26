#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <map>
#include <memory>
#include <QXmlStreamAttributes>
#include "actor_component.hpp"

typedef unsigned long ActorId;

class Actor {
public:
    explicit Actor(ActorId actor_id);
    ~Actor();

    bool init(const QXmlStreamAttributes &attrs);

    ActorId actor_id() const { return actor_id_; }

private:
    std::map<ComponentId, std::shared_ptr<ActorComponent>> component_list_;
    ActorId actor_id_;
};

#endif // ACTOR_HPP
