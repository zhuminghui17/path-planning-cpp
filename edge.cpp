#include "edge.hpp"

// constructor using initialization list
Edge::Edge(Node start, Node end): start(start), end(end) {
}

// get weight of the edge
double Edge::getweight() {
    return start.distanceFrom(end);
}

// check if two edges intersect
bool Edge::checkIntersect(Edge & e) {
    // if intersect, return true
    // else return false
    // if two edges have same start or end, return false
    if (start == e.start || start == e.end || end == e.start || end == e.end) {
        return false;
    }
    // if two edges have same slope, return false
    if (start.slopeFrom(end) == e.start.slopeFrom(e.end)) {
        return false;
    }
    // if two edges intersect, return true
    // else return false
    double Ax = start.getX();
    double Ay = start.getY();
    double Bx = end.getX();
    double By = end.getY();
    double Mx = e.start.getX();
    double My = e.start.getY();
    double Nx = e.end.getX();
    double Ny = e.end.getY();

    double ori1 = (By - Ay) * (Mx - Bx) - (Bx - Ax) * (My - By);
    double ori2 = (By - Ay) * (Nx - Bx) - (Bx - Ax) * (Ny - By);
    double ori3 = (Ny - My) * (Ax - Nx) - (Nx - Mx) * (Ay - Ny);
    double ori4 = (Ny - My) * (Bx - Nx) - (Nx - Mx) * (By - Ny);

    if (ori1 * ori2 < 0 && ori3 * ori4 < 0) {
        return true;
    }

    if (ori1 == 0 && ori2 == 0 && ori3 == 0 && ori4 == 0) {
        // check if x-projections intersect
        if (std::max(Ax, Bx) >= std::min(Mx, Nx) && std::max(Mx, Nx) >= std::min(Ax, Bx)) {
            // check if y-projections intersect
            if (std::max(Ay, By) >= std::min(My, Ny) && std::max(My, Ny) >= std::min(Ay, By)) {
                return true;
            }
        }
    }
    return false;
}

// get start node
Node Edge::getStart() {
    return start;
}

// get end node
Node Edge::getEnd() {
    return end;
}

// check if edge touch any obstacle
bool Edge::touchObs(std::vector<std::vector<Node> > allObs) {
    // if touch, return true
    // else return false
    for (size_t i = 0; i < allObs.size(); i++) {
        for (size_t j = 0; j < allObs[i].size(); j++) {
            if (allObs[i][j] == start || allObs[i][j] == end) {
                return true;
            }
        }
    }
    return false;
}

// check if edge intersect any obstacle
bool Edge::intersectObs(std::vector<std::vector<std::pair<Node, Node> > >pairObsVec) {
    // if intersect, return true
    // else return false
    for (size_t i = 0; i < pairObsVec.size(); i++) {
        for (size_t j = 0; j < pairObsVec[i].size(); j++) {
            Edge e = Edge(pairObsVec[i][j].first, pairObsVec[i][j].second);
            if (checkIntersect(e)) {
                return true;
            }
        }
    }
    return false;
}

// overloaded == operator to compare two edges
bool Edge::operator==(const Edge & e) const {
    return (start == e.start && end == e.end) || (start == e.end && end == e.start);
}

// overloaded << operator to print the edge
std::ostream & operator<<(std::ostream & os, Edge & rhs) {
    os << rhs.start << "->" << rhs.end;
    return os;
}

