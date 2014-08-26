#include "actor.hpp"
#include <QDebug>

Actor::Actor(ActorId actor_id) : actor_id_(actor_id)
{
}

Actor::~Actor()
{
}

bool Actor::init(const QXmlStreamAttributes &attrs)
{
    if (!attrs.hasAttribute("", "type")) {
        return false;
    }

    qDebug() << "actor type: " << attrs.value("type");

    return true;
}
