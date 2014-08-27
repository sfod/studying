#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "actor_component.hpp"

class PhysicsComponent : public ActorComponent
{
public:
    PhysicsComponent();
    ~PhysicsComponent();

    bool init(const boost_pt::ptree &component_data);

private:
    unsigned char pos_[2];
    unsigned char color_[3];
};

#endif // PHYSICS_COMPONENT_HPP
