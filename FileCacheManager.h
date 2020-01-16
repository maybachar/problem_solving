#ifndef PROBLEM_SOLVING_FILECACHEMANAGER_H
#define PROBLEM_SOLVING_FILECACHEMANAGER_H

#include <unordered_map>
#include <fstream>
#include <iostream>
#include "CacheManager.h"

using namespace std;

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
public:
    /// Constructor
    FileCacheManager() {}

    /// Destructor
    virtual ~FileCacheManager() {}

    virtual bool isSolutionExists(Problem problem) {
        return (this->problemsFiles.find(problem) != this->problemsFiles.end());
    };

    virtual Solution getSolution(Problem problem) {
        Solution obj;
        string file_name;
        if (this->isSolutionExists(problem)) {
            // If the key exists in the cache
            if (this->cache.find(problem) != this->cache.end()) {
                // Update the key to be the most recently used
                this->lru_list.push_front(*this->cache.find(problem)->second);
                this->lru_list.erase(this->cache.find(problem)->second);
                this->cache[problem] = this->lru_list.begin();
                // Return the object that matches the key
                return this->cache.find(problem)->second->second;
                // If the key exists in the filesystem (it means that the file is open)
            } else {
                file_name = this->problemsFiles.find(problem)->second;
                // Open a file for reading in binary mode
                ifstream in_file(file_name, ios::binary);
                // Read the object from the binary input file
                in_file.read((char *) &obj, sizeof(obj));
                // Close the file
                in_file.close();
                // Insert key and object into the cache
                this->insertSolution(problem, obj);
                return obj;
            }
            // If key doesn't exist both in cache and filesystem
        } else {
            cerr << "Error: key does not exist" << endl;
        }
    }

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
        ofstream out_file {file_name, ios::binary};
        // Check if the file is open
        if (!out_file) {
            throw "Error: output file could not be opened";
        } else {
            // Write the object to the binary output file
            out_file.write((char *) &solution, sizeof(solution));
            // Close the file
            out_file.close();
            // Insert the problem and the file name to the files map
            this->problemsFiles.insert({problem,file_name});
        }
    }
};

#endif //PROBLEM_SOLVING_FILECACHEMANAGER_H
