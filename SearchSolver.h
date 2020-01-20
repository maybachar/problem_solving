#ifndef PROBLEM_SOLVING_SEARCHSOLVER_H
#define PROBLEM_SOLVING_SEARCHSOLVER_H

#include <vector>
#include "Solver.h"
#include "Searchable.h"
#include "Point.h"
#include "Searcher.h"

class SearchSolver : public Solver <Searchable<Point*>*, string> {
    Searcher<Point*, vector<State<Point*>*>>* searcher;
public:
    SearchSolver(Searcher<Point*, vector<State<Point*>*>>* searcherObj);
    virtual ~SearchSolver();
    virtual string solve(Searchable<Point*>* problem);
};


#endif //PROBLEM_SOLVING_SEARCHSOLVER_H