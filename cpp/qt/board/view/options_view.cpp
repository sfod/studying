#include "options_view.hpp"
#include <QDebug>
#include "events/event_data.hpp"
#include "events/event_manager.hpp"

OptionsView::OptionsView(QObject *qroot, QObject *qparent)
    : QObject(qparent), IView(), qroot_(qroot), object_list_()
{
}

OptionsView::~OptionsView()
{
    qDebug() << "destroying OptionsView";
}

bool OptionsView::init()
{
    QObject *qbutton = qroot_->findChild<QObject*>("buttonStartGame");
    if (qbutton == NULL) {
        qDebug() << "cannot find buttonStartGame element";
        return false;
    }
    QObject::connect(
            qbutton, SIGNAL(clicked()),
            this, SLOT(button_start_game_clicked())
    );
    object_list_.push_back(qbutton);

    qbutton = qroot_->findChild<QObject*>("buttonBackToMainMenu");
    if (qbutton == NULL) {
        qDebug() << "cannot find buttonBackToMainMenu element";
        return false;
    }
    QObject::connect(
            qbutton, SIGNAL(clicked()),
            this, SLOT(button_back_clicked())
    );
    object_list_.push_back(qbutton);

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
