#include "SearchSolver.h"
#include "Searcher.h"

/// Constructor
SearchSolver::SearchSolver(Searcher<Point*, vector<State<Point*>*>>* searcherObj) {
    this->searcher = searcherObj;
}

/// Destructor
SearchSolver::~SearchSolver() {}


string SearchSolver::solve(Searchable<Point*>* problem) {
    string path = "";
    vector<string> directions;
    // Get a vector of states in the shortest path
    vector<State<Point*>*> solution = this->searcher->search(problem);
    int pathLength = solution.size(), i;
    Point *currentLocation, *nextLocation;
    // Check the direction needed to move by in order to get to the next state in the path
    for (i = 0; i < pathLength - 1; i++) {
        currentLocation = solution.at(i)->getState();
        nextLocation = solution.at(i + 1)->getState();
        // If points are in the same row in the matrix
        if (currentLocation->getX() == nextLocation->getX()) {
            if (currentLocation->getY() < nextLocation->getY()) {
                directions.push_back("Right");
            } else {
                directions.push_back("Left");
            }
        // If points are in the same column in the matrix
        } else {
            if (currentLocation->getX() < nextLocation->getX()) {
                directions.push_back("Down");
            } else {
                directions.push_back("Up");
            }
        }
    }
    // Create one string from the directions
    for (string direction : directions) {
        path += direction + ",";
    }
    path = path.substr(0, path.size() - 1);
    return path;
}