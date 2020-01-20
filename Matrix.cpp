#include "Matrix.h"

/// Constructor
Matrix::Matrix(vector<vector<State<Point*>*>> mat, State<Point*>* init, State<Point*>* goal) {
    this->matrix = mat;
    this->initialState = init;
    this->goalState = goal;
}

/// Destructor
Matrix::~Matrix() {}

State<Point*>* Matrix::getInitialState() {
    return this->initialState;
}

State<Point*>* Matrix::getGoalState() {
    return this->goalState;
}

bool Matrix::isGoalState(State<Point*>* state) {
    return state->isDest();
}

list<State<Point*>*> Matrix::getAllPossibleStates(State<Point*>* state) {

}