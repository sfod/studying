#include "game_app.hpp"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>

#include "view/main_menu_view.hpp"

GameApp::GameApp() : logic_(), qengine_(), qcomponent_(), qroot_()
{
}

GameApp::~GameApp()
{
}

int GameApp::run(int argc, char **argv)
{
    QGuiApplication qapp(argc, argv);

    qengine_ = new QQmlEngine;
    qcomponent_ = new QQmlComponent(qengine_, QUrl(QStringLiteral("qrc:///main.qml")));
    qroot_ = qcomponent_->create();

    std::shared_ptr<IView> view(new MainMenuView(qroot_));
    if (!view->init()) {
        return 1;
    }
    logic_.add_view(view);

    return qapp.exec();
}
