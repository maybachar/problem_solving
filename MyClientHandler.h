#ifndef PROBLEM_SOLVING_MYCLIENTHANDLER_H
#define PROBLEM_SOLVING_MYCLIENTHANDLER_H

#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <iostream>
#include <regex>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "Point.h"
#include "Matrix.h"
#include "State.h"

using namespace std;

template <class Problem, class Solution>
class MyClientHandler : public ClientHandler {
    Solver<Problem, Solution>* solver;
    CacheManager<Problem, Solution>* cacheManager;
public:
    /// Constructor
    MyClientHandler(Solver<Problem, Solution>* s, CacheManager<Problem, Solution>* cm) {
        this->solver = s;
        this->cacheManager = cm;
    }

    /// Destructor
    virtual ~MyClientHandler() {}


    virtual void handleClient(int client_socket) {
        int is_sent, xPos = 0, yPos = 0, iterAfterEnd = 0, row, col;
        double cost;
        string str = "", bufferStr, rest, line, problem, solution;
        Matrix* matrixObj = nullptr;
        Point* point;
        State<Point*> *state = nullptr, *initialState = nullptr, *goalState = nullptr;
        vector<State<Point*>*> matrixRow;
        vector<vector<State<Point*>*>> matrix;
        char* solutionToSend;
        // Read matrix from client
        while (iterAfterEnd <= 2) {
            char buffer[1024] = {0};
            // Read line from client
            read(client_socket, buffer, 1024);
            // Convert to string
            bufferStr = buffer;
            // Concatenate the rest of the string from the previous iteration to the string from the current iteration
            str = str + bufferStr;
            // Get the first part of the string until '\n'
            line = str.substr(0, str.find("\n"));
            // Save the rest of the string to the next iteration
            rest = str.substr(str.find("\n") + 1, str.length());
            regex regex(",");
            // Separate the values by ',' and put them in vector
            vector<string> out(
                    sregex_token_iterator(line.begin(), line.end(), regex, -1),
                    sregex_token_iterator());
            if (line == "end") {
                iterAfterEnd++;
            // Set initial state
            } else if (iterAfterEnd == 1) {
                row = stoi(out[0]);
                col = stoi(out[1]);
                matrix.at(row).at(col)->setIsSource();
                initialState = matrix.at(row).at(col);
                iterAfterEnd++;
            // Set goal state
            } else if (iterAfterEnd == 2) {
                row = stoi(out[0]);
                col = stoi(out[1]);
                matrix.at(row).at(col)->setIsDest();
                goalState = matrix.at(row).at(col);
                // Create a new matrix
                matrixObj = new Matrix(matrix, initialState, goalState);
                break;
            // Create the matrix
            } else {
                // Create vector of one row in the matrix
                for (string s : out) {
                    cost = stod(s);
                    point = new Point(xPos, yPos);
                    state = new State<Point*>(point, cost);
                    matrixRow.push_back(state);
                    yPos++;
                }
                // Insert the row to the matrix
                matrix.push_back(matrixRow);
                matrixRow.clear();
                yPos = 0;
                xPos++;
            }
            // Clear the vector for the next iteration
            out.clear();
            str = rest;
        }

        // If solution already exists in the cache
        if (cacheManager->isSolutionExists(matrixObj)) {
            // Get the solution from the cache
            solution = cacheManager->getSolution(matrixObj);
        } else {
            // Get solution from the solver
            solution = solver->solve(matrixObj);
            // Insert the problem and its solution to the cache
            cacheManager->insertSolution(matrixObj, solution);
        }

        solutionToSend = &solution[0];
        // Send solution to client
        is_sent = send(client_socket, solutionToSend, strlen(solutionToSend), 0);
        if (is_sent == -1) {
            cerr << "Could not send solution to client" << endl;
            exit(-1);
        }
    }
};


#endif //PROBLEM_SOLVING_MYCLIENTHANDLER_H
