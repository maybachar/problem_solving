#ifndef PROBLEM_SOLVING_SERVER_H
#define PROBLEM_SOLVING_SERVER_H

#include "ClientHandler.h"

using namespace std;

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop() = 0;
        virtual ~Server() {}
    };
}

#endif //PROBLEM_SOLVING_SERVER_H
