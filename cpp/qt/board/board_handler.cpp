#include "board_handler.hpp"
#include <QDebug>

BoardHandler::BoardHandler(QObject *parent) :
    QObject(parent)
{
}

void BoardHandler::node_clicked(int idx)
{
    qDebug() << "called cpp_slot with idx " << idx;
}
