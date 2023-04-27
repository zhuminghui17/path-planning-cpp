#include "node.hpp"
#include "graph.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

class invalid_input : public std::exception
{
public:
    const char *what() const throw() { return "Invalid Input Format"; };
};
// read the nodes in the file

void readNodesFunc(std::string line, Graph &graph)
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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open())
    {
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 1;
    }

    Graph graph = Graph();

    std::string line;

    bool readNodes = false;
    bool readEdges = false;

    while (std::getline(input_file, line))
    {
        if (line.empty())
        {
            continue;
        }
        if (readNodes == false && line.find("$nodes") != line.npos)
        {
            readNodes = true;
            continue;
        }

        if (readNodes == true && line.find("$edges") == line.npos)
        {
            readNodesFunc(line, graph);
        }

        if (readEdges == false && line.find("$edges") != line.npos)
        {
            readNodes = false;
            readEdges = true;
            graph.initAdj();
            continue;
        }

        if (readEdges == true && line.find("$edges") == line.npos)
        {
            readEdgesFunc(line, graph);
        }
    }
    std::cout << graph << std::endl;
    input_file.close();

    return 0;
}
