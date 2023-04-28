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
        else if (readNodes == false && line.find("$nodes") != line.npos) {
            readNodes++;
            continue;
        }
        else if (readNodes == true && line.find("$edges") == line.npos) {
            readNodesFunc(line, graph);
        }
        else if (readEdges == false && line.find("$edges") != line.npos) {
            readNodes++;
            readEdges++;
            graph.initAdj();
            continue;
        }
        else if (readEdges == true && line.find("$edges") == line.npos) {
            readEdgesFunc(line, graph);
        }
    }
}

