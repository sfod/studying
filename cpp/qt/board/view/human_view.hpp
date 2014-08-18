#ifndef HUMAN_VIEW_HPP
#define HUMAN_VIEW_HPP

#include <QObject>

class HumanView : public QObject
{
    Q_OBJECT

public:
    explicit HumanView(QObject *parent = 0);

public slots:
    void node_clicked(int idx);
};

#endif // HUMAN_VIEW_HPP
