#include <iostream>

#include <Networking/TCPServer.h>
#include <Networking/TCPSocket.h>

#include <string>
#include <stdexcept>

using std::string;
using std::endl;
using std::cout;
using std::exception;

int notmain(int argc, char **argv) {
    try {
        TCPServer server("0.0.0.0", 1777);
        TCPSocket socket("127.0.0.1", 1777);
        server.acceptWaiting();

        socket.writeString("test send to server");
        cout << server.readString() << endl;

        server.writeString("test send to client");
        cout << socket.readString() << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
