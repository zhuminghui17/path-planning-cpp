#ifndef POINT_H
#define POINT_H

#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

class Point {
    private:
        double x, y;
    public:
        Point(double a, double b);
        double distanceFrom(const Point & rhs);
};

class Node: public Point {
    private:
        size_t nodeId;
        std::vector<Node> neighbors;
    public:
        Node(double a, double b, size_t id);
        size_t getNodeId();
};  



#endif
