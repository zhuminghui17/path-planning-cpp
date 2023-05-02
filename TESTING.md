path_planning

# Step 1

1. Run `./path-step1 data/gridmap/sample_input.txt` 
The output should be: 
```
(0,0) (0.5,0) (1,0) (1.5,0) (2,0) (2.5,0) (0,0.4) (0.5,0.4) (1,0.4) (1.5,0.4) (2,0.4) (2.5,0.4) (0,0.8) (0.5,0.8) (1,0.8) (1.5,0.8) (2,0.8) (2.5,0.8) (0,1.2) (0.5,1.2) (1,1.2) (1.5,1.2) (2,1.2) (2.5,1.2) 
0: 1,0.5 6,0.4 7,0.640312 
1: 0,0.5 2,0.5 6,0.640312 7,0.4 8,0.640312 
2: 1,0.5 3,0.5 7,0.640312 8,0.4 9,0.640312 
3: 2,0.5 4,0.5 8,0.640312 9,0.4 10,0.640312 
4: 3,0.5 5,0.5 9,0.640312 10,0.4 11,0.640312 
5: 4,0.5 10,0.640312 11,0.4 
6: 0,0.4 1,0.640312 7,0.5 12,0.4 13,0.640312 
7: 0,0.640312 1,0.4 2,0.640312 6,0.5 8,0.5 12,0.640312 13,0.4 14,0.640312 
8: 1,0.640312 2,0.4 3,0.640312 7,0.5 9,0.5 13,0.640312 14,0.4 15,0.640312 
9: 2,0.640312 3,0.4 4,0.640312 8,0.5 10,0.5 14,0.640312 15,0.4 16,0.640312 
10: 3,0.640312 4,0.4 5,0.640312 9,0.5 11,0.5 15,0.640312 16,0.4 17,0.640312 
11: 4,0.640312 5,0.4 10,0.5 16,0.640312 17,0.4 
12: 6,0.4 7,0.640312 13,0.5 18,0.4 19,0.640312 
13: 6,0.640312 7,0.4 8,0.640312 12,0.5 14,0.5 18,0.640312 19,0.4 20,0.640312 
14: 7,0.640312 8,0.4 9,0.640312 13,0.5 15,0.5 19,0.640312 20,0.4 21,0.640312 
15: 8,0.640312 9,0.4 10,0.640312 14,0.5 16,0.5 20,0.640312 21,0.4 22,0.640312 
16: 9,0.640312 10,0.4 11,0.640312 15,0.5 17,0.5 21,0.640312 22,0.4 23,0.640312 
17: 10,0.640312 11,0.4 16,0.5 22,0.640312 23,0.4 
18: 12,0.4 13,0.640312 19,0.5 
19: 12,0.640312 13,0.4 14,0.640312 18,0.5 20,0.5 
20: 13,0.640312 14,0.4 15,0.640312 19,0.5 21,0.5 
21: 14,0.640312 15,0.4 16,0.640312 20,0.5 22,0.5 
22: 15,0.640312 16,0.4 17,0.640312 21,0.5 23,0.5 
23: 16,0.640312 17,0.4 22,0.5
``` 

2. Run `./path-step1 data/gridmap/sample_input.txt 1`
The output should be 
```
Argument count is not correct! It should be 2!
```
Because the step 1 only read the gridmap file, it only require the file name argument.

3. Run `./path-step1 data/gridmap/fake_input.txt`
The output should be
```
Cannot open file data/gridmap/fake_input.txt, please check the file name or path is right!
```
Because it's a non-existing fake file. 

4. Run `./path-step1 data/gridmap/bugmap_s1_4.txt`
The output should be
```
Invalid Input.
```
Because there is non-numeric in reading nodes (O in line 2).

5. Run `./path-step1 data/gridmap/bugmap_s1_5.txt`
The output should be
```
The input is not numeric!
```
Because there is non-numeric in reading edges (I in line 9).

6. Run `./path-step1 data/gridmap/bugmap_s1_6.txt`
The output should be
```
There is node information missing in the line!
```
Because missing one space in reading nodes.

7. Run `./path-step1 data/gridmap/bugmap_s1_7.txt`
The output should be
```
There is node information missing in the line!
```
Because missing two spaces in reading nodes.

8. Run `./path-step1 data/gridmap/bugmap_s1_8.txt`
The output should be
```
There is edge information missing in the line!
```
Because missing one nodes in reading edges. 

9. Run `./path-step1 data/gridmap/bugmap_s1_9.txt`
The output should be
```
There is node information more than needed in the line!
```
Because there is more items in reading one line of nodes than required.

10. Run `./path-step1 data/gridmap/bugmap_s1_10.txt`
The output should be
```
There is edge information more than needed in the line!
```
Because there is more items in reading one line of edges than required.


11. Run `./path-step1 data/gridmap/bugmap_s1_11.txt`
The output should be
```
The input is not numeric!
```
Because having bugs in reading nodes, charcter in reading nodes. 

12. Run `./path-step1 data/gridmap/bugmap_s1_12.txt`
The output should be
```
The input is not integer!
```
Because having bugs in reading edge, double in edge

13. Run `./path-step1 data/gridmap/bugmap_s1_13.txt`
The output should be
```
$edges is before $nodes!
```
This is one testcase that $edges is above $nodes.

14. Run `./path-step1 data/gridmap/bugmap_s1_14.txt`
The output should be
```
There is unexpected input.
```
This is one testcase that no $nodes header.

15. Run `./path-step1 data/gridmap/bugmap_s1_15.txt`
The output should be
```
There is unexpected input.
```
one test case about reading gridmap: no $edges

16. Run `./path-step1 data/gridmap/bugmap_s1_16.txt`
The output should be
```
The input is not numeric!
```
This is one test case about there are mutliple "$nodes" headers. the program will read it in the process of reading nodes or edges, which leads to a non-numeric or non-integer error. 
 
17. Run `./path-step1 data/gridmap/bugmap_s1_17.txt`
The output should be
```
There is unexpected input.
```
This is one test case about there are mutliple "$edges" headers. In this case, the additional $edges is put at the buttom. 

18. 
Run `./path-step1 data/gridmap/bugmap_s1_18.txt`
The output should be
```
There is a gap in numbering nodes!
```
Because the test cases have missing Node with nodeId 6 but have Node with nodeId 7.

19. 
Run `./path-step1 data/gridmap/goodmap2.txt`
The output should be
```
(2.5,0) (0.5,0) (1,0) (1.5,0) (2,0) (0,0) 
0: 1,0.5 3,1.5 4,2 
1: 0,0.5 2,0.5 5,2 
2: 1,0.5 3,0.5 4,1 
3: 0,1.5 2,0.5 5,1 
4: 0,2 2,1 5,0.5 
5: 1,2 3,1 4,0.5 
```
The test case examine that the program works if the nodes may be listed in any order without any gap in numbering.

20. Run `./path-step1 data/gridmap/empty_input.txt`
The output should be
```

```
The test case is to check if the program works if the nodes and edges are empty. It outputs a empty line.

21. Run `./path-step1 data/gridmap/bugmap_s1_21.txt`
The output should be
```
There is a gap in numbering nodes!
```
The test case it to check if will bug if missing nodeId 0 in my program


# Step 2
1. Run `./path-step2 data/gridmap/sample_input.txt 0 23`
The output should be
```
New best path found: 0 1 : 0.5
New best path found: 0 6 : 0.4
New best path found: 0 7 : 0.640312
New best path found: 0 1 2 : 1
New best path found: 0 1 8 : 1.14031
New best path found: 0 1 2 3 : 1.5
New best path found: 0 1 2 9 : 1.64031
New best path found: 0 1 2 3 4 : 2
New best path found: 0 1 2 3 10 : 2.14031
New best path found: 0 1 2 3 4 5 : 2.5
New best path found: 0 1 2 3 4 11 : 2.64031
New best path found: 0 6 12 : 0.8
New best path found: 0 6 13 : 1.04031
New best path found: 0 7 14 : 1.28062
New best path found: 0 1 8 15 : 1.78062
New best path found: 0 1 2 9 16 : 2.28062
New best path found: 0 1 2 3 10 17 : 2.78062
New best path found: 0 6 12 18 : 1.2
New best path found: 0 6 12 19 : 1.44031
New best path found: 0 6 13 20 : 1.68062
New best path found: 0 7 14 21 : 1.92094
New best path found: 0 1 8 15 22 : 2.42094
New best path found: 0 1 2 9 16 23 : 2.92094

Shortest path found: 0 1 2 9 16 23 : 2.92094
```
It correctly run the Dijkstra's algorithm. It will print the new best path found each time and finally print the shortest path found between the start and goal points and the cost. 


2. Run `./path-step2 data/gridmap/sample_input.txt 0`
The output should be
```
Argument count is not correct! It should be 4!
```
Because step2 program read in the gridmap file and read the start and goal nodeIds. Altogether the argument count is 4. 

3. Run `./path-step2 data/gridmap/sample_input.txt a 23`
The output should be
```
The input is not integer!
```
This is one testcase to check if it will report error if the start-point-id is not `int`.

4. Run `./path-step2 data/gridmap/sample_input.txt 0 a`
The output should be
```
The input is not integer!
```
This is one testcase to check if it will report error if the goal-point-id is not `int`.

5. Run `./path-step2 data/gridmap/sample_input.txt -1 23`
The output should be
```
Node id is not valid in the graph!
```
This is one testcase to check if it will report error if the start-point-id is not valid (not in graph)

6. Run `./path-step2 data/gridmap/sample_input.txt 0 24`
The output should be
```
Node id is not valid in the graph!
```
This is one testcase to check if it will report error if the goal-point-id is not valid (not in graph)

7. Run `./path-step2 data/gridmap/sample_input.txt 0.5 23`
The output should be
```
The input is not integer!
```
This is one testcase to check if it will report error if the start-point-id is not `int` (it's a double).

8. Run `./path-step2 data/gridmap/sample_input.txt 0 23.3`
The output should be
```
The input is not integer!
```
This is one testcase to check if it will report error if the goal-point-id is not `int` (it's a double).

9. Run `./path-step2 data/gridmap/bugmap_s2_9.txt 0 6`
The output should be
```
New best path found: 0 1 : 1
New best path found: 0 2 : 2.91548
New best path found: 0 3 : 1.11803

No path exists
```
This is one testcase to check if it will print "No path exists" and exit with a failure status if there is no path between the start point and end point. It print the new best path it found each time and stop and exit and print "No path exists".

10. Run `./path-step2 data/gridmap/goodmap3.txt 0 3`
The output should be
```
New best path found: 0 1 : 1
New best path found: 0 2 : 1
New best path found: 0 1 3 : 2

Shortest path found: 0 1 3 : 2
```
This is one testcase to check if there are multiple paths with the lowest cost, the algorithm will choose the one to the node with the smallest node ID. In my setting, nodes 0,1,2,3 make a square. the path from 0 to 3: 0 1 3 or 0 2 3, has the same cost. The algorithm choose the one with smallest node ID.

11. Run `./path-step2 data/gridmap/empty_input.txt 1 2`
The output should be
```
Node id is not valid in the graph!
```
The test case is to check if it gives error message when the nodes and edges are empty, but there are start points and goal points input. 


# Step 3
1. Run `./path-step3 data/gridmap/sample_input.txt data/obs/sample_obs.txt 0 23`
the output should be
```
New best path found: 0 1 : 0.5
New best path found: 0 6 : 0.4
New best path found: 0 7 : 0.640312
New best path found: 0 1 8 : 1.14031
New best path found: 0 6 12 : 0.8
New best path found: 0 6 13 : 1.04031
New best path found: 0 6 12 18 : 1.2
New best path found: 0 6 12 19 : 1.44031
New best path found: 0 6 13 20 : 1.68062
New best path found: 0 6 13 20 15 : 2.32094
New best path found: 0 6 13 20 21 : 2.18062
New best path found: 0 6 13 20 15 10 : 2.96125
New best path found: 0 6 13 20 15 16 : 2.82094
New best path found: 0 6 13 20 15 22 : 2.96125
New best path found: 0 6 13 20 15 10 3 : 3.60156
New best path found: 0 6 13 20 15 10 4 : 3.36125
New best path found: 0 6 13 20 15 10 5 : 3.60156
New best path found: 0 6 13 20 15 10 11 : 3.46125
New best path found: 0 6 13 20 15 10 17 : 3.60156
New best path found: 0 6 13 20 15 16 17 : 3.32094
New best path found: 0 6 13 20 15 16 23 : 3.46125
New best path found: 0 6 13 20 21 22 : 2.68062
New best path found: 0 6 13 20 21 22 23 : 3.18062

Shortest path found: 0 6 13 20 21 22 23 : 3.18062
```
This is the correct one with the sample gridmap and obstacles files. 

2. Run `./path-step3 data/gridmap/sample_input.txt data/obs/sample_obs.txt 0`
The output should be 
```
Argument count is not correct! It should be 5!
```
Because step2 program read in the gridmap file, the obstacle file, and read the start and goal nodeIds. Altogether the argument count is 5. 

3. Run `./path-step3 data/gridmap/sample_input.txt data/obs/bugobs_s3_3.txt 0 23`
The output should be
```
no $obstacles header
```
one test case about reading obstacles: no $obstacles header

4. Run `./path-step3 data/gridmap/sample_input.txt data/obs/bugobs_s3_4.txt 0 23`
The output should be
```
It's required to have at least two nodes in each obstacles!
```
the nodes in one line should be at least two to form an obstacle. this test case fail as there is only one. 

5. Run `./path-step3 data/gridmap/sample_input.txt data/obs/bugobs_s3_5.txt 0 23`
The output should be
```
The input is not integer!
```
include invalid obstacles (non-int: character)

6. Run `./path-step3 data/gridmap/sample_input.txt data/obs/bugobs_s3_6.txt 0 23`
The output should be
```
The input is not integer!
```
include invalid obstacles (non-int: double)

7. Run `./path-step3 data/gridmap/sample_input.txt data/obs/bugobs_s3_7.txt 0 23`
The output should be
```
Node id is not valid in the graph!
```
include invalid obstacles (the nodeId is not in the graph)

8. Run `./path-step3 data/gridmap/sample_input.txt data/obs/goodobs1.txt 0 23`
The output should be
```
New best path found: 0 1 : 0.5
New best path found: 0 6 : 0.4
New best path found: 0 7 : 0.640312
New best path found: 0 1 8 : 1.14031
New best path found: 0 6 12 : 0.8
New best path found: 0 6 13 : 1.04031
New best path found: 0 1 8 3 : 1.78062
New best path found: 0 1 8 9 : 1.64031
New best path found: 0 1 8 15 : 1.78062
New best path found: 0 1 8 3 4 : 2.28062
New best path found: 0 1 8 3 10 : 2.42094
New best path found: 0 1 8 3 4 5 : 2.78062
New best path found: 0 1 8 3 4 11 : 2.92094
New best path found: 0 1 8 9 10 : 2.14031
New best path found: 0 1 8 9 16 : 2.28062
New best path found: 0 1 8 9 10 5 : 2.78062
New best path found: 0 1 8 9 10 11 : 2.64031
New best path found: 0 1 8 9 10 17 : 2.78062
New best path found: 0 6 12 18 : 1.2
New best path found: 0 6 12 19 : 1.44031
New best path found: 0 6 13 20 : 1.68062
New best path found: 0 1 8 15 21 : 2.18062
New best path found: 0 1 8 15 22 : 2.42094
New best path found: 0 1 8 9 16 23 : 2.92094

Shortest path found: 0 1 8 9 16 23 : 2.92094
```
This is to show the program if works well with two-node obs.

9. Run `./path-step3 data/gridmap/sample_input.txt data/obs/goodobs2.txt 0 23`
The output should be
```
New best path found: 0 1 : 0.5
New best path found: 0 6 : 0.4
New best path found: 0 7 : 0.640312
New best path found: 0 1 8 : 1.14031
New best path found: 0 6 12 : 0.8
New best path found: 0 6 13 : 1.04031
New best path found: 0 6 12 18 : 1.2
New best path found: 0 6 12 19 : 1.44031
New best path found: 0 6 13 20 : 1.68062
New best path found: 0 6 13 20 15 : 2.32094
New best path found: 0 6 13 20 21 : 2.18062
New best path found: 0 6 13 20 15 16 : 2.82094
New best path found: 0 6 13 20 15 22 : 2.96125
New best path found: 0 6 13 20 15 16 17 : 3.32094
New best path found: 0 6 13 20 15 16 23 : 3.46125
New best path found: 0 6 13 20 21 22 : 2.68062
New best path found: 0 6 13 20 21 22 23 : 3.18062

Shortest path found: 0 6 13 20 21 22 23 : 3.18062
```
This is a test case to check the program if works well with four-node obs.


10. Run `./path-step3 data/gridmap/test_input.txt data/obs/test_obs.txt 0 3`
The output should be
```

No path exists
```
This is a testcase to check if there is no path available (the only path is intersected with the obs) it should print "No path exists" and exit.


# Step 4
1. Run `./path-step4 -a data/gridmap/sample_input.txt data/obs/sample_obs.txt 0 23`
The output should be
```
Using A* algorithm
New best path found: 0 1 : 2.83238
New best path found: 0 6 : 3.02488
New best path found: 0 7 : 2.79438
New best path found: 0 7 8 : 2.84031
New best path found: 0 7 12 : 3.81242
New best path found: 0 7 13 : 3.07992
New best path found: 0 6 12 : 3.3318
New best path found: 0 7 13 18 : 4.18062
New best path found: 0 7 13 19 : 3.44031
New best path found: 0 7 13 20 : 3.18062
New best path found: 0 7 13 20 15 : 3.39797
New best path found: 0 7 13 20 21 : 3.18062
New best path found: 0 7 13 20 21 16 : 3.46125
New best path found: 0 7 13 20 21 22 : 3.18062
New best path found: 0 7 13 20 21 22 17 : 3.72094
New best path found: 0 7 13 20 21 22 23 : 3.18062

Shortest path found: 0 7 13 20 21 22 23 : 3.18062
```

2. 1. Run `./path-step4 data/gridmap/sample_input.txt data/obs/sample_obs.txt 0 23`
The output should be
```
Using Dijkstra's algorithm
New best path found: 0 1 : 0.5
New best path found: 0 6 : 0.4
New best path found: 0 7 : 0.640312
New best path found: 0 1 8 : 1.14031
New best path found: 0 6 12 : 0.8
New best path found: 0 6 13 : 1.04031
New best path found: 0 6 12 18 : 1.2
New best path found: 0 6 12 19 : 1.44031
New best path found: 0 6 13 20 : 1.68062
New best path found: 0 6 13 20 15 : 2.32094
New best path found: 0 6 13 20 21 : 2.18062
New best path found: 0 6 13 20 15 10 : 2.96125
New best path found: 0 6 13 20 15 16 : 2.82094
New best path found: 0 6 13 20 15 22 : 2.96125
New best path found: 0 6 13 20 15 10 3 : 3.60156
New best path found: 0 6 13 20 15 10 4 : 3.36125
New best path found: 0 6 13 20 15 10 5 : 3.60156
New best path found: 0 6 13 20 15 10 11 : 3.46125
New best path found: 0 6 13 20 15 10 17 : 3.60156
New best path found: 0 6 13 20 15 16 17 : 3.32094
New best path found: 0 6 13 20 15 16 23 : 3.46125
New best path found: 0 6 13 20 21 22 : 2.68062
New best path found: 0 6 13 20 21 22 23 : 3.18062

Shortest path found: 0 6 13 20 21 22 23 : 3.18062
```
