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
                qboard_, SIGNAL(pawnDropped(int, int)),
                this, SLOT(on_pawn_dropped(int, int))
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

    conn = EventManager::get()->add_listener(
            boost::bind(&PlayerView::move_actor_delegate, this, _1),
            EventData_MoveActor::event_type_);
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
    std::shared_ptr<EventData_NewActor> ev =
            std::dynamic_pointer_cast<EventData_NewActor>(event);
    QMetaObject::invokeMethod(qboard_, "addPawn",
            Q_ARG(QVariant, static_cast<int>(ev->id())));
}

void PlayerView::move_actor_delegate(const std::shared_ptr<EventData> &event)
{
    std::shared_ptr<EventData_MoveActor> move_event =
            std::dynamic_pointer_cast<EventData_MoveActor>(event);

    const Node &node = move_event->node();
    int idx = (8 - node.row()) * 9 + node.col();

    QVariantList possible_idx_list;
    for (auto &node : move_event->possible_moves()) {
        int idx = (8 - node.row()) * 9 + node.col();
        possible_idx_list << idx;
    }

    QMetaObject::invokeMethod(qboard_, "setPawnPos",
            Q_ARG(QVariant, static_cast<int>(move_event->id())),
            Q_ARG(QVariant, idx),
            Q_ARG(QVariant, QVariant::fromValue(possible_idx_list)));
}

void PlayerView::on_pawn_dropped(int id, int idx)
{
    Node node;
    node.set_row(8 - idx / 9);
    node.set_col(idx % 9);
    qDebug() << "pawn" << id << "dropped on" << node.row() << ":" << node.col();
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_RequestActorMove(id, node)))) {
        qDebug() << "failed to queue MoveActor event";
    }
}

void PlayerView::button_back_clicked()
{
    qDebug() << "back button clicked";
    if (!EventManager::get()->queue_event(std::shared_ptr<EventData>(new EventData_MainMenu))) {
        qDebug() << "failed to queue MainMenu event";
    }
}
