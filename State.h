#ifndef PROBLEM_SOLVING_STATE_H
#define PROBLEM_SOLVING_STATE_H

#include <string>
#include <limits>

using namespace std;

template <class T>
class State {
    T state;
    // Cost to get to this state
    double cost = 0;
    double accumulateCost = 0;
    bool visited = false;
    bool isInitial = false;
    bool isGoal = false;
    State<T>* cameFrom = nullptr;
    double f = numeric_limits<double>::infinity();
    double g = numeric_limits<double>::infinity();
    double distanceFromDest;
public:
    /// Constructor
    State(T stateTemp, double c) {
        this->state = stateTemp;
        this->cost = c;
        this->accumulateCost = c;
    }

    /// Destructor
    ~State() {}

    T getState() {
        return this->state;
    }

    void setState(T stateTemp) {
        this->state = stateTemp;
    }

    void setCameFrom(State<T>* came) {
        this->cameFrom = came;
    }

    State<T>* getCameFrom() {
        return this->cameFrom;
    }

    double getCost() {
        return this->cost;
    }

    void setVisited(bool val) {
        this->visited = val;
    }

    bool isVisited() {
        return this->visited;
    }

    bool isSource() {
        return this->isInitial;
    }

    void setIsSource() {
        this->isInitial = true;
    }

    bool isDest() {
        return this->isGoal;
    }

    void setIsDest() {
        this->isGoal = true;
    }

    void addToAccumulateCost(double addCost) {
        this->accumulateCost += addCost;
    }

    void setAccumulateCost(double setCost){
        this->accumulateCost = setCost;
    }

    double getAccumulateCost() {
        return this->accumulateCost;
    }

    double getF() {
        return this->f;
    }

    void setF(double fTemp) {
        this->f = fTemp;
    }

    double getG() {
        return this->g;
    }

    void setG(double gTemp) {
        this->g = gTemp;
    }

    void setDistanceFromDest(double distance) {
        this->distanceFromDest = distance;
    }

    double getDistanceFromDest() {
        return this->distanceFromDest;
    }
};

#endif //PROBLEM_SOLVING_STATE_H
