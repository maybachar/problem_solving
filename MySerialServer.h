#ifndef PROBLEM_SOLVING_MYSERIALSERVER_H
#define PROBLEM_SOLVING_MYSERIALSERVER_H

#include <netinet/in.h>
#include <thread>
#include "Server.h"
#include "ClientHandler.h"

using namespace std;

/**
 * MySerialServer Class
 *
 * This class implements the Server interface.
 * This class create a server which treats clients in a serial form.
 * It open a server which open for listening in separate thread, it accept a client
 * that connected to it, handle him and then it is available for accepting another
 * client and so on- in a serial form. The server will stop listening after 2 minutes
 * that no client is connected.
 */
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
