#ifndef MAIN_MENU_VIEW_HPP
#define MAIN_MENU_VIEW_HPP

#include <QObject>
#include "iview.hpp"

class MainMenuView : public QObject, public IView
{
    Q_OBJECT
public:
    explicit MainMenuView(QObject *parent = 0);

signals:

public slots:

};

#endif // MAIN_MENU_VIEW_HPP
