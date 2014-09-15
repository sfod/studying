#ifndef MAIN_MENU_VIEW_HPP
#define MAIN_MENU_VIEW_HPP

#include <list>
#include <QObject>
#include "iview.hpp"

class MainMenuView : public QObject, public IView {
    Q_OBJECT

public:
    explicit MainMenuView(QObject *qroot, QObject *qparent = 0);
    virtual ~MainMenuView();

    bool init();
    virtual void on_msg();
    virtual void on_update();

public slots:
    void button_new_game_clicked();
    void button_quit_clicked();

private:
    QObject *qroot_;
    std::list<QObject*> object_list_;
};

#endif // MAIN_MENU_VIEW_HPP
