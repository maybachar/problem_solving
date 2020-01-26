#ifndef PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H
#define PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H

#include <unistd.h>
#include <cstring>
#include <iostream>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

using namespace std;

/**
 * MyTestClientHandler class
 *
 * The class implements ClientHandler interface.
 * This class reads a problem from a client and sends him a solution.
 * The problem is a string, and the solution is the reverse string.
 */
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

/**
     * The function reads a string from client. It looks for a solution in cache
     * and filesystem. If the solution exists, it sends the solution to the client
     * without solve it again. If solution doesn't exist, the function calls
     * the solver to solve the problem, and sends the solution to the client.
     *
     * @param client_socket number for connection with client.
     */
    virtual void handleClient(int client_socket) {
        int is_sent;
        string bufferStr, problem, fileName, solution;
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
                fileName = this->getFileName(problem);
                // If solution already exists in the cache
                if (cacheManager->isSolutionExists(fileName)) {
                    // Get the solution from the cache
                    solution = cacheManager->getSolution(fileName);
                } else {
                    // Get solution from the solver
                    solution = solver->solve(problem);
                    // Insert the problem and its solution to the cache
                    cacheManager->insertSolution(fileName, solution);
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

    /**
     * The function receives the string received from client and returns a unique
     * number symbolises the string, in order to name the solution file with a
     * unique name.
     *
     * @param clientInput string received from client.
     * @return unique name for the solution file.
     */
    string getFileName(string problem) {
        hash<string> str_hash;
        size_t hashResult;
        hashResult = str_hash(problem);
        return to_string(hashResult);
    }

    /**
     * The function does a deep copy to this client handler. It calls it's constructor
     * and returns the new object.
     *
     * @return new MyTestClientHandler.
     */
    ClientHandler* deepCopy() {
        ClientHandler* newClientHandler = new MyTestClientHandler<Problem, Solution>(this->solver->deepCopy(),this->cacheManager);
        return newClientHandler;
    }
};

#endif //PROBLEM_SOLVING_MYTESTCLIENTHANDLER_H
