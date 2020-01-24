#include "StringReverser.h"

using namespace std;

/// Constructor
StringReverser::StringReverser() {
    this->solverName = "StringReverser";
}

/// Destructor
StringReverser::~StringReverser() {}

string StringReverser::solve(string problem) {
    int i, n = problem.length();
    string reverseStr = problem;
    for (i = 0; i < n / 2; i++) {
        swap(reverseStr[i], reverseStr[n - i - 1]);
    }
    return reverseStr + "\n";
}

Solver<string,string>* StringReverser::deepCopy() {
    return new StringReverser();
}