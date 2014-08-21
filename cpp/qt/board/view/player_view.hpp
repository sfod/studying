#ifndef PLAYER_VIEW_HPP
#define PLAYER_VIEW_HPP

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>

#include "iview.hpp"

class PlayerView : public QObject, public IView
{
    Q_OBJECT

public:
    explicit PlayerView(QObject *parent = 0);
    ~PlayerView();

    bool init();
    virtual void on_msg();
    virtual void on_update();

public slots:
    void node_clicked(int idx);
    void button_back_clicked();

private:
    QQmlEngine *qengine_;
    QQmlComponent *qcomponent_;
    QObject *qobject_;
    QObject *qboard_;
    QObject *qbutton_;
};

#endif // PLAYER_VIEW_HPP
