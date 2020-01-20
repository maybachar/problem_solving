#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "SearcherToSolver.h"
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
        }
/*
        void matrixMain(int argc, char *argv[]) {
            int port = atoi(argv[1]);
            Solver<Searchable<Point*>*, vector<State<Point*>*>>* sr = new SearcherToSolver(new Astar);
            CacheManager<Searchable<Point*>*, vector<State<Point*>*>>* cm = new FileCacheManager<Searchable<Point*>*, vector<State<Point*>*>>();
            ClientHandler* handler = new MyClientHandler<Searchable<Point*>*, vector<State<Point*>*>>(sr, cm);
            server_side::Server* server = new MySerialServer();
            server->open(port, handler);
        }
*/
    };
}


int main(int argc, char *argv[]) {
    boot::Main* main = new boot::Main;
    main->stringReverseMain(argc, argv);
    return 0;
}