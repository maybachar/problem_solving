#ifndef PROBLEM_SOLVING_STRINGREVERSER_H
#define PROBLEM_SOLVING_STRINGREVERSER_H

#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    StringReverser();
    virtual ~StringReverser();
    virtual string solve(string problem);
};

#endif //PROBLEM_SOLVING_STRINGREVERSER_H
