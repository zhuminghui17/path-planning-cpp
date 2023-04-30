# Mini Project C++
Due: May 2 12pm 2023

## Path Planning

- Step 1 Read in a graph representation from a file.
- Step 2 Use Dijkstra's algorithm to calculate the shortest path from a start to goal node.
- Step 3 Use Dijkstra's algorithm to calculate the shortest path when there are obstacles.
- Step 4 Use the A* algorithm to calculate the shortest path when there are obstacles.

### Step 1

- [x] Node Class
- [x] Graph Class
- [x] read file and match nodes and edges
- [x] ID starts from zero
- [ ] node type is unsigned integer. ?
- [x] Print it
- [ ] test cases and invalid stuffs
can have zeros nodes

every file needs "$node" "$edge"
format wrong, bug

 The node type is unsigned integer.?
### Step 2

- [ ] Dijkstra's algorithm

### step 3
- read the obs file into std::vector<std::vector<Node> > done
- for obs, add edges for each pairs of node, return the vector of pairs (for one single pair), so it will return a vector of vector of pairs
- also use a set of edges to collect all obs edges
- so for each value of each key in adj list, initialize the edge, if the edge not in obs edge, check if it touch the obs, check if it intersect with obs, if so, change its weight to inf.
- run the dij algo.



multiple $nodes, $edges


### Test cases

gridmap
map1: no 0 index but start from 1, should be wrong


addEdge要检查是否已经有edge

