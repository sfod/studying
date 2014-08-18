#include "human_view.hpp"
#include <QQuickItem>
#include <QDebug>

HumanView::HumanView(QObject *parent) : QObject(parent), IView(), qview_(NULL), qboard_(NULL)
{
}

HumanView::~HumanView()
{
    delete qview_;
    qDebug() << "destroying HumanView";
}

bool HumanView::init()
{
    qview_ = new QQuickView;
    qview_->setSource(QUrl(QStringLiteral("qrc:///main.qml")));

    qboard_ = qview_->rootObject()->findChild<QObject*>("board");
    if (qboard_ == NULL) {
        qDebug() << "cannot find board element";
        return false;
    }

    QObject::connect(
                qboard_, SIGNAL(boardSignal(int)),
                this, SLOT(node_clicked(int))
    );

    qview_->show();

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
