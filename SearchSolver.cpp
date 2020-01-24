#include <iostream>
#include "SearchSolver.h"
#include "Searcher.h"

/// Constructor
SearchSolver::SearchSolver(Searcher<Point*, vector<State<Point*>*>>* searcherObj) {
    this->searcher = searcherObj;
}

/// Destructor
SearchSolver::~SearchSolver() {}


string SearchSolver::solve(Searchable<Point*>* problem) {
    string path = "", totalCostStr;
    vector<string> directions;
    // Get a vector of states in the shortest path
    vector<State<Point*>*> solution = this->searcher->search(problem);
    // If there is no path
    if (solution.empty()) {
        return "There is no path from source to destination\n";
    }
    int totalCost = solution.at(0)->getCost();
    int pathLength = solution.size(), i, numOfNodesEvaluated = this->searcher->getNumOfNodesEvaluated();
    Point *currentLocation, *nextLocation;
    // Check the direction needed to move by in order to get to the next state in the path
    for (i = 0; i < pathLength - 1; i++) {
        currentLocation = solution.at(i)->getState();
        nextLocation = solution.at(i + 1)->getState();
        totalCostStr = to_string(totalCost += solution.at(i + 1)->getCost());
        // If points are in the same row in the matrix
        if (currentLocation->getX() == nextLocation->getX()) {
            if (currentLocation->getY() < nextLocation->getY()) {
                directions.push_back("Right (" + totalCostStr + ")");
            } else {
                directions.push_back("Left (" + totalCostStr + ")");
            }
        // If points are in the same column in the matrix
        } else {
            if (currentLocation->getX() < nextLocation->getX()) {
                directions.push_back("Down (" + totalCostStr + ")");
            } else {
                directions.push_back("Up (" + totalCostStr + ")");
            }
        }
    }
    // Create one string from the directions
    for (string direction : directions) {
        path += direction + " ,";
    }
    path = path.substr(0, path.size() - 1);
    path += "\n";
    cout << "Number of nodes evaluated: " << numOfNodesEvaluated << endl;
    return path;
}

string SearchSolver::getName() {
    return this->searcher->getName();
}

Solver<Searchable<Point*>*, string>* SearchSolver::deepCopy() {
    Searcher<Point*, vector<State<Point*>*>>* newSearcher = this->getSearcher()->deepCopy();
    return new SearchSolver(newSearcher);
}