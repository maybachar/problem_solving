#ifndef PROBLEM_SOLVING_SEARCHER_H
#define PROBLEM_SOLVING_SEARCHER_H

#include <vector>
#include "Searchable.h"

using namespace std;

template <typename T, typename Solution>
class Searcher {
protected:
    int numOfNodesEvaluated = 0;
    string searcherName;
public:
    virtual ~Searcher() {}

    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual int getNumOfNodesEvaluated() {
        return this->numOfNodesEvaluated;
    }

    virtual string getName() {
        return this->searcherName;
    }

    virtual Searcher<T,Solution>* deepCopy() = 0;

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
