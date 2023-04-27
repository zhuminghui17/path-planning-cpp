#include "graph.hpp"

Graph::Graph(): nodes(std::vector<Node>()), adj(std::map<size_t, std::vector<size_t> > ()) {
}

void Graph::addNode(Node node) {
    nodes.push_back(node);
}

void Graph::addEdge(size_t f, size_t s) {

    // if node f or s not in nodes, it's bug
    if (std::find(nodes.begin(), nodes.end(), f) == nodes.end() ||
        std::find(nodes.begin(), nodes.end(), s) == nodes.end()) {
        std::cerr << "Error: node not in nodes" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // if f not in adj, add s to adj[f]
    if (adj.find(f) == adj.end()) {
        std::vector<size_t> v;
        v.push_back(s);
        adj[f] = v;
    }
    else {
        adj[f].push_back(s); // f in adj, add s to adj[f]
    }

    // if s not in adj, add f to adj[s]
    if (adj.find(s) == adj.end()) {
        std::vector<size_t> v;
        v.push_back(f);
        adj[s] = v;
    }
    else {
        adj[s].push_back(f); // s in adj, add f to adj[s]
    }
}


size_t Graph::getNumNodes() {
    return nodes.size();
};
size_t Graph::getNumEdges() {

    size_t numEdges = 0;
    std::map<size_t, std::vector<size_t> >::iterator it = adj.begin();
    while (it != adj.end()) {
        numEdges += it->second.size();
        it++;
    }
    return numEdges / 2;
};

std::vector<Node> Graph::getNodes() {
    return nodes;
};