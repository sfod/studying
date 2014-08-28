#ifndef CREATOR_COMPONENT_HPP
#define CREATOR_COMPONENT_HPP

#include "actor_component.hpp"

class CreatorComponent : public ActorComponent
{
public:
    CreatorComponent();
    virtual ~CreatorComponent();

    virtual bool init(const boost_pt::ptree &component_data) override;
    virtual const char *name() const override { return name_; }

private:
    static const char *name_;
};

#endif // CREATOR_COMPONENT_HPP
