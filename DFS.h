#ifndef PROBLEM_SOLVING_DFS_H
#define PROBLEM_SOLVING_DFS_H

#include <stack>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"

using namespace std;
/**
 * DFS Class
 *
 * This class is a generic class implements the Searcher interface.
 * This class is a search algorithm which commit the method search
 * which get a problem and returns a solution, finding a path from source to target.
 * This algorithm search and going over the nodes in graph from source to depth
 * until it finds the target it looking for or didn't find a path to target.
 */
template <typename T, typename Solution>
class DFS : public Searcher<T,Solution> {
public:
    /// Constructor
    DFS() {
        this->searcherName = "DFS";
    }

    /// Destructor
    virtual ~DFS() {}

    /**
    * This function gets a problem and returns a solution, finding a path from source
     * to target.
    * This algorithm search and going over the nodes in graph to depth using a stack
    * until it finds the target it looking for or didn't find a path to target.
    *
    * @param searchable the problem we want to solve and return it's solution.
    * @return solution to the received problem.
    */
    virtual Solution search(Searchable<T> *searchable) {
        stack<State<T>*> stackD;
        vector<State<T>*> successors;
        State<T>* s;
        vector<State<T>*> vec;
        //push to stack the source node.
        stackD.push(searchable->getInitialState());
        //mark source node as visited
        searchable->getInitialState()->setVisited(true);
        //if the value of source or target is -1 there is no path.
        if(searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1){
            return vec;
        }
        //while stack isn't empty.
        while (!stackD.empty()) {
            // Pop a node from stack.
            s = stackD.top();
            stackD.pop();
            // check if s is the target node- return the path we found from source to target.
            if(searchable->isGoalState(s)) {
                return this->backTrace(searchable->getInitialState(), s);
            }
            // Stack may contain same node twice. So check if it is not visited.
            if (s->isVisited() == false)
            {
                //mark this node as visited.
                s->setVisited(true);
                this->numOfNodesEvaluated++;
            }

            // Get all neighbors nodes of the popped node s.
            successors = searchable->getAllPossibleStates(s);
            //for each neighbor.
            for (State<T>* i : successors) {
                //If a neighbor has not been visited
                if (i->isVisited() == false) {
                    //push this neighbor to stack.
                    stackD.push(i);
                    //update that the neighbor came from s.
                    if(i->getCameFrom() == nullptr) {
                        i->setCameFrom(s);
                    }
                }
            }
        }
        // There is no path.
        return vec;
    }

    /**
    * This function do a deep copy to this DFS searcher, call it's constructor
    * and returns it.
     *
    * @return a new DFS searcher.
    */
    virtual Searcher<T,Solution>* deepCopy() {
        return new DFS<T,Solution>();
    }
};

#endif //PROBLEM_SOLVING_DFS_H
