#ifndef PROBLEM_SOLVING_SEARCHER_H
#define PROBLEM_SOLVING_SEARCHER_H

#include <vector>
#include "Searchable.h"

using namespace std;

template <typename T, typename Solution>
class Searcher {
protected:
    double numOfNodesEvaluated = 0;
public:
    virtual ~Searcher() {}

    virtual Solution search(Searchable<T> *searchable) {}

    virtual double getSearcherNumOfNodes(){
        return this->numOfNodesEvaluated;
    }

    virtual vector<State<T>*> backTrace(State<T>* source, State<T>* dest) {
        vector<State<T>*> solution;
        solution.insert(solution.begin(), dest);
        State<T>* node = dest->getCameFrom();
        while (!node->isSource()) {
            solution.insert(solution.begin(), node);
            node = node->getCameFrom();
        }
        solution.insert(solution.begin(), source);
        return solution;
    }
};


#endif //PROBLEM_SOLVING_SEARCHER_H
