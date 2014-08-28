#ifndef ACTOR_COMPONENT_HPP
#define ACTOR_COMPONENT_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/functional/hash.hpp>

namespace boost_pt = boost::property_tree;
typedef unsigned long ComponentId;

class ActorComponent {
public:
    ActorComponent();
    virtual bool init(const boost_pt::ptree &component_data) = 0;
    virtual const char *name() const = 0;

    virtual ComponentId id() const {
        boost::hash<std::string> hash;
        return hash(name());
    }
};

#endif // ACTOR_COMPONENT_HPP
