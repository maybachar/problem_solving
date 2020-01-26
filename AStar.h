#ifndef PROBLEM_SOLVING_ASTAR_H
#define PROBLEM_SOLVING_ASTAR_H

#include <queue>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"
#include <set>

using namespace std;

/**
 * AStar Class
 *
 * This class is a generic class implements the Searcher interface.
 * This class is a search algorithm which commit the method search
 * which get a problem and returns a solution, finding the shortest
 * path with the lowest cost path from source to target.
 * This algorithm use in its search with f(n) which is the sum of g(n) and h(n).
 * g(n) is the accumulate cost from start node to n,
 * and h(n) which is the estimated distance from node n to the goal node.
 */
template <typename T, typename Solution>
class AStar : public Searcher<T,Solution> {
public:
    /// Constructor
    AStar() {
        this->searcherName = "AStar";
    }

    /// Destructor
    virtual ~AStar() {}

    /**
     * This function get a problem and performs the search of algorithm A*.
     * It finds the shortest path for the lowest cost path from source to target.
     * This algorithm use in its search with f(n) which is the sum of g(n) and h(n).
     * g(n) is the accumulate cost from start node to n,
     * and h(n) which is the estimated distance from node n to the goal node.
     *
     * @param searchable the problem we want to solve and return it's solution.
     * @return solution to the received problem.
     */
    virtual Solution search(Searchable<T> *searchable) {
        vector<State<T>*> successors;
        set<State<T>*> close;
        set<State<T>*> open;
        State<T>* current;
        vector<State<T>*> vec;
        this->numOfNodesEvaluated = 0;
        //if the value of source or target is -1 there is no path.
        if (searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return vec;
        }
        //the g of source is it's cost.
        searchable->getInitialState()->setG(searchable->getInitialState()->getCost());
        //the f of source is g+h (it's distance to target).
        searchable->getInitialState()->setF(searchable->getInitialState()->getG()+searchable->getInitialState()->getDistanceFromDest());
        open.insert(searchable->getInitialState());
        // do the loop until open set is empty.
        while(!open.empty()) {
            this->numOfNodesEvaluated++;
            //get the node with the minimum f value from open set.
            current = findMinfCost(open);
            //check if this current node is the target node- return the path we found
            // from source to target.
            if(searchable->isGoalState(current)) {
                return this->backTrace(searchable->getInitialState(), current);
            }
            open.erase(current);
            close.insert(current);
            //get all the neighbors of current node.
            successors = searchable->getAllPossibleStates(current);
            //for each neighbor.
            for(State<T>* i : successors){
                //calculate the current neighbor's g value which it's father g value plus the
                // it's cost.
                double tentative_g_score = current->getG() + i->getCost();
                //if this neighbor is already in close set or it's g value we found now isn't
                // smaller then it's g value.
                if(close.find(i) != close.end() || tentative_g_score >= i->getG()) {
                    continue;
                }
                //if the neighbor isn't  in open set or it's g value we found now isn smaller
                // then it's g value.
                if(open.find(i) == open.end() || tentative_g_score < i->getG()) {
                    //set that this neighbor came from current node.
                    i->setCameFrom(current);
                    //set this neighbor's new g value we calculated before.
                    i->setG(tentative_g_score);
                    //set this neighbor's new f.
                    i->setF(i->getG() + i->getDistanceFromDest());
                    //if this neighbor isn't in open set insert it.
                    if (open.find(i) == open.end()){
                        open.insert(i);
                    }
                }
            }
        }
        // There is no path found - return empty vector.
        return vec;
    }

    /**
     * This function goes over the set it get and find the node with the
     * minimum f value.
     *
     * @param pq the set we want to find the minimum f value from.
     * @return the node with minimum f value in the set.
     */
    State<T>* findMinfCost(set<State<T>*> pq) {
        auto myIterator = pq.begin();
        //set the first in set to be the temp minimum.
        State<T>* min = *myIterator;
        //go over the set and update the minimum if it find another node
        // with f value smaller then the current min.
        for (State<T>* i : pq){
            if (i->getF() < min->getF()){
                min = i;
            }
        }
        //return the node with the minimum f value.
        return min;
    }

    /**
     * This function do a deep copy to this A* searcher, call it's constructor
     * and returns it.
     *
     * @return a new A* searcher.
     */
    virtual Searcher<T,Solution>* deepCopy() {
        return new AStar<T,Solution>();
    }
};

#endif //PROBLEM_SOLVING_ASTAR_H

