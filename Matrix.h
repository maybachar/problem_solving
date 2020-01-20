#ifndef PROBLEM_SOLVING_MATRIX_H
#define PROBLEM_SOLVING_MATRIX_H

#include <vector>
#include "Searchable.h"
#include "Point.h"

using namespace std;

class Matrix : public Searchable<Point*> {
    vector<vector<State<Point*>*>> matrix;
    State<Point*>* initialState;
    State<Point*>* goalState;
public:
    Matrix(vector<vector<State<Point*>*>> mat, State<Point*>* init, State<Point*>* goal);
    ~Matrix();
    virtual State<Point*>* getInitialState();
    virtual State<Point*>* getGoalState();
    virtual bool isGoalState(State<Point*>* state);
    virtual list<State<Point*>*> getAllPossibleStates(State<Point*>* state);
};

#endif //PROBLEM_SOLVING_MATRIX_H
