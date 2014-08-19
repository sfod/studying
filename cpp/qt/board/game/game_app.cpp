#include "game_app.hpp"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>

#include "view/human_view.hpp"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

int GameApp::run(int argc, char **argv)
{
    QGuiApplication qapp(argc, argv);

    std::shared_ptr<IView> view(new HumanView);
    if (!view->init()) {
        return 1;
    }
    logic_.add_view(view);

    return qapp.exec();
}
