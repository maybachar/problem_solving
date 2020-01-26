#ifndef PROBLEM_SOLVING_SOLVER_H
#define PROBLEM_SOLVING_SOLVER_H

#include <string>

using namespace std;

/**
 * Solver Class
 *
 * This class is a generic interface which get a problem a and return a solution.
 * The class that will implements this interface knows to solve a given problem.
 * It also knows to return a deep copy of this solver and get the solver name.
 *
 * @param Problem that we want to solve.
 * @param Solution we solved for a given problem.
 */
template <class Problem, class Solution>
class Solver {
protected:
    string solverName;
public:
    virtual ~Solver() {}
    virtual Solution solve(Problem problem) = 0;
    virtual Solver<Problem,Solution>* deepCopy() = 0;

    /**
     * This function return a string of this solver name.
     * @return this solver name.
     */
    virtual string getName() {
        return this->solverName;
    }
};

#endif //PROBLEM_SOLVING_SOLVER_H
