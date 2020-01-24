#ifndef PROBLEM_SOLVING_SOLVER_H
#define PROBLEM_SOLVING_SOLVER_H

#include <string>

using namespace std;

template <class Problem, class Solution>
class Solver {
protected:
    string solverName;
public:
    virtual Solution solve(Problem problem) = 0;
    virtual ~Solver() {}
    virtual string getName() {
        return this->solverName;
    }
};

#endif //PROBLEM_SOLVING_SOLVER_H
