#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <thread> 
#include <mutex>
#include <poll.h>
using namespace std;

struct Data
{
    int i;
    int j;
};

class server
{
    public:
        server(int port);
        ~server(){};
        void init();
        void run(); //this is the function where polling takes place

        //virtual functions where derived class server should implement
        virtual void onMessage(int clientSocket);
        virtual void onConnect();
        virtual void onDisconnect();
    
    private:
        void add_client(int client_sock);
        void del_client(std::vector<pollfd>::iterator it);
        void set_reuse_addr(int listen_sock);

    private:
        int m_serverSocket, m_clientSocket;
        int m_port;
        sockaddr_in m_hint;
        sockaddr_in m_client;
        socklen_t m_clientSize = sizeof(m_client);
        std::vector<pollfd> poll_sets;
        pollfd listen_pollfd;
        
};