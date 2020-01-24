#include "MyParallelServer.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>

using namespace std;

/// Constructor
MyParallelServer::MyParallelServer() {}

/// Destructor
MyParallelServer::~MyParallelServer() {}

void MyParallelServer::open(int port, ClientHandler* handler) {
    // Create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        // Error
        cerr << "Could not create a socket" << endl;
        exit(-1);
    }

    // Bind socket to IP address.
    // We first need to create the sockaddr obj.
    sockaddr_in address; // In means IP4
    address.sin_family = AF_INET;
    // Give me any IP allocated for my machine
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind command
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        // Error
        cerr << "Could not bind the socket to an IP" << endl;
        exit(-2);
    }

    // Make socket listen to the port
    if (listen(this->socketfd, 10) == -1) {
        // Error
        cerr << "Error during listening command" << endl;
        exit(-3);
    } else {
        cout << "Server is now listening ..." << endl;
    }

    // Set timeout for client connection
    struct timeval tv;
    tv.tv_sec = 120;
    tv.tv_usec = 0;
    setsockopt(this->socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    // Handle clients
    this->serverThread = thread(&MyParallelServer::acceptClient, this, address, handler);
    serverThread.join();

}

void MyParallelServer::acceptClient(sockaddr_in address, ClientHandler* handler) {
    while (!this->shouldStop) {
        // Accept client
        int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                                   (socklen_t *) &address);
        if (client_socket == -1) {
            // Error
            cerr << "Client has not connected for a long time" << endl;
            this->stop();
        } else {
            cout << "Client is connected" << endl;
            thread *handle = new thread(&MyParallelServer::handleClients, this, client_socket, handler);
            handle->detach();
        }
    }
}

void MyParallelServer::handleClients(int client_socket, ClientHandler *handler) {
    //new client handler
    ClientHandler* newHandler = handler->deepCopy();
    newHandler->handleClient(client_socket);
}
void MyParallelServer::stop() {
    this->shouldStop = true;
}


