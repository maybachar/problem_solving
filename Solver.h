#ifndef PROBLEM_SOLVING_SOLVER_H
#define PROBLEM_SOLVING_SOLVER_H

#include <string>

using namespace std;

template <class Problem, class Solution>
class Solver {
protected:
    string solverName;
public:
    virtual ~Solver() {}
    virtual Solution solve(Problem problem) = 0;
    virtual string getName() {
        return this->solverName;
    }
    virtual Solver<Problem,Solution>* deepCopy() = 0;
};

#endif //PROBLEM_SOLVING_SOLVER_H
