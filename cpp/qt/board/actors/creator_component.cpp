#include "creator_component.hpp"

const char *CreatorComponent::name_ = "CreatorComponent";

CreatorComponent::CreatorComponent()
{
}

CreatorComponent::~CreatorComponent()
{
}

bool CreatorComponent::init(const boost_pt::ptree &component_data)
{
    return true;
}
