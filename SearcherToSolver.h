#ifndef PROBLEM_SOLVING_SEARCHERTOSOLVER_H
#define PROBLEM_SOLVING_SEARCHERTOSOLVER_H

#include <vector>
#include "Solver.h"
#include "Searchable.h"
#include "Point.h"
#include "Searcher.h"


// problem: Searchable<Point*>* (matrix)
// solution: string created from the vector of the states in the path

class SearcherToSolver : public Solver <Searchable<Point*>*, string> {
    Searcher<Point*, vector<State<Point*>*>>* searcher;
public:
    SearcherToSolver(Searcher<Point*, vector<State<Point*>*>>* searcherObj);
    virtual ~SearcherToSolver();
    virtual string solve(Searchable<Point*>* problem);
};


#endif //PROBLEM_SOLVING_SEARCHERTOSOLVER_H
