#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QObject>

class BoardHandler : public QObject
{
    Q_OBJECT
public:
    explicit BoardHandler(QObject *parent = 0);

signals:

public slots:
    void node_clicked(int idx);

};

#endif // QMLHANDLER_H
