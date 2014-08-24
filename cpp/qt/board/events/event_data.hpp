#ifndef EVENT_DATA_HPP
#define EVENT_DATA_HPP

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

class EventData_NewGame : public EventData {
public:
    EventData_NewGame() : EventData() {}
    virtual ~EventData_NewGame() {}

    virtual const EventType &event_type() const { return event_type_; }

    static const EventType event_type_;
};

#endif // EVENT_DATA_HPP
