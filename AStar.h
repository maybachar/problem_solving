#ifndef PROBLEM_SOLVING_ASTAR_H
#define PROBLEM_SOLVING_ASTAR_H

#include <queue>
#include "State.h"
#include "Searchable.h"
#include "Searcher.h"
#include <set>

using namespace std;

template <typename T, typename Solution>
class AStar : public Searcher<T,Solution> {
public:
    AStar() {
        this->searcherName = "AStar";
    }

    virtual ~AStar() {}

    virtual Solution search(Searchable<T> *searchable) {
        vector<State<T>*> successors;
        set<State<T>*> close;
        set<State<T>*> open;
        State<T>* current;
        vector<State<T>*> vec;
        this->numOfNodesEvaluated = 0;
        if (searchable->getInitialState()->getCost() == -1 || searchable->getGoalState()->getCost() == -1) {
            return vec;
        }
        searchable->getInitialState()->setG(searchable->getInitialState()->getCost());
        searchable->getInitialState()->setF(searchable->getInitialState()->getG()+searchable->getInitialState()->getDistanceFromDest());
        open.insert(searchable->getInitialState());
        while(!open.empty()) {
            this->numOfNodesEvaluated++;
            current = findMinfCost(open);
            if(searchable->isGoalState(current)) {
                return this->backTrace(searchable->getInitialState(), current);
            }
            open.erase(current);
            close.insert(current);
            successors = searchable->getAllPossibleStates(current);
            for(State<T>* i : successors){
                double tentative_g_score = current->getG() + i->getCost();
                if(close.find(i) != close.end() || tentative_g_score >= i->getG()) {
                    continue;
                }
                if(open.find(i) == open.end() || tentative_g_score < i->getG()) {
                    i->setCameFrom(current);
                    i->setG(tentative_g_score);
                    i->setF(i->getG() + i->getDistanceFromDest());
                    if (open.find(i) == open.end()){
                        open.insert(i);
                    }
                }
            }
        }
        // There is no path
        return vec;
    }

    State<T>* findMinfCost(set<State<T>*> pq) {
        auto myIterator = pq.begin();
        State<T>* min = *myIterator;
        for (State<T>* i : pq){
            if (i->getF() < min->getF()){
                min = i;
            }
        }
        return min;
    }

    virtual Searcher<T,Solution>* deepCopy() {
        return new AStar<T,Solution>();
    }
};

#endif //PROBLEM_SOLVING_ASTAR_H
