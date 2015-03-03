#ifndef WALL_HPP
#define WALL_HPP

#include <vector>
#include <QObject>
#include <QtQml>
#include "node.hpp"


class WallEnumClass : public QObject {
    Q_OBJECT

public:
    enum WallOrientation {
        WO_Horizontal,
        WO_Vertical,
        WO_Invalid
    };
    Q_ENUMS(WallOrientation)

    static void declareQML() {
        qmlRegisterUncreatableType<WallEnumClass>("WallOrientationQML", 1, 0, "WallOrientation", "mesasge");
    }
};

class Wall {
public:
    Wall(WallEnumClass::WallOrientation wo, Node node, int len);
    ~Wall();

private:
    std::vector<std::pair<Node, Node>> affected_nodes_;
};

#endif // WALL_HPP
