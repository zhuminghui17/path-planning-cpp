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

4. 
one test case about their is non-numeric in reading nodes

5. 
one test case about their is non-numeric in reading nodes

6. 
one test case about miss one space in reading nodes

7. 
one test case about missing two space in reading nodes

8. 
one test case about missing one space in reading edges

9. 
one test case about reading gridmap: $edges is above $nodes

10. 
one test case about reading gridmap: no $nodes

11. 
one test case about reading gridmap: no $edges

12. 
one test case about reading gridmap: more than one "$nodes"
 
13. 
one test case about reading gridmap: more than one "$edges"

14. 
one test case about reading gridmap: unexpected input TBD


# Step 2