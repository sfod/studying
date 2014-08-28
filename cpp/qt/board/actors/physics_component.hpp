#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "actor_component.hpp"

class PhysicsComponent : public ActorComponent
{
public:
    PhysicsComponent();
    ~PhysicsComponent();

    virtual bool init(const boost_pt::ptree &component_data) override;
    virtual const char *name() const override { return name_; }

private:
    static const char *name_;

private:
    unsigned char pos_[2];
    unsigned char color_[3];
};

#endif // PHYSICS_COMPONENT_HPP
