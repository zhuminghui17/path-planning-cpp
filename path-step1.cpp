#include "point.hpp"
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

void readNodesFunc(std::string line, std::vector<Node> nodes)
{
    // nodeid, x, y
    size_t firstSpacePos = line.find(" ");
    std::string nodeId = line.substr(0, firstSpacePos);
    size_t secondSpacePos = line.find(" ", firstSpacePos + 1);
    std::string x = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
    std::string y = line.substr(secondSpacePos + 1, line.length() - secondSpacePos - 1);

    std::cout << nodeId << " " << x << " " << y << std::endl;

    Node node = Node(std::stod(x), std::stod(y), std::stoi(nodeId));
    nodes.push_back(node);
}

void readEdgesFunc(std::string line, std::vector<std::pair<size_t, size_t> > edges)
{
    // nodeid, x, y
    size_t firstSpacePos = line.find(" ");
    std::string firstNodeId = line.substr(0, firstSpacePos);
    std::string secondNodeId = line.substr(firstSpacePos + 1, line.length() - firstSpacePos - 1);
    std::pair<size_t, size_t> edge = std::make_pair(std::stoi(firstNodeId), std::stoi(secondNodeId));
    edges.push_back(edge);

    std::cout << firstNodeId << " " << secondNodeId << std::endl;
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

    std::string line;

    bool readNodes = false;
    bool readEdges = false;

    std::vector<Node> nodes;
    std::vector<std::pair<size_t, size_t> > edges;

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
            readNodesFunc(line, nodes);
        }

        if (readEdges == false && line.find("$edges") != line.npos)
        {
            readNodes = false;
            readEdges = true;
            continue;
        }

        if (readEdges == true && line.find("$edges") == line.npos)
        {
            readEdgesFunc(line, edges);
        }
    }

    input_file.close();

    return 0;
}
