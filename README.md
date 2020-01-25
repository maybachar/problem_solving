# **Problem Solving**

This program created by Ayelet Tennenboim and May Bachar for Advance Programming course in Bar Ilan university.

## Authors
**Ayelet Tennenboim**
     - ID: 209026517
     - Submit name: tennena
     
**May Bachar**
     - ID: 313370876
     - Submit name: bacharm3

## Intrudoction
This program implement a number of search algorithms, compare who is the most successful, and implement the winner as server-side solver. This project in an advanced programming course is a showcase to our programming experience. The project contains the following elements: use of design and architectural templates, communication and server architecture, use of databases, data streaming, comparison, selection and implementation of algorithms within the system we create and parallel programming using Threads.
In addition, we learned about team work.

## Description
This program creates a server that listens on
the port it get as argument. The server will receive clients either in serial or parallel form (in our case, we were asked to receive 10 clients in a parallel form). The server will finish listening when no client has logged in for 2 minutes and the program is finished. Each client will give a problem to the server which will return the solution using the algorithm which found the best to solve this problem. The server will get a generic problem from the client, in our case the problem is finding the lowest cost path from source to target in a square matrix using the best search algorithm that will return a solution in the shortest path. With a client login the server read the problem data line by line, in our case we will read a matrix, source and destination.With a given problem, we will check quickly whether we have solved it before, so we will get the solution from the existing files instead of calculating it. Otherwise, we will solve the problem and save the solution to a file. Each client's treatment is done in a separate thread. The returned solution use one of the search algorithms we implemented for solving this problem: DFS, BFS, Best first search and A*. From an empirical experiment we conducted, we found that for the matrix problem, algorithm A* returns a path with the lowest cost in the shortest path, i.e., passing the lowest number of vertices from the other algorithms. So, the server will return a solution to this problem using the most efficient algorithm- A*. In this program we use Design patterns like bridge and object adapter. In addition have kept the programming principles solid such as:
open/close and dependency Inversion.

## Start Running
* Compile the program in the linux terminal:
g++ -std=c++14 */*.cpp *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
* Run the program and give a port number as argument.
* conect to server as client, sent a metrix, source, target and write "end". The server will return the solution.

# Files
* main.cpp
* AStar.h
* BestFirstSearch.h
* BFS.h
* CacheManager.h
* ClientHandler.h
* DFS.h
* FileCacheManager.h
* Matrix.cpp
* Matrix.h
* MyClientHandler.h
* MyParallelServer.cpp
* MyParallelServer.h
* MySerialServer.cpp
* MySerialServer.h
* MyTestClientHandler.h
* Point.cpp
* Point.h
* Searchable.h
* Searcher.h
* SearchSolver.cpp
* SearchSolver.h
* Server.h
* Solver.h
* State.h
* StringReverser.cpp
* StringReverser.h

## Attached Files
### Algorithms_experiments

### Matrices - The matrix we checked in the experiment
* Matrix15x15.txt
* Matrix19x19.txt
* Matrix24x24.txt
* Matrix28x28.txt
* Matrix34x34.txt
* Matrix37x37.txt
* Matrix42x42.txt
* Matrix45x45.txt
* Matrix48x48.txt
* Matrix50x50.txt

### Matrices_results
* Matrix_15x15_result.txt
* Matrix_19x19_result.txt
* Matrix_24x24_result.txt
* Matrix_28x28_result.txt
* Matrix_34x34_result.txt
* Matrix_37x37_result.txt
* Matrix_42x42_result.txt
* Matrix_45x45_result.txt
* Matrix_48x48_result.txt
* Matrix_50x50_result.txt

### Graph of the experiment's results
* algorithms_experiment_graph.pdf
* algorithms_graph.ods
