# Operating Systems Assignment 2

## Setup

Please download both *code.cpp* and *input.txt* into the samed folder.
Ensure that c++ and its compilers have been downloaded.

### Input setup
Feel free to edit the *input.txt* file with whatever values you feel fit, the program works on dynamic resource instance sizes, seperating values with a space ' '. You will need to input the current allocated memory, then the max memory for each program.  
Ex, if the program has 2 of the first memory type allocated and 3 of the second, but it requires 3 of the first and 5 of the second the entire line inside of `input.txt` will look like this
```
2 3 3 5
```
**THE FIRST LINE** is used for initial available resources, it will be shorter than the rest.  
**ENSURE** you input ALL values, even if they are zero, neglecting to do so will force an error in the program.  
*Example*
```
2 4 6 7 //Initial available resources
1 2 3 4 5 0 0 8
1 1 1 1 0 0 9 1
5 8 1 3 6 9 3 6
10 11 1 2 10 12 3 4
```
*Note* - negative values will break the program (and how would that even happen in real life, anyways?)

### Program Setup
The code can be compiled with  
```
g++ code.cpp -o code
```
Or any other compiling method you prefer. 
Running the program is as easy as
```
./code
```
And will produce the console with
```
OUTPUT: P1, P3, P2, etc...
```
If there **IS** a deadlock, the computer will produce the process list as far as it has gotten, followed by an error message
```
Deadlock detected, cannot continue
```

## EXAMPLE USE AND PROOF OF COMPLETION
### SETUP
The input matrix is set up as
```
3 2 2
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 2 1 2 2 2
0 0 2 4 3 3
```
| PROCESS # | ALLOCATED | MAXIMUM |
|----------|----------|----------|
| 1 | A:0 B:1 C:0 | A:7 B:5 C:3 |
| 2 | A:2 B:0 C:0 | A:3 B:2 C:2 |
| 3 | A:3 B:0 C:2 | A:9 B:0 C:2 |
| 4 | A:2 B:2 C:1 | A:2 B:2 C:2 |
| 5 | A:0 B:0 C:2 | A:4 B:3 C:3 |

