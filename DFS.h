#ifndef PROBLEM_SOLVING_DFS_H
#define PROBLEM_SOLVING_DFS_H

#include <stack>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"

using namespace std;

template <typename T, typename Solution>
class DFS : public Searcher<T,Solution> {
public:
    DFS() {
        this->searcherName = "DFS";
    }

    virtual ~DFS() {}

    virtual Solution search(Searchable<T> *searchable) {
        stack<State<T>*> stackD;
        vector<State<T>*> successors;
        State<T>* s;
        vector<State<T>*> vec;
        stackD.push(searchable->getInitialState());
        searchable->getInitialState()->setVisited(true);
        if(searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1){
            return vec;
        }
        while (!stackD.empty()) {
            // Pop a vertex from stack and print it
            s = stackD.top();
            stackD.pop();
            if(searchable->isGoalState(s)) {
                return this->backTrace(searchable->getInitialState(), s);
            }
            // Stack may contain same vertex twice. So
            // we need to print the popped item only
            // if it is not visited.
            if (s->isVisited() == false)
            {
                s->setVisited(true);
                this->numOfNodesEvaluated++;
            }

            // Get all adjacent vertices of the popped vertex s
            // If a adjacent has not been visited, then push it
            // to the stack.
            successors = searchable->getAllPossibleStates(s);
            for (State<T>* i : successors) {
                if (i->isVisited() == false) {
                    stackD.push(i);
                    if(i->getCameFrom() == nullptr) {
                        i->setCameFrom(s);
                    }
                }
            }
        }
        // There is no path.
        return vec;
    }

    virtual Searcher<T,Solution>* deepCopy() {
        return new DFS<T,Solution>();
    }
};

#endif //PROBLEM_SOLVING_DFS_H
