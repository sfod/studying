#include "main_menu_view.hpp"
#include <QDebug>
#include "events/event_data.hpp"
#include "events/event_manager.hpp"

MainMenuView::MainMenuView(QObject *qroot, QObject *qparent)
    : QObject(qparent), IView(), qroot_(qroot), object_list_()
{
}

MainMenuView::~MainMenuView()
{
    qDebug() << "destroying MainMenuView";
}

bool MainMenuView::init()
{
    QObject *qbutton = qroot_->findChild<QObject*>("buttonNewGame");
    if (qbutton == NULL) {
        qDebug() << "cannot find buttonNewGame element";
        return false;
    }
    QObject::connect(
                qbutton, SIGNAL(clicked()),
                this, SLOT(button_new_game_clicked())
    );
    object_list_.push_back(qbutton);

    qbutton = qroot_->findChild<QObject*>("buttonQuit");
    if (qbutton == NULL) {
        qDebug() << "cannot find buttonQuit element";
        return false;
    }
    QObject::connect(
                qbutton, SIGNAL(clicked()),
                this, SLOT(button_quit_clicked())
    );
    object_list_.push_back(qbutton);

    return true;
}

void MainMenuView::on_msg()
{
}

void MainMenuView::on_update()
{
}

void MainMenuView::button_new_game_clicked()
{
    auto event = std::make_shared<EventData_Options>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue Options event";
    }
}

void MainMenuView::button_quit_clicked()
{
    auto event = std::make_shared<EventData_Quit>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue Quit event";
    }

}
