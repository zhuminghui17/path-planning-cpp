#include "point.hpp"

Point::Point(double a, double b): x(a), y(b){ 
}

double Point::distanceFrom(const Point & rhs) {
    return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
}

Node::Node(double a, double b, size_t id): Point(a, b), nodeId(id), neighbors(std::vector<Node>()) {
}

size_t Node::getNodeId() {
    return nodeId;
}

