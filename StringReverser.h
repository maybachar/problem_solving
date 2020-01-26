#ifndef PROBLEM_SOLVING_STRINGREVERSER_H
#define PROBLEM_SOLVING_STRINGREVERSER_H

#include "Solver.h"
#include <string>

using namespace std;

/**
 * StringReverser Class
 *
 * This class is implements the interface solver which get a problem a and return
 * a solution.
 * The class knows to solve a given problem- return a reverse string to a given string.
 * It also knows to return a deep copy of StringReverser.
 *
 * @param Problem that we want to solve - a string.
 * @param Solution we solved for a given problem - a reversed string.
 */
class StringReverser : public Solver<string, string> {
public:
    StringReverser();
    virtual ~StringReverser();
    virtual string solve(string problem);
    virtual Solver<string,string>* deepCopy();
};

#endif //PROBLEM_SOLVING_STRINGREVERSER_H

