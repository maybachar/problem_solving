# **Problem Solving**

This program created by Ayelet Tennenboim and May Bachar for Advanced Programming course in Bar Ilan university.

## Authors
**Ayelet Tennenboim**

**May Bachar**


## Introduction
This program implement a number of search algorithms, compare who is the most successful, and implement the winner as server-side solver.

This project in an advanced programming course is a showcase to our programming experience.
The project contains the following elements: use of design and architectural templates, communication and server architecture, use of databases, data streaming, comparison, selection and implementation of algorithms within the system we create and parallel programming using Threads.

In addition, we learned about team work.


## Description
This program creates a server that listens on the port it get as argument.
The server can receive clients either in serial or parallel form (in our case, we were asked to receive 10 clients in a parallel form).

The server finishes listening when no client is logged in for 2 minutes and the program is finished. Each client gives a problem to the server which returns the solution using the algorithm which found the best to solve this problem. The server gets a generic problem from the client. In our case the problem is finding the lowest cost path from source to target in a matrix using the best search algorithm.

With a client login, the server reads the problem data line by line. In our case, the server reads a matrix with source and destination positions. With a given problem, it checks quickly whether was solved before, so it will get the solution from the existing files instead of calculating it. Otherwise, it solves the problem and save the solution in a file.

Each client's treatment is done in a separate thread. The returned solution uses one of the search algorithms implemented for solving this problem: DFS, BFS, Best first search and A*.

From an empirical experiment conducted, it was found that for the matrix problem, algorithm A* returns the lowest cost path in the shortest way, i.e. passing the lowest number of vertices from the other algorithms.
So, the server returns a solution to this problem using the most efficient algorithm - A*.

In this program we used Design patterns like bridge and object adapter.
In addition have kept the programming principles solid such as:
open/close and dependency Inversion.


## Start Running
* Compile the program in the linux terminal:
```
g++ -std=c++14 *.cpp *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
* Run the program and give a port number as argument:
```
./a.out port_number
```
* Connect to server as client, send a matrix, source and destination and write "end". The server will return the solution.


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
### algorithms_experiment

#### Matrices_results
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

#### Graph of the experiment's results
* algorithms_experiment_graph.pdf


## Links
* GitHub: https://github.com/maybachar/problem_solving
