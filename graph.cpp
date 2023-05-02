#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <cstdlib>
#include <map>
#include <iostream>
#include <queue>

// constructor
Graph::Graph(): nodes(std::vector<Node>()), adj(std::vector<std::map<size_t, double> >()) {
}

// add a node to the graph
void Graph::addNode(Node node) {
    nodes.push_back(node);
}

// add an edge between two nodes
void Graph::addEdge(size_t f, size_t s) {
    // check if the node id is valid
    checkNodeValid(f);
    checkNodeValid(s);

    // check if there is edge between f and s
    if (adj[f].find(s) != adj[f].end() || adj[s].find(f) != adj[s].end()) {
        return;
    }

    // map: key is f or s, value is the distance between f and s
    // remember to initialize the the adj[] as empty map    
    adj[f].insert(std::pair<size_t, double> (s, nodes[f].distanceFrom(nodes[s])));
    adj[s].insert(std::pair<size_t, double> (f, nodes[f].distanceFrom(nodes[s])));
}

// get the number of nodes in the graph
size_t Graph::getNumNodes() {
    return nodes.size();
}

// get the number of edges in the graph
size_t Graph::getNumEdges() {
    size_t numEdges = 0;
    for (size_t i = 0; i < adj.size(); i++) {
        numEdges += adj[i].size();
    }
    return numEdges / 2;
}

// get the vector of nodes in the graph
std::vector<Node> Graph::getNodes() {
    return nodes;
}

// initialize the adjacency list
void Graph::initAdj() {
    for (size_t i = 0; i < nodes.size(); i++) {
        std::map<size_t, double> m;
        adj.push_back(m);
    }
}

// get the node with the given id
Node Graph::getNode(size_t nodeId) {
    // check if the node id is valid
    checkNodeValid(nodeId);

    return nodes[nodeId];
}

// get the size of the adjacency list
size_t Graph::getAdjSize() {
    return adj.size();
}

// get the adjacency list
std::map<size_t, double> Graph::getAdj(size_t nodeId) {
    // check if the node id is valid
    checkNodeValid(nodeId);
    // all the adjacency list is initialized in initAdj()
    // so we don't need to check if the adj[nodeId] is empty

    return adj[nodeId];
}

// print the graph
std::ostream & operator<<(std::ostream & os, Graph & rhs) {
    for (size_t i = 0; i < rhs.getNumNodes(); i++) {
        Node curNode = rhs.getNode(i);
        os << "(" << curNode.getX() << "," << curNode.getY() <<")" << " ";
    }
    os << std::endl;
    for (size_t i = 0; i < rhs.getAdjSize(); i++) {
        os << i << ": ";
        std::map<size_t, double> curAdj = rhs.getAdj(i);
        for (std::map<size_t, double>::const_iterator it = curAdj.begin(); it != curAdj.end(); it++) {
            os << it->first << "," << it->second << " ";
        }
        os << std::endl;
    }
  return os;
}

void Graph::dijkstra(size_t startNodeId, size_t endNodeId) {
    // get the adj of startNodeId
    std::map<size_t, double> adj = getAdj(startNodeId);
    // initialize the distance vector for all nodes to be infinity
    std::vector<double> dist = std::vector<double>(this->getNumNodes(), std::numeric_limits<double>::infinity());
    // set the distance of startNodeId to be 0
    dist[startNodeId] = 0;

    // initialize visited and unvisited
    std::vector<size_t> visited;
    std::vector<bool> unvisited = std::vector<bool>(this->getNumNodes(), true);

    // initialize previous vector to keep track of the previous node in the path
    std::vector<size_t> previous = std::vector<size_t>(this->getNumNodes(), -1);

    // initialize priority queue
    std::priority_queue<std::pair<size_t, double>, std::vector<std::pair<size_t, double> >, std::greater<std::pair<size_t, double> > > pq;
    pq.push(std::make_pair(startNodeId, 0));

    while(!pq.empty() && unvisited[endNodeId]) {
        size_t cur = pq.top().first;
        pq.pop();
        unvisited[cur] = false;

            // Update distances to neighbors of current node
    std::map<size_t, double> neighbors = getAdj(cur);
    std::map<size_t, double>::iterator it = neighbors.begin();
    while (it != neighbors.end()) {
        size_t neighborId = it->first;
        double neighborDist = it->second;
        double newDist = dist[cur] + neighborDist;

        if (newDist < dist[neighborId]) {
            dist[neighborId] = newDist;
            previous[neighborId] = cur;
            pq.push(std::make_pair(neighborId, newDist));
            
            // print out the new best path found
            std::vector<size_t> path;
            size_t tmp = neighborId;
            while (tmp != startNodeId) {
                path.push_back(tmp);
                tmp = previous[tmp];
            }
            path.push_back(startNodeId);
            std::reverse(path.begin(), path.end());
            double cost = dist[neighborId];
            std::cout << "New best path found: ";
            for (size_t i = 0; i < path.size(); i++) {
                std::cout << path[i];
                if (i < path.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << " : " << cost << std::endl;
        }
        it++;
    }
}

// If endNodeId was not reached, there is no path
if (dist[endNodeId] == std::numeric_limits<double>::infinity()) {
    std::cerr << "No path exists" << std::endl;
    exit(EXIT_FAILURE);

} else {
    // print out the final best path
    std::vector<size_t> path;
    size_t cur = endNodeId;
    while (cur != startNodeId) {
        path.push_back(cur);
        cur = previous[cur];
    }
    path.push_back(startNodeId);
    std::reverse(path.begin(), path.end());
    double cost = dist[endNodeId];
    std::cout << "Shortest path found: ";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << " : " << cost << std::endl;
}
}
std::vector<std::pair<Node, Node> > Graph::addOneObs(std::vector<Node> oneObs) {
    std::vector<std::pair<Node, Node> > PairNodeforOneObs;
    for (size_t i = 0; i < oneObs.size(); i++) {
        for (size_t j = i + 1; j < oneObs.size(); j++) {
            addEdge(oneObs[i].getNodeId(), oneObs[j].getNodeId());
            std::pair<Node, Node> PairObs = std::make_pair(oneObs[i], oneObs[j]);
            PairNodeforOneObs.push_back(PairObs);
        }    
    }
    return PairNodeforOneObs;    
}

void Graph::changeWeight(size_t firstNodeId, size_t secondNodeId, double newWeight) {
    // check if there is edge between f and s
    if (adj[firstNodeId].find(secondNodeId) != adj[firstNodeId].end()) {
        adj[firstNodeId][secondNodeId] = newWeight;
    }

    if (adj[secondNodeId].find(firstNodeId) != adj[secondNodeId].end()) {
        adj[secondNodeId][firstNodeId] = newWeight;
    }
}


// Custom comparison function that compares the second element of pairs
struct ComparePairs {
    bool operator() (const std::pair<size_t, double>& p1, const std::pair<size_t, double>& p2) const {
        return p1.second > p2.second;
    }
};


void Graph::Astar(size_t startNodeId, size_t endNodeId) {
    // use a map to store, g h f
    std::map<size_t, std::vector<double> > ghf;
    // initialize the map, g value = inf, h value = inf, f value = inf
    for (size_t i = 0; i < this->getNumNodes(); i++) {
        std::vector<double> v = std::vector<double>(3, std::numeric_limits<double>::infinity());
        ghf[i] = v;
    }
    // set the g value of startNodeId to be 0
    ghf[startNodeId][0] = 0;
    // set the h value of startNodeId to be the distance between startNodeId and endNodeId
    ghf[startNodeId][1] = this->getNode(startNodeId).distanceFrom(this->getNode(endNodeId));
    // set the f value of startNodeId to be the sum of g and h
    ghf[startNodeId][2] = ghf[startNodeId][0] + ghf[startNodeId][1];
    
    // initialize visited and unvisited
    std::vector<size_t> visited;
    std::vector<bool> unvisited = std::vector<bool>(this->getNumNodes(), true);

    // initialize previous vector to keep track of the previous node in the path
    std::vector<size_t> previous = std::vector<size_t>(this->getNumNodes(), -1);

    // initialize priority queue
    std::priority_queue<std::pair<size_t, double>, std::vector<std::pair<size_t, double> >, ComparePairs > pq;
    pq.push(std::make_pair(startNodeId, ghf[startNodeId][2]));

    while (!pq.empty() && unvisited[endNodeId]) {
        size_t cur = pq.top().first;
        pq.pop();
        unvisited[cur] = false;

        if (cur == endNodeId) {
            break;
        }
        // Update distances to neighbors of current node
        std::map<size_t, double> neighbors = getAdj(cur);
        std::map<size_t, double>::iterator it = neighbors.begin();
        while (it != neighbors.end()) {
            size_t neighborId = it->first;
            double neighborDist = it->second;
            double newG = ghf[cur][0] + neighborDist;
            double newH = this->getNode(neighborId).distanceFrom(this->getNode(endNodeId));
            double newF = newG + newH;

            if (newF < ghf[neighborId][2]) {
                ghf[neighborId][0] = newG;
                ghf[neighborId][1] = newH;
                ghf[neighborId][2] = newF;
                previous[neighborId] = cur;
                pq.push(std::make_pair(neighborId, newF));

                // print out the new best path found
                std::vector<size_t> path;
                size_t tmp = neighborId;
                while (tmp != startNodeId) {
                    path.push_back(tmp);
                    tmp = previous[tmp];
                }
                path.push_back(startNodeId);
                std::reverse(path.begin(), path.end());
                std::cout << "New best path found: ";
                for (size_t i = 0; i < path.size(); i++) {
                    std::cout << path[i];
                    if (i < path.size() - 1) {
                        std::cout << " ";
                    }
                }
                std::cout << " : " << ghf[neighborId][2] << std::endl;                
            }
            it++;
        }
    }

    // If endNodeId was not reached, there is no path
    if (ghf[endNodeId][2] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path exists" << std::endl;
        exit(EXIT_FAILURE);
    }  else {
        // print out the final best path
        std::vector<size_t> path;
        size_t cur = endNodeId;
        while (cur != startNodeId) {
            path.push_back(cur);
            cur = previous[cur];
        }
        path.push_back(startNodeId);
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << " : " << ghf[endNodeId][2] << std::endl;
    }
}

    

void Graph::checkNodeValid(size_t nodeId) {
    try {
        if (nodeId < 0 || nodeId >= nodes.size()) {
            throw invalid_node();
        }
    }
    catch (invalid_node & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool compareNodeId(Node & a, Node & b) {
    return a.getNodeId() < b.getNodeId();
}


void Graph::checkNodes() {
    // sort the nodes vector by nodeId, from small to large
    std::sort(nodes.begin(), nodes.end(), compareNodeId);
    try {
        // iterate through the nodes vector, if the node id is not consecutive, throw invalid_input
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i].getNodeId() != i) {
                throw invalid_input();
            }
        }
    }
    catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}


