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


class EventData_Options : public EventData {
public:
    EventData_Options();
    virtual ~EventData_Options();
    virtual const EventType &event_type() const;
    static const EventType event_type_;
};


class EventData_Game : public EventData {
public:
    EventData_Game();
    virtual ~EventData_Game();
    virtual const EventType &event_type() const;
    static const EventType event_type_;
};


class EventData_GameEnd : public EventData {
public:
    EventData_GameEnd();
    virtual ~EventData_GameEnd();
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


class EventData_RequestNewActor : public EventData {
public:
    EventData_RequestNewActor();
    virtual ~EventData_RequestNewActor();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

private:
};


class EventData_NewActor : public EventData {
public:
    explicit EventData_NewActor(ActorId actor_id);
    virtual ~EventData_NewActor();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId actor_id() const { return actor_id_; }

private:
    ActorId actor_id_;
};


class EventData_RequestActorMove : public EventData {
public:
    EventData_RequestActorMove(ActorId actor_id, const Node &node);
    virtual ~EventData_RequestActorMove();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId actor_id() const { return actor_id_; }
    Node node() const { return node_; }

private:
    ActorId actor_id_;
    Node node_;
};


class EventData_MoveActor : public EventData {
public:
    EventData_MoveActor(ActorId actor_id, const Node &node,
            const std::list<Node> &possible_moves);
    virtual ~EventData_MoveActor();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId actor_id() const { return actor_id_; }
    Node node() const { return node_; }
    const std::list<Node> &possible_moves() const { return possible_moves_; }

private:
    ActorId actor_id_;
    Node node_;
    std::list<Node> possible_moves_;
};

class EventData_SetActorActive : public EventData {
public:
    EventData_SetActorActive(ActorId actor_id, bool av);
    virtual ~EventData_SetActorActive();
    virtual const EventType &event_type() const;
    static const EventType event_type_;

    ActorId actor_id() const { return actor_id_; }
    bool active() const { return active_; }

private:
    ActorId actor_id_;
    bool active_;
};

#endif // EVENT_DATA_HPP
