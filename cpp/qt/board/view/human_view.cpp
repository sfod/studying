#include "human_view.hpp"
#include <QQuickItem>
#include <QDebug>

HumanView::HumanView(QObject *parent)
    : QObject(parent), IView(), qengine_(), qcomponent_(), qobject_(), qboard_()
{
}

HumanView::~HumanView()
{
    delete qobject_;
    delete qcomponent_;
}

bool HumanView::init()
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

    return true;
}

void HumanView::on_msg()
{
}

void HumanView::on_update()
{
}

void HumanView::node_clicked(int idx)
{
    qDebug() << "node " << idx << " clicked";
}
