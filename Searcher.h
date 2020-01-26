#ifndef PROBLEM_SOLVING_SEARCHER_H
#define PROBLEM_SOLVING_SEARCHER_H

#include <vector>
#include "Searchable.h"
#include "State.h"

using namespace std;

/**
 * Searcher Class
 *
 * This class is a generic interface representing a searcher which will solve a search
 * problem. It knows to get the number of nodes evaluated for solving this problem and
 * to get the searcher name.
 * It also knows how so search and return a solution to a given searchable problem.
 * It knows to deep copy a specific searcher and to do back trace which will return
 * a vector of states representing a path as a solution to the problem.
 */
template <typename T, typename Solution>
class Searcher {
protected:
    int numOfNodesEvaluated = 0;
    string searcherName;
public:
    virtual ~Searcher() {}

    virtual Solution search(Searchable<T> *searchable) = 0;

    /**
     * This function return number of nodes evaluated for solving a problem and get
     * from source to target.
     *
     * @return number of nodes evaluated for solving a problem.
     */
    virtual int getNumOfNodesEvaluated() {
        return this->numOfNodesEvaluated;
    }

    /**
     * This function return the name of this searcher.
     *
     * @return name of this searcher.
     */
    virtual string getName() {
        return this->searcherName;
    }

    virtual Searcher<T,Solution>* deepCopy() = 0;

    /**
     * This function gets a source and a target and return a vector
     * of states which representing a path as a solution to the problem.
     * It start from the target node and insert it to the returning vector. It get
     * to the node it came from in the path it found as a solution to the problem in
     * the search function and insert him also to vector. so on until we get to the
     * source node and return the path from source to target in vector.
     *
     * @param source the initial node.
     * @param dest the target node.
     * @return vector of states which representing a path from source to target
     * (the solution to the problem).
     */
    virtual vector<State<T>*> backTrace(State<T>* source, State<T>* dest) {
        vector<State<T>*> solution;
        //Insert the target to the vector.
        solution.insert(solution.begin(), dest);
        //The father node that the target is came from.
        State<T>* node = dest->getCameFrom();
        //While the node isn't the source node.
        while (!node->isSource()) {
            //Insert the node to vector.
            solution.insert(solution.begin(), node);
            //Get the node it came from.
            node = node->getCameFrom();
        }
        //insert the source node to vector.
        solution.insert(solution.begin(), source);
        //return the vector of states which representing a path from source to target.
        return solution;
    }
};

#endif //PROBLEM_SOLVING_SEARCHER_H

