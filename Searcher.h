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
        return this->numOfNudesEvaluated;
    }

    virtual vector<State<T>*> backTrace(State<T>* source, State<T>* dest){
        vector<State<T>*> solution;
        solution.push_back(dest);
        State<T*> node = dest->getCameFrom();
        while (!node.equals(source)){
            solution.push_back(node);
            node = node.getCameFrom();
        }
        solution.push_back(source);
        return solution;
    }
};


#endif //PROBLEM_SOLVING_SEARCHER_H
