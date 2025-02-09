#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>

class Client
{



    public:
        Client(int port);
        ~Client();
        void start();
        void init();
        void loop();
        void close();

    

    public:
        int m_port;
        int m_clientSocket;
        sockaddr_in m_serverAddress;
        FILE* m_client;
};

#endif