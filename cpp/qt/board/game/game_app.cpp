#include "game_app.hpp"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QTimer>

#include "events/event_manager.hpp"
#include "events/event_caller.hpp"
#include "view/main_menu_view.hpp"

GameApp::GameApp()
    : event_manager_(new EventManager), logic_(),
      qengine_(), qcomponent_(), qroot_()
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

    QTimer qtimer;
    EventCaller event_caller;
    QObject::connect(&qtimer, SIGNAL(timeout()), &event_caller, SLOT(update()));
    qtimer.start(10);

    return qapp.exec();
}
