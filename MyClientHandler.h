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

/**
 * MyClientHandler class
 *
 * The class implements ClientHandler interface.
 * This class reads a problem from a client and sends him a solution.
 * The problem is finding the path with the lowest cost from source
 * to destination in the matrix, and the solution is the path.
 */
template <class Problem, class Solution>
class MyClientHandler : public ClientHandler {
    Solver<Problem, Solution>* solver;
    CacheManager<string, string>* cacheManager;
public:
    /// Constructor
    MyClientHandler(Solver<Problem, Solution>* s, CacheManager<string, string>* cm) {
        this->solver = s;
        this->cacheManager = cm;
    }

    /// Destructor
    virtual ~MyClientHandler() {}

    /**
     * The function reads a matrix from client and also source and destination
     * positions. It creates a matrix object and looks for a solution in cache and
     * filesystem. If the solution exists, it sends the solution to the client
     * without calculate it again. If solution doesn't exist, the function calls
     * the solver to solve the problem, and sends the solution to the client.
     *
     * @param client_socket number for connection with client.
     */
    virtual void handleClient(int client_socket) {
        int is_sent, xPos = 0, yPos = 0, row, col, numOfRows = 0, i;
        double cost;
        string str = "", data = "", dataForMatrix, bufferStr, rest, line, problem, solution, problemStr;
        Matrix* matrixObj = nullptr;
        Point* point;
        State<Point*> *state = nullptr, *initialState = nullptr, *goalState = nullptr;
        vector<State<Point*>*> matrixRow;
        vector<vector<State<Point*>*>> matrix;
        vector<string> clientInput;
        char* solutionToSend;

        // Read matrix from client
        while (line != "end") {
            numOfRows++;
            char buffer[1024] = {0};
            // Read line from client
            read(client_socket, buffer, 1024);
            // Convert to string
            bufferStr = buffer;
            // Concatenate the rest of the string from the previous iteration to the string from the current iteration
            str = str + bufferStr;
            // Get the first part of the string until '\n' or '\r'
            line = str.substr(0, str.find("\r\n"));
            // Remove spaces
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());
            data += line + "\n";
            // Save the rest of the string to the next iteration
            str = str.substr(str.find("\n") + 1, str.length());
        }
        numOfRows -= 3;
        dataForMatrix = data;
        for (i = 0; i < numOfRows; i++) {
            // Get the first part of the string until '\n'
            line = dataForMatrix.substr(0, dataForMatrix.find("\n"));
            // Save the rest of the string to the next iteration
            dataForMatrix = dataForMatrix.substr(dataForMatrix.find("\n") + 1, dataForMatrix.length());
            regex regex(",");
            // Separate the values by ',' and put them in vector
            vector<string> out(
                    sregex_token_iterator(line.begin(), line.end(), regex, -1),
                    sregex_token_iterator());
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
            // Clear the vector for the next iteration
            out.clear();
        }
        regex regex(",|\n");
        // Separate the values by ',' or '\n' and put them in vector
        vector<string> out(
                sregex_token_iterator(dataForMatrix.begin(), dataForMatrix.end(), regex,
                        -1),sregex_token_iterator());
        // If source and destination are the same
        if (out[0] == out[2] && out[1] == out[3]) {
            solution = "Source is also destination, so the lowest cost path is empty.\n";
        } else {
            // Set initial state
            row = stoi(out[0]);
            col = stoi(out[1]);
            matrix.at(row).at(col)->setIsSource();
            initialState = matrix.at(row).at(col);
            // Set goal state
            row = stoi(out[2]);
            col = stoi(out[3]);
            matrix.at(row).at(col)->setIsDest();
            goalState = matrix.at(row).at(col);
            this->setDistancesFromDest(matrix, row, col);
            // Create a new matrix
            matrixObj = new Matrix(matrix, initialState, goalState);

            problemStr = this->problemHashFunc(data);
            // If solution already exists in the cache
            if (cacheManager->isSolutionExists(problemStr)) {
                // Get the solution from the cache
                solution = cacheManager->getSolution(problemStr);
            } else {
                // Get solution from the solver
                solution = solver->solve(matrixObj);
                // Insert the problem and its solution to the cache
                cacheManager->insertSolution(problemStr, solution);
            }
        }
        solutionToSend = &solution[0];
        // Send solution to client
        is_sent = send(client_socket, solutionToSend, strlen(solutionToSend), 0);
        cout << "Path: " << solutionToSend;
        if (is_sent == -1) {
            cerr << "Could not send solution to client" << endl;
            exit(-1);
        }
        close(client_socket);
    }

    /**
     * The function calculates the absolute distance of each state in the matrix
     * from the destination state.
     *
     * @param matrix matrix to search.
     * @param destX x position of destination state.
     * @param destY y position of destination state.
     */
    void setDistancesFromDest(vector<vector<State<Point*>*>> &matrix, int destX, int destY) {
        int rows, columns, i, j, distance;
        rows = matrix.size();
        columns = matrix.at(0).size();
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                distance = abs(i - destX) + abs(j - destY);
                matrix.at(i).at(j)->setDistanceFromDest(distance);
            }
        }
    }

    /**
     * The function receives the input received from client and returns a unique
     * number symbolises the problem & type of the searcher, in order to name the
     * solution file with a unique name.
     *
     * @param clientInput string of the problem received from client.
     * @return unique name for the solution file.
     */
    string problemHashFunc(string clientInput) {
        hash<string> str_hash;
        size_t hashResult;
        string problemStr, solverName = this->solver->getName();
        hashResult = str_hash(clientInput + solverName);
        problemStr = to_string(hashResult);
        return problemStr;
    }

    /**
     * The function does a deep copy to this client handler. It calls it's constructor
     * and returns the new object.
     *
     * @return new MyClientHandler.
     */
    ClientHandler* deepCopy() {
        ClientHandler* newClientHandler = new MyClientHandler<Problem, Solution>(this->solver->deepCopy(),this->cacheManager);
        return newClientHandler;
    }
};


#endif //PROBLEM_SOLVING_MYCLIENTHANDLER_H

