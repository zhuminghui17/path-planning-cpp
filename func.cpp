#include "node.hpp"
#include "graph.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

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
        throw invalid_input();
    }
    
    std::vector<size_t> nodeIds = std::vector<size_t>();

    std::string nodeId = line.substr(0, spacePos);
    nodeIds.push_back(std::stoi(nodeId));
    
    spacePos = line.find(" ",spacePos + 1);
    while (spacePos != line.npos) {
        nodeId = line.substr(spacePos + 1, line.length() - spacePos - 1);
        nodeIds.push_back(std::stoi(nodeId));
        spacePos = line.find(" ",spacePos + 1);
    }
    std::vector<Node> oneObs = std::vector<Node>();
    for (size_t i = 0; i < nodeIds.size(); i++) {
        oneObs.push_back(graph.getNode(nodeIds[i]));
    }
    obs.push_back(oneObs);
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
