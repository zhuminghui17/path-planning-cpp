#include <vector>
#include <cstdlib>
#include "point.hpp"
# include <map>

class Graph {
    private:
        std::vector<Node> nodes;
        std::vector<std::map<size_t, std::vector<size_t> > > adj;
    public:
        Graph(): nodes(std::vector<Node>()), adj(std::vector<std::map<size_t, std::vector<size_t> > >()) {};
        void addNode(Node node);
        void addEdge(size_t firstNodeId, size_t secondNodeId);

};