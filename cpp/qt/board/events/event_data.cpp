#include "event_data.hpp"

const EventType EventData_MainMenu::event_type_(1011);
const EventType EventData_NewGame::event_type_(1012);
const EventType EventData_Quit::event_type_(1013);
const EventType EventData_NewActor::event_type_(1014);
const EventType EventData_RequestActorMove::event_type_(1015);
const EventType EventData_MoveActor::event_type_(1016);


EventData_MainMenu::EventData_MainMenu() : EventData()
{
}

EventData_MainMenu::~EventData_MainMenu()
{
}

const EventType &EventData_MainMenu::event_type() const
{
    return event_type_;
}


EventData_NewGame::EventData_NewGame() : EventData()
{
}

EventData_NewGame::~EventData_NewGame()
{
}

const EventType &EventData_NewGame::event_type() const
{
    return event_type_;
}


EventData_Quit::EventData_Quit() : EventData()
{
}

EventData_Quit::~EventData_Quit()
{
}

const EventType &EventData_Quit::event_type() const
{
    return event_type_;
}


EventData_NewActor::EventData_NewActor(ActorId id) : EventData(), id_(id)
{
}

EventData_NewActor::~EventData_NewActor()
{
}

const EventType &EventData_NewActor::event_type() const
{
    return event_type_;
}


EventData_RequestActorMove::EventData_RequestActorMove(ActorId id,
        const std::pair<int, int> &pos)
    : EventData(), id_(id), pos_(pos)
{
}

EventData_RequestActorMove::~EventData_RequestActorMove()
{
}

const EventType &EventData_RequestActorMove::event_type() const
{
    return event_type_;
}


EventData_MoveActor::EventData_MoveActor(ActorId id,
        const std::pair<int, int> &pos,
        const std::list<std::pair<int, int> > &possible_moves)
    : id_(id), pos_(pos), possible_moves_(possible_moves)
{
}

EventData_MoveActor::~EventData_MoveActor()
{
}

const EventType &EventData_MoveActor::event_type() const
{
    return event_type_;
}
