#include "player_view.hpp"
#include <QQuickItem>
#include <QDebug>

PlayerView::PlayerView(QObject *parent)
    : QObject(parent), IView(), qengine_(), qcomponent_(), qobject_(),
      qboard_(), qbutton_()
{
}

PlayerView::~PlayerView()
{
    delete qobject_;
    delete qcomponent_;
}

bool PlayerView::init()
{
    qengine_ = new QQmlEngine;
    qcomponent_ = new QQmlComponent(qengine_, QUrl(QStringLiteral("qrc:///main.qml")));
    qobject_ = qcomponent_->create();

    qboard_ = qobject_->findChild<QObject*>("board");
    if (qboard_ == NULL) {
        qDebug() << "cannot find board element";
        return false;
    }
    QObject::connect(
                qboard_, SIGNAL(boardSignal(int)),
                this, SLOT(node_clicked(int))
    );

    qbutton_ = qobject_->findChild<QObject*>("boardBack");
    if (qbutton_ == NULL) {
        qDebug() << "cannot find boardBack element";
        return false;
    }
    QObject::connect(
                qbutton_, SIGNAL(clicked()),
                this, SLOT(button_back_clicked())
    );

    return true;
}

void PlayerView::on_msg()
{
}

void PlayerView::on_update()
{
}

void PlayerView::node_clicked(int idx)
{
    qDebug() << "node " << idx << " clicked";
}

void PlayerView::button_back_clicked()
{
    qDebug() << "back button clicked";
}
