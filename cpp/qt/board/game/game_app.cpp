#include "game_app.hpp"

#include <QDebug>


#include "game/game_logic.hpp"
#include "view/human_view.hpp"

GameApp::GameApp() : qapp_(), qview_()
{
}

GameApp::~GameApp()
{
    delete qapp_;
}

bool GameApp::init(int argc, char **argv)
{
    qapp_ = new QGuiApplication(argc, argv);
    int *aeuia = new int[172];
    aeuia[0] = 10;
//    qview_ = new QQuickView;
//    qview_->setSource(QUrl(QStringLiteral("qrc:///main.qml")));
//    qview_->show();

    return true;
}

int GameApp::run()
{
//    std::shared_ptr<IView> hv(new HumanView);
//    if (!hv->init()) {
//        qDebug() << "failed to initialize HumanView";
//        return 1;
//    }

//    logic_.add_view(hv);

    qview_ = new QQuickView;
    qview_->setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    qview_->show();

    return qapp_->exec();
}
