#ifndef PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H
#define PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

using namespace std;

template <class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
    Solver<Problem, Solution>* solver;
    CacheManager<Problem, Solution>* cacheManager;
public:
    /// Constructor
    MyTestClientHandler(Solver<Problem, Solution>* s, CacheManager<Problem, Solution>* cm) {
        this->solver = s;
        this->cacheManager = cm;
    }

    /// Destructor
    virtual ~MyTestClientHandler() {}


    virtual void handleClient(int client_socket) {
        int is_sent;
        string bufferStr, problem, solution;
        char* solutionToSend;
        while (true) {
            char buffer[1024] = {0};
            // Read line from client
            read(client_socket, buffer, 1024);
            // Convert to string
            bufferStr = buffer;
            // Get the first part of the string until '\n'
            problem = bufferStr.substr(0, bufferStr.find("\r\n"));
            if (problem == "end") {
                return;
            } else {
                // If solution already exists in the cache
                if (cacheManager->isSolutionExists(problem)) {
                    // Get the solution from the cache
                    solution = cacheManager->getSolution(problem);
                } else {
                    // Get solution from the solver
                    solution = solver->solve(problem);
                    // Insert the problem and its solution to the cache
                    cacheManager->insertSolution(problem, solution);
                }
            }
            solutionToSend = &solution[0];
            // Send solution to client
            is_sent = send(client_socket, solutionToSend, strlen(solutionToSend), 0);
            if (is_sent == -1) {
                cerr << "Could not send solution to client" << endl;
                exit(-1);
            }
        }
    }
};

#endif //PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H
