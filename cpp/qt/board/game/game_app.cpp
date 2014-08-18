#include "game_app.hpp"

#include <QQuickView>
#include <QQuickItem>

#include "view/human_view.hpp"

GameApp::GameApp() : app_()
{
}

GameApp::~GameApp()
{
    delete app_;
}

bool GameApp::init(int argc, char **argv)
{
    app_ = new QApplication(argc, argv);
    return true;
}

int GameApp::run()
{
    QQuickView view(QUrl(QStringLiteral("qrc:///main.qml")));
    QQuickItem *item = view.rootObject();
    QObject *board = item->findChild<QObject*>("board");

    HumanView hv;
    QObject::connect(board, SIGNAL(boardSignal(int)), &hv, SLOT(node_clicked(int)));

    view.show();

    return app_->exec();
}
