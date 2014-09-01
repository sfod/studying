#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <map>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include "actor_component.hpp"

namespace boost_pt = boost::property_tree;
typedef unsigned long ActorId;

class Actor {
public:
    explicit Actor(ActorId id);
    ~Actor();

    bool init(const boost_pt::ptree &actor_data);
    void add_component(std::shared_ptr<ActorComponent> &component);

    ActorId id() const { return id_; }

private:
    std::map<ComponentId, std::shared_ptr<ActorComponent>> component_list_;
    ActorId id_;
    std::string type_;
};

#endif // ACTOR_HPP
