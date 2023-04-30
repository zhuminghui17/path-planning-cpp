#include "node.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <set>

class invalid_input : public std::exception {
public:
    const char *what() const throw() { return "Invalid Input Format"; };
};

void readNodesFunc(std::string line, Graph & graph)
{
    // nodeid, x, y
    size_t firstSpacePos = line.find(" ");
    std::string nodeId = line.substr(0, firstSpacePos);
    size_t secondSpacePos = line.find(" ", firstSpacePos + 1);
    std::string x = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
    std::string y = line.substr(secondSpacePos + 1, line.length() - secondSpacePos - 1);

    Node node = Node(std::stod(x), std::stod(y), std::stoi(nodeId));
    graph.addNode(node);
}

void readEdgesFunc(std::string line, Graph  & graph)
{
    // nodeid, x, y
    size_t firstSpacePos = line.find(" ");
    std::string firstNodeId = line.substr(0, firstSpacePos);
    std::string secondNodeId = line.substr(firstSpacePos + 1, line.length() - firstSpacePos - 1);
    
    // std::stoi(firstNodeId), std::stoi(secondNodeId));
    graph.addEdge(std::stoi(firstNodeId), std::stoi(secondNodeId));
}

void checkArgc(int argc, int right) {
   if (argc != right) {
        std::cerr << "Argument count is not correct!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void checkFileOpen(std::ifstream &input_file, std::string filename) {
    if (!input_file.is_open())
    {
        std::cerr << "Could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

void checkFileClose(std::ifstream &input_file, std::string filename) {
    if (input_file.is_open()) {
        std::cerr << filename << "is still open" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void readGridMap(std::ifstream & input_file, Graph & graph) {
    // initialize line and conditional boolean
    std::string line;
    int readNodes = 0;
    int readEdges = 0;

    while (std::getline(input_file, line)) {
        if (line.empty()) {
            continue;
        }
        else if (readNodes == 0 && line.find("$nodes") != line.npos) {
            readNodes++;
            continue;
        }
        else if (readNodes == 1 && line.find("$edges") == line.npos) {
            readNodesFunc(line, graph);
        }
        else if (readEdges == 0 && line.find("$edges") != line.npos) {
            readNodes++;
            readEdges++;
            graph.initAdj();
            continue;
        }
        else if (readEdges == 1 && line.find("$edges") == line.npos) {
            readEdgesFunc(line, graph);
        }
    }
}


// read obstacles
/* at least two nodes per line, so at least one space per list
*/
void readObsFunc(std::string line, Graph & graph, std::vector<std::vector<Node> > & obs)
{
    size_t spacePos = line.find(" ");
    if (spacePos == line.npos) {
        throw invalid_input(); // need at least two nodes per line
    }
    
    std::vector<size_t> nodeIds = std::vector<size_t>();

    std::string nodeId = line.substr(0, spacePos); // first node
    nodeIds.push_back(std::stoi(nodeId)); // add first node
    
    spacePos = line.find(" ",spacePos + 1); // find second space
    while (spacePos != line.npos) { // while there are still spaces
        nodeId = line.substr(spacePos + 1, line.length() - spacePos - 1); // get next node
        nodeIds.push_back(std::stoi(nodeId));   // add next node
        spacePos = line.find(" ",spacePos + 1); // find next space
    }
    std::vector<Node> oneObs = std::vector<Node>();
    for (size_t i = 0; i < nodeIds.size(); i++) {
        oneObs.push_back(graph.getNode(nodeIds[i])); // add node to obs
    }
    obs.push_back(oneObs);  // add obs to obs list
}


void readObs(std::ifstream & input_file, Graph & graph, std::vector<std::vector<Node> > & obs) {
    // initialize line and conditional boolean
    std::string line;
    int readObs = 0;
    
    while (std::getline(input_file, line)) {
        if (line.empty()) {
            continue;
        }
        else if (readObs == 0 && line.find("$obstacles") != line.npos) {
            readObs++;
            continue;
        }
        else if (readObs == 1 && line.find("$obstacles") == line.npos) {
            readObsFunc(line, graph, obs);
        } 
    }
    
    std::cout << "obs size: " << obs.size() << std::endl;
}

void addEdgeForObs(std::vector<std::vector<Node> > obs, Graph & graph,
    std::vector<std::vector<std::pair<Node, Node> > > & pairObsVec,
    std::set<Edge> & edgeSet) {
    for (size_t i = 0; i < obs.size(); i++) {
        std::vector<std::pair<Node, Node> > pairObs = graph.addOneObs(obs[i]);          
        pairObsVec.push_back(pairObs);
        for (size_t j = 0; j < pairObs.size(); j++) {
            Edge edge = Edge(pairObs[j].first, pairObs[j].second);
            edgeSet.insert(edge);
        }
    }
}

// - so for each value of each key in adj list, initialize the edge, 
// if the edge not in obs edge, check if it touch the obs, check if it
//  intersect with obs, if so, change its weight to inf.

void checkEdgeStillWork(Graph & graph, std::set<Edge> & edgeSet, std::vector<std::vector<std::pair<Node, Node> > > & pairObsVec, std::vector<std::vector<Node> > & obs) {
    for (size_t i = 0; i < graph.getNumNodes(); i++) {
        std::map<size_t, double> adj = graph.getAdj(i);
        for (std::map<size_t, double>::iterator it = adj.begin(); it != adj.end(); ++it) {
            Edge edge = Edge(graph.getNode(i), graph.getNode(it->first));
            if (edgeSet.find(edge) != edgeSet.end()) { // it's a obs edge
                it->second = std::numeric_limits<double>::infinity();
            }
            else {
                // check if it touch the obs
                if (edge.touchObs(obs) || edge.intersectObs(pairObsVec)) {
                    it->second = std::numeric_limits<double>::infinity();
                }   
            }
        }
    }
}

