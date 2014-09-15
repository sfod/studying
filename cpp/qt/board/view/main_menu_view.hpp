#ifndef MAIN_MENU_VIEW_HPP
#define MAIN_MENU_VIEW_HPP

#include <list>
#include <QObject>
#include "qt_view.hpp"

class MainMenuView : public QtView {
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
    virtual QObject *find_object_by_name(const char *name) const override;

private:
    QObject *qroot_;
};

#endif // MAIN_MENU_VIEW_HPP
