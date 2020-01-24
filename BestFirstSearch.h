#ifndef PROBLEM_SOLVING_BESTFIRSTSEARCH_H
#define PROBLEM_SOLVING_BESTFIRSTSEARCH_H

#include <queue>
#include "Searchable.h"
#include "Searcher.h"
#include "State.h"

using namespace std;

template <typename T, typename Solution>
class BestFirstSearch : public Searcher<T,Solution> {
    list<State<T>*> pq;
    vector<State<T>*> successors;
    vector<State<T>*> vec;
public:
    BestFirstSearch() {
        this->searcherName = "BestFirstSearch";
    }

    virtual ~BestFirstSearch() {}

    virtual Solution search(Searchable<T> *searchable) {
        searchable->getInitialState()->setAccumulateCost(0);
        if (searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return vec;
        }
        pq.push_back(searchable->getInitialState());
        while(!pq.empty()) {
            this->numOfNodesEvaluated++;
            State<T>* min = this->findMinAccumulateCost(pq);
            pq.remove(min);
            if(searchable->isGoalState(min)) {
                return this->backTrace(searchable->getInitialState(), min);
            }
            successors = searchable->getAllPossibleStates(min);
            for (State<T>* i : successors){
                if (i->isVisited() == false){
                    i->setVisited(true);
                    pq.push_back(i);
                    i->setCameFrom(min);
                    i->addToAccumulateCost(i->getCameFrom()->getAccumulateCost());
                }
                else if (min->getAccumulateCost() + i->getCost() < i->getAccumulateCost()) {
                    i->setCameFrom(min);
                    i->setAccumulateCost(min->getAccumulateCost() + i->getCost());
                }
            }
            min->setVisited(true);
        }
        // There is no path
        return vec;
    }

    State<T>* findMinAccumulateCost(list<State<T>*> pq) {
        State<T>* min = pq.front();
        for(State<T>* i : pq){
            if(i->getAccumulateCost() < min->getAccumulateCost()) {
                min = i;
            }
        }
        return min;
    }
};

#endif //PROBLEM_SOLVING_BESTFIRSTSEARCH_H
