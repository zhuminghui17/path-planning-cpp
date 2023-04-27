#ifndef NODE_H
#define NODE_H

#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

class Node {
    private:
        double x, y;
        size_t nodeId;
    public:
        Node(double a, double b, size_t id);
        size_t getNodeId();
        double getX();
        double getY();
        double distanceFrom(const Node & rhs);
        friend std::ostream & operator<<(std::ostream & os, Node & rhs);

    
};


#endif
