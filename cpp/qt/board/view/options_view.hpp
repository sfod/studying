#ifndef OPTIONS_VIEW_HPP
#define OPTIONS_VIEW_HPP

#include <QObject>
#include "qt_view.hpp"

class OptionsView : public QtView {
    Q_OBJECT

public:
    explicit OptionsView(QObject *qroot, QObject *qparent = 0);
    virtual ~OptionsView();

    bool init();
    virtual void on_msg();
    virtual void on_update();

public slots:
    void button_start_game_clicked();
    void button_back_clicked();

private:
    virtual QObject *find_object_by_name(const char *name) const override;
    bool connect_options();

private:
    QObject *qroot_;
    QObject *qoptions_;
};

#endif // OPTIONS_VIEW_HPP
