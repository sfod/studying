#ifndef EVENT_DATA_HPP
#define EVENT_DATA_HPP

#include "actors/actor.hpp"

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
    EventData_MainMenu() : EventData() {}
    virtual ~EventData_MainMenu() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;
};

class EventData_NewGame : public EventData {
public:
    EventData_NewGame() : EventData() {}
    virtual ~EventData_NewGame() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;
};

class EventData_Quit : public EventData {
public:
    EventData_Quit() : EventData() {}
    virtual ~EventData_Quit() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;
};

class EventData_NewActor : public EventData {
public:
    explicit EventData_NewActor(ActorId id) : EventData(), id_(id) {}
    virtual ~EventData_NewActor() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;

    ActorId id() const { return id_; }

private:
    ActorId id_;
};

class EventData_MoveActor : public EventData {
public:
    EventData_MoveActor(ActorId id, const std::pair<int, int> &pos) : EventData(), id_(id), pos_(pos) {}
    virtual ~EventData_MoveActor() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;

    ActorId id() const { return id_; }
    std::pair<int, int> pos() const { return pos_; }

private:
    ActorId id_;
    std::pair<int, int> pos_;
};

#endif // EVENT_DATA_HPP
