#ifndef EVENT_DATA_HPP
#define EVENT_DATA_HPP

#include "actors/actor.hpp"
#include "graph/node.hpp"

typedef unsigned long EventType;

class EventData {
public:
    explicit EventData(float ts = 0) : ts_(ts) {}
    virtual ~EventData() {}
    virtual const EventType &event_type() const = 0;
    virtual float ts() const { return ts_; }

private:
    float ts_;
};


class EventData_MainMenu : public EventData {
public:
    EventData_MainMenu();
    virtual ~EventData_MainMenu();
    virtual const EventType &event_type() const;
    static const EventType event_type_;
};


class EventData_NewGame : public EventData {
public:
    EventData_NewGame();
    virtual ~EventData_NewGame();
    virtual const EventType &event_type() const;
    static const EventType event_type_;
};


class EventData_Quit : public EventData {
public:
    EventData_Quit();
    virtual ~EventData_Quit();
    virtual const EventType &event_type() const;
    static const EventType event_type_;
};


class EventData_NewActor : public EventData {
public:
    explicit EventData_NewActor(ActorId id);
    virtual ~EventData_NewActor();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId id() const { return id_; }

private:
    ActorId id_;
};


class EventData_RequestActorMove : public EventData {
public:
    EventData_RequestActorMove(ActorId id, const Node &node);
    virtual ~EventData_RequestActorMove();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId id() const { return id_; }
    Node node() const { return node_; }

private:
    ActorId id_;
    Node node_;
};


class EventData_MoveActor : public EventData {
public:
    EventData_MoveActor(ActorId id, const Node &node,
            const std::list<Node> &possible_moves);
    virtual ~EventData_MoveActor();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId id() const { return id_; }
    Node node() const { return node_; }
    const std::list<Node> &possible_moves() const { return possible_moves_; }

private:
    ActorId id_;
    Node node_;
    std::list<Node> possible_moves_;
};

#endif // EVENT_DATA_HPP
