#ifndef PROBLEM_SOLVING_CACHEMANAGER_H
#define PROBLEM_SOLVING_CACHEMANAGER_H

#include <string>
#include <list>
#include <unordered_map>

using namespace std;

/**
 * CacheManager Interface
 *
 * This class is an interface to classes that are responsible for keeping program
 * data and receiving it quickly when it is needed.
 */
template <class Problem, class Solution>
class CacheManager {
protected:
    int capacity = 5;
    list<pair<Problem,Solution>> lru_list;
    typename list<pair<Problem,Solution>>::iterator itr;
    unordered_map<string, typename list<pair<Problem,Solution>>::iterator> cache;
public:
    virtual bool isSolutionExists(Problem problem) = 0;
    virtual Solution getSolution(Problem problem) = 0;
    virtual void insertSolution(Problem problem, Solution solution) = 0;
    virtual ~CacheManager() {}
};

#endif //PROBLEM_SOLVING_CACHEMANAGER_H
