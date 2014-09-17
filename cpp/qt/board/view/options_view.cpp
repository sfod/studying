#include "options_view.hpp"
#include <QDebug>
#include "events/event_data.hpp"
#include "events/event_manager.hpp"

OptionsView::OptionsView(QObject *qroot, QObject *qparent)
    : QtView(qparent), qroot_(qroot), qoptions_()
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
