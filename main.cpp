#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "SearchSolver.h"
#include "Searchable.h"
#include "Point.h"
#include "AStar.h"
#include "MyParallelServer.h"
#include <string>
#include <vector>

using namespace std;

/**
 * Main class
 *
 * This class contain functions which run the program in different way,
 * for different problems, different server form, different client handler
 * and different solution.
 * we will call in the major main to the suitable function in this class
 * according to the problem we want to solve and run.
 */
namespace boot {
    class Main {
    public:
        /**
         * This function running the program for the string reverse problem.
         * The server treats the clients in a serial form,
         * and send the suitable solution -reverse string, to each client.
         *
         * @param argc number of command line arguments.
         * @param argv command line arguments.
         */
        void stringReverseMain(int argc, char *argv[]) {
            (void) argc;
            int port;
            if (argc < 2) {
                port = 5600;
            } else {
                // Get a port as argument
                port = atoi(argv[1]);
            }
            // Create a solver for the problem
            Solver<string, string>* sr = new StringReverser();
            // Create a cache manager
            CacheManager<string, string>* cm = new FileCacheManager<string, string>();
            // Create a suitable client handler for this string reversing problem
            ClientHandler* handler = new MyTestClientHandler<string, string>(sr, cm);
            // Create a server which treat clients in a serial form
            server_side::Server* server = new MySerialServer();
            server->open(port, handler);
            delete sr;
            delete cm;
            delete handler;
            delete server;
        }

        /**
         * This function running the program for the matrix problem.
         * The server treats the clients in a parallel form,
         * and send the suitable solution, the shortest path of lowest cost path,
         * to each client.
         *
         * @param argc number of command line arguments.
         * @param argv command line arguments.
         */
        void matrixMain(int argc, char *argv[]) {
            (void) argc;
            int port;
            if (argc < 2) {
                port = 5600;
            } else {
                // Get a port as argument
                port = atoi(argv[1]);
            }
            Searcher<Point*, vector<State<Point*>*>>* searcher = new AStar<Point*, vector<State<Point*>*>>();
            Solver<Searchable<Point*>*, string>* sr = new SearchSolver(searcher);
            CacheManager<string, string>* cm = new FileCacheManager<string, string>();
            ClientHandler* handler = new MyClientHandler<Searchable<Point*>*, string>(sr, cm);
            server_side::Server* server = new MyParallelServer();
            server->open(port, handler);
            delete searcher;
            delete sr;
            delete cm;
            delete handler;
            delete server;
        }
    };
}

/**
 * This function is responsible for running the program.
 *
 * @param argc number of command line arguments.
 * @param argv command line arguments.
 * @return 0
 */
int main(int argc, char *argv[]) {
    boot::Main* main;
    // Run the matrix main in class Main
    main->matrixMain(argc, argv);
    return 0;
}
