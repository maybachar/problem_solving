#ifndef PROBLEM_SOLVING_STATE_H
#define PROBLEM_SOLVING_STATE_H

#include <string>
#include <limits>

using namespace std;

/**
 * State class
 *
 * This generic class state is holds the information of a node in graph which
 * represent a problem and used in algorithms. Each state has it's cost-value, it's
 * accumulate cost from source, is g value (accumulate cost from source), it's
 * distance from destination and f value(the sum of g value and distance from dest).
 * Each state knows the state it came from in a path in the graph.
 * Each state knows if it mark as visited in the algorithm which using it, if it
 * is the initial node and if it is the goal node.
 *
 * @param T template we get for defining this state.
 */
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

    /**
     * This function return the templates type which defining the state.
     *
     * @return T the type which defining the state.
     */
    T getState() {
        return this->state;
    }

    /**
     * This function set where this state is came from with a given state.
     *
     * @param came the state we want to set with the cameFrom filed.
     */
    void setCameFrom(State<T>* came) {
        this->cameFrom = came;
    }

    /**
     * This function return the state that this state has came from.
     *
     * @return the state this state has came from.
     */
    State<T>* getCameFrom() {
        return this->cameFrom;
    }

    /**
     * This function return the state's cost- it's value.
     *
     * @return this state's cost.
     */
    double getCost() {
        return this->cost;
    }

    /**
     * This function set the filed visited with true if we want to mark
     * it as visited or false if not.
     *
     * @param val to set with the visited field-true if this state is visited or
     * false if isn't.
     */
    void setVisited(bool val) {
        this->visited = val;
    }

    /**
     * This function return true if this state has been visited or false if isn't.
     *
     * @return true if this state has been visited or false if isn't.
     */
    bool isVisited() {
        return this->visited;
    }

    /**
     * This function return true if this state is the source node or false if isn't.
     *
     * @return true if this state is the source node or false if isn't.
     */
    bool isSource() {
        return this->isInitial;
    }

    /**
     * This function mark this state as source node (true).
     */
    void setIsSource() {
        this->isInitial = true;
    }

    /**
     * This function return true if this state is the target node or false if isn't.
     *
     * @return true if this state is the target node or false if isn't.
     */
    bool isDest() {
        return this->isGoal;
    }

    /**
     * This function mark this state as target node (true).
     */
    void setIsDest() {
        this->isGoal = true;
    }

    /**
     * This function add a given cost to the accumulate cost field.
     *
     * @param addCost the cost we wand to add to the accumulate cost field.
     */
    void addToAccumulateCost(double addCost) {
        this->accumulateCost += addCost;
    }

    /**
     * This function set the value of the accumulateCost field with a given value.
     *
     * @param setCost the value we want to set with the accumulateCost field.
     */
    void setAccumulateCost(double setCost){
        this->accumulateCost = setCost;
    }

    /**
     * This function return the accumulateCost value.
     *
     * @return the accumulateCost value.
     */
    double getAccumulateCost() {
        return this->accumulateCost;
    }

    /**
     * This function return the field F value.
     *
     * @return the field F value.
     */
    double getF() {
        return this->f;
    }

    /**
     * This function set the F field with a given value.
     *
     * @param fTemp a given value we want to set with the field F.
     */
    void setF(double fTemp) {
        this->f = fTemp;
    }

    /**
     * This function return the field G value.
     *
     * @return the field G value.
     */
    double getG() {
        return this->g;
    }

    /**
     * This function set the G field with a given value.
     *
     * @param gTemp a given value we want to set with the field G.
     */
    void setG(double gTemp) {
        this->g = gTemp;
    }

    /**
     * This function set the field distanceFromDest with a given value.
     *
     * @param distance the value we want to set with the field distanceFromDest.
     */
    void setDistanceFromDest(double distance) {
        this->distanceFromDest = distance;
    }

    /**
     * This function return the value of the field distanceFromDest
     * (the distance of this state from target).
     *
     * @return the value of the field distanceFromDest.
     */
    double getDistanceFromDest() {
        return this->distanceFromDest;
    }
};

#endif //PROBLEM_SOLVING_STATE_H

