#include "game_app.hpp"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QTimer>
#include <QDebug>

#include "events/event_manager.hpp"
#include "events/event_caller.hpp"

static GameApp *g_app;

GameApp::GameApp()
    : event_manager_(new EventManager), conn_list_(), logic_(),
      qengine_(), qcomponent_(), qroot_()
{
    g_app = this;
}

GameApp::~GameApp()
{
    for (auto conn : conn_list_) {
        conn.disconnect();
    }
}

int GameApp::run(int argc, char **argv)
{
    QGuiApplication *qapp = new QGuiApplication(argc, argv);

    qengine_ = new QQmlEngine;
    qcomponent_ = new QQmlComponent(qengine_, QUrl(QStringLiteral("qrc:///main.qml")));
    qroot_ = qcomponent_->create();

    logic_ = new GameLogic(qroot_);
    logic_->change_state(LogicState::LS_MainMenu);

    register_delegates();

    QTimer qtimer;
    EventCaller event_caller;
    QObject::connect(&qtimer, SIGNAL(timeout()), &event_caller, SLOT(update()));
    qtimer.start(10);  // call event_caller every 10 ms

    return qapp->exec();
}

void GameApp::main_menu_delegate(const std::shared_ptr<EventData> &event)
{
    (void) event;
    logic_->change_state(LogicState::LS_MainMenu);
}

void GameApp::new_game_delegate(const std::shared_ptr<EventData> &event)
{
    (void) event;
    logic_->change_state(LogicState::LS_Game);
}

void GameApp::quit_delegate(const std::shared_ptr<EventData> &event)
{
    (void) event;
    QGuiApplication::quit();
}

GameApp *GameApp::get()
{
    return g_app;
}

void GameApp::register_delegates()
{
    bs2::connection conn;

    conn = EventManager::get()->add_listener(
            boost::bind(&GameApp::main_menu_delegate, this, _1),
            EventData_MainMenu::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameApp::new_game_delegate, this, _1),
            EventData_NewGame::event_type_);
    conn_list_.push_back(conn);

    conn = EventManager::get()->add_listener(
            boost::bind(&GameApp::quit_delegate, this, _1),
            EventData_Quit::event_type_);
    conn_list_.push_back(conn);
}
