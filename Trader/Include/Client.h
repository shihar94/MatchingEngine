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
#include <string>

#include "OrderGenerator.h"

class Client
{



    public:
        Client(int port , std::string& clientID);
        ~Client();
        void start();
        void init();
        void loop();
        void stop();

    

    public:
        int m_port;
        int m_clientSocket;
        sockaddr_in m_serverAddress;
        FILE* m_client;

    private:
        OrderGenerator* orderGenerator;
        std::string m_clientID = "";
};

#endif