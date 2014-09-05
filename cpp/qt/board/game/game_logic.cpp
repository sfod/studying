#include "game_logic.hpp"
#include <QDebug>
#include <boost/bind.hpp>

#include "events/event_manager.hpp"
#include "events/event_data.hpp"
#include "view/main_menu_view.hpp"
#include "view/player_view.hpp"
#include "actors/physics_component.hpp"

GameLogic::GameLogic(QObject *qroot)
    : state_(LogicState::LS_Uninitialized), qroot_(qroot),
    actor_factory_(new ActorFactory), actor_keeper_(new ActorKeeper),
    view_list_()
{
}

void GameLogic::change_state(LogicState state)
{
    std::shared_ptr<IView> view;

    switch (state) {
    case LogicState::LS_Uninitialized:
        break;
    case LogicState::LS_MainMenu:
        view.reset(new MainMenuView(qroot_));
        view->init();
        change_view(view);
        break;
    case LogicState::LS_Game: {
        view.reset(new PlayerView(qroot_));
        view->init();

        std::shared_ptr<Actor> actor = actor_factory_->create_actor("../board/data/player.json");
        if (actor) {
            std::shared_ptr<PhysicsComponent> ph_comp(new PhysicsComponent);
            ph_comp = std::static_pointer_cast<PhysicsComponent>(actor->component(ph_comp->id()));
            if (ph_comp) {
                EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_NewActor(actor->id(), ph_comp->pos())));
                qDebug() << "created actor (id" << actor->id() << ")";
            }
            else {
                qDebug() << "";
            }
        }

        change_view(view);
        break;
    }
    case LogicState::LS_Invalid:
        break;
    default:
        break;
    }
}

void GameLogic::add_view(std::shared_ptr<IView> view)
{
    view_list_.push_back(view);
}

void GameLogic::change_view(std::shared_ptr<IView> view)
{
    if (!view_list_.empty()) {
        view_list_.pop_back();
    }
    view_list_.push_back(view);
}
