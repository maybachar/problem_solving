#include "SearcherToSolver.h"
#include "Searcher.h"

/// Constructor
SearcherToSolver::SearcherToSolver(Searcher<Point*, vector<State<Point*>*>>* searcherObj) {
    this->searcher = searcherObj;
}

/// Destructor
SearcherToSolver::~SearcherToSolver() {}


vector<State<Point*>*> SearcherToSolver::solve(Searchable<Point*>* problem) {
    return this->searcher->search(problem);
}