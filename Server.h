#ifndef PROBLEM_SOLVING_SERVER_H
#define PROBLEM_SOLVING_SERVER_H

#include "ClientHandler.h"

using namespace std;

/**
 * Server Class
 *
 * This class is a server interface.
 * It knows to open a server which will listen to a given port
 * and will accept and handle clients in serial or parallel form.
 * The server will stop listening when time has passed and no client
 * has been connected for a time that is set(in our case 2 minutes).
 */
namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop() = 0;
        virtual ~Server() {}
    };
}

#endif //PROBLEM_SOLVING_SERVER_H

