#ifndef PROBLEM_SOLVING_BESTFIRSTSEARCH_H
#define PROBLEM_SOLVING_BESTFIRSTSEARCH_H

#include <queue>
#include "Searchable.h"
#include "Searcher.h"
#include "State.h"

using namespace std;

/**
 * BestFirstSearch Class
 *
 * This class is a generic class implements the Searcher interface.
 * This class is a search algorithm which commit the method search
 * which get a problem and returns a solution,
 * finding the shortest path with the lowest cost path from source to target.
 * This algorithm use each iteration the node with the minimum accumulate cost
 * from source in its search.
 */
template <typename T, typename Solution>
class BestFirstSearch : public Searcher<T,Solution> {
public:
    /// Constructor
    BestFirstSearch() {
        this->searcherName = "BestFirstSearch";
    }

    /// Destructor
    virtual ~BestFirstSearch() {}

    /**
    * This function get a problem and performs the search of algorithm Best
     * first search.
    * It finds the shortest path for the lowest cost path from source to target.
    * This algorithm use in its search the node with the minimum accumulate cost
     * from source.
    * @param searchable the problem we want to solve and return it's solution.
    * @return solution to the received problem.
    */
    virtual Solution search(Searchable<T> *searchable) {
        list<State<T>*> pq;
        vector<State<T>*> successors;
        vector<State<T>*> vec;
        //set the accumulate cost of source to be 0.
        searchable->getInitialState()->setAccumulateCost(0);
        //if the value of source or target is -1 there is no path.
        if (searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return vec;
        }
        // push the source to list.
        pq.push_back(searchable->getInitialState());
        // do the loop until list is empty.
        while(!pq.empty()) {
            this->numOfNodesEvaluated++;
            // get the node with the minimum accumulate cost from source in list.
            State<T>* min = this->findMinAccumulateCost(pq);
            pq.remove(min);
            //check if this current node is the target node- return the path we
            // found from source to target.
            if(searchable->isGoalState(min)) {
                return this->backTrace(searchable->getInitialState(), min);
            }
            //get all the neighbors of current node.
            successors = searchable->getAllPossibleStates(min);
            //for each neighbor.
            for (State<T>* i : successors){
                //if we didn't visit this node already.
                if (i->isVisited() == false){
                    //set this neighbor that we visited it.
                    i->setVisited(true);
                    //push this neighbor to list.
                    pq.push_back(i);
                    //set that we came to this neighbor from the minimum node we
                    // found earlier.
                    i->setCameFrom(min);
                    //we add to accumulate cost of this neighbor the accumulate cost of it's father.
                    i->addToAccumulateCost(i->getCameFrom()->getAccumulateCost());
                }
                    //if we visit this node but the accumulate cost of min(the father)
                    // + the neighbor's cost is smaller than the current accumulate cost
                    // of the neighbor.
                else if (min->getAccumulateCost() + i->getCost() < i->getAccumulateCost()) {
                    //update that we came to this neighbor from min.
                    i->setCameFrom(min);
                    //update the accumulate cost of this neighbor to be the accumulate cost
                    // of min(the updated father) plus the neighbor's cost.
                    i->setAccumulateCost(min->getAccumulateCost() + i->getCost());
                }
            }
            //mark the current minimum that we visited it.
            min->setVisited(true);
        }
        // There is no path found.
        return vec;
    }

    /**
     * This function find the node with the minimum accumulate cost in a given list.
     *
     * @param pq the list we want to find the minimum accumulate cost value from.
     * @return the node with minimum accumulate cost value in the list.
     */
    State<T>* findMinAccumulateCost(list<State<T>*> pq) {
        //set the first in list to be the temp minimum.
        State<T>* min = pq.front();
        //go over the list.
        for(State<T>* i : pq){
            //update the minimum if it find another node with accumulate cost value
            // smaller then the current min.
            if(i->getAccumulateCost() < min->getAccumulateCost()) {
                min = i;
            }
        }
        //return the node with minimum accumulate cost value in the list.
        return min;
    }

    /**
     * This function do a deep copy to this best first search searcher,
     * call it's constructor and returns it.
     *
     * @return a new best first search searcher.
     */
    virtual Searcher<T,Solution>* deepCopy() {
        return new BestFirstSearch();
    }
};

#endif //PROBLEM_SOLVING_BESTFIRSTSEARCH_H

