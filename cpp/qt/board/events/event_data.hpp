#ifndef EVENT_DATA_HPP
#define EVENT_DATA_HPP

class EventData {
public:
    explicit EventData(float ts = 0) : ts_(ts) {}
    virtual ~EventData() {}

    virtual float ts() const { return ts_; }

private:
    float ts_;
};

class EventData_NewGame : public EventData {
public:
    EventData_NewGame() {}
    virtual ~EventData_NewGame() {}
};

#endif // EVENT_DATA_HPP
