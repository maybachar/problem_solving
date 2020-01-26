#ifndef PROBLEM_SOLVING_MATRIX_H
#define PROBLEM_SOLVING_MATRIX_H

#include <vector>
#include "Searchable.h"
#include "Point.h"
#include "State.h"

using namespace std;

/**
 * Matrix class
 *
 * This class represents a matrix in which each cell is a state.
 */

class Matrix : public Searchable<Point*> {
    vector<vector<State<Point*>*>> matrix;
    State<Point*>* initialState;
    State<Point*>* goalState;
    int rows;
    int columns;
public:
    Matrix(vector<vector<State<Point*>*>> mat, State<Point*>* init, State<Point*>* goal);
    virtual ~Matrix();
    virtual State<Point*>* getInitialState();
    virtual State<Point*>* getGoalState();
    virtual bool isGoalState(State<Point*>* state);
    virtual vector<State<Point*>*> getAllPossibleStates(State<Point*>* state);
};

#endif //PROBLEM_SOLVING_MATRIX_H
