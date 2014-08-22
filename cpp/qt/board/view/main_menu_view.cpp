#include "main_menu_view.hpp"
#include <QDebug>

MainMenuView::MainMenuView(QObject *qroot, QObject *qparent)
    : QObject(qparent), IView(), qroot_(qroot), qbutton_()
{
}

MainMenuView::~MainMenuView()
{
}

bool MainMenuView::init()
{
    qbutton_ = qroot_->findChild<QObject*>("buttonNewGame");
    if (qbutton_ == NULL) {
        qDebug() << "cannot find buttonNewGame element";
        return false;
    }
    QObject::connect(
                qbutton_, SIGNAL(clicked()),
                this, SLOT(button_new_game_clicked())
    );

    return true;
}

void MainMenuView::on_msg()
{
}

void MainMenuView::on_update()
{
}

void MainMenuView::button_new_game_clicked()
{
    qDebug() << "New Game button clicked";
}
