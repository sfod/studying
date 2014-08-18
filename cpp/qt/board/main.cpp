#include <QApplication>
#include <QQuickView>
#include <QQuickItem>

#include "board_handler.hpp"
#include "view/human_view.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView view(QUrl(QStringLiteral("qrc:///main.qml")));
    QQuickItem *item = view.rootObject();
    QObject *board = item->findChild<QObject*>("board");

    BoardHandler handler;
    QObject::connect(board, SIGNAL(boardSignal(int)), &handler, SLOT(node_clicked(int)));

    HumanView hv;

    view.show();

    return app.exec();
}
