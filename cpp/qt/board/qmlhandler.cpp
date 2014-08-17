#include "qmlhandler.h"
#include <QDebug>

QMLHandler::QMLHandler(QObject *parent) :
    QObject(parent)
{
}

void QMLHandler::node_clicked(int idx)
{
    qDebug() << "called cpp_slot with idx " << idx;
}
