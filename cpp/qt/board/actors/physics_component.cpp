#include "physics_component.hpp"
#include <QDebug>

const char *PhysicsComponent::name_ = "PhysicsComponent";

PhysicsComponent::PhysicsComponent()
{
    memset(pos_, 0, sizeof(pos_));
    memset(color_, 0, sizeof(color_));
}

PhysicsComponent::~PhysicsComponent()
{
}

// @fixme refactor
bool PhysicsComponent::init(const boost_pt::ptree &component_data)
{
    boost::optional<const boost_pt::ptree &> pos = component_data.get_child_optional("position");
    if (pos) {
        int i = 0;
        for (auto c : *pos) {
            if (i > 1) {
                break;
            }
            pos_[i] = c.second.get_value<unsigned char>();
            qDebug() << "pos:" << pos_[i];
            ++i;
        }
    }

    boost::optional<const boost_pt::ptree &> color = component_data.get_child_optional("color");
    if (color) {
        int i = 0;
        for (auto c : *color) {
            if (i > 2) {
                break;
            }
            color_[i] = c.second.get_value<unsigned char>();
            qDebug() << "color:" << color_[i];
        }
    }

    return true;
}
