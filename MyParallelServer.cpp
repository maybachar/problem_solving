#include "MyParallelServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>

using namespace std;

/// Constructor
MyParallelServer::MyParallelServer() {}

/// Destructor
MyParallelServer::~MyParallelServer() {}

/**
 * This function create a socket and bind it to IP address. It also make
 * socket listen to port and set a time so when the time will pass without
 * accept any clients it will stop listening. the handle of clients will apply
 * in another thread.
 *
 * @param port number of port the socket will listen to.
 * @param handler suitable client handler which know how to handle clients.
 */
void MyParallelServer::open(int port, ClientHandler* handler) {
    // Create socket.
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        // Error.
        cerr << "Could not create a socket" << endl;
        exit(-1);
    }

    // Bind socket to IP address.
    // We first need to create the sockaddr obj.
    sockaddr_in address; // In means IP4
    address.sin_family = AF_INET;
    // Give me any IP allocated for my machine.
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind command.
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        // Error.
        cerr << "Could not bind the socket to an IP" << endl;
        exit(-2);
    }

    // Make socket listen to the port.
    if (listen(this->socketfd, 10) == -1) {
        // Error.
        cerr << "Error during listening command" << endl;
        exit(-3);
    } else {
        cout << "Server is now listening ..." << endl;
    }

    // Set timeout for client connection.
    struct timeval tv;
    tv.tv_sec = 120;
    tv.tv_usec = 0;
    setsockopt(this->socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    // Handle clients on another thread.
    this->serverThread = thread(&MyParallelServer::acceptClient, this, address, handler);
    serverThread.join();

}

/**
 * This function accept a clients in parallel form.
 * while the loop shouldn't stop we accepting clients and handle each client
 * in a new thread. So, we are handling the client's problem and send him a
 * solution while continuing accepting another clients parallel. The server
 * will stop accepting clients when the time has passed and no clients has
 * connected to it for 2 minutes.
 *
 * @param address the socket address.
 * @param handler client handler that will send to deep copy so the copy will
 * handle a client.
 */
void MyParallelServer::acceptClient(sockaddr_in address, ClientHandler* handler) {
    while (!this->shouldStop) {
        // Accept client.
        int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                                   (socklen_t *) &address);
        if (client_socket == -1) {
            // Time has passed so stop the while loop and print a massage.
            cerr << "Client has not connected for a long time" << endl;
            this->stop();
        } else {
            //Client connected to server.
            cout << "Client is connected" << endl;
            //Create a new thread which will handle the client.
            thread *handleClient = new thread(&MyParallelServer::handleClients, this, client_socket, handler);
            //Detach the thread so will accept another clients in parallel form.
            handleClient->detach();
        }
    }
}

/**
 * This function create a new client handler in the same dynamic type of client
 * handler it get as parameter (deep copy) and handle the client.
 *
 * @param client_socket the client we want to handle.
 * @param handler the client handler we want to deep copy and create a new one
 * from the same dynamic type.
 */
void MyParallelServer::handleClients(int client_socket, ClientHandler *handler) {
    //Create new client handler that will handle this client.
    ClientHandler* newHandler = handler->deepCopy();
    newHandler->handleClient(client_socket);
}

/**
 * This function set the field should stop to true so the while loop in
 * accept client will stop.
 */
void MyParallelServer::stop() {
    this->shouldStop = true;
}


