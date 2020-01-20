#ifndef PROBLEM_SOLVING_SEARCHABLE_H
#define PROBLEM_SOLVING_SEARCHABLE_H

#include <list>
#include "State.h"

using namespace std;

template <class T>
class Searchable {
public:
    ~Searchable() {}
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual bool isGoalState(State<T>*) = 0;
    virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
};

#endif //PROBLEM_SOLVING_SEARCHABLE_H
