#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "SearchSolver.h"
#include "Searchable.h"
#include "Point.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include <string>
#include <vector>

using namespace std;

namespace boot {
    class Main {
    public:
        void stringReverseMain(int argc, char *argv[]) {
            int port = atoi(argv[1]);
            Solver<string, string>* sr = new StringReverser();
            CacheManager<string, string>* cm = new FileCacheManager<string, string>();
            ClientHandler* handler = new MyTestClientHandler<string, string>(sr, cm);
            server_side::Server* server = new MySerialServer();
            server->open(port, handler);
            delete sr;
            delete cm;
            delete handler;
            delete server;
        }

        void matrixMain(int argc, char *argv[]) {
            int port = atoi(argv[1]);
            //Searcher<Point*, vector<State<Point*>*>>* searcher = new DFS<Point*, vector<State<Point*>*>>();
            Searcher<Point*, vector<State<Point*>*>>* searcher = new AStar<Point*, vector<State<Point*>*>>();
            Solver<Searchable<Point*>*, string>* sr = new SearchSolver(searcher);
            CacheManager<string, string>* cm = new FileCacheManager<string, string>();
            ClientHandler* handler = new MyClientHandler<Searchable<Point*>*, string>(sr, cm);
            server_side::Server* server = new MySerialServer();
            server->open(port, handler);
            delete searcher;
            delete sr;
            delete cm;
            delete handler;
            delete server;
        }

    };
}


int main(int argc, char *argv[]) {
    boot::Main* main = new boot::Main;
    main->matrixMain(argc, argv);
    return 0;
}