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
    explicit Actor(ActorId actor_id);
    ~Actor();

    bool init(const boost_pt::ptree &actor_data);

    ActorId actor_id() const { return actor_id_; }

private:
    std::map<ComponentId, std::shared_ptr<ActorComponent>> component_list_;
    ActorId actor_id_;
    std::string type_;
};

#endif // ACTOR_HPP
