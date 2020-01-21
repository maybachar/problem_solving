#ifndef PROBLEM_SOLVING_BFS_H
#define PROBLEM_SOLVING_BFS_H

#include <queue>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"

using namespace std;

template <typename T, typename Solution>
class BFS : public Searcher <T,Solution> {
    queue<State<T>*> queueB;
    vector<State<T>*> successors;
    State<T>* n;
    vector<State<T>*> vec;
public:
    BFS() {}

    virtual ~BFS() {}

    virtual Solution search(Searchable<T> *searchable) {
        queueB.push(searchable->getInitialState());
        searchable->getInitialState()->setVisited(true);
        if(searchable->getInitialState()->getCost() == -1 && searchable->getGoalState()->getCost() == -1){
            return vec;
        }
        while (!queueB.empty()){
            this->numOfNodesEvaluated++;
            n = queueB.front();
            queueB.pop();
            if(searchable->isGoalState(n)){
                return this->backTrace(searchable->getInitialState(), n);
            }
            successors = searchable->getAllPossibleStates(n);
            for(State<T>* i : successors){
                if(i->isVisited() == false && i->getCost() != -1){
                    i->setVisited(true);
                    i->setCameFrom(n);
                    queueB.push(i);
                }
            }
        }
        //there is no path.
        return vec;
    }
};

#endif //PROBLEM_SOLVING_BFS_H
