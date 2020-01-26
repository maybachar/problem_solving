#ifndef PROBLEM_SOLVING_FILECACHEMANAGER_H
#define PROBLEM_SOLVING_FILECACHEMANAGER_H

#include <unordered_map>
#include <fstream>
#include <iostream>
#include "CacheManager.h"

using namespace std;

/**
 * FileCacheManager class
 *
 * The class implements CacheManager interface.
 * This class is responsible for saving solutions to problems that were solved
 * in previous program runs, so when the program receives a problem that is already
 * resolved in the past, it can returns the solution without the need to
 * recalculate it.
 * The solutions are saved in cache and in files.
 */

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
public:
    /// Constructor
    FileCacheManager() {}

    /// Destructor
    virtual ~FileCacheManager() {}

    /**
     * The function receives a problem and checks if solution exists in cache
     * or in files.
     *
     * @param problem a problem that needs to be solved.
     * @return true - if solution exits, false - otherwise.
     */
    virtual bool isSolutionExists(Problem problem) {
        string file_name = problem + ".txt";
        // If Solution exists in cache
        if (this->cache.find(problem) != this->cache.end()) {
            return true;
        } else {
            ifstream in_file(file_name);
            // If solution exists in the filesystem
            if (in_file) {
                return true;
            } else {
                return false;
            }
        }
    }

    /**
     * The function returns the solution that matches the problem, either from
     * cache or filesystem.
     *
     * @param problem a problem that needs to be solved.
     * @return solution to the problem.
     */
    virtual Solution getSolution(Problem problem) {
        Solution obj;
        string file_name = problem + ".txt";
        if (this->isSolutionExists(problem)) {
            // If the key exists in the cache
            if (this->cache.find(problem) != this->cache.end()) {
                // Update the key to be the most recently used
                this->lru_list.push_front(*this->cache.find(problem)->second);
                this->lru_list.erase(this->cache.find(problem)->second);
                this->cache[problem] = this->lru_list.begin();
                // Return the object that matches the key
                return this->cache.find(problem)->second->second;
            // If the key exists in the filesystem
            } else {
                // Open a file for reading in binary mode
                ifstream in_file(file_name);
                // Check if the file is open
                if (!in_file) {
                    cerr << "Error: input file could not be opened" << endl;
                }
                // Read the object from the input file
                getline(in_file, obj);
                obj += '\n';
                // Close the file
                in_file.close();
                // Insert key and object into the cache
                this->insertSolution(problem, obj);
                return obj;
            }
        // If key doesn't exist both in cache and filesystem
        } else {
            cerr << "Error: problem does not exist" << endl;
            exit (-1);
        }
    }

    /**
     * The function inserts problem and solution into cache and filesystem.
     *
     * @param problem a problem that needs to be solved.
     * @param solution solution to the problem.
     */
    virtual void insertSolution(Problem problem, Solution solution) {
        Problem least_rec_used;
        string file_name = problem + ".txt";
        // If the key doesn't exist in the cache
        if (this->cache.find(problem) == this->cache.end()) {
            // If the cache is full
            if (this->cache.size() == (unsigned) this->capacity) {
                // Remove the least recently used object from the lru list and the cache
                least_rec_used = this->lru_list.back().first;
                this->lru_list.pop_back();
                this->cache.erase(least_rec_used);
            }
            // Insert the new pair (key and object) into the lru list
            this->lru_list.push_front({problem,solution});
            // Insert the new pair into the map
            this->cache.insert({problem, this->lru_list.begin()});
        // If the key exists in the cache
        } else {
            // Update the key to be the most recently used
            this->lru_list.erase(this->cache.find(problem)->second);
            this->lru_list.push_front({problem,solution});
            // Update the object in the cache
            this->cache[problem] = this->lru_list.begin();
        }
        // Open a file for writing in binary mode
        ofstream out_file (file_name);
        // Check if the file is open
        if (!out_file) {
            cerr << "Error: output file could not be opened" << endl;
        } else {
            // Write the object to the binary output file
            out_file << solution << endl;
            // Close the file
            out_file.close();
        }
    }
};

#endif //PROBLEM_SOLVING_FILECACHEMANAGER_H
