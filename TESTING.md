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
Invalid format. Please check the format.
```
Because there is non-numeric in reading nodes (O in line 2).

5. Run `./path-step1 data/gridmap/bugmap_s1_5.txt`
The output should be
```
Invalid format. Please check the format.
```
Because there is non-numeric in reading edges (I in line 9).

6. Run `./path-step1 data/gridmap/bugmap_s1_6.txt`
The output should be
```
Invalid Input.
```
Because missing one space in reading nodes.

7. Run `./path-step1 data/gridmap/bugmap_s1_7.txt`
The output should be
```
Invalid Input.
```
Because missing two spaces in reading nodes.

8. Run `./path-step1 data/gridmap/bugmap_s1_8.txt`
The output should be
```
Invalid Input.
```
Because missing one nodes in reading edges. 

9. Run `./path-step1 data/gridmap/bugmap_s1_9.txt`
The output should be
```
Invalid Input.
```
Because there is more items in reading one line of nodes than required.

10. Run `./path-step1 data/gridmap/bugmap_s1_10.txt`
The output should be
```
Invalid Input.
```
Because there is more items in reading one line of edges than required.


11. Run `./path-step1 data/gridmap/bugmap_s1_11.txt`
The output should be
```
Invalid Input.
```
Because stod have bugs in reading nodes

12. Run `./path-step1 data/gridmap/bugmap_s1_12.txt`
The output should be
```
Invalid Input.
```
Because stoi have bugs in reading nodes

13. Run `./path-step1 data/gridmap/bugmap_s1_13.txt`
The output should be
```
Invalid Input.
```
one test case about reading gridmap: $edges is above $nodes

14. Run `./path-step1 data/gridmap/bugmap_s1_14.txt`
The output should be
```
Invalid Input.
```
one test case about reading gridmap: no $nodes

15. Run `./path-step1 data/gridmap/bugmap_s1_15.txt`
The output should be
```
Invalid Input.
```
one test case about reading gridmap: no $edges

16. Run `./path-step1 data/gridmap/bugmap_s1_16.txt`
The output should be
```
Invalid Input.
```
one test case about reading gridmap: more than one "$nodes"
 
17. Run `./path-step1 data/gridmap/bugmap_s1_17.txt`
The output should be
```
Invalid Input.
```
one test case about reading gridmap: more than one "$edges"

18. 
Run `./path-step1 data/gridmap/bugmap_s1_18.txt`
The output should be
```
Invalid Input.
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

# Step 2
