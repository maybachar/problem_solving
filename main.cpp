#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "SearchSolver.h"
#include "Searchable.h"
#include "Point.h"
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
/*
        void matrixMain(int argc, char *argv[]) {
            int port = atoi(argv[1]);
            Searcher<Point*>* searcher = new AStar<Point*>();
            Solver<Searchable<Point*>*, string>* sr = new SearchSolver(searcher);
            CacheManager<Searchable<Point*>*, string>* cm = new FileCacheManager<Searchable<Point*>*, string>();
            ClientHandler* handler = new MyClientHandler<Searchable<Point*>*, string>(sr, cm);
            server_side::Server* server = new MySerialServer();
            server->open(port, handler);
            delete searcher;
            delete sr;
            delete cm;
            delete handler;
            delete server;
        }
*/
    };
}


int main(int argc, char *argv[]) {
    boot::Main* main = new boot::Main;
    main->stringReverseMain(argc, argv);
    return 0;
}