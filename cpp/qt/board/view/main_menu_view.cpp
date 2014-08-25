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
    qDebug() << "New Game button clicked";
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_NewGame))) {
        qDebug() << "failed to queue NewGame event";
    }
}

void MainMenuView::button_quit_clicked()
{
    qDebug() << "Quit button clicked";
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_Quit))) {
        qDebug() << "failed to queue Quit event";
    }

}
