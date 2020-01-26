#include "MySerialServer.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>

using namespace std;

/// Constructor
MySerialServer::MySerialServer() {}

/// Destructor
MySerialServer::~MySerialServer() {}

/**
 * This function create a socket and bind it to IP address. It also make
 * socket listen to port and set a time so when the time will pass without
 * accept any clients it will stop listening. the handle of clients will apply
 * in another thread.
 *
 * @param port number of port the socket will listen to.
 * @param handler suitable client handler which know how to handle clients.
 */
void MySerialServer::open(int port, ClientHandler* handler) {
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
    if (listen(this->socketfd, 5) == -1) {
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

    // Handle clients.
    this->serverThread = thread(&MySerialServer::acceptClient, this, address, handler);
    this->serverThread.join();
}

/**
 * This function accept a clients in serial form.
 * while the loop shouldn't stop we accepting a client and handle him.
 * After the server finished to handle a client he in available to accept another
 * client and handle him and so on.
 * The server will stop accepting clients when the time has passed and no clients
 * has connected to it for 2 minutes.
 *
 * @param address the socket address.
 * @param handler client handler that handle a client.
 */
void MySerialServer::acceptClient(sockaddr_in address, ClientHandler* handler) {
    while (!this->shouldStop) {
        // Accept client.
        int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                                   (socklen_t *) &address);
        if (client_socket == -1) {
            // Time has passed so stop the while loop and print a massage.
            cerr << "Client has not connected for a long time" << endl;
            this->stop();
        } else {
            cout << "Client is connected" << endl;
            // Handle client.
            handler->handleClient(client_socket);
            cout << "Client is disconnected" << endl;
        }
    }
    // Close the socket.
    close(this->socketfd);
}

/**
 * This function set the field should stop to true so the while loop in
 * accept client will stop.
 */
void MySerialServer::stop() {
    this->shouldStop = true;
}
