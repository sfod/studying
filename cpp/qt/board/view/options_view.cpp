#include "options_view.hpp"
#include <QDebug>
#include "events/event_data.hpp"
#include "events/event_manager.hpp"

OptionsView::OptionsView(QObject *qroot, QObject *qparent)
    : QtView(qparent), qroot_(qroot), qoptions_(), actor_id_(-1)
{
}

OptionsView::~OptionsView()
{
    qDebug() << "destroying OptionsView";
}

bool OptionsView::init()
{
    if (!connect_options()) {
        return false;
    }

    QVariantList player_types;
    // @fixme get list of player types from JSON file
    player_types << "human" << "AI";
    QMetaObject::invokeMethod(qoptions_, "setPlayerTypes",
            Q_ARG(QVariant, QVariant::fromValue(player_types)));

    QMetaObject::invokeMethod(qoptions_, "setPlayerNum", Q_ARG(QVariant, 2));

    if (!connect_button("buttonStartGame", SLOT(button_start_game_clicked()))) {
        return false;
    }
    if (!connect_button("buttonBackToMainMenu", SLOT(button_back_clicked()))) {
        return false;
    }

    return true;
}

void OptionsView::on_msg()
{
}

void OptionsView::on_update()
{
}

void OptionsView::attach(ActorId actor_id)
{
    actor_id_ = actor_id;
}

void OptionsView::button_start_game_clicked()
{
    qDebug() << "button_start_game_clicked";

    send_new_actors_data();

    auto event = std::make_shared<EventData_Game>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue Game event";
    }
}

void OptionsView::button_back_clicked()
{
    qDebug() << "button_back_clicked";
    auto event = std::make_shared<EventData_MainMenu>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue MainMenu event";
    }
}

QObject *OptionsView::find_object_by_name(const char *name) const
{
    return qroot_->findChild<QObject*>(name);
}

bool OptionsView::connect_options()
{
    qoptions_ = find_object_by_name("options");
    return (qoptions_ != NULL);
}

void OptionsView::send_new_actors_data() const
{
    auto ev1 = std::make_shared<EventData_RequestNewActor>();
    EventManager::get()->queue_event(ev1);
    auto ev2 = std::make_shared<EventData_RequestNewActor>();
    EventManager::get()->queue_event(ev2);
}
