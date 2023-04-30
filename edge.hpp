#ifndef EDGE_HPP
#define EDGE_HPP
#include "node.hpp"

class Edge {
    private:
        Node start;
        Node end;
        // double weight;
    public:
        Edge(Node start, Node end);
        double getweight();
        bool checkIntersect(Edge & e);
        bool touchObs(std::vector<std::vector<Node> > allObs);
        bool intersectObs(std::vector<std::vector<std::pair<Node, Node> > >pairObsVec);
        Node getStart();
        Node getEnd();
        bool operator==(const Edge & e) const;
        friend std::ostream & operator<<(std::ostream & os, Edge & rhs);

};


#endif // EDGE_HPP

