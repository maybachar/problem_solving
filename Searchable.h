#ifndef PROBLEM_SOLVING_SEARCHABLE_H
#define PROBLEM_SOLVING_SEARCHABLE_H

#include <list>
#include "State.h"

using namespace std;

/**
 * Searchable Class
 *
 * This class is a generic interface representing a problem we want to solve.
 * It knows to get the initial state-the source and also to get the goal state-the target.
 * It knows to return true if a given state is the goal state and false if isn't.
 * It also knows to get a vector of all the possible state of a given state.
 */
template <class T>
class Searchable {
public:
    virtual ~Searchable() {}
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual bool isGoalState(State<T>*) = 0;
    virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
};

#endif //PROBLEM_SOLVING_SEARCHABLE_H
