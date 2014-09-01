#include "player_view.hpp"
#include <QQuickItem>
#include <QDebug>

PlayerView::PlayerView(QObject *qroot, QObject *qparent)
    : QObject(qparent), IView(), qroot_(qroot), qboard_(), qbutton_()
{
}

PlayerView::~PlayerView()
{
    qDebug() << "destroying PlayerView";
}

bool PlayerView::init()
{
    qboard_ = qroot_->findChild<QObject*>("game");
    if (qboard_ == NULL) {
        qDebug() << "cannot find board element";
        return false;
    }
    QObject::connect(
                qboard_, SIGNAL(nodeClicked(int)),
                this, SLOT(node_clicked(int))
    );

    qbutton_ = qroot_->findChild<QObject*>("buttonBackToMainMenu");
    if (qbutton_ == NULL) {
        qDebug() << "cannot find buttonBackToMainMenu element";
        return false;
    }
    QObject::connect(
                qbutton_, SIGNAL(clicked()),
                this, SLOT(button_back_clicked())
    );

    EventManager::get()->add_listener(
            boost::bind(&PlayerView::new_actor_delegate, this, _1),
            EventData_NewActor::event_type_);

    return true;
}

void PlayerView::on_msg()
{
}

void PlayerView::on_update()
{
}

void PlayerView::new_actor_delegate(const std::shared_ptr<EventData> &event)
{
    std::shared_ptr<EventData_NewActor> ev = std::dynamic_pointer_cast<EventData_NewActor>(event);
    const unsigned char *pos = ev->pos();
    qDebug() << "PlayerView New Actor delegate called: set actor on" << pos[0] << ":" << pos[1];
}

void PlayerView::node_clicked(int idx)
{
    qDebug() << "node " << idx << " clicked";
}

void PlayerView::button_back_clicked()
{
    qDebug() << "back button clicked";
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_MainMenu))) {
        qDebug() << "failed to queue MainMenu event";
    }
}
