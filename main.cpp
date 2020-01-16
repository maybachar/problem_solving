#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    (void) argc;
    int port = atoi(argv[1]);
    Solver<string, string>* sr = new StringReverser();
    CacheManager<string, string>* cm = new FileCacheManager<string, string>();
    ClientHandler* handler = new MyTestClientHandler<string, string>(sr, cm);
    server_side::Server* server = new MySerialServer();
    server->open(port, handler);
    return 0;
}