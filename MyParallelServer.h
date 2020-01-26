#ifndef PROBLEM_SOLVING_MYPARALLELSERVER_H
#define PROBLEM_SOLVING_MYPARALLELSERVER_H

#include <netinet/in.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "ClientHandler.h"

using namespace std;

/**
 * MyParallelServer Class
 *
 * This class implements the Server interface.
 * This class create a server which treats clients in a parallel form.
 * It open a server which open for listening in separate thread, it accept
 * clients so each client is treated by a new client handler in a new thread.
 * So, we can accept and handle clients in parallel form. The server
 * will stop listening after 2 minutes that no client is connected.
 */
class MyParallelServer : public server_side::Server {
    bool shouldStop = false;
    int socketfd;
    thread serverThread;
public:
    MyParallelServer();
    virtual void open(int port, ClientHandler* handler);
    void acceptClient(sockaddr_in address, ClientHandler* handler);
    void handleClients(int client_socket, ClientHandler* handler);
    virtual void stop();
    virtual ~MyParallelServer();
};

#endif //PROBLEM_SOLVING_MYPARALLELSERVER_H
