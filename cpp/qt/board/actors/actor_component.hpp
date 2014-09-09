#ifndef ACTOR_COMPONENT_HPP
#define ACTOR_COMPONENT_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/functional/hash.hpp>

namespace boost_pt = boost::property_tree;
typedef unsigned long ComponentId;


class Actor;

class ActorComponent {
public:
    virtual ~ActorComponent() {}

    virtual bool init(const boost_pt::ptree &component_data) = 0;
    virtual void post_init() {}
    virtual const char *name() const = 0;
    virtual void set_owner(std::shared_ptr<Actor> &owner) { owner_ = owner; }

    virtual ComponentId id() const {
        boost::hash<std::string> hash;
        return hash(name());
    }

private:
    std::shared_ptr<Actor> owner_;
};

#endif // ACTOR_COMPONENT_HPP
