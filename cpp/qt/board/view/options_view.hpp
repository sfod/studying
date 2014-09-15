#ifndef OPTIONS_VIEW_HPP
#define OPTIONS_VIEW_HPP

#include <QObject>
#include "iview.hpp"

class OptionsView : public QObject, public IView {
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
    QObject *qroot_;
    std::list<QObject*> object_list_;
};

#endif // OPTIONS_VIEW_HPP
