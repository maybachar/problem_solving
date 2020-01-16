#ifndef PROBLEM_SOLVING_SOLVER_H
#define PROBLEM_SOLVING_SOLVER_H

using namespace std;

template <class Problem, class Solution>
class Solver {
public:
    virtual Solution solve(Problem problem) = 0;
    virtual ~Solver() {}
};

#endif //PROBLEM_SOLVING_SOLVER_H
