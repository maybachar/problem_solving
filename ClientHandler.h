#ifndef PROBLEM_SOLVING_CLIENTHANDLER_H
#define PROBLEM_SOLVING_CLIENTHANDLER_H

using namespace std;

/**
 * ClientHandler Interface
 *
 * This class is an interface to classes that are responsible for handling clients.
 */
class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
    virtual ClientHandler* deepCopy() = 0;
    virtual ~ClientHandler() {}
};

#endif //PROBLEM_SOLVING_CLIENTHANDLER_H
