#include "Matrix.h"

/// Constructor
Matrix::Matrix(vector<vector<State<Point*>*>> mat, State<Point*>* init, State<Point*>* goal) {
    this->matrix = mat;
    this->initialState = init;
    this->goalState = goal;
    this->rows = mat.size();
    this->columns = mat.at(0).size();
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

vector<State<Point*>*> Matrix::getAllPossibleStates(State<Point*>* state) {
    vector<State<Point*>*> possibleStates;
    int xPos = state->getState()->getX();
    int yPos = state->getState()->getY();
    // If this state can be achieved (the cost is not infinite)
    if (xPos != 0 && this->matrix.at(xPos - 1).at(yPos)->getCost() != -1) {
        possibleStates.push_back(this->matrix.at(xPos - 1).at(yPos));
    }
    if (xPos != this->rows - 1 && this->matrix.at(xPos + 1).at(yPos)->getCost() != -1) {
        possibleStates.push_back(this->matrix.at(xPos + 1).at(yPos));
    }
    if (yPos != 0 && this->matrix.at(xPos).at(yPos - 1)->getCost() != -1) {
        possibleStates.push_back(this->matrix.at(xPos).at(yPos - 1));
    }
    if (yPos != this->columns - 1 && this->matrix.at(xPos).at(yPos + 1)->getCost() != -1) {
        possibleStates.push_back(this->matrix.at(xPos).at(yPos + 1));
    }
    return possibleStates;
}