#ifndef PROBLEM_SOLVING_MYSERIALSERVER_H
#define PROBLEM_SOLVING_MYSERIALSERVER_H
#include <netinet/in.h>
#include <thread>
#include "Server.h"

using namespace std;

class MySerialServer : public server_side::Server {
    bool shouldStop = false;
    int socketfd;
    thread serverThread;
public:
    MySerialServer();
    virtual void open(int port, ClientHandler* handler);
    void acceptClient(sockaddr_in address, ClientHandler* handler);
    virtual void stop();
    virtual ~MySerialServer();
};

#endif //PROBLEM_SOLVING_MYSERIALSERVER_H
