#include "node.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include "exceptions.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

// check the argument count
void checkArgc(int argc, int right) {
   if (argc != right) {
        std::cerr << "Argument count is not correct! It should be " << right << "!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// check if the file can be opened
void checkFileOpen(std::ifstream &input_file, std::string filename) {
    if (!input_file.is_open())
    {
        std::cerr << "Cannot open file " << filename << ", please check the file name or path is right!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void checkFileClose(std::ifstream &input_file, std::string filename) {
    if (input_file.is_open()) {
        std::cerr << filename << "is still open" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// check the input is only numeric
void checkOnlyNumeric(std::string line) {
    try {
        for (size_t i = 0; i < line.length(); i++) {
            if (isalpha(line[i])) {
                throw invalid_input("The input is not numeric!");
            }
        }
    }
    catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

// check the input is only int
void checkOnlyInt(std::string line) {
    try {
        for (size_t i = 0; i < line.length(); i++) {
            if (isalpha(line[i]) || line[i] == '.') {
                throw invalid_input("The input is not integer!");
            }
        }
    }
    catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

// read nodes and store in graph
void readNodesFunc(std::string line, Graph & graph) {
    //line: nodeId x y

    // check no letter in the line
    checkOnlyNumeric(line);
    try {
        size_t firstSpacePos = line.find(" ");
        size_t secondSpacePos = line.find(" ", firstSpacePos + 1);
        if (firstSpacePos == line.npos || secondSpacePos == line.npos) {
            throw invalid_input("There is node information missing in the line!");
        }
        std::string nodeId = line.substr(0, firstSpacePos);
        std::string x = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);

        size_t thirdSpacePos = line.find(" ", secondSpacePos + 1); // third space if exist
        
        if (thirdSpacePos != line.npos) { // avoid more input in the lines
            throw invalid_input("There is node information more than needed in the line!");
        }

        std::string y = line.substr(secondSpacePos + 1, line.length() - secondSpacePos - 1);

        Node node = Node(std::stod(x), std::stod(y), std::stoi(nodeId));
        graph.addNode(node);
    } 
    catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

// read edges and store in graph
void readEdgesFunc(std::string line, Graph  & graph) {
    // nodeid, x, y
    // check no letter in the line
    checkOnlyInt(line);
    try {
    size_t firstSpacePos = line.find(" ");
    if (firstSpacePos == line.npos) {
        throw invalid_input("There is edge information missing in the line!");
    }

    size_t secondSpacePos = line.find(" ", firstSpacePos + 1); // third space if exist
    
    if (secondSpacePos != line.npos) { // avoid more input in the lines
        throw invalid_input("There is edge information more than needed in the line!");
    }
    
    std::string firstNodeId = line.substr(0, firstSpacePos);
    std::string secondNodeId = line.substr(firstSpacePos + 1, line.length() - firstSpacePos - 1);
    graph.addEdge(std::stoi(firstNodeId), std::stoi(secondNodeId));
    } catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }    
}

// read nodes and edges
void readGridMap(std::ifstream & input_file, Graph & graph) {
    // initialize line and conditional boolean
    std::string line;
    int readNodesStatus = 0; // 0 = not read, 1 = reading, 2 = done
    int readEdgesStatus = 0; // 0 = not read, 1 = reading, 2 = done

    try {
        while (std::getline(input_file, line)) {
            // skipe empty line
            if (line.empty()) {
                continue;
            }
            // if #edges is before #nodes, throw error
            else if (readNodesStatus == 0 && readEdgesStatus == 0 && line.find("$edges") != line.npos) {
                throw invalid_input("$edges is before $nodes!");
            }
            else if (readNodesStatus == 0 && readEdgesStatus == 0 && line.find("$nodes") != line.npos) {
                readNodesStatus++;
            }
            else if (readNodesStatus == 1 && readEdgesStatus == 0 && line.find("$edges") == line.npos) {
                readNodesFunc(line, graph);
            }
            else if (readNodesStatus == 1 && readEdgesStatus == 0 && line.find("$edges") != line.npos) {
                readNodesStatus++;
                readEdgesStatus++;
                graph.initAdj();
                continue;
            }
            else if (readNodesStatus == 2 && readEdgesStatus == 1 && line.find("$edges") == line.npos) {
                readEdgesFunc(line, graph);
            }
            else {
                throw invalid_input("There is unexpected input."); // unexpected input, for example, multiple $nodes
            }
        }
        readEdgesStatus++;
        graph.checkNodes();
        // if #nodes or #edges is not read, throw error
        if (readNodesStatus != 2 || readEdgesStatus != 2) {
            // // have not read nodes or edges, or not finished reading
            throw invalid_input("Have not read nodes or edges, or not finished reading!"); 
        }

    } catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }   
}


// read obstacles
// at least two nodes per line, so at least one space per list
void readObsFunc(std::string line, Graph & graph, std::vector<std::vector<Node> > & obs)
{
    size_t spacePos = line.find(" ");
    if (spacePos == line.npos) {
        // need at least two nodes per line
        throw invalid_input("It's required to have at least two nodes in each obstacles!"); 
    }
    
    std::vector<size_t> nodeIds = std::vector<size_t>();

    // use split to get the nodeIds
    std::stringstream ss(line);
    std::string nodeId;
    while (ss >> nodeId) {
        checkOnlyInt(nodeId);
        nodeIds.push_back(std::stoi(nodeId));
    }
    // I delete the method with finding space and substr, because it's not efficient

    std::vector<Node> oneObs = std::vector<Node>();
    for (size_t i = 0; i < nodeIds.size(); i++) {
        oneObs.push_back(graph.getNode(nodeIds[i])); // add node to obs
    }
    obs.push_back(oneObs);  // add obs to obs list
}


void readObs(std::ifstream & input_file, Graph & graph, std::vector<std::vector<Node> > & obs) {
    // initialize line and conditional boolean
    std::string line;
    int readObsStaus = 0; // 0 = not read, 1 = reading, 2 = done
    
    try {
        while (std::getline(input_file, line)) {
            if (line.empty()) { // skip empty line
                continue;
            }
            else if (readObsStaus == 0 && line.find("$obstacles") == line.npos) {
                throw invalid_input("$obstacles"); 
            }
            else if (readObsStaus == 0 && line.find("$obstacles") != line.npos) {
                readObsStaus++;
                continue;
            }
            else if (readObsStaus == 1 && line.find("$obstacles") == line.npos) {
                readObsFunc(line, graph, obs);
            }
            else {
                throw invalid_input("There is unexpected input!"); 
                // unexpected input, for example, multiple $obstacles
            }
        }
        readObsStaus++;
        // if #obstacles is not read, throw error
        if (readObsStaus != 2) {
            throw invalid_input("Have not read obstacles, or not finished reading");
        }
    } catch (invalid_input & e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void addEdgeForObs(std::vector<std::vector<Node> > obs, Graph & graph,
    std::vector<std::vector<std::pair<Node, Node> > > & pairObsVec,
    std::vector<Edge> & edgeObs) {
    for (size_t i = 0; i < obs.size(); i++) {
        std::vector<std::pair<Node, Node> > PairNodeforOneObs = graph.addOneObs(obs[i]);          
        pairObsVec.push_back(PairNodeforOneObs);
        for (size_t j = 0; j < PairNodeforOneObs.size(); j++) {
            Edge edge = Edge(PairNodeforOneObs[j].first, PairNodeforOneObs[j].second);
            edgeObs.push_back(edge);
        }
    }
    // // print edgeObs
    // for (size_t i = 0; i < edgeObs.size(); i++) {
    //     std::cout << edgeObs[i] << std::endl;
    // }
}

// - so for each value of each key in adj list, initialize the edge, 
// if the edge not in obs edge, check if it touch the obs, check if it
//  intersect with obs, if so, change its weight to inf.

void checkEdgeStillWork(Graph & graph, std::vector<Edge> & edgeObs, std::vector<std::vector<std::pair<Node, Node> > > & pairObsVec, std::vector<std::vector<Node> > & obs) {
    // printObs
    // for (size_t i = 0; i < obs.size(); i++) {
    //     std::cout << "obs " << i << ": ";
    //     for (size_t j = 0; j < obs[i].size(); j++) {
    //         std::cout << obs[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    for (size_t i = 0; i < graph.getNumNodes(); i++) { // index
        std::map<size_t, double> adj = graph.getAdj(i); // key value
        for (std::map<size_t, double>::iterator it = adj.begin(); it != adj.end(); ++it) {
            Edge edge = Edge(graph.getNode(i), graph.getNode(it->first));

            // check if it's a obs edge
            if (std::find(edgeObs.begin(), edgeObs.end(), edge) != edgeObs.end()) {
                graph.changeWeight(i, it->first, std::numeric_limits<double>::infinity());
            }
            else {
                // check if it touch the obs
                if (edge.touchObs(obs) || edge.intersectObs(pairObsVec)) {
                    graph.changeWeight(i, it->first, std::numeric_limits<double>::infinity());
                }   
            }
        }
    }
    // print graph's adj list and weight
    // for (size_t i = 0; i < graph.getNumNodes(); i++) {
    //     std::map<size_t, double> adj = graph.getAdj(i);
    //     std::cout << "node " << i << " adj: ";
    //     for (std::map<size_t, double>::iterator it = adj.begin(); it != adj.end(); ++it) {
    //         std::cout << it->first << " " << it->second << " " << std::endl;
    //     }
    // }
}


