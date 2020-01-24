#ifndef PROBLEM_SOLVING_MYPARALLELSERVER_H
#define PROBLEM_SOLVING_MYPARALLELSERVER_H

#include <netinet/in.h>
#include <thread>
#include <vector>
#include "Server.h"

using namespace std;

class MyParallelServer : public server_side::Server {
    bool shouldStop = false;
    int socketfd;
    thread serverThread;
    vector<thread> vecThread;
public:
    MyParallelServer();
    virtual void open(int port, ClientHandler* handler);
    void acceptClient(sockaddr_in address, ClientHandler* handler);
    void handleClients(int client_socket, ClientHandler* handler);
    virtual void stop();
    virtual ~MyParallelServer();
};

#endif //PROBLEM_SOLVING_MYPARALLELSERVER_H
