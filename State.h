#ifndef PROBLEM_SOLVING_STATE_H
#define PROBLEM_SOLVING_STATE_H

#include <string>

using namespace std;

template <class T>
class State {
    T state;
    // Cost to get to this state
    double cost;
    State<T>* cameFrom = nullptr;
    bool visited;
    bool isInitial = false;
    bool isGoal = false;
public:
    /// Constructor
    State(T stateTemp, double c) {
        this->state = stateTemp;
        this->cost = c;
    }

    /// Destructor
    ~State() {}


    virtual T getState() {
        return this->state;
    }

    virtual void setState(T stateTemp) {
        this->state = stateTemp;
    }

    //overriding Object's Equals method.///////////////////////////////////////////////
    bool equals(State<T>* st) {
        return this->equals(st.state);
    }

    virtual void setCameFrom(State<T*> came) {
        this->cameFrom = came;
    }

    virtual void getCameFrom() {
        return this->cameFrom;
    }

    virtual void setCost(double val) {
        this->cost = val;
    }

    virtual void getCost() {
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
};

#endif //PROBLEM_SOLVING_STATE_H
