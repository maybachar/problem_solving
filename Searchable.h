#ifndef PROBLEM_SOLVING_SEARCHABLE_H
#define PROBLEM_SOLVING_SEARCHABLE_H

#include <list>
#include "State.h"

using namespace std;

template <class T>
class Searchable {
public:
    ~Searchable() {}
    virtual State<T>* getInitialState();
    virtual State<T>* getGoalState();
    virtual bool isGoalState(State<T>*);
    virtual list<State<T>*> getAllPossibleStates(State<T>*);
};

#endif //PROBLEM_SOLVING_SEARCHABLE_H
