#include <vector>
#include <cstdlib>
#include "point.hpp"
# include <map>

class Graph {
    /*
    * A graph is a collection of nodes and edges.
    * The nodes are stored in a vector.
    * The edges are stored in an adjacency list.
    */
    private:
        std::vector<Node> nodes;
        std::map<size_t, std::vector<size_t> > adj;
    public:
        Graph(): nodes(std::vector<Node>()), adj(std::map<size_t, std::vector<size_t> >()) {};
        void addNode(Node node);
        void addEdge(size_t firstNodeId, size_t secondNodeId);
        size_t getNumNodes();
        size_t getNumEdges();
        std::vector<Node> getNodes();

};