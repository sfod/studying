#ifndef PLAYER_VIEW_HPP
#define PLAYER_VIEW_HPP

#include <QObject>
#include "iview.hpp"
#include "events/event_manager.hpp"

class PlayerView : public QObject, public IView
{
    Q_OBJECT

public:
    explicit PlayerView(QObject *qroot, QObject *qparent = 0);
    virtual ~PlayerView();

    bool init();
    virtual void on_msg();
    virtual void on_update();

    void new_actor_delegate(const std::shared_ptr<EventData> &event);

public slots:
    void on_pawn_dropped(int idx);
    void button_back_clicked();

private:
    std::list<bs2::connection> conn_list_;
    QObject *qroot_;
    QObject *qboard_;
    QObject *qbutton_;
};

#endif // PLAYER_VIEW_HPP
