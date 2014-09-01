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
    explicit EventData_NewActor(const unsigned char pos[2]) : EventData() {pos_[0] = pos[0]; pos_[1] = pos[1]; }
    virtual ~EventData_NewActor() {}
    virtual const EventType &event_type() const { return event_type_; }
    static const EventType event_type_;

    const unsigned char *pos() const { return pos_; }

private:
    unsigned char pos_[2];
};

#endif // EVENT_DATA_HPP
