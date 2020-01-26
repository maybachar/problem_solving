#ifndef PROBLEM_SOLVING_BFS_H
#define PROBLEM_SOLVING_BFS_H

#include <queue>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"

using namespace std;

/**
 * BFS Class
 *
 * This class is a generic class implements the Searcher interface.
 * This class is a search algorithm which commit the method search
 * which get a problem and returns a solution,
 * finding a path from source to target.
 * This algorithm search and going over the nodes in graph to breadth
 * until it finds the target it looking for or didn't find a path to target.
 */
template <typename T, typename Solution>
class BFS : public Searcher <T,Solution> {
public:
    /// Constructor
    BFS() {
        this->searcherName = "BFS";
    }

    /// Destructor
    virtual ~BFS() {}

    /**
    * This function get a problem and performs the search of algorithm BFS-Breadth first search.
    * It finds a path from source to target.
    * This algorithm in its search going the nodes in the graph in breadth form,
    * It starts traversing the graph from root node and explores all the neighbouring nodes.
    * Then, it selects the nearest node and explore all the unexplored nodes.
    * The algorithm follows the same process for each of the nearest node until it finds the goal
    * or didn't find a path after going over all the possible nodes in graph.
     *
    * @param searchable the problem we want to solve and return it's solution.
    * @return solution to the received problem.
    */
    virtual Solution search(Searchable<T> *searchable) {
        queue<State<T>*> queueB;
        vector<State<T>*> successors;
        State<T>* n;
        vector<State<T>*> vec;
        //push the source node to queue.
        queueB.push(searchable->getInitialState());
        //mark the source as visited.
        searchable->getInitialState()->setVisited(true);
        //if the value of source or target is -1 there is no path.
        if(searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return vec;
        }
        // do the loop until queue is empty.
        while (!queueB.empty()) {
            this->numOfNodesEvaluated++;
            //get the first node in queue.
            n = queueB.front();
            queueB.pop();
            //check if n is the target node- return the path we found from source to target.
            if(searchable->isGoalState(n)) {
                return this->backTrace(searchable->getInitialState(), n);
            }
            //get all the neighbors of current n node.
            successors = searchable->getAllPossibleStates(n);
            //for each neighbor.
            for(State<T>* i : successors){
                //if we didn't visit already this neighbor and it's value isn't -1 (no path).
                if(i->isVisited() == false && i->getCost() != -1) {
                    //mark this neighbor as visited.
                    i->setVisited(true);
                    //update that we came to this neighbor from n.
                    i->setCameFrom(n);
                    //insert this neighbor to queue.
                    queueB.push(i);
                }
            }
        }
        // There is no path.
        return vec;
    }

    /**
     * This function do a deep copy to this BFS searcher, call it's constructor
     * and returns it.
     *
     * @return a new BFS searcher.
     */
    virtual Searcher<T,Solution>* deepCopy() {
        return new BFS<T,Solution>();
    }
};

#endif //PROBLEM_SOLVING_BFS_H

