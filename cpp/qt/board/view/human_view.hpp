#ifndef HUMAN_VIEW_HPP
#define HUMAN_VIEW_HPP

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>

#include "iview.hpp"

class HumanView : public QObject, public IView
{
    Q_OBJECT

public:
    explicit HumanView(QObject *parent = 0);
    ~HumanView();

    bool init();
    virtual void on_msg();
    virtual void on_update();

public slots:
    void node_clicked(int idx);

private:
    QQmlEngine *qengine_;
    QQmlComponent *qcomponent_;
    QObject *qobject_;
    QObject *qboard_;
};

#endif // HUMAN_VIEW_HPP
