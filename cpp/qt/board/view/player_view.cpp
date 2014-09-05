#include "player_view.hpp"
#include <QQuickItem>
#include <QDebug>

PlayerView::PlayerView(QObject *qroot, QObject *qparent)
    : QObject(qparent), IView(), conn_list_(),
      qroot_(qroot), qboard_(), qbutton_()
{
}

PlayerView::~PlayerView()
{
    qDebug() << "destroying PlayerView";
    for (auto conn : conn_list_) {
        conn.disconnect();
    }
}

bool PlayerView::init()
{
    qboard_ = qroot_->findChild<QObject*>("board");
    if (qboard_ == NULL) {
        qDebug() << "cannot find board element";
        return false;
    }
    QObject::connect(
                qboard_, SIGNAL(pawnDropped(int)),
                this, SLOT(on_pawn_dropped(int))
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

    bs2::connection conn;
    conn = EventManager::get()->add_listener(
            boost::bind(&PlayerView::new_actor_delegate, this, _1),
            EventData_NewActor::event_type_);
    conn_list_.push_back(conn);

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

    int idx = (8 - pos[0]) * 9 + pos[1];
    QMetaObject::invokeMethod(qboard_, "addPawn", Q_ARG(QVariant, idx));
}

void PlayerView::on_pawn_dropped(int idx)
{
    qDebug() << "pawn dropped on" << idx;
}

void PlayerView::button_back_clicked()
{
    qDebug() << "back button clicked";
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_MainMenu))) {
        qDebug() << "failed to queue MainMenu event";
    }
}
