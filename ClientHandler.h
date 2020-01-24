#ifndef PROBLEM_SOLVING_CLIENTHANDLER_H
#define PROBLEM_SOLVING_CLIENTHANDLER_H

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
    virtual ClientHandler* deepCopy() = 0;
    virtual ~ClientHandler() {}
};

#endif //PROBLEM_SOLVING_CLIENTHANDLER_H
