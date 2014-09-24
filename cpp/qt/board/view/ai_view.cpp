#include "ai_view.hpp"
#include "game/game_app.hpp"
#include "actors/ai_component.hpp"

AIView::AIView() : conn_list_(), actor_id_(-1)
{
}

AIView::~AIView()
{
    for (auto conn : conn_list_) {
        conn.disconnect();
    }
}

bool AIView::init()
{
    bs2::connection conn;
    conn = EventManager::get()->add_listener(
            boost::bind(&AIView::set_active_delegate, this, _1),
            EventData_SetActorActive::event_type_);
    conn_list_.push_back(conn);

    return true;
}

void AIView::on_msg()
{
}

void AIView::on_update()
{
}

void AIView::attach(ActorId actor_id)
{
    actor_id_ = actor_id;
}

void AIView::set_active_delegate(const std::shared_ptr<EventData> &event)
{
    auto active_event = std::dynamic_pointer_cast<EventData_SetActorActive>(event);
    if ((active_event->actor_id() == actor_id_) && (active_event->active())) {
        // @fixme remove actor_keeper from chain
        const std::shared_ptr<Actor> &actor =
                GameApp::get()->game_logic()->actor_keeper()->actor(active_event->actor_id());
        ComponentId cid = ActorComponent::id(AIComponent::name_);
        auto ai_comp = std::dynamic_pointer_cast<AIComponent>(actor->component(cid));
        if (ai_comp) {
            ai_comp->make_move();
        }
    }
}
