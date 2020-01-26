#include "StringReverser.h"

using namespace std;

/// Constructor
StringReverser::StringReverser() {
    this->solverName = "StringReverser";
}

/// Destructor
StringReverser::~StringReverser() {}

/**
 * This function return a reverse string as a solution of a given string problem.
 *
 * @param problem a string.
 * @return the reverse string.
 */
string StringReverser::solve(string problem) {
    int i, n = problem.length();
    string reverseStr = problem;
    //going over the given string from start to the middle of the string.
    for (i = 0; i < n / 2; i++) {
        //swap the location of this char in string to this location from the end in a
        // symmetrical way. so in the end the string will be reversed.
        swap(reverseStr[i], reverseStr[n - i - 1]);
    }
    //return the solution- the reversed string.
    return reverseStr + "\n";
}

/**
 * This function return a deep copy of this string reverse solver-call his constructor.
 *
 * @return new StringReverser solver.
 */
Solver<string,string>* StringReverser::deepCopy() {
    return new StringReverser();
}
