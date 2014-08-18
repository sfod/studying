#include "human_view.hpp"
#include <QDebug>

HumanView::HumanView(QObject *parent) : QObject(parent)
{
}

void HumanView::node_clicked(int idx)
{
    qDebug() << "node " << idx << " clicked";
}
